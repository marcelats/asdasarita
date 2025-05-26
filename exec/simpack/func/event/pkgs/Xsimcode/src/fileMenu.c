
/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : fileMenu.c 12/1/91 22:02:24
**		Author    : Brian Harrington 
**		Purpose   : 
**		Files Used:
**		History   :

   origin: 
      A simple Simple Menu Widget example.
      November 30, 1989 - Chris D. Peterson
      $XConsortium: xmenu1.c,v 1.8 89/12/15 19:33:15 kit Exp $
 
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)fileMenu.c	1.21 12/1/91 22:02:24";
#endif /* lint */

#include "modeller.h"

/* ================================================================
   EXTERNAL PROCEDURES 
   ================================================================ */
extern void quitX(char *);
extern Boolean fileExists( char *);
extern char saveFile( char *);
extern void writeMessage(char *);
extern void freeSettings();


/* ================================================================
   EXTERNAL GLOBAL VARIABLES
   ================================================================ */
extern Widget pad, commands, fileMenuButton, optMenuButton;
extern Widget topLevel;
extern XtAppContext appCon;               
extern struct Settings settings;
extern Pixmap fileMenuButtonPattern;

/* ================================================================
   PROTOTYPES
   ================================================================ */
void savePopupPrompt(Widget, XtPointer, XtPointer);
void saveChoice(Widget, XtPointer, XtPointer);
void loadReturn(Widget, XEvent*, String*, Cardinal*);
void saveReturn(Widget, XEvent*, String*, Cardinal*);
void overwriteTheFile(Widget, XtPointer, XtPointer);
void saveTheFile(Widget, XtPointer, XtPointer);
void DestroyPopupPrompt(Widget, XtPointer, XtPointer);


/* ================================================================
   GLOBAL VARIABLES
   ================================================================ */

   /* For dialog boxes -- handles return key */
   XtActionsRec actionTableFileMenu[] = 
   {
       {"loadReturn",	        loadReturn},
       {"saveReturn",	        saveReturn}
   };



/* ================================================================
   CALLBACK PROCEDURES 
   ================================================================ */

/* ----------------------------------------------------------------
    overwriteTheFile

    Called by Replace button on second popup for "SAVE AS" or
           by "SAVE".

    Callback procedure.  Called by clicking "REPLACE" on dialog box 
    for file save. Calls procedure to save the 
    file under the name given in settings.fileName.

    client_data contains fileName as char *
    --------------------------------------------------------------- */
void overwriteTheFile(w, client_data, call_data)
    Widget	w;		        /* "SAVE AS" widget */
    XtPointer   client_data, call_data;	
{

    Widget dialog,     /* dialog box                    */
           popup;      /* Widget that contains the dialog box */
    char msg[MAX_CHARS_IN_WINDOW];    /* error message   */

    /* Save file */
    if ( saveFile( (char *) client_data ) == ERR_OPEN_FILE_FOR_WRITE )
    {
        sprintf( msg, "Unable to open file %s.  File not saved",
		(char *) client_data);
	writeMessage( msg );
    }
    else
        writeMessage("Settings saved");

    /* Get rid of popup & dialog box, restore screen */
    popup = XtParent( XtParent(w) );
    XtDestroyWidget(popup);
}


/* ----------------------------------------------------------------
    savePopupPrompt

    Second popup prompt for "SAVE AS".  First popup for "SAVE".

    client_data: contains fileName as char *
    --------------------------------------------------------------- */
