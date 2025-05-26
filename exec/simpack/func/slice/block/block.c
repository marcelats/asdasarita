#include <math.h>

#define NUM_BLOCKS 100
#define NUM_TYPES 8
#define MAX_INPUTS 5
#define MAX_PARAMS 5
#define ADD 0
#define CONST 1
#define DIV 2
#define INT 3
#define MULT 4
#define SUBTRACT 5
#define USER 6
#define GEN 7

int num_blocks,out_block;
int in[NUM_BLOCKS][MAX_INPUTS],out[NUM_BLOCKS],block[NUM_BLOCKS];
float time,delta_time,param[NUM_BLOCKS][MAX_PARAMS],end_time;
float value[NUM_BLOCKS];
char type[20];
char types[NUM_TYPES][20] = {"add","const","div","int","mult","sub",
                             "user","gen"};
int param_num[NUM_TYPES] = {0,1,0,1,0,0,3,2};
int input_num[NUM_TYPES] = {2,0,2,1,2,2,1,0};

main()
{
  int i;

  init_conditions();
  for (i=0;i<num_blocks;i++) 
    if (block[i] == INT) 
      value[i] = param[i][0];
    else
      value[i] = 0.0;
  while (time < end_time) { 
   update_blocks();
   /* output time,x */
   printf("%f %f\n",time,value[out_block]);
  }  /* end while */
} /* end main */

init_conditions()
{
  int i,j,block_num,block_type;


  scanf("%d %d %f",&num_blocks,&out_block,&end_time);
  for (i=0;i<num_blocks;i++) {
   scanf("%d %s",&block_num,type);
   /* determine numeric type */
   for (j=0;j<NUM_TYPES;j++)
     if (strcmp(type,types[j]) == 0)
        block[i] = j;
   for (j=0;j<input_num[block[i]];j++)
     scanf("%d",&in[i][j]);
   for (j=0;j<param_num[block[i]];j++)
     scanf("%f",&param[i][j]);
  } /* end for */
  time = 0.0;
  delta_time = 0.01;
}

update_blocks()
{ 
  int i;

  /* determine function type and apply inputs */
  for (i=0;i<num_blocks;i++) {
    switch (block[i]) {
     
    case ADD: value[i] = value[in[i][0]] + value[in[i][1]]; break;
    case CONST: value[i] = param[i][0]; break;
    case DIV: value[i] = value[in[i][0]] / value[in[i][1]]; break;
    case INT: integrate(i); break;
    case MULT: value[i] = value[in[i][0]] * value[in[i][1]]; break;
    case SUBTRACT: value[i] = value[in[i][0]] - value[in[i][1]]; break;
    case USER: value[i] = value[in[i][0]] - param[i][2];
               if (value[i] < param[i][0])
                  value[i] = param[i][0];
               else {if (value[i] > param[i][1])
                  value[i] = param[i][1];}
               break;
    case GEN: value[i] = param[i][0] + time*param[i][1]; break;
    } /* end switch */
  } /* end for */
 time += delta_time;
} /* end update_blocks() */
 
integrate(i)
int i;
{
 value[i] += value[in[i][0]]*delta_time;
}
