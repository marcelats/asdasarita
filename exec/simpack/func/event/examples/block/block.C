#include "queuing.h"
#include <stdio.h>

#define GENERATE_PARTS 1
#define REQUEST_ACC 2
#define BLOCK_ACC 3
#define RELEASE_ACC 4
#define REQUEST_LATHE 5
#define BLOCK_LATHE 6
#define RELEASE_LATHE 7
#define REQUEST_INSPECTOR 8
#define RELEASE_INSPECTOR 9

#define NUM_PARTS 100

TOKEN a_token;

main()
  {
    int i,event,id,accumulator,lathe,inspector,count_parts=NUM_PARTS;
    int acc_waiting,lathe_waiting,acc_waiting_id,lathe_waiting_id;
    float lathe_to_release,blocking_time;
    float cost_part_gen, cost_labor_server1, cost_labor_server2;
    float total_cost;

    init_simpack(LINKED);
    accumulator=create_facility("ACC",1);
    lathe=create_facility("LATHE",1);
    inspector=create_facility("INSPECTOR",1);
    for (i=1; i<=count_parts; i++) {
     a_token.attr[0] = (float) i;
     schedule(GENERATE_PARTS,0.0,a_token);
    } /* end for */
    count_parts = NUM_PARTS;
    while (count_parts > 0)
      {
        next_event(&event,&a_token);
        id = (int) a_token.attr[0];
        switch(event)
          {
            case GENERATE_PARTS:
              schedule(REQUEST_ACC,0.0,a_token);
              update_arrivals();
              break;
            case REQUEST_ACC:
              if (request(accumulator,a_token,0) == FREE)
                 schedule(BLOCK_ACC,2.0,a_token);
              break;
            case BLOCK_ACC:
              acc_waiting = TRUE;
              acc_waiting_id = id;
              if (facility_size(lathe) == 0) {
                acc_waiting = FALSE;
                schedule(RELEASE_ACC,0.0,a_token);
              }
              break;
            case RELEASE_ACC:
              acc_waiting = FALSE;
              release(accumulator,a_token);
              schedule(REQUEST_LATHE,0.0,a_token);
              break;
            case REQUEST_LATHE:
              if (request(lathe,a_token,0) == FREE)
                 schedule(BLOCK_LATHE,normal(120.0,3.0),a_token);
              break;
            case BLOCK_LATHE:
              lathe_waiting = TRUE;
              lathe_waiting_id = id;
              if (facility_size(inspector) <= 3) {
                lathe_waiting = FALSE;
                schedule(RELEASE_LATHE,0.0,a_token);
              }
              break;
            case RELEASE_LATHE:
              lathe_waiting = FALSE;
              release(lathe,a_token);
              if (acc_waiting) {
                 a_token.attr[0] = (int) acc_waiting_id;
                 schedule(RELEASE_ACC,0.0,a_token);
              }
              schedule(REQUEST_INSPECTOR,0.0,a_token);
              break;
            case REQUEST_INSPECTOR:
              if (request(inspector,a_token,0) == FREE)
                 schedule(RELEASE_INSPECTOR,normal(15.0,1.0),a_token);
              break;
            case RELEASE_INSPECTOR:
              release(inspector,a_token);
              if (lathe_waiting) {
                 a_token.attr[0] = (int) lathe_waiting_id;
                 schedule(RELEASE_LATHE,0.0,a_token);
              }
              count_parts--;
              update_completions();
              break;
          }
      }
    printf("Costs for Part Processing\n");
    cost_part_gen = NUM_PARTS*0.40;
    cost_labor_server1  = (busy_time(lathe)/3600.0)*15.50;
    cost_labor_server2  = (busy_time(inspector)/3600.0)*14.00;
    total_cost = cost_part_gen+cost_labor_server1+cost_labor_server2;
    printf("Cost for part generation: $%.2f\n", cost_part_gen);
    printf("Cost of labor for server 1: $%.2f\n", cost_labor_server1);
    printf("Cost of labor for server 2: $%.2f\n", cost_labor_server2);
    printf("Total Cost is $%.2f\n",total_cost);
  fflush(stdout);
    report_stats(); printf("\n\n");
  return 0;
  }



