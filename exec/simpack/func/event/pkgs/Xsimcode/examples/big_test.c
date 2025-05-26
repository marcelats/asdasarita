/* ------------------------------------------------   
   Simpack Code - Created by Xsimcode

   Sun Nov 24 15:31:13 1991
   File: big_test.c
--------------------------------------------------- */


#include "queuing.h"
#define NUM_TOKENS 1000
#define MAX_WEIGHTS 10
#define NUM_FACILITIES 11
int cumulative();

main()
{
   int     arc[MAX_WEIGHTS];/* used for a cumulative distribution  */
   float   weight[MAX_WEIGHTS];/* also used for a cumulative distn */
   int     num;  /* # of arcs - for a cumulative distn */
   int     priority =  0;
   int     nextQ;         /* Used by routing points */
   TOKEN   token;     /* object that flow through facilities */
   TOKEN   nextToken; 

   int     i,       /* loop counter                */
           event,       /* next event to occur         */
           numTokens=1; /* number of tokens in model */
   int     facility[NUM_FACILITIES+1];


   init_simpack(HEAP);

   /* Create Facilities */
   facility[1] = create_facility( "FAC1", 1);
   facility[2] = create_facility( "FAC2", 1);
   facility[3] = create_facility( "FAC3", 1);
   facility[4] = create_facility( "FAC4", 1);
   facility[5] = create_facility( "FAC5", 1);
   facility[6] = create_facility( "FAC6", 1);
   facility[7] = create_facility( "FAC7", 1);
   facility[8] = create_facility( "FAC8", 1);
   facility[9] = create_facility( "FAC9", 1);
   facility[10] = create_facility( "FAC10", 1);
   facility[11] = create_facility( "FAC11", 1);

   /* Schedule initial release of tokens */
   for (i=1; i<= 1; i++)
   {
      token.attr[0] = (float) i;
      schedule( 1,0.0, token );
   }
   numTokens = 1;

   /* Specify simulation run time*/
   while ( sim_time() <= 100.000000 )
   {
      /* Determine next event in simulation */
      next_event( &event, &token);

      /* Process the event */
      switch( event )
      {
      /* Arrivals */
         case 1:
            update_arrivals();

            /* Schedule next arrival */
            nextToken.attr[0] = (float) ++numTokens;
            schedule( 1,     2.00 , nextToken);

            /* Schedule first resource */
            schedule( 2, 0.0, token);
            break;

         /* Request facility FAC1 */
         case 2:
            if (request
               (facility[1], token, priority) == FREE)
                  schedule( 3,      1.00 , token);
            break;

         /* Release facility FAC1 */
         case 3:
            release( facility[1], token);
            schedule( 4, 0.0, token);
            break;

         /* Fork # 1 */
         case 4:
            /* Select the next facility */
            weight[0] = 0.10;   arc[0] = 5;
            weight[1] = 0.10;   arc[1] = 6;
            weight[2] = 0.10;   arc[2] = 7;
            weight[3] = 0.10;   arc[3] = 8;
            weight[4] = 0.10;   arc[4] = 9;
            weight[5] = 0.10;   arc[5] = 10;
            weight[6] = 0.10;   arc[6] = 11;
            weight[7] = 0.10;   arc[7] = 12;
            weight[8] = 0.10;   arc[8] = 13;
            weight[9] = 0.10;   arc[9] = 14;
            num = 10;
            nextQ = cumulative( weight, arc, num );
            schedule( nextQ, 0.0, token);
            break;

         /* Request facility FAC10 */
         case 5:
            if (request
               (facility[10], token, priority) == FREE)
                  schedule( 15,      1.00 , token);
            break;

         /* Release facility FAC10 */
         case 15:
            release( facility[10], token);
            schedule( 16, 0.0, token);
            break;

         /* Join # 2 */
         case 16:
            update_completions();
            break;

         /* Request facility FAC3 */
         case 6:
            if (request
               (facility[3], token, priority) == FREE)
                  schedule( 17,      1.00 , token);
            break;

         /* Release facility FAC3 */
         case 17:
            release( facility[3], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC9 */
         case 7:
            if (request
               (facility[9], token, priority) == FREE)
                  schedule( 18,      1.00 , token);
            break;

         /* Release facility FAC9 */
         case 18:
            release( facility[9], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC8 */
         case 8:
            if (request
               (facility[8], token, priority) == FREE)
                  schedule( 19,      1.00 , token);
            break;

         /* Release facility FAC8 */
         case 19:
            release( facility[8], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC11 */
         case 9:
            if (request
               (facility[11], token, priority) == FREE)
                  schedule( 20,      1.00 , token);
            break;

         /* Release facility FAC11 */
         case 20:
            release( facility[11], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC7 */
         case 10:
            if (request
               (facility[7], token, priority) == FREE)
                  schedule( 21,      1.00 , token);
            break;

         /* Release facility FAC7 */
         case 21:
            release( facility[7], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC6 */
         case 11:
            if (request
               (facility[6], token, priority) == FREE)
                  schedule( 22,      1.00 , token);
            break;

         /* Release facility FAC6 */
         case 22:
            release( facility[6], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC5 */
         case 12:
            if (request
               (facility[5], token, priority) == FREE)
                  schedule( 23,      1.00 , token);
            break;

         /* Release facility FAC5 */
         case 23:
            release( facility[5], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC4 */
         case 13:
            if (request
               (facility[4], token, priority) == FREE)
                  schedule( 24,      1.00 , token);
            break;

         /* Release facility FAC4 */
         case 24:
            release( facility[4], token);
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC2 */
         case 14:
            if (request
               (facility[2], token, priority) == FREE)
                  schedule( 25,      1.00 , token);
            break;

         /* Release facility FAC2 */
         case 25:
            release( facility[2], token);
            schedule( 16, 0.0, token);
            break;
      }
   }
   report_stats();
}
/* ------------------------------------------------   
   cumulative()

   A discrete, non-uniform distribution used by forks.
   It allows arcs to have weights.
--------------------------------------------------- */
int cumulative( weight, arc, num)
   float weight[];
   int   arc[];
   int   num;
{
   int   index;
   int   i;
   float sample;

   for( i=1; i <num; i++ )
      weight[i] += weight[i-1];   /* build distribution in input array */

   sample = uniform( 0.0, 1.0 );
   index = 0;
   while( weight[index] < sample )
      index++;

   return( arc[index] );
}
