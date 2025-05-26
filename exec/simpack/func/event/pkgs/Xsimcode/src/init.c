
/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : init.c 12/1/91 22:02:35
**		Author    : Brian Harrington 
**		Purpose   : Initialization routines for X Toolkit 
                            windows & for the simcode translator.
**		Files Used:
**		History   :
   origin:   3/90 (as memo.c from UnixWorld tutorial)

   changes since ver1
   ------------------------------------------------------------------
   1/5 support for using return in dialog boxes for padMenu.c
   11/1 changed default to display grid
   
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)init.c	1.21 12/1/91 22:02:35";
#endif /* lint */


#include "modeller.h"
#include "blankIcon.h"
#include "drawIcon.h"
#include "facilityIcon.h"
#include "fanInIcon.h"
#include "fanOutIcon.h"
#include "fileIcon.h"
#include "genericIcon.h"
#include "goIcon.h"
#include "optionIcon.h"
#include "sinkIcon.h"
#include "srcIcon.h"


/* ================================================================
   External Global Variables & Procedures
   ================================================================ */
extern void createFileMenu();
extern void createOptMenu();
extern void createDrawMenu();
extern void quitX( char *);
extern void displayPixmap( int, int, int);
extern void generateCode();
extern void writeMessage(char *);
struct Settings settings;

/* 
extern Widget AddToggle;
*/

/* ================================================================
   Global Variables 
   ================================================================ */
   struct Settings settings;
   XtAppContext appCon;               
   Display *theDisplay; /* X's display id */
   GC       theGC;      /* X's graphics context id */
   Window   padWindow;  /* Window id of pad widget */
   Window   outerWindow=NULL;  /* the outer most Window */
   Cursor   theBusyCursor;  /* a stop watch */
   Cursor   theKillCursor;  /* a skull and crossbones */
   Cursor   theDrawCursor;  /* a pencil */
   int      gridDisplay;  /* TRUE if the grid should be displayed */

   /* Widgets used in the program */
   Widget       topLevel,    /* Top Level Shell widget */
                windowW,     /* Contains all other widgets */
                commands,    /* Contains the buttons */
                fileMenuButton,  /* Press for user menu */
                optMenuButton,   /* option menu */
		drawMenuButton,  /* Press to link elements */
		goButton,        /* Press to generate C code */
                pad,         /* Displays Simpack Models     */
                msgBox;      /* Displays messages for user */

   /* Pixmaps for Icons used thoroughout program */
   Pixmap       blankPattern,            /* blankIcon */
                srcPattern,              /* sourceIcon */
                sinkPattern,             /* sinkIcon   */
                facilityPattern,         /* facilityIcon   */
                fanInPattern,            /* fanInIcon   */
                fanOutPattern,           /* fanOutIcon   */
                genericPattern,           /* genericIcon   */
                fileMenuButtonPattern,   /* fileIcon */
                optionMenuButtonPattern, /* optionIcon */
                drawMenuButtonPattern,   /* connecting Icon */
                goMenuButtonPattern,     /* translate to C Icon */
                pgmIconPattern;          /* program's icon */



/* ----------------------------------------------------------------
    goCallback
  
    Called when the goButton is pressed. Generate C code.
    --------------------------------------------------------------- */

void goCallback(widget, client_data, call_data)

   Widget  widget;      /* the widget in which the event occurred */
   XtPointer client_data; /* Data provide by the appln */
   XtPointer call_data;   /* Data provide by the widget */
  
{
   int i;

   /* reset case numbers -- needed if user translates same model twice
      in same Xsimcode session */
   for( i=0; i<=MAX_ELEMENTS; i++)
   {
      settings.facility[i].caseNum = 0;
      settings.routing[i].caseNum = 0;
   }

   generateCode();

}




/* -------------------------------------------------------------------
   initG

   Initialize the data structure settings.  These are the default
   settings used for generating simpack code.
   ------------------------------------------------------------------- */

