    *  Series  Model

           Simulate


    * Model Definition
      
           Generate 18,6  
    * Phase 1

           Queue   Phase1 
           Seize    Phase1 
           Depart   Phase1 
           Advance  16,4 
           Release  Phase1 
    * Phase 2

           Queue    Phase2 
           Seize    Phase2 
           Depart   Phase2 
           Advance  5,5 
           Release  Phase2 
           Terminate 1            decrement termination count
           Start     25           # of terminations 
           end
    * End Simulation
