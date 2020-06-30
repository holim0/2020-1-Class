#	include <stdlib.h>
# 	include <stdio.h>
# 	include <string.h>

#	define DBG(x)
#	define XLOG(x)
# 	define LLOG(x)
# 	define STDMALLOC(p,s,r)	 if (!((p)=malloc((s))))\
				 return (r); else memset((p),0,(s))

# 	define STDREALLOC(p,s,r) if (!((p)=realloc((p),(s)))) return (r)
# 	define STDFREE(p)        free((p))


/*
 * NULL: value for null pointers, normally defined by stdio.h.
 */

#if !defined(NULL)
#define NULL 0L
#endif

/*
 * LOCAL: synonym for static declares an object as local to a source file.
 */

#define local     static

/*
 * BOOL, TRUE, FALSE: standard names for logical values.
 */

typedef short int bool;

#if !defined(TRUE)
#define TRUE  ((bool) 1)
#define FALSE ((bool) 0)
#endif

/*
 * BYTE: name a handy chunk of bits.
 */

typedef unsigned char byte;

/*
 * STRING: null-terminated char array.
 */

typedef char *string;

/*
 * STREAM: more elegant synonym for FILE *.
 */

typedef FILE *stream;                   /* note: stdio.h is included above  */

/* 
 * REAL, REALPTR: Compile-time precision specification.  Options are:
 *      DOUBLEPREC:     everything (variables & functions) is double.
 *      MIXEDPREC:      user values are float, -lm functions are double.
 *      SINGLEPREC:     everything (variables & functions) is float.
 * See mathfns.h for a list of real-valued functions.  If single
 * precision library functions are not availible then use MIXEDPREC
 * instead of SINGLEPREC.
 */

/* 
 * Default precision: use SINGLEPREC on SGI and MIXEDPREC on IBM.
 */

#if !defined(MIXEDPREC) && !defined(SINGLEPREC) && !defined(DOUBLEPREC)
#define SINGLEPREC
#endif

#if defined(DOUBLEPREC)
#undef SINGLEPREC
#undef MIXEDPREC
typedef double real, *realptr;
#define Precision "DOUBLEPREC"
#endif

#if defined(MIXEDPREC)
#undef DOUBLEPREC
#undef SINGLEPREC
typedef float *realptr, real;
#define Precision "MIXEDPREC"
#endif

#if defined(SINGLEPREC)
#undef DOUBLEPREC
#undef MIXEDPREC
typedef float real, *realptr;
#define Precision "SINGLEPREC"
#endif

/*
 * PI, etc.  --  mathematical constants.
 */

#define PI         3.14159265358979323846
#define TWO_PI     6.28318530717958647693
#define FOUR_PI   12.56637061435917295385
#define HALF_PI    1.57079632679489661923
#define FRTHRD_PI  4.18879020478639098462

/*
 * STREQ: string-equality macro. STRNULL: test for empty string.
 * Note that string.h should be included if these are used.
 */

#define streq(x,y) (strcmp((x), (y)) == 0)
#define strnull(x) (strcmp((x), "") == 0)

/*
 * ABS: returns the absolute value of its argument.
 * MAX: returns the argument with the highest value.
 * MIN: returns the argument with the lowest value.
 */

#define ABS(x)   (((x)<0)?-(x):(x))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

/*
 * Prototypes for misc. functions in libZeno.a.
 */

void *allocate(int);                    /* alloc, check for errors, zero    */

double cputime(void);                   /* returns CPU time in minutes      */

void error(string, ...);                /* complain about error and exit    */

void eprintf(string, ...);              /* print message to stderr          */

bool scanopt(string, string);           /* scan options for keyword         */

stream stropen(string, string);         /* arguments are much like fopen    */

# ifndef _LIBDS_H_
# define _LIBDS_H_

# define DS_LIB_VERSION_MAJOR	2
# define DS_LIB_VERSION_MINOR	1
# define DS_LIB_VERSION_STATUS	

typedef void*	DSKEY;
typedef int 	(*DSKEYCMPFUN)(const DSKEY,const DSKEY);

/*----------------------------------------------------------------------*
 * Tree									*
 *----------------------------------------------------------------------*/
# define AVLTreeNoCopyKeys      0
# define AVLTreeCopyKeys        1
# define AVLTreeNoKeySize       0

# define AVLTreeNoCompFun       ((void*)0)
# define AVLTreeNullData        ((void*)0)

typedef DSKEYCMPFUN		AVLKEYCOMPFUN;

typedef struct avltree	AvlTree;
typedef AvlTree*	AVLTREE;
typedef struct avlnode	AvlNode;
typedef AvlNode*	AVLNODE;


/* Default tree making routine for nodes with string keys */
# define avlNewTreeStrKeys()	\
	avlNewTree((AVLKEYCOMPFUN)strcmp,AVLTreeCopyKeys,AVLTreeNoKeySize)
