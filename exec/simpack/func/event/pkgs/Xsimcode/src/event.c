
/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : event.c 12/1/91 22:02:19
**		Author    : Brian Harrington 
**		Purpose   : Main routine.  Initialize Xsimcode and 
**                          process X and X toolkit events.
**		Files Used:
**		History   :
**	origin:   8/14/90

   changes since ver1
   ------------------------------------------------------------------
   1/5   elminated triple sleep in initialization
   1/5   added debug switch
   3/3   modified processEvent to eliminate test for SINK
   6/22  bug fix for -d option
   10/28 changed terms to source, fork, and join
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)event.c	1.21 12/1/91 22:02:19";
#endif /* lint */
   


#include "modeller.h"




/* ================================================================
   EXTERNAL GLOBAL PROCEDURES
   ================================================================ */
extern void initG();
extern void initX();
extern void quitX( char *);
extern void convertXYtoPad( int, int, int *, int *);
extern Boolean padLocInUse( int, int);
extern Boolean padLocSpecail( int, int);
extern void writeMessage( char *);
extern void addMenu( int, int);
extern void modifyMenu( int, int);
extern void linkElements(void);
extern void removeLink(void);


/* ================================================================
   EXTERNAL GLOBAL VARIABLES
   ================================================================ */
   XtAppContext appCon;               
   extern Display      *theDisplay; /* X's display id          */
   extern GC           theGC;       /* X's graphics context id */
   extern Window       padWindow;   /* Window id of pad widget */
   extern Window       outerWindow;  

   extern struct Settings settings;

   extern char drawSwitch;   /* if the user is linking elements */
   extern int drawFromX,     /* "from" is the element the link  */
	      drawFromY,     /* comes from.  "To" is the element*/
	      drawToX,       /* that will be connected to the   */
	      drawToY;       /* "from" element.                 */


/* ================================================================
   PROTOTYPES
   ================================================================ */
void processEvent( int, int);

/* ================================================================
   GLOBAL VARIABLES
   ================================================================ */
char debug=FALSE;   /* command line arg */


/* ----------------------------------------------------------------
    mainEventLoop

    Processes both X and X toolkit events.  Scans events, looking
    for an X event in the user's pad.  If it finds one, then it
    calls processEvent, otherwise it assumes the toolkit can handle
    the other events.
    --------------------------------------------------------------- */
void mainEventLoop()

{
  XEvent  theEvent;     /* The next X event */
  int     X, Y;         /* location of mouse click */
  int     padx, pady;   /* row & column of mouse click */



   /* Select input from pad window only */
   XSelectInput( theDisplay, padWindow, EV_MASK);


   /* Process Events: X  & X toolkit. 
      Cannot use XtAppMainLoop( appCon ) since we need specific
      X events in the pad widget.  We need to know when the user
      clicks the mouse.                                           */

   while (TRUE)  /* forever */
   {
     XPeekEvent( theDisplay, &theEvent );
    
     /* is it a mouse event */
     if (( theEvent.type == ButtonPress ) &&

         /* is it for the pad */
         ( theEvent.xbutton.window == padWindow ))

     {
        /* get the X, Y location */
        XWindowEvent( theDisplay, padWindow, EV_MASK, &theEvent);
        X = theEvent.xkey.x;
	Y = theEvent.xkey.y;
	convertXYtoPad(X,Y, &padx, &pady );
	processEvent(X, Y );

     }

     /* is it an exposure event */
     else if (( theEvent.type == Expose ) &&
	     ( theEvent.xexpose.count == 0 ) ) 

       reDrawPad(NULL,NULL,NULL); 

       /* refresh pad; widgets (the buttons) automatically
			 redraw themselves */


     /* process X toolkit events no matter what */
     while (XtAppPending(appCon))
         XtAppProcessEvent(appCon, XtIMAll);
   }
}

/* ----------------------------------------------------------------
    processEvent

    Handle an X event that occurred in pad.  Pop up the appropriate
    menu (dialog box).  If the location has an element ask the 
    user if they want to edit or delete it.  If the location is
    empty, ask the user if they want to add an element.
    --------------------------------------------------------------- */
