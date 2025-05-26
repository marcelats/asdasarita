/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : drawMenu.c 12/1/91 22:02:17
**		Author    : Brian Harrington 
**		Purpose   : user interface code for drawing lines and 
				objects 
**		Files Used:
**		History   :
			origin:   7/ 4/90
		: 11/3 beh  
			fixed bug that caused a core dump when switching
			between connect and edit modes
	
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)drawMenu.c	1.21 12/1/91 22:02:17";
#endif /* lint */

#include "modeller.h"



/* ================================================================
   EXTERNAL PROCEDURES
   ================================================================ */
extern struct List *new();   /* list.c call */
extern void convertXYtoPad( int, int, int*, int*);
extern void convertXYtoStartLine( int, int, int*, int*);
extern void convertXYtoEndLine( int, int, int*, int*);
extern void writeMessage(char *);
extern void reDrawPad(Widget, XtPointer, XtPointer );


/* ================================================================
   EXTERNAL GLOBAL VARIABLES
   ================================================================ */
extern Display *theDisplay; /* X's display id */
extern Window   padWindow;  /* window id of the user's pad */
extern Window   outerWindow;  
extern GC       theGC;      /* X's graphics context id */
extern Widget   drawMenuButton, /* Button for connecting elements */
                optMenuButton, /* Button for option menu */
                commands,   /* holds all buttons   */
                pad;        /* Users' working area */
extern struct Settings settings;
extern int gridDisplay;   /* draw the grid?  TRUE or FALSE */

/* ================================================================
   GLOBAL VARIABLES
   ================================================================ */
char drawSwitch=OFF;   /* Used for getting points that link elements
			  Has three states,
			     OFF, WAIT_FIRST_PT, & WAIT_SECOND_PT  */
int drawFromX, drawFromY,  /* pad points of one element to be linked */
    drawToX, drawToY;      /* pad points of the other element */

Widget instructDialog=NULL;  /* the dialog box used by instructions() */


/* ----------------------------------------------------------------
   drawEndPoint

   Draw a line in the user's pad.
   ---------------------------------------------------------------- */

void drawEndPoint( x1,y1, x2, y2 )

   int       x1, y1;       /* first endpoint of the line */
   int       x2, y2;       /* the other endpoint         */

{
   x2 = x2 - 10;
   y2 = y2 - 5;

   if( x2 > x1 )
   { 
        XDrawArc( theDisplay, padWindow, theGC, x2, y2 , 10, 10,
	    -90*64, 180*64);
        XFillArc( theDisplay, padWindow, theGC, x2, y2 , 10, 10,
	    -90*64, 180*64);
   }
   else
   {
        XDrawArc( theDisplay, padWindow, theGC, x2, y2 , 10, 10,
	    90*64, 180*64);
        XFillArc( theDisplay, padWindow, theGC, x2, y2 , 10, 10,
	    90*64, 180*64);
   }
}

/* ----------------------------------------------------------------
   drawLine

   Draw a line in the user's pad.
   ---------------------------------------------------------------- */

void drawLine( i1, j1, i2, j2)

   int       i1, j1;       /* first endpoint of the line */
   int       i2, j2;       /* the other endpoint         */

{
   int  newX1, newY1, newX2, newY2;

   /* Translate points from arbritary i,j position in padElements[][]
      to an x,y position at the center of appropriate icon */
   convertPadtoStartLine( i1, j1, &newX1, &newY1);
   convertPadtoEndLine( i2, j2, &newX2, &newY2);

   XDrawLine( theDisplay, padWindow, theGC, newX1, newY1, newX2, newY2);
   drawEndPoint(newX1,newY1,newX2,newY2);
}


/* ----------------------------------------------------------------
    drawDestroyPopupPrompt

    Used to take the user out of "connect" or "disconnect" mode and
	put them in "edit" mode.

 *	Arguments: w - *** UNUSED ***.
 *                 client_data - the dialog widget.  This widget is a direct
 *                               child of the popup shell to destroy.
 *                 call_data - *** UNUSED **.
 *	Returns: none.

    --------------------------------------------------------------- */

void drawDestroyPopupPrompt(widget, client_data, call_data)
    Widget	widget;		
    XtPointer client_data, call_data;	
{
	Widget popup;

	if( instructDialog )
	{
		/* get rid of the popup & reset global variable */
    	popup = XtParent( (Widget) instructDialog);
    	XtDestroyWidget(popup);
		instructDialog = NULL;

    	drawSwitch = OFF;  /* reset draw switch */
    	setCursor( XS_DEFAULT ); /* reset cursor to edit mode */
	}
}