# define avlMake()		avlNewTree((void*)0,1,0)
# define avlAdd(t,k,d)		avlInsert((t),(const DSKEY)(k),(void*)(d))
# define avlRemove(t,k)		avlRemoveByKey((t),(k))
# define avlFirstNode(tr)	avlMinimumNode((tr))
# define avlLastNode(tr)	avlMaximumNode((tr))
# define avlFirst(tr)		avlMinimum((tr))
# define avlLast(tr)		avlMaximum((tr))
# define avlSize(tr)		avlTotalNodes((tr))

# define AVLPreWalk		0
# define AVLInWalk		1
# define AVLPostWalk		2

/*----------------------------------------------------------------------*
 * Queue								*
 *----------------------------------------------------------------------*/

typedef struct QElem	QElem;
typedef QElem*		QELEM;
typedef struct Queue	Queue;
typedef Queue*		QUEUE;

# define qAdd(q,e)	qEnque((q),(void*)(e))
# define qRemove(q)	qDeque((q))
# define qSize(q)	qLength((q))

/*----------------------------------------------------------------------*
 * Heap									*
 *----------------------------------------------------------------------*/
typedef struct Heap	Heap;
typedef Heap*		HEAP;

# define HEAP_MAXIMIZE		0
# define HEAP_MINIMIZE		1

typedef DSKEYCMPFUN	HEAPCMPFUNC;

typedef void (*HEAPCHGFUNC)(void*,int);
typedef void (*HEAPWALKFUNC)(int,const DSKEY,void*);
typedef void (*HEAPPRINTFUNC)(int,void*,void*);

# define heapAdd(h,k,d)	heapInsert((h),(k),(d))

/*----------------------------------------------------------------------*
 * Hashing								*
 *----------------------------------------------------------------------*/

typedef unsigned (*HASHFUNC)(DSKEY);
typedef DSKEYCMPFUN	HASHCMPFUNC;

typedef struct hashtable	HashTable;
typedef HashTable*		HASHTABLE;

typedef struct Stack	Stack;
typedef Stack*		STACK;
typedef struct PArray	PArray;
typedef PArray*		PARRAY;

/*----------------------------------------------------------------------*
 * Set									*
 *----------------------------------------------------------------------*/
typedef struct _set	Set;
typedef Set*		SET;
typedef Set*		BAG;
typedef int (*SETCMPFUN)(void*,void*);

# define setAppend(s1,s2)	setUnion(s1,s2)