void initG()
{
	char nameString[8];
	int i,j;              /* loop counters */

	strcpy( settings.fileName, "model");
	settings.mode = HEAP;
	settings.trace_visual = NONE;
	settings.trace_facility = OFF;
	settings.fac_num = NULL;
	settings.trace_eventlist = OFF;
	settings.departure = ABSORB;
	settings.numFacilities = 0;
	settings.numRoutingPoints = 0;
	settings.numGenericPoints = 0;
	settings.runTime = 100.0;
	settings.report = ON;
	settings.fac_num = NULL;

	/* Initialize the facility, arrival and routing points to
	their default settings.  Note that if a user does not
	change these settings, they'll be used to generate the model */

	for( i=0; i<=MAX_ELEMENTS; i++)
	{
		/* Model is initally empty */
		settings.arrival[i].valid = FALSE;
		settings.routing[i].valid = FALSE;                           
		settings.facility[i].valid = FALSE;
		settings.generic[i].valid = FALSE;

		/* Give each facility a name */
		sprintf( nameString, "FAC%d", i);
		strcpy( settings.facility[i].nameStr, nameString);

		settings.facility[i].numServers = 1;
		settings.facility[i].typeRequest = REQUEST;
		settings.arrival[i].priority = 0;
		settings.arrival[i].initialCount = 1;

		/* Set default distribution */
		settings.facility[i].distn = CONSTANT;
		settings.facility[i].param1 = 1.0;
		settings.facility[i].param2 = 0.0;
		settings.facility[i].param3 = 0.0;
		settings.facility[i].caseNum = 0;

		/* Give each generic block a name */
		sprintf( nameString, "GEN%d", i);
		strcpy( settings.generic[i].nameStr, nameString);
		settings.facility[i].caseNum = 0;

		settings.arrival[i].distn = CONSTANT;
		settings.arrival[i].param1 = 2.0;
		settings.arrival[i].param2 = 0.0;
		settings.arrival[i].param3 = 0.0;

		settings.routing[i].distn = CUMULATIVE;
		for ( j= 1; j <= MAX_WEIGHTS; j++ )
			settings.routing[i].weight[j] = 0.0;
		settings.routing[i].caseNum = 0;

		/* For safety's sake */
		settings.arrival[i].out = NULL;
		settings.facility[i].out = NULL;
		settings.generic[i].out = NULL;
		settings.routing[i].out = NULL;
	}

	for (i=0; i<PAD_ROWS; i++)
	   for (j=0; j<PAD_COLUMNS; j++)
	      padElement[i][j].valid = FALSE;

	/* Default is one arrival */
	settings.arrival[1].valid = TRUE;
        padElement[SRC_X][SRC_Y].valid = TRUE;
        padElement[SRC_X][SRC_Y].elementType = ARRIVAL;
        padElement[SRC_X][SRC_Y].id = 1;

	padElement[SINK_I][SINK_J].valid = TRUE;
	padElement[SINK_I][SINK_J].elementType = SINK;
  
}

/* ----------------------------------------------------------------
   createXWindow

   Create a window from the a widget.  Give the window a graphics
   context and a background.
   ---------------------------------------------------------------- */
void createXWindow()
{
   int     *theScreen;  /* Widget's screen  */
   XSetWindowAttributes theWindowAttributes;
   unsigned long        theWindowMask;

   Arg       argList[MAX_ARGS];    /* resource list   */            
   Pixmap    theIconPixmap;        /* Xlib version of the bitmap */
   XGCValues theGCValues;          /* return value from XCreateGC */
   unsigned long        theBlackPixel;
   unsigned long        theWhitePixel;

   /* Bitmap vars for menuButton*/
   unsigned int width, heigth;       /*  unused */
   Pixmap menuPattern;      /* Pixmap copy of menuIcon */
   Pixmap testPatternSrc;   /* Pixmap copy of theIcon */
   int xHotSpot, yHotSpot;  /* unused */

   outerWindow = XtWindow( windowW );
   padWindow   = XtWindow( pad );
   theDisplay  = XtDisplay( pad );
   theScreen   = ( int *)XtScreen( pad ); 

   /* Create a graphics context */
   theGC = XCreateGC( theDisplay, padWindow, (unsigned long) 0,
                      &theGCValues);
   if( theGC == 0 ) 
      quitX("initX couldn't get a graphic context");

   /* Specify colors for  GC */
   theBlackPixel = BlackPixel( theDisplay, *theScreen);
   theWhitePixel = WhitePixel( theDisplay, *theScreen);
   XSetForeground( theDisplay, theGC, theBlackPixel);
   XSetBackground( theDisplay, theGC, theWhitePixel);

/*
   XFlush( theDisplay );
*/
}

/* ----------------------------------------------------------------
   readBitmaps

   Read in bitmaps for use later.
   ---------------------------------------------------------------- */
