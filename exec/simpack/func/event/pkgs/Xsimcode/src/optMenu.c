/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : optMenu.c 12/1/91 22:02:40
**		Author    : Brian Harrington 
**		Purpose   : 
**		Files Used:
**		History   :
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)optMenu.c	1.21 12/1/91 22:02:40";
#endif /* lint */

/*

   optMenu.c

   Brian Harrington
   origin:   8/22/90
   version:  1/ 5/91

   changes since 1.0
   1/5  added cancel option to trace data struct

   -------------------------------------------------------------------

   Procedures to generate option menus on user's pad.

   The following options are supported.  (These are options which
   affect the C code that is generated.  They are SimPack options.)
	FILENAME: change the filename for the C code
	RUNTIME:  length of time model should run
	DEPARTURE: determines how tokens leave the system
		ABSORB - tokens leave the system when they reach the sink
		RECIRCULATE - tokens never leave the system
			when they reach the sink, they are rerouted to
			the source
	MODE:  determines data structure used to represent event list.
		HEAP - heap
		LINKED - linked list
	Data Struct Trace: dynamically display all data structures
		INTERACTIVE - display on screen
		BATCH - output sent to a file
	Event List: visually trace eventlist
		ON or OFF
		setting depends on mode
			if mode = LINKED then LINKTRACE
			if mode = HEAP   then HEAPTRACE
	Facility Trace - trace facility queue
	REPORT: display statistics after running model
		ON or OFF

*/

#include "modeller.h"

/* ================================================================
   EXTERNAL PROCEDURES 
   ================================================================ */
extern void quitX( char *);
extern void writeMessage( char *);
extern void DestroyPopupPrompt( Widget, XtPointer, XtPointer);
extern void addToList( struct List **, struct List *);
extern void findElement( struct List *, int, struct List **,
			 struct List **);
extern void removeFromList( struct List **, struct List *,
			 struct List *);
extern struct List *new();


/* ================================================================
   EXTERNAL GLOBAL VARIABLES
   ================================================================ */
extern Display     *theDisplay;
extern Window       padWindow;  /* Window id of pad widget */
extern GC           theGC;      /* X's graphics context id */
extern XtAppContext appCon;
extern Widget topLevel, pad, commands, fileMenuButton;
extern Widget optMenuButton;    /* Options Menu button */
extern struct Settings settings;
extern XtActionsRec actionTable;
extern Pixmap optionMenuButtonPattern;

/* ================================================================
   PROTOTYPES
   ================================================================ */
void fileNameReturn (Widget, XEvent*, String *, Cardinal* );
void runTimeReturn  (Widget, XEvent*, String*, Cardinal*);
void changeFacReturn (Widget, XEvent*, String*, Cardinal*);
void changeFileName( Widget,  XtPointer, XtPointer );
void changeRunTime ( Widget,  XtPointer, XtPointer );
void changeTraceFacilityList( Widget,  XtPointer, XtPointer );


/* ================================================================
   GLOBAL VARIABLES
   ================================================================ */

   /* For dialog boxes -- handles return key */
   XtActionsRec actionTableOptMenu[] = 
   {
       {"fileNameReturn",	fileNameReturn},
       {"runTimeReturn",	runTimeReturn},
       {"changeFacReturn",	changeFacReturn}
   };


/* ================================================================
   CALLBACK PROCEDURES 
   ================================================================ */
/* ----------------------------------------------------------------
    fileNameReturn

    Callback procedure.  Called by pressing return in dialog box.
    Calls changeFileName.
    --------------------------------------------------------------- */