void processEvent(x,y)
   int     x,y;         /* pad location of mouse click in pixels */
{
   int     i,j;         /* pad location of mouse click in padElement[]*/   


   convertXYtoPad(x,y, &i, &j );

   switch( drawSwitch )
   {
      case OFF:  /* user is NOT linking elements, they must
			 want to add or edit an element  */

	if(debug)printf("drawSwitch = OFF\n");
/*
	 if ( padLocSpecial(i,j) )
	    writeMessage("You cannot modify the sink");
*/
	 if ( padLocInUse(i,j) )  /* delete or edit */
	    modifyMenu(x,y);   /* edit */
	 else
	    addMenu(x,y);      /* add */
	 break;

      case WAIT_FIRST_PT:  /* user is linking elements, this
				is the first point, the "from" */
	if(debug)printf("drawSwitch = WAIT_FIRST_PT\n");

	 if ( ! padLocInUse(i,j) )
	    writeMessage("That spot is empty. Please select an element");
	 else if ( padLocSpecial(i,j) )
	    writeMessage("Cannot connect FROM the sink");

         /* If its a facility ,fan-in point or the arrival point make 
            sure the out list is empty.  (Facilities, the arrival and Fan-out
            points can only be connected to ONE other element.) */

         else if ( padElement[i][j].elementType == FACILITY  &&
                   settings.facility[padElement[i][j].id].out != NULL )
            writeMessage("Facilities may only be connected to one element");

         else if ( padElement[i][j].elementType == FAN_IN_RP &&
                   settings.routing[padElement[i][j].id].out != NULL)
            writeMessage(
               "Join elments may only be connected to one element");

         else if ( padElement[i][j].elementType == GENERIC &&
                   settings.generic[padElement[i][j].id].out != NULL)
            writeMessage(
               "Generic elments may only be connected to one element");

         else if ( padElement[i][j].elementType == ARRIVAL &&
                   settings.arrival[1].out != NULL)
            writeMessage("The Source may only be connected to one element");

	 else /* everything is fine, save point */
	 {
	    drawFromX = x;
	    drawFromY = y;
	    drawSwitch = WAIT_SECOND_PT;
	 }
	 break;

      case WAIT_SECOND_PT:  /* user is linking elements, this
				is the second point, the "to" */
	setCursor( XS_BUSY );
	XFlush(theDisplay);
	if(debug)printf("drawSwitch = WAIT_SECOND_PT\n");

	 if ( ! padLocInUse(i,j) )
	    writeMessage("Please select an element");
	 else if ( i == SRC_X && j == SRC_Y )
	    writeMessage("Cannot connect TO the source");
	 else if ( drawFromX == x && drawFromY == y )
	    writeMessage("Cannot connect an element to itself");
	 else
	 {
	    drawToX = x;
	    drawToY = y;
	    drawSwitch = WAIT_FIRST_PT; /* wait for next pair of points*/
	    linkElements();  /* link the two elements */

	 }
	 setCursor( XS_DRAW );
	 break;

      case WAIT_FIRST_PT_UNLINK:  /* user is unlinking elements, this
				  is the first point, the "from" */

	if(debug)printf("drawSwitch = WAIT_FIRST_PT_UNLINK\n");

	 if ( ! padLocInUse(i,j) )
	    writeMessage("That spot is empty. Please select an element");

	 else /* everything is fine, save point */
	 {
	    drawFromX = x;
	    drawFromY = y;
	    drawSwitch = WAIT_SECOND_PT_UNLINK;
	 }
	 break;

      case WAIT_SECOND_PT_UNLINK:  /* user is unlinking elements, this
				is the second point, the "to" */

	if(debug)printf("drawSwitch = WAIT_SECOND_PT_UNLINK\n");

	 if ( ! padLocInUse(i,j) )
	    writeMessage("That spot is empty. Please select an element");
	 else
	 {
	    drawToX = x;
	    drawToY = y;
	    drawSwitch = WAIT_FIRST_PT_UNLINK; /* wait for the next 
						pair of points */
	    removeLink();  /* unlink the two elements */

	 }
	 break;
   }

}



/* ---------------------------------------------------------------
   main

   
   --------------------------------------------------------------- */

main (argc, argv)
int argc; char *argv[];

{
   char msg[MAX_CHARS_IN_WINDOW];
   char *name[] = {"Xsimcode"};
   char filename[MAX_UNIX_NAME];

   /* initialize display */
   initG();
   initX(1, &name);  /* set up X windows */

   /* get command line arguments */
   if (argc > 1) 
   {

      /* check for switches */
      if ( argv[1][0] == '-')
      {
	 if( strcmp( *++argv, "-d") == 0 )
	 {
	 	debug = TRUE;
	 }
      	 else
	 	quitX( "USAGE: Xsimcode [-d] [<filename>]");
	 argc--;
      }

      if ((argc >1) && (fileExists(*++argv)) )
      {
         if ( loadFile( *argv)  == ERR_OPEN_FILE_FOR_READ )
         {
            sprintf( msg, "Unable to open file %s.  File not loaded", *argv);
	    writeErrMessage( msg );
         }
         else
	 {
             writeMessage("New file loaded");
         }
      }
      else if (argc >1)/* the file does not exist */
      {
         sprintf( msg, "Unable to find file %s.  File not loaded", *argv);
         writeErrMessage( msg );
      }
   }


   sleep(4);
   reDrawPad(NULL,NULL,NULL);  /* clear screen */

   mainEventLoop();

}
 
