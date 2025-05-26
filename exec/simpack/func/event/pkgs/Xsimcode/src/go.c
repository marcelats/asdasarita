/**********************************************************************
			     	- NOTICE -
	Source Code owned by Brian Harrington (c) 1991
	May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : go.c 12/1/91 22:02:28
**		Author    : Brian Harrington
**		Purpose   : Generate C code from the data structure "settings" 
                    (described in go.h).
**		History   :
                  :origin:   6/12/90
**
**********************************************************************/

/*
 * Modified 950728 by robert cubert as part of release of SimPack3:
 * The emitted code of whatever.c (by default it is model.c)
 * now does #include "queuing.h" instead of the previous version
 * which did #include "../../../queuing/queuing.h", for 2 reasons:
 * first, we want emitted code to be free of the relative location of
 * queuing.h (instead that location will be specified by -I on the
 * compilation line in the makefile); and, second, the relative location
 * specified did not seem consistent with the location of queuing.h in 
 * SimPack2.x so either something had changed or robert did not understand
 * what is going on in Xsimcode.
 *
 * Robert did an experiment, prior to the change, in which he copied examp1.sim
 * from Xsimcode/examples to Xsimcode/src, ran Xsimcode, and generated
 * examp1.c from examp1.sim, then used diff to compare the result with the
 * examp1.c in the Xsimcode/examples directory.  Turned out the
 * ONLY difference was examples/examp1.c had NO directory dependence
 * on queuing.h.  In fact the way the code has been revised, it
 * NOW generates code identical to examples/*.c, which it did NOT before (?!).
 */
  
   
#ifndef lint
        static char sccs_id[] = "@(#)go.c	1.21 12/1/91 22:02:28";
#endif /* lint */

#include "modeller.h"
#include <time.h>
#include <unistd.h>




/* ===================================================================
   GLOBAL VARIABLES - FROM OTHER FILES
   =================================================================== */
   /* Data structure that contains all the model parameters.  Created in
   create.h and initialized in initg */

extern struct Settings settings;

/* ===================================================================
   GLOBAL VARIABLES
   =================================================================== */
   char sp3[4], sp6[7], sp9[10],
       sp12[13], sp15[16];    /* Strings of spaces used for indention */
   Boolean genericBlock=FALSE;  /* TRUE if at least one generic block
				was used */

void addToSwitch( FILE *, struct List *, int *, int*);
void addDepartureCaseForFanOut( FILE* );


/* -------------------------------------------------------------------
   initGo 

   Reset variables before processing. 
   ------------------------------------------------------------------- */
void initGo()
{
	int  i,j;

	settings.sinkCaseNum = 0;

	for( i=0; i <= MAX_ELEMENTS; i++ )
	{
		settings.routing[i].written = FALSE;
		settings.facility[i].written = FALSE;
		settings.generic[i].written = FALSE;

		settings.routing[i].caseNum = 0;
		settings.facility[i].caseNum = 0;
		settings.generic[i].caseNum = 0;
	}
}

/* -------------------------------------------------------------------
   CreateStrSpaces

   Create strings of blank characters for indention. (sp3 uses 6 spaces)
   ------------------------------------------------------------------- */
void createStrSpaces()
{
	char bigStr[24];
	int  i;

	for (i=0; i< 24; i++)
		bigStr[i] = ' ';

	strncpy( sp3, bigStr, 3);
	sp3[3] = '\0';
	strncpy( sp6, bigStr, 6);
	sp6[6] = '\0';
	strncpy( sp9, bigStr, 9);
	sp9[9] = '\0';
	strncpy( sp12, bigStr, 12);
	sp12[12] = '\0';
	strncpy( sp15, bigStr, 15);
	sp15[15] = '\0';

}



/* ===================================================================
   PROCEDURES TO PARSE DISTRIBUTION & PARAMETERS
   =================================================================== */


/* -------------------------------------------------------------------
   addDistn

   Print the name of distribution used by the given list element
   (either a facility, arrival point or routing point).
   ------------------------------------------------------------------- */
