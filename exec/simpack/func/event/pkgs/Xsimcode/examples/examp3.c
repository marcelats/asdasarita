/* ------------------------------------------------   
   Simpack Code - Created by Xsimcode

   Sun Nov 24 16:13:37 1991
   File: model.c
--------------------------------------------------- */


#include "queuing.h"
#define NUM_TOKENS 1000
#define MAX_WEIGHTS 10
#define NUM_FACILITIES 6
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
            schedule( 1,expntl(     0.20 ), nextToken);

            /* Schedule first resource */
            schedule( 2, 0.0, token);
            break;

         /* Fork # 1 */
         case 2:
            /* Select the next facility */
            weight[0] = 0.33;   arc[0] = 3;
            weight[1] = 0.33;   arc[1] = 4;
            weight[2] = 0.33;   arc[2] = 5;
            num = 3;
            nextQ = cumulative( weight, arc, num );
            schedule( nextQ, 0.0, token);
            break;

         /* Request facility FAC3 */
         case 3:
            if (request
               (facility[3], token, priority) == FREE)
                  schedule( 6, normal(     0.50,     0.10), token);
            break;

         /* Release facility FAC3 */
         case 6:
            release( facility[3], token);
            schedule( 7, 0.0, token);
            break;

         /* Fork # 4 */
         case 7:
            /* Select the next facility */
            weight[0] = 0.60;   arc[0] = 8;
            weight[1] = 0.30;   arc[1] = 9;
            weight[2] = 0.10;   arc[2] = 10;
            num = 3;
            nextQ = cumulative( weight, arc, num );
            schedule( nextQ, 0.0, token);
            break;

         /* Join # 7 */
         case 8:
            schedule( 11, 0.0, token);
            break;

         /* Request facility FAC6 */
         case 11:
            if (request
               (facility[6], token, priority) == FREE)
                  schedule( 12, normal(     0.40,     0.25), token);
            break;

         /* Release facility FAC6 */
         case 12:
            release( facility[6], token);
            schedule( 13, 0.0, token);
            break;

         /* Join # 8 */
         case 13:
            update_completions();
            break;

         /* Join # 6 */
         case 9:
            schedule( 14, 0.0, token);
            break;

         /* Request facility FAC5 */
         case 14:
            if (request
               (facility[5], token, priority) == FREE)
                  schedule( 15, normal(     0.40,     0.25), token);
            break;

         /* Release facility FAC5 */
         case 15:
            release( facility[5], token);
            schedule( 13, 0.0, token);
            break;

         /* Join # 5 */
         case 10:
            schedule( 16, 0.0, token);
            break;

         /* Request facility FAC4 */
         case 16:
            if (request
               (facility[4], token, priority) == FREE)
                  schedule( 17, normal(     0.40,     0.25), token);
            break;

         /* Release facility FAC4 */
         case 17:
            release( facility[4], token);
            schedule( 13, 0.0, token);
            break;

         /* Request facility FAC2 */
         case 4:
            if (request
               (facility[2], token, priority) == FREE)
                  schedule( 18, normal(     0.50,     0.10), token);
            break;

         /* Release facility FAC2 */
         case 18:
            release( facility[2], token);
            schedule( 19, 0.0, token);
            break;

         /* Fork # 3 */
         case 19:
            /* Select the next facility */
            weight[0] = 0.20;   arc[0] = 8;
            weight[1] = 0.60;   arc[1] = 9;
            weight[2] = 0.20;   arc[2] = 10;
            num = 3;
            nextQ = cumulative( weight, arc, num );
            schedule( nextQ, 0.0, token);
            break;

         /* Request facility FAC1 */
         case 5:
            if (request
               (facility[1], token, priority) == FREE)
                  schedule( 20, normal(     0.50,     0.10), token);
            break;

         /* Release facility FAC1 */
         case 20:
            release( facility[1], token);
            schedule( 21, 0.0, token);
            break;

         /* Fork # 2 */
         case 21:
            /* Select the next facility */
            weight[0] = 0.60;   arc[0] = 8;
            weight[1] = 0.30;   arc[1] = 9;
            weight[2] = 0.10;   arc[2] = 10;
            num = 3;
            nextQ = cumulative( weight, arc, num );
            schedule( nextQ, 0.0, token);
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
