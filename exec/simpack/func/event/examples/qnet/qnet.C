#include <math.h>
#include "queuing.h"
#include <stdio.h>

#define NUM_BLOCKS 100
#define NUM_TYPES 6
#define MAX_INPUTS 5
#define MAX_OUTPUTS 5
/* Blocks */
#define GEN 0
#define REQUEST 1
#define RELEASE 2
#define FORK 3
#define JOIN 4
#define SINK 5

typedef struct {
 char string[5][30];
 float param[10];
} BLOCK;

BLOCK block[NUM_BLOCKS];
int num_blocks,event,inputs[NUM_BLOCKS],outputs[NUM_BLOCKS];
int in[NUM_BLOCKS][MAX_INPUTS],out[NUM_BLOCKS][MAX_OUTPUTS];
int block_type[NUM_BLOCKS],queue_id[NUM_BLOCKS];
float end_time,branch_prob[MAX_OUTPUTS];
char type_string[20];
char types[NUM_TYPES][20] = {"gen","request","release","fork","join","sink"};
TOKEN block_token;

// fn prototype declarations:
void read_network (void);
void process_block (int event, TOKEN block_token);

main()
{
  int i,j;

  init_simpack(HEAP | REMOVE_DUPLICATES);
  read_network();
  cout << "Back from read_network\n";

  for (i=0;i<num_blocks;i++) {
  cout << "for loop, i=" << i << '\n';
  /* for all GEN nodes, start scheduling */
  if (block_type[i] == GEN) {
     block_token.attr[0] = (float) i;
     schedule(GEN,0.0,block_token);
  } /* end if */
  /* create a facility for each queue node */
  if (block_type[i] == REQUEST)
     {
     int number_of_servers = (int) block[i].param[0];
     char * name_of_facility = block[i].string[0];
     int fac_id = create_facility (name_of_facility, number_of_servers);
     queue_id[i] = fac_id;

     cout << "\ncreating facility\n"
          << "i=" << i << " name of facility='" << name_of_facility << "'"
          << " number_of_servers=" << number_of_servers
          << " fac_id=" << fac_id << "\n\n";
     }

  cout << "end for loop, i=" << i << '\n';
  } /* end for */
  cout << "for loop has ended, about to enter while loop\n";
  while (sim_time() < end_time) {
   next_event(&event,&block_token);
   if (event < GEN || event > SINK)
     {
     cout << "bad event_id = " << event << '\n';
     exit(99);
     }
   cout << "event_id=" << event << ", about to call process_block()\n";
   process_block(event,block_token);
  }  /* end while */
  report_stats();
return 0; // pacify compiler
} /* end main */

void read_network()
  {
  int i,j,k,block_num,num_inputs,num_outputs;

  scanf("%d %f",&num_blocks,&end_time);
  for (i=0;i<num_blocks;i++) {
   scanf("%d %s",&block_num,type_string);
   /* determine numeric type */
   for (j=0;j<NUM_TYPES;j++) {
     if (strcmp(type_string,types[j]) == 0)
        block_type[i] = j;
   } /* end for */
   switch(block_type[i]) {
    case GEN: scanf("%f",&block[i].param[0]); break;
    case REQUEST: scanf("%s %f %s %f %f", block[i].string[0],
           &block[i].param[0],block[i].string[1], &block[i].param[1],
           &block[i].param[2]); break;
    case RELEASE: break;
    case FORK: scanf("%f",&block[i].param[0]);
               for (k=0;k<(int)block[i].param[0];k++)
                  scanf("%f",&block[i].param[k+1]);
               break;
    case JOIN: break;
    case SINK: break;
   } /* end switch */
   } /* end for */
   for (i=0; i<num_blocks;i++) {
    scanf("%d", &block_num);
   scanf("%d",&num_inputs);
   inputs[i] = num_inputs;
   for (j=0;j<num_inputs;j++)
     scanf("%d",&in[i][j]);
   scanf("%d",&num_outputs);
   outputs[i] = num_outputs;
   for (j=0;j<num_outputs;j++)
     scanf("%d",&out[i][j]);
  } /* end for */
} /* end read_network() */

void process_block (int event, TOKEN block_token)
  {
  int i,j,count,branch;
  double sample;

  i = (int) block_token.attr[0];
  switch (event) {

   case GEN: update_arrivals();
             block_token.attr[0] = (float) i;
             schedule(GEN,block[i].param[0],block_token);
             for(j=0;j<outputs[i];j++) {
                block_token.attr[0] = (float) out[i][j];
                schedule(block_type[out[i][j]],0.0,block_token);
             } /* end for */
             break;
   case REQUEST:
                   cout << "case is REQUEST. token id=" << i
                        << " facility_id = " << queue_id[i] << '\n';



                   if (request(queue_id[i],block_token,0) == FREE) {
                   if (strcmp(block[i].string[1],"expon") == 0)
                       sample = expntl(block[i].param[1]);
                   else if (strcmp(block[i].string[1],"normal")==0)
                       sample = normal(block[i].param[1],block[i].param[2]);
                   else if (strcmp(block[i].string[1],"uniform")==0)
                       sample = uniform(block[i].param[1],block[i].param[2]);

                   block_token.attr[0] = (float) i;
                   schedule(RELEASE,sample,block_token);
                 } /* end if */
                 break;
   case RELEASE:

                   cout << "case is RELEASE. token id=" << i
                        << " facility_id = " << queue_id[i] << '\n';


                 release(queue_id[i],block_token);
                 for(j=0;j<outputs[i];j++) {
                     block_token.attr[0] = (float) out[i][j];
                     schedule(block_type[out[i][j]],0.0,block_token);
                 } /* end for */
                 break;
   case FORK: /* create a cumulative distribution based on fork probs */
              branch_prob[0] = block[i].param[1];
              for(j=1;j<(int)block[i].param[0];j++)
               branch_prob[j] = branch_prob[j-1] + block[i].param[j+1];

              /* sample from the cum. distribution */
              sample = uniform(0.0,1.0);
              count = 0;
              while (branch_prob[count] < sample) count++;
              branch = count;
              block_token.attr[0] = (float) out[i][branch];
              schedule(block_type[out[i][branch]],0.0,block_token);
              break;
   case JOIN: for(j=0;j<outputs[i];j++) {
                block_token.attr[0] = (float) out[i][j];
                schedule(block_type[out[i][j]],0.0,block_token);
              } /* end for */
              break;
   case SINK: update_completions(); break;
  } /* end switch */
} /* end process_block */