void fileNameReturn(widget, event, params, num_params)
    Widget widget;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    Widget dialog = XtParent(widget);
    changeFileName(widget, (XtPointer) dialog, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    changeFileName

    Callback procedure.  Called by clicking "OK" on dialog box or
    by pressing return in dialog box for File Name option.  Gets
    file name from the user and changes the name in settings.

    client_data is the widget id of the dialog box
    --------------------------------------------------------------- */
void changeFileName(w, client_data, call_data)
    Widget      w;                      /* "SAVE AS" widget */
    XtPointer   client_data, call_data;
{

    Widget dialog,     /* dialog box                    */
	   popup;      /* Widget that contains the dialog box */
    String fileName;   /* input from user */

    /* Get file name */
    dialog = (Widget) client_data;
    fileName =  XawDialogGetValueString(dialog);

    strcpy( settings.fileName, fileName);
    writeMessage("File name changed");

    /* Get rid of popup & dialog box, restore screen */
    popup = XtParent( (Widget) client_data);
    XtDestroyWidget(popup);
}

/* ----------------------------------------------------------------
    fileNameChoice

    Called by File Name entry on Option menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    enter a new file name.

    client_data is unused
    --------------------------------------------------------------- */
void fileNameChoice(w, client_data, call_data)
    Widget	w;		        /* "SAVE AS" widget */
    XtPointer   client_data, call_data;	
{

    Position   x,y;    /* position of dialog box        */
    Arg         argList[MAX_ARGS];   /* resource list   */
    int        n;      /* arg list                      */
    Widget dialog,     /* dialog box                    */
           popup;      /* Widget that contains the dialog box */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("fileNamePrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter new file name");
    n++;
    XtSetArg( argList[n],XtNvalue, settings.fileName);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "OK", changeFileName, (XtPointer) dialog);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}


/* ----------------------------------------------------------------
    runTimeReturn

    Callback procedure.  Called by pressing return in dialog box.
    Calls changeRunTime.
    --------------------------------------------------------------- */
void runTimeReturn(widget, event, params, num_params)
    Widget widget;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    Widget dialog = XtParent(widget);
    changeRunTime(widget, (XtPointer) dialog, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    changeRunTime

    Callback procedure.  Called by clicking "OK" on dialog box or
    by pressing return in dialog box for Run Time option.  Gets
    the new run time from the user and changes it in settings.

    client_data is the widget id of the dialog box
    --------------------------------------------------------------- */
void changeRunTime(w, client_data, call_data)
    Widget      w;                      /* "File Name" widget */
    XtPointer   client_data, call_data;
{

    Widget dialog,     /* dialog box                    */
	   popup;      /* Widget that contains the dialog box */
    String runTimeStr; /* input from user as a string */
    Real   newRunTime; /* input from user as a float */

    /* Get run time */
    dialog = (Widget) client_data;
    runTimeStr = XawDialogGetValueString(dialog);

    if ( sscanf( runTimeStr, "%f", &newRunTime) == 0)

	/* an illegal value has been entered */
	writeMessage("I don't understand.  Please re-enter the run time.");

    else
    {
	settings.runTime = newRunTime;
	writeMessage("Run-time changed");

	/* Get rid of popup & dialog box, restore screen */
	popup = XtParent( (Widget) client_data);
	XtDestroyWidget(popup);
    }
}

/* ----------------------------------------------------------------
    runTimeChoice

    Called by Run Time entry on Option menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    enter a new run time for the model.

    client_data is unused
    --------------------------------------------------------------- */
void runTimeChoice(w, client_data, call_data)
    Widget      w;                      /* "Run Time" widget */
    XtPointer   client_data, call_data;
{

   Position  x,y;     /* pixel position of upper left hand corner */ 
   Widget dialog,     /* dialog box                    */
	   popup;     /* Widget that contains the dialog box */
   int         n;     /* number of args */
   Arg      argList[MAX_ARGS];  /* arguement list */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("runTimePrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter the new run time");
    n++;
    XtSetArg( argList[n],XtNvalue, "");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "OK", changeRunTime, (XtPointer) dialog);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeDeparture

    Callback procedure.  Called by selecting either "Absorb" or
    "Recirculate" on the departure menu (which is part of the
    options menu).  Changes the departure type in settings.

    client_data is the new setting.
    --------------------------------------------------------------- */
void changeDeparture(w, client_data, call_data)
    Widget      w;                      /* "File Name" widget */
    XtPointer   client_data, call_data;
{
    int mode;

    /* change selected mode */
    settings.departure = (int) client_data;

    if ( settings.departure == ABSORB )
	writeMessage("Changed departure type to Absorb");
    else if ( settings.departure == RECIRCULATE )
	writeMessage("Changed departure type to Recirculate");

    /* Get rid of popup & dialog box, restore screen */
    XtDestroyWidget(XtParent(XtParent(w)));
}


/* ----------------------------------------------------------------
    departureChoice

    Called by departure on option menu.

    Callback procedure.  Asks user to select "ABSORB" or "RECIRCULATE".

    client_data unused
    --------------------------------------------------------------- */
void departureChoice(parent,client_data, call_data)
    Widget	parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg         argList[MAX_ARGS];  /* argument list          */
    Position    x, y;               /* pixel position of upper left corner */
    int         n;                  /* number of args         */
    Widget dialog,     /* dialog box                          */
	   popup;      /* Widget that contains the dialog box */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);


    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Select choice for Departure mode");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add buttons */
    XawDialogAddButton(dialog, "Absorb", changeDeparture,
					(XtPointer) ABSORB);
    XawDialogAddButton(dialog, "Recirculate", changeDeparture,
					(XtPointer) RECIRCULATE);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,
					(XtPointer) dialog);
    XtPopup(popup, XtGrabNone);
}


