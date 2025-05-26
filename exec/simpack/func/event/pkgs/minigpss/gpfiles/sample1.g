      Simulate
      Generate  8      
      Priority 10
      transfer 0.30,,Fac2  thirty percent of arrivals branch to fac2    
       Priority 1
       Queue    Line1
       Seize    Line1
       Depart   Line1
      Advance  10
      Release  Line1
      Terminate  1

Fac2  Queue    Line1
      Seize    Line1
      Depart   Line1
      Advance  1
      Release  Line1
      Terminate 1

Start    50                     
end
