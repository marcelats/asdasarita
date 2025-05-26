/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1991, Paul A. Fishwick
---------------------------------------------*/

#include "queuing.h"
#include <stdio.h>

#define MAX_TIME 1000.0
#define SECONDS 0
#define MINUTES 1
#define HOURS 2

int seconds=0,minutes=0,hours=0;

void print_time (void); // fn prototype declaration

main() {
 int event,i;
 TOKEN tick;

 init_simpack(HEAP);
 schedule(SECONDS,0.0,tick);
 schedule(MINUTES,60.0,tick);
 schedule(HOURS,3600.0,tick);
 while (sim_time()< MAX_TIME) {
   next_event(&event,&tick);
    switch(event) {
     case SECONDS: print_time(); seconds = (seconds+1) % 60;
                   schedule(SECONDS,1.0,tick); break;

     case MINUTES: minutes = (minutes+1) % 60;
                   schedule(MINUTES,60.0,tick); break;

     case HOURS:   hours = (hours+1) % 12;
                   schedule(HOURS,3600.0,tick); break;

    } /* end switch */
 } /* end while */
return 0;
} /* end main() */

void print_time()
{
  printf("Time: %2d:%2d:%2d\n",hours,minutes,seconds);
} /* end print_time() */


