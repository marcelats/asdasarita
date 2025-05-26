/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : file.c 12/1/91 22:02:21
**		Author    : Brian Harrington 
**		Purpose   : Utility procedures to open, close and save files.
**		Files Used:
**		History   :
**                        : origin:  6/12/90
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)file.c	1.21 12/1/91 22:02:21";
#endif /* lint */

#include"modeller.h"


/* ===================================================================
   EXTERNAL GLOBAL VARIABLES - FROM OTHER FILES
   =================================================================== */
   /* Data structure that contains all the model parameters.  Created in
   create.h and initialized in initg */

extern char debug;
extern struct Settings settings;


/* ================================================================
   EXTERNAL PROCEDURES
   =============================================================== */
extern struct List * new();


/* ================================================================
   Global Variables 
   ================================================================ */
/* ================================================================
   PROTOTYPES
   ================================================================ */
void freeSettings();

/* -------------------------------------------------------------------
   fileExists

   Check if the given file exists.
   ------------------------------------------------------------------- */
Boolean fileExists( nameStr )
	char *nameStr;  /* name of file */
{

        char wholeNameStr[MAX_MODEL_NAME_SIZE+5];

   /* strcpy required -- a simple wholeNameStr = nameStr 
      would modify the char * nameStr! */
   strcpy( wholeNameStr, nameStr );    
   strcat( wholeNameStr, ".sim");  /* append .sim to end of file name */

   if (fopen(wholeNameStr, "r") == NULL) 
      return FALSE;
   else 
      return TRUE;
}


/* -------------------------------------------------------------------
   saveFile

   Save the data structure settings in the named file.  Save one
   setting per line.  Use NULL lines (blank lines) to indicate
   separation between parts of the data structure.
   ------------------------------------------------------------------- */
