/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#define MAX_STATES 50
#define MAX_LINKS MAX_STATES*MAX_STATES
#define MAX_STRING_LEN 20
#define NUM_INPUTS 2
#define MAX_INPUTS 20

struct {
 int state;
 float time;
} transition[MAX_STATES][MAX_INPUTS];
char state[MAX_STATES][MAX_STRING_LEN];
int control[MAX_STATES],state_freq[MAX_STATES],link_freq[MAX_LINKS];
int index,current_state,num_states,control_length,total,i;
int row,col,save_state,tr_index;
float current_time,state_time[MAX_STATES],total_state_time[MAX_STATES];

main()
{
  init();
  current_time = 0.0;
  current_state = 0;
  for (i=0;i<num_states;i++) {
   state_freq[i] = 0;
   total_state_time[i] = 0.0;
  }
  for (i=0;i<MAX_LINKS;i++) link_freq[i] = 0;
  index = 0;
  printf("FSA Simulator Output\n\n");
  while (index <= control_length) {
   printf("Time: %f, ",current_time);
   printf("State: %s\n",state[current_state]); 
   /* gather statistics */
   state_freq[current_state] += 1;
   current_time += state_time[current_state];
   total_state_time[current_state] += state_time[current_state];
   if(index != control_length) {
     current_time += transition[current_state][control[index]].time;
     save_state = current_state;
     current_state = transition[current_state][control[index]].state;
     tr_index = save_state*num_states+current_state;
     link_freq[tr_index] += 1;
   }
   index++;
  }; /* end while */
  printf("\n\nFSA Model Statistics\n\n");
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
  for (i=0;i<MAX_LINKS;i++) total += link_freq[i];
  printf("Link     ");printf("Id      ");
  printf("  Freq  ");
  printf("Freq %%\n");
  for (i=0;i<MAX_LINKS;i++) {
  if(link_freq[i] > 0) {
   printf("%-3d     ",i);
   row = i/num_states;
   col = i%num_states;
   printf("%2d -> %2d ",row,col);
   printf("%6d  ",link_freq[i]);
   printf("%5.1f%%\n",(float) link_freq[i] * 100.0/ (float) total);
  } /* end if */
  } /* end for */
} /* end main() */

init()
{
  int i,j;
  /* read in number of states */
  scanf("%d",&num_states);
  /* read in the length of time for each state */
  for (i=0;i<num_states;i++)
    scanf("%f",&state_time[i]);
  /* read in transition array */
  for (i=0;i<num_states;i++) 
    for (j=0;j<NUM_INPUTS;j++)
      scanf("%d",&transition[i][j].state);
 
  /* read in state descriptors */
  for (i=0;i<num_states;i++) 
      scanf("%s",state[i]);
  /* read in control string length */
  scanf("%d",&control_length);
  /* read in control (input) string */
  for (i=0;i<control_length;i++) 
      scanf("%1d",&control[i]);
} /* end init() */
