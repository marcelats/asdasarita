/* henrik */
typedef struct hnode *hnoderef;
struct hnode {
  hnoderef leftlink, rightlink;
  ITEM element;
};
typedef struct {
  hnoderef ptrvec[1024];
  hnoderef zero;
  double timevec[1024];
  int vecsize, leftlim, starti, startj;
} hqueue;

/* inomial */
typedef struct inode *inoderef;
typedef struct inode {
  inoderef leftlink, downlink;
  ITEM element;
  int flag;
};
typedef struct {
  inoderef leftmostroot;
  int size;
} iqueue;

/* leftist */
typedef struct lnode *lnoderef;
typedef struct lnode {
  lnoderef leftlink, rightlink;
  int dist,flag;
  ITEM element;
};
typedef lnoderef lqueue;

/* common */
typedef struct cnode *cnoderef;
typedef struct cnode {
  cnoderef leftlink, rightlink,parent;
  int flag;
  ITEM element;
};
typedef cnoderef cqueue;

/* pair */
typedef struct pnode *pnoderef;
typedef struct pnode {
  pnoderef leftlink, downlink;
  int flag;
  ITEM element;
};
typedef pnoderef pqueue;

/* skewup */
typedef struct snode *snoderef;
typedef struct snode {
  snoderef uplink, leftlink;
  int flag;
  ITEM element;
};
typedef snoderef squeue;

/* twolist */
typedef struct tnode *tnoderef;
typedef struct tnode {
  tnoderef leftlink;
  ITEM element;
};
typedef struct {
  tnoderef sorted, unsorted;
  int length;
  double cutoff,delta;
} tqueue;

hqueue hqq;
iqueue iqq;
lqueue lqq;
cqueue pqq;
pqueue aqq;
cqueue kqq;
squeue sqq;
cqueue yqq;
tqueue tqq;
