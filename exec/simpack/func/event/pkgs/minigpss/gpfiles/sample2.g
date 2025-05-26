      Simulate
      Generate  8      
      Priority 10
      transfer BOTH,,Fac2  tokens attempt each facility; goes to avail facil    
      
       Queue    Line1
       Seize    Line1
       Depart   Line1
      Advance  10
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
