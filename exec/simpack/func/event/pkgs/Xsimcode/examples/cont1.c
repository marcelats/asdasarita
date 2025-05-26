/*---------------------------------------------
   cont.c
   12/1/91
   Brian Harrington
   derived from->
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/
#include "queuing.h"
#define BELT_MOVING 4
#define PACKING 5

float delta_time,in[4];

/*--------------------------
   Belt

   models continuous movement
  --------------------------*/
void
Belt(token)
	TOKEN *token;
{
	state();
	integrate(token);
	if (state_event(*token)) 
		schedule(PACKING,0.0,*token);
	else
		schedule(BELT_MOVING,delta_time,*token);
}

/* 
** state event transition 
*/
state_event(token)
	TOKEN token;
{
	if (token.attr[1] >= 400.0)
		return (TRUE);
	else
		return (FALSE);
}

/* 
** initialization for each token 
*/
initTokenForBelt(token)
	TOKEN *token;
{
	token->attr[1] = 0.0;
	delta_time = .1;
}

/*
**  Calculate state: x' = 2 
*/
state()
{ 
	in[1] = 2.0;
}
 
/*
**  change in state 
*/
integrate(token)
	TOKEN *token;
{
	token->attr[1] += in[1]*delta_time;
}

/*
** unused 
*/
initGeneric()
{
} 
