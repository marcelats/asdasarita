    * Barbershop Model with single server and timed 

           Simulate


    * Block Definition
      
           Generate 18,  6      Customer arrives
           Queue    Barber      Customer queued
           Seize    Barber      Reserve server
           Depart   Barber      When free, released from queue
           Advance  16,4        service time 
           Release  Barber      Free Joe
           Terminate            

           generate  1000        At time 1000, decrement termination count
           Terminate 1

           Start     1         # of terminations 
           end
     *     
     * End Simulation
