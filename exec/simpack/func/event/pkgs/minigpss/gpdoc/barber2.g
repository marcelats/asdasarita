* BARBERSHOP MODEL WITH TWO BARBERS    
   
          SIMULATE   
          STORAGE    S$BARBERSHOP,2      DECLARE 2 BARBERS   
   
* MODEL DEFINITION   
         
          GENERATE   18,6              CUSTOMERS ARRIVE UNIFORMLY (12,24)    
          QUEUE      BARBERSHOP        CUSTOMER QUEUED   
          ENTER      BARBERSHOP        ENTER BARBERSHOP    
          DEPART     BARBERSHOP        WHEN FREE SERVER, RELEASE FROM QUEUE   
          ADVANCE    16,4              CUSTOMER IS SERVED   
          LEAVE      BARBERSHOP        LEAVE BARBERSHOP    
          TERMINATE  1                DECREMENT TERMINATION COUNT   
          START      25               # OF TERMINATIONS    
          END   
*        
* END SIMULATION   

