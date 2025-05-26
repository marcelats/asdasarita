/**********************************************************************
			     	- NOTICE -
             Source code owned by Brian Harrington (c) 1991 
	      May be freely distributed for non-profit use.
***********************************************************************
**
**		Name/Date : list.c 12/1/91 22:02:38
**		Author    : Brian Harrington 
**		Purpose   : 
**		Files Used:
**		History   :
**
**********************************************************************/
#ifndef lint 
        static char sccs_id[] = "@(#)list.c	1.21 12/1/91 22:02:38";
#endif /* lint */

/*

	list.c
	Brian Harrington
	origin:  4/30/90  (for X Simpack)
	version: 6/22/91

        Linked list functions.
*/


#include"modeller.h"



/* ----------------------------------------------------------------
   createList

   Initialize head to start of empty list.
   ---------------------------------------------------------------- */
void createList( head )
	struct List *head;
{
	head = NULL;
}

/* ----------------------------------------------------------------
   new

   Uses malloc to allocate a new element to the list. Set the
   element's next pointer is set to NULL.
   -----------------------------------------------------------------*/
struct List* new()
{
   struct List* ptr; /* ptr: pointer to new list element */

   ptr = (struct List*) malloc( sizeof( struct List ));
   if (ptr == NULL) fprintf(stderr, "Error: Out of Memory\n");

   /* initialize */
   ptr->next = NULL;
   return(ptr);
}

/* ----------------------------------------------------------------
   addToList

   Adds an element to the FRONT of a linked list.
   -----------------------------------------------------------------*/
void addToList( head, newElem)
   struct List **head;     /*  pointer to pointer of head of list   */
   struct List  *newElem;  /*  new list element to be added to list */
{
   struct List* ptr;       /*  pointer to list element */

   ptr = *head;   /* save original list */
   *head = newElem;    /* add new element */
   newElem->next = ptr;   /* concatenate rest of list */
}

/* ----------------------------------------------------------------
   findElement

   Find a pointer to an element in a linked list and a pointer to 
   the previous element.

   Returns elem & prevElem.
      1) elem == NULL  => element is not found
      2) prevElem == NULL => element found & is first on list
      3) prevElem != NULL => element found & not first on list
   -----------------------------------------------------------------*/
void findElement( head, id, elem, prevElem)
   struct List  *head;     /*  head of list to be searched        */
   int           id;       /*  the element we're looking for      */
   struct List  **elem;     /*  pointer to the element             */
   struct List  **prevElem; /*  pointer to the element before elem */
{
   *prevElem = NULL;  /* in case list has 0 or 1 items */
   *elem = head;      /* NULL if list is empty */


      /* search list */
      while ( (*elem != NULL) &&      /* not the end of the list */
              ((**elem).id != id))    /* element not found */
      {
	  *prevElem = *elem;
	  *elem = (**elem).next;
      }
}

/* ----------------------------------------------------------------
   findElementByType

   Find a pointer to an element in a linked list and a pointer to 
   the previous element.  Searching for a specific id and type.

   Returns elem & prevElem.
      1) elem == NULL  => element is not found
      2) prevElem == NULL => element found & is first on list
      3) prevElem != NULL => element found & not first on list
   -----------------------------------------------------------------*/
void findElementByType( head, type, id, elem, prevElem)
   struct List  *head;     /*  head of list to be searched        */
   int           type;     /*  ARRIVAL, FAN_IN_RP, FAN_OUT_RP, 
                                or FACILILTY */
   int           id;       /*  the element we're looking for      */
   struct List  **elem;     /* pointer to the element             */
   struct List  **prevElem; /* pointer to the element before elem */
{
   *prevElem = NULL;  /* in case list has 0 or 1 items */
   *elem = head;      /* NULL if list is empty */


      /* search list */
      while ( (*elem != NULL) &&      /* not the end of the list */
              ( (**elem).id != id ||
                (**elem).elementType != type ))    /* element not found */
      {
	  *prevElem = *elem;
	  *elem = (**elem).next;
      }
}

/* ----------------------------------------------------------------
   removeFromList

   Remove an element from the list.  This procedure assumes that
   elem is NOT NULL (that the given element is in the list).
   -----------------------------------------------------------------*/
void removeFromList( head, elem, prevElem )
   struct List **head;     /*  pointer to pointer of head of list   */
   struct List  *elem;     /*  list element to be removed           */
   struct List  *prevElem; /*  list element before the element
					    to be removed           */

{
   struct List *ptr;       /*   pointer to element is list          */

   if ( prevElem == NULL )  /* element first on list */
   {
	if (  (*head)->next == NULL )
	{
		/* one item list */
		free( *head );
		*head = NULL;
	}
	else /* multi item list */
	{
		*head = elem->next;
		free( elem );
	}
   }
   else /*  ( prevElem != NULL ) => element not first */
   {
	/* list length > 1 */
	prevElem->next = elem->next;
	free( elem );
   }
}

/* ----------------------------------------------------------------
   printList 

   For debugging
   -----------------------------------------------------------------*/
void printList( head )
   struct List *head;     /*  pointer of head of list   */
{
   char tempStr[20];
   int i=1;

   while( head != NULL )
   {
      switch ( head->elementType )
      {
         case ARRIVAL: strcpy( tempStr, "ARRIVAL"); break;
         case GENERIC: strcpy( tempStr, "GENERIC"); break;
         case FACILITY: strcpy( tempStr, "FACILITY"); break;
         case FAN_IN_RP: strcpy( tempStr, "FAN_IN_RP"); break;
         case FAN_OUT_RP: strcpy( tempStr, "FAN_OUT_RP"); break;
         case SINK: strcpy( tempStr, "SINK"); break;
      }
      printf("Element %d is %s at pos %d in padElements[%d][%d]\n",
         i++,tempStr, head->id, head->i,head->j);
      head = head->next;
   }
}
