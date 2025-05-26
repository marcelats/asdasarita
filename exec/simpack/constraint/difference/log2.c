/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include <math.h>

int time,delta_time;
float a,out[3],in[3];

main()
{
  init_conditions();
  while (time <= 100) {
   state();
   update(); 
   /* output time,x */
   printf("%d %f\n",time,in[2]);
  } /* end while */
} /* end main */

init_conditions()
{
  out[1] = 0.8;
  out[2] = 0.8;
  time = 0;
  delta_time = 1;
  a = 1.5;
}

state()
{ 
/* Calculate state: x(t) = a*x(t-1)(1.0 - x(t-2)) */
in[1] = out[2];
in[2] = a*out[2]*(1.0 - out[1]);
}
 
update()
{
 int i;
 for(i=1;i<=2;i++)
   out[i] = in[i];
 time += delta_time;
}

