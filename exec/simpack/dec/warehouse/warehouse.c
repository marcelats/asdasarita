/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include "../../func/queuing/queuing.h"

#define ORDER 1
#define SHIP 2
#define DURBAN 3
#define BALTIMORE 4

main()
  { 
    int event,queue_id,i,iteration;
    TOKEN shipment;
    float warehouse_stock,warehouse_time,warehouse_cost;
    float shipment_amount,ship_frequency,order_amount,order_frequency;
    float to_durban,to_baltimore,last_time;
    float minimum_cost=9999999.0,minimum_shipment=9999999.0;
    double sample;

    shipment.attr[0] = 1;
    shipment_amount = 100.0;
    while (shipment_amount<=1000.0) {

    shipment_amount += 10.0;
    /* things to vary */
    warehouse_cost = 0.0;
    ship_frequency = 4.0;
    order_amount = 333.0;
    order_frequency = 4.0;
    to_durban = 2.0;
    to_baltimore = 4.0;
    warehouse_stock = 1500.0;
    last_time = 0.0;

    init_simpack(LINKED);
    schedule(ORDER,0.0,shipment);
    schedule(SHIP,0.0,shipment);
    iteration = 0;
    while (sim_time()< 600.0)
      {
        next_event(&event,&shipment); 
        iteration++;
        if (shipment_amount == 340.00) printf("%f %f\n",sim_time(),warehouse_stock);
        if (warehouse_stock <= 0.0) goto exit;
        switch(event)
          {
          case ORDER: 
               update_arrivals();
               warehouse_stock = warehouse_stock - order_amount;
               warehouse_time = sim_time() - last_time;
               warehouse_cost = warehouse_cost + 
                                0.75 * warehouse_time * warehouse_stock;
               last_time = sim_time();
               schedule(ORDER,order_frequency,shipment);
               break;

          case SHIP:
               schedule(DURBAN,to_durban,shipment);
               schedule(SHIP,ship_frequency,shipment);
               break;

          case DURBAN:
               schedule(BALTIMORE,to_baltimore,shipment);
               break;

          case BALTIMORE:
               warehouse_stock = warehouse_stock + shipment_amount;
               update_completions();
               break;
	     }
      }
      if (warehouse_cost < minimum_cost) {
         minimum_cost = warehouse_cost;
         minimum_shipment = shipment_amount;
       }
 exit: end_simpack();
    } /* while shipment_amount */
    printf("Minimum Amount %f, Minimum Cost %f\n",
            minimum_shipment,minimum_cost);
  } /* end main() */



