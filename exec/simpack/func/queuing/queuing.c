/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

/* This is a set of routines for discrete event simulation.
It was inspired by both CSIM (Herb Schwetman) and SMPL
(M. H. MacDougall). The syntax is very similar to SMPL's
with the exceptions as noted in the file README.
*/

/* SET MAXIMUMS HERE!! ------------------------------ */
#define MAX_TOKENS 20000 /* max. number of tokens going through the system */
#define MAX_SERVERS 1000 /* max. number of servers for a facility */
#define MAX_FACILITIES 1000 /* max. number of facilities */
#define MAX_NUM_ATTR 5 /* max. number of attributes for an entity */
#define HEAP_SIZE 50000 /* max. heap size */
#define CALQSPACE 49153     /* calendar array size needed for maximum resize */
#define MAXNBUCKETS 32768     /* maximum number of buckets in calendar queue */
/* SET MAXIMUMS HERE!! ------------------------------ */


/* Set the type of system. Three are supported:
   (1) UNIX   -  UNIX System C (normal UNIX setting)
   (2) UNIXX  -  UNIX System C without Curses (used to generate
                 a smaller executable. You cannot access visual
                 trace facility with this option.
   (3) TURBOC -  Borland Turbo C (setting for IBM/PC and compatibles)

   NOTE: set one flag to the value '1' and the rest to '0'.
*/
#define UNIX    1
#define UNIXX   0
#define TURBOC  0

#define NIL 0 
#define FREE 0 
#define BUSY 1 
#define ON 1
#define OFF 0
#define FOUND 1
#define NOT_FOUND -1
#define TIME_KEY 0
#define AHEAD_PRIORITY_KEY 1
#define BEHIND_PRIORITY_KEY 2
#define INTERACTIVE 0
#define BATCH 1
#define LINKED 0
#define HEAP 1
#define CALENDAR 2
#define HENRIK 3
#define INOMIAL 4
#define LEFTIST 5
#define PAGODA 6
#define PAIR 7
#define SKEWDN 8
#define SKEWUP 9
#define SPLAY 10
#define TWOLIST 11
#define REMOVE_DUPLICATES 16
#define RESEED 32

#include <malloc.h>
#include <stdio.h> 
#include <math.h>

#if UNIX
#include <curses.h>
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef struct {
  float attr[MAX_NUM_ATTR];
} TOKEN;

typedef struct item{
  float time;
  int event;
  TOKEN token;
  int priority;
} ITEM;

typedef struct node {
  ITEM item;
  struct node *next;
} NODE;

typedef struct {
  NODE *front;
  int size;
} LIST;

typedef struct {
  LIST queue;
  int status;
  char name[25];
  int total_servers;
  int busy_servers;
  float total_busy_time;
  float start_busy_time;
  int preemptions;
  int server_info[MAX_SERVERS][2];
} FACILITY;

struct tokenstruct {
  int event;
  float time;
  float first_arg;
  float second_arg;
} token_list[MAX_TOKENS+1];

typedef struct calist *calptr;         /* type of a pointer to a calist node */
struct calist {          /* node type for a linked list of pointers to items */
  ITEM entry;               /* these are used in the calendar queue routines */
  calptr next;
};
calptr calq[CALQSPACE];                    /* array of linked lists of items */
calptr *calendar;                   /* pointer to use as a sub-array to calq */

int calfirstsub,
    nbuckets, calqsize, lastbucket, calresize_enable;   /* global variables- */
float caltop_threshold, calbot_threshold, lastprio;     /* for the calendar- */
double buckettop, calendar_width;                       /* queueing routines */

#include "merged.c"

float current_time,sim_time(),busy_time(),last_event_time;
float total_token_time;
int current_event,facilities,status(),arrivals,completions;
int tokens_in_system,trace_flag,trace_type,heap_count;
int event_list_type,remove_duplicates;
char current_operation[100];
LIST event_list;
ITEM heap[HEAP_SIZE],an_item,item1;
FACILITY facility[MAX_FACILITIES];

/* Performance variables */
float utilization,idle,arrival_rate,throughput,total_sim_time;
float total_busy_time;
float total_utilization;
float mean_service_time,mean_num_tokens,mean_residence_time;

/* Declarations for random distribution sampling */

#define then

#define A 16807L           /* multiplier (7**5) for 'ranf' */
#define M 2147483647L      /* modulus (2**31-1) for 'ranf' */

long In[] = {0L,           /* seeds for streams 1 thru 15  */
  1973272912L,  747177549L,   20464843L,  640830765L, 1098742207L,
    78126602L,   84743774L,  831312807L,  124667236L, 1172177002L,
  1124933064L, 1223960546L, 1878892440L, 1449793615L,  553303732L};

int strm=1;                /* index of current stream */


/* -------------------------------------------------------------------- */


/************************************************************************/
/*                                                                      */
/* init_simpack:                                                        */
/*      Initialize data structures and variables for simulation.        */
/*                                                                      */
/************************************************************************/
init_simpack(flags)
int flags;
{
  static int rn_stream = 1;
  int i,type;
  int ranmark;
  type = flags & 15;
  ranmark = flags & 32;
  remove_duplicates = flags & 16;
  /* initialize token list table */
  for (i=0;i<MAX_TOKENS;i++) token_list[i].event = 99999;
  event_list_type = type;
  create_list(&event_list);
  heap_count = 0;
  trace_flag = OFF;
  current_time = 0.0;
  last_event_time = current_time;
  facilities = 0;
  arrivals = 0;
  completions = 0;
  total_token_time = 0;
  tokens_in_system = 0;
/*  printf("list type: %d\n",event_list_type); */
  switch (event_list_type) {
  case LINKED:
  case HEAP: break;
  case CALENDAR: calendar_init(); break;
  case HENRIK: hinitqueue(&hqq); break;
  case INOMIAL: iinitqueue(&iqq); break;
  case LEFTIST: linitqueue(&lqq); break;
  case PAGODA: pinitqueue(&pqq); break;
  case PAIR: ainitqueue(&aqq); break;
  case SKEWDN: kinitqueue(&kqq); break;
  case SKEWUP: sinitqueue(&sqq); break;
  case SPLAY: yinitqueue(&yqq); break;
  case TWOLIST: tinitqueue(&tqq); break;
  }
  calresize_enable = TRUE;

  /* set random number stream */
  rn_stream = stream(rn_stream);
/* this next part is included so that one may run multiple passes
   with different data structures for the FEL but generate the same
   random number stream for easy comparison.  To use this, call
   init_simpack with the flags binary or'ed with RESEED  */
  if (ranmark) {
    In[0] = 0L;
    In[1] = 1973272912L;
    In[2] = 747177549L;
    In[3] = 20464843L;
    In[4] = 640830765L;
    In[5] = 1098742207L;
    In[6] = 78126602L;
    In[7] = 84743774L;
    In[8] = 831312807L;
    In[9] = 124667236L;
    In[10] = 1172177002L;
    In[11] = 1124933064L;
    In[12] = 1223960546L;
    In[13] = 1878892440L;
    In[14] = 1449793615L;
    In[15] = 553303732L;
  }
  else rn_stream++;
  if (rn_stream > 15) rn_stream = 1;
} /* end init() */


void end_simpack()
{
  int i;
  ITEM an_item;
  switch (event_list_type) {
  case LINKED: listblankqueue(&(event_list.front)); break;
  case HEAP: break;
  case CALENDAR: clearcalqueue(); break;
  case HENRIK: hclearqueue(&hqq); break;
  case INOMIAL: iclearqueue(&(iqq.leftmostroot)); break;
  case LEFTIST: lclearqueue(&lqq); break;
  case PAGODA: pclearqueue(&pqq); break;
  case PAIR: aclearqueue(&aqq); break;
  case SKEWDN: yclearqueue(&kqq); break;
  case SKEWUP: sclearqueue(&sqq); break;
  case SPLAY: yclearqueue(&yqq); break;
  case TWOLIST: tclearqueue(&(tqq.sorted)); 
                tclearqueue(&(tqq.unsorted)); break;
  }
  for (i=facilities;i>0;i--) {
    while (!empty_list(&(facility[i].queue)))
      remove_front_list(&(facility[i].queue),&an_item);
  } 
}

/************************************************************************/
/*                                                                      */
/* time:                                                                */
/*      Provide the current simulation time.                            */
/*                                                                      */
/************************************************************************/
float sim_time()
{
  return(current_time);
} /* end time() */




