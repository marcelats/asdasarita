/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : utility.c 12/1/91 22:02:56
**		Author    : Brian Harrington 
**		Purpose   : Procedures used by the graphical side of 
**                          Xsimcode. They involve the user's drawing 
**                          area (the pad ).
**		Files Used:
**		History   :
**                        :origin:   8/14/90
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)utility.c	1.21 12/1/91 22:02:56";
#endif /* lint */

#include "modeller.h"

/* ================================================================
   EXTERNAL PROCEDURES 
   ================================================================ */
   void quitX( char *);
   extern void drawGrid();

/* ================================================================
   EXTERNAL GLOBAL VARIABLES
   ================================================================ */
   Widget   msgBox;     /* window with msg for user */
   extern Display *theDisplay; /* X's display id */
   extern GC       theGC;      /* X's graphics context id */
   extern Window   padWindow,  /* Window id of pad widget */
                   outerWindow;
   extern Cursor   theBusyCursor,
                   theDrawCursor,
                   theKillCursor;
   extern char debug;	
   
   extern int gridDisplay;  /* global boolean for grid on or off */ 
   extern struct Settings settings;

   /* Pixmaps for Icons used thoroughout program */
   Pixmap       blankPattern,            /* blankIcon */
                srcPattern,              /* sourceIcon */
                sinkPattern,             /* sinkIcon   */
                facilityPattern,         /* facilityIcon   */
                fanInPattern,            /* fanInIcon   */
                fanOutPattern,           /* fanOutIcon   */
                genericPattern,           /* genericIcon   */
                fileMenuButtonPattern,   /* fileIcon */
                optionMenuButtonPattern; /* optionIcon */



/* ================================================================
   GLOBAL VARIABLES
   ================================================================ */

/* ================================================================
   PROTOTYPES
   ================================================================ */


/* ---------------------------------------------------------------
   quitX

   Closes down the connection to the X server.  If there was a 
   fatal error, print the error message.
   --------------------------------------------------------------- */
void quitX( errorStr )
   char errorStr[];
{

  if ( errorStr != NULL) 
     fprintf(stderr, "FATAL ERROR: %s\n", errorStr);
  
  XCloseDisplay( theDisplay );
  exit(0);
}



/* ---------------------------------------------------------------
   writeMessage

   Display a given message in the message window.
   --------------------------------------------------------------- */
void writeMessage( msgStr )
   char msgStr[];
{
	Arg     argList[MAX_ARGS]; /* resource list */
	int     n=0;               /* # of args     */

	XtSetArg( argList[n], XtNlabel, msgStr);
	n++;
	XtSetValues( msgBox, argList, n);
	sleep(2);
}

/* ---------------------------------------------------------------
   writeErrMessage

   Display a given message in the message window.
   --------------------------------------------------------------- */
void writeErrMessage( msgStr )
   char msgStr[];
{
	Arg     argList[MAX_ARGS]; /* resource list */
	int     n=0;               /* # of args     */

	XtSetArg( argList[n], XtNlabel, msgStr);
	n++;
	XtSetArg( argList[n], XtNborderColor, (Pixel) 4);
	n++;
	XtSetValues( msgBox, argList, n);
	sleep(2);
}



/* ----------------------------------------------------------------
   convertXYtoPad

   Translate an (x,y) coordinate in the Pad window into the
   appropriate row and column of the padElement data structure.  The
   user's pad is sub-divided into ICON_SIZE squares.
   ---------------------------------------------------------------- */
void convertXYtoPad( x,y, padX, padY)
   int x, y;          /* input */
   int *padX, *padY;  /* output */
{
/*   *padX = (x-1) / ICON_SIZE + 1;
   *padY = (y-1) / ICON_SIZE + 1;
*/
   *padY = (x-1) / ICON_SIZE + 1;
   *padX = (y-1) / ICON_SIZE + 1;

  
}


/* ----------------------------------------------------------------
   convertPadtoIcon

   Translate an (i,j) pair of indices for the padElements[][] data 
   structure to the appropriated (x,y) coordinate to display a
   icon. (Upper left hand corner)
   ---------------------------------------------------------------- */
void convertPadtoIcon( i,j, iconX, iconY)
   int i,j;             /* input */
   int *iconX, *iconY;  /* output */
{
/*   *iconX = (x-1) * ICON_SIZE + 1;
   *iconY = (y-1) * ICON_SIZE + 1;
*/
   *iconX = (j-1) * ICON_SIZE + 5;
   *iconY = (i-1) * ICON_SIZE + 5;
}


/* ----------------------------------------------------------------
   convertPadtoStartLine

   Translate an (i,j) pair of indices for the padElements[][] data 
   structure to the appropriated (x,y) coordinate to display the 
   beginning of a line. 
   ---------------------------------------------------------------- */
