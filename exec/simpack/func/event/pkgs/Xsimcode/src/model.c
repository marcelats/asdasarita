/* ------------------------------------------------   
   Simpack Code - Created by Xsimcode

   Fri Jul 28 17:16:21 1995
   File: model
--------------------------------------------------- */


#include "queuing.h"
#define NUM_TOKENS 1000
#define MAX_WEIGHTS 10
#define NUM_FACILITIES 1
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