/*----------------------------- ( 139 lines) --------------------------*/
extern void * avlNodeKey(AVLNODE);
extern char * avlNodeKeyAsString(void *);
extern AVLTREE avlNewTree(int(*)(DSKEY,DSKEY),int,int);
extern void avlClose(AVLTREE);
extern void avlCloseWithFunction(AVLTREE,void(*)(void *));
extern void avlWalk(AVLTREE,void(*)(void *),int);
extern void avlWalkAscending(AVLTREE,void(*)(void *));
extern void avlWalkDescending(AVLTREE,void(*)(void *));
extern int avlHeight(AVLTREE);
extern int avlInsert(AVLTREE,const DSKEY,void *);
extern AVLNODE avlFindNode(AVLTREE,DSKEY);
extern void * avlFind(AVLTREE,DSKEY);
extern AVLNODE avlMinimumNode(AVLTREE);
extern void * avlMinimum(AVLTREE);
extern AVLNODE avlMaximumNode(AVLTREE);
extern void * avlMaximum(AVLTREE);
extern AVLNODE avlNextNode(AVLTREE,AVLNODE);
extern AVLNODE avlNextNodeByKey(AVLTREE,DSKEY);
extern AVLNODE avlPrevNode(AVLTREE,AVLNODE);
extern AVLNODE avlPrevNodeByKey(AVLTREE,DSKEY);
extern int avlGetData(AVLNODE,void **);
extern void * avlNodeData(AVLNODE);
extern void * avlNodeUpdateData(AVLNODE,void *);
extern void * avlUpdateData(AVLTREE,DSKEY,void *);
extern void * avlRemoveByKey(AVLTREE,DSKEY);
extern int avlRemoveNode(AVLTREE,AVLNODE);
extern int avlSetCurrent(AVLTREE,DSKEY);
extern int avlClearCurrent(AVLTREE);
extern void * avlCurrent(AVLTREE);
extern void * avlPrev(AVLTREE);
extern void * avlNext(AVLTREE);
extern void * avlCut(AVLTREE);
extern void avlFreeNode(void *);
extern int avlTotalNodes(AVLTREE);
extern AVLNODE avlRootNode(AVLTREE);
extern AVLNODE avlLeftNode(AVLNODE);
extern AVLNODE avlRightNode(AVLNODE);
extern int avlNodeHeight(AVLNODE);
extern int avlCheck(AVLTREE);
extern HASHTABLE htMake(int);
extern HASHTABLE htMakeHashTable(int,HASHFUNC,HASHCMPFUNC);
extern void htClose(HASHTABLE);
extern void htCloseWithFunction(HASHTABLE,void(*)(void*));
extern int htAdd(HASHTABLE,DSKEY,void *);
extern void * htFind(HASHTABLE,DSKEY);
extern void * htRemove(HASHTABLE,DSKEY);
extern int htSize(HASHTABLE);
extern int htItems(HASHTABLE);
extern int htEmpty(HASHTABLE);
extern int htConflicts(HASHTABLE);
extern void htWalk(HASHTABLE,int,void(*)(DSKEY,void *,int));
extern HEAP heapMake(void);
extern HEAP heapNew(int(*)(DSKEY,DSKEY),int,int,int);
extern void heapCloseWithFunction(HEAP,void(*)(void *));
extern void heapClose(HEAP);
extern HEAP heapMakeIntKeys(int,int,int);
extern HEAP heapMakeDoubleKeys(int,int,int);
extern HEAP heapMakeFloatKeys(int,int,int);
extern HEAP heapMakeStringKeys(int,int,int);
extern int heapSetChgFunc(HEAP,HEAPCHGFUNC);
extern int heapInsert(HEAP,const DSKEY,void *);
extern void * heapDelete(HEAP,int);
extern void * heapFirst(HEAP);
extern void * heapPeekFirst(HEAP);
extern void * heapElementAt(HEAP,int);
extern int heapSize(HEAP);
extern int heapEmpty(HEAP);
extern void heapWalk(HEAP,HEAPWALKFUNC);
extern void heapPrintArray(HEAP,HEAPPRINTFUNC);
extern void heapPrintTree(HEAP,HEAPPRINTFUNC);
extern int heapCheck(HEAP);
extern PARRAY paMake(int,int);
extern void paCloseWithFunction(PARRAY,void(*)(void *));
extern void paClose(PARRAY);
extern int paAdd(PARRAY,void *);
extern void * paRemove(PARRAY,int);
extern int paSize(PARRAY);
extern void * paReplace(PARRAY,int,void *);
extern int paContains(PARRAY,int(*)(void *,void *),void *);
extern void * paElementAt(PARRAY,int);
extern void * paCurrent(PARRAY);
extern void paSetCurrent(PARRAY,int);
extern void paClearCurrent(PARRAY);
extern void * paFirst(PARRAY);
extern void * paLast(PARRAY);
extern void * paNext(PARRAY);
extern void * paPrev(PARRAY);
extern QUEUE qMake(void);
extern void qClose(QUEUE);
extern void qCloseWithFunction(QUEUE,void(*)(void *));
extern QELEM qEnque(QUEUE,void *);
extern void * qDeque(QUEUE);
extern int qWalk(QUEUE,void(*)(void *));
extern int qWalkAscending(QUEUE,void(*)(void *));
extern int qWalkDescending(QUEUE,void(*)(void *));
extern int qLength(QUEUE);
extern int qEmpty(QUEUE);
extern void * qCurrent(QUEUE);
extern void qClearCurrent(QUEUE);
extern void qSetCurrent(QUEUE,QELEM);
extern void * qFirst(QUEUE);
extern void * qLast(QUEUE);
extern void * qNext(QUEUE);
extern void * qPrev(QUEUE);
extern void * qElemData(QELEM);
extern int qElemInsert(QUEUE,QELEM,QELEM);
extern int qElemAttach(QUEUE,QELEM);
extern int qElemDetach(QUEUE,QELEM);
extern void qElemFree(QELEM);
extern QELEM qElemFirst(QUEUE);
extern QELEM qElemLast(QUEUE);
extern QELEM qElemNext(QELEM);
extern QELEM qElemPrev(QELEM);
extern QELEM qElemCurr(QUEUE);
extern void * qElemRemove(QUEUE,QELEM);
extern SET setMake(void);
extern SET setNew(SETCMPFUN,int,int);
extern void setClose(SET);
extern void setCloseWithFunction(SET,void(*)(void *));
extern int setAdd(SET,void *);
extern void * setRemove(SET,void *);
extern void * setFirst(SET);
extern void * setNext(SET);
extern int setSize(SET);
extern int setEmpty(SET);
extern int setContains(SET,void *);
extern void * setFind(SET,void *);
extern SET setUnion(SET,SET);
extern SET setUnion1(SET,SET);
extern SET setIntersect(SET,SET);
extern SET setDifference(SET,SET);
extern SET setXIntersect(SET,SET);
extern STACK stkMake(void);
extern void stkCloseWithFunction(STACK,void(*)(void *));
extern void stkClose(STACK);
extern int stkPush(STACK,void *);
extern void * stkPop(STACK);
extern void * stkPeek(STACK);
extern int stkSize(STACK);
extern int stkEmpty(STACK);

# endif /* ! _LIBDS_H_ */

extern const char* nullstr(const char *);
extern const char* okfail(int);