/************************************************************************/
/*                                                                      */
/* busy_time:                                                           */
/*      Provide total accumulated busy time for a facility.             */
/*                                                                      */
/************************************************************************/
float busy_time(facility_id)
int facility_id;
{
  return(facility[facility_id].total_busy_time); 
}




/************************************************************************/
/*                                                                      */
/* update_arrivals:                                                     */
/*      Update # of arrivals into a system.                             */
/*                                                                      */
/************************************************************************/
update_arrivals()
{
  arrivals++;
  tokens_in_system++;
}




/************************************************************************/
/*                                                                      */
/* update_completions:                                                  */
/*      Update # of completions out of a system.                        */
/*                                                                      */
/************************************************************************/
update_completions()
{
  completions++;
  tokens_in_system--;
}




/************************************************************************/
/*                                                                      */
/* status:                                                              */
/*      Return facility status.                                         */
/*                                                                      */
/************************************************************************/
int status(facility_id)
int facility_id;
{
  return(facility[facility_id].status);
}

/************************************************************************/
/*                                                                      */
/* status:                                                              */
/*      Return facility queue size.       f                              */
/*                                                                      */
/************************************************************************/
int facility_size(facility_id)
int facility_id;
{
  return(facility[facility_id].queue.size);
}




/************************************************************************/
/*                                                                      */
/* create_facility:                                                     */
/*      Setup a facility with a given number of servers.                */
/*                                                                      */
/************************************************************************/
int create_facility(name,num_servers)
char *name;
int num_servers;
{ int i;

  facilities++;
  create_list(&facility[facilities].queue);
  facility[facilities].status = FREE;
  strcpy(facility[facilities].name,name);
  facility[facilities].total_servers = num_servers;
  facility[facilities].busy_servers = 0;

  /* clear servers */
  for (i=1;i<=num_servers;i++) {
   facility[facilities].server_info[i][0] = 0;
   facility[facilities].server_info[i][1] = 0;
  } /* end for */

  facility[facilities].preemptions = 0;
  facility[facilities].total_busy_time = 0.0;
  return(facilities);
} /* end facility() */




/************************************************************************/
/*                                                                      */
/* schedule:                                                            */
/* Schedule a given event in a given time.                              */
/*                                                                      */
/************************************************************************/
schedule(event,inter_time,token)
int event;
float inter_time;
TOKEN token;
{
  float event_time;
  ITEM an_item;
  int i,token_id;

        /* If in remove-duplicates mode then do not schedule this item if it */
        /* is already in the future event list.                              */
  token_id = (int) token.attr[0] % MAX_TOKENS;
  event_time = current_time + inter_time;
  if ((!remove_duplicates) ||
      (token_list[token_id].event != event) ||
      (token_list[token_id].time != event_time) ||
      (token_list[token_id].first_arg != token.attr[1]) ||
      (token_list[token_id].second_arg != token.attr[2])) {

    token_list[token_id].event = event;
    token_list[token_id].time = event_time;
    token_list[token_id].first_arg = token.attr[1];
    token_list[token_id].second_arg = token.attr[2];

                                                   /* update trace if active */
    sprintf(current_operation,
            "BEFORE SCHEDULE Event %2d Inter-Time %5.1f Token %3d",
            event,inter_time,(int) token.attr[0]);
    trace_update();

    an_item.time = event_time;
    an_item.event = event;
    for (i=0;i<MAX_NUM_ATTR;i++)
      an_item.token.attr[i] = token.attr[i];

    switch (event_list_type) {
    case LINKED: insert_list(&event_list,&an_item,TIME_KEY); break;
    case CALENDAR: calendar_insert(&an_item); break;
    case HEAP: heap_insert(an_item); break;
    case HENRIK: henqueue(an_item,&hqq); break;
    case INOMIAL: ienqueue(an_item,&iqq); break;
    case LEFTIST: lenqueue(an_item,&lqq); break;
    case PAGODA: penqueue(an_item,&pqq); break;
    case PAIR: aenqueue(an_item,&aqq); break;
    case SKEWDN: kenqueue(an_item,&kqq); break;
    case SKEWUP: senqueue(an_item,&sqq); break;
    case SPLAY: yenqueue(an_item,&yqq); break;
    case TWOLIST: tenqueue(an_item,&tqq); break;
    }


                                                   /* update trace if active */
    sprintf(current_operation,
            "AFTER SCHEDULE Event %2d Inter-Time %5.1f Token %3d",
            event,inter_time,(int) token.attr[0]);
    trace_update();
  } /* end if */
} /* end schedule() */




/************************************************************************/
/*                                                                      */
/* next_event:                                                          */
/* Cause an event to occur and return it in the given pointers.         */
/*                                                                      */
/************************************************************************/
next_event(event_ptr,token_ptr)
int *event_ptr;
TOKEN *token_ptr;
{
  ITEM an_item;


                                                   /* update trace if active */
  strcpy(current_operation,"BEFORE NEXT_EVENT");
  trace_update();

  switch (event_list_type) {
  case LINKED: remove_front_list(&event_list,&an_item); break;
  case CALENDAR: calendar_remove(&an_item); break;
  case HEAP: heap_remove(&an_item); break;
  case HENRIK: an_item = hdequeue(&hqq); break;
  case INOMIAL: an_item = idequeue(&iqq); break; 
  case LEFTIST: an_item = ldequeue(&lqq); break;
  case PAGODA: an_item = pdequeue(&pqq); break;
  case PAIR: an_item = adequeue(&aqq); break;
  case SKEWDN: an_item = kdequeue(&kqq); break;
  case SKEWUP: an_item = sdequeue(&sqq); break;
  case SPLAY: an_item = ydequeue(&yqq); break;
  case TWOLIST: an_item = tdequeue(&tqq); break;
  }
  current_time = an_item.time;
  current_event = an_item.event;
  *event_ptr = an_item.event;
  *token_ptr = an_item.token;

                                                   /* update trace if active */
  sprintf(current_operation,"AFTER NEXT_EVENT Event %2d Token %3d",
          *event_ptr,(int) (*token_ptr).attr[0]);
  trace_update();

                      /* update the total token-time spent within the system */
  total_token_time += tokens_in_system*(sim_time() - last_event_time);
  last_event_time = sim_time();
} /* end next_event() */




/************************************************************************/
/*                                                                      */
/* cancel_event:                                                        */
/*      Remove the given event from the queue.                          */
/*                                                                      */
/************************************************************************/
int cancel_event(event)
int event;
{
  NODE *current_node,*previous_node,*temp_ptr;
  LIST *list_ptr;

                                                   /* update trace if active */
  sprintf(current_operation,"BEFORE CANCEL_EVENT Event %2d",
          event);
  trace_update();

                                 /* search event list for that token's entry */
  list_ptr = &event_list;
  current_node = list_ptr->front;
  previous_node = list_ptr->front;
  while ((current_node != NIL) && 
         (current_node->item.event != event)) {
    previous_node = current_node;
    current_node = current_node->next;
  } /* end while */
              /* we are pointing at list node to be deleted - save node info */
  if (current_node == NIL)
    return(NOT_FOUND);
  else {
                                      /* delete this node and return token # */
    if (previous_node == current_node ) {
                                     /* token is the first on the event list */
      temp_ptr = (NODE *) list_ptr->front;
      list_ptr->front = current_node->next;
      cfree(temp_ptr);
    }
    else {
      temp_ptr = (NODE *) current_node;
      previous_node->next = current_node->next;
      cfree(temp_ptr);
    }
    list_ptr->size--;
                                                   /* update trace if active */
    sprintf(current_operation,"AFTER CANCEL_EVENT Event %2d (Token %3d)",
            event,(int) current_node->item.token.attr[0]);
    trace_update();

    return((int) current_node->item.token.attr[0]);
  }
} /* end cancel_event */




