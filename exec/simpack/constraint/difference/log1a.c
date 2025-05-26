/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include <math.h>

int time,delta_time;
float a,in[2],out[2];

main()
{
  init_conditions();
  while (time <= 100) {
   state();
   /* output time,x */
   printf("%d %f\n",time,in[1]);
   update(); 
  } /* end while */
} /* end main */

init_conditions()
{
  out[1] = 0.8;
  time = 0;
  delta_time = 1;
  a = 1.2;
}

state()
{ 
/* Calculate state: x(t) = a*x(t-1)(1.0 - x(t-1)) */
in[1] = a*out[1]*(1.0 - out[1]);
}
 
update()
{
 int i;
 out[1] = in[1];
 time += delta_time;
}

