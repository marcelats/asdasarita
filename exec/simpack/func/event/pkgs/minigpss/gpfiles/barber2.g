     * Barbershop Model with two barbers 

           Simulate
           Storage S$BARBERSHOP,2      Declare 2 barbers


    * Model Definition
      
           Generate  rvnorm(8,2)
           Queue    BARBERSHOP        
           Enter    BARBERSHOP        
           Depart   BARBERSHOP  
           Advance  rvexpo(8,2)           
           Leave    BARBERSHOP  
           Terminate 1          
           Start     25         
           end
     *     
     * End Simulation
