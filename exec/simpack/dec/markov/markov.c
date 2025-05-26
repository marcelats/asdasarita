/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include "../../func/queuing/queuing.h"
#define MAX_STATES 100
#define MAX_LINKS MAX_STATES*MAX_STATES
#define MAX_STRING_LEN 20

float adj[MAX_STATES][MAX_STATES];
char state[MAX_STATES][MAX_STRING_LEN];
int current_state,next_state,tr_index,row,col;
int count,num_states,state_freq[MAX_STATES],link_freq[MAX_LINKS],total;
float current_time,end_time,branch_prob[MAX_STATES],state_time[MAX_STATES];
float total_state_time[MAX_STATES];
double prob;

main()
{
  int i,j;

  init();
  current_time = 0.0;
  current_state = 0;
  for (i=0;i<num_states;i++) {
    state_freq[i] = 0;
    total_state_time[i] = 0.0;
   }
  for (i=0;i<MAX_LINKS;i++) link_freq[i] = 0;
  printf("Markov Simulator Output\n\n");
  while (current_time < end_time) {
   /* printf("Time: %f, ",current_time);
   printf("State: %s\n",state[current_state]); */
   /* gather statistics */
   state_freq[current_state] += 1;

   /* initialize arrays */
   branch_prob[0] = adj[current_state][0];
   branch_prob[num_states-1] = 1.0;   
   for (i=1;i<num_states-1;i++)
     branch_prob[i] = branch_prob[i-1] + adj[current_state][i];
   /* decide which state to branch to */
   prob = uniform(0.0,1.0);
   count = 0;
   while (branch_prob[count] < (float) prob)
     count++;
   next_state = count;
   current_time += state_time[current_state];
   total_state_time[current_state] += state_time[current_state];
   tr_index = current_state*num_states+next_state;
   link_freq[tr_index] += 1;
   current_state = next_state;
  } /* end while */
  printf("Markov Model Statistics\n\n");
  printf("State Statistics\n");
  printf("----------------\n");
  total = 0;
  for (i=0;i<num_states;i++)
      total += state_freq[i];
  printf("State   ");printf("Name                ");
  printf("  Freq  ");
  printf("Freq %%   ");
  printf("  Time  ");
  printf(" Time %%\n");
  for (i=0;i<num_states;i++) {
     printf("%-3d     ",i);
     printf("%-20s",state[i]);
     printf("%6d  ",state_freq[i]);
     printf("%5.1f%%   ",(float) state_freq[i] * 100.0/ (float) total);
     printf("%6.1f  ",total_state_time[i]);
     printf(" %5.1f%%\n",(float) total_state_time[i]* 100.0/
                         (float) current_time);
  } /* end for */
  printf("\n\n");
  printf("Link Statistics\n");
  printf("----------------\n");
  total = 0;
  for (i=0;i<MAX_LINKS;i++)
    total += link_freq[i];
  printf("Link     ");printf("Id      ");
  printf("  Freq  ");
  printf("Freq %%\n");
  for (i=0;i<MAX_LINKS;i++) {
    if(link_freq[i] > 0) {
      printf("%-3d     ",i);
      row = i/num_states;
      col = i%num_states;
      printf("%2d -> %2d ",row,col);  printf("%6d  ",link_freq[i]);
      printf("%5.1f%%\n",(float) link_freq[i] * 100.0/ (float) total);
    } /* end if */
  } /* end for */
} /* end main() */

init()
{
  int i,j;
  float t;
  
  /* read in number of states and end time */
  scanf("%d %f",&num_states,&end_time);
  /* read in the length of time for each state */
  for (i=0;i<num_states;i++)
   scanf("%f",&state_time[i]);
  /* read in connection matrix */
  for (i=0;i<num_states;i++) 
    for (j=0;j<num_states;j++) 
      scanf("%f",&adj[i][j]);
  /* read in state descriptors */
  for (i=0;i<num_states;i++) 
      scanf("%s",state[i]);
  /* Calculate totals and divide matrix */
  /* to create an adjacency matrix */
  for (i=0;i<num_states;i++) 
  {
     t = 0.0;
     for (j=0;j<num_states;j++)
	   t += adj[i][j];
     for (j=0;j<num_states;j++)
	   adj[i][j] /= t;
  }
} /* end init() */

