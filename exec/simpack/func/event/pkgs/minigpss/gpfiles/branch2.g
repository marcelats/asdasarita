* model with two independent facilities branching

      Simulate

      Generate  1 
      transfer  0.30,,Fac2  thirty percent of arrivals branch to fac2
      Generate  8,4
      Queue    Line1
      Seize    Line1
      Depart   Line1
      Advance  rvexpo(4)
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
