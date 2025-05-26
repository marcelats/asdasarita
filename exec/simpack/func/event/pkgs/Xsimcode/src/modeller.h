/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distrubuted for non-profit use.
***********************************************************************
**
**		Name/Date : modeller.h 12/1/91 22:02:58
**		Author    : Brian Harrington 
**		Purpose   : Header file for Xsimcode.  Included by most 
**                          Xsimcode files.
**		Files Used:
**		History   :
**                        :origin:  6/12/90
**
**********************************************************************
** sccs_id: @(#)modeller.h	1.21 12/1/91 22:02:58
**********************************************************************/

/* ================================================================
   LIBRARIES USED
   ================================================================ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Do Not Change Order of the next 4 Include Files */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>

#include <X11/Xaw/Command.h>
#include <X11/Xaw/Paned.h>
#include <X11/Shell.h>
#include <X11/cursorfont.h>

#include <X11/Xaw/MenuButton.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/Sme.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/Cardinals.h>
#include <X11/Xaw/Box.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/Dialog.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Form.h>


/* ================================================================
   TYPE DEFINITIONS
   ================================================================ */
/* typedef int Boolean; */

typedef float Real;

/* ================================================================
   ENUMERATED TYPES
   ================================================================ */
#define TRUE 1
#define FALSE 0

#define ON 2
#define OFF 3

#define LINKED 10
#define HEAP 11

#define NONE 20
#define INTERACTIVE 21
#define BATCH 22
#define FACILITY 23
#define EVENTLIST 24
#define HEAPTRACE 25
#define REMOVE 27

#define UNIFORM 30
#define RANDOM 31
#define EXPONENTIAL 32
#define NORMAL 33
#define ERLANG 34
#define HYPERX 35
#define TRIANGLE 36
#define CONSTANT 37
#define CUMULATIVE 38

#define REQUEST 40
#define PREEMPT 41

#define IN 50
#define OUT 51
#define ABSORB 52
#define RECIRCULATE 53

#define FAN_IN_RP 61
#define FAN_OUT_RP 62
#define ARRIVAL 63
#define GENERIC 64

#define FAN_IN 70
#define FAN_OUT 71

#define LOAD 80
#define SAVEAS 81
#define ADD 82
#define DELETE 83
#define EDIT 84
#define CONNECT 85
#define NON_PAD 86

#define SOURCE 90
#define SINK 91
#define BLANK 92

#define WAIT 100
#define WAIT_FIRST_PT 101
#define WAIT_SECOND_PT 102
#define WAIT_FIRST_PT_UNLINK 103
#define WAIT_SECOND_PT_UNLINK 104
#define LINK 103
#define UNLINK 104


/* ================================================================
   CONSTANTS
   ================================================================ */
#define MAX_ARGS 50
#define MAX_CHARS_IN_WINDOW 80
#define MAX_ERROR_MSG 80
#define MAX_WEIGHTS 10
#define INT_STR 8
#define PAD_H_SIZE 600
#define PAD_V_SIZE 900
#define BUTTON_H_SIZE 60
#define BUTTON_V_SIZE 60
#define DIALOG_HEIGHT 150
#define DIALOG_WIDTH 200
#define DIALOG_POS_X 10     /* x,y position of dialog box in pad window */
#define DIALOG_POS_Y 10
#define DIALOG_POS_X_2 30   /* x,y position of 2nd dialog box in pad window */
#define DIALOG_POS_Y_2 30
#define OFFSET 20
#define MAX_DIALOG_WIDTH 40
#define ICON_SIZE 60        /* Icons are square */
#define WIDTH_ICON 50
#define HEIGTH_ICON 50
#define PAD_ROWS PAD_H_SIZE/ICON_SIZE+1
#define PAD_COLUMNS PAD_V_SIZE/ICON_SIZE+1
#define SRC_X 5                        /* location of source */
#define SRC_Y 1 
#define SINK_I 5                         /* location of sink */
#define SINK_J 15
#define DELAY 6
#define FULL_CIRCLE (360*64)
#define START_CIRCLE 0

#define MAX_INFO 1000
#define MAX_UNIX_NAME 100


#define EV_MASK (ButtonPressMask | \
                 ExposureMask )

#define MAX_FACILITY_NAME_SIZE 20
#define MAX_MODEL_NAME_SIZE 200
#define MAX_TOKENS 1000
#define MAX_ELEMENTS 50

