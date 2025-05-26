
/* Gas Molecule Simulator using Time Slicing */

#include "../../func/queuing/queuing.h"

#define MAX_BALLS 1000
#define NUM_BALLS 4
#define DELTA_TIME 0.001
#define MAX_TIME 1.0
main()
  { 
    float time,x[MAX_BALLS],y[MAX_BALLS],vx[MAX_BALLS],vy[MAX_BALLS];
    int i;

    /* Provide all balls with an initial
       x,y position and velocity in the x,y direction
    */
    time = 0.0;
    x[0] = 0.4; y[0] = 0.4; vx[0] = -20.0; vy[0] = -10.0;
    x[1] = 0.4; y[1] = 0.6; vx[1] = -10.0; vy[1] = 30.0;
    x[2] = 0.6; y[2] = 0.6; vx[2] = 10.0; vy[2] = 20.0;
    x[3] = 0.6; y[3] = 0.4; vx[3] = 20.0; vy[3] = -30.0;

   while (time < MAX_TIME) { 
   /* Update new positions of all balls */
      for (i=0;i<NUM_BALLS;i++) {
        printf("%2d %f %f\n",i,x[i],y[i]);
        x[i] += DELTA_TIME*vx[i];
        if ((x[i] <= 0.0) || (x[i] >= 1.0)) vx[i] = -vx[i];
        if (x[i] < 0.0) x[i] = 0.0; if (x[i] > 1.0) x[i] = 1.0;
        y[i] += DELTA_TIME*vy[i];
        if ((y[i] <= 0.0) || (y[i] >= 1.0)) vy[i] = -vy[i];
        if (y[i] < 0.0) y[i] = 0.0; if (y[i] > 1.0) y[i] = 1.0;
      } /* end for */
   time += DELTA_TIME;
  } /* end while */
} /* end main() */



