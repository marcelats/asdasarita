/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : padMenu.c 12/1/91 22:02:43
**		Author    : Brian Harrington 
**		Purpose   : 
   Procedures for menu on the user's pad.  Allows user to add/edit/
   delete a facility, routing point or the arrival point.
**		Files Used:
**		History   :
**

   origin:   9/22/90 
   changes since ver1
   1/5 support for using return in dialog boxes 
   3/3 add info option for elements
   3/17 add generic block
   6/22 fix bugs for generic block	
   10/5 shrunk menus 
   10/28 changed terms;  "arrival"-> "source"; "fan-in"->"join";
              "fan-out"->"fork"
   10/31 fixed bug that did not allow fork's to have a distribution
   11/3  added cumulative distribution to forks

**********************************************************************/

#ifndef lint 
        static char sccs_id[] = "@(#)padMenu.c	1.21 12/1/91 22:02:43";
#endif /* lint */
   


#include "modeller.h"

/* ================================================================
   EXTERNAL GLOBAL VARIABLES
   ================================================================ */
extern char debug;
extern Widget pad;
extern struct Settings settings;
extern XtAppContext appCon;               
/*
extern Widget AddToggle, EditToggle;
*/
/* ================================================================
   EXTERNAL PROCEDURES
   ================================================================ */
extern void DestroyPopupPrompt( Widget, XtPointer, XtPointer );
extern void convertXYtoPad( int, int, int*, int*);
extern void convertPadtoIcon( int, int, int*, int*);
extern void quitX(char *);
extern void findElement( struct List *, int, struct List **,
				struct List **);
extern void findElementByType( struct List *, int, int, 
                                 struct List **,struct List **);
extern void removeFromList( struct List **, struct List *,struct List *);
extern void displayPixmap(int,int,int);
extern void quitX(char *);
/*
extern void createAddToggle();
extern void createEditToggle();
extern void destroyToggle(Widget);
*/
/* ===================================================================
   PROTOTYPES
   =================================================================== */
void changeName(Widget,XtPointer,XtPointer);
void changeServers(Widget,XtPointer,XtPointer);
void changeParam(Widget,XtPointer,XtPointer);
void changeCount(Widget,XtPointer,XtPointer);
void changePriority(Widget,XtPointer,XtPointer);
void changeFunction(Widget,XtPointer,XtPointer);
void nameReturn(Widget, XEvent *,String *,Cardinal *);
void serverReturn(Widget, XEvent *,String *,Cardinal *);
void paramReturn(Widget, XEvent *,String *,Cardinal *);
void countReturn(Widget, XEvent *,String *,Cardinal *);
void priorityReturn(Widget, XEvent *,String *,Cardinal *);
void functionReturn(Widget, XEvent *,String *,Cardinal *);


/* ================================================================
   GLOBAL VARIABLES
   ================================================================ */

   /* For dialog boxes -- handles return key */
   XtActionsRec actionTablePadMenu[] = 
   {
       {"nameReturn",	        nameReturn},
       {"serverReturn",	        serverReturn},
       {"paramReturn",	        paramReturn},
       {"countReturn",	        countReturn},
       {"priorityReturn",	priorityReturn},
       {"functionReturn",	functionReturn}
   };

   /* Indices in padElements where mouse click took place.
      Must be global since procedures like nameReturn (action 
      table procedures) don't have access to location */
    struct PositionStruct *locationGlobal;


/* ===================================================================
   INTERNAL PROCEDURES
   =================================================================== */
void changeName(Widget,XtPointer,XtPointer);


/* ----------------------------------------------------------------
    delOutListEntries

    Search ALL out lists and eliminate any entries for this element.
    --------------------------------------------------------------- */
void delOutListEntries( element, i )
   int element,   /* ARRIVAL, FAN_IN_RP, FAN_OUT_RP, or FACILILTY */
       i;         /* array index */
{
    struct List *elem, *prevElem;   /* temp ptrs */
    int j;                          /* loop counter */

    elem = NULL;
    prevElem = NULL;   /* initialize */

    /* Look for the element in each possible out list */
    /* If its found, delete it */

    /* check arrival out list */
    findElementByType( settings.arrival[1].out, element,i, 
                              &elem, &prevElem);
    if ( elem != NULL )
	removeFromList( &(settings.arrival[1].out), elem, prevElem);

    /* check facility out lists */
    for (j = 1; j< MAX_ELEMENTS; j++)
	if ( settings.facility[j].valid )
	{
	   findElementByType( settings.facility[j].out, element,i,
				&elem, &prevElem);
	   if ( elem != NULL )
		removeFromList( &(settings.facility[j].out),
				   elem, prevElem);
	}

    /* check routing point out lists */
    for (j = 1; j< MAX_ELEMENTS; j++)
	if ( settings.routing[j].valid )
	{
printf("out list before deletion\n");
printList( settings.routing[j].out );
	   findElementByType( settings.routing[j].out, element,i,
				&elem, &prevElem);
	   if ( elem != NULL )
{
printf("found an element to delete %d\n",elem->id);
if( prevElem == NULL ) printf( "prevElem is NULL\n");
		removeFromList( &(settings.routing[j].out),
				   elem, prevElem);
printf("out list after deletion\n");
printList( settings.routing[j].out );
}
	}

}


/* ===================================================================
   CALLBACK PROCEDURES FOR ADD
   =================================================================== */

/* ----------------------------------------------------------------
    addFacility

    Called by selecting Facility on ADD menu.

    Callback procedure.  Displays bitmap for facility.  Set-ups
    data structure for facility with default settings.

    client_data is i,j index of padElement[][]
    --------------------------------------------------------------- */
void addFacility(w, client_data, call_data)
    Widget      w;                      /* parent widget */
    XtPointer   client_data, call_data;
{
    int i,j;           /* indices to padElement[][] */
    int x,y;           /* icon position */
    struct PositionStruct *location;  /* temp location of indices */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* setup facility with default values */
    settings.numFacilities++;
    settings.facility[settings.numFacilities].valid = TRUE;
    padElement[i][j].elementType = FACILITY;
    padElement[i][j].id = settings.numFacilities;
    padElement[i][j].valid = TRUE;

    /* find position for icon and display it */
    convertPadtoIcon(i,j,&x,&y);
    displayPixmap( FACILITY, x,y); 

    /* eliminate dialog box */
    writeMessage("New facility created. Use Edit to change settings.");
    XtDestroyWidget( XtParent( XtParent( w )));
}

