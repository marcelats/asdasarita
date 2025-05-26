/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

/* 
   Timed PETRI NET Simulator

   This program simulates any timed Petri net represented in the
   data structure given in array 't' (standing for 't'ransition).

*/

#include <stdio.h>
#include "../../func/queuing/queuing.h"

#define BUSY 1
#define FREE 0
#define BEGINFIRE 1
#define ENDFIRE 2
#define FALSE 0
#define TRUE 1

#define MAX_TRANS 100
#define MAX_PLACES 200
#define MAX_BRANCH 20

/* transitions are facilities */
int transition[MAX_TRANS],tr_status[MAX_TRANS]; 
int t_in[MAX_TRANS][MAX_BRANCH],t_out[MAX_TRANS][MAX_BRANCH];
int out_set[MAX_TRANS][MAX_BRANCH],out_set_count[MAX_TRANS];
int p[MAX_PLACES],iteration_count;
int places,transitions,firings,array[500],number,events;
extern int facilities;
float trans_time[MAX_TRANS];
TOKEN a_token;


/* Format of the input file is as follows:
   #transitions #places #firings
   "#places for input to transition 0" place-0 place-1 ...
     "#places for output from transition 0" place-0 place-1 ...
   "#places for input to transition 1" place-0 place-1 ...
     "#places for output from transition 1" place-0 place-1 ...
   ...........
   "#places for input to transition (#transitions-1)" place-0 place-1 ...
     "#places for output from transition (#transitions-1)" place-0 place-1 ...
   tokens-in-place-0 tokens-in-place-1 ... tokens-in-place (#places-1)
*/


main()
/*
 Driver Program - Check each transition for some given number of
iterations (or until a given absolute simulation time has been
reached).
*/
{
  int i,i2,event,transition_number;
  char string[5],newstring[10];
  FILE *points;
  
  init_simpack(HEAP); 
  events = 0;
  /* read in network data */
  read_net();
  /* create a transition out set table */
  for (i=0;i<transitions;i++) out_set_count[i] = 0;
  create_out_set();
  printf("Petri net contains %3d transitions and %3d places.\n",
         transitions,places);
  printf("Simulate for %d firings.\n",firings); printf("\n");

  /* Print Table Header */
  printf("TIME   "); printf("TRS ");
  for (i=0;i<places;i++)
      printf("%2d ",i);
  printf("\n");
  for(i=0;i<(11+places*3);i++) printf("-");
  printf("\n");

    /* print out initial place array */
    printf("%6.2f ",sim_time());
    printf("XX: ",transition_number);
    for (i=0;i<places;i++)
      printf("%2d ",p[i]);
    printf("\n");

  /* Simulate this run for a designated number of transition firings */
  for(i=0;i<transitions;i++) {
    a_token.attr[0] = (float) i;
    schedule(BEGINFIRE,0.0,a_token);
    events++;
  }
  iteration_count = firings;
  /* continue to check all net transitions until a total of
     'firings' transitions have been fired - check transitions
     in a random fashion to insure fairness.
  */
  while (iteration_count != 0 && events > 0) {
   /* take one event from the event list and cause it to occur */
   next_event(&event,&a_token);
   transition_number = (int) a_token.attr[0];
   events--;
   check_transition(event,transition_number);
  } /* end while */
  /* Print Table Trailer */
  for(i=0;i<(11+places*3);i++) printf("-");
  printf("\n");
  /* exit(); */
} /* end main() */

check_transition(event,transition_number)

/*
 Check a transition for firing. If the transition is not already busy
 then fire it as long as at least one token exists in each input
 place for that transition.
*/

int event,transition_number;
{
  int input_places,output_places,i,fire,tokens,out_set_number;
 

  switch(event) {

  case BEGINFIRE: /* check transition for firing */

  input_places = t_in[transition_number][0];
  fire = TRUE;
  for(i=0;i<input_places;i++) {
    tokens = p[t_in[transition_number][i+1]];
    fire = fire && (tokens > 0);
  }
  if ((tr_status[transition_number] == FREE) && fire) {
    /* delete one token from each input place */
    for (i=0;i<input_places;i++) p[t_in[transition_number][i+1]] -= 1;

    tr_status[transition_number] = BUSY;
    a_token.attr[0] = (float) transition_number;
    schedule(ENDFIRE,trans_time[transition_number],a_token);
    events++;
  } /* end if */
  break;

    case ENDFIRE: /* end of transition fire */
  
    tr_status[transition_number] = FREE;
    /* add one token to each output place */
    input_places = t_in[transition_number][0];
    output_places = t_out[transition_number][0];
    for (i=0;i<output_places;i++) 
         p[t_out[transition_number][i+1]] += 1;

    /* firing just occurred, print out the 'p'lace array */
    printf("%6.2f ",sim_time());
    printf("%2d: ",transition_number);
    for (i=0;i<places;i++)
      printf("%2d ",p[i]);
    printf("\n");

   /* sweep through outset transitions once to schedule new events */
   out_set_number = out_set_count[transition_number];
   for (i=0;i<out_set_number;i++) array[i] = out_set[transition_number][i];
   random_array(out_set_number-1,array);
   
   for(number=0;number<out_set_count[transition_number];number++) {   
      a_token.attr[0] = (float) array[number];
      schedule(BEGINFIRE,0.0,a_token);
      events++;
    }
    iteration_count--;
    break;

} /* end switch */
} /* end check_transition */


random_array(max,array)

/* take the integers between 0 and max and return
a randomly sorted array 'newarray' containing
these integers */

int max,array[];
{
  int element,i,swap;
  /* rearrange array to yield a random ordering */
  for(i=0;i<max;i++) {
    element = random(0,max-i);
    swap = array[element];
    array[element] = array[max-i];
    array[max-i] = swap;
  }
}


read_net()
{
/* Read in the Network Information from Standard Input (stdin)  */
  int i,j,number_inputs,number_outputs;

  /* Read #transitions, #places, #firings */
  scanf("%d %d %d",&transitions,&places,&firings);
  /* Read transition information:
  time-delay #inputs i1 i2 i3 ... #outputs o1 o2 o3 ... */
  for(i=0;i<transitions;i++) {
     scanf("%f %d",&trans_time[i],&t_in[i][0]);
     number_inputs = t_in[i][0];
     for(j=0;j<number_inputs;j++) scanf("%d",&t_in[i][j+1]);
     scanf("%d",&t_out[i][0]);
     number_outputs = t_out[i][0];
     for(j=0;j<number_outputs;j++) scanf("%d",&t_out[i][j+1]);
   }
   /* Read place information */
   for(i=0;i<places;i++) scanf("%d",&p[i]);
} /* end read_net() */


create_out_set()
/* Create the transition out set for each transition in the net */
{
  int tr,tr1,tr2,op,in,found;

  for (tr1=0;tr1<transitions;tr1++) 
    for (op=1;op<=t_out[tr1][0];op++)
      for (tr2=0;tr2<transitions;tr2++)
        for (in=1;in<=t_in[tr2][0];in++) 
          if (t_in[tr2][in] == t_out[tr1][op]) {
          /* check to see if the transition is already stored */
            found = FALSE;
            for (tr=0;tr<out_set_count[tr1];tr++)
                if (out_set[tr1][tr] == tr2) found = TRUE;
            if (!found) {
                out_set[tr1][out_set_count[tr1]] = tr2;
                out_set_count[tr1]++;
            } /* end if */
	   }
} /* end out_set() */

