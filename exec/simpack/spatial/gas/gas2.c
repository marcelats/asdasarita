
/* Gas Molecule Simulator using Discrete Events */

#include "../../func/queuing/queuing.h"

#define MAX_BALLS 1000
#define NUM_BALLS 4
#define MAX_EVENTS 50

#define BALL_ATTR 0

#define NUM_WALLS 4
#define LEFT 0
#define RIGHT 1
#define BOTTOM 2
#define TOP 3

#define MOVE 1

float x[MAX_BALLS],y[MAX_BALLS],vx[MAX_BALLS],vy[MAX_BALLS];
float t[MAX_BALLS],time_to_impact,last_time,collision_time();
int wall_to_impact;

main()
  { 
    TOKEN ball;
    int ball_num,event,events,i,j,a_wall;
    float test;

    init_simpack(HEAP);

    /* Give 4 balls an initial position and velocity vector */ 
    x[0] = 0.4; y[0] = 0.4; vx[0] = -2.0; vy[0] = -1.0;
    x[1] = 0.4; y[1] = 0.6; vx[1] = -1.0; vy[1] = 3.0;
    x[2] = 0.6; y[2] = 0.6; vx[2] = 1.0; vy[2] = 2.0;
    x[3] = 0.6; y[3] = 0.4; vx[3] = 2.0; vy[3] = -3.0; 

    for (ball_num=0;ball_num < NUM_BALLS;ball_num++) {
     time_to_impact = collision_time(ball_num);
     ball.attr[BALL_ATTR] = (float) ball_num; 
     schedule(MOVE,time_to_impact,ball);
    } /* end for */

    last_time = -1.0; 
    events = 0;
    while (events < MAX_EVENTS)
      { 
        next_event(&event,&ball); 
        events++;
        switch(event) {
	  case MOVE:
              ball_num = (int) ball.attr[BALL_ATTR];
              time_to_impact = collision_time(ball_num);
              test = sim_time() - last_time;
              if (test > 0.001) {
                last_time = sim_time(); 
                update_positions(time_to_impact);
                for (i=0;i<NUM_BALLS;i++) 
                  printf("%2d %f %f\n",i,x[i],y[i]); 
                time_to_impact = collision_time(ball_num);
              } /* end if */
              ball.attr[BALL_ATTR] = (float) ball_num;
              schedule(MOVE,time_to_impact,ball);
              break;
        } /* end switch */
     } /* end while */
} /* end main() */


/* Find the time of the next collision for a ball */
float collision_time(ball_num)
int ball_num;
{
  int j;
  float t[MAX_BALLS],shortest_time;

  /* First, determine time to hit each wall */
  if (vx[ball_num] == 0.0) {
     t[LEFT] = 5000.0; 
     t[RIGHT] = 5000.0;
   }
  else {
     t[LEFT] = -x[ball_num]/vx[ball_num];
     t[RIGHT] = (1.0 - x[ball_num])/vx[ball_num];
  } /* end if */

  if (vy[ball_num] == 0.0) {
     t[BOTTOM] = 5000.0; 
     t[TOP] = 5000.0;
  }
  else {
     t[BOTTOM] = -y[ball_num]/vy[ball_num];
     t[TOP] = (1.0 - y[ball_num])/vy[ball_num];
  } /* end if */

  /* Second, find the wall that is closest */
  shortest_time = 5000.0;
  for (j=0;j<NUM_WALLS;j++)
    if ((t[j] < shortest_time) && 
        (t[j] >  0.001))
        shortest_time = t[j];
  return(shortest_time);
} /* end collision_time() */

/* Update new positions of all balls */
update_positions(time_to_impact)
float time_to_impact;
{
  int ball_num;

  for (ball_num=0;ball_num<NUM_BALLS;ball_num++) {
    x[ball_num] += time_to_impact*vx[ball_num];
    if((x[ball_num] <= 0.0001) || (x[ball_num] >= 0.9999)) 
       vx[ball_num] = -vx[ball_num];

    y[ball_num] += time_to_impact*vy[ball_num];
    if((y[ball_num] <= 0.0001) || (y[ball_num] >= 0.9999)) 
       vy[ball_num] = -vy[ball_num];
  } /* end for */
} /* end update_positions() */