void savePopupPrompt(parent,client_data, call_data)
    Widget	parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg		args[5];       /* argument list                       */
    Widget	popup, dialog; /* new widgets                         */
    Position	x, y;          /* pixel position of upper left corner */
    Dimension	width, height; /* size of widget                      */
    Cardinal	n;             /* counter                             */
    char        userPrompt[MAX_DIALOG_WIDTH];  /* Question for user   */
    String fileName;           /* passed as input from user */


    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) 30, (Position) 30, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(args[n], XtNx, x);				n++;
    XtSetArg(args[n], XtNy, y);				n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       args, n);

    /* Create prompt */
    fileName = (char *) client_data;
    sprintf( userPrompt, "File \"%s\" exists.  Replace?", fileName);


    /* user input is from the dialog box */
    n=0;
    XtSetArg( args[n],XtNlabel, userPrompt);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   args, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "Replace", overwriteTheFile, 
                          (XtPointer) fileName);
    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
   quitChoice

   Called when "Quit" is selected on FILE menu.

	Arguments: w - the menu item that was selected.
                 junk, garbage - *** unused ***.
	Returns: 
   ---------------------------------------------------------------- */
void quitChoice(w, junk, garbage)
   Widget w;
   XtPointer junk, garbage;
{
       quitX(NULL);
}

/* ----------------------------------------------------------------
    quitPopupPrompt

    Called by pressing QUIT on FILE menu.

    client_data: unused
    --------------------------------------------------------------- */
void quitPopupPrompt(parent,client_data, call_data)
    Widget	parent;  /* dialog box that called this procedure */
    XtPointer client_data, call_data;
{
    Arg		args[5];       /* argument list                       */
    Widget	popup, dialog; /* new widgets                         */
    Position	x, y;          /* pixel position of upper left corner */
    Dimension	width, height; /* size of widget                      */
    Cardinal	n;             /* counter                             */
    char        userPrompt[MAX_DIALOG_WIDTH];  /* Question for user   */
    String fileName;           /* passed as input from user */


    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) 30, (Position) 30, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(args[n], XtNx, x);				n++;
    XtSetArg(args[n], XtNy, y);				n++;
    popup = XtCreatePopupShell("noPrompt", transientShellWidgetClass, pad,
			       args, n);

    /* user input is from the dialog box */
    n=0;
    XtSetArg( args[n],XtNlabel, "Are you sure you want to quit?");
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   args, n);

    /* Add 2 buttons */
    XawDialogAddButton(dialog, "Yes", quitChoice, NULL);
    XawDialogAddButton(dialog, "No", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}


/* ----------------------------------------------------------------
    saveTheFile

    Callback procedure.  Called by pressing SAVE on file menu or
    by clicking "DONE" or by pressing return in dialog box for 
    SAVE AS. Checks if file exists and 
    prompts to overwrite it.  Then, calls procedure to save the 
    file under the name given in settings.fileName.
    --------------------------------------------------------------- */
void saveTheFile(w, client_data, call_data)
    Widget	w;		        /* "SAVE AS" widget */
    XtPointer   client_data, call_data;	
{

    Widget dialog,     /* dialog box                    */
           popup;      /* Widget that contains the dialog box */
    String fileName;   /* input from user */
    char msg[MAX_CHARS_IN_WINDOW];    /* error message   */


    /* Get file name */
    dialog = (Widget) client_data;
    fileName = XawDialogGetValueString(dialog);

    /* Does the file exist ? */
    if (fileExists( fileName ))  /* ask user if they want to overwrite */
    {
       savePopupPrompt( XtParent( (Widget) client_data),
                             (XtPointer) fileName, call_data);
    }
    /* else save the file */
    else if ( saveFile( fileName ) == ERR_OPEN_FILE_FOR_WRITE )
    {
        sprintf( msg, "Unable to open file %s.  File not saved", fileName );
	writeMessage( msg );
    }

    
    /* Get rid of popup & dialog box, restore screen */
    popup = XtParent( (Widget) client_data);
    XtDestroyWidget(popup);

}

/* ----------------------------------------------------------------
    saveChoice

    Callback procedure.  Called by pressing SAVE on file menu.

    Checks if file exists and 
    prompts to overwrite it.  Then, calls procedure to save the 
    file under the name given in settings.fileName.
    --------------------------------------------------------------- */