/* ----------------------------------------------------------------
    addFanIn

    Called by selecting Fan In Routing Point on ADD menu.

    Callback procedure.  Displays bitmap for fan in.  Set-ups
    data structure for fan in with default settings.

    client_data is i,j index of padElement[][]
    --------------------------------------------------------------- */
void addFanIn(w, client_data, call_data)
    Widget      w;                      /* parent widget */
    XtPointer   client_data, call_data;
{
    int i,j;           /* indices to padElement[][] */
    int x,y;           /* position in pixels of Icon */
    struct PositionStruct *location;  /* temp location of indices */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* setup facility with default values */
    settings.numRoutingPoints++;
    settings.routing[settings.numRoutingPoints].valid = TRUE;
    padElement[i][j].elementType = FAN_IN_RP;
    padElement[i][j].id = settings.numRoutingPoints; 
    padElement[i][j].valid = TRUE;

    /* find position for icon and display it */
    convertPadtoIcon(i,j,&x,&y);
    displayPixmap( FAN_IN_RP, x,y); 

    /* eliminate dialog box */
    writeMessage("New routing point created. Use Edit to change settings.");
    XtDestroyWidget( XtParent( XtParent( w )));
}


/* ----------------------------------------------------------------
    addFanOut

    Called by selecting Fan Out Routing Point on ADD menu.

    Callback procedure.  Displays bitmap for fan out.  Set-ups
    data structure for fan out with default settings.

    client_data is i,j index of padElement[][]
    --------------------------------------------------------------- */
void addFanOut(w, client_data, call_data)
    Widget      w;                      /* parent widget */
    XtPointer   client_data, call_data;
{
    int i,j;           /* indices to padElement[][] */
    int x,y;           /* position in pixels of Icon */
    struct PositionStruct *location;  /* temp location of indices */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* setup facility with default values */
    settings.numRoutingPoints++;
    settings.routing[settings.numRoutingPoints].valid = TRUE;
    padElement[i][j].elementType = FAN_OUT_RP;
    padElement[i][j].id = settings.numRoutingPoints;
    padElement[i][j].valid = TRUE;

    /* find position for icon and display it */
    convertPadtoIcon(i,j,&x,&y);
    displayPixmap( FAN_OUT_RP, x,y); 

    /* eliminate dialog box */
    writeMessage("New routing point created. Use Edit to change settings.");
    XtDestroyWidget( XtParent( XtParent( w )));
}

/* ----------------------------------------------------------------
    addGenericPoint

    Called by selecting Generic Point on ADD menu.

    Callback procedure.  Displays bitmap for generic block.  Set-ups
    data structure for a generic block with default settings.

    client_data is i,j index of padElement[][]
    --------------------------------------------------------------- */
void addGenericPoint(w, client_data, call_data)
    Widget      w;                      /* parent widget */
    XtPointer   client_data, call_data;
{
    int i,j;           /* indices to padElement[][] */
    int x,y;           /* position in pixels of Icon */
    struct PositionStruct *location;  /* temp location of indices */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* setup generic with default values */
    settings.numGenericPoints++;
    settings.generic[settings.numGenericPoints].valid = TRUE;
    padElement[i][j].elementType = GENERIC;
    padElement[i][j].id = settings.numGenericPoints;
    padElement[i][j].valid = TRUE;

    /* find position for icon and display it */
    convertPadtoIcon(i,j,&x,&y);
    displayPixmap( GENERIC, x,y); 

    /* eliminate dialog box */
    writeMessage("New generic point created. Use Edit to change settings.");
    XtDestroyWidget( XtParent( XtParent( w )));
}

/* ===================================================================
   CALLBACK PROCEDURES FOR DELETE
   =================================================================== */

/* ----------------------------------------------------------------
    delElement

    Called by selecting Delete from MODIFY menu.

    Callback procedure.  Deletes elements and displays blank bitmap.
    Searches all in and out lists and eliminates all references to
    element.

    client_data is i,j index of padElement[][]
    --------------------------------------------------------------- */
void delElement(w, client_data, call_data)
    Widget      w;                      /* parent widget */
    XtPointer   client_data, call_data;
{
    int i,j;           /* indices to padElement[][] */
    int x,y;           /* pixel position of icon */
    struct PositionStruct *location;  /* temp location of indices */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* invalidate entry */
    if ( !padElement[i][j].valid)
	writeMessage("That cell location is empty");
    else if ((i == SRC_X) && (j == SRC_Y)) 
	writeMessage("You cannot delete the source");
    else
    {
       padElement[i][j].valid = FALSE;
       switch ( padElement[i][j].elementType )
       {
	  case FACILITY:
	     settings.facility[padElement[i][j].id].valid = FALSE;
	     break;
	  case FAN_IN_RP:
	  case FAN_OUT_RP:
	     settings.routing[padElement[i][j].id].valid = FALSE;
	     break;
	  case GENERIC:
	     settings.generic[padElement[i][j].id].valid = FALSE;
	     break;
	  default:
	     quitX ( "SYSTEM ERROR in delElement");
	     break;
       }

      /* eliminate out list entries for this element */
      delOutListEntries( padElement[i][j].elementType,
	      	         padElement[i][j].id );

      /* find position for icon and display it */
      convertPadtoIcon(i,j,&x,&y);
      displayPixmap( BLANK, x,y); 
   
      writeMessage("Element deleted");
   }

   /* eliminate dialog box */
   XtDestroyWidget( XtParent( XtParent( w )));

   reDrawPad(NULL,NULL,NULL);
}

/* ===================================================================
   CALLBACK PROCEDURES FOR EDIT
   =================================================================== */

/* ----------------------------------------------------------------
    nameReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Calls changeName.
    --------------------------------------------------------------- */
void nameReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    changeName(widget, (XtPointer) locationGlobal, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    paramReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Forces user to pick a number.
    --------------------------------------------------------------- */
void paramReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    writeErrMessage("Please select parmeter number: 1, 2 or 3");
}

/* ----------------------------------------------------------------
    serverReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Calls changeServers.
    --------------------------------------------------------------- */
void serverReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    changeServers(widget, (XtPointer) locationGlobal, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    priorityReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Calls changePriority

    --------------------------------------------------------------- */
void priorityReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    changePriority(widget, (XtPointer) locationGlobal, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    countReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Calls changeCount.

    --------------------------------------------------------------- */
void countReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    changeCount(widget, (XtPointer) locationGlobal, (XtPointer) NULL);
}



/* ----------------------------------------------------------------
    functionReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Calls changeFunction.
    --------------------------------------------------------------- */
void functionReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    if(debug) printf("in functionReturn\n");
    changeFunction(widget, (XtPointer) locationGlobal, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    changeName

    Callback procedure.  Called by clicking "OK" on dialog box.
    (Pressing return in dialog box doesn't work).
    Gets name from the user and changes the name in settings.

    client_data is location (contain i,j for padElements & x,y on pad)
    --------------------------------------------------------------- */
void changeName(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;        /* indices in padElements[][]  */
    struct PositionStruct *location;  /* location of indices */
    String tempStr;        /* temporarily hold name  */
    char   msgStr[MAX_CHARS_IN_WINDOW]; /* success message to user  */


    if(debug)printf("in changeName()\n");

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;


    /* Get name, check for empty string */
    tempStr = 	XawDialogGetValueString(XtParent(w));
    if ( strcmp(tempStr, "") == 0)

       writeMessage("Must give the facility a name");  
    else
    {
       strcpy( 
          settings.facility[padElement[i][j].id].nameStr, tempStr);
       sprintf(msgStr, "Facility given the name: %s", tempStr);
       writeMessage(msgStr);  

       /* Get rid of popup & dialog box, restore screen */
       XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(
          XtParent(XtParent(w)))))));
    }
}

/* ----------------------------------------------------------------
    nameChoice

    Called by Name entry on Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    enter a new name for a facility.  Used for facilities ONLY.

    client_data is location in padElements[][]
    --------------------------------------------------------------- */
void nameChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    i,j;                  /* indices in padElements */
    int                    x,y;                  /* position in window */

    if(debug) printf("in nameChoice\n");

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+OFFSET+OFFSET);
    n++;
    XtSetArg(argList[n], XtNy, y+OFFSET+OFFSET);
    n++;
    popup = XtCreatePopupShell("namePrompt", transientShellWidgetClass,
				XtParent(w),argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter new name");
    n++;
    XtSetArg( argList[n],XtNvalue, 
          settings.facility[padElement[i][j].id].nameStr);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "OK", changeName, (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeServers

    Callback procedure.  Called by clicking "OK" on dialog box.
    (pressing return in dialog box doesn't work).
    Gets new number of servers from the user and updates settings.

    client_data is location (contain i,j for padElements & x,y on pad)
    --------------------------------------------------------------- */
void changeServers(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;        /* indices in padElements[][]  */
    struct PositionStruct *location;  /* location of indices */
    String serversStr; /* char string of number of servers  */
    int    serversInt; /* integer version */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* Get name */
    serversStr =  XawDialogGetValueString(XtParent(w));
    if ( sscanf( serversStr, "%d", &serversInt) == EOF)

	/* an illegal value has been entered */
	writeMessage("I don't understand.  Please re-enter.");
    else
    {
	settings.facility[padElement[i][j].id].numServers = serversInt;
	writeMessage("Number of servers changed");

        /* Get rid of popup & dialog box, restore screen */
        XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(
           XtParent(XtParent(w)))))));
    }
}

/* ----------------------------------------------------------------
    serversChoice

    Called by Name entry on Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    enter a new number of servers.  Used for facilities ONLY.

    client_data is location in padElements[][]
    --------------------------------------------------------------- */
void serversChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                  /* counter */
    int                    i,j;                  /* indices in padElements */
    int                    x,y;                  /* position in pad */
    char                   valueStr[INT_STR];    /* str version of value */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+ OFFSET+OFFSET );
    n++;
    XtSetArg(argList[n], XtNy, y+ OFFSET+OFFSET );
    n++;
    popup = XtCreatePopupShell("serversPrompt", transientShellWidgetClass,
				XtParent(w),argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter new number of servers");
    n++;
    sprintf(valueStr, "%d", 
       settings.facility[padElement[i][j].id].numServers);
    XtSetArg( argList[n],XtNvalue,valueStr);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "OK", changeServers, (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeRequest

    Callback procedure.  Called by clicking "OK" on dialog box.
    (pressing return in dialog box doesn't work).
    Gets new request type for facility.

    client_data is location (contain i,j for padElements) 
    --------------------------------------------------------------- */
void changeRequest(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;        /* indices in padElements[][]  */
    int    request;      /* REQUEST or PREEMPT */
    struct PositionStruct *location;  /* location of indices
					   and distn!  */
    String nameStr;     /* button widget's name */            
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */


    /* Get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* The request can be found by checking the name (label)
       of the widget that called this procedure  */
    n = 0;
    XtSetArg(argList[n], XtNlabel, &nameStr );
    n++;
    XtGetValues(w,argList,n);

    if( !(request = convertStrToType(nameStr)))
	   quitX("SYSTEM ERROR in changeRequest"); 

    settings.facility[padElement[i][j].id].typeRequest = request;

    writeMessage("Request changed");

    /* Get rid of popup & dialog box, restore screen */
    XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(
        XtParent(XtParent(w)))))));
}

/* ----------------------------------------------------------------
    requestChoice

    Called by Type of Request entry on Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    change the type of request for a facility.

    client_data is location in padElements[][]
    --------------------------------------------------------------- */
void requestChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices 
					   and distn type */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    x,y;                  /* position in pad */

    /* get position */
    location = (struct PositionStruct *) client_data;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+ OFFSET+OFFSET );
    n++;
    XtSetArg(argList[n], XtNy, y+ OFFSET+OFFSET );
    n++;
    popup = XtCreatePopupShell("Prompt", transientShellWidgetClass,
				XtParent(w),argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Select the type of request");
    n++;
    XtSetArg( argList[n],XtNdefaultDistance, 0);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add buttons */
    XawDialogAddButton(dialog, "Request", changeRequest, (XtPointer) location);
    XawDialogAddButton(dialog, "Preempt", changeRequest, (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changePriority

    Callback procedure.  Called by clicking "OK" on dialog box.
    (pressing return in dialog box doesn't work).
    Gets new priority for arrivals from the user and updates settings.

    client_data is location (contain i,j for padElements & x,y on pad)
    --------------------------------------------------------------- */
void changePriority(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;        /* indices in padElements[][]  */
    struct PositionStruct *location;  /* location of indices */
    String priorityStr; /* char string of number of servers  */
    int    priorityInt; /* integer version */

    /* Get new priority */
    priorityStr =  XawDialogGetValueString(XtParent(w));
    if ( ( strcmp(priorityStr, "") == 0) ||
         ( sscanf( priorityStr, "%d", &priorityInt) == 0) ||
         ( priorityInt < 0 ) ||
         ( priorityInt > 100 ) )

	/* an illegal value has been entered */
	writeMessage("I don't understand.  Please re-enter.");
    else
    {
	settings.arrival[1].priority = priorityInt;
	writeMessage("Arrival priority changed");

        /* Get rid of popup & dialog box, restore screen */
        XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(
           XtParent(XtParent(w)))))));
    }
}