void addDistn( fp, distn, param1, param2, param3 )
	FILE *fp;         /* id of C code file                   */
	int  distn;       /* type of probability distribution    */
	float param1,     /* parameters to the given probability */
	      param2,     /*    distribtion.  Some may be unused.*/
	      param3;
{

	switch (distn)
	{
		case UNIFORM:
			fprintf( fp, "uniform( %8.2f, %8.2f)",
				param1, param2);
			break;
		case EXPONENTIAL:
			fprintf( fp, "expntl( %8.2f )", param1);
			break;
		case NORMAL:
			fprintf( fp, "normal( %8.2f, %8.2f)",
				param1, param2);
			break;
		case ERLANG:
			fprintf( fp, "erlang( %8.2f, %8.2f)",
				param1, param2);
			break;
		case RANDOM:
			fprintf( fp, "random( (int) %8.0f, (int) %8.0f)",
				param1, param2);
			break;
		case HYPERX:
			fprintf( fp, "hyperx( %8.2f, %8.2f)",
				param1, param2);
			break;
		case TRIANGLE:
			fprintf( fp, "triang( %8.2f, %8.2f, %8.2f)",
				param1, param2, param3);
			break;
    	        case CONSTANT:
			fprintf( fp, " %8.2f ",param1);
			break;
		case CUMULATIVE:
			fprintf( fp, "cumulative( weight, arc, num )");
			break;
		default:
			fprintf(stderr,"ERROR: ");
			fprintf(stderr,"Illegal distn in addDistn %d\n",distn);

	}
}

/* -------------------------------------------------------------------
   addRoutingDistn

   Parse the routing point data structure (the array routing) to determine
   the type of distn.  Call addDistn() to print the distribution and
   appropriate parameters.
   ------------------------------------------------------------------- */
void addRoutingDistn( fp, id )
	FILE *fp;         /* id of C code file */
	int  id;          /* array index */
{
	addDistn( fp, settings.routing[id].distn, 0.0, 0.0, 0.0  );
}

/* -------------------------------------------------------------------
   addFacilityDistn

   Parse the facility data structure (the array facility) to determine
   the type of distn.  Call addDistn() to print the distribution and
   appropriate parameters.
   ------------------------------------------------------------------- */
void addFacilityDistn( fp, id )
	FILE *fp;         /* id of C code file */
	int  id;          /* array index */
{
	addDistn( fp, settings.facility[id].distn,
		      settings.facility[id].param1,
		      settings.facility[id].param2,
		      settings.facility[id].param3 );
}
/* -------------------------------------------------------------------
   addArrivalDistn

   Parse the arrival data structure (the array arrival) to determine
   the type of distn.  Call addDistn() to print the distribution and
   appropriate parameters.
   ------------------------------------------------------------------- */

void addArrivalDistn( fp, id )
	FILE *fp;         /* id of C code file */
	int  id;          /* array index */
{
	addDistn( fp, settings.arrival[id].distn,
		      settings.arrival[id].param1,
		      settings.arrival[id].param2,
		      settings.arrival[id].param3 );
}

/* ===================================================================
   PROCEDURES TO CREATE PARTS OF THE C FILE
   =================================================================== */

/* -------------------------------------------------------------------
   addComments

   Put initial comments, and variable declarations in C file.
   ------------------------------------------------------------------- */
void addComments( fp )
	FILE *fp;  /* id of C code file */
{
   time_t ltime;    /* or time of day */
   int numFacilities = settings.numFacilities;
   int i;


   fprintf( fp, "/* ------------------------------------------------   \n");
   fprintf( fp, "   Simpack Code - Created by Xsimcode\n");

   /* Get Unix-style time and display as number and string. */
   time( &ltime );
   fprintf( fp, "\n   %s", ctime( &ltime ) );

   fprintf( fp, "   File: %s\n", settings.fileName);
   fprintf( fp, "--------------------------------------------------- */\n");
   fprintf( fp, "\n\n#include \"queuing.h\"\n");
   fprintf( fp, "#define NUM_TOKENS %d\n", MAX_TOKENS);
   fprintf( fp, "#define MAX_WEIGHTS %d\n", MAX_WEIGHTS);
   fprintf( fp, "#define NUM_FACILITIES %d\n", numFacilities);
   fprintf( fp, "int cumulative();\n");

   fprintf( fp, "\nmain()\n{\n");
/******REMOVED token data struct ********************
   fprintf( fp, "   ** Token Data Structure **\n");
   fprintf( fp, "   struct\n");
   fprintf( fp, "   {\n");
   fprintf( fp, "%sint   priority;\n",sp6);
   fprintf( fp, "%sint   lastQ;\n",sp6);

   fprintf( fp, "   } tokenInfo[NUM_TOKENS+1];\n");
*************************************************************/
   fprintf( fp, "%sint     arc[MAX_WEIGHTS];/* used for a cumulative distribution  */\n",sp3);
   fprintf( fp, "%sfloat   weight[MAX_WEIGHTS];/* also used for a cumulative distn */\n",sp3);
   fprintf( fp, "%sint     num;  /* # of arcs - for a cumulative distn */\n",sp3);
   fprintf( fp, "%sint     priority =  %d;\n",sp3, settings.arrival[1].priority);
   fprintf( fp, "%sint     nextQ;         /* Used by routing points */\n",sp3);
   fprintf( fp, "   TOKEN   token;     /* object that flow through facilities */\n");
   if ( settings.departure == ABSORB )
	fprintf( fp, "   TOKEN   nextToken; \n");
   fprintf( fp, "\n   int     i,       /* loop counter                */\n");
   fprintf( fp, "           event,       /* next event to occur         */\n");
   fprintf( fp, "           numTokens=1; /* number of tokens in model */\n");
   fprintf( fp, "   int     facility[NUM_FACILITIES+1];\n");

	/* declare each generic block */

	for( i=1; i <=MAX_ELEMENTS; i++)
	{
		if( settings.generic[i].valid)
		{
			fprintf( fp,"   extern int %s();\n",
				settings.generic[i].nameStr);
			genericBlock = TRUE;
		}
	}

	if( genericBlock )
	{
		fprintf( fp, "   extern int initGeneric();\n\n");
	}


}