/* ----------------------------------------------------------------
    changeMode

    Callback procedure.  Called by selecting either "Heap" or "Linked
    List" from the mode menu (which is part of the options menu).
    Changes the mode in settings.

    client_data is the new setting.
    --------------------------------------------------------------- */
void changeMode(w, client_data, call_data)
    Widget      w;                      /* "File Name" widget */
    XtPointer   client_data, call_data;
{

    /* change selected mode */
    settings.mode = (int) client_data;
    if ( settings.mode == HEAP )
	writeMessage("Changed mode to heap");
    else if ( settings.mode == LINKED )
	writeMessage("Changed mode to linked list");

    /* Get rid of popup & dialog box, restore screen */
    XtDestroyWidget(XtParent( XtParent(w) ));
}


/* ----------------------------------------------------------------
    modeChoice

    Called by mode on option menu.

    Callback procedure.  Asks user to select "HEAP" or "LINKED LIST".

    client_data unused
    --------------------------------------------------------------- */
void modeChoice(parent,client_data, call_data)
    Widget      parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg         argList[MAX_ARGS];  /* argument list          */
    Position    x, y;               /* pixel position of upper left corner */
    int         n;                  /* number of args         */
    Widget dialog,     /* dialog box                          */
	   popup;      /* Widget that contains the dialog box */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel,"Please select an event list data structure");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "Heap", changeMode,
					(XtPointer) HEAP);
    XawDialogAddButton(dialog, "Linked List", changeMode,
					(XtPointer) LINKED);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,
					(XtPointer) dialog);
    XtPopup(popup, XtGrabNone);

}

/* ----------------------------------------------------------------
    changeReport

    Callback procedure.  Called by selecting either "On" or "Off"
    from the report menu (which is part of the options menu).
    Changes the report mode in settings.

    client_data is the new setting.
    --------------------------------------------------------------- */
void changeReport(w, client_data, call_data)
    Widget      w;                      /* "File Name" widget */
    XtPointer   client_data, call_data;
{

    /* change selected mode */
    settings.report = (int) client_data;
    if ( settings.report == ON )
	writeMessage("Changed report mode to On");
    else if ( settings.report == OFF )
	writeMessage("Changed report mode to Off");

    /* Get rid of popup & dialog box, restore screen */
    XtDestroyWidget(XtParent( XtParent(w) ));

}


/* ----------------------------------------------------------------
    reportChoice

    Called by report on option menu.

    Callback procedure.  Asks user to select "ON" or "OFF".

    client_data unused
    --------------------------------------------------------------- */
void reportChoice(parent,client_data, call_data)
    Widget      parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg         argList[MAX_ARGS];  /* argument list          */
    Position    x, y;               /* pixel position of upper left corner */
    int         n;                  /* number of args         */
    Widget dialog,     /* dialog box                          */
	   popup;      /* Widget that contains the dialog box */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Select choice for Report mode");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "On", changeReport,
					(XtPointer) ON);
    XawDialogAddButton(dialog, "Off", changeReport,
					(XtPointer) OFF);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,
					(XtPointer) dialog);
    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeTraceData

    Callback procedure.  Called by selecting either "INTERACTIVE",
    "BATCH" or "NONE" from the trace entry on the options menu.
    Changes the trace mode for the data structures.

    client_data is the new setting.
    --------------------------------------------------------------- */
void changeTraceData(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    Widget popup;   /* menu */
    int mode;


    /* change selected mode */
    mode = (int) client_data;
    settings.trace_visual = mode;
    if      ( mode == NONE )
	writeMessage("Turned off data structures trace");
    else if ( mode == INTERACTIVE )
	writeMessage("Data structures will be displayed on the screen");
    else if ( mode == BATCH )
	writeMessage("Data structure display will be sent to a file");

    /* Get rid of popup & dialog box, restore screen */
    popup = XtParent( XtParent(w) );
    XtDestroyWidget(popup);
}


