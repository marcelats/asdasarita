/* ------------------------------------------------   
   Simpack Code - Created by Xsimcode

   Sun Dec  1 19:23:03 1991
   File: combined1
--------------------------------------------------- */


#include "queuing.h"
#define NUM_TOKENS 1000
#define MAX_WEIGHTS 10
#define NUM_FACILITIES 2
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
   extern int Belt();
   extern int initGeneric();



   init_simpack(HEAP);

   /* Create Facilities */
   facility[1] = create_facility( "Check-In", 1);
   facility[2] = create_facility( "Load-Baggage", 1);

   /* Schedule initial release of tokens */
   for (i=1; i<= 1; i++)
   {
      token.attr[0] = (float) i;
      schedule( 1,0.0, token );
   }
   numTokens = 1;
   initGeneric();

   /* Specify simulation run time*/
   while ( sim_time() <= 1000.000000 )
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
            schedule( 1,   200.00 , nextToken);

            /* Schedule first resource */
            schedule( 2, 0.0, token);
            break;

         /* Request facility Check-In */
         case 2:
            if (request
               (facility[1], token, priority) == FREE)
                  schedule( 3,    200.00 , token);
            break;

         /* Release facility Check-In */
         case 3:
            release( facility[1], token);
            initTokenForBelt(&token);
            schedule( 4, 0.0, token);
            break;

         /* Generic Block # 1 */
         case 4:
            /* Call external generic function */
            Belt(&token);
/*
            schedule( 5, 0.0, token);
*/
            break;

         /* Request facility Load-Baggage */
         case 5:
            if (request
               (facility[2], token, priority) == FREE)
                  schedule( 6,    200.00 , token);
            break;

         /* Release facility Load-Baggage */
         case 6:
            release( facility[2], token);
            update_completions();
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