void convertPadtoStartLine( i,j, iconX, iconY)
   int i,j;             /* input */
   int *iconX, *iconY;  /* output */
{

   /* don't allow line to go through the icon */
/*
   *iconX = (j-1) * ICON_SIZE + ICON_SIZE - 16;
   *iconY = (i-1) * ICON_SIZE + ICON_SIZE / 2;
*/
   *iconX = (j-1) * ICON_SIZE + ICON_SIZE - 13;
   *iconY = (i-1) * ICON_SIZE + ICON_SIZE / 2;
}
/* ----------------------------------------------------------------
   convertPadtoEndLine

   Translate an (i,j) pair of indices for the padElements[][] data 
   structure to the appropriated (x,y) coordinate to display the 
   end of a line. 
   ---------------------------------------------------------------- */
void convertPadtoEndLine( i,j, iconX, iconY)
   int i,j;             /* input */
   int *iconX, *iconY;  /* output */
{
/*
   *iconX = (j-1) * ICON_SIZE + 16;
   *iconY = (i-1) * ICON_SIZE + ICON_SIZE / 2;
*/
   *iconX = (j-1) * ICON_SIZE + 13;
   *iconY = (i-1) * ICON_SIZE + ICON_SIZE / 2;
}

/* ----------------------------------------------------------------
   convertStrToType

   Translate a string name into a #define (enumerated type) value.
   Returns 
      #define of distribution (see modeller.h) or
      0 if the str is not matched.
   ---------------------------------------------------------------- */
int convertStrToType( String str )
{
   int type;

   /* distributions */
   if ( strcmp(str, "Normal") == 0)
      type = NORMAL;
   else if ( strcmp(str, "Constant") == 0)
      type = CONSTANT;
   else if ( strcmp(str, "Uniform") == 0)
      type = UNIFORM;
   else if ( strcmp(str, "Random") == 0)
      type = RANDOM;
   else if ( strcmp(str, "Exponential") == 0)
      type = EXPONENTIAL;
   else if ( strcmp(str, "Erlang") == 0)
      type = ERLANG;
   else if ( strcmp(str, "Hyperx") == 0)
      type = HYPERX;
   else if ( strcmp(str, "Triangle") == 0)
      type = TRIANGLE;
   else if ( strcmp(str, "Cumulative") == 0)
      type = CUMULATIVE;

   /* parmeters */
   else if ( strcmp(str, "Param 1") == 0)
      type = 1;
   else if ( strcmp(str, "Param 2") == 0)
      type = 2;
   else if ( strcmp(str, "Param 3") == 0)
      type = 3;

   /* request types */
   else if ( strcmp(str, "Request") == 0)
      type = REQUEST;
   else if ( strcmp(str, "Preempt") == 0)
      type = PREEMPT;

   else
      type = 0;  /* Error */

   return type;
}


/* ----------------------------------------------------------------
   padLocInUse

   Check if a pad location is being used.
   ---------------------------------------------------------------- */
Boolean padLocInUse( padX, padY)
   int padX, padY;  /* pad location in array */
{

   if ( padElement[padX][padY].valid == TRUE )
      return TRUE;
   else
      return FALSE;
}


/* ----------------------------------------------------------------
   padLocSpecial

   Check if a pad location is the sink.
   ---------------------------------------------------------------- */
Boolean padLocSpecial( padX, padY)
   int padX, padY;  /* pad location in array */
{

   if ((padX == SINK_I) && (padY == SINK_J)) 
	return TRUE;
   else
	return FALSE;
}

/* ----------------------------------------------------------------
   setCursor 

	Change the cursor to newCursor. The global enumeration
    CurrentCursor keeps track of which cursor we are currently using. 
   ---------------------------------------------------------------- */
void
setCursor( newCursor )
   int newCursor;
{
	if( outerWindow != NULL )
	{
		if(debug)printf("setting cursor to %d\n", newCursor);
		switch( newCursor )
   		{
			case XS_DEFAULT: 
				XUndefineCursor(theDisplay, outerWindow);
				break;
			case XS_KILL:
				XDefineCursor(theDisplay, outerWindow, theKillCursor);
				break;
			case XS_DRAW:
				XDefineCursor(theDisplay, outerWindow, theDrawCursor);
				break;
			case XS_BUSY:
				XDefineCursor(theDisplay, outerWindow, theBusyCursor);
				break;
		}
	}
   CurrentCursor = newCursor;
}
/* ----------------------------------------------------------------
   displayPixmap

   Display the desired pixmap at the given location.
   ---------------------------------------------------------------- */
void displayPixmap( choice, x, y)
   int  choice;   /* describes selected pixmap */
                  /* actual pixmaps are global vars read in 
                     readBitmaps() in initx.c  */
   int  x,y;      /* position of bitmap */
{
   Pixmap pattern;
   unsigned int width, heigth;  /* unused */

   switch (choice)
   {
      case ARRIVAL:     pattern = srcPattern;  break;
      case SINK:       pattern = sinkPattern; break; 
      case BLANK:      pattern = blankPattern; break;
      case FACILITY:   pattern = facilityPattern; break;
      case FAN_IN_RP:  pattern = fanInPattern; break;
      case FAN_OUT_RP: pattern = fanOutPattern; break;
      case GENERIC:    pattern = genericPattern; break;

      default:
	quitX("Error in displayPixmap()"); break;

   }

   XCopyPlane( theDisplay, pattern, padWindow, theGC, 0,0,
               (unsigned int) WIDTH_ICON, 
               (unsigned int) HEIGTH_ICON, x,y, 0x01);

/*   sleep(DELAY); *//* required */
   XFlush( theDisplay );
}