/* -------------------------------------------------------------------
   addTraceOptions

   Add code for Simpack tracing options
	1) Facility Queue
	2) Event List
	3) Heap
   ------------------------------------------------------------------- */
void addTraceOptions( fp )
	FILE *fp;  /* id of C code file */
{
	struct List *ptr;  /* pointer to elements in facility list */

	/* 1) Set up facility queue trace--if any */
	if ( settings.trace_facility == ON )
	{
		/* loop through the list of facilities to be traced */
		ptr = settings.fac_num;
		while (ptr != NULL)
		{
			fprintf( fp, "%strace_facility(%d);\n", sp6,
				ptr->id);
			ptr = ptr->next;
		}
	}

	/* 2) Set up event queue trace--if any */
	if ( settings.trace_eventlist == ON )
		fprintf( fp, "%strace_eventlist();\n", sp6);

	/* 3) Set up heap trace--if any */
	if ( settings.trace_heap == ON )
		fprintf( fp, "%sprint_heap();\n", sp6);

}


/* -------------------------------------------------------------------
   addInitialization

   Add code for Simpack initialization and model initialization.
	1) Initialize simpack as LINKED or HEAP
	2) Specify visual tracing
	3) Create facilities
	4) Create tokens to start model
	5) Create simulation loop based on RUN TIME
   ------------------------------------------------------------------- */
void addInitialization( fp )
	FILE *fp;  /* id of C code file */
{
	int          facilityCount = 1;
	int          tokenCount = 1;
	int          i;                 /* loop counter */



	/* Initialize Simpack */
	fprintf( fp, "\n\n   init_simpack(");
	switch (settings.mode)
	{
		case LINKED: fprintf( fp, "LINKED);\n");
			     break;
		case HEAP:   fprintf( fp, "HEAP);\n");
			     break;
		default:     fprintf( stderr, "Error in mode\n");
			     break;
	}
	/* Set up visual trace--if any */
	if ( settings.trace_visual != NONE )
	{
	   switch (settings.trace_visual)
	   {
	      case BATCH:       fprintf( fp, "   trace_visual(BATCH);\n");
				break;
	      case INTERACTIVE: fprintf( fp, "   trace_visual(INTERACTIVE);\n");
				break;
	      default:          fprintf( stderr, "Error in trace_visual\n");
				break;
	   }
	}

	/* Create each facility */
	fprintf( fp, "\n   /* Create Facilities */\n");
	for (i=1; i<= MAX_ELEMENTS; i++)
	{
		if( settings.facility[i].valid)
		{
			fprintf( fp, "   facility[%d] =", facilityCount++);
			fprintf( fp, " create_facility( \"%s\", %d);\n",
				settings.facility[i].nameStr,
				settings.facility[i].numServers);
		}
	}

	/* Schedule initial tokens */
	fprintf( fp, "\n   /* Schedule initial release of tokens */\n");

	/* Create a for loop for EACH group of tokens */
	for( i=1; i <=MAX_ELEMENTS; i++)
	{
		if( settings.arrival[i].valid)
		{

			fprintf( fp, "   for (i=%d; i<= %d; i++)\n",
				tokenCount, settings.arrival[i].initialCount
				+ tokenCount - 1);
			fprintf( fp, "   {\n");
/****************** OLD VERSION OF SIMPACK ***************************
			fprintf( fp, "%sschedule( 1,0.0, i );\n",sp6);
********************************************************************/
			fprintf( fp, "%stoken.attr[0] = (float) i;\n",sp6);
			fprintf( fp, "%sschedule( 1,0.0, token );\n",sp6);
/****************** REMOVED token data struct ************************
			fprintf( fp, "%stokenInfo[i].priority = %d;\n", sp6,
				settings.arrival[i].priority);
********************************************************************/

			fprintf( fp, "   }\n");

			/* Keep a running total of tokens created */
			tokenCount = settings.arrival[i].initialCount +
				tokenCount - 1;
		}
	}
	fprintf( fp, "   numTokens = %d;\n", tokenCount);

	/* if there is at least on generic block, call initGeneric() */
	if( genericBlock )
	{
		fprintf( fp, "   initGeneric();\n");
	}

	/* Create main loop--run simulation based on time */
	fprintf(fp, "\n   /* Specify simulation run time*/\n");
	fprintf(fp, "   while ( sim_time() <= %f )\n", settings.runTime);
	fprintf(fp, "   {\n");
	fprintf( fp,"%s/* Determine next event in simulation */\n",sp6);
	fprintf(fp, "%snext_event( &event, &token);\n",sp6);
	addTraceOptions( fp );
	fprintf(fp, "\n%s/* Process the event */\n",sp6);
	fprintf(fp, "%sswitch( event )\n",sp6);
	fprintf(fp, "%s{\n",sp6);

}