/* ----------------------------------------------------------------
    drawReset 

    Used by the reset the points to connect or disconnect 

 *	Arguments: w - *** UNUSED ***.
 *                 client_data - the dialog widget.  This widget is a direct
 *                               child of the popup shell to destroy.
 *                 call_data - *** UNUSED **.
 *	Returns: none.

    --------------------------------------------------------------- */
void drawReset(widget, client_data, call_data)
    Widget	widget;		
    XtPointer client_data, call_data;	
{
	switch( drawSwitch)
	{
		case WAIT_SECOND_PT:
			drawSwitch = WAIT_FIRST_PT;
			break;

		case WAIT_SECOND_PT_UNLINK:
			drawSwitch = WAIT_FIRST_PT_UNLINK;
			break;

		case WAIT_FIRST_PT:
		case WAIT_FIRST_PT_UNLINK:
		case OFF:
		default:  
			break;
	}
}

/* ----------------------------------------------------------------
    removeLink

    Called by processEvent() in event.c.  The user has selected
    to remove a link and entered points in the pad.  Update the data
    structures to remove the link the elements and erase it from the 
    display.
    --------------------------------------------------------------- */
void removeLink(void)
{
   int drawFromI, drawFromJ,   /* padElement indices for "from" x,y */
       drawToI, drawToJ;       /* padElement indices for "to" x,y */
   struct List *prev, *elem;   /* temporary pointers used to delete */
   int toElemID,              /* the element the line points TO */
       fromElemID;            /* the element the line points FROM */
   int toElemType;            /* the element type the line points FROM */
   char errMsg[MAX_ERROR_MSG];

    /* convert x,y to indices of padElement[][] */
    convertXYtoPad( drawFromX, drawFromY, &drawFromI, &drawFromJ);
    convertXYtoPad( drawToX, drawToY, &drawToI, &drawToJ);

       /* shorthand */
       fromElemID = padElement[drawFromI][drawFromJ].id;
       toElemID = padElement[drawToI][drawToJ].id;
       toElemType = padElement[drawToI][drawToJ].elementType;

       switch( padElement[drawFromI][drawFromJ].elementType )
       {
	  case FACILITY:
                findElementByType( settings.facility[fromElemID].out, 
                             toElemType, toElemID, &elem, &prev );

                if (elem != NULL)
		{
                    removeFromList( &(settings.facility[fromElemID].out), 
                             elem, prev );

                    reDrawPad(NULL,NULL,NULL);
                    writeMessage("link removed");
	        }
                else
		  {
                    writeMessage(
                      "There is not a link between those two element");
		  }
		break;

	  case ARRIVAL:

                findElementByType( settings.arrival[1].out, 
                             toElemType, toElemID, &elem, &prev );
                if (elem != NULL)
		{
                    removeFromList( &(settings.arrival[1].out), 
                             elem, prev );
                    reDrawPad(NULL,NULL,NULL);
                    writeMessage("link removed");
	        }
                else
                    writeMessage(
                      "There is not a link between those two element");
		break;

	  case FAN_IN_RP:
	  case FAN_OUT_RP:


                findElementByType( settings.routing[fromElemID].out, 
                              toElemType, toElemID, &elem, &prev );
                if (elem != NULL)
		{
                    removeFromList( &(settings.routing[fromElemID].out), 
                             elem, prev );
                    reDrawPad(NULL,NULL,NULL);
                    writeMessage("link removed");
	        }
                else
                    writeMessage(
                      "There is not a link between those two element");
		break;

	  case GENERIC:
                findElementByType( settings.generic[fromElemID].out, 
                             toElemType, toElemID, &elem, &prev );

                if (elem != NULL)
		{
                    removeFromList( &(settings.generic[fromElemID].out), 
                             elem, prev );

                    reDrawPad(NULL,NULL,NULL);
                    writeMessage("link removed");
	        }
                else
		  {
                    writeMessage(
                      "There is not a link between those two element");
		  }
		break;

	case SINK:
                writeMessage("Pick the starting point of the link FIRST");
		break;

           default:
		sprintf(errMsg,"Problems in removeLink, got element type %d\n",
       		   padElement[drawFromI][drawFromJ].elementType );
		quitX(errMsg);
                break;

    }
}

/* ----------------------------------------------------------------
    linkElements

    Called by processEvent() in event.c.  The user has selected
    link and entered to points in the pad.  Update the data
    structures to link the elements and draw a line on the display.
    --------------------------------------------------------------- */
