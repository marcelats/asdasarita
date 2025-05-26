/* ----------------------------------------------------------------------- 
Código gerado com o ASDA - Ambiente de Simulação Distribuída Automático
--------------------------------------------------------------------------*/
#include "queuing.h"

main()
{
 /* definicoes */
  Token Customer(1);
  int Aleatorio;
  
 float Te = 100000;
 float Ta1 = 0.0833, Ts1 = 0.04, Ts2 = 0.05;
 int i = 0;

 Facility *CS_1, *CS_2;

 /* prepara o sistema de simulacao e da nome ao modelo */
 new Future(LINKED);


 /* cria e da nome as facilidades */
 CS_1 = new Facility("CS_1");
 CS_2 = new Facility("CS_2");

 /* escalona a chegada do primeiro cliente */
   Future::Schedule(1,1.0, Customer);

 while ( (Future::SimTime() < Te) )
 {
    Estatus es = Future::NextEvent();
    switch(es.event_id)
   {
        case 1 : 
         {
          Token Customer = Future::CurrentToken();
          Future::UpdateArrivals();
          Future::Schedule(2,0.0, Customer);
          stream(7);
          Customer.Id(Customer.Id() + 1);
          Future::Schedule(1,expntl(Ta1), Customer);
         }
          break;

        /*  centro de serviço = CS_1 */
        case 2 : 
         {
          Token Customer = Future::CurrentToken();
          if (CS_1->Request(Customer) == FREE)
             Future::Schedule(3,expntl(Ts1), Customer);
         }
          break;
        case 3 : 
         {
          Token Customer = Future::CurrentToken();
          CS_1->Release( Customer.Id() );
          Aleatorio = random(1,10000);
          if (( 1 <= Aleatorio) && ( Aleatorio <= 4000) )
           Future::Schedule(4,0.0, Customer);
         }
          break;

        /*  centro de serviço = CS_2 */
        case 4 : 
         {
          Token Customer = Future::CurrentToken();
          if (CS_2->Request(Customer) == FREE)
             Future::Schedule(5,expntl(Ts2), Customer);
         }
          break;
        case 5 : 
         {
          Token Customer = Future::CurrentToken();
          CS_2->Release( Customer.Id() );
             Future::Schedule(2,0.0, Customer);
         }
          break;
      default: ErrXit(1,"bad event id");
   }
 }


/* gera o relatorio da simulacao */
   Future::ReportStats();
 return 0;
}
/* ----------------------------------------------------------------------- */