/* -------------------------------------------------------------------
   addArrival

   Add code to perform an arrival (the first case in the switch
   statement).
   ------------------------------------------------------------------- */
void addArrival( fp )
	FILE *fp;  /* id of C code file */
{
	int i;  /* loop counter */


	/* Start Case 1 */
	fprintf( fp, "%s/* Arrivals */\n",sp6);
	fprintf( fp, "%scase 1:\n",sp9);
	fprintf( fp, "%supdate_arrivals();\n",sp12);

	/* Schedule next arrival */
	/* This code must be modified to support multiple arrival
	   points. */
	if ( settings.departure == ABSORB )
	{
		fprintf( fp, "\n%s/* Schedule next arrival */\n",sp12);
		fprintf( fp, "%snextToken.attr[0] = (float) ++numTokens;\n",sp12);
		fprintf( fp, "%sschedule( 1,",sp12);
		addArrivalDistn( fp, 1);
		fprintf( fp, ", nextToken);\n");
	};

	fprintf( fp, "\n%s/* Schedule first resource */\n",sp12);

	/* Case statment will be finished by addRequestReleasePair */
}

/* -------------------------------------------------------------------
   addRequestReleasePair

   Add a "case" in the switch statement to request and release a
   particular facility.

   1) Finish previous case statement by scheduling the request event.
   2) Add "request case statement"
   3) Add release case statement (if needed)
   4) recursively call addToSwitch
   ------------------------------------------------------------------- */