/* ----------------------------------------------------------------
    priorityChoice

    Called by Priority entry on Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    change the priority for an arrival or facility.

    client_data is location in padElements[][]
    --------------------------------------------------------------- */
void priorityChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    x,y;                  /* position in pad */
    char                   valueStr[INT_STR];    /* str version of value */


    /* get position */
    location = (struct PositionStruct *) client_data;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+ OFFSET+OFFSET );
    n++;
    XtSetArg(argList[n], XtNy, y+ OFFSET+OFFSET );
    n++;
    popup = XtCreatePopupShell("priorityPrompt", transientShellWidgetClass,
				XtParent(w),argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter the new priority");
    n++;
    sprintf(valueStr, "%d", settings.arrival[1].priority);
    XtSetArg( argList[n],XtNvalue, valueStr);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "OK", changePriority, (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeCount

    Callback procedure.  Called by clicking "OK" on dialog box.
    (pressing return in dialog box doesn't work).
    Gets new initial count for arrivals from the user and updates
    settings.

    client_data is location (contain i,j for padElements & x,y on pad)
    --------------------------------------------------------------- */
void changeCount(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;        /* indices in padElements[][]  */
    struct PositionStruct *location;  /* location of indices */
    String countStr; /* char string of number of servers  */
    int    countInt; /* integer version */

    /* Get name */
    countStr =  XawDialogGetValueString(XtParent(w));
    if ( ( strcmp(countStr, "") == 0) ||
         ( sscanf( countStr, "%d", &countInt) == 0) )

	/* an illegal value has been entered */
	writeMessage("I don't understand.  Please re-enter.");
    else
    {
	settings.arrival[1].initialCount = countInt;
	writeMessage("Arrival's initial count changed");

       /* Get rid of popup & dialog box, restore screen */
       XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(
          XtParent(XtParent(w)))))));
    }

}

/* ----------------------------------------------------------------
    countChoice

    Called by count entry on Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    change the initial count for an arrival.

    client_data is location in padElements[][]
    --------------------------------------------------------------- */
void countChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    x,y;                  /* position in pad */
    char                   valueStr[INT_STR];    /* current count */

    /* get position */
    location = (struct PositionStruct *) client_data;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+ OFFSET+OFFSET );
    n++;
    XtSetArg(argList[n], XtNy, y+ OFFSET+OFFSET );
    n++;
    popup = XtCreatePopupShell("countPrompt", transientShellWidgetClass,
				XtParent(w) ,argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter the new Initial Count");
    n++;
    sprintf(valueStr, "%d", settings.arrival[1].initialCount);

    XtSetArg( argList[n],XtNvalue,valueStr);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "OK", changeCount, (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeDistn

    Callback procedure.  Called by clicking "OK" on dialog box.
    (pressing return in dialog box doesn't work).
    Gets new distribution for arrival, facility or routing point.

    client_data is location (contain i,j for padElements) AND
		distribution type
    --------------------------------------------------------------- */
void changeDistn(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;        /* indices in padElements[][]  */
    int    distn;      /* distribution  */
    struct PositionStruct *location;  /* location of indices
					   and distn!  */
    String nameStr;     /* button widget's name */            
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */


    /* Get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* The distribution can be found by checking the name (label)
       of the widget that called this procedure  */
    n = 0;
    XtSetArg(argList[n], XtNlabel, &nameStr );
    n++;
    XtGetValues(w,argList,n);
    if( !(distn = convertStrToType(nameStr)))
	   quitX("SYSTEM ERROR in changeDistn"); 

    switch( padElement[i][j].elementType )
    {
	case FACILITY:
	   settings.facility[padElement[i][j].id].distn = distn; break;
	case FAN_IN_RP:
	case FAN_OUT_RP:
	   settings.routing[padElement[i][j].id].distn = distn; break;
	case ARRIVAL:
	   settings.arrival[1].distn = distn; break;
	default:
	   quitX("SYSTEM ERROR in changeDistn"); break;
    }

    writeMessage("Distribution changed");

    /* Get rid of popup & dialog box, restore screen */
    XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(
        XtParent(XtParent(w)))))));
}

/* ----------------------------------------------------------------
    distnChoice

    Called by distn entry on Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    change the distribution for a facility or an arrival.

    client_data is location in padElements[][]
    --------------------------------------------------------------- */
void distnChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices 
					   and distn type */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    x,y;                  /* position in pad */

    /* get position */
    location = (struct PositionStruct *) client_data;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+ OFFSET+OFFSET );
    n++;
    XtSetArg(argList[n], XtNy, y+ OFFSET+OFFSET );
    n++;
    popup = XtCreatePopupShell("Prompt", transientShellWidgetClass,
				XtParent(w),argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Select the distribution");
    n++;
    XtSetArg( argList[n],XtNdefaultDistance, 0);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add buttons */
    XawDialogAddButton(dialog, "Constant", changeDistn , (XtPointer) location);
    XawDialogAddButton(dialog, "Uniform", changeDistn , (XtPointer) location);
    XawDialogAddButton(dialog, "Random", changeDistn , (XtPointer) location);

    XawDialogAddButton(dialog, "Exponential", changeDistn , 
      		(XtPointer) location);
    XawDialogAddButton(dialog, "Normal", changeDistn , (XtPointer) location);
    XawDialogAddButton(dialog, "Erlang", changeDistn , (XtPointer) location);
    XawDialogAddButton(dialog, "Hyperx", changeDistn , (XtPointer) location);
    XawDialogAddButton(dialog, "Triangle", changeDistn , (XtPointer) location);

    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);
    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
    changeParam

    Callback procedure.  Called by clicking "OK" on dialog box.
    (pressing return in dialog box doesn't work).
    Gets new parameter (1,2 or 3) for arrival, facility.

    client_data is location (contain i,j for padElements & x,y on pad)
		and parameter number.
    --------------------------------------------------------------- */
void changeParam(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;                         /* indices in padElements[][]  */
    struct PositionStruct *location;             /* padElement indices */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* arg count */
    String nameStr;   /* name of button that called this widget */
    String paramStr;  /* param as a char * */
    float param; /* user input */
    int paramNum;  /* 1,2 or 3 */
    char msg[MAX_CHARS_IN_WINDOW];  /* msg to user */

    /* get position and parameter */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* The parameter number can be found by checking the name (label)
       of the widget that called this procedure  */
    n = 0;
    XtSetArg(argList[n], XtNlabel, &nameStr );
    n++;
    XtGetValues(w,argList,n);
    paramNum = atoi(nameStr);

    /* get parameter from user */
    paramStr = XawDialogGetValueString(XtParent(w));
    if ( ( strcmp(paramStr, "") == 0) ||
         ( sscanf( paramStr, "%f", &param) == 0) ) 

	/* an illegal value has been entered */
	writeMessage("I don't understand.  Please re-enter.");
    else
    {
	/* we got a legal value for the parameter.  Update settings */
	switch ( padElement[i][j].elementType )
	{
	   case FACILITY:
           
	      switch (paramNum)
	      {
		 case 1: settings.facility[padElement[i][j].id].param1 =
		    param; break;
		 case 2: settings.facility[padElement[i][j].id].param2 =
		    param; break;
		 case 3: settings.facility[padElement[i][j].id].param3 =
		    param; break;
	      }; break;
	    case ARRIVAL:
	      switch (paramNum)
	      {
		 case 1: settings.arrival[1].param1 = param; break;
		 case 2: settings.arrival[1].param2 = param; break;
		 case 3: settings.arrival[1].param3 = param; break;
	      }; break;
	   case FAN_IN_RP:
	   case FAN_OUT_RP:
	   default:
	      quitX("SYSTEM ERROR in changeParam with element type"); break;
	}

        sprintf(msg, "Paramater # %d changed to %4.2f",paramNum,param);
	writeMessage(msg);

        /* Get rid of popup & dialog box, restore screen */
        XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(XtParent(
           XtParent(XtParent(w))))))));
    }
}

/* ----------------------------------------------------------------
    paramChoice

    Called by Parameter 1, Parameter 2 or Parameter 3 entry on
    Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    change one of the parameters for the distn for a facility,
    arrival, or routing point.

    client_data is location in padElements[][] AND parameter
    --------------------------------------------------------------- */
void paramChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices
					   AND parameter number */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    x,y;                  /* position in pad */

    /* get position */
    location = (struct PositionStruct *) client_data;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+ OFFSET+OFFSET );
    n++;
    XtSetArg(argList[n], XtNy, y+ OFFSET+OFFSET );
    n++;
    popup = XtCreatePopupShell("paramPrompt", transientShellWidgetClass,
				w,argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter the new parameter");
    n++;
    XtSetArg( argList[n],XtNvalue,"");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "1", changeParam, (XtPointer) location);
    XawDialogAddButton(dialog, "2", changeParam, (XtPointer) location);
    XawDialogAddButton(dialog, "3", changeParam, (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}


/* ----------------------------------------------------------------
    changeWeight

    Callback procedure.  Called by clicking "OK" on dialog box.
    (pressing return in dialog box doesn't work).
    Gets new arc weight (1,2 or 3) for cumulative distribution
	on a fork (routing point element).

    client_data is location (contain i,j for padElements & x,y on pad)
		and parameter number.
    --------------------------------------------------------------- */
void changeWeight(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;                         /* indices in padElements[][]  */
    struct PositionStruct *location;             /* padElement indices */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* arg count */
    String nameStr;   /* name of button that called this widget */
    String paramStr;  /* param as a char * */
    float param; /* user input */
    int paramNum;  /* 1,2 or 3 */
    char msg[MAX_CHARS_IN_WINDOW];  /* msg to user */

    /* get position and parameter */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* The parameter number can be found by checking the name (label)
       of the widget that called this procedure  */
    n = 0;
    XtSetArg(argList[n], XtNlabel, &nameStr );
    n++;
    XtGetValues(w,argList,n);
    paramNum = atoi(nameStr);

    /* get parameter from user */
    paramStr = XawDialogGetValueString(XtParent(w));
    if ( ( strcmp(paramStr, "") == 0) ||
         ( sscanf( paramStr, "%f", &param) == 0) ) 

	/* an illegal value has been entered */
	writeMessage("I don't understand.  Please re-enter.");
    else
    {
	settings.routing[padElement[i][j].id].weight[paramNum] = param;
	sprintf(msg, "Arc Weight# %d changed to %4.2f",paramNum,param);
	writeMessage(msg);

	/* Get rid of popup & dialog box, restore screen */
	/*
        XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(XtParent(
	   XtParent(XtParent(w))))))));
	*/
    }
}

/* ----------------------------------------------------------------
   	weightChoice 

    Called by Weight entry on edit menu for a fork.

    Callback procedure.  Pops up a dialog box to allow the user to
    change one of the parameters for the distn for a facility,
    arrival, or routing point.

    client_data is location in padElements[][] AND parameter
    --------------------------------------------------------------- */
void weightChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices
					   AND parameter number */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    x,y;                  /* position in pad */
    char                   num[3];               /* char version of
						 weight index */

    /* get position */
    location = (struct PositionStruct *) client_data;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+ OFFSET+OFFSET );
    n++;
    XtSetArg(argList[n], XtNy, y+ OFFSET+OFFSET );
    n++;
    popup = XtCreatePopupShell("weightPrompt", transientShellWidgetClass,
				w,argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter the arc weight (0.0-1.0)\n(Weights used for cumulative distribution only.)");
    n++;
    XtSetArg( argList[n],XtNvalue,"");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add buttons */
    for( n = 1; n <= MAX_WEIGHTS; n++ )
    {
	sprintf( num, "%d", n );
	XawDialogAddButton(dialog, num, changeWeight, (XtPointer) location);
    }
    XawDialogAddButton(dialog, "Done" ,DestroyPopupPrompt,(XtPointer)
        XtParent(XtParent(XtParent(
           XtParent(XtParent(dialog))))));
    XtPopup(popup, XtGrabNone);
}




/* ----------------------------------------------------------------
    changeFunction

    Callback procedure.  Called by clicking "OK" on dialog box.
    (Pressing return in dialog box doesn't work).
    Gets name from the user and changes the name in settings.

    client_data is location (contain i,j for padElements & x,y on pad)
    --------------------------------------------------------------- */