char saveFile( nameStr )
	char *nameStr;  /* name of file */
{
	FILE        *fp;          /* id of file call nameStr */
	struct List *ptr;         /* pointer to the list structure */
	int          i,j,         /* loop counter */
		     length=0,    /* length of file name */
		     err=NO_ERR;  /* error message to be returned */

   length = strlen( nameStr );
   strcat( nameStr, ".sim");  /* append .sim to end of file name */

   if ((fp = fopen(nameStr, "w")) == NULL)
   {
        nameStr[length] = '\0';   /* remove .sim from file name */
	err = ERR_OPEN_FILE_FOR_WRITE;
   }
      else
   {

	/* write data structure settings to the file */
        nameStr[length] = '\0';   /* remove .sim from file name */
	fprintf( fp, "%s\n", nameStr);
	fprintf( fp, "%f\n", settings.runTime);
	fprintf( fp, "%d\n", settings.mode );
	fprintf( fp, "%d\n", settings.trace_visual);
	fprintf( fp, "%d\n", settings.trace_facility);

	/* write list of facilities to be traced
           '0' is used for element_type to save code in loadFile */
	ptr = settings.fac_num;
	while (ptr != NULL)
	{
		fprintf( fp, "0\n");   /* element_type */
		fprintf( fp, "%d\n", ptr->id);
		ptr = ptr->next;
	}
	fprintf( fp, "%d\n", END_LIST );  /* end marker */

	fprintf( fp, "%d\n", settings.trace_eventlist);
	fprintf( fp, "%d\n", settings.trace_heap);
	fprintf( fp, "%d\n", settings.departure );
	fprintf( fp, "%d\n", settings.numFacilities );
	fprintf( fp, "%d\n", settings.numRoutingPoints );
	fprintf( fp, "%d\n", settings.report );

	/* write data for each facility */
	for (i=1; i<=MAX_ELEMENTS; i++)
	{
		if ( settings.facility[i].valid )
		{
			fprintf(fp, "%d\n",i);
			fprintf( fp, "%s\n", settings.facility[i].nameStr);
			fprintf( fp, "%d\n", settings.facility[i].numServers);
			fprintf( fp, "%d\n", settings.facility[i].typeRequest);
			fprintf( fp, "%d\n", settings.facility[i].distn);
			fprintf( fp, "%f\n", settings.facility[i].param1);
			fprintf( fp, "%f\n", settings.facility[i].param2);
			fprintf( fp, "%f\n", settings.facility[i].param3);

			/* write out list */
			ptr = settings.facility[i].out;
			while (ptr != NULL)
			{
				fprintf( fp, "%d\n", ptr->elementType);
				fprintf( fp, "%d\n", ptr->id);
                                fprintf( fp, "%d %d\n", ptr->i, ptr->j);
				ptr = ptr->next;
			}
			fprintf( fp, "%d\n", END_LIST );  /* end marker */
		}
	}
	fprintf( fp, "%d\n", END_SECTION );  /* end marker */


	/* write data for each generic */
	for (i=1; i<=MAX_ELEMENTS; i++)
	{
		if ( settings.generic[i].valid )
		{
			fprintf(fp, "%d\n",i);
			fprintf( fp, "%s\n", settings.generic[i].nameStr);

			/* write out list */
			ptr = settings.generic[i].out;
			while (ptr != NULL)
			{
				fprintf( fp, "%d\n", ptr->elementType);
				fprintf( fp, "%d\n", ptr->id);
                                fprintf( fp, "%d %d\n", ptr->i, ptr->j);
				ptr = ptr->next;
			}
			fprintf( fp, "%d\n", END_LIST );  /* end marker */
		}
	}
	fprintf( fp, "%d\n", END_SECTION );  /* end marker */


	/* write data for each arrival point in the model */
	/* currently limited to ONE */
	for (i=1; i<=MAX_ELEMENTS; i++)
	{
		if ( settings.arrival[i].valid )
		{
			fprintf( fp, "%d\n",i);
			fprintf( fp, "%d\n", settings.arrival[i].priority);
			fprintf( fp, "%d\n", settings.arrival[i].initialCount);
			fprintf( fp, "%d\n", settings.arrival[i].distn);
			fprintf( fp, "%f\n", settings.arrival[i].param1);
			fprintf( fp, "%f\n", settings.arrival[i].param2);
			fprintf( fp, "%f\n", settings.arrival[i].param3);

			/* Write the "out" list */
			ptr = settings.arrival[i].out;
			while (ptr != NULL)
			{
				fprintf( fp, "%d\n", ptr->elementType);
				fprintf( fp, "%d\n", ptr->id);
                                fprintf( fp, "%d %d\n", ptr->i, ptr->j);
				ptr = ptr->next;
			}
			fprintf( fp, "%d\n", END_LIST );  /* end marker */
		}
	}
	fprintf( fp, "%d\n", END_SECTION );  /* end marker */


	/* write data for each routing point in the model */
	for (i=1; i<=MAX_ELEMENTS; i++)
	{
		if ( settings.routing[i].valid )
		{
			fprintf( fp, "%d\n",i);
			fprintf( fp, "%d\n", settings.routing[i].distn);
			for( j=1; j <= MAX_WEIGHTS; j++ )
				fprintf( fp, "%f\n", settings.routing[i].weight[j]);

			/* Write "out" list */
			ptr = settings.routing[i].out;
			while (ptr != NULL)
			{
				fprintf( fp, "%d\n", ptr->elementType);
				fprintf( fp, "%d\n", ptr->id);
                                fprintf( fp, "%d %d\n", ptr->i, ptr->j);
				ptr = ptr->next;
			}
			fprintf( fp, "%d\n", END_LIST );  /* end marker */
		}
	}
	fprintf( fp, "%d\n", END_SECTION );  /* end marker */

       /* write padElements[][] to file */
       for ( i=1; i<PAD_ROWS; i++)
       {
          for( j=1; j< PAD_COLUMNS; j++ )
          {
	     if ( padElement[i][j].valid)
     	     {
   	        fprintf( fp, "%d %d\n",i,j);
	        fprintf( fp, "%d %d\n",padElement[i][j].elementType,
	           padElement[i][j].id);
             }
	  }
       }
       fprintf( fp, "%d\n", END_SECTION ); /* end marker */
       fclose( fp );
    }

   return err;
}

/* -------------------------------------------------------------------
   readList

   Load the data for a single "in" or "out" list.
   ------------------------------------------------------------------- */

