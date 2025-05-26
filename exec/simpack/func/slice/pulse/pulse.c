/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_STRING_LEN 20

float adj[MAX_VERTICES][MAX_VERTICES],value[MAX_VERTICES];
float temp[MAX_VERTICES],pulse[MAX_VERTICES];
char vertex[MAX_VERTICES][MAX_STRING_LEN];
int end_time,num_vertices;

main()
{
  int i,j,time;

  init();
  printf("Pulse Process Results\n");
  printf("------------------------\n\n");
  for (time=0;time<end_time;time++) {
   /* output transient behavior */
   printf("%d: ",time);
   printf(" P ");
   for (j=0;j<num_vertices;j++)
    printf("%.2f ",pulse[j]);
   printf("V ");
   for (j=0;j<num_vertices;j++)
    printf("%.2f ",value[j]);
   printf("\n");
   /* for each vertex, determine new state value */
   for (j=0;j<num_vertices;j++) {
    temp[j] = 0.0;
    for (i=0;i<num_vertices;i++)
      temp[j] += adj[i][j]*pulse[i];
    value[j] += temp[j];
   } /* end for */
   for (j=0;j<num_vertices;j++)
    pulse[j] = temp[j];
 }
} /* end main */

init()
{
  int i,j;
  /* read in number of vertices, end time */
  scanf("%d %d",&num_vertices,&end_time);
  /* read in adjacency matrix */
  for (i=0;i<num_vertices;i++) 
    for (j=0;j<num_vertices;j++)
      scanf("%f",&adj[i][j]);
  /* read in vertex descriptors */
  for (i=0;i<num_vertices;i++) 
      scanf("%s",vertex[i]);
  /* read in values for each vertex */
  for (i=0;i<num_vertices;i++)
    scanf("%f",&value[i]);
  /* read in pulse for each vertex */
  for (i=0;i<num_vertices;i++)
    scanf("%f",&pulse[i]);
} /* end init() */