void addRequestReleasePair( fp, id, caseNumber, lastElement)
	FILE *fp;         /* id of C file for Simpack model   */
	int id;           /* index in facility array          */
	int *caseNumber;  /* Case number for switch statement */
	int *lastElement; /* Last element added to C code     */
{
	int reqCaseNum,   /* Used because the request & release        */
	    relCaseNum;   /*   case numbers are not always consecutive */

	/* initialize case number if one has already been assigned */
	if ( settings.facility[id].caseNum != 0 )
	{
		reqCaseNum = settings.facility[id].caseNum;
		relCaseNum = (*caseNumber)++;
	}
	else
	{
		reqCaseNum = (*caseNumber)++;
		relCaseNum = (*caseNumber)++;
		settings.facility[id].caseNum = reqCaseNum;
	}

	/* 1) Finish off previous case statement */
	if ( *lastElement != FAN_OUT_RP )
	{
		/* Schedule arrival event of next facility */
		fprintf( fp, "%sschedule( %d, 0.0, token);\n",
			sp12, reqCaseNum);
		fprintf( fp, "%sbreak;\n",sp12);
	}


	/* have we written this element already ? */
	if ( settings.facility[id].written == TRUE)
	{
		return;  /*don't write it a second time */
	}
	else	
	{
		settings.facility[id].written = TRUE;
	}

	/* 2) Case for requesting server */
	fprintf( fp, "\n%s/* Request facility %s */\n", sp9,
		settings.facility[id].nameStr);
	fprintf( fp, "%scase %d:\n", sp9, reqCaseNum);
	fprintf( fp, "%sif (",sp12);

	if (settings.facility[id].typeRequest == REQUEST)
		fprintf( fp, "request");
	else if (settings.facility[id].typeRequest == PREEMPT)
		fprintf( fp, "preempt");
	else
		fprintf ( stderr, "ERROR: In AddRequestReleasePair\n");

	fprintf( fp, "\n%s(facility[%d], token, ", sp15, id);
	fprintf( fp, "priority) == FREE)\n");
	/* finish off request */
	fprintf( fp, "%s   schedule( %d, ", sp15, relCaseNum);
	addFacilityDistn( fp, id );
	fprintf( fp, ", token);\n");
	fprintf( fp, "%sbreak;\n",sp12);

	/* generate release case */
	fprintf( fp, "\n%s/* Release facility %s */\n", sp9,
			settings.facility[id].nameStr);
	fprintf( fp, "%scase %d:\n", sp9, relCaseNum);
	fprintf( fp, "%srelease( facility[%d], token);\n",sp12,id);

	*lastElement = FACILITY;
	addToSwitch( fp, settings.facility[id].out, caseNumber,
		lastElement);


}
/* -------------------------------------------------------------------
   addGeneric

   Generic blocks can have only 1 outgoing path.

	a) assign a case statement number to this generic block (an event)
	b) finish off last case statement (the release of a facility)
	c) create the case statement for this generic block
	d) create the case statement for the request and release of
		the facility that follows the routing point
    ------------------------------------------------------------------- */
void addGeneric( fp, ptr, caseNumber, lastElement )
	FILE *fp;        /* id of C file for Simpack model            */
	struct List *ptr;/* ptr to out of facility released last      */
	int *caseNumber; /* the next unused number in the switch stmt */
	int *lastElement;      /* last element added to C code        */
{
	struct List *tempPtr;  /* ptr to out list                     */

	/* give the generic block a case number */
	if (settings.generic[ptr->id].caseNum == 0)

		settings.generic[ptr->id].caseNum = (*caseNumber)++;


	/* Finish off last case statment  */
	if (*lastElement != FAN_OUT_RP)
	{
		fprintf( fp, "%sschedule( %d, 0.0, token);\n",
			sp12, settings.generic[ptr->id].caseNum);
		fprintf( fp, "%sbreak;\n",sp12);
	}

	/* have we written this element already ? */
	if ( settings.generic[ptr->id].written == TRUE)
	{
		return;  /*don't write it a second time */
	}
	else	
	{
		settings.generic[ptr->id].written = TRUE;
	}


	/* create generic block case statement */
	fprintf( fp, "\n%s/* Generic Block # %d */\n", sp9,
		ptr->id);
	fprintf( fp, "%scase %d:\n", sp9,
		settings.generic[ptr->id].caseNum);
	fprintf( fp, "%s/* Call external generic function */\n",sp12);
	fprintf( fp, "%s%s(&token);\n",sp12,
		settings.generic[ptr->id].nameStr );

	/* handle next element in model recursively */
	*lastElement = GENERIC;
	addToSwitch( fp, settings.generic[ptr->id].out, caseNumber,
		lastElement);
}

/* -------------------------------------------------------------------
   assignCase 

   Supporting routing for addFanOut.  Assigns case numbers if they
   are not assigned.
    ------------------------------------------------------------------- */
int assignCase( ptr, caseNumber)
	struct List *ptr;
	int *caseNumber; /* the next unused number in the switch stmt */
{
	int   caseN; 

   switch( ptr->elementType )
   {
      case FACILITY:
         if( settings.facility[ptr->id].caseNum == 0 )
            settings.facility[ptr->id].caseNum = (*caseNumber)++;
         caseN = settings.facility[ptr->id].caseNum;
         break;
    
      case FAN_OUT_RP:
      case FAN_IN_RP:

         if( settings.routing[ptr->id].caseNum == 0 )
            settings.routing[ptr->id].caseNum = (*caseNumber)++;
         caseN = settings.routing[ptr->id].caseNum;
         break;

      case GENERIC:
         if( settings.generic[ptr->id].caseNum == 0 )
            settings.generic[ptr->id].caseNum = (*caseNumber)++;
         caseN = settings.generic[ptr->id].caseNum;
         break;

      case SINK:
         if( settings.sinkCaseNum == 0 )
            caseN = settings.sinkCaseNum = (*caseNumber)++;
         break;

      default:
         fprintf(stderr, "ERROR in assignCase element type %d\n",ptr->elementType);
         caseN = 1;
    }
    return( caseN);
}