/************************************************************************/
/*                                                                      */
/* cancel_token:                                                        */
/*      Remove the given token from consideration.                      */
/*                                                                      */
/************************************************************************/
int cancel_token(token)
TOKEN token;
{
  NODE *current_node,*previous_node,*temp_ptr;
  LIST *list_ptr;

                                                   /* update trace if active */
  sprintf(current_operation,"BEFORE CANCEL_TOKEN Token %3d",
          (int) token.attr[0]);
  trace_update();

                                 /* search event list for that token's entry */
  list_ptr = &event_list;
  current_node = list_ptr->front;
  previous_node = list_ptr->front;
  while ((current_node != NIL) && 
         (current_node->item.token.attr[0] != token.attr[0])) {
    previous_node = current_node;
    current_node = current_node->next;
  } /* end while */
              /* we are pointing at list node to be deleted - save node info */
  if (current_node == NIL)
    return(NOT_FOUND);
  else {
                                      /* delete this node and return token # */
    if (previous_node == current_node ) {
                                     /* token is the first on the event list */
      temp_ptr = (NODE *) list_ptr->front;
      list_ptr->front = current_node->next;
      cfree(temp_ptr);
    }
    else {
      temp_ptr = (NODE *) current_node;
      previous_node->next = current_node->next;
      cfree(temp_ptr);
    }
    list_ptr->size--;
                                                   /* update trace if active */
    sprintf(current_operation,"AFTER CANCEL_TOKEN Token %3d (Event %2d)",
            (int) token.attr[0],current_node->item.event);
    trace_update();

    return(current_node->item.event);
  }
} /* end cancel_event */




/************************************************************************/
/*                                                                      */
/* request:                                                             */
/*      Request the use of a given queue.                               */
/*                                                                      */
/************************************************************************/
int request(facility_id,token,priority)
int facility_id,priority;
TOKEN token;
{
 ITEM an_item;
 int i,server_num;

                                                   /* update trace if active */
  sprintf(current_operation,
	  "BEFORE REQUEST Facility %2d Token %3d Priority %2d",
          facility_id,(int) token.attr[0],priority);
  trace_update();

  if (facility[facility_id].busy_servers == 0)
      facility[facility_id].start_busy_time = sim_time();

  if (facility[facility_id].status == FREE) {
    facility[facility_id].busy_servers++;

    /* search for an open server */
    server_num = 1;
    while (facility[facility_id].server_info[server_num][0] != 0) 
          server_num++;
    facility[facility_id].server_info[server_num][0] = (int) token.attr[0];
    facility[facility_id].server_info[server_num][1] = priority;
    if (facility[facility_id].busy_servers ==
       facility[facility_id].total_servers)
         facility[facility_id].status = BUSY;
                                                   /* update trace if active */
    sprintf(current_operation,
	    "AFTER REQUEST Facility %2d Token %3d Priority %2d",
            facility_id,(int) token.attr[0],priority);
    trace_update();
    return(FREE);
  } else {                            /* facility is BUSY (all servers busy) */
    an_item.time = current_time; /* time that token entered fac. queue */
    for (i=0;i<MAX_NUM_ATTR;i++)
      an_item.token.attr[i] = token.attr[i];
    an_item.priority = priority;
    an_item.event = current_event;
    insert_list(&facility[facility_id].queue,&an_item,BEHIND_PRIORITY_KEY);
                                                   /* update trace if active */
    sprintf(current_operation,
	    "AFTER REQUEST Facility %2d Token %3d Priority %2d",
	    facility_id,(int) token.attr[0],priority);
    trace_update();
    return(BUSY);
  }
} /* end request() */



ITEM listrmqueue(n,list_ptr)
int n;
LIST *list_ptr;
{
  ITEM temp;
  NODE *current_node, *previous_node, *temp_ptr;
  current_node = list_ptr->front;
  previous_node = list_ptr->front;
  while ((current_node != NIL) &&
        ((int) current_node->item.token.attr[0] != n)) {
    previous_node = current_node;
    current_node = current_node->next;
  } /* end while */
  if(current_node == NIL) {
    printf("PREEMPT: Attempt to preempt a non-existent token\n");
    printf("Token # %d\n",n);
    exit();
  } else {
    temp = current_node->item;
    if (previous_node == current_node ) {
    /* token is the first on the event list */
      temp_ptr= (NODE *) list_ptr->front;
      list_ptr->front = current_node->next;
      cfree(temp_ptr);
    } else {
      temp_ptr = (NODE *) current_node;
      previous_node->next = current_node->next;
      cfree(temp_ptr);
    }
    list_ptr->size--;
    return temp;
  }
}




