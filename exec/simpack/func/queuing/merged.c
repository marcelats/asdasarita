/***************************************************************************/
/* CODE FOR IMPLEMENTING NINE NEW DATA STRUCTURES FOR USE WITH THE SIMPACK */
/* QUEUING LIBRARY.  CODED BY DANIEL HAY.                                  */
/* IMPLEMENTS: SPLAY TREES
               PAIRED HEAPS
               HENRIKSON'S ALGORITHM
               SKEWED UP HEAPS
               SKEWED DOWN HEAPS
               BINOMIAL FORESTS
               PAGODAS
               LEFTIST TREES
               TWOLIST STRUCTURE                                           */
/* PLEASE SEE THE README.DATA FILE FOR IMPORTANT INFORMATION BEFORE USING! */

#include "mytypes.h"

/************************/
/* SPLAY TREE SECTION   */
/************************/

void yinitqueue(q) 
cqueue *q; 
/*  initialize a variable of type queue  */ 
{ 
  *q = NULL; 
} 

void yenqueue(nn, q) 
ITEM nn; 
cqueue *q; 
{ 
  /*  the rightmost item in the left tree  */ 
  cnoderef left;
  /*  the leftmost item in the right tree  */ 
  cnoderef right;
  /*  the root of that part of the tree not yet split  */ 
  cnoderef next;
  cnoderef temp, n;
  /*  the time of n  */ 
  double nprio;
  n = (struct cnode *)malloc(sizeof(struct cnode));
  n->element = nn;
  next = *q; 
  *q = n; 
  if (next == NULL) {   /*  trivial enqueue  */ 
    n->leftlink = NULL; 
    n->rightlink = NULL; 
  }
  else {   /*  difficult enqueue  */ 
    nprio = n->element.time; 
    left = n; 
    right = n; 
    /*  n's left and right children will hold the right and left
    splayed trees resulting from splitting on n^.prio;
    note that the children will be reversed!   */ 
    if (next->element.time > nprio) goto label_2;
label_1:   /*  assert next^.prio <= nprio  */ ; 
    do {   /*  walk to the right in the left tree  */ 
      temp = next->rightlink; 
      if (temp == NULL) { 
        left->rightlink = next; 
        right->leftlink = NULL; 
        goto label_999;  /*  job done, entire tree split  */ 
      } 
      if (temp->element.time > nprio) { 
        left->rightlink = next; 
        left = next; 
        next = temp; 
        goto label_2;  /*  change sides  */ 
      } 
      next->rightlink = temp->leftlink; 
      left->rightlink = temp; 
      temp->leftlink = next; 
      left = temp; 
      next = temp->rightlink; 
      if (next == NULL) { 
        right->leftlink = NULL; 
        goto label_999;  /*  job done, entire tree split  */ 
      } 
      /*  change sides  */ 
    }  while (next->element.time <= nprio) ; 
label_2:   /*  assert next^.prio > nprio  */ ; 
    do {   /*  walk to the left in the right tree  */ 
      temp = next->leftlink; 
      if (temp == NULL) { 
        right->leftlink = next; 
        left->rightlink = NULL; 
        goto label_999;  /*  job done, entire tree split  */ 
      } 
      if (temp->element.time <= nprio) { 
        right->leftlink = next; 
        right = next; 
        next = temp; 
        goto label_1;  /*  change sides  */ 
      } 
      next->leftlink = temp->rightlink; 
      right->leftlink = temp; 
      temp->rightlink = next; 
      right = temp; 
      next = temp->leftlink; 
      if (next == NULL) { 
        left->rightlink = NULL; 
        goto label_999;  /*  job done, entire tree split  */ 
      } 
      /*  change sides  */ 
    }  while (next->element.time > nprio) ; 
    goto label_1;
label_999:   /*  split is done, branches of n need reversal  */ ; 
    temp = n->leftlink; 
    n->leftlink = n->rightlink; 
    n->rightlink = temp; 
  } 
} 

ITEM ydequeue(q) 
cqueue *q; 
{
  /*  the next item to deal with  */ 
  cnoderef next;
  cnoderef temp;
  /*  nodes to the left of next or q  */ 
  cnoderef left, farleft, farfarleft;
  ITEM dummy;
  next = *q; 
  left = next->leftlink; 
  if (left == NULL) {
    temp = next;
    *q = next->rightlink;
    dummy = temp->element;
    free(temp);
    return dummy;
  } 
  else for (;;) { 
    /*  next is not it, left is not NULL, might be it  */ 
    farleft = left->leftlink; 
    if (farleft == NULL) { 
      temp = left;
      next->leftlink = left->rightlink;
      dummy = temp->element;
      free(temp);
      return dummy;
    } 
    /*  next, left are not it, farleft is not nil, might be it  */ 
    farfarleft = farleft->leftlink; 
    if (farfarleft == NULL) { 
      temp = farleft;
      left->leftlink = farleft->rightlink;
      dummy = temp->element;
      free(temp); 
      return dummy;
    } 
    /*  next, left, farleft are not it, rotate  */ 
    next->leftlink = farleft; 
    left->leftlink = farleft->rightlink; 
    farleft->rightlink = left; 
    next = farleft; 
    left = farfarleft; 
  } 
} 


/* ysearch looks for the node in the tree with n as its token number
   and assigns parent nodes along the way.  Ultimately will return a 
   pointer to the node being sought */

cnoderef ysearch(n,q)
int n;
cnoderef q;
{
  cnoderef temp;
  if (q == NULL) return NULL;
  if ((int)q->element.token.attr[0] == n) return q;
  /* try the leftlink in the tree */
  temp = ysearch(n,q->leftlink);
  if (temp != NULL) {
    q->leftlink->parent = q;
    return temp;
  }
  /* didn't find it, so try the rightlink */
  temp = ysearch(n,q->rightlink);
  if (temp != NULL) {
    q->rightlink->parent = q;
    return temp;
  }
  /* didn't find it, return NULL */
  return NULL;
}


/* yswap is a misnomer, it merely assigns the 2nd argument to point to the
   first argument, and the first to point to the third.  Saves a little typing
   later.  */

void yswap(q1,q2,q3)
cnoderef *q1,*q2,*q3;
{
  *q2=(*q1);
  *q1=(*q3);
}


/* ysplay will splay a tree at a node q, according to the splaying formula */