void readBitmaps()
{
   unsigned int width, heigth;     /*  unused */
   int xHotSpot, yHotSpot;         /* unused */
   Arg argList[MAX_ARGS];
   int i,j;                        /* loop counters */

   width = 50;
   heigth = 50;

   /* Read in Bitmaps we'll need later */
   fileMenuButtonPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		fileIcon_bits, width, heigth);
   optionMenuButtonPattern = XCreateBitmapFromData( theDisplay, padWindow,
		optionIcon_bits, width, heigth);
   drawMenuButtonPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		drawIcon_bits, width, heigth);
   goMenuButtonPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		goIcon_bits, width, heigth);
   blankPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		blankIcon_bits, width, heigth);
   srcPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		srcIcon_bits, width, heigth);
   sinkPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		sinkIcon_bits, width, heigth);
   facilityPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		facilityIcon_bits, width, heigth);
   fanInPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		fanInIcon_bits, width, heigth);
   fanOutPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		fanOutIcon_bits, width, heigth);
   genericPattern = XCreateBitmapFromData( theDisplay, padWindow, 
		genericIcon_bits, width, heigth);

   XtSetArg(argList[0], XtNbitmap, fileMenuButtonPattern);
   XtSetValues( fileMenuButton, argList, 1);
   XtSetArg(argList[0], XtNbitmap, optionMenuButtonPattern);
   XtSetValues( optMenuButton, argList, 1);
   XtSetArg(argList[0], XtNbitmap, drawMenuButtonPattern);
   XtSetValues( drawMenuButton, argList, 1);
   XtSetArg(argList[0], XtNbitmap, goMenuButtonPattern);
   XtSetValues( goButton, argList, 1);

/* 
   XtSetArg(argList[0], XtNbitmap, facilityPattern);
   XtSetValues( AddToggle, argList, 1);
*/
}

/* ----------------------------------------------------------------
   createCursors 

    Create the cursors for the program 
   ---------------------------------------------------------------- */
void createCursors()
{
	unsigned int theBusyCursorShape=XC_watch;
	unsigned int theKillCursorShape=XC_pirate;
	unsigned int theDrawCursorShape=XC_pencil;

	theBusyCursor=XCreateFontCursor(
		theDisplay, theBusyCursorShape);
	theKillCursor=XCreateFontCursor(
		theDisplay, theKillCursorShape);
	theDrawCursor=XCreateFontCursor(
		theDisplay, theDrawCursorShape);
        CurrentCursor = XS_DEFAULT;
}

/* ----------------------------------------------------------------
    makeIcon 

    Create an icon for the program. 
   ---------------------------------------------------------------- */
void makeIcon()
{
    XWMHints theWMHints;
    
    theWMHints.icon_pixmap = pgmIconPattern; 
    theWMHints.initial_state = NormalState; 
    theWMHints.flags = IconPixmapHint | StateHint; 
    XSetWMHints( theDisplay, outerWindow, &theWMHints );
}
/* ----------------------------------------------------------------
    createGoMenu

    Create menu tree.  
    --------------------------------------------------------------- */

void createGoMenu()
{
    Arg          argList[MAX_ARGS];    /* resource list   */            
    Widget       firstLevelMenu,       
                 entry;
    int          i,n;                  /* counters */
    
    char * menu_item_names[] = {
        "Translate", NULL
    };

    /* Create Button to generate C code */
    n=0;
    XtSetArg( argList[n], XtNfromHoriz, drawMenuButton);
    n++;
    XtSetArg( argList[n], XtNheight, BUTTON_H_SIZE);
    n++;
    XtSetArg( argList[n], XtNwidth, BUTTON_V_SIZE);
    n++;
    XtSetArg( argList[n], XtNmenuName, "goMenu");
    n++;
    goButton = XtCreateManagedWidget("Go", menuButtonWidgetClass,
                   commands, argList, n);

    firstLevelMenu = XtCreatePopupShell("goMenu", simpleMenuWidgetClass, 
         goButton, NULL, ZERO);
    
    for (i = 0; i < (int) XtNumber(menu_item_names) ; i++) 
      {
	char * item = menu_item_names[i];
	entry = XtCreateManagedWidget(item, smeBSBObjectClass, firstLevelMenu,
				      NULL, ZERO);
        if      ( item == "Translate" )
	        XtAddCallback(entry, XtNcallback, goCallback, NULL);

    }
}





/* ----------------------------------------------------------------
   Createwidgets

   Create the widgets used by the 
   program.  Although the program makes Xlib and Xtoolkit calls,
   the program is initialized as a toolkit application.  'Low level
   X calls are only used when necessary.

   For simplicity, all of the Widget id's are global to this file.


   **hierarchy of widgets used**

   topLevel
      windowW
         commands
            fileMenuButton
	    optMenuButton
            drawMenuButton
            goButton
         pad
         msgbox
   ---------------------------------------------------------------- */