void saveChoice(w, client_data, call_data)
    Widget	w;		        /* "SAVE AS" widget */
    XtPointer   client_data, call_data;	
{

    String fileName;   /* input from user */
    char msg[MAX_CHARS_IN_WINDOW];    /* error message   */


    /* Get file name */
    fileName = (char *) client_data;

    /* Does the file exist ? */
    if (fileExists( fileName ))  /* ask user if they want to overwrite */
    {
       savePopupPrompt( XtParent( (Widget) client_data),
                             (XtPointer) fileName, call_data);
    }
    /* else save the file */
    else if ( saveFile( fileName ) == ERR_OPEN_FILE_FOR_WRITE )
    {
        sprintf( msg, "Unable to open file %s.  File not saved", fileName );
	writeMessage( msg );
    }
    else
        writeMessage("Settings saved");
}

/* ----------------------------------------------------------------
    loadTheFile

    Calls procedure in file.c to load the new file.
    --------------------------------------------------------------- */
void loadTheFile(w, client_data, call_data)
    Widget	w;		        /* "SAVE AS" widget */
    XtPointer   client_data, call_data;	
{

    Widget dialog,     /* dialog box                    */
           popup;      /* Widget that contains the dialog box */
    String fileName;   /* input from user */
    char msg[MAX_CHARS_IN_WINDOW];    /* error message   */
int i,j;

    /* Get file name */
    dialog = (Widget) client_data;
    fileName = XawDialogGetValueString(dialog);

    freeSettings();  /* clear ALL settings */
    initG();         /* restore default settings */

    if ( loadFile( fileName ) == ERR_OPEN_FILE_FOR_READ )
    {
        sprintf( msg, "Unable to open file %s.  File not loaded", fileName);
	writeMessage( msg );
    }
    else
        writeMessage("New file loaded");

    reDrawPad(NULL,NULL,NULL);  /* clear screen */

    /* Get rid of popup & dialog box, restore screen */
    popup = XtParent( (Widget) client_data);
    XtDestroyWidget(popup);

}

/* ----------------------------------------------------------------
    SaveReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Calls saveTheFile.
    --------------------------------------------------------------- */

void saveReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    Widget dialog = XtParent(widget);
    saveTheFile(widget, (XtPointer) dialog, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    LoadReturn

    Callback procedure.  Called by pressing return in dialog box. 
    Calls loadTheFile.
    --------------------------------------------------------------- */

void loadReturn(widget, event, params, num_params)
    Widget widget;		
    XEvent *event;		
    String *params;	
    Cardinal *num_params;
{
    Widget dialog = XtParent(widget);
    loadTheFile(widget, (XtPointer) dialog, (XtPointer) NULL);
}

/* ----------------------------------------------------------------
    filePopupPrompt

    Called by "LOAD" & "SAVE AS".  Gets filename.

    client_data contains LOAD vs SAVE AS identifier as
       an int (defined in modeller.h)
    --------------------------------------------------------------- */
void filePopupPrompt(button, client_data, call_data)
    Widget	button;		
    XtPointer client_data, call_data;
{
    Arg		args[5];
    Widget	popup, dialog;
    Position	x, y;
    Dimension	width, height;
    Cardinal	n;

    /* Position dialog box in pad window */
    XtTranslateCoords(pad, (Position) 10, (Position) 10, &x, &y);

    /* Create a popup widget to hold dialog box */
    n = 0;
    XtSetArg(args[n], XtNx, x);				n++;
    XtSetArg(args[n], XtNy, y);				n++;

    /* Must use different widget name here so I can have 2 
       different entries in the translations tables if the users 
       hits return */
    if ( (int) client_data == SAVEAS )
         popup = XtCreatePopupShell("savePrompt", transientShellWidgetClass,
                                     pad, args, n);
    else
         popup = XtCreatePopupShell("loadPrompt", transientShellWidgetClass, 
                                     pad, args, n);

    /* user input is from the dialog box */
    n=0;
    XtSetArg( args[n],XtNlabel, "Filename ?");
    n++;
    XtSetArg( args[n],XtNvalue, settings.fileName);
    n++;
    dialog = XtCreateManagedWidget("dialog", dialogWidgetClass, popup,
				   args, n);

    /* Add 2 buttons */
    if ( (int) client_data == SAVEAS )
       XawDialogAddButton(dialog, "Done", saveTheFile, (XtPointer) dialog);
    else
       XawDialogAddButton(dialog, "Load", loadTheFile, (XtPointer) dialog);

    XawDialogAddButton(dialog, "Cancel", DestroyPopupPrompt,(XtPointer)dialog);

    XtPopup(popup, XtGrabNone);
}

/* ----------------------------------------------------------------
   newChoice

   Called when "New" is selected on FILE menu. Clears the data structure
   settings and the screen.

	Arguments: w - the menu item that was selected.
                 junk, garbage - *** unused ***.
	Returns: 
   ---------------------------------------------------------------- */
void newChoice(w, junk, garbage)
   Widget w;
   XtPointer junk, garbage;
{
   writeMessage("All settings cleared");
   freeSettings();  /* clear ALL settings */
   initG();         /* restore default settings */
   reDrawPad(NULL,NULL,NULL);  /* clear screen */
}


/* ----------------------------------------------------------------
    DestroyPopupPrompt

    Used by all popup's with "Cancel" button.
    --------------------------------------------------------------- */
/*	Function Name: DestroyPopupPrompt
 *	Description: Destroys the popup dialog widget.
 *	Arguments: w - *** UNUSED ***.
 *                 client_data - the dialog widget.  This widget is a direct
 *                               child of the popup shell to destroy.
 *                 call_data - *** UNUSED **.
 *	Returns: none.
 */

void DestroyPopupPrompt(widget, client_data, call_data)
    Widget	widget;		
    XtPointer client_data, call_data;	
{
/*
	extern Widget AddToggle, EditToggle;
*/
    
    Widget popup = XtParent( (Widget) client_data);
    XtDestroyWidget(popup);

/*
	XtUnmapWidget( AddToggle );
	XtUnmapWidget( EditToggle );
*/
}

/* ================================================================
   "MAIN"
   ================================================================ */


/* ----------------------------------------------------------------
    createFileMenu

    Create menu tree.  
    --------------------------------------------------------------- */

void createFileMenu()
{
    Arg          argList[MAX_ARGS];    /* resource list   */            
    Widget       firstLevelMenu,       
                 entry;
    int          i,n;                  /* counters */
    
    char * menu_item_names[] = {
        "New", "Load",	"Save", "Save As", "Quit", NULL
    };

    XtAppAddActions(appCon, actionTableFileMenu, 
                    XtNumber(actionTableFileMenu));

    /* Create menu button */
    n=0;
    XtSetArg( argList[n], XtNheight, BUTTON_H_SIZE);
    n++;
    XtSetArg( argList[n], XtNwidth, BUTTON_V_SIZE);
    n++;
    XtSetArg( argList[n], XtNmenuName, "fileMenu");
    n++;
    fileMenuButton = XtCreateManagedWidget("fileMenuButton", 
         menuButtonWidgetClass, commands, argList, n);
    
    firstLevelMenu = XtCreatePopupShell("fileMenu", simpleMenuWidgetClass, 
         fileMenuButton, NULL, ZERO);
    
    for (i = 0; i < (int) XtNumber(menu_item_names) ; i++) 
      {
	char * item = menu_item_names[i];
	entry = XtCreateManagedWidget(item, smeBSBObjectClass, firstLevelMenu,
				      NULL, ZERO);

        if      ( item == "New" )
	        XtAddCallback(entry, XtNcallback, newChoice, NULL);
        else if ( item == "Load" )
        	XtAddCallback(entry, XtNcallback, filePopupPrompt, 
                                (XtPointer) LOAD);
        else if ( item == "Save" )
        	XtAddCallback(entry, XtNcallback, saveChoice, 
                                (XtPointer) settings.fileName);
        else if ( item == "Save As" )
        	XtAddCallback(entry, XtNcallback, filePopupPrompt,
                                (XtPointer) SAVEAS);
        else if ( item == "Quit" )
        	XtAddCallback(entry, XtNcallback, quitPopupPrompt, NULL);
    }
}