void linkElements(void)
{
   int drawFromI, drawFromJ,   /* padElement indices for "from" x,y */
       drawToI,   drawToJ;     /* padElement indices for "to" x,y */
   struct List   *newNode;     /* node to add to an out list */
   int            toElemID,    /* the element the line points TO */
                  fromElemID;  /* the element the line points FROM */


    /* convert x,y to indices of padElement[][] */
    convertXYtoPad( drawFromX, drawFromY, &drawFromI, &drawFromJ);
    convertXYtoPad( drawToX, drawToY, &drawToI, &drawToJ);

       /* create new out list entry */
       newNode = new();
       newNode->elementType = padElement[drawToI][drawToJ].elementType;
       newNode->id = padElement[drawToI][drawToJ].id;

       /* shorthand */
       fromElemID = padElement[drawFromI][drawFromJ].id;
       toElemID = padElement[drawToI][drawToJ].id;


       switch( padElement[drawFromI][drawFromJ].elementType )
       {
	  case FACILITY:
		addToList( &(settings.facility[fromElemID].out), newNode );

                /* save the (i,j) for the element that is connected to */
                settings.facility[fromElemID].out->i = drawToI;
                settings.facility[fromElemID].out->j = drawToJ;
		break;

	  case ARRIVAL:
		if (newNode->elementType == FAN_IN_RP)
		   writeMessage("Cannot connect the source to a fan in");
		else 
		{
		   addToList( &(settings.arrival[1].out), newNode );
                   settings.arrival[1].out->i = drawToI;
                   settings.arrival[1].out->j = drawToJ;
		}
		break;

	  case FAN_IN_RP:
	  case FAN_OUT_RP:
		addToList( &(settings.routing[fromElemID].out), newNode);
                settings.routing[fromElemID].out->i = drawToI;
                settings.routing[fromElemID].out->j = drawToJ;
		break;

	  case GENERIC:
		addToList( &(settings.generic[fromElemID].out), newNode );

                /* save the (i,j) for the element that is connected to */
                settings.generic[fromElemID].out->i = drawToI;
                settings.generic[fromElemID].out->j = drawToJ;
		break;
	}

       
    drawLine(drawFromI, drawFromJ, drawToI, drawToJ);
    writeMessage("elements connected");
}

/* ----------------------------------------------------------------
    resetDrawSwitch

    Called from draw menu.

    Callback procedure.  Takes a user out of "connect" or "disconnect"
    mode and puts him/her in "edit" mode.

    client_data is unused
    --------------------------------------------------------------- */
void resetDrawSwitch(w, client_data, call_data)
    Widget      w;
    XtPointer   client_data, call_data;
{
  
    switch( drawSwitch )
      {
      case WAIT_FIRST_PT:      
      case WAIT_FIRST_PT_UNLINK:
	break;

      case WAIT_SECOND_PT:
	drawSwitch = WAIT_FIRST_PT;
	break;

      case WAIT_SECOND_PT_UNLINK:
	drawSwitch = WAIT_FIRST_PT_UNLINK;
	break;

      case OFF:
      default:
	break;
      }

}

/* ----------------------------------------------------------------
    instructions

    Called from draw menu.

    Callback procedure.  Pops up a dialog box that gives the users
    instructions for linking two objects.

    client_data is LINK or UNLINK
    --------------------------------------------------------------- */