/* -------------------------------------------------------------------
   addFanOutRP

   FanOut routing points can have many outgoing paths.  However, since
   they only have ONE incoming path this procedure is only called once.

	a) assign a case statement number to this routing point (an event)
	b) finish off last case statement (the release of a facility)
	c) create the case statement for this routing point
	d) create the case statement for the request and release of
		the facility that follows the routing point
    ------------------------------------------------------------------- */
void addFanOutRP( fp, ptr, caseNumber, lastElement )
	FILE *fp;        /* id of C file for Simpack model            */
	struct List *ptr;/* ptr to out of facility released last      */
	int *caseNumber; /* the next unused number in the switch stmt */
	int *lastElement;      /* last element added to C code        */
{
	struct List *tempPtr;  /* ptr to out list                     */
	int     startCase,     /* case # of first arc in out list */
		stopCase;      /* case # of last arc in out list */
	int     count;         /* number of arcs in out list */


	/* give the routing point a case number */
	if (settings.routing[ptr->id].caseNum == 0)
		settings.routing[ptr->id].caseNum = (*caseNumber)++;


	/* Finish off last case statment  */
	if (*lastElement != FAN_OUT_RP)
	{
		fprintf( fp, "%sschedule( %d, 0.0, token);\n",
			sp12, settings.routing[ptr->id].caseNum);
		fprintf( fp, "%sbreak;\n",sp12);
	}

	/* have we already written this case statement ? */
	if( settings.routing[ptr->id].written == TRUE)
	{
		*lastElement = FAN_OUT_RP;
		return;  
	}

	/* write the case statment */
	settings.routing[ptr->id].written = TRUE;

	/* create routing point case statement */
	fprintf( fp, "\n%s/* Fork # %d */\n", sp9,
		ptr->id);
	fprintf( fp, "%scase %d:\n", sp9,
		settings.routing[ptr->id].caseNum);
	fprintf( fp, "%s/* Select the next facility */\n",sp12);

	/* Assign a case number for each facility or routing
   	point if its not already assigned */

	count = 0;
	tempPtr = settings.routing[ptr->id].out;
	if (tempPtr == NULL) {printf("ERROR in addFanOutRP\n"); return;}
	while ( tempPtr != NULL )
	{
		fprintf( fp,"%sweight[%d] = %4.2f;   arc[%d] = %d;\n", sp12,
			count, settings.routing[ptr->id].weight[count+1],
			count, assignCase(tempPtr, caseNumber) );
		tempPtr = tempPtr->next;
		count++;
	}
	fprintf(fp, "%snum = %d;\n",sp12,count);

	fprintf( fp, "%snextQ = ",sp12);
	addRoutingDistn( fp, ptr->id );
	fprintf ( fp, ";\n");

	/* Schedule request event of next facility */
	fprintf( fp, "%sschedule( nextQ, 0.0, token);\n",
		sp12, ptr->id);
	fprintf( fp, "%sbreak;\n",sp12);


	/* Do cases of all facilities in out list */
	tempPtr = settings.routing[ptr->id].out;
	while (tempPtr != NULL)
	{
		*lastElement = FAN_OUT_RP;
		if( tempPtr->elementType == SINK )
			addDepartureCaseForFanOut(fp);
		else
			addToSwitch( fp, tempPtr, caseNumber,lastElement);
		tempPtr = tempPtr->next;
	}


}

/* -------------------------------------------------------------------
   addFanInRP

   FanIn routing points can have many incoming paths.  This procedure
   is called once for each incoming path.  (This code assumes that
   incoming paths are ALWAYS facilities.)  Its possible a case
   statement has already been created for this routing point.

   1) There is already a case statement for this routing point.
	a) finish off last case statement (the release of a facility)
   2) There is NOT a case statement for this routing point.
	a) assign a case statement number to this routing point (an event)
	b) finish off last case statement (the release of a facility)
	c) create the case statement for this routing point
	d) create the case statement for the request and release of
		the facility that follows the routing point
    ------------------------------------------------------------------- */

