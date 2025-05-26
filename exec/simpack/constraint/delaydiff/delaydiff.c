/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1991, Paul A. Fishwick
---------------------------------------------*/
 
/*
This program simulates the Mackey-Glass delay differential equation.
A circular buffer is used to store the delayed state variable values.
One hundred state values are stored per time unit.

Use: %delaydiff > points.dat
Use a plotting program, such as gnuplot to see the points.

*/

#include<math.h>
#define TRUE 1
#define FALSE 0
#define MAX 2000
#define BUFFER_SIZE (MAX+1)
#define PI   3.14159265 

double time,delta_time,in[2],out[2];
double f[2],savevar[2],buffer[BUFFER_SIZE];
double theta,m,lambda,g;
int num_equations,ptr,intervals_per_step,T;

main()
{ 
  init_conditions();
  while (time < 600.0) {
   /* output time,x */
   printf("%f %f\n",time,out[1]); 
   /* output a phase plot 
   printf("%f %f\n",out[1],buffer[t(-20)]); */
   state();
   integrate(); 
   ptr = (ptr + 1) % BUFFER_SIZE;
   buffer[ptr] = out[1];
   time += delta_time;
  } /* end while */
} /* end main */

init_conditions()
{
  int i;
  ptr = MAX;

  delta_time = 0.01;
  intervals_per_step = (int) 1.0/delta_time;

  /* initialize the buffer */
  for (i=0;i<=MAX;i++)  buffer[i] = 0.1;
  out[1] = buffer[MAX];
  theta = 1.0;
  lambda = 0.2;
  m = 10.0;
  g = 0.1;
  time = 0.0;
  num_equations = 1;
}

state()
{  double constant;

   constant = PI/4.0;
   in[1] = (lambda*pow(theta,10.0)*buffer[t(-20)])/
           (pow(theta,10.0) + pow(buffer[t(-20)],10.0)) - g*buffer[t(0)]; 
}

integrate()
{
  int i;

  for (i=1;i<=num_equations;i++) {
    f[i] = delta_time*in[i];
    savevar[i] = out[i];
    out[i] += f[i]/2;
  }
  time += delta_time/2;
  state();

  for (i=1;i<=num_equations;i++) {
    f[i] += 2*delta_time*in[i];
    out[i] = savevar[i] + delta_time*in[i]/2;
  }
  state();

  for (i=1;i<=num_equations;i++) {
    f[i] += 2*delta_time*in[i];
    out[i] = savevar[i] + delta_time*in[i];
  }
  time += delta_time/2;
  state();

  for (i=1;i<=num_equations;i++) 
    out[i] = savevar[i] + (f[i] + delta_time*in[i])/6;
}


int t(index)
int index;
{int new_pointer;
 new_pointer = ptr + index*intervals_per_step;
 if (new_pointer >= 0)
   return(new_pointer);
 else
   return(new_pointer + BUFFER_SIZE);
}