void ysplay(q,q2)
cnoderef *q,*q2;
{
  for (;;) {  /* do this until you hit the root */
    if (*q == *q2) return; /* you are there */
    if ((*q)->parent == *q2) { /* you are one under the root */
      if ((*q)->parent->leftlink == (*q))
        yswap(&((*q)->rightlink),&((*q)->parent->leftlink),&((*q)->parent));
      else
        yswap(&((*q)->leftlink),&((*q)->parent->rightlink),&((*q)->parent));
      *q2 = *q;
      return;
    }

  /* according to splaying, if you are the same child type as your parent,
     you rotate the parent and grandparent nodes, then the current node and
     parent nodes. */
    if ((((*q)->parent->parent->leftlink == (*q)->parent) &&
        ((*q)->parent->leftlink == (*q))) ||
        (((*q)->parent->parent->rightlink == (*q)->parent) &&
        ((*q)->parent->rightlink == (*q)))) {
      if ((*q)->parent->leftlink == (*q)) {
        yswap(&((*q)->parent->rightlink),
              &((*q)->parent->parent->leftlink),&((*q)->parent->parent));
        yswap(&((*q)->rightlink),&((*q)->parent->leftlink),&((*q)->parent));
      }
      else {
        yswap(&((*q)->parent->leftlink),&((*q)->parent->parent->rightlink),
              &((*q)->parent->parent));
        yswap(&((*q)->leftlink),&((*q)->parent->rightlink),&((*q)->parent));
      }
    }

  /* if you and your parent are different child types, then rotate this node
     and its parent first, then rotate this node and the grandparent */
    else {
      if ((*q)->parent->rightlink == (*q)) {
        yswap(&((*q)->leftlink),&((*q)->parent->rightlink),&((*q)->parent));
        yswap(&((*q)->rightlink),&((*q)->parent->parent->leftlink),
              &((*q)->parent->parent));
      }
      else {
        yswap(&((*q)->rightlink),&((*q)->parent->leftlink),&((*q)->parent));
        yswap(&((*q)->leftlink),&((*q)->parent->parent->rightlink),
              &((*q)->parent->parent));
      }
    }
  /* now, move the current node up the appropriate number of places */
    if ((*q)->parent->parent->parent == NULL) *q2 = *q;
    else {
      if ((*q)->parent->parent->parent->leftlink == (*q)->parent->parent)
        (*q)->parent->parent->parent->leftlink = *q;
      else (*q)->parent->parent->parent->rightlink = *q;
      (*q)->parent = (*q)->parent->parent->parent;
    }
  }
}


/* yjoin will merge two trees, either of which or both of which can be NULL,
   under the assumption that all the nodes in q2 are greater than all the nodes
   in q1 */

cnoderef yjoin(q1,q2)
cnoderef *q1;
cnoderef *q2;
{ 
  cnoderef temp,temp2;
  if (*q1 == NULL) return *q2;
  else if (*q2 == NULL) return *q1;
  else {
    (*q1)->parent = NULL; /* mark a finishing place */
    temp2 = *q1;
    temp = *q1;
  /* slide down the right child of the first tree */
    while (temp->rightlink != NULL) { 
      temp->rightlink->parent = temp;
      temp = temp->rightlink;
    }
  /* now bring this node to the top of the tree by splaying, knowing that
     there are only two possibilities, either the parent node is a right 
     child, or it is the root */
    while (temp->parent != NULL) {
      if (temp->parent == temp2) 
        yswap(&(temp->leftlink),&(temp2->rightlink),&(temp2));
      else {
        yswap(&(temp->parent->leftlink),&(temp->parent->parent->rightlink),
              &(temp->parent->parent));
        yswap(&(temp->leftlink),&(temp->parent->rightlink),&(temp->parent));
        temp->parent = temp->parent->parent->parent;
        if (temp->parent != NULL) temp->parent->rightlink = temp;
      }
    }
  /* now, hang q2 on the right child of the first tree */
    temp->rightlink = *q2;
    return temp;
  }
}


/* yrmqueue will remove the node with token number n from the splay tree q */

ITEM yrmqueue(n,q)
int n;
cqueue *q;
{
  cnoderef temp,temp2,temp4;
  ITEM temp3;
  /* if the current root is the correct node, replace it with the merge of 
     its two children */
  if ((int) (*q)->element.token.attr[0] == n) {
    temp3 = (*q)->element; 
    temp4 = *q;
    *q = yjoin(&((*q)->leftlink),&((*q)->rightlink));
    free(temp4);
    return temp3;
  }
  /* otherwise, find the node, replace it with the merge of its two children,
     then splay at the parent node */
  else {
    (*q)->parent = NULL;
    temp = ysearch(n,*q);
    temp3 = temp->element;
    temp2 = yjoin(&(temp->leftlink),&(temp->rightlink));
    if (temp->parent->leftlink == temp) temp->parent->leftlink = temp2;
    else temp->parent->rightlink = temp2;
    ysplay(&(temp->parent),&(*q));
    free(temp);
    return temp3;
  }
}

void yclearqueue(q)
cnoderef *q;
{
  if (*q == NULL) return;
  yclearqueue(&(*q)->leftlink);
  yclearqueue(&(*q)->rightlink);
  free(*q);
}

/************************/
/*  PAIRED HEAP SECTION */
/************************/

void ainitqueue(q) 
pqueue *q; 
/*  initialize a variable of type queue  */ 
{ 
  *q = NULL; 
} 

void aenqueue(nn, q) 
ITEM nn; 
pqueue *q; 
{ 
  pnoderef n;
  n = (struct pnode *)malloc(sizeof(struct pnode));
  n->element = nn;
  n->flag = 0;
  if (*q == NULL) {   /*  trivial enqueue  */ 
    n->downlink = NULL; 
    *q = n; 
  } 
  else {   /*  consider n to be a minimal heap, pair it with q  */ 
    if ((*q)->element.time <= n->element.time) {   
      /*  q remains the root  */ 
      n->downlink = NULL; 
      n->leftlink = (*q)->downlink; 
      (*q)->downlink = n; 
    } 
    else {   /*  n becomes the new root  */ 
      (*q)->leftlink = NULL; 
      n->downlink = *q; 
      *q = n; 
    } 
  } 
} 

ITEM adequeue(q) 
pqueue *q; 
{   
  /*  pointer to list of pairs  */ 
  pnoderef head;
  /*  pointer to next unpaired subtree  */ 
  pnoderef next;
  /*  working pointers for pairing operation  */ 
  pnoderef a, b;
  pnoderef temp;
  ITEM dummy;
  temp = *q;
  if (*q != NULL) {   /*  have work to do  */ 
    next = (*q)->downlink; 
    head = NULL; 
    while (next != NULL) {   /*  make list of pairs  */ 
      a = next; 
      next = a->leftlink; 
      if (next != NULL) { 
        b = next; 
        next = b->leftlink; 
        /*  pair up a and b  */ 
        if (a->element.time <= b->element.time) { 
          b->leftlink = a->downlink; 
          a->downlink = b; 
          a->leftlink = head; 
          head = a; 
        } 
        else { 
          a->leftlink = b->downlink; 
          b->downlink = a; 
          b->leftlink = head; 
          head = b; 
        } 
      } 
      else {   /*  put single left over node on pair list  */ 
        a->leftlink = head; 
        head = a; 
      } 
    } 
    /*  compute new head of queue  */ 
    a = head; 
    if (a != NULL) { 
      head = a->leftlink; 
      while (head != NULL) {   /*  link up list entries with a  */ 
        b = head; 
        head = b->leftlink; 
        if (a->element.time <= b->element.time) { 
          b->leftlink = a->downlink; 
          a->downlink = b; 
        } 
        else { 
          a->leftlink = b->downlink; 
          b->downlink = a; 
          a = b; 
        } 
      } 
    } 
    *q = a;
  }
  dummy = temp->element;
  free(temp);
  return dummy;
} 


/* findnode will search for a node specified by token number n and will
   ultimately return a pointer to the parent of the node */