void addFanInRP( fp, ptr, caseNumber, lastElement)
	FILE *fp;        /* id of C file for Simpack model */
	struct List *ptr;       /* ptr to out of facility released last */
	int *caseNumber; /* the next unused number in the switch stmt */
	int *lastElement; /* previous element add to C code */
{


	/* does the routing point have a case number already? */
	if ( settings.routing[ptr->id].caseNum == 0 )
	{
		/* give the routing point a case number */
		settings.routing[ptr->id].caseNum = *caseNumber;
		(*caseNumber)++;
	}

	/* have we written this routing point already ? */
	if ( settings.routing[ptr->id].written == FALSE )
	{
		settings.routing[ptr->id].written = TRUE;

		/* Finish off last case statement */
		if ( *lastElement != FAN_OUT_RP)
		{
			fprintf( fp, "%sschedule( %d, 0.0, token);\n",
				sp12, settings.routing[ptr->id].caseNum);
			fprintf( fp, "%sbreak;\n",sp12);
		}

		/* create routing point case statement */
		fprintf( fp, "\n%s/* Join # %d */\n", sp9, ptr->id);
		fprintf( fp, "%scase %d:\n", sp9, 
			settings.routing[ptr->id].caseNum);

		/* Finally, add cases for the request and release of
		   the next facility */
		*lastElement = FAN_IN_RP;
		addToSwitch( fp, settings.routing[ptr->id].out,
			caseNumber,lastElement);
	}
	else  /* routing point already has a case */
	{
		/* Finish off last case statement */
		if ( *lastElement !=FAN_OUT_RP)
		{
			fprintf( fp, "%sschedule( %d, 0.0, token);\n",
				sp12, settings.routing[ptr->id].caseNum);
			fprintf( fp, "%sbreak;\n",sp12);
		}
		*lastElement = FAN_IN_RP;

	}
}

/* -------------------------------------------------------------------
   addDepartureCase

   Finish off C code by adding code to the model's last case
   statement to absorb or recirculte tokens. Add closing }'s,
   and report_stats (if called for by user).

   ------------------------------------------------------------------- */
void addDepartureCase( fp )
	FILE *fp;        /* id of C file for Simpack model */
{

	fprintf( fp, "%supdate_completions();\n",sp12);

	/* Get rid of the token or reuse them? */
	if ( settings.departure == RECIRCULATE )
		fprintf( fp, "%sschedule(1, 0.0, token);\n",sp12);

	/* Close switch and C code file */
	fprintf( fp, "%sbreak;\n",sp12);

}


/* -------------------------------------------------------------------
   addDepartureCaseForFanOut

   Make a separate case statement for the departure (sink).  No
   need to finish last case statement sink we are coming from a 
   fanout. 

   ------------------------------------------------------------------- */
void addDepartureCaseForFanOut( fp )
	FILE *fp;        /* id of C file for Simpack model */
{

	/* create case statement */
	fprintf( fp, "\n%s/* Departure  */\n", sp9);
	fprintf( fp, "%scase %d:\n", sp9, settings.sinkCaseNum);
	fprintf( fp, "%supdate_completions();\n",sp12);

	/* Get rid of the token or reuse them? */
	if ( settings.departure == RECIRCULATE )
		fprintf( fp, "%sschedule(1, 0.0, token);\n",sp12);

	/* Close switch and C code file */
	fprintf( fp, "%sbreak;\n",sp12);
}


/* ------------------------------------------------------------------
   addToSwitch

   Add additional cases to the C program's main switch statement.

   Do a breadth-first search through the graph.  At each step, add a
   "case" to the switch statement that represents the facility or
   routing point.

   Since the graph may contain cycles, each case that is created must
   be recorded.  This is done with settings.facility[i].caseNum &
   settings.routing[i].caseNum.  They contain the event number (the
   "case" number in the switch statement) of their entity.

   Eventually, an out list will be empty.  This indicates the last
   entry in the graph.  addDeparture() finishs up the C code.

   The breadth first search is done recursively based on "ptr".
   ------------------------------------------------------------------- */