void readList( head, fp)
	struct List **head;
	FILE *fp;
{
	Boolean moreData;
	struct List *ptr, *tailPtr;

		/* read "out" list */
		/* is there an "out" list ? */
		ptr = new();
		fscanf( fp, "%d\n", &(ptr->elementType));
		if ( ptr->elementType != -1 )
		{
			*head = ptr;  /* link element to array */
			fscanf( fp, "%d\n", &(ptr->id));
                        fscanf( fp, "%d %d\n", &(ptr->i), &(ptr->j));
			ptr = new();
			fscanf( fp, "%d\n", &(ptr->elementType));
			if ( ptr->elementType == -1 )  /* done */
				moreData = FALSE;
			else
			{
				moreData = TRUE;
				tailPtr = *head;  /* one element list */
			}

			/* get the elements in the "out" list */
			while( moreData )
			{
				fscanf( fp, "%d\n", &(ptr->id));
                                fscanf( fp, "%d %d\n", &(ptr->i), &(ptr->j));
				tailPtr->next = ptr;  /* attach new element */
				tailPtr = ptr; /* update tail of list */
				ptr = new();
				fscanf( fp, "%d\n", &(ptr->elementType));
				if ( ptr->elementType == -1 )  /* done */
					moreData = FALSE;
			}
		}
		else
			*head = NULL;
		free( ptr );
}

/* -------------------------------------------------------------------
   loadFile

   Load the data structure settings in the named file.
   ------------------------------------------------------------------- */
char loadFile( nameStr )
	char *nameStr;  /* name of file */
{
	FILE *fp;   /* id of file call nameStr */
	struct List *ptr;  /* pointer to the list structure */
	struct Settings *setPtr;   /* pointer to settings */
	int          i,           /* loop counter */
		     length=0,    /* length of file name */
		     err=NO_ERR,  /* error message to be returned */
		     j,type,id;   /* for padElements[][] vars */
	Boolean  moreData;

   if(debug)printf("in loadfile with filename = %s\n", nameStr);


   setPtr = &settings;

   length = strlen( nameStr );
   strcat( nameStr, ".sim");  /* append .sim to end of file name */

   if ((fp = fopen(nameStr, "r")) == NULL)
	err =  ERR_OPEN_FILE_FOR_READ;
   else
   {
	freeSettings();  /* clear data struct & free memory */

	/* read data structure settings to the file */
	fscanf( fp, "%s\n", setPtr->fileName);

	fscanf( fp, "%f\n", &(setPtr->runTime));
	fscanf( fp, "%d\n", &(setPtr->mode ));
	fscanf( fp, "%d\n", &(setPtr->trace_visual));
	fscanf( fp, "%d\n", &(setPtr->trace_facility));
        
        readList( &(setPtr->fac_num), fp );

	fscanf( fp, "%d\n", &(setPtr->trace_eventlist));
	fscanf( fp, "%d\n", &(setPtr->trace_heap));
	fscanf( fp, "%d\n", &(setPtr->departure ));
	fscanf( fp, "%d\n", &(setPtr->numFacilities));
	fscanf( fp, "%d\n", &(setPtr->numRoutingPoints));
	fscanf( fp, "%d\n", &(setPtr->report));

	/* read data for each facility */
	fscanf(fp, "%d\n", &i);  /* get array index */

	if ( i != -2 )
		moreData = TRUE;
	else
		moreData = FALSE;

	while ( moreData )
	{
		setPtr->facility[i].valid = TRUE;  /* reset valid bit */

		/* read data */
		fscanf( fp, "%s\n", setPtr->facility[i].nameStr);
		fscanf( fp, "%d\n", &(setPtr->facility[i].numServers));
		fscanf( fp, "%d\n", &(setPtr->facility[i].typeRequest));
		fscanf( fp, "%d\n", &(setPtr->facility[i].distn));
		fscanf( fp, "%f\n", &(setPtr->facility[i].param1));
		fscanf( fp, "%f\n", &(setPtr->facility[i].param2));
		fscanf( fp, "%f\n", &(setPtr->facility[i].param3));

		/* read "out" list */
		readList( &(setPtr->facility[i].out), fp );

		/* are we done ? */
		fscanf(fp, "%d\n", &i);  /* get array index */
		if ( i != -2 )
			moreData = TRUE;
		else
			moreData = FALSE;

	}

	/* read data for each generic */
	fscanf(fp, "%d\n", &i);  /* get array index */

	if ( i != -2 )
		moreData = TRUE;
	else
		moreData = FALSE;

	while ( moreData )
	{
		setPtr->generic[i].valid = TRUE;  /* reset valid bit */

		/* read data */
		fscanf( fp, "%s\n", setPtr->generic[i].nameStr);

		/* read "out" list */
		readList( &(setPtr->generic[i].out), fp );

		/* are we done ? */
		fscanf(fp, "%d\n", &i);  /* get array index */
		if ( i != -2 )
			moreData = TRUE;
		else
			moreData = FALSE;

	}


	/* read data for each arrival point */
	fscanf(fp, "%d\n", &i);  /* get array index */
	if ( i != -2 )
		moreData = TRUE;
	else
		moreData = FALSE;

	while ( moreData )
	{
		setPtr->arrival[i].valid = TRUE;  /* reset valid bit */

		/* read data */
		fscanf( fp, "%d\n", &(setPtr->arrival[i].priority));
		fscanf( fp, "%d\n", &(setPtr->arrival[i].initialCount));
		fscanf( fp, "%d\n", &(setPtr->arrival[i].distn));
		fscanf( fp, "%f\n", &(setPtr->arrival[i].param1));
		fscanf( fp, "%f\n", &(setPtr->arrival[i].param2));
		fscanf( fp, "%f\n", &(setPtr->arrival[i].param3));

		/* read "out" list */
		readList( &(setPtr->arrival[i].out), fp );

		/* are we done ? */
		fscanf(fp, "%d\n", &i);  /* get array index */
		if ( i != -2 )
			moreData = TRUE;
		else
			moreData = FALSE;

	}

	/* read data for each routing point */
	fscanf(fp, "%d\n", &i);  /* get array index */
	if ( i != -2 )
		moreData = TRUE;
	else
		moreData = FALSE;

	while ( moreData )
	{
		setPtr->routing[i].valid = TRUE;  /* reset valid bit */

		/* read data */
		fscanf( fp, "%d\n", &(setPtr->routing[i].distn));
		for( j=1; j <= MAX_WEIGHTS; j++ )
			fscanf( fp, "%f\n", &(setPtr->routing[i].weight[j]));

		/* read "out" list */
		readList( &(setPtr->routing[i].out), fp );

		/* are we done ? */
		fscanf(fp, "%d\n", &i);  /* get array index */
		if ( i != END_SECTION )
			moreData = TRUE;
		else
			moreData = FALSE;
	}



	/* read padElements[][] from file */
	fscanf( fp, "%d", &i );
	while( i != END_SECTION )
	{
	   fscanf( fp, "%d\n", &j);
	   fscanf( fp, "%d %d\n", &type, &id);
	   padElement[i][j].elementType = type;
	   padElement[i][j].id =id;
           padElement[i][j].valid = TRUE;
	   fscanf( fp, "%d", &i );
	}
        fclose( fp );
   }


   /* remove .sim from file name */
   nameStr[length] = '\0';


   return err;
}