/************************************************************************/
/*                                                                      */
/* preempt:                                                             */
/*      Seize control of the given queue for the given token.           */
/*                                                                      */
/************************************************************************/
int preempt(facility_id,token,priority)
int facility_id,priority;
TOKEN token;
{
  ITEM an_item,heap_item;
  NODE *current_node,*previous_node,*temp_ptr;
  LIST *list_ptr;
  int server_num,do_preempt,i,preempted_token;
  int num_servers,minimum_priority,server_with_min;
  int preempted_token_priority;

                                                   /* update trace if active */
  sprintf(current_operation,
	  "BEFORE PREEMPT Facility %2d Token %3d Priority %2d",
          facility_id,(int) token.attr[0],priority);
  trace_update();

  if (facility[facility_id].busy_servers == 0)
     facility[facility_id].start_busy_time = sim_time();

  if (facility[facility_id].status == FREE) {
    facility[facility_id].busy_servers++;

    /* search for an open server */
    server_num = 1;
    while (facility[facility_id].server_info[server_num][0] != 0) 
          server_num++;
    facility[facility_id].server_info[server_num][0] = (int) token.attr[0];
    facility[facility_id].server_info[server_num][1] = priority;
    if (facility[facility_id].busy_servers ==
       facility[facility_id].total_servers)
         facility[facility_id].status = BUSY;
                                                   /* update trace if active */
    sprintf(current_operation,
	    "AFTER PREEMPT Facility %2d Token %3d Priority %2d",
            facility_id,(int) token.attr[0],priority);
    trace_update();
    return(FREE);
  } else {                            /* facility is BUSY (all servers busy) */
   /* Search each server for token priorities - find the smallest.  */
   /* If this token has higher priority than the minimum found then */
   /* preempt that token.                                           */

    minimum_priority = 9999;
    num_servers = facility[facility_id].total_servers;
                               /* locate server with smallest priority token */
    for (i=1;i<=num_servers;i++) 
       if (facility[facility_id].server_info[i][1] < minimum_priority) {
         minimum_priority = facility[facility_id].server_info[i][1];
         server_with_min = i;
       }
    if (priority > minimum_priority)
       do_preempt = TRUE;
    else
       do_preempt = FALSE;

    if (do_preempt == TRUE)   { 
                                 /* obtain token # that is occupying server */
      facility[facility_id].preemptions++;
      preempted_token = facility[facility_id].server_info[server_with_min][0];
                           /* save the priority of the token being preempted */
      preempted_token_priority = 
        facility[facility_id].server_info[server_with_min][1];
             /* replace server status to reflect preempting token & priority */
      facility[facility_id].server_info[server_with_min][0] = 
         (int) token.attr[0];
      facility[facility_id].server_info[server_with_min][1] = priority;

                                 /* search event list for that token's entry */

      switch (event_list_type) {

      case LINKED: an_item = listrmqueue(preempted_token,&event_list);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case HEAP:        heap_delete(preempted_token,&heap_item);
         an_item.event = heap_item.event;
         an_item.priority = preempted_token_priority;
                             /* calculate time remaining for preempted token */
         an_item.time = heap_item.time - sim_time();
                     /* make time negative to indicate that this is time     */
	             /* "remaining" and not time that token enters the queue */
         an_item.time = -an_item.time;
                  /* re-insert preempted token in facility queue - it should */
                  /* be placed ahead of other tokens with same priority      */
         an_item.token = heap_item.token;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case CALENDAR:        calendar_delete(preempted_token,&an_item);
         an_item.priority = preempted_token_priority;
                             /* calculate time remaining for preempted token */
         an_item.time -= sim_time();
                     /* make time negative to indicate that this is time     */
	             /* "remaining" and not time that token enters the queue */
         an_item.time = -an_item.time;
                  /* re-insert preempted token in facility queue - it should */
                  /* be placed ahead of other tokens with same priority      */
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case HENRIK: an_item = hrmqueue(preempted_token,&hqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         an_item.token.attr[0] = -an_item.token.attr[0];
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case INOMIAL: an_item = irmqueue(preempted_token,&iqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case LEFTIST: an_item = lrmqueue(preempted_token,&lqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case PAGODA:an_item = prmqueue(preempted_token,&pqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case PAIR:an_item = armqueue(preempted_token,&aqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case SKEWDN:an_item = krmqueue(preempted_token,&kqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case SKEWUP:an_item = srmqueue(preempted_token,&sqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case SPLAY:an_item = yrmqueue(preempted_token,&yqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      case TWOLIST:an_item = trmqueue(preempted_token,&tqq);
         an_item.priority = preempted_token_priority;
         an_item.time -= sim_time();
         an_item.time = -an_item.time;
         insert_list(&facility[facility_id].queue,&an_item,AHEAD_PRIORITY_KEY);
         break;
      }

                                                   /* update trace if active */
      sprintf(current_operation,
       "AFTER PREEMPT Facility %2d Token %3d Priority %2d",
        facility_id,(int) token.attr[0],priority);
      trace_update();
      return(FREE);
    } /* end if */
    else { /* if not preempt */
      an_item.time = current_time;     /* time that token entered fac. queue */
      for (i=0;i<MAX_NUM_ATTR;i++)
        an_item.token.attr[i] = token.attr[i];
      an_item.priority = priority;
      an_item.event = current_event;
      insert_list(&facility[facility_id].queue,&an_item,BEHIND_PRIORITY_KEY);
                                                   /* update trace if active */
      sprintf(current_operation,
	      "AFTER PREEMPT Facility %2d Token %3d Priority %2d",
	      facility_id,(int) token.attr[0],priority);
      trace_update();
      return(BUSY);
    } /* end else */
  } /* end if */
} /* end preempt() */




/************************************************************************/
/*                                                                      */
/* release:                                                             */
/*      Release server to waiting tokens (if any)                       */
/*                                                                      */
/************************************************************************/
release(facility_id,token)
 int facility_id;
 TOKEN token;
{
   ITEM an_item;
   int server_num,i,found;

   /* update trace if active */
   sprintf(current_operation,"BEFORE RELEASE Facility %2d Token %3d",
          facility_id,(int) token.attr[0]);
   trace_update();
   server_num = facility[facility_id].total_servers;
   found = FALSE;
   i = 1;
   while(!found && i<=server_num) {
      if(facility[facility_id].server_info[i][0] == (int) token.attr[0]) {
	 facility[facility_id].server_info[i][0] = 0;
	 facility[facility_id].server_info[i][1] = 0;
	 found = TRUE;
      } /* end if */
   i++;
   } /* end while */
   if(found) {
      facility[facility_id].status = FREE;
      facility[facility_id].busy_servers--;
      if(facility[facility_id].busy_servers == 0) {
         facility[facility_id].total_busy_time += sim_time() - 
         	    facility[facility_id].start_busy_time;
         facility[facility_id].start_busy_time = sim_time();
      } /* end if */
      if(facility[facility_id].queue.size > 0) {
      /* at least one entity was waiting on this facility/server */
      remove_front_list(&facility[facility_id].queue,&an_item);
      if (an_item.time < 0) {
      /* this token was preempted - put back on event list so it can finish */
        an_item.time = current_time - an_item.time;
    switch (event_list_type) {
    case LINKED: insert_list(&event_list,&an_item,TIME_KEY); break;
    case CALENDAR: calendar_insert(&an_item); break;
    case HEAP: heap_insert(an_item); break;
    case HENRIK: henqueue(an_item,&hqq); break;
    case INOMIAL: ienqueue(an_item,&iqq); break;
    case LEFTIST: lenqueue(an_item,&lqq); break;
    case PAGODA: penqueue(an_item,&pqq); break;
    case PAIR: aenqueue(an_item,&aqq); break;
    case SKEWDN: kenqueue(an_item,&kqq); break;
    case SKEWUP: senqueue(an_item,&sqq); break;
    case SPLAY: yenqueue(an_item,&yqq); break;
    case TWOLIST: tenqueue(an_item,&tqq); break;
    }

        facility[facility_id].status = BUSY;
        facility[facility_id].busy_servers++;

        /* search for an open server */
        server_num = 1;
        while (facility[facility_id].server_info[server_num][0] != 0) 
              server_num++;
        facility[facility_id].server_info[server_num][0] = 
                                                  (int) an_item.token.attr[0];
        facility[facility_id].server_info[server_num][1] = an_item.priority;
      } else {
                                             /* this token was not preempted */
        an_item.time = current_time;
	switch (event_list_type) {
	case LINKED: add_front_list(&event_list,&an_item); break;
	case CALENDAR: calendar_insert(&an_item); break;
	case HEAP: heap_insert(an_item); break;
	case HENRIK: henqueue(an_item,&hqq); break;
	case INOMIAL: ienqueue(an_item,&iqq); break;
	case LEFTIST: lenqueue(an_item,&lqq); break;
	case PAGODA: penqueue(an_item,&pqq); break;
	case PAIR: aenqueue(an_item,&aqq); break;
	case SKEWDN: kenqueue(an_item,&kqq); break;
	case SKEWUP: senqueue(an_item,&sqq); break;
	case SPLAY: yenqueue(an_item,&yqq); break;
	case TWOLIST: tenqueue(an_item,&tqq); break;
	}
      } /* end if */
    } /* end if */
  } /* end if (found) */

                                                   /* update trace if active */
  sprintf(current_operation,"AFTER RELEASE Facility %2d Token %3d",
          facility_id,(int) token.attr[0]);
  trace_update();

} /* end release() */




/************************************************************************/
/*                                                                      */
/* create_list:                                                         */
/*      Create a list structure.                                        */
/*                                                                      */
/************************************************************************/
create_list(list_ptr)
  LIST *list_ptr;
{
  list_ptr->front = NIL;
  list_ptr->size = 0;
} /* end create_list() */




/************************************************************************/
/*                                                                      */
/* empty_list:                                                          */
/*      Answers the question -- "is the list empty?"                    */
/*                                                                      */
/************************************************************************/
empty_list(list_ptr)
  LIST *list_ptr;
{
  return(list_ptr->size == 0);
} /* end empty_list() */




/************************************************************************/
/*                                                                      */
/* insert_list:                                                         */
/*      Insert an item inside the list according to a key.              */
/*                                                                      */
/************************************************************************/
insert_list(list_ptr,item_ptr,key)
  LIST *list_ptr;
  ITEM *item_ptr;
  int key;
{
  NODE *current_node,*previous_node;
  NODE *new_node;
 
  new_node = (NODE *) calloc(1,sizeof(NODE));
  new_node->item = *item_ptr;
  new_node->next = NIL;
  list_ptr->size += 1;
  /* printf("size = %d\n",facility[1].queue.size); */

  current_node = list_ptr->front;
  previous_node = list_ptr->front;
                                   /* insert in list according to sorted key */
  if (key == TIME_KEY) 
    while ((current_node != NIL) && 
           (current_node->item.time <= item_ptr->time)) {
      previous_node = current_node;
      current_node = current_node->next;
    } /* end while */
  else if (key == BEHIND_PRIORITY_KEY)
    while ((current_node != NIL) && 
           (current_node->item.priority >= item_ptr->priority)) {
      previous_node = current_node;
      current_node = current_node->next;
    } /* end while */
    else /* key == AHEAD_PRIORITY_KEY */
      while ((current_node != NIL) && 
             (current_node->item.priority > item_ptr->priority)) {
        previous_node = current_node;
        current_node = current_node->next;
      } /* end while */

  if (current_node == NIL) {
                                     /* add the inserted item to end of list */
    if (previous_node == NIL) /* list is empty */
      list_ptr->front = new_node;
    else
      previous_node->next = new_node;
  } else {
                                     /* insert item between 2 existing items */
    if (previous_node != current_node) {
                                                      /* list has >= 2 items */
      previous_node->next = new_node;
      new_node->next = current_node;
    } 
                                                     /* list has only 1 item */
    else {
      list_ptr->front = new_node;
      new_node->next = current_node;
    }
  }
} /* end insert_list() */




/************************************************************************/
/*                                                                      */
/* add_front_list:                                                      */
/*      Add item at front of list.                                      */
/*                                                                      */
/************************************************************************/
add_front_list(list_ptr,item_ptr)
  LIST *list_ptr;
  ITEM *item_ptr;
{
  NODE *new_node;
 
  new_node = (NODE *) calloc(1,sizeof(NODE));
  new_node->item = *item_ptr;
  new_node->next = NIL;
  if (list_ptr->size == 0) 
    list_ptr->front = new_node;
  else {
    new_node->next = list_ptr->front;
    list_ptr->front = new_node;
  }   
  list_ptr->size += 1;
                            /* printf("size = %d\n",facility[1].queue.size); */
} /* end add_front_list() */




/************************************************************************/
/*                                                                      */
/* remove_front_list:                                                   */
/*      Remove item from front of list.                                 */
/*                                                                      */
/************************************************************************/
remove_front_list(list_ptr,item_ptr)
  LIST *list_ptr;
  ITEM *item_ptr;
{
  NODE *temp_ptr;

  *item_ptr = list_ptr->front->item;
  temp_ptr = (NODE *) list_ptr->front;
  list_ptr->front = list_ptr->front->next;
                                                    /* deallocate node space */
  cfree(temp_ptr); 
  list_ptr->size -= 1;
} /* end remove_front_list() */


/* added by D. Hay */
listblankqueue(q)
NODE *q;
{
  if (q==NULL) return;
  listblankqueue(q->next);
  free(q);
}

/************************************************************************/
/*                                                                      */
/* trace_facility:                                                      */
/*      Output information about the given facility.                    */
/*                                                                      */
/************************************************************************/
trace_facility(facility_id)
int facility_id;
{
  NODE *node;
  LIST *list_ptr;
  int i;

  list_ptr = &facility[facility_id].queue;
  printf("Time: %3.1f\n",sim_time());
  printf("Queue %d: ",facility_id);
  node = list_ptr->front;
  while (node != NIL) {
    printf("(TM %3.1f,",node->item.time);
    printf("EV %1d,",node->item.event);
    printf("TK %1d) ",(int) node->item.token.attr[0]);
    node = node->next;
  }
  printf("\n");
  for(i=0;i<60;i++) printf("-");
  printf("\n");
} /* end trace_facility() */




/************************************************************************/
/*                                                                      */
/* trace_eventlist:                                                     */
/*      Output information about the eventlist.                         */
/*                                                                      */
/************************************************************************/
trace_eventlist()
{
  NODE *node;
  LIST *list_ptr;
  int i;

  list_ptr = &event_list;
  printf("Time: %3.1f\n",sim_time());
  printf("Events: ");
  node = list_ptr->front;
  while (node != NIL) {
    printf("(TM %3.1f,",node->item.time);
    printf("EV %1d,",node->item.event);
    printf("TK %1d) ",(int) node->item.token.attr[0]);
    node = node->next;
  }
  printf("\n");
  for(i=0;i<60;i++) printf("-");
  printf("\n");
} /* end trace_eventlist() */








/************************************************************************/
/*                                                                      */
/* trace_eventlist_size:                                                */
/*      Output the size of the event list.                              */
/*                                                                      */
/************************************************************************/
int trace_eventlist_size()
{
  return(event_list.size);
} /* end trace_eventlist_size() */




/************************************************************************/
/*                                                                      */
/* trace_visual:                                                        */
/*      Complete Graphical Trace of Queuing Simulation.                 */
/*                                                                      */
/************************************************************************/
trace_visual(type)
int type;
{
  trace_type = type;
  trace_flag = ON;
  strcpy(current_operation,"START SIMULATION");
  /* initialize screens */
#if UNIX
  if (trace_type == INTERACTIVE) initscr();
#endif
}




/************************************************************************/
/*                                                                      */
/* trace_update:                                                        */
/*      Output a detailed graphical trace.                              */
/*                                                                      */
/************************************************************************/
trace_update()
{
  LIST *list_ptr;
  NODE *node;
  int i,j;
  char any_char;

  if (trace_flag == ON && trace_type == INTERACTIVE) {
    /* Refresh screen */
#if UNIX
    clear();
    refresh();
    move(0,0);
#endif
#if TURBOC
    clrscr();
    gotoxy(0,0);
#endif
  }

  if (trace_flag == ON) {

  printf("## TIME: %5.1f\n",sim_time()); 
  printf("## %s\n",current_operation);
  printf("\n");

  if(event_list_type == LINKED) {

                                                         /* Trace Event List */
    printf("## EVENT LIST\n");

    list_ptr = &event_list;
    printf("      ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("+-----+");
      node = node->next;
    }
    printf("\n");

    printf("Token ");
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("|%5d|",(int) node->item.token.attr[0]);
      node = node->next;
    }
    printf("\n");

    printf("Time  ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("<=");
      printf("|%5.1f|",node->item.time);
      node = node->next;
    }
    printf("\n");

    printf("Event ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("|%5d|",node->item.event);
      node = node->next;
    } 
    printf("\n");

    printf("      ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("+-----+");
      node = node->next;
    }
    printf("\n");
  } else {
     if (event_list_type == CALENDAR) {                    /* trace calendar */
	printf("## CALENDAR QUEUE\n");
	print_calendar();
     } else {                                                  /* Trace HEAP */
	printf("## PRIORITY QUEUE\n");
	print_heap();
     }
  }
                                                /* Trace each facility queue */
  for(i=1;i<=facilities;i++) {

    printf("## FACILITY %2d: (%s). %2d Server(s), %2d Busy.\n",
	   i,facility[i].name,facility[i].total_servers,
	   facility[i].busy_servers);
    printf("Server(s): ");
    for(j=1;j<=facility[i].total_servers;j++)
       printf("(%2d) TK %3d PR %2d ",j,facility[i].server_info[j][0],
	      facility[i].server_info[j][1]);
    printf("\n");

    list_ptr = &facility[i].queue;
    printf("         ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("+-----+");
      node = node->next;
    }
    printf("\n");

    printf("Token    ");
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("|%5d|",(int) node->item.token.attr[0]);
      node = node->next;
    }
    printf("\n");
    
    printf("Time     ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("<=");
      printf("|%5.1f|",node->item.time);
      node = node->next;
    }
    printf("\n");

    printf("Event    ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("|%5d|",node->item.event);
      node = node->next;
    }
    printf("\n");

    printf("Priority ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("|%5d|",node->item.priority);
      node = node->next;
    }
    printf("\n");

    printf("         ");  
    node = list_ptr->front;
    while (node != NIL) {
      printf("  ");
      printf("+-----+");
      node = node->next;
    } 
    printf("\n");
  } /* end for */

  printf("\n");
  if (trace_type == INTERACTIVE) {
                       /* if INTERACTIVE mode, hold screen until key pressed */
    printf("-- press any key to continue ('X' to exit) --");
#if UNIX || TURBOC
    any_char = getch();
#else
    scanf("%c",any_char);
#endif
    if (any_char == 'x' || any_char == 'X') {
#if UNIX
      endwin();
#endif
      printf("\n");
      exit();
    }
  } /* end if */
} /* end if (trace_flag == ON) */
} /* end trace_update() */





typedef double real;

/* These random number generator routines were written by
   M.H. MacDougall, "Simulating Computer Systems", MIT Press, 1987.
*/

#if TURBOC
/*-------------  UNIFORM [0, 1] RANDOM NUMBER GENERATOR  -------------*/
/*                                                                    */
/* This implementation is for Intel 8086/8 and 80286/386 CPUs using   */
/* C compilers with 16-bit short integers and 32-bit long integers.   */
/*                                                                    */
/*--------------------------------------------------------------------*/
real ranf()
  {
    short *p,*q,k; long Hi,Lo;
    /* generate product using double precision simulation  (comments  */
    /* refer to In's lower 16 bits as "L", its upper 16 bits as "H")  */
    p=(short *)&In[strm]; Hi= *(p+1)*A;                 /* 16807*H->Hi */
    *(p+1)=0; Lo=In[strm]*A;                           /* 16807*L->Lo */
    p=(short *)&Lo; Hi+= *(p+1);    /* add high-order bits of Lo to Hi */
    q=(short *)&Hi;                       /* low-order bits of Hi->LO */
    *(p+1)= *q&0X7FFF;                               /* clear sign bit */
    k= *(q+1)<<1; if (*q&0X8000) then k++;         /* Hi bits 31-45->K */
    /* form Z + K [- M] (where Z=Lo): presubtract M to avoid overflow */
    Lo-=M; Lo+=k; if (Lo<0) then Lo+=M;
    In[strm]=Lo;
    return((real)Lo*4.656612875E-10);             /* Lo x 1/(2**31-1) */
  }
#endif

#if UNIX || UNIXX
/*-------------  UNIFORM [0, 1] RANDOM NUMBER GENERATOR  -------------*/
/*                                                                    */
/* This implementation is for Motorola 680x0 CPUs using C compilers   */
/* with 16-bit short integers and 32-bit long integers.               */
/*                                                                    */
/*--------------------------------------------------------------------*/
real ranf_old()
  {
    short *p,*q,k; long Hi,Lo;
    /* generate product using double precision simulation  (comments  */
    /* refer to In's lower 16 bits as "L", its upper 16 bits as "H")  */
    p=(short *)&In[strm]; Hi= *(p)*A;                   /* 16807*H->Hi */
    *(p)=0; Lo=In[strm]*A;                             /* 16807*L->Lo */
    p=(short *)&Lo; Hi+= *(p);      /* add high-order bits of Lo to Hi */
    q=(short *)&Hi;                       /* low-order bits of Hi->LO */
    *(p)= *(q+1)&0X7FFF;                             /* clear sign bit */
    k= *(q)<<1; if (*(q+1)&0X8000) then k++;       /* Hi bits 31-45->K */
    /* form Z + K [- M] (where Z=Lo): presubtract M to avoid overflow */
    Lo-=M; Lo+=k; if (Lo<0) then Lo+=M;
    In[strm]=Lo;
    return((real)Lo*4.656612875E-10);             /* Lo x 1/(2**31-1) */
  }

/*
 * New version of the RNG from simpack-2.22, more portable
 * than the original.
 *
 * hrp@cray.com, 94/05/26
 */

/*-------------  UNIFORM [0, 1] RANDOM NUMBER GENERATOR  -------------*/
/*                                                                    */
/* This implementation should be portable to machines with	      */
/* sizeof(int) >=4.					              */
/*                                                                    */
/*--------------------------------------------------------------------*/
real ranf()
  {
    unsigned int k; long Hi,Lo;
    /* generate product using double precision simulation  (comments  */
    /* refer to In's lower 16 bits as "L", its upper 16 bits as "H")  */
    Hi = ((In[strm] >> 16) & 0xffff) * A; /* 16807*H->Hi */
    Lo = (In[strm] & 0xffff) * A;	/* 16807*L->Lo */
    Hi += Lo >> 16;		/* add high-order bits of Lo to Hi */
    Lo &= 0xffff; Lo += (Hi & 0x7fff) << 16; /* low-order bits of Hi->Lo */
    k = Hi >> 15;
    /* form Z + K [- M] (where Z=Lo): presubtract M to avoid overflow */
    Lo-=M; Lo+=k; if (Lo<0) then Lo+=M;
    In[strm]=Lo;
    return((real)Lo*4.656612875E-10); /* Lo / (2**31-1) */
  }
#endif

/*--------------------  SELECT GENERATOR STREAM  ---------------------*/
stream(n)
  int n;
    { /* set stream for 1<=n<=15, return stream for n=0 */
      /* if ((n<0)||(n>15)) then error(0,"stream Argument Error"); */
      if (n) then strm=n;
      return(strm);
    }

/*--------------------------  SET/GET SEED  --------------------------*/
long seed(Ik,n)
  long Ik; int n;
    { /* set seed of stream n for Ik>0, return current seed for Ik=0  */
      /* if ((n<1)||(n>15)) then error(0,"seed Argument Error"); */
      if (Ik>0L) then  In[n]=Ik;
      return(In[n]);
    }

/*------------  UNIFORM [a, b] RANDOM VARIATE GENERATOR  -------------*/
real uniform(a,b)
  real a,b;
    { /* 'uniform' returns a psuedo-random variate from a uniform     */
      /* distribution with lower bound a and upper bound b.           */
      /* if (a>b) then error(0,"uniform Argument Error: a > b"); */
      return(a+(b-a)*ranf());
    }

/*--------------------  RANDOM INTEGER GENERATOR  --------------------*/
random(i,n)
  int i,n;
    { /* 'random' returns an integer equiprobably selected from the   */
      /* set of integers i, i+1, i+2, . . , n.                        */
      /* if (i>n) then error(0,"random Argument Error: i > n"); */
      n-=i; n=(n+1.0)*ranf();
      return(i+n);
    }

/*--------------  EXPONENTIAL RANDOM VARIATE GENERATOR  --------------*/
real expntl(x)
  real x;
    { /* 'expntl' returns a psuedo-random variate from a negative     */
      /* exponential distribution with mean x.                        */
      return(-x*log(ranf()));
    }

/*----------------  ERLANG RANDOM VARIATE GENERATOR  -----------------*/
real erlang(x,s)
  real x,s;
    { /* 'erlang' returns a psuedo-random variate from an erlang      */
      /* distribution with mean x and standard deviation s.           */
      int i,k; real z;
      /* if (s>x) then error(0,"erlang Argument Error: s > x"); */
      z=x/s; k=(int)z*z;
      z=1.0; for (i=0; i<k; i++) z *= ranf();
      return(-(x/k)*log(z));
    }

/*-----------  HYPEREXPONENTIAL RANDOM VARIATE GENERATION  -----------*/
real hyperx(x,s)
  real x,s;
    { /* 'hyperx' returns a psuedo-random variate from Morse's two-   */
      /* stage hyperexponential distribution with mean x and standard */
      /* deviation s, s>x.  */
      real cv,z,p;
      /* if (s<=x) then error(0,"hyperx Argument Error: s not > x"); */
      cv=s/x; z=cv*cv; p=0.5*(1.0-sqrt((z-1.0)/(z+1.0)));
      z=(ranf()>p)? (x/(1.0-p)):(x/p);
      return(-0.5*z*log(ranf()));
    }

/*-----------  TRIANGULAR RANDOM VARIATE GENERATION  -----------*/
real triang(a,c,b)
real a,c,b;
{
 /* triangular distribution with left and right being [a,b] and the
    mode being at point c */
  real sample,point;
  point = (c-a)/(b-a);
  sample = uniform(0.0,1.0);
  if (sample <= point)
    return(sqrt(sample*(b-a)*(c-a)) + a);
  else 
    return(b - sqrt((1.0-sample)*(b-a)*(b-c)));
}

/*-----------------  NORMAL RANDOM VARIATE GENERATOR  ----------------*/
real normal(x,s)
  real x,s;
    { /* 'normal' returns a psuedo-random variate from a normal dis-  */
      /* tribution with mean x and standard deviation s.              */
      real v1,v2,w,z1; static real z2=0.0;
      if (z2!=0.0)
        then {z1=z2; z2=0.0;}  /* use value from previous call */
        else
          {
            do
              {v1=2.0*ranf()-1.0; v2=2.0*ranf()-1.0; w=v1*v1+v2*v2;}
            while (w>=1.0);
            w=sqrt((-2.0*log(w))/w); z1=v1*w; z2=v2*w;
          }
      return(x+z1*s);
  }




/************************************************************************/
/*                                                                      */
/* report_stats:                                                        */
/*      Output all relavent simulation statistics.                      */
/*                                                                      */
/************************************************************************/
report_stats()
{
  int i;

  printf("\n");
  printf("+---------------------------+\n");
  printf("| SimPack SIMULATION REPORT |\n");
  printf("+---------------------------+\n");
  printf("\n");

  if (completions == 0) completions = 1;
  total_sim_time = sim_time();
  total_busy_time = 0.0;
  for(i=1;i<=facilities;i++) {
        /* update busy time if simulation ends when there is a busy facility */
    if(facility[i].busy_servers > 0) 
      facility[i].total_busy_time += sim_time() - 
      facility[i].start_busy_time;
    total_busy_time += busy_time(i);
  }
  total_busy_time /= facilities;
  total_utilization = total_busy_time/total_sim_time;
  arrival_rate = (float) arrivals/total_sim_time;
  throughput = (float) completions/total_sim_time;
  mean_service_time = total_busy_time/completions;
  mean_num_tokens = total_token_time/total_sim_time;
  mean_residence_time = mean_num_tokens/throughput;

  printf("Total Simulation Time: %f\n",total_sim_time);
  printf("Total System Arrivals: %d\n",arrivals);
  printf("Total System Completions: %d\n",completions);
  printf("\n");
  printf("System Wide Statistics\n");
  printf("----------------------\n");
  printf("System Utilization: %4.1f%%\n",100.0*total_utilization);
  printf("Arrival Rate: %f, Throughput: %f\n",arrival_rate,throughput);
  printf("Mean Service Time per Token: %f\n",mean_service_time);
  printf("Mean # of Tokens in System: %f\n",mean_num_tokens);
  printf("Mean Residence Time for each Token: %f\n",mean_residence_time);
  printf("\n");

  printf("Facility Statistics\n");
  printf("-------------------\n");
  for (i=1;i<=facilities;i++) {
    utilization = 100.0 * busy_time(i)/sim_time();
    idle = 100.0 * (sim_time() - busy_time(i))/sim_time();
    printf("F %d (%s): Idle: %4.1f%%, Util: %4.1f%%, Preemptions: %d\n",
	   i,facility[i].name,idle,utilization,facility[i].preemptions); 
  }
}




/************************************************************************/
/*                                                                      */
/* heap_insert:                                                         */
/*      Put the given item in the heap structure.                       */
/*                                                                      */
/************************************************************************/
heap_insert(item)
ITEM item;
{
  int parent,child;

  heap_count++;
  heap[heap_count] = item;
  if(heap_count > 1) {
    child = heap_count;
    parent = child/2;
    while ((heap[parent].time > heap[child].time) && (child > 1)) {
      heap_swap(&heap[parent],&heap[child]);
      child = parent;
      if (child > 1)
        parent = child/2;
    } /* end while */
  } /* end if */
} /* end heap_insert */




/************************************************************************/
/*                                                                      */
/* heap_remove:                                                         */
/*      Return the next item at the top of the heap.                    */
/*                                                                      */
/************************************************************************/
heap_remove(item_addr)
ITEM *item_addr;
{
  int parent,child;
  *item_addr = heap[1];
  heap_swap(&heap[1],&heap[heap_count]);
  heap_count--;
  heap_down_adjust(1);

} /* heap_remove */


/************************************************************************/
/*                                                                      */
/* heap_up_adjust:                                                      */
/*      Adjust the heap going up from the given location.               */
/*                                                                      */
/************************************************************************/
heap_up_adjust(child)
 int child;
{
int parent = child/2; 
 
while (parent>0) {
    if (heap[parent].time < heap[child].time) break; 
    heap_swap(&heap[parent],&heap[child]);
    child = parent; parent /= 2; 
  } 
}
/************************************************************************/
/*                                                                      */
/* heap_down_adjust:                                                    */
/*      Adjust the heap going down from the given location.             */
/*                                                                      */
/************************************************************************/
heap_down_adjust(parent)
 int parent;
{
int child;
  /* this loop copied from old heap_delete routine */
  while (1) {
    if (2*parent > heap_count)
      goto exit;
    else
      child = 2*parent;
    if (child+1 <= heap_count) 
      if (heap[child+1].time < heap[child].time)
        child++;
    if (heap[parent].time < heap[child].time) goto exit;
    heap_swap(&heap[parent],&heap[child]);
    parent = child;
  } /* end while */  
 exit: ;
} 

/************************************************************************/
/*                                                                      */
/* heap_delete:                                                         */
/*      Remove a specific item from the heap.                           */
/*                                                                      */
/************************************************************************/
heap_delete(token_id,item)
int token_id;
ITEM *item;
{
  int i,j,parent,child;

  /* find the item in the heap first */
  i = 1;
  while (heap[i].token.attr[0] != token_id) i++;
  /* save all info. in the heap item to be deleted */
  heap_swap(&heap[i],&heap[heap_count]);
  *item = heap[heap_count];
  heap_count--;

  /* reorganize heap */
  heap_up_adjust(i);
  heap_down_adjust(i);

} /* heap_delete */




/************************************************************************/
/*                                                                      */
/* heap_swap:                                                           */
/*      Switch the positions of two items in the heap.                  */
/*                                                                      */
/************************************************************************/
heap_swap(item1,item2)
ITEM *item1,*item2;
{
  ITEM temp;

  temp = *item1;
  *item1 = *item2;
  *item2 = temp;
}




/************************************************************************/
/*                                                                      */
/* print_heap:                                                          */
/*      Output the contents of the heap.                                */
/*                                                                      */
/************************************************************************/
print_heap()
{
          int i;
          for(i=1;i<=heap_count;i++)
	         printf("%.2f ",heap[i].time);
          printf("\n");
}




/*************************************************************************/
/**                                                                      */
/** Calendar Queueing Method for Future Event List Manipulation:         */
/**     As presented in the article by Randy Brown in Communications of  */
/** the ACM, Oct. 1988 Vol. 30 Num. 10.  Coded by Eric Callman 3/4/92    */
/**                                                                      */
/*************************************************************************/
/*                                                                       */
/* calendar_insert:                                                      */
/*     This routine adds one entry to the future event queue if the      */
/* calendar queueing method was chosen in init_simpack().  The priority  */
/* (or time) of the event is given in the ITEM structure.                */
/*                                                                       */
/*************************************************************************/

calendar_insert(ent)
ITEM *ent;
{
   int i;
   calptr temp, traverse;
   void item_copy();
if (ent == NULL) printf("No entry!\n");
                 /* calculate the number of the bucket to place new entry in */
   i = (int)(ent->time / (float)calendar_width);      /* find virtual bucket */
   i = i % nbuckets;                                   /* find actual bucket */

   temp = (struct calist *) malloc(sizeof(*temp)); /* initialize a list node */

   temp->entry.time = ent->time;             /* insert the given information */
   temp->entry.event = ent->event;
   temp->entry.token = ent->token;
   temp->entry.priority = ent->priority;
   traverse = calendar[i];     /* grab head of list of events in that bucket */
                                       /* put in head of list if appropriate */
   if ((traverse == NULL) || (traverse->entry.time > ent->time)) {

      temp->next = traverse;
      calendar[i] = temp;
   } else {
      while ((traverse->next != NULL) &&    /* find the correct spot in list */
	     (traverse->next->entry.time < ent->time))
         traverse = traverse->next;
      temp->next = traverse->next;                 /* put in the new element */
      traverse->next = temp;
   }
/* printf("inserting: %.1f(%d) in bucket %d\n",calendar[i]->entry.time,calendar[i]->entry.event,i); */

   calqsize++;                               /* update the size of the queue */
   if ((calqsize > caltop_threshold) && (nbuckets < MAXNBUCKETS))
      calendar_resize(2 * nbuckets);      /* double the size of the calendar */
}




/*************************************************************************/
/*                                                                       */
/* calendar_remove:                                                      */
/*     This function removes the next item from the calendar queue, and  */
/* returnes that item in the given parameter.                            */
/*                                                                       */
/*************************************************************************/

calendar_remove(ent)
ITEM *ent;
{
   register int i;
   int flag, temp2;
   calptr temp;
   float lowest;

   i = lastbucket;                                  /* search for next entry */
   flag = 0;
   while (flag == 0){
if (ent == NULL) printf("No return entry!\n");
      if ((calendar[i] != NULL) && (calendar[i]->entry.time < buckettop)){
	 ent->time = calendar[i]->entry.time;        /* put in return values */
	 ent->event = calendar[i]->entry.event;
	 ent->token = calendar[i]->entry.token;
	 ent->priority = calendar[i]->entry.priority;
/* printf("extracting: %.1f(%d)\n",ent->time,ent->event); */
	 temp = calendar[i];                        /* remove item from list */
	 calendar[i] = calendar[i]->next;
	 free(temp);    /* return the memory from the list node to the stack */

	 lastbucket = i;   /* update position in calendar and set found flag */
	 lastprio = ent->time;
	 flag = 1;

	 calqsize--;                         /* update the size of the queue */
	 if (calqsize < calbot_threshold)    /* cut the size of the queue in */
	    calendar_resize((int)((float)nbuckets / 2));   /* half if needed */

      } else {

	 i++; if (i == nbuckets) i = 0;              /* go on to next bucket */
	 buckettop += calendar_width;
	 if (i == lastbucket) flag = 2;   /* go to a direct search if needed */
      }
   }
   if (flag == 2){     /* directly search for the event with the lowest time */
      temp2 = -1;
      for (i = 0; i < nbuckets; i++)
	 if ((calendar[i] != NULL) && ((temp2 == -1) ||
		(calendar[i]->entry.time < lowest))){
	    temp2 = i;                       /* mark the lowest entry so far */
	    lowest = calendar[i]->entry.time;
	 }

      ent->time = calendar[temp2]->entry.time;       /* put in return values */
      ent->event = calendar[temp2]->entry.event;
      ent->token = calendar[temp2]->entry.token;
      ent->priority = calendar[temp2]->entry.priority;
/* printf("extracting: %.1f(%d)\n",ent->time,ent->event); */
      temp = calendar[temp2];                       /* remove item from list */
      calendar[temp2] = calendar[temp2]->next;
      free(temp);       /* return the memory from the list node to the stack */

      lastbucket = temp2;                     /* update position in calendar */
      lastprio = ent->time;                         /* recalculate buckettop */
      buckettop = (float)((int)(lastprio / calendar_width) + 1) *
	           calendar_width + (0.5 * calendar_width);

      calqsize--;                            /* update the size of the queue */
      if (calqsize < calbot_threshold)       /* cut the size of the queue in */
	 calendar_resize((int)((float)nbuckets / 2));      /* half if needed */
   }
}




/*************************************************************************/
/*                                                                       */
/* calendar_delete:                                                      */
/*     This function removes the specified item from the calendar queue, */
/* and returnes that item in the given parameter.                        */
/*                                                                       */
/*************************************************************************/
calendar_delete(id,ent)
int id;
ITEM *ent;
{
   register int i;
   int flag;
   calptr temp, temp2;
   float lowest;

if (ent == NULL) printf("No return entry!\n");
   i = flag = 0;                                 /* search for correct entry */
   while (flag == 0){
      temp = calendar[i];
      if (temp != NULL) {
	 if (temp->entry.token.attr[0] == id) flag = 2;
	 while ((temp->next != NULL) && (flag == 0)){
	    if (temp->next->entry.token.attr[0] == id) flag = 1;
	    else temp = temp->next;
	 }
      }
      i++;                                   /* searched entire list already */
      if ((i == nbuckets) && (flag == 0)) flag = -1;
   }
   if (flag == -1) printf("Entry not found!\n");
   else {
      i--;
      if (flag == 2) {                     /* it was at the head of the list */
	 ent->time = temp->entry.time;               /* put in return values */
	 ent->event = temp->entry.event;
	 ent->token = temp->entry.token;
	 ent->priority = temp->entry.priority;
	 temp = calendar[i];                        /* remove item from list */
	 calendar[i] = calendar[i]->next;
	 free(temp);    /* return the memory from the list node to the stack */
      } else {
	 ent->time = temp->next->entry.time;         /* put in return values */
	 ent->event = temp->next->entry.event;
	 ent->token = temp->next->entry.token;
	 ent->priority = temp->next->entry.priority;
	 temp2 = temp->next;                    /* remove item from the list */
	 temp->next = temp->next->next;
	 free(temp2);   /* return the memory from the list node to the stack */
      }
      calqsize--;                            /* update the size of the queue */
      if (calqsize < calbot_threshold)       /* cut the size of the queue in */
	 calendar_resize((int)((float)nbuckets / 2));      /* half if needed */
   }
}




/*************************************************************************/
/*                                                                       */
/* calendar_localinit:                                                   */
/*     This routine initializes a bucket array within the array calq[].  */
/* Calendar[0] is made equal to calq[qbase], the number of buckets is    */
/* nbuck, and startprio is the priority at which dequeing begins.  All   */
/* external variables except calresize_enable are initialized.           */
/*                                                                       */
/*************************************************************************/

calendar_localinit(qbase, nbuck, bwidth, startprio)
int qbase, nbuck;
double bwidth, startprio;
{
   int i;
   long n;

   calfirstsub = qbase;                /* set position and size of new queue */
   calendar = calq+qbase;                      /* initialize the new queue */
   calendar_width = bwidth;
   nbuckets = nbuck;

   calqsize = 0;                                      /* initialize as empty */
   for (i = 0; i < nbuckets; i++) calendar[i] = NULL;
   lastprio = startprio;                          /* set up initial position */
   n = (long)((float)startprio / calendar_width);          /* virtual bucket */
   lastbucket = n % nbuckets;
   buckettop = (float)(n + 1) * calendar_width + (0.5 * calendar_width);
                                      /* set up queue size change thresholds */
   calbot_threshold = (int)((float)nbuckets / 2) - 2;
   caltop_threshold = 2 * nbuckets;
}




/*************************************************************************/
/*                                                                       */
/* calendar_init:                                                        */
/*     This routine uses calendar_localinit() to start the calendar with */
/* nothing in it for initializing.                                       */
/*                                                                       */
/*************************************************************************/
calendar_init()                           /* this initializes an empty queue */
{
   calendar_localinit(0, 2, 1.0, 0.0);
   calresize_enable = TRUE;
}




/*************************************************************************/
/*                                                                       */
/* calendar_resize:                                                      */
/*     This routine copies the queue into a calendar with the number of  */
/* buckets specified in the parameter newsize.  The new queue is in the  */
/* opposit end of calq from the original.                                */
/*                                                                       */
/*************************************************************************/

calendar_resize(newsize)
int newsize;
{
   double bwidth;
   int i, oldnbuckets;
   calptr *oldcalendar, temp;
   double new_cal_width();

   if (!calresize_enable) return;

   bwidth = new_cal_width();                        /* find new bucket width */
   oldcalendar = calendar;         /* save location and size of old calendar */
   oldnbuckets = nbuckets;         /* for use when copying calendar          */

   if (calfirstsub == 0)                          /* initialize new calendar */
      calendar_localinit(CALQSPACE-newsize, newsize, bwidth, lastprio);
   else
      calendar_localinit(0, newsize, bwidth, lastprio);

   for (i = oldnbuckets-1; i >= 0; i--){    /* copy elements to new calendar */
      temp = oldcalendar[i];
      while (temp != NULL){              /* traverse linked list of elements */
	 calendar_insert(&(temp->entry)); /* use insert routine for transfer */
	 temp = temp->next;
      }
   }
}




/*************************************************************************/
/*                                                                       */
/* new_cal_width:                                                        */
/*     This function returns the width that the buckets should have      */
/* based on a random sample of the queue so that there will be about 3   */
/* items in each bucket.                                                 */
/*                                                                       */
/*************************************************************************/

double new_cal_width()       /* this calculates the width to use for buckets */
{
   int nsamples, templastbucket, i, j;
   float templastprio;
   double tempbuckettop, average, newaverage;
   ITEM temp[25];

   if (calqsize < 2) return(1.0);    /* decide # of queue elements to sample */
   if (calqsize <= 5) nsamples = calqsize;
   else nsamples = 5 + (int)((float)calqsize / 10);
   if (nsamples > 25) nsamples = 25;

   templastbucket = lastbucket;                /* save the present situation */
   templastprio = lastprio;
   tempbuckettop = buckettop;

   calresize_enable = FALSE;
   average = 0.0;
   for (i = 0; i < nsamples; i++){    /* dequeue events to get a test sample */
      calendar_remove(&temp[i]);      /* and sum up the differences in time  */
      if (i > 0) average += temp[i].time - temp[i-1].time;
   }
   average = average / (float)(nsamples - 1);             /* get the average */
   newaverage = 0.0; j = 0;
   calendar_insert(&temp[0]);
   for (i = 1; i < nsamples; i++){ /* recalculate ignoring large seperations */
      if ((temp[i].time - temp[i-1].time) < (average * 2.0)){
	 newaverage += (temp[i].time - temp[i-1].time);
	 j++;
      }
      calendar_insert(&temp[i]);       /* put the sample back into the queue */
   }
   
   newaverage = (newaverage / (float)j) * 3.0;      /* this is the new width */

   lastbucket = templastbucket;           /* restore the original conditions */
   lastprio = templastprio;
   buckettop = tempbuckettop;
   calresize_enable = TRUE;

   return(newaverage);
}




/*************************************************************************/
/*                                                                       */
/* print_calendar:                                                       */
/*     This routine outputes the priorities of the elements in the       */
/* calendar queue.  It's used for tracing.                               */
/*                                                                       */
/*************************************************************************/
print_calendar()
{
   register int i;
   calptr temp;

   for (i = 0; i < nbuckets; i++){        /* print priorities in each bucket */
      temp = calendar[i];
      if (i == lastbucket) printf("%d>",i);
      else printf("%d ",i);
      while (temp != NULL){                 /* traverse linked list of items */
	 printf("%.2f(%d) ",temp->entry.time,temp->entry.event);
	 temp = temp->next;
      }
      printf("\n");
   }
}

/* added by D. Hay */
clearcalqueue()
{
  int i;
  calptr temp,temp2;
  for (i = 0; i < nbuckets; i++) {
    temp2 = calendar[i];
    while (temp2!=NULL) {
      temp = temp2;
      temp2 = temp2->next;
      free(temp);
    }
  }
}