#define END_LIST -1
#define END_SECTION -2

/* ================================================================
   ERROR MESSAGES
   ================================================================ */
#define NO_ERR 10
#define ERR_OPEN_FILE_FOR_WRITE 11
#define ERR_OPEN_FILE_FOR_READ 12

/* ================================================================
   GLOBAL DATA STRUCTURES
   ================================================================ */
/* the current cursor */
enum { XS_DEFAULT, XS_KILL, XS_DRAW, XS_BUSY } CurrentCursor; 
/* A linked list is used to keep track of all the input and output
   points for facilities, routing points and arrivals. */

struct List
{
	int elementType,    /* FACILITY OR ROUTING_POINT */
	    id;             /* Array index */
	struct List *next;  /* Next element in list */
        int i,j;            /* padElements[][] indices for 
                               out lists elements */
};


/* Data structure that links the graphical "pad" to the
   data structure "settings".  The pad is divided into a grid.
   Each spot on the grid is a position in padElement[][].  */
struct padStruct
{
        Boolean valid;      /* TRUE if element is in use */

	int elementType,    /* FACILITY OR ROUTING_POINT */
	    id;             /* Array index */

} padElement[ PAD_ROWS][PAD_COLUMNS];


/*  position of object in padElement[][] array */
struct PositionStruct
{
	int i,j;  /* indices in padElement[][] */
	int x,y;  /* corresponding pixel location in pad */
        int type; /* #define switch used for distribution &
                      parameter number */
};


/* Main data structure.  Contains all info about the model. */
struct Settings
{

	/* model parameters */
	char    fileName[MAX_MODEL_NAME_SIZE];
	float   runTime;         /* Length of time to run simulation */

	int     mode,            /* HEAP or LINKED */
		trace_visual,    /* BATCH or INTERACTIVE or NONE */
		trace_facility,  /* ON or OFF      */
		trace_eventlist, /* ON or OFF      */
		trace_heap,      /* ON or OFF      */

		departure,       /* ABSORB or RECIRCULATE */
		numFacilities,   /* Number of facilites used by model */
		numRoutingPoints, /* Number of routing points used by model */
		numGenericPoints, /* Number of generic points used by model */
		report,          /* report_stats: ON or OFF  */

		sinkCaseNum;	/* case number for sink */

	struct List *fac_num;    /* list of facility numbers to trace */


	/* Data structure for each facility in the model */
	struct
	{

		Boolean valid;        /* TRUE if this record is in use */
		char    nameStr[MAX_FACILITY_NAME_SIZE];  /* facility name*/
		struct List*   out;   /* list of places tokens go to     */
		Boolean	written;      /* TRUE if this record's case stmt 
					 has been written            */

		int     caseNum;      /* Event number used in switch */
		int     numServers,
			typeRequest,  /* Request or Preempty THIS facility */
			distn;        /* type of prob distribution  */
		float   param1,       /* parameters of probability  */
			param2,       /*   distribution             */
			param3;

	} facility[MAX_ELEMENTS+1];

	/* Data structure for each generic block in the model */
	struct
	{
		Boolean valid;        /* TRUE if this record is in use */
		char    nameStr[MAX_FACILITY_NAME_SIZE];  /* function name*/
		int     caseNum;      /* Event number used in switch */
		struct List*   out;   /* list of places tokens go to     */
		Boolean	written;      /* TRUE if this record's case stmt 
					 has been written            */

	} generic[MAX_ELEMENTS+1];

	/* Data structure for each arrival point in the model */
	struct
	{
		Boolean valid;        /* TRUE if this record is in use */
		struct List*   out;   /* list of places tokens go to */

		int     priority,     /* token priority level       */
			initialCount, /* start model with this many */
			distn;        /* type of prob distribution  */
		float   param1,       /* parameters of probability  */
			param2,       /*   distribution             */
			param3;
	}arrival[MAX_ELEMENTS+1];

	/* Data structure for each routing point in the model */
	struct
	{
		Boolean valid;        /* TRUE if this record is in use   */
		struct List*   out;   /* list of places tokens go to */
		Boolean	written;      /* TRUE if this record's case stmt 
					 has been written            */
		int     caseNum;      /* Event number used in switch */
		int     distn;        /* type of prob distribution   */

		/* parameters of probability  distribution */
		float   weight[MAX_WEIGHTS+1];  /* 0 is unused */

	}routing[MAX_ELEMENTS+1];
};
