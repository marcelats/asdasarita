/* SET MAXIMUMS HERE!! ------------------------------ */
#define MAX_TOKENS 20000 /* max. number of tokens going through the system */
#define MAX_SERVERS 1000 /* max. number of servers for a facility */
#define MAX_FACILITIES 1000 /* max. number of facilities */
#define MAX_NUM_ATTR 5 /* max. number of attributes for an entity */
#define HEAP_SIZE 50000 /* max. heap size */
#define CALQSPACE 49153     /* calendar array size needed for maximum resize */
#define MAXNBUCKETS 32768     /* maximum number of buckets in calendar queue */
/* SET MAXIMUMS HERE!! ------------------------------ */

#define TRUE 1
#define FALSE 0
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

typedef struct {
  float attr[MAX_NUM_ATTR];
} TOKEN;

typedef struct {
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

struct calist {          /* node type for a linked list of pointers to items */
  ITEM *entry;              /* these are used in the calender queue routines */
  struct calist *next;
};
struct calist *calq[CALQSPACE];            /* array of linked lists of items */
struct calist *calender;            /* pointer to use as a sub-array to calq */

#include "mytypes.h"

int nbuckets, calqsize, lastbucket, calresize_enable;   /* global variables- */
float caltop_threshold, calbot_threshold, lastprio;     /* for the calender- */
double buckettop, calender_width;                       /* queueing routines */


extern float current_time,sim_time(),busy_time(),last_event_time;
extern float total_token_time;
extern int current_event,facilities,status(),arrivals,completions;
extern int tokens_in_system,trace_flag,trace_type,heap_count;
extern int event_list_type,remove_duplicates;
extern char current_operation[100];
extern LIST event_list;
extern ITEM heap[HEAP_SIZE],an_item,item1;
extern FACILITY facility[MAX_FACILITIES];


/* Performance variables

extern float utilization,idle,arrival_rate,throughput,total_sim_time;
extern float total_busy_time;
extern float total_utilization;
extern float mean_service_time,mean_num_tokens,mean_residence_time;

/* Declarations for random distribution sampling */

extern double ranf(), uniform(), expntl(), erlang(), hyperx(), normal();
extern double triang();
extern long seed();