pnoderef findnode(flag,n,q)
int *flag;
int n;
pqueue *q;
{
  pnoderef tempnode;
  /* the sought after node is the leftlink in this structure */
  if (((*q)->leftlink != NULL) && 
     ((int)(*q)->leftlink->element.token.attr[0] == n)) {
    *flag = 1;
    return *q;
  }
  /* the sought after node is the downlink in this structure */
  else if (((*q)->downlink!=NULL) && 
   ((*q)->downlink->element.token.attr[0]==n)) {
    *flag = 0;
    return *q;
  }
  /* we've come upon a dead end */
  else if (((*q)->downlink == NULL) && ((*q)->leftlink == NULL)) {
    *flag = 2;
    return NULL;
  }
  else {
    /* try to find it in the downlink */
    if ((*q)->downlink != NULL) 
      tempnode = findnode(flag,n,&((*q)->downlink));
    else *flag = 2;
    if (*flag != 2) return tempnode;
    else { 
      /* try to find it in the leftlink */
      if ((*q)->leftlink != NULL) 
        tempnode = findnode(flag,n,&((*q)->leftlink)); 
      else *flag = 2; 
    }
    if (*flag != 2) return tempnode;
    else return NULL;
  }
}


/* armqueue will arbitrarily delete the node with token number n from the
   paired heap q */

ITEM armqueue(n,q)
int n;
pqueue *q;
{
  pnoderef parentnode,leftnode;
  ITEM temp;
  int flag=0;
  /* if the node is at the head of the queue, do a dequeue */
  if ((int) (*q)->element.token.attr[0] == n) return adequeue(q);
  /* otherwise, find the node, replace it with the dequeue of the
     subtree that starts with the to-be-deleted node */
  else {
    parentnode = findnode(&flag,n,q);
    if (flag==0) {
      leftnode = parentnode->downlink->leftlink;
      parentnode->downlink->leftlink = NULL;
      temp = adequeue(&(parentnode->downlink));
      if (parentnode->downlink == NULL) 
        parentnode->downlink = leftnode;
      else parentnode->downlink->leftlink = leftnode;
    }
    else {
      leftnode = parentnode->leftlink->leftlink;
      parentnode->leftlink->leftlink = NULL;
      temp = adequeue(&(parentnode->leftlink));
      if (parentnode->leftlink == NULL)
        parentnode->leftlink = leftnode;
      else parentnode->leftlink->leftlink = leftnode;
    }
    return temp;
  }
}

void aclearqueue(q)
pnoderef *q;
{
  if (*q == NULL) return;
  if ((*q)->flag == 1000) return;
  (*q)->flag = 1000;
  aclearqueue(&(*q)->leftlink);
  aclearqueue(&(*q)->downlink);
  free(*q);
}


/************************/
/* LEFTIST TREE SECTION */
/************************/

void linitqueue(q) 
lqueue *q; 
/*  initialize a variable of type queue  */ 
{ 
  *q = NULL; 
} 

void merge(p, q) 
lqueue *p,*q; 
  /*  merge two trees, either can be possibly a single node  */ 
{ 
  int stay,d,distance;
  lnoderef t, r;
  r = NULL; 
  stay = TRUE; 
  /*  merge the two trees, inserting upward right pointers  */ 
  while (stay) { 
    if (*q == NULL) { 
      d = (*p)->dist; 
      stay = FALSE; 
    } 
    else if (*p == NULL) { 
      *p = *q; 
      d = (*p)->dist; 
      stay = FALSE; 
    } 
    else if ((*p)->element.time <= (*q)->element.time) { 
      t = (*p)->rightlink; 
      (*p)->rightlink = r; 
      r = *p; 
      *p = t; 
    } 
    else { 
      t = (*q)->rightlink; 
      (*q)->rightlink = r; 
      r = *q; 
      *q = t; 
    } 
  } 
  /*  convert the tree to normal form  */ 
  while (r != NULL) { 
    if (r->leftlink == NULL) distance = 0; 
    else distance = r->leftlink->dist; 
    *q = r->rightlink; 
    if (distance < d) { 
      d = distance + 1; 
      r->rightlink = r->leftlink; 
      r->leftlink = *p; 
    } 
    else { 
      d++; 
      r->rightlink = *p; 
    } 
    r->dist = d; 
    *p = r; 
    r = *q; 
  } 
} 

void lenqueue(nn, q) 
ITEM nn; 
lqueue *q; 
{ 
  lnoderef n;
  n = (struct lnode *)malloc(sizeof(struct lnode));
  n->element = nn;
  n->dist = 1; 
  n->leftlink = NULL; 
  n->rightlink = NULL; 
  merge(q, &n); 
} 

ITEM ldequeue(q) 
lqueue *q; 
{ 
  lnoderef temp;
  ITEM dummy;
  temp = *q;
  dummy = temp->element;
  if (((*q)->leftlink != NULL) || ((*q)->rightlink != NULL)) 
    merge(&((*q)->leftlink), &((*q)->rightlink)); 
  *q = (*q)->leftlink;
  free(temp);
  return dummy; 
}


/* lsearch hunts for a node with token number n in a leftist tree q,
   ultimately sets a flag saying to turn left or right to reach it */

int lsearch(n,q)
int n;
lnoderef *q;
{
  if (*q == NULL) return 0;
  if ((int)(*q)->element.token.attr[0] == n) return 1;
  if (lsearch(n,&((*q)->leftlink)) == 1) {
    (*q)->flag = 0;
    return 1;
  }
  if (lsearch(n,&((*q)->rightlink)) == 1) {
    (*q)->flag = 1;
    return 1;
  }
  return 0;
}


/* dista returns the distance of a node in a leftist tree; handles NULL */

int dista(q)
lnoderef q;
{
  if (q == NULL) return 0;
  else return q->dist;
}


/* lblah handles the process of adjusting a tree when an arbitrary node is
   removed.  First, it adjusts the tree below it.  Then, it swaps the 
   children if necessary according to the distances.  Finally, it sets its
   own distance, based in the children. */

ITEM lblah(n,q)
int n;
lnoderef *q;
{
  lnoderef temp;
  ITEM temp2;
  /* a flag of 0 means you head left to reach the node in question */
  if ((*q)->flag==0) {
  /* if you're at the node, replace it with the dequeue of the subtree 
     else adjust the leftchild */
    if ((int)(*q)->leftlink->element.token.attr[0] == n)
      temp2=ldequeue(&((*q)->leftlink));
    else temp2=lblah(n,&((*q)->leftlink));
  /* if the new distance of the leftchild is less then that of the right child
     it is necessary to swap the two children */
    if (dista((*q)->leftlink)<dista((*q)->rightlink)) {
      temp = (*q)->rightlink;
      (*q)->rightlink = (*q)->leftlink;
      (*q)->leftlink = temp;
    }
  /* set the new distance of the current node */
    (*q)->dist = dista((*q)->rightlink) + 1;
  }
  else {
  /* same idea, but on the right child, and no swapping necessary */
    if ((*q)->rightlink->element.token.attr[0] == n) 
      temp2=ldequeue(&((*q)->rightlink));
    else temp2=lblah(n,&((*q)->rightlink));
    (*q)->dist = dista((*q)->rightlink) + 1;
  }
  return temp2;
}


/* lrmqueue arbitrarily removes the node with token number n from tree q */