/* ----------------------------------------------------------------
    traceDataChoice

    Called by trace data structures on option menu.

    Callback procedure.  Asks user to select "INTERACTIVE", "BATCH",
    or "NONE".

    client_data unused
    --------------------------------------------------------------- */
void traceDataChoice(parent,client_data, call_data)
    Widget      parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg         argList[MAX_ARGS];  /* argument list          */
    Position    x, y;               /* pixel position of upper left corner */
    int         n;                  /* number of args         */
    Widget dialog,     /* dialog box                          */
	   popup;      /* Widget that contains the dialog box */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel,
	"Please select a trace mode for the data structures");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 3buttons */
    XawDialogAddButton(dialog, "Interactive", changeTraceData,
					(XtPointer) INTERACTIVE);
    XawDialogAddButton(dialog, "Batch", changeTraceData,
					(XtPointer) BATCH);
    XawDialogAddButton(dialog, "None", changeTraceData,
					(XtPointer) NONE);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,
					(XtPointer) dialog);
    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeTraceEvent

    Callback procedure.  Called by selecting either "ON" or "OFF"
    from the trace event on the options menu.  If ON is selected
    and HEAP mode is in use then trace_heap is set.  If LINKED
    mode is in use the trace_eventlist is set.

    client_data is the new setting (ON or OFF).
    --------------------------------------------------------------- */
void changeTraceEvent(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int mode;


    /* change selected mode */
    mode = (int) client_data;

    if ( mode == ON )
    {
	if ( settings.mode == HEAP )
	{
		settings.trace_heap = ON;
		settings.trace_eventlist = OFF;
	}
	else /* settings.mode == LINKED */
	{
		settings.trace_heap = OFF;
		settings.trace_eventlist = ON;
	}
	writeMessage("The event list will be displayed");
    }
    else /* mode == OFF */
    {
	 settings.trace_heap = OFF;
	 settings.trace_eventlist = OFF;
	 writeMessage("The event list will not be displayed");
    }

    /* get rid of popup menu */
    XtDestroyWidget(XtParent( XtParent(w) ));
}

/* ----------------------------------------------------------------
    traceEventChoice

    Called by trace event on option menu.

    Callback procedure.  Asks user to select "ON" or "OFF".

    client_data is unused
    --------------------------------------------------------------- */
void traceEventChoice(parent,client_data, call_data)
    Widget      parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg         argList[MAX_ARGS];  /* argument list          */
    Position    x, y;               /* pixel position of upper left corner */
    int         n;                  /* number of args         */
    Widget dialog,     /* dialog box                          */
	   popup;      /* Widget that contains the dialog box */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel,
	"Please select a trace mode for the event list");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 3 buttons */
    XawDialogAddButton(dialog, "On", changeTraceEvent,
					(XtPointer) ON);
    XawDialogAddButton(dialog, "Off", changeTraceEvent,
					(XtPointer) OFF);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,
					(XtPointer) dialog);
    XtPopup(popup, XtGrabNone);
}
/* ----------------------------------------------------------------
    changeFacReturn

    Callback procedure.  Called by pressing return in dialog box.
    --------------------------------------------------------------- */
void changeFacReturn(widget, event, params, num_params)
    Widget widget;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    /* do nothing -- User MUST press either add or remove */
    writeMessage("Please select either ADD, REMOVE or CANCEL");
}

/* ----------------------------------------------------------------
    changeTraceFacilityList

    Callback procedure.  Called by selecting "DONE" or by
    pressing return in the second dialog box under the trace
    facility entry of the options menu.

    Adds or removes a facility number from the list of facilities
    to be traced.

    client_data is either ADD or REMOVE
    --------------------------------------------------------------- */
void changeTraceFacilityList(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    Widget popup,dialog;   /* id of dialog box widgets */
    String facilityNumStr; /* User input as a string */
    int    facilityNum;    /* User input as an int   */
    struct List *ptr;      /* new element in facility list */
    struct List *prevElem; /* previous element in facility list */

    /* Get facility number */
    facilityNumStr = XawDialogGetValueString(XtParent(w));

    if ( sscanf( facilityNumStr, "%d", &facilityNum) == 0)

	/* an illegal value has been entered */
	writeMessage(
		"I don't understand.  Please re-enter the facility number.");

    else if ( (int) client_data == ADD )
    {
	/* add a facility to the list */
	ptr = new();
	ptr->id = facilityNum;
	addToList( &(settings.fac_num), ptr );
	settings.trace_facility = ON;
	writeMessage("Facility added to trace list");
    }
    else /*  (int) client_data == REMOVE ) */
    {

      findElement( settings.fac_num, facilityNum, &ptr, &prevElem);
	if ( ptr == NULL )
		writeMessage("That facility number is not in the list");
	else
	{
		removeFromList( &(settings.fac_num), ptr, prevElem );
		writeMessage("Facility remove from trace list");
	}
    }

    /* Get rid of popup & dialog box, restore screen */
    XtDestroyWidget(XtParent(XtParent(w)));
}

