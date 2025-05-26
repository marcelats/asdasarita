    * Model with multiple servers and served twice

           Simulate
           Storage  S$Food,2    declare # of servers

    * Block Definition
      
           Generate 48,6        Customer arrives
           Queue    food        Customer queued
           Enter    food        Enter facility 
           Depart   food        When free, released from queue
           Advance  16,4        service time 
           Leave    food        customer leaves facility 

           Advance   10         Pause until customer can re-enter 

* Customer re-enters facility

           Queue    food 
           Enter    food 
           Depart   food 
           Advance  2,1
           Leave    food 

           Terminate 1          decrement termination count

           Start      25        # of terminations 
           end
          
     * End Simulation
