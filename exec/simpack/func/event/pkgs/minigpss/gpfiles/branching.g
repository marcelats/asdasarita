* model with two independent facilities branching

      Simulate

      Generate  1 
      transfer  both,,Fac2  thirty percent of arrivals branch to fac2

      Queue    Line1
      Seize    Line1
      Depart   Line1
      Advance  1 
      Release  Line1
      Terminate  1

Fac2  Queue    Line2
      Seize    Line2
      Depart   Line2
      Advance  1  
      Release  Line2
      Terminate 1


Start    50                     
end
