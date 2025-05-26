      Simulate
      Generate  RVNORM(8,2)      
      transfer BOTH,,Fac2  tokens attempt each queue arrivals branch to fac2    
      
       Queue    Line1
       Seize    Line1
       Depart   Line1
      Advance  RVUNI(2,10)
      Release  Line1
      Terminate  1

Fac2  Queue    Line2
      Seize    Line2
      Depart   Line2
      Advance  RVEXPO(6)
      Release  Line2
      Terminate 1

Start    50                     
end