void createWidgets()
{

   Arg          argList[MAX_ARGS];    /* resource list   */            
   int          n;                    /* argument count  */
   char         displayString[MAX_CHARS_IN_WINDOW];  /* message for user */

   /* This widget contains all other widgets */
   n=0;
   windowW = XtCreateManagedWidget( "Big Window", formWidgetClass, 
      topLevel,argList,n);

   /* Create Widget to Hold Menus & Buttons */
   n=0;
   XtSetArg( argList[n], XtNborderWidth, 0);
   n++;
   commands = XtCreateManagedWidget( "commands", formWidgetClass, windowW,
                                   argList,n);

   /* Create Menus */
   createFileMenu();
   createOptMenu();
   createDrawMenu(); 
   createGoMenu();
/* 
	createAddToggle();
	createEditToggle();
*/
   initPadMenu();

   /* Create message box */
   n = 0;
   sprintf( displayString, "%s", 
      "Welcome to XSimCode--A Simpack Code Generator");
   XtSetArg( argList[n], XtNlabel, displayString);
   n++;
   XtSetArg( argList[n], XtNfromVert, commands);
   n++;
   XtSetArg( argList[n], XtNwidth, PAD_V_SIZE);
   n++;
   msgBox = XtCreateManagedWidget("message", labelWidgetClass,
                   windowW, argList, n);

   /* Create the user's working area: the "pad" */
   n=0;
   XtSetArg( argList[n], XtNfromVert, msgBox);
   n++;
   XtSetArg( argList[n], XtNheight, PAD_H_SIZE);
   n++;
   XtSetArg( argList[n], XtNwidth, PAD_V_SIZE);
   n++;
   pad = XtCreateManagedWidget("pad", formWidgetClass, windowW, 
                argList, n);

}

/* ----------------------------------------------------------------
   initX

   Create a window using the X Toolkit    
   ---------------------------------------------------------------- */

void initX( argc, argv)
   int argc;
   char *argv[];
{ 
   int i,j;

   /* default values used by widgets */
   String fallbackResources[] = 
   {
     "*icon_pixmap:	./facilityIcon",
     "*.resizable:              False",
     "*.font:                   -*-helvetica-bold-r-normal--12-*", 
#ifdef COLOR_DISPLAY
     /* For Color workstations. */
     "*menu.menuLabel.foreground:    Blue",
     "*menu*quit.foreground:	    Green",
     "*menu*item1.foreground:        Red",
     "xmenu1*menu*item2.foreground:  White",
     "*menu*item3.foreground:        Blue",
     "*menu*item4.foreground:	    Red",
#endif /* COLOR_DISPLAY */
     "*input: True",
     "*prompt*value: ",
     "*savePrompt*value.translations: #override \\n <Key>Return: saveReturn()",
     "*loadPrompt*value.translations: #override \\n <Key>Return: loadReturn()",
     "*fileNamePrompt*value.translations: #override \\n <Key>Return: fileNameReturn()",
     "*runTimePrompt*value.translations: #override \\n <Key>Return: runTimeReturn()",
     "*changeFacPrompt*value.translations: #override \\n <Key>Return: changeFacReturn()",
     "*namePrompt*value.translations: #override \\n <Key>Return: nameReturn()",
     "*serversPrompt*value.translations: #override \\n <Key>Return: serverReturn()",
     "*paramPrompt*value.translations: #override \\n <Key>Return: paramReturn()",
     "*countPrompt*value.translations: #override \\n <Key>Return: countReturn()",
     "*priorityPrompt*value.translations: #override \\n <Key>Return: priorityReturn()",
     "*functionPrompt*value.translations: #override \\n <Key>Return: functionReturn()",
	"*bitmapFilePath   /cis/lightning0/beh/simulation/proj",
     NULL,
   };

   gridDisplay = TRUE; /* default is the grid on */

   /* Initialize  the X Toolkit */
   topLevel = XtAppInitialize(&appCon, "XSimCode", NULL, 0, &argc, argv, 
			      fallbackResources, NULL, 0);
   /*  Create Widgets */
   createWidgets();

   /* Display the window */
   XtRealizeWidget(topLevel);

   /* Find the window id of the pad (widget) */
   createXWindow(); 

   /* Read bitmaps for use by widgets  & Add initial ones */
   readBitmaps();
 
    /* establish an icon for the program */
/*
    makeIcon();
*/

    /* create special cursors */ 
    createCursors();

}