void changeFunction(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    int    i,j;        /* indices in padElements[][]  */
    struct PositionStruct *location;  /* location of indices */
    String tempStr;        /* temporarily hold name  */
    char   msgStr[MAX_CHARS_IN_WINDOW]; /* success message to user  */


    if(debug)printf("in changeFunction()\n");

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;

    /* Get name, check for empty string */
    tempStr = 	XawDialogGetValueString(XtParent(w));
    if ( strcmp(tempStr, "") == 0)

       writeMessage("Must give the generic a function name");  
    else
    {
       strcpy( 
          settings.generic[padElement[i][j].id].nameStr, tempStr);
       sprintf(msgStr, "Generic Block's function name: %s", tempStr);
       writeMessage(msgStr);  

       /* Get rid of popup & dialog box, restore screen */
       XtDestroyWidget(XtParent(XtParent(XtParent(XtParent(
          XtParent(XtParent(w)))))));
    }
}

/* ----------------------------------------------------------------
    functionChoice 

    Called by Name entry on Edit menu.

    Callback procedure.  Pops up a dialog box to allow the user to
    enter a new function name for a generic block.  

    client_data is location in padElements[][]
    --------------------------------------------------------------- */
void functionChoice(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
    struct PositionStruct *location;  /* location of indices */
    Widget                 dialog,    /* dialog box          */
			   popup;     /* contains the dialog box */
    Arg                    argList[MAX_ARGS];    /* resource list   */
    int                    n;                    /* counter */
    int                    i,j;                  /* indices in padElements */
    int                    x,y;                  /* position in window */

    if(debug) printf("in functionChoice\n");

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;
    x = location->x;
    y = location->y;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x+OFFSET+OFFSET);
    n++;
    XtSetArg(argList[n], XtNy, y+OFFSET+OFFSET);
    n++;
    popup = XtCreatePopupShell("functionPrompt", transientShellWidgetClass,
				XtParent(w),argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Enter function name");
    n++;
    XtSetArg( argList[n],XtNvalue, 
          settings.generic[padElement[i][j].id].nameStr);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "OK", changeFunction, (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}
/* ----------------------------------------------------------------
    editElement

    Called by selecting Edit from MODIFY menu.

    Callback procedure. Allows user to change the following features.

	For Facilites:
		Name
		Number of Servers
		Distribution
		Parameter 1
		Parameter 2
		Parameter 3
	For Fan-in Points
                * nothing *
	For Fan-Out Points (always uses cumulative distn)
		Weight 1
		Weight 2
		Weight 3
	For the Arrival Point
		Priority
		Initial Count
		Distribution
		Parameter 1
		Parameter 2
		Parameter 3

    client_data is i,j index of padElement[][]
    --------------------------------------------------------------- */
void editElement(w, client_data, call_data)
    Widget      w;                      /* parent widget */
    XtPointer   client_data, call_data;
{
    int i,j;           /* indices to padElement[][] */
    int x,y;           /* pixel location of i,j */
    Arg          arglist[MAX_ARGS];
    struct PositionStruct *location;   /* padElement indices   */
     			                     /* and parameter number */
    Arg          argList[MAX_ARGS];    /* resource list   */
    Widget       popup, dialog;         /* menu windows    */
    int          n;                    /* counter */

/*
	XtMapWidget(EditToggle);
*/

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;
    x = location->x;
    y = location->y;

    /* check location   */
    if ( !padElement[i][j].valid)
    {
	writeMessage("That cell location is empty");
	return;
    }

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, (Position) x + OFFSET);
    n++;
    XtSetArg(argList[n], XtNy, (Position) y + OFFSET);
    n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, 
                               XtParent(w),argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Select item to change");
    n++;
    XtSetArg( argList[n],XtNdefaultDistance, 0);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);
    /* Add buttons */
    if ( padElement[i][j].elementType == FACILITY )
    {
	XawDialogAddButton(dialog, "Name", nameChoice,
			 (XtPointer) location);
	XawDialogAddButton(dialog, "Servers", serversChoice,
			 (XtPointer) location);
	XawDialogAddButton(dialog, "Request", requestChoice,
			 (XtPointer) location);
    }
    else if ( padElement[i][j].elementType == ARRIVAL )
    {
	XawDialogAddButton(dialog, "Priority", priorityChoice,
			 (XtPointer) location);
	XawDialogAddButton(dialog, "Initial Count", countChoice,
			 (XtPointer) location);
    }

    /* allow them to edit Distn on FACILITY & ARRIVAL */
    if ( padElement[i][j].elementType != GENERIC && 
    	padElement[i][j].elementType != FAN_OUT_RP)

    	XawDialogAddButton(dialog, "Distn", distnChoice,
			 (XtPointer) location);

    /* allow them to edit parameters on FACILITY & ARRIVAL & FORK */
    if ( padElement[i][j].elementType != GENERIC )
    {
    	if ( padElement[i][j].elementType != FAN_OUT_RP )
	{
    		XawDialogAddButton(dialog, "Param", paramChoice,
			 (XtPointer) location);
	}
	else
	{
    		XawDialogAddButton(dialog, "Weight", weightChoice,
			 (XtPointer) location);
	}
    }
    else /* padElement == GENERIC */
    {
    	XawDialogAddButton(dialog, "Name", functionChoice,
			 (XtPointer) location);
    }

    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)
      		XtParent(XtParent(dialog)));

    XtPopup(popup, XtGrabNone);
}




/* -------------------------------------------------------------------
   getDistn

   Print the name of distribution used by the given list element
   (either a facility, arrival point or routing point).
   ------------------------------------------------------------------- */
