/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include <math.h>
/* Forced Vibration */

float in[4],out[4],f[4],savevar[4],time,delta_time;
int num_equations=3;

main()
{
  init_conditions();
  while (time < 60) {
   state();
   integrate(); 
   printf("%f %f\n",time,out[1]);
 }
} /* end main */

init_conditions()
{
  out[1] = 1.0;
  out[2] = 1.0;
  out[3] = 1.0;
  time = 0.0;
  delta_time = 0.05;
}

state()
{ /* parameters are chosen for demonstrating the formation
     of "wave packets". */
  float a=3.7,c=0.0,f=10.0,k=16.0,m=1.0; 
 /* Calculate state:
    x1' = x2
    x2' = -c/m(x2)  - k/m(x1) + f/m(cos(ax3))
    x3' = 1.0
 */
 in[1] = out[2];
 in[2] = -c*out[2]/m - k*out[1]/m + f*cos(a*out[3])/m;
 in[3] = 1.0;
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