ITEM lrmqueue(n,q)
int n;
lqueue *q;
{
  /* if the root is it, do a dequeue, else find the node and use lblah */
  if ((int)(*q)->element.token.attr[0] == n) return ldequeue(q);
  else {
    if (lsearch(n,&((*q)->leftlink)) == 1) (*q)->flag = 0;
    else if (lsearch(n,&((*q)->rightlink)) == 1) (*q)->flag = 1;
    return lblah(n,q);
  }
}

void lclearqueue(q)
lnoderef *q;
{
  if (*q==NULL) return;
  lclearqueue(&(*q)->leftlink);
  lclearqueue(&(*q)->rightlink);
  free(*q);
}

/*******************/
/* TWOLIST SECTION */
/*******************/

void tinitqueue(q) 
tqueue *q; 
{ 
  q->sorted = NULL; 
  q->unsorted = NULL; 
  q->length = 0; 
  q->cutoff = 1.0; 
  q->delta = 100.0; 
} 

void tenqueue(nn, q) 
ITEM nn; 
tqueue *q; 
{   /*  used for loop exit  */ 
  tnoderef n,p;
  n = (struct tnode *)malloc(sizeof(struct tnode));
  n->element = nn;
  if (q->length == 0) { 
    q->sorted = n; 
    n->leftlink = NULL; 
    q->cutoff = n->element.time; 
  } 
  else if (n->element.time > q->cutoff) {   
    /*  put new node in unsorted list  */ 
    n->leftlink = q->unsorted; 
    q->unsorted = n; 
  }
  else if (q->sorted == NULL) {   /*  put new node in sorted list  */ 
    q->sorted = n; 
    n->leftlink = NULL; 
  } 
  else if (q->sorted->element.time > n->element.time) { 
    n->leftlink = q->sorted; 
    q->sorted = n; 
  }
  else {   /*  sift new node into sorted list  */ 
    p = q->sorted; 
    for (;;) { 
      if (p->leftlink == NULL) { 
        p->leftlink = n; 
        n->leftlink = NULL; 
        break;
      }
      else if (p->leftlink->element.time > n->element.time) { 
        n->leftlink = p->leftlink; 
        p->leftlink = n; 
        break;
      }
      else p = p->leftlink; 
    }   /*  for  */ 
  }
  q->length++; 
} 

ITEM tdequeue(q) 
tqueue *q; 
{
  tnoderef n, p, r, temp;
  int moved;
  ITEM dummy;
  while (q->sorted == NULL) {   /*  unsorted queue must be scanned  */ 
    q->cutoff += q->delta; 
    moved = 0; 
    r = q->unsorted; 
    q->unsorted = NULL; 
    do {   /*  scan down old unsorted list, picking out nodes to sort  */ 
      n = r; 
      r = r->leftlink; 
      if (n->element.time > q->cutoff) {   
        /*  put back on unsorted list  */ 
        n->leftlink = q->unsorted; 
        q->unsorted = n; 
      } 
      else {   /*  sift into sorted list  */ 
        if (q->sorted == NULL) { 
          q->sorted = n; 
          n->leftlink = NULL; 
        } 
        else if (q->sorted->element.time >= n->element.time) { 
          n->leftlink = q->sorted; 
          q->sorted = n; 
        }
        else { 
          p = q->sorted; 
          for (;;) { 
            if (p->leftlink == NULL) { 
              p->leftlink = n; 
              n->leftlink = NULL; 
              break;
            }
            else if (p->leftlink->element.time >= n->element.time) { 
              n->leftlink = p->leftlink; 
              p->leftlink = n; 
              break;
            }
            else p = p->leftlink; 
          } 
        } 
        moved++; 
      }
    }  while (r != NULL) ; 
  /* this is the adjustment line that seems to make bad things happen.
     I put in the and FALSE to make sure it didn't fire, and it speeded up
     the process greatly */
    if (FALSE && (moved > 0) && (q->length > 4)) 
      q->delta = q->delta * (0.5 + 0.5 * ((2 * sqrt(q->length)) / moved)); 
  } 
  p = q->sorted; 
  temp = p; 
  q->sorted = p->leftlink; 
  q->length--;
  dummy = temp->element;
  free(temp);
  return dummy;
}


/* trmqueue arbitrarily removed a node with token number n from q */

ITEM trmqueue(n,q)
int n;
tqueue *q;
{
  tnoderef prevnode,currentnode;
  int flag;
  ITEM dummy;
  /* search the sorted part for the node */
  prevnode = NULL;
  flag = 0;
  q->length--;
  currentnode = q->sorted;
  while ((currentnode != NULL) && 
   ((int)currentnode->element.token.attr[0] != n)) {
    prevnode = currentnode;
    currentnode = currentnode->leftlink;
  }
  /* if not found, search the unsorted part */
  if (currentnode == NULL) {
    flag = 1;
    currentnode = q->unsorted;
    prevnode = NULL;
    while ((currentnode != NULL) && 
      ((int)currentnode->element.token.attr[0] != n)) {
      prevnode = currentnode;
      currentnode = currentnode->leftlink;
    }
  }
  /* once found, point the previous pointer to the next item in the list */
  if (currentnode != NULL) {
    if (prevnode == NULL) {
      if (flag == 0) q->sorted = currentnode->leftlink;
      else q->unsorted = currentnode->leftlink;
    }
    else prevnode->leftlink = currentnode->leftlink;
    dummy = currentnode->element;
    free(currentnode);
    return dummy;
  }
}

void tclearqueue(q)
tnoderef *q;
{
  if (*q==NULL) return;
  tclearqueue(&(*q)->leftlink);
  free(*q);
}

/****************************/
/* SKEWED DOWN HEAP SECTION */
/****************************/

void kinitqueue(q) 
cqueue *q; 
/*  initialize a variable of type queue  */ 
{ 
  *q = NULL; 
} 

cqueue meld(h1, h2) 
cqueue *h1; 
cqueue *h2; 
/*  merge two skew heaps from the top down  */ 
{ 
  cnoderef temp, y, temp2;
  if (*h1 == NULL) return *h2; 
  else if (*h2 == NULL) return *h1; 
  else { 
    if ((*h1)->element.time >= (*h2)->element.time) {   
    /*  swap  */ 
      temp = *h1; 
      *h1 = *h2; 
      *h2 = temp; 
    } 
    temp2 = *h1;
    y = *h1; 
    *h1 = y->rightlink; 
    y->rightlink = y->leftlink; 
    while (*h1 != NULL) { 
      if ((*h1)->element.time >= (*h2)->element.time) {   
        /*  swap  */ 
        temp = *h1; 
        *h1 = *h2; 
        *h2 = temp; 
      } 
      y->leftlink = *h1; 
      y = *h1; 
      *h1 = y->rightlink; 
      y->rightlink = y->leftlink; 
    } 
    y->leftlink = *h2; 
  } 
  return temp2;
} 

void kenqueue(nn, q) 
ITEM nn; 
cqueue *q; 
{ 
  cnoderef n;
  n = (struct cnode *)malloc(sizeof(struct cnode));
  n->element = nn;
  n->leftlink = NULL; 
  n->rightlink = NULL; 
  *q = meld(&n, q); 
} 

ITEM kdequeue(q) 
cqueue *q; 
{ 
  cnoderef temp;
  ITEM dummy;
  temp = *q; 
  *q = meld(&((*q)->leftlink), &((*q)->rightlink)); 
  dummy = temp->element;
  free(temp);
  return dummy;
}