char * getDistn( distn, param1, param2, param3 )
	int  distn;       /* type of probability distribution    */
	float param1,     /* parameters to the given probability */
	      param2,     /*    distribtion.  Some may be unused.*/
	      param3;
{
    static char returnStr[MAX_INFO];
    char  tempStr[MAX_INFO];

	if(debug) printf("in getDist with distn %d p1 %f p2 %f p3 %f\n",distn,param1,param2,param3);

	switch (distn)
	{
		case UNIFORM:
                        strcpy(returnStr,"Uniform distribution");
                        sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
                           param1);
                        strcat( returnStr, tempStr);
                        sprintf(tempStr,"\tParameter 2: %8.2f\n",
                           param2);
                        strcat( returnStr, tempStr);
			break;

		case EXPONENTIAL:
			strcpy(returnStr,"Exponential distribution");
			sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
			   param1);
			strcat( returnStr, tempStr);
			break;

		case NORMAL:
			strcpy(returnStr,"Normal distribution");
			sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
			   param1);
			strcat( returnStr, tempStr);
			sprintf(tempStr,"\tParameter 2: %8.2f\n",
			   param2);
			strcat( returnStr, tempStr);
			break;

		case ERLANG:
			strcpy(returnStr,"Erlang distribution");
			sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
			   param1);
			strcat( returnStr, tempStr);
			sprintf(tempStr,"\tParameter 2: %8.2f\n",
			   param2);
			strcat( returnStr, tempStr);
			break;

		case RANDOM:
			strcpy(returnStr,"Random distribution");
			sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
			   param1);
			strcat( returnStr, tempStr);
			sprintf(tempStr,"\tParameter 2: %8.2f\n",
			   param2);
			strcat( returnStr, tempStr);
			break;

		case HYPERX:
			strcpy(returnStr,"Hyperexponential distribution");
			sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
			   param1);
			strcat( returnStr, tempStr);
			sprintf(tempStr,"\tParameter 2: %8.2f\n",
			   param2);
			strcat( returnStr, tempStr);
			break;

		case TRIANGLE:
			strcpy(returnStr,"Triangle distribution");
			sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
			   param1);
			strcat( returnStr, tempStr);
			sprintf(tempStr,"\tParameter 2: %8.2f\n",
			   param2);
			strcat( returnStr, tempStr);
			sprintf(tempStr,"\tParameter 3: %8.2f\n",
			   param3);
			strcat( returnStr, tempStr);
			break;
		case CONSTANT:
			strcpy(returnStr,"Constant distribution");
			sprintf(tempStr,"\n\tParameter 1: %8.2f\n",
			   param1);
			strcat( returnStr, tempStr);
			break;

		default:
			fprintf(stderr,"ERROR: ");
			fprintf(stderr,"Illegal distn in getDistn\n");
		        returnStr[0] ='\0';
		        break;

	}
	return returnStr;
}

/* -------------------------------------------------------------------
   getRoutingDistn

   Get the info on the distribution.
   ------------------------------------------------------------------- */
char * getRoutingDistn( int index )
{
    	static char returnStr[MAX_INFO];
    	char tempStr[MAX_INFO];
	int	i;

	strcpy(returnStr,"Cumulative distribution\n");

	/*  FIX !  count number of arcs */
	for( i =1; i <= MAX_WEIGHTS; i++)
	{
		sprintf(tempStr,"Weight %d: %8.2f\n",i,
			settings.routing[index].weight[i]);
		strcat( returnStr, tempStr );

	}
	return(returnStr);
}

/* -------------------------------------------------------------------
   getFacilityDistn

   Get the info on the distribution.
   ------------------------------------------------------------------- */
char * getFacilityDistn( int index )
{
     return(
	getDistn(     settings.facility[index].distn,
		      settings.facility[index].param1,
		      settings.facility[index].param2,
		      settings.facility[index].param3 ));
}
/* -------------------------------------------------------------------
   getArrivalDistn

   Get the info on the distribution.
   ------------------------------------------------------------------- */
char * getArrivalDistn( int index )
{
    return(
	getDistn(     settings.arrival[index].distn,
		      settings.arrival[index].param1,
		      settings.arrival[index].param2,
		      settings.arrival[index].param3 ));
}

/* ----------------------------------------------------------------
    getInfo

    Combine info on the given element into a string.
    --------------------------------------------------------------- */
void getInfo(str,i,j)
   char str[];  /* return value */
   int  i,j;    /* position in padElements[][] */
{
   int  pos=padElement[i][j].id;  /* Position in facilities,
                                     arrival or routing arrays */
   char tempStr[MAX_INFO];

   switch( padElement[i][j].elementType )
   {
      case ARRIVAL: 
               sprintf(str, "SOURCE\n\tTokens have priority %d\n", 
                  settings.arrival[pos].priority);
               sprintf(tempStr,"\tInitial Token Count: %d\n", 
                  settings.arrival[pos].initialCount);
               strcat(str,tempStr);
               strcat(str, getArrivalDistn(pos));
	       break;

      case FACILITY:
	       sprintf(str, "FACILITY: %s\n",
		  settings.facility[pos].nameStr);
	       if (settings.facility[pos].numServers > 1)
	           sprintf(tempStr,"\t%d servers\n",
		      settings.facility[pos].numServers);
	       else  /* single server process */
	           sprintf(tempStr,"\t%d server\n",
		      settings.facility[pos].numServers);
	       strcat(str,tempStr);
	       if ( settings.facility[pos].typeRequest == PREEMPT )
	       {
	          sprintf(tempStr, "\tPreempt processes\n");
		  strcat(str,tempStr);
	       }
	       else /* typeRequest == REQUEST */
	       {
	          sprintf(tempStr, "\tDoes not Preempt processes\n");
		  strcat(str,tempStr);
	       }
	       strcat(str, getFacilityDistn(pos));
	       break;

      case FAN_IN_RP:
	       strcpy(str, "Join Element\n(No Parameters)\n");
	       break;

      case FAN_OUT_RP:
	       strcpy(str, "Fork Element \n");
	       strcat(str, getRoutingDistn(pos));
	       break;
   
      case SINK:
	       strcpy(str, "Sink Element \n(No Parameters)\n");
	       break;
   
      case GENERIC:
	       strcpy(str, "Generic Element\n");
	       sprintf(tempStr, "Function: %s\n",settings.generic[pos].nameStr);
	       strcat(str,tempStr); 
	       break;

      default: quitX("Problem in getInfo");
	       break;
   }
}


/* ----------------------------------------------------------------
    infoElement

    Called by selecting Info from MODIFY menu.
    Callback procedure. Displays current settings for the
    element selected.

    client_data is i,j index of padElement[][]
    --------------------------------------------------------------- */
void infoElement(w, client_data, call_data)
    Widget      w;                      /* parent widget */
    XtPointer   client_data, call_data;
{
    int i,j;           /* indices to padElement[][] */
    int x,y;           /* pixel location of i,j */
    struct PositionStruct *location;   /* padElement indices   */
    Arg          argList[MAX_ARGS];    /* resource list   */
    Widget       popup, dialog;         /* menu windows    */
    int          n;                    /* counter */
    char         labelStr[MAX_INFO];   /* text of info for element */

    /* get position */
    location = (struct PositionStruct *) client_data;
    i = location->i;
    j = location->j;
    x = location->x;
    y = location->y;


    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, (Position) x + OFFSET);
    n++;
    XtSetArg(argList[n], XtNy, (Position) y + OFFSET);
    n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, 
                               XtParent(w),argList, n);
    
    /* get information */
    getInfo( labelStr, i,j );

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, labelStr );
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);
    /* Add button */
    XawDialogAddButton(dialog, "Done", DestroyPopupPrompt,(XtPointer)
    	XtParent(XtParent(dialog)));

    /*  XtParent(XtParent(XtParent(XtParent(dialog))))); */

    XtPopup(popup, XtGrabNone);
}

