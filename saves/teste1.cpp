/* ----------------------------------------------------------------------- */
#include <stdio.h>
#include <conio.h>
#include "smpl.h"
#include "rand.h"

main()
{
 /* definicoes */
 float Te = 200;
 unsigned int Maximo_Entidades = 0, Num_Max_Entidades = 20;
 char Flag_Reset = 1;
 char Flag_Reset = 1; int Event = 1, Customer = 1, Aleatorio;
 real Ta1 = null, Ts1 = null, Ts2 = null, Ts3 = null, Ts5 = null;
 int teste, teste2, teste3teste4;
 unsigned int Max1 = 0, Min1 = 1000;
 unsigned int Max5 = 0, Min5 = 1000;
 unsigned int Total_Clientes = 0; 
 unsigned int Total_Clientes = 0; 
 float TBatch = 0;
 int r = 0;
 FILE *p, *saida;
 saida = fopen("TESTE1.out","w");
 if ((p = sendto(saida)) == NULL)
    printf("Erro na saida \n");


 /* prepara o sistema de simulacao e da nome ao modelo */
 smpl(0," TESTE1");


 /* cria e da nome as facilidades */
 teste = facility("teste",1);
 teste2 = facility("teste2",1);
 teste3 = facility("teste3",1);
 teste4 = facility("teste4",1);

 /* escalona a chegada do primeiro cliente */
      schedule(1,1.0, Customer);
      schedule(1,1.0, Customer);


 while( (time() < Te) && (Maximo_Entidades < Num_Max_Entidades)&& (r== 0) )
{
    cause(&Event,&Customer);
    switch(Event)
    {
        case 1 : 
          schedule(2,0.0,Customer);