/* kfindnode attempts to find a node specified by token number n in a
   skewed down heap q, returns a pointer to the parent of the node */

cnoderef kfindnode(flag,n,q)
int *flag;
int n;
cqueue *q;
{
  cnoderef tempnode;
  /* the leftlink contains the node */
  if (((*q)->leftlink != NULL) && 
     ((int)(*q)->leftlink->element.token.attr[0] == n)) {
    *flag = 1;
    return *q;
  }
  /* the rightlink contains the node */
  else if (((*q)->rightlink!=NULL) &&
    ((int)(*q)->rightlink->element.token.attr[0]==n)) {
    *flag = 0;
    return *q;
  }
  /* dead end */
  else if (((*q)->rightlink == NULL) && ((*q)->leftlink == NULL)) {
    *flag = 2;
    return NULL;
  }
  /* search the rightlink, if not there, search the leftlink */
  else {
    if ((*q)->rightlink != NULL) 
      tempnode = kfindnode(flag,n,&((*q)->rightlink));
    else *flag = 2;
    if (*flag != 2) return tempnode;
    else { if ((*q)->leftlink != NULL) 
      tempnode = kfindnode(flag,n,&((*q)->leftlink)); 
    else *flag = 2; }
    if (*flag != 2) return tempnode;
    else return NULL;
  }
}


/* krmqueue arbitrarily removes the node with token number n from 
   skewed down heap q */

ITEM krmqueue(n,q)
int n;
cqueue *q;
{
  cnoderef parentnode;
  int flag=0;
  if ((int)(*q)->element.token.attr[0] == n) return kdequeue(q);
  else {
    parentnode = kfindnode(&flag,n,q);
    if (flag==0) return kdequeue(&(parentnode->rightlink));
    else return kdequeue(&(parentnode->leftlink));
  }
}


/*********************************/
/* SKEWED HEAP BOTTOM UP SECTION */
/*********************************/

void sinitqueue(q) 
squeue *q; 
  /*  initialize a variable of type queue  */ 
{ 
  *q = NULL; 
} 

void senqueue(nn, q) 
ITEM nn; 
squeue *q; 
{
  snoderef bound, lownode, temp, n;
  n = (struct snode *)malloc(sizeof(struct snode));
  n->element = nn;
  n->flag = 0;
  if (*q == NULL) {   /*  trivial insertion in empty queue  */ 
    *q = n; 
    (*q)->uplink = n; 
    (*q)->leftlink = n; 
  } 
  else if (n->element.time < (*q)->element.time) {   
    /*  trivial insertion at head  */ 
    n->leftlink = (*q)->uplink; 
    (*q)->uplink = n; 
    n->uplink = n; 
    *q = n; 
  } 
  else if (n->element.time >= (*q)->uplink->element.time) {   
    /*  trivial at tail  */ 
    n->uplink = (*q)->uplink; 
    (*q)->uplink = n; 
    n->leftlink = n; 
  }
  else {   /*  non-trivial insertion  */ 
    bound = (*q)->uplink; 
    lownode = bound; 
    temp = bound->uplink; 
    while (n->element.time < temp->element.time) { 
      bound = temp; 
      temp = bound->leftlink; 
      bound->leftlink = lownode; 
      lownode = temp; 
      temp = bound->uplink; 
    } 
    n->uplink = temp; 
    n->leftlink = lownode; 
    bound->uplink = n; 
    (*q)->uplink = n; 
  }
} 

ITEM sdequeue(q) 
squeue *q; 
{
  snoderef temp, major, minor, next, newq;
  ITEM dummy;
  /*  always return the head  */
  temp = *q; 
  if (*q != NULL) {   /*  delete the head of the queue  */ 
    major = (*q)->uplink; 
    minor = (*q)->leftlink; 
    if (major->element.time <= minor->element.time) {   
      /*  exchange major and minor  */ 
      major = minor; 
      minor = (*q)->uplink; 
    } 
    if (major == *q) {   /*  unless priorities are equal, queue is empty  */ 
      if (minor == *q) /*  queue really is empty  */ 
        *q = NULL; 
      else {   /*  minor has prio equal to q  */ 
        next = minor; 
        while (minor->uplink != *q) minor = minor->uplink; 
        minor->uplink = next; 
        *q = minor; 
      } 
    }
    else {   /*  setup to do full scale merge of major and minor  */ 
      newq = major; 
      major = major->uplink; 
      newq->uplink = newq; 
      if (major->element.time <= minor->element.time) { 
        next = minor; 
        minor = major; 
      }
      else next = major; 
      while (next != *q) { 
        major = next->uplink; 
        next->uplink = next->leftlink; 
        next->leftlink = newq->uplink; 
        newq->uplink = next; 
        newq = next; 
        if (major->element.time <= minor->element.time) { 
          next = minor; 
          minor = major; 
        }
        else next = major; 
      } 
      /*  unless priorities are equal, merger is done  */ 
      if (minor == *q) /*  merger is done  */ 
        *q = newq; 
      else {   /*  minor has prio equal to q  */ 
        next = minor; 
        while (minor->uplink != *q) minor = minor->uplink; 
        minor->uplink = newq->uplink; 
        newq->uplink = next; 
        *q = minor; 
      } 
    } 
  }
  dummy = temp->element;
  free(temp);
  return dummy;
}


/* ssearch looks for a node specified by token number n in a skewed heap q
   returning a pointer to the node in the process */

snoderef ssearch(n,q,qroot)
int n;
snoderef q;
squeue qroot;
{
  snoderef temp;
  if ((int)q->element.token.attr[0] == n) return q;
  /* if you are at the place you started from, you haven't found the node */
  if (q->uplink != qroot) temp = ssearch(n,q->uplink,qroot);
  else temp = NULL;
  if (temp!=NULL) return temp;
  /* try looking in the leftlink of this node, but don't come back around
     and try to look in already checked nodes */
  if ((q->leftlink != qroot) && (q->leftlink != q)) 
    temp = ssearch(n,q->leftlink,q);
  else temp = NULL;
  return temp;
  /* return the a pointer to the node containing n */
}


/* sfroml will determine if q1 is a left child or right child */

int sfroml(q1,q2)
snoderef q1;
squeue q2;
{
  snoderef temp;
  temp = q1->uplink->leftlink;
  while ((temp!=q1) && (temp!=q1->uplink)) temp=temp->uplink;
  return temp==q1;
  /* tell if a node q1 in a skewed heap q2 is a left child or not */
}


/* srootonl determines if q1 is a right descendent of the root */

int srootonl(q1,q2)
snoderef q1;
squeue q2;
{
  snoderef temp;
  temp = q2->uplink;
  while ((temp!=q2) && (temp!=q1)) temp = temp->uplink;
  return temp==q1;
  /* tell if the node q1 is a direct right descendent of root q2 */
}


/* srmqueue deletes the node with token number n from the queue q.
   There are two possible cases.  First, the node to be deleted can be
   a left child, or it can be any right child that is not a direct
   descendant of the root.  In this case, it is necessary to find the
   first parent of a left child along the path from the node to the root
   (which would be the parent of a left child, or the first left child's
   parent following uplinks).  Once this is found, pointer swapping and
   a dequeue take care of business.
   In the remaining cases, the root serves the same function as the above
   searched for node, and pointer swapping and a dequeue handle the rest */ 