/* ================================================================
   MAIN
   ================================================================ */

/* ----------------------------------------------------------------
   addMenu

   Called by clicking an empty location the pad.

   Pops up a dialog box with ADD options
       ADD facility,
       ADD fan in routing point,
       ADD fan out routing point, or 
       CANCEL.

   Note: This procedure is called by processEvent.  During this time
   the X queue is filling up with events, but NOT processing events.
   This procedure setup a dialog box with some callback procedures 
   and returns.  When it returns, it returns to processEvent (event.c)
   and then processEvent() returns back to the main event loop and
   X continues processing events.
   --------------------------------------------------------------- */
void addMenu(x,y)
    int x,y;           /* pixel location relative to pad */
{
    Arg    argList[MAX_ARGS];  /* resource list  */
    int    n;                  /* resource count */
    Widget dialog,             /* dialog box     */
	   popup;              /* Widget that contains the dialog box */
    int    i,j;                      /* indices in padElements */
    struct PositionStruct *location; /* indices in padElements */
    Position  padx, pady;      /* pixel location relative to 
                                  entire window */

/*
	XtMapWidget(AddToggle);
*/

    /* make permanent space for location struct */
    location = (struct PositionStruct *)
                   malloc( sizeof( struct PositionStruct));

    /* Convert pixel position to indices of padElements matrix */
    convertXYtoPad(x,y,&i,&j);
    location->i = i;
    location->j = j;

    /* Create a popup widget to hold dialog box */
    XtTranslateCoords(pad, (Position) x, (Position) y, &padx, &pady);
    n = 0;
    XtSetArg(argList[n], XtNx, (Position) padx);                         
    n++;
    XtSetArg(argList[n], XtNy, (Position) pady);
    n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Select element to add");
    n++;
    XtSetArg( argList[n],XtNdefaultDistance, 0);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);
    /* Add buttons */
    XawDialogAddButton(dialog, "Facility", addFacility, 
                         (XtPointer) location);
    XawDialogAddButton(dialog, "Join", addFanIn,
                         (XtPointer) location);
    XawDialogAddButton(dialog, "Fork", addFanOut,
                         (XtPointer) location);
    XawDialogAddButton(dialog, "Generic", addGenericPoint,
                         (XtPointer) location);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);


}

/* ----------------------------------------------------------------
   modifyMenu

   Called by clicking a full location the pad.

   Pops up a dialog box with EDIT options
       EDIT,
       INFO,
       DELETE, or
       CANCEL.

   Note: This procedure is called by processEvent.  During this time
   the X queue is filling up with events, but NOT processing events.
   This procedure setup a dialog box with some callback procedures 
   and returns.  When it returns, it returns to processEvent (event.c)
   and then processEvent() returns back to the main event loop and
   X continues processing events.
   --------------------------------------------------------------- */
void modifyMenu(x,y)
    int x,y;           /* pixel location relative to pad */
{

    Arg    argList[MAX_ARGS];  /* resource list  */
    int    n;                  /* resource count */
    Widget dialog,             /* dialog box     */
	   popup;              /* Widget that contains the dialog box */
    int    i,j;                      /* indices in padElements */
    Position  padx, pady;            /* pixel location relative to 
                                        entire window */
	Widget button;


    /* make permanent space for location struct */
    locationGlobal = (struct PositionStruct *)
                   malloc( sizeof( struct PositionStruct));

    /* Convert pixel position to indices of padElements matrix */
    convertXYtoPad(x,y,&i,&j);
    XtTranslateCoords(pad, (Position) x, (Position) y, &padx, &pady);
    locationGlobal->i = i;      
    locationGlobal->j = j;
    locationGlobal->x = padx;
    locationGlobal->y = pady;

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, (Position) padx);
    n++;
    XtSetArg(argList[n], XtNy, (Position) pady);
    n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    XtSetArg( argList[n],XtNlabel, "Change This Element:");
    n++;
    XtSetArg( argList[n],XtNdefaultDistance, 0);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);
    /* Add buttons */
    if( padElement[i][j].elementType != FAN_IN_RP &&
        padElement[i][j].elementType != SINK )
       XawDialogAddButton(dialog, "Edit  ", editElement,
			 (XtPointer) locationGlobal);
    XawDialogAddButton(dialog, "Info  ", infoElement,
			 (XtPointer) locationGlobal);
    if( padElement[i][j].elementType != SINK &&
        padElement[i][j].elementType != ARRIVAL)
       XawDialogAddButton(dialog, "Delete", delElement,
			 (XtPointer) locationGlobal);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

/*************************************************************
	Code to make menus vertical
	**************************
    dialog = XtCreateManagedWidget("dialog", formWidgetClass, popup,
				   argList, n);

    n=0;
    XtSetArg( argList[n],XtNfromVert, NULL);
    n++;
    XtSetArg( argList[n],XtNwidth, 60);
    n++;
    button = XtCreateManagedWidget( "Edit", commandWidgetClass,
			dialog, argList,n);
    XtAddCallback(button, XtNcallback, editElement,  
			(XtPointer)locationGlobal);

    n=0;
    XtSetArg( argList[n],XtNfromVert, button);
    n++;
    XtSetArg( argList[n],XtNwidth, 60);
    n++;
    button = XtCreateManagedWidget( "Info", commandWidgetClass,
			dialog,argList,n);
    XtAddCallback(button, XtNcallback, infoElement,  
			(XtPointer)locationGlobal);
 
    n=0;
    XtSetArg( argList[n],XtNfromVert, button);
    n++;
    XtSetArg( argList[n],XtNwidth, 60);
    n++;
    button = XtCreateManagedWidget( "Cancel", commandWidgetClass,
			dialog,argList,n);
    XtAddCallback(button, XtNcallback, DestroyPopupPrompt,  
			(XtPointer)dialog);
****************************************************************/

    XtPopup(popup, XtGrabNone);
}


/* ----------------------------------------------------------------
    initPadMenu

    Create menu tree.  
    --------------------------------------------------------------- */

void initPadMenu()
{
    XtAppAddActions(appCon, actionTablePadMenu, 
                    XtNumber(actionTablePadMenu));
}