void instructions(w, client_data, call_data)
    Widget	w;		        
    XtPointer   client_data, call_data;	
{

    Position   x,y;    /* position of dialog box        */
    Arg         argList[MAX_ARGS];   /* resource list   */
    int        n;      /* arg list                      */
    Widget dialog,     /* dialog box                    */
           popup;      /* Widget that contains the dialog box */

    /* Check if there is already an instruction box on the screen */
	if( instructDialog )
	{
		/* just change the label of the instruction box */
		n=0;
		if ( (int) client_data == LINK )
		{
			XtSetArg( argList[n],XtNlabel, 
              "Select the elements\nto connect or\npress Reset to start over");

       		drawSwitch = WAIT_FIRST_PT;  
			setCursor(XS_DRAW);
		}
		else if ( (int) client_data == UNLINK )
		{
			XtSetArg( argList[n],XtNlabel, 
              "Select the elements\nto disconnect or\npress Reset to start over");
			drawSwitch = WAIT_FIRST_PT_UNLINK;  
			setCursor( XS_KILL);
		}
		n++;
		XtSetValues( instructDialog, argList, n);
		return;  /* don't want the continue because the code creates
					a new dialog box */
	}
	

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) DIALOG_POS_X,
			(Position) DIALOG_POS_Y, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(argList[n], XtNx, x);                         
    n++;
    XtSetArg(argList[n], XtNy, y);                         
    n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       argList, n);

    /* create dialog box */
    n=0;
    if ( (int) client_data == LINK )
    {
       XtSetArg( argList[n],XtNlabel, 
              "Select the elements\nto connect or\npress Reset to start over");
       drawSwitch = WAIT_FIRST_PT;  
	   setCursor(XS_DRAW);
    }
    else if ( (int) client_data == UNLINK )
    {
       XtSetArg( argList[n],XtNlabel, 
              "Select the elements\nto disconnect or\npress Reset to start over");
       drawSwitch = WAIT_FIRST_PT_UNLINK;  
	   setCursor( XS_KILL);
    }
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   argList, n);

    /* let processEvent() know we are waiting for 2 points in the pad */
    instructDialog = dialog;  /* global variable used to destroy prompt 
                               after drawing line */

    /* Add button */
    XawDialogAddButton(dialog, "Reset", drawReset,
                       (XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}
 
/* ----------------------------------------------------------------
    drawGrid

    Called by toggleGrid. Draws the grid on the screen.   
    --------------------------------------------------------------- */
void drawGrid()
{
    int x,y;
    int horizSkip,vertSkip;

       vertSkip = 10;
       horizSkip = ICON_SIZE;

       for( x=ICON_SIZE; x <= PAD_V_SIZE; x += horizSkip)
          for(y=5; y <=PAD_H_SIZE; y += vertSkip)
          { 
             XDrawPoint( theDisplay, padWindow,  theGC,x,y);
          }

       vertSkip = ICON_SIZE;
       horizSkip = 10;

       for( y=ICON_SIZE; y <= PAD_H_SIZE; y += vertSkip)
          for(x=5; x <=PAD_V_SIZE; x += horizSkip)
          { 
              XDrawPoint( theDisplay, padWindow,  theGC,x,y);
          }
}

/* ----------------------------------------------------------------
    toggleGrid 

    Called from draw menu. Callback procedure.

    Callback procedure.  
    If grid is on, turn it off.
    If grid is off, turn it on.

    client_data is unused
    --------------------------------------------------------------- */
void toggleGrid(w, client_data, call_data)
    Widget	w;		        
    XtPointer   client_data, call_data;	
{

    /* toggle the current value of gridDisplay */
    if( gridDisplay )  
       gridDisplay = FALSE;
    else  
       gridDisplay = TRUE;

    if( gridDisplay )  
       printf("Grid should be turned on\n"); 
    else  
       printf("Grid should be turned off\n"); 
	
	
    if (gridDisplay)
       drawGrid(); 
    else   /* grid should not be displayed */
       reDrawPad(NULL,NULL,NULL);

}


/* ----------------------------------------------------------------
   createDrawMenu

   Initialize widget to create a pulldown menu with a single entry
   "connect two elements".  Calls instructions().
   --------------------------------------------------------------- */
void createDrawMenu()
{

    Arg    argList[MAX_ARGS];  /* resource list  */
    int    i,n=0;              /* resource count */
    Widget dialog,             /* dialog box     */
	   popup,              /* Widget that contains the dialog box */
           entry,
           drawPulldownMenu;   /* Pull down menu for draw button */
    Position  x, y;            /* pixel location relative to 
                                  entire window */
    
    char *menu_item_names[] =
    {
	"Edit", "Connect", "Disconnect", "Grid","Refresh", NULL
    };

    n = 0;
    XtSetArg( argList[n], XtNfromHoriz, optMenuButton);
    n++;
    n++;
    XtSetArg( argList[n], XtNheight, BUTTON_H_SIZE);
    n++;
    XtSetArg( argList[n], XtNwidth, BUTTON_V_SIZE);
    n++;
    XtSetArg( argList[n], XtNmenuName, "drawMenu");
    n++;
    drawMenuButton = XtCreateManagedWidget("Draw",
         menuButtonWidgetClass, commands, argList, n);
    
    drawPulldownMenu = XtCreatePopupShell("drawMenu", simpleMenuWidgetClass, 
         drawMenuButton, NULL, ZERO);
    
    for (i = 0; i < (int) XtNumber(menu_item_names) ; i++) 
    {
	char * item = menu_item_names[i];
	entry = XtCreateManagedWidget(item, smeBSBObjectClass, 
                                      drawPulldownMenu,NULL, ZERO);

	/* these procedures are called when one of the menu entries
	   is selected */
	if      ( item == "Edit" )
		XtAddCallback(entry, XtNcallback, drawDestroyPopupPrompt,
			      (XtPointer) instructDialog);
	else if ( item == "Connect" )
		XtAddCallback(entry, XtNcallback, instructions, 
                              (XtPointer) LINK);
	else if ( item == "Disconnect" )
		XtAddCallback(entry, XtNcallback, instructions, 
                              (XtPointer) UNLINK);
	else if ( item == "Grid" )
		XtAddCallback(entry, XtNcallback, toggleGrid, 
                              (XtPointer) NULL);

	else if ( item == "Refresh" )
		XtAddCallback(entry, XtNcallback, reDrawPad, NULL );


    }
}