ITEM srmqueue(n,q)
int n;
squeue *q;
{
  snoderef temp,temp2,temp3;
  ITEM temp4;
  int flag;
  /* dequeue if the head is the node */
  if ((int)(*q)->element.token.attr[0] == n) return sdequeue(q);
  else {
    /* search for the node and determine if a left child */
    temp = ssearch(n,(*q),(*q));
    flag = sfroml(temp,(*q));
    /* case one: left child or non-direct-from-root-right child */
    if ((flag!=0) || (srootonl(temp,(*q))==0)) {
      temp2 = temp->uplink;
      /* find first left child's parent */
      if (flag==0) {
        for (;;) {
          temp3 = temp2->leftlink;
          while ((temp3!=temp) && (temp3!=temp2)) temp3=temp3->uplink;
          if (temp3==temp) break;
          else temp2=temp2->uplink;
        }
      }
      temp3 = temp->uplink;
      temp->uplink = temp2->leftlink;
      temp4 = sdequeue(&(temp));
      if (temp!=NULL) {
        temp2->leftlink = temp->uplink;
        temp->uplink = temp3;
      }
      else temp2->leftlink = temp3;
    }
    /* case two */
    else {
      temp3 = temp->uplink;
      temp->uplink = (*q)->uplink;
      temp4 = sdequeue(&(temp));
      if (temp!=NULL) {
        (*q)->uplink = temp->uplink;
        temp->uplink = temp3;
      }
      else (*q)->uplink = temp3;
    }
    return temp4;
  }
}

void sclearqueue(q)
snoderef *q;
{
  if (*q==NULL) return;
  if ((*q)->flag==1000) return;
  (*q)->flag = 1000;
  sclearqueue(&(*q)->leftlink);
  sclearqueue(&(*q)->uplink);
  free(*q);
}


/******************/
/* PAGODA SECTION */
/******************/

void pinitqueue(q) 
cqueue *q; 
/*  initialize a variable of type queue  */ 
{ 
  *q = NULL; 
} 

void penqueue(nn, q) 
ITEM nn; 
cqueue *q; 
{ 
  cnoderef p,n;
  n = (struct cnode *)malloc(sizeof(struct cnode));
  n->element = nn;
  n->flag = 0;
  /*  point new nodes sons at itself  */ 
  n->rightlink = n; 
  n->leftlink = n; 
  if (*q == NULL) *q = n; 
  else {   /*  non-trivial insertion  */ 
    p = (*q)->rightlink; 
    if (n->element.time >= p->element.time) {   
      /*  new node goes to the bottom  */ 
      n->rightlink = (*q)->rightlink; 
      (*q)->rightlink = n; 
    } 
    else if ((n->element.time <= (*q)->element.time)) {   
      /*  new node replaces head  */ 
      n->leftlink = (*q)->leftlink; 
      (*q)->leftlink = n; 
      *q = n; 
    } 
    else {   /*  new node goes somewhere in the middle  */ 
      while (n->element.time < p->rightlink->element.time) 
	p = p->rightlink; 
      n->rightlink = p->rightlink; 
      p->rightlink = (*q)->rightlink; 
      (*q)->rightlink = n; 
      n->leftlink = p->leftlink; 
      p->leftlink = n; 
    } 
  } 
} 

ITEM pdequeue(q) 
cqueue *q; 
{ 
  cnoderef lb, rb, f, tl;
  cqueue temp;
  ITEM dummy;
  temp = *q;
  dummy = temp->element;
  lb = (*q)->rightlink; 
  rb = (*q)->leftlink; 
  if (lb == rb)  /*  there was only one node in the queue  */ 
    *q = NULL; 
  else if (lb == *q) {   /*  there was no rightlink  */ 
    do rb = rb->leftlink; while (rb->leftlink != *q); 
    rb->leftlink = (*q)->leftlink; 
    *q = rb; 
  } 
  else if (rb == *q) {   /*  there was no leftlink  */ 
    do lb = lb->rightlink; while (lb->rightlink != *q); 
    lb->rightlink = (*q)->rightlink; 
    *q = lb; 
  } 
  else {   /*  non-trivial deletion  */ 
    /*  compare left and right sons, prepare to merge sub-pagodas  */ 
    if (lb->element.time >= rb->element.time) { 
      f = lb; 
      tl = lb->rightlink; 
      lb->rightlink = lb; 
      lb = tl; 
    } 
    else { 
      f = rb; 
      tl = rb->leftlink; 
      rb->leftlink = rb; 
      rb = tl; 
    } 
    /*  merge the left and right branches, bottom to top  */ 
    while ((lb != *q) && (rb != *q)) { 
      if (lb->element.time >= rb->element.time) { 
	tl = lb->rightlink; 
	lb->rightlink = f->rightlink; 
	f->rightlink = lb; 
	f = lb; 
	lb = tl; 
      } 
      else { 
	tl = rb->leftlink; 
	rb->leftlink = f->leftlink; 
	f->leftlink = rb; 
	f = rb; 
	rb = tl; 
      } 
    } 
    /*  put any leftovers from the merge at the top of the queue  */ 
    if (lb == *q) { 
      tl = f->leftlink; 
      f->leftlink = rb; 
      while (rb->leftlink != *q) rb = rb->leftlink; 
      rb->leftlink = tl; 
      *q = rb; 
    } 
    else { 
      tl = f->rightlink; 
      f->rightlink = lb; 
      while (lb->rightlink != *q) lb = lb->rightlink;
      lb->rightlink = tl; 
      *q = lb; 
    } 
  }
  free(temp);
  return dummy;
}


/* psearch looks for the node to be deleted, and marks it as a left or right
   child.  Note:  this can happen because the path from the root is being
   followed.  In the general case of a node, one cannot tell in constant
   time if it is a left or right child. */

cnoderef psearch(n,q)
int n;
cqueue q;
{
  cnoderef temp;
  /* you've hit an already looked at node */
  if (q->flag == 1) return NULL;
  /* ah, this is the node you want */
  if ((int)q->element.token.attr[0] == n) return q;
  /* okay, mark this node as being looked at before seaching from it */
  q->flag = 1;
  temp = psearch(n,q->leftlink);
  /* you've found the node in the leftlink.  If the leftlink is the node 
     you want, then it must be a left child since you came from the root,
     mark it as such with the flag field. */
  if (temp!=NULL) {
    if (q->leftlink == temp) temp->flag = 2;
    q->flag = 0;
    return temp;
  }
  /* search the rightlink.  If you find it, then it is a right child if the
     node you want is at the rightlink, mark it as such using flag */
  temp = psearch(n,q->rightlink);
  if ((temp != NULL) && (q->rightlink == temp)) temp->flag = 3;
  q->flag = 0;
  return temp;
}


/* pisleft is an obsolete function which determined if a node was a left
   child or not.  Replaced by a modification to psearch above, but only
   works for the node that is being looked for.  The general case still
   relies on the index, which must be unique if it is to work. */

int pisleft(q)
cnoderef q;
{
  if ((q->rightlink == q) || (q->leftlink->element.time<q->element.time))
    return 1;
  else return 0;
}


/* prmqueue deletes the node specified by token number n. */

