     * Barbershop Model with two barbers 

           Simulate
           Storage S$BARBERSHOP,2      Declare 2 barbers


    * Model Definition
      
           Generate  8,2       Customers arrive uniformly 
           Queue    BARBERSHOP        Customer queued
           Enter    BARBERSHOP        Enter Barbershop 
           Depart   BARBERSHOP        When free server, release from queue
           Advance   1             Customer is served
           Leave    BARBERSHOP        Leave Barbershop 
           Terminate 1                decrement termination count
           Start     25               # of terminations 
           end
     *     
     * End Simulation
