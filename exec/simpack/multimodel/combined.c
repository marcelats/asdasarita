/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include "../func/queuing/queuing.h"
#define ARRIVAL 1
#define PLACE_ITEMS 2
#define REQUEST_SERVER 3
#define PACKING 4
#define BELT_MOVING 5

int event,queue_id;
float delta_time,in[4],out[4];
TOKEN customer;

main()
 { 
  init_simpack(HEAP);
  queue_id = create_facility("cashier",1);
  customer.attr[0] = 1;
  schedule(ARRIVAL,0.0,customer);
  while (customer.attr[0] <= 30.0)   {
      next_event(&event,&customer);
      switch(event) {

      /*-----------------------------------*/
      /* discrete event models             */
      /*-----------------------------------*/
      case ARRIVAL: 
         update_arrivals();
         schedule(PLACE_ITEMS,0.0,customer);
         customer.attr[0] += 1;
         schedule(ARRIVAL,expntl(90.0),customer);
         break;
      case PLACE_ITEMS:
         schedule(REQUEST_SERVER,uniform(20.0,30.0),customer);
         break;
      case REQUEST_SERVER: 
         if (request(queue_id,customer,0) == FREE) {
           init_conditions();
           schedule(BELT_MOVING,4.0,customer);
         }
         break;
      case PACKING:  /* release server */
         release(queue_id,customer);
         update_completions();
         break;

      /*--------------------------*/
      /* continuous model         */
      /*--------------------------*/
       case BELT_MOVING:
         state();
         integrate();
         if (state_event()) 
           schedule(PACKING,normal(120.0,15.0),customer);
         else
           schedule(BELT_MOVING,delta_time,customer);
         break;
       } /* end switch */
    } /* end while */
  report_stats();
} /* end main() */

state_event()
/* state event transition */
{
  if (out[1] >= 3.0)
    return (TRUE);
  else
    return (FALSE);
}

init_conditions()
{
  out[1] = 0.0;
  delta_time = 0.1;
}

state()
{ 
/* Calculate state: x' = 2 */
 in[1] = 2.0;
}
 
integrate()
{
 int i;
 out[1] += in[1]*delta_time;
}
 
