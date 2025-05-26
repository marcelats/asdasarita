/******************************************************
 *      Module Filename: bif3.c
 *
 *      Description:    This plots the bifurcation of
 *                      the logistic equation
 *			x(t) = a x(t-1) (1 - x(t-1))
 *			with values of a in [1.5, 4.0].
 *			This checks to see if the
 *			last two points might be at a
 *			steady state and then goes to
 *			the next value of alpha.
 *
 *	Note:		The points should be plotted
 *			without connecting lines.
 *
 *			This code was almost entirely
 *			taken from log1.c.
 *-----------------------------------------------------
 *      Creation Date:	April 15, 1991
 *      Author:  William Dean Norris II
 *****************************************************/

#include <stdio.h>
#include <math.h>

#define EP	.0000001	/* The error value */

long	cur_time, delta_time;
double	a, prev[2], next[2];

extern void exit();

void init_conditions ()
{
   prev[1] = 0.8;
   cur_time = 0;
   delta_time = 1;
}

void state ()
{ 
   /* Calculate state: x(t) = a x(t-1) (1 - x(t-1)) */
   next[1] = a * prev[1] * (1.0 - prev[1]);
}

void update ()
{
   prev[1] = next[1];
   cur_time += delta_time;
}				/* update */

void main ()
{
   double	first;
   
   for (a = 1.5; a <= 4.0; a += 0.01) {
   
      init_conditions ();
      
      /* let settle */
      while (cur_time <= 100) {
	 state ();
	 update ();
      }				/* end while */
      first = prev[1];
      
      /* plot points */
      while (cur_time <= 150) {
	 state ();
	 (void) printf("%lf %lf\n", a, prev[1]);
	 update ();
	 if (fabs ((first - prev[1])) < EP) break;
      }				/* while */
   }				/* for */
   exit (0);
   /* NOTREACHED */
}				/* main */

