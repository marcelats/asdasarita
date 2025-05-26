#include <math.h>
#include "queuing.h"
#include <stdio.h>

#define NUM_BLOCKS 100
#define NUM_TYPES 6
#define MAX_INPUTS 5
#define MAX_OUTPUTS 5
#define MAX_PARAMS 5
/* Blocks */
#define GEN 0
#define AND 1
#define NAND 2
#define OR 3
#define NOR 4
#define INV 5

float f[4],savevar[4],last_time,delta_time,delay[NUM_BLOCKS];
int num_blocks,out_block,block_num,event;
int in[NUM_BLOCKS][MAX_INPUTS],out[NUM_BLOCKS][MAX_OUTPUTS];
int block_type[NUM_BLOCKS];
float param[NUM_BLOCKS][MAX_PARAMS],end_time;
float value[NUM_BLOCKS];
char type_string[20];
char types[NUM_TYPES][20] = {"gen","and","nand","or","nor","inv"};
int param_num[NUM_TYPES] = {0,0,0,0,0,0};
int input_num[NUM_TYPES] = {0,2,2,2,2,1};
int output_num[NUM_BLOCKS];
TOKEN block_token;

// fn prototype declarations:
void read_network(void);
void update_block (int event, TOKEN block_token);

main()
{
  int i;

  init_simpack(HEAP | REMOVE_DUPLICATES);
  read_network();
  for (i=0;i<num_blocks;i++) {
    value[i] = 0.0;
    /* for all GEN nodes, start scheduling */
    if (block_type[i] == GEN) {
      block_token.attr[0] = (float) i;
      schedule(GEN,0.0,block_token);
    } /* end if */
  } /* end for */
  last_time = 0.0;
  while (sim_time() < end_time) {
   next_event(&event,&block_token);
   if (sim_time() != last_time) {
     printf("%-3f ",last_time);
     for(i=0;i<num_blocks;i++) printf("%1d ",(int) value[i]);
     printf("\n");
     last_time = sim_time();
   } /* end if */
   update_block(event,block_token);
   /* output time,x */
  }  /* end while */
return 0;
} /* end main */

void read_network()
{
  int i,j,block_num;

  scanf("%d %d %f",&num_blocks,&out_block,&end_time);
  for (i=0;i<num_blocks;i++) {
   scanf("%d %s",&block_num,type_string);
   /* determine numeric type */
   for (j=0;j<NUM_TYPES;j++) {
     if (strcmp(type_string,types[j]) == 0)
        block_type[i] = j;
   }
   scanf("%f",&delay[i]);
   for (j=0;j<input_num[block_type[i]];j++)
     scanf("%d",&in[i][j]);
   scanf("%d",&output_num[i]);
   for (j=0;j<output_num[i];j++)
     scanf("%d",&out[i][j]);
   for (j=0;j<param_num[block_type[i]];j++)
     scanf("%f",&param[i][j]);
  } /* end for */
}

void update_block (int event, TOKEN block_token)
  {
  int j;

  block_num = (int) block_token.attr[0];
 /* determine function type and apply inputs */
  switch (event) {

   case GEN: value[block_num] = (int) (value[block_num]+1) % 2;
             schedule(GEN,delay[block_num],block_token);
             break;
   case AND: value[block_num] = (int) block_token.attr[1] &&
                                 (int) block_token.attr[2];
             break;
   case NAND:value[block_num] = (((int) block_token.attr[1] &&
                                  (int) block_token.attr[2]) + 1) % 2;
             break;
   case OR:  value[block_num] = (int) block_token.attr[1] ||
                                (int) block_token.attr[2];
             break;
   case NOR: value[block_num] = (((int) block_token.attr[1] ||
                                  (int) block_token.attr[2]) + 1) % 2;
             break;
   case INV: value[block_num] = (int)(block_token.attr[1]+1) % 2;
             break;
  } /* end switch */
  /* update all blocks in the out set of this block */
  for(j=0;j<output_num[block_num];j++) {
    block_token.attr[0] = (float) out[block_num][j];
    /* save inputs for this block */
    block_token.attr[1] = value[in[out[block_num][j]][0]];
    block_token.attr[2] = value[in[out[block_num][j]][1]];
    schedule(block_type[out[block_num][j]],
             delay[out[block_num][j]],block_token);
  } /* end for */
} /* end update_block */




