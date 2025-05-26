/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include <math.h>

float in[4],out[4],f[4],savevar[4],time,delta_time;
float k1,k2,k3,k4;
int num_equations;

main()
{
  init_conditions();
  while (time < 400.0) {
   state();
   integrate(); 
   printf("%f %f\n",out[1],out[2]);
  } /* end while */
} /* end main */

init_conditions()
{
  num_equations = 2;
  out[1] = 100.0;
  out[2] = 100.0;

  k1 = 0.1; k2 = 0.001; k3 = 0.001; k4 = 0.3;
  time = 0.0;
  delta_time = 0.1;
}

state()
{ 
/* Calculate state */
  in[1] = k1*out[1] - k2*out[1]*out[2];
  in[2] = k3*out[1]*out[2] - k4*out[2];
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