/* ----------------------------------------------------------------
    traceFacilityChoice

    Called by trace facility on option menu.

    Callback procedure.  Asks user to select "ADD" or "REMOVE".

    client_data is unused
    --------------------------------------------------------------- */
void traceFacilityChoice(parent,client_data, call_data)
    Widget      parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg         argList[MAX_ARGS];  /* argument list          */
    Position    x, y;               /* pixel position of upper left corner */
    int         n;                  /* number of args         */
    Widget dialog,     /* dialog box                          */
	   popup;      /* Widget that contains the dialog box */

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         n++;
    XtSetArg(argList[n], XtNy, y);                         n++;
    popup = XtCreatePopupShell("changeFacPrompt", transientShellWidgetClass, 
                                   pad, argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel,
	"Enter facility to add or remove from the list of facilities to be traced.");
    n++;
    XtSetArg( argList[n],XtNvalue, "");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 3 buttons */
    XawDialogAddButton(dialog, "Add", changeTraceFacilityList,
					(XtPointer) ADD);
    XawDialogAddButton(dialog, "Remove", changeTraceFacilityList,
					(XtPointer) REMOVE);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,
					(XtPointer) dialog);
    XtPopup(popup, XtGrabNone);
}

/* ================================================================
   "MAIN"
   ================================================================ */

/* ----------------------------------------------------------------
    createOptMenu

    Create option menu tree.
    --------------------------------------------------------------- */

void createOptMenu()
{
    Arg          argList[MAX_ARGS];    /* resource list   */            
    Widget       optPulldownMenu,       
                 entry;
    int          i,n;                  /* counters */

    
    char *menu_item_names[] =
    {
	"File Name", "Run Time",  "Departure", "Mode", "Report",
	"Trace Data Struct", "Trace Event List", "Trace Facility",
    };

    XtAppAddActions(appCon, actionTableOptMenu, XtNumber(actionTableOptMenu));

    /* Create option menu button */
    n=0;
    XtSetArg( argList[n], XtNfromHoriz, fileMenuButton);
    n++;
    XtSetArg( argList[n], XtNheight, BUTTON_H_SIZE);
    n++;
    XtSetArg( argList[n], XtNwidth, BUTTON_V_SIZE);
    n++;
    XtSetArg( argList[n], XtNmenuName, "optionsMenu");
    n++;

    optMenuButton = XtCreateManagedWidget("Options",
         menuButtonWidgetClass, commands, argList, n);
    
    optPulldownMenu = XtCreatePopupShell("optionsMenu", simpleMenuWidgetClass, 
         optMenuButton, NULL, ZERO);
    
    for (i = 0; i < (int) XtNumber(menu_item_names) ; i++) 
    {
	char * item = menu_item_names[i];
	entry = XtCreateManagedWidget(item, smeBSBObjectClass, optPulldownMenu,
				      NULL, ZERO);

	/* these procedures are called when one of the menu entries
	   is selected */
	if      ( item == "File Name" )
		XtAddCallback(entry, XtNcallback, fileNameChoice, NULL);
	else if ( item == "Run Time" )
		XtAddCallback(entry, XtNcallback, runTimeChoice, NULL);
	else if ( item == "Departure" )
		XtAddCallback(entry, XtNcallback, departureChoice, NULL);
	else if ( item == "Mode" )
		XtAddCallback(entry, XtNcallback, modeChoice, NULL);
	else if ( item == "Report" )
		XtAddCallback(entry, XtNcallback, reportChoice, NULL);
	else if ( item == "Trace Data Struct" )
	        XtAddCallback(entry, XtNcallback, traceDataChoice, NULL);
	else if ( item == "Trace Event List" )
		XtAddCallback(entry, XtNcallback, traceEventChoice, NULL);
	else if ( item == "Trace Facility" )
		XtAddCallback(entry, XtNcallback, traceFacilityChoice, NULL);

    }
}