/* ----------------------------------------------------------------
   fastDisplayPixmap

   Display the desired pixmap at the given location.  "Fast" 
   because it doesn't sleep or do an XFlush, this must be done
   by the calling procedure.
   ---------------------------------------------------------------- */
void fastDisplayPixmap( choice, x, y)
   int  choice;   /* describes selected pixmap */
                  /* actual pixmaps are global vars read in 
                     readBitmaps() in initx.c  */
   int  x,y;      /* position of bitmap */
{
   Pixmap pattern;
   unsigned int width, heigth;  /* unused */
   char errStr[MAX_CHARS_IN_WINDOW];

   switch (choice)
   {
      case ARRIVAL:    pattern = srcPattern;  break;
      case SINK:       pattern = sinkPattern; break; 
      case BLANK:      pattern = blankPattern; break;
      case FACILITY:   pattern = facilityPattern; break;
      case FAN_IN_RP:  pattern = fanInPattern; break;
      case FAN_OUT_RP: pattern = fanOutPattern; break;
      case GENERIC:    pattern = genericPattern; break;

      default:    
           sprintf(errStr,"Error in fastDisplayPixmap() with choice = %d",
                   choice);
           quitX(errStr); break;

   }

   XCopyPlane( theDisplay, pattern, padWindow, theGC, 0,0,
               (unsigned int) WIDTH_ICON, 
               (unsigned int) HEIGTH_ICON, x,y, 0x01);
 }

void printOutList(void)  /*debugging only */
{
    int i;struct List *ptr;

    printf("facilities\n");
    for(i=1;i<=MAX_ELEMENTS;i++)
      if( settings.facility[i].valid)
      {
        printf("%d : ",i);
        ptr=settings.facility[i].out;
        while( ptr != NULL )
	{
           printf("(%d,%d) ",ptr->elementType,ptr->id);
           ptr = ptr->next;
	}
        printf("\n");
      }
    printf("routing\n");
    for(i=1;i<=MAX_ELEMENTS;i++)
      if( settings.routing[i].valid)
      {
        printf("%d : ",i);
        ptr=settings.routing[i].out;
        while( ptr != NULL )
	{
           printf("(%d,%d) ",ptr->elementType,ptr->id);
           ptr = ptr->next;
	}
        printf("\n");
      }
}

   


/* ----------------------------------------------------------------
   reDrawPad

   Refresh the screen.
   ---------------------------------------------------------------- */
void reDrawPad(w, client_data, call_data)
    Widget	w;		        
    XtPointer   client_data, call_data;	/* unused */
{
   int i,j;  /* position in padElements[][] */
   int x,y;  /* pixel position in pad       */
   struct List *ptr; /* pointer to out list */
   int oldCursor;  /* the cursor before its changed to busy */

   oldCursor = CurrentCursor;
   setCursor( XS_BUSY );

   XClearWindow( theDisplay, padWindow );  /* clear the pad */

   XFlush( theDisplay );

   /* draw the grid ?*/
   if( gridDisplay )
      drawGrid();

   /* draw the elements */
   for (i=0;i<PAD_ROWS; i++)
   {
     for( j=0; j<PAD_COLUMNS; j++ )
     {
        if( padElement[i][j].valid)
	{

           /* draw the icon */
           convertPadtoIcon( i,j, &x, &y );
           fastDisplayPixmap( padElement[i][j].elementType, x,y);
        }
      }
   }

   /* draw the links */
   for (i=0;i<PAD_ROWS; i++)
   {
     for( j=0; j<PAD_COLUMNS; j++ )
     {

        if( padElement[i][j].valid)
	{

           /* draw connections to other elements */
           switch( padElement[i][j].elementType )
	   {
	      case FACILITY:
                 ptr = settings.facility[padElement[i][j].id].out;
                 break;
 
  	      case FAN_IN_RP: 
              case FAN_OUT_RP: 
                 ptr = settings.routing[padElement[i][j].id].out;
                 break;

              case ARRIVAL: 
		 ptr = settings.arrival[padElement[i][j].id].out;
                 break;

              case SINK:
                 ptr = NULL;  /* no connects begin at sink */
                 break;

              case GENERIC:
                 ptr = settings.generic[padElement[i][j].id].out;
                 break;

              default:
                 quitX("Trouble in reDrawPad");
	    }

            /* loop through the outlist redrawing each connection */    
            while( ptr != NULL )
            {
               drawLine( i,j, ptr->i, ptr->j );
               ptr = ptr->next;
	    }
        }
      }
   }

/*   sleep(DELAY);  */
/* required */
   XFlush( theDisplay ); 
   setCursor( oldCursor );
}
     
   