ITEM prmqueue(n,q)
int n;
cqueue *q;
{
  cnoderef temp,temp2,temp3;
  ITEM temp4;
  int lflag;
  /* if at the root, just do a dequeue */
  if ((int)(*q)->element.token.attr[0] == n) return pdequeue(q);
  /* look for the node and mark it as a left or right child */
  temp = psearch(n,*q);
/*  lflag = pisleft(temp); */
  temp2 = temp;
  /* if it's a left child, then look for the first node that specifies the
     left-most node in the subtree rooted at the node to be deleted.  Once
     this is done, assign the leftlink of the deletable node to this left-
     most node, perform a dequeue, and set the pointers back to normal */
  if (temp->flag == 2) {
    temp3 = temp->leftlink;
    do temp2 = temp2->leftlink;
    while (temp2->leftlink->element.time<temp->element.time);
    temp->leftlink = temp2->leftlink;
    temp4 = pdequeue(&temp);
    temp2->leftlink = temp->leftlink;
    temp->leftlink = temp3;
  }
  /* if it's a right child, one must look for the node that specifies the 
     right-most node in the subtree rooted at the node to be deleted.  This
     done, one proceeds as above, rearranging the correct pointers. */
  else {
    temp3=temp->rightlink;
    do temp2 = temp2->rightlink;
    while (temp2->rightlink->element.time<temp->element.time);
    temp->rightlink = temp2->rightlink;
    temp4 = pdequeue(&temp);
    temp2->rightlink = temp->rightlink;
    temp->rightlink = temp3;
  }
  return temp4;
}

void pclearqueue(q)
cnoderef *q;
{
  if (*q==NULL) return;
  if ((*q)->flag == 1000) return;
  (*q)->flag = 1000;
  pclearqueue(&(*q)->leftlink);
  pclearqueue(&(*q)->rightlink);
  free(*q);
}

/*********************************/
/* HENRIKSON'S ALGORITHM SECTION */
/*********************************/

void setvec(q, newsize) 
hqueue *q; 
int newsize; 
{ 
  if (newsize > 1024) exit(0);
  q->vecsize = newsize; 
  q->leftlim = 1024 - newsize; 
  q->starti = 1024 - newsize / 2 - 1; 
  q->startj = newsize / 4; 
} 

void hinitqueue(q) 
hqueue *q; 
{ 
  hnoderef n;
  int i;
  for (i = 0; i <= 1023; i++) q->timevec[i] = 0.0; 
  n = (struct hnode *)malloc(sizeof(*n));
  q->zero = (struct hnode *)malloc(sizeof(struct hnode));
  q->zero->leftlink = NULL; 
  q->zero->rightlink = n; 
  q->zero->element.time = 0.0; 
  n->leftlink = q->zero; 
  n->rightlink = NULL; 
  n->element.time = 1e38 ;  /* must be big number */ 
  q->timevec[1023] = 1e38; /* same here */
  q->ptrvec[1023] = n; 
  setvec(q, 1); 
} 

void henqueue(nn, q) 
ITEM nn; 
hqueue *q; 
{ 
  int i, j, count;
  float t;
  hnoderef qq,n;
  n = (struct hnode *)malloc(sizeof(struct hnode));
  n->element = nn;
  /*  search setting i to index of right entry in ptrvec  */ 
  i = q->starti; 
  j = q->startj; 
  t = n->element.time; 
  while (j > 0) { 
    if (q->timevec[i] <= t) i += j; 
    else i -= j; 
    j = j / 2; 
  } 
  if (q->timevec[i] <= t) i++; 
  /*  now do insertion in queue  */ 
  qq = q->ptrvec[i]->leftlink; 
  count = 0; 
  while (n->element.time < qq->element.time) { 
    count++; 
    if (count == 4) {   /*  pull  */ 
      if (i <= q->leftlim) setvec(q, q->vecsize * 2); 
      i--; 
      count = 0; 
      q->ptrvec[i] = qq; 
      q->timevec[i] = qq->element.time; 
    } 
    qq = qq->leftlink; 
  } 
  n->leftlink = qq; 
  n->rightlink = qq->rightlink; 
  n->rightlink->leftlink = n; 
  qq->rightlink = n; 
} 

ITEM hdequeue(q) 
hqueue *q; 
{ 
  hnoderef temp;
  ITEM dummy;
  if ((q->timevec[q->starti] <= q->zero->rightlink->element.time) 
      && (q->vecsize > 2)) setvec(q, q->vecsize / 2); 
  temp = q->zero->rightlink;
  dummy = temp->element;
  q->zero->rightlink = q->zero->rightlink->rightlink; 
  q->zero->rightlink->leftlink = q->zero;
  if (temp->element.token.attr[0] < 0.0) {
    free(temp);
    return hdequeue(q);
  }
  else {
    free(temp);
    return dummy;
  }
} 



/* hrmqueue marks as bad the node that is specified by token number n */

ITEM hrmqueue(n,q)
int n;
hqueue *q;
{
  hnoderef temp;
  temp = q->zero->rightlink;
  while (temp->element.token.attr[0] != n) temp = temp->rightlink;
  temp->element.token.attr[0] = -temp->element.token.attr[0];
  return temp->element;
}

void hclearqueue(q)
hnoderef *q;
{
  if (*q==NULL) return;
  hclearqueue(&(*q)->rightlink);
  free(*q);
}  

/***************************/
/* BINOMIAL FOREST SECTION */
/***************************/

int odd(s)
int s;
{
  return s % 2;
}

void iinitqueue(q) 
iqueue *q; 
/*  initialize a variable of type queue  */ 
{ 
  q->size = 0; 
} 

void ienqueue(nn, q) 
ITEM nn; 
iqueue *q; 
{ 
  inoderef n,rtmrt, nxtrt;
  int s;
  n = (struct inode *)malloc(sizeof(struct inode));
  n->element = nn;
  n->flag = -1;
  s = q->size; 
  n->downlink = NULL; 
  if (s != 0) rtmrt = q->leftmostroot->leftlink; 
  if (odd(s)) { 
    /*  the rightmost tree in q consists of a single node; merge it into n */
    nxtrt = rtmrt->leftlink; 
    if (n->element.time >= rtmrt->element.time) {   
      /*  exchange n and rtmrt  */ 
      n->leftlink = n; 
      rtmrt->downlink = n; 
      n = rtmrt; 
    } 
    else { 
      n->downlink = rtmrt; 
      rtmrt->leftlink = rtmrt; 
    } 
    rtmrt = nxtrt; 
    s = s / 2; 
    while (odd(s)) { 
    /*  the rightmost tree remaining is same size as n; merge with x  */ 
      nxtrt = rtmrt->leftlink; 
      if (n->element.time >= rtmrt->element.time) {   
        /*  exchange n and rtmrt  */ 
        n->leftlink = rtmrt->downlink->leftlink; 
        rtmrt->downlink->leftlink = n; 
        rtmrt->downlink = n; 
        n = rtmrt; 
      } 
      else { 
        rtmrt->leftlink = n->downlink->leftlink; 
        n->downlink->leftlink = rtmrt; 
        n->downlink = rtmrt; 
      } 
      rtmrt = nxtrt; 
      s = s / 2; 
    }   /*  merge loop  */ 
  } 
  if (s == 0) {   /*  entire forest merged with n, size was power of 2  */ 
    n->leftlink = n; 
    q->leftmostroot = n; 
  } 
  else {   /*  some of orig .forest remains, n is rightmost in new one  */ 
    q->leftmostroot->leftlink = n; 
    n->leftlink = rtmrt; 
  } 
  q->size++; 
} 