void addToSwitch( fp, ptr, caseNumber, lastElement )
	FILE *fp;         /* id of C program to be created               */
	struct List *ptr; /* ptr to out list of last element add to code */
	int *caseNumber;  /* next event to be added to switch statement  */
	int *lastElement; /* FACILITY, ARRIVAL, FAN_IN_RP or FAN_OUT_RP  */
{

	/* What's next?  Could be
		1) The departure point
		2) A fan-in routing point
		3) A fan-out routing point
		4) A facility
		5) A generic block
	   Note that facilities and fan-in routing points are always
	   linked to only ONE element.  Where as fan-out routing point
	   may be linked to multiple elements.       */


	/* Traverse the graph with a breadth first search. */
	if ( ptr->elementType == SINK )

		/* end of the road (and the code) */
		addDepartureCase( fp );

	 /* Is the next element a facility? */
	 else if ( ptr->elementType == FACILITY)
	 {
		addRequestReleasePair( fp, ptr->id, caseNumber,lastElement);
	 }

	 /* Is the next point a generic block */
	 else if (ptr->elementType == GENERIC)
	 {
		addGeneric( fp, ptr, caseNumber, lastElement);
	 }

	 /* Is the next point a FanIn routing point? */
	 else if (ptr->elementType == FAN_IN_RP)
	 {
		addFanInRP( fp, ptr, caseNumber, lastElement);
	 }
	 /* Is the next point a FanOut routing point? */
	 else if (ptr->elementType == FAN_OUT_RP)
	 {
		addFanOutRP( fp, ptr, caseNumber, lastElement);
	 }
	 /* Not a facility or a routing point == Error... */
	 else
	 {
		fprintf( stderr,"ERROR with elementType");
		fprintf( stderr, " in AddToSwitch\n");
		return;
	 }
}

/* -------------------------------------------------------------------
   addCumulative

   Add a procedure at the bottom of the code to generate a cumulative
   distribution.  (A discrete non-uniform distribution).
   ------------------------------------------------------------------- */
void addCumulative( fp )
	FILE *fp;  /* id of C code file */
{
   fprintf( fp, "/* ------------------------------------------------   \n");
   fprintf( fp, "   cumulative()\n\n");
   fprintf( fp, "   A discrete, non-uniform distribution used by forks.\n");
   fprintf( fp, "   It allows arcs to have weights.\n");
   fprintf( fp, "--------------------------------------------------- */\n");
   fprintf( fp, "int cumulative( weight, arc, num)\n");
   fprintf( fp, "%sfloat weight[];\n",sp3);
   fprintf( fp, "%sint   arc[];\n",sp3);
   fprintf( fp, "%sint   num;\n",sp3);
   fprintf( fp, "{\n");
   fprintf( fp, "%sint   index;\n",sp3);
   fprintf( fp, "%sint   i;\n",sp3);
   fprintf( fp, "%sfloat sample;\n\n",sp3);
   fprintf( fp, "%sfor( i=1; i <num; i++ )\n", sp3);
   fprintf( fp, "%sweight[i] += weight[i-1];   /* build distribution in input array */\n\n",sp6);
   fprintf( fp, "%ssample = uniform( 0.0, 1.0 );\n",sp3);
   fprintf( fp, "%sindex = 0;\n",sp3);
   fprintf( fp, "%swhile( weight[index] < sample )\n",sp3);
   fprintf( fp, "%sindex++;\n\n",sp6);
   fprintf( fp, "%sreturn( arc[index] );\n",sp3);
   fprintf( fp, "}\n");

}


/* ===================================================================
   CONTROLLING PROCEDURE FOR THIS FILE (THE "MAIN")
   =================================================================== */

/* ------------------------------------------------------------------
   generateCode

   Generate C code from the data structure "settings" (described in
   go.h).
   ------------------------------------------------------------------- */

void generateCode()
{
	FILE *fp;           /* id of C code file */
	char  nameStr[MAX_MODEL_NAME_SIZE];  /* name of C code file */
	char  msg[MAX_CHARS_IN_WINDOW];      /* error message */
	int   i=1;          /* loop counter */
	int   caseNumber=2; /* First number of events in switch stmt */
	int   lastElement=ARRIVAL; /* Previous element in graph */

	/* open file to write code */
	strcpy(nameStr, settings.fileName);
	strcat( nameStr, ".c");  /* make it a C file */
	if( access(nameStr, F_OK) == 0  &&
	    access(nameStr, W_OK) != 0  )
	{
		sprintf(msg, "Cannot write to file %s\n", nameStr);
		writeMessage(msg);
		return;
	}
	else
	{
		fp = fopen( nameStr, "w");
	}

	initGo();
	createStrSpaces();
	addComments( fp );
	addInitialization( fp );
	addArrival( fp );

	/* Assumes that there is only one arrival point.   This code
	would have to be changed for multiple arrival points */
	addToSwitch( fp, (struct List*) settings.arrival[1].out,
		&caseNumber, &lastElement);

	/* the end */
	fprintf( fp, "%s}\n",sp6);
	fprintf( fp, "   }\n");
	if (settings.report == ON) fprintf(fp, "   report_stats();\n");
	fprintf( fp, "}\n");
	addCumulative( fp );
	fclose( fp );

	sprintf(msg,"Code created and written to file %s", nameStr);
	writeMessage(msg);

}