/* -------------------------------------------------------------------
   freeList

   Free the memory used by the linked list in the "in" or "out"
   list for facilities, arrival points or routing points.
   ------------------------------------------------------------------- */

void freeList( head)
	struct List **head;  /* "handle": pointer to a pointer
				allows procedure to update the
				data structure and not just a copy of
				it */
{
	struct List *ptr,
		    *next;  /* pointers to elements in the list */

	ptr = *head;
	next = ptr;

	while( ptr != NULL )  /* loop through list, freeing memory */
	{
		next = ptr->next;
		free( ptr );
		ptr = next;
	}
	*head = NULL;
}

/* -------------------------------------------------------------------
   freeSettings

   Free up memory space used by pointers in the data structure
   settings.  Also invalidate entries in the array.  This procedure
   is used in preparation to load a new file.
   ------------------------------------------------------------------- */

void freeSettings()
{
	int     i,j;  /* loop counters */

	/* clear "settings" data structure */
	for (i=1; i<=MAX_ELEMENTS; i++)
	{
		/* reset valid 'bit' in data structure &
		   free memory used by linked lists */
		if (settings.facility[i].valid )
		{
			settings.facility[i].valid = FALSE;
			freeList( &(settings.facility[i].out) );
		}

		if (settings.arrival[i].valid )
		{
			settings.arrival[i].valid = FALSE;
			freeList( &(settings.arrival[i].out) );
		}

		if (settings.routing[i].valid )
		{
			settings.routing[i].valid = FALSE;
			freeList( &(settings.routing[i].out) );
		}
	}

}