ITEM idequeue(q) 
iqueue *q; 
{ 
  inoderef lfmrt, rtmrt, smallest, pred, succ, 
           smallestpred, rtmchild, newrtmrt, mrgtree, nxttree;
  int s;
  ITEM dummy;
  double smallestkey;
  lfmrt = q->leftmostroot; 
  rtmrt = lfmrt->leftlink; 
  s = q->size; 
  if (lfmrt == rtmrt) {   /*  there is only one tree in the forest  */ 
    /*  return the root, make a new forest of its sons  */ 
    smallest = lfmrt; 
    q->leftmostroot = lfmrt->downlink; 
  } 
  else {   /*  there are two or more trees in the forest  */ 
    /*  search for the node containing the smallest key in the queue  */ 
    /*  mark the leftmost node to stop search  */ 
    lfmrt->leftlink = NULL; 
    smallestkey = lfmrt->element.time; 
    pred = lfmrt; 
    succ = rtmrt; 
    do { 
      if (smallestkey >= succ->element.time) { 
        smallestkey = succ->element.time; 
        smallestpred = pred; 
      } 
      pred = succ; 
      succ = succ->leftlink;
    }  while (succ != NULL) ; 
    smallest = smallestpred->leftlink; 
    if (smallest == NULL) {   /*  the rightmost root is the smallest  */ 
      smallest = rtmrt; 
      if (odd(s)) /*  rightmost is single node, just remove it  */ 
        lfmrt->leftlink = smallest->leftlink; 
      else {   /*  sons of rightmost become smallest in forest  */ 
        lfmrt->leftlink = smallest->downlink->leftlink; 
        smallest->downlink->leftlink = smallest->leftlink; 
      } 
    } 
    else {   /*  a root other than rightmost was smallest  */ 
      /*  the tree containing this root must be replaced.  A replacement
          is formed by mergint the rightmost tree with the children of the
          removed root.  Children smaller than the rightmost tree become
          the smallest trees in the new forest  */ 
      rtmchild = smallest->downlink->leftlink; 
      /*  mark leftmost child as end  */ 
      smallest->downlink->leftlink = NULL; 
      if (!odd(s)) {   /*  queue size was even before deletion,
		  children of removed root will move up to become smallest
                  trees in new forest.  Scan through children until mrgtree,
                  the one which will merge with rightmost in forest  */ 
        newrtmrt = rtmchild; 
        s = s / 2; 
        while (!odd(s)) { 
          rtmchild = rtmchild->leftlink; 
          s = s / 2; 
        } 
        mrgtree = rtmchild->leftlink; 
        /*  the tree to right of removed root is rightmost, will be
        consumed in building replacement tree; replacement's
        predicessor will be leftmost child which moves up  */ 
        if (smallestpred == rtmrt)   
          /*  link children into right of forest; their sibling
          is not the replacement and is therfore known  */ 
          smallestpred = rtmchild; 
        else rtmchild->leftlink = rtmrt->leftlink; 
      } 
      else {   /*  queue size is odd, children of removed root will
                  be used to make replacement  */ 
        newrtmrt = rtmrt->leftlink; 
        /*  the replacement will be the rightmost in the new forest;
        newrtmrt and smallestpred cannot be given values now;
        flag this with a NULL value  */ 
        if (smallestpred == rtmrt) smallestpred = NULL; 
        /*  do first merge  */ 
        mrgtree = rtmchild->leftlink; 
        if (rtmrt->element.time >= rtmchild->element.time) { 
          rtmchild->downlink = rtmrt; 
          rtmrt->leftlink = rtmrt; 
          rtmrt = rtmchild; 
        } 
        else { 
          rtmrt->downlink = rtmchild; 
          rtmchild->leftlink = rtmchild; 
        } 
      } 
      /*  complete the merge  */ 
      while (mrgtree != NULL) { 
        nxttree = mrgtree->leftlink; 
        if (rtmrt->element.time >= mrgtree->element.time) { 
          rtmrt->leftlink = mrgtree->downlink->leftlink; 
          mrgtree->downlink->leftlink = rtmrt; 
          mrgtree->downlink = rtmrt; 
          rtmrt = mrgtree; 
        } 
        else { 
          mrgtree->leftlink = rtmrt->downlink->leftlink; 
          rtmrt->downlink->leftlink = mrgtree; 
          rtmrt->downlink = mrgtree; 
        } 
        mrgtree = nxttree; 
      } 
      /*  fixup links between roots in the forest: sibling link from
      leftmost to rightmost root, sibling link from replacement
      tree to next larger, and sibling link to replacement tree
      from next smaller  */ 
      if (smallest == lfmrt) {   /*  leftmost was replaced  */ 
        q->leftmostroot = rtmrt; 
        if (smallestpred == NULL) /*  replacement is only one  */ 
          rtmrt->leftlink = rtmrt; 
        else {   /*  more than one tree in forest  */ 
          rtmrt->leftlink = newrtmrt; 
          smallestpred->leftlink = rtmrt; 
        } 
      } 
      else {   /*  there is tree larger than replacement  */ 
        rtmrt->leftlink = smallest->leftlink; 
        if (smallestpred == NULL) /*  no tree smaller than repl  */ 
          lfmrt->leftlink = rtmrt; 
        else {   /*  there is tree smaller than replacement  */ 
          lfmrt->leftlink = newrtmrt; 
          smallestpred->leftlink = rtmrt; 
        } 
      } 
    } 
  } 
  q->size--; 
  if (smallest->element.token.attr[0] < 0.0) {
    free(smallest);
    return idequeue(q);
  }
  else {
    dummy = smallest->element;
    free(smallest);
    return dummy;
  } 
}


/* isearch looks for the node to delete and marks it as bad. It then
   returns that node to the calling procedure */

int isearch(n,q,keepthis)
int n;
inoderef q;
ITEM *keepthis;
{
  if (q == NULL) return 0;
  if (q->flag == 2) return 0;
  if (q->element.token.attr[0] == n) {
    q->flag = -1;
    *keepthis = q->element;
    q->element.token.attr[0] *= -1;
    return 1;
  }
  q->flag = 2;
  if (isearch(n,q->leftlink,keepthis)) { 
    q->flag = -1;
    return 1;
  }
  if (isearch(n,q->downlink,keepthis)) {
    q->flag = -1;
    return 1;
  }
  q->flag = -1;
  return 0;
}


/* irmqueue calls isearch and gets the node to be deleted.  It started
   out as a huge algorithm for actually removing the node, but when this
   approach failed, modifying isearch was easier then rewriting the huge
   block of code that was irmqueue */

ITEM irmqueue(n,q)
int n;
iqueue *q;
{
  ITEM keepthis;
  if (isearch(n,q->leftmostroot,&keepthis)) return keepthis;
}

void iclearqueue(q)
inoderef *q;
{
  if (*q==NULL) return;
  if ((*q)->flag==1000) return;
  (*q)->flag = 1000;
  iclearqueue(&(*q)->leftlink);
  iclearqueue(&(*q)->downlink);
  free(*q);
}
