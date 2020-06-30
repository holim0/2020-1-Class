# include "ds.h"

struct PArray
{
    int	    curr_size;
    int	    grow_by;
    int	    num_elems;
    void**  elements;
    int	    curr;
};

PARRAY
paMake(int init_size,int grow_by)
{
    PArray *	parray;

    /* Allocate the PArray structure */
    STDMALLOC(parray,sizeof(PArray),NULL);

    /* Allocate enough space for init_size elements */
    STDMALLOC(parray->elements,sizeof(void*) * init_size,NULL);

    parray->num_elems = 0;
    parray->curr_size = init_size;
    parray->grow_by   = grow_by;
    parray->curr      = -1;

    return (PARRAY)parray;
}
void
paCloseWithFunction(PARRAY pa,void (*f)(void*))
{
    PArray *	parray = (PArray*)pa;
    int i;
    for (i = 0; i < parray->num_elems; i++)
    {
	if (parray->elements[i] && f)
	    f(parray->elements[i]);
    }
    STDFREE(parray->elements);
    STDFREE(parray);
}
void
paClose(PARRAY pa)
{
    STDFREE(((PArray*)pa)->elements);
    STDFREE( pa );
}
# define NeedsToGrow(p)	    ((p)->num_elems >= (p)->curr_size)
# define NeedsToShrink(p)   \
	((p)->num_elems <= (p)->curr_size - (p)->grow_by)

static int
pa_grow(PArray *parray)
{
    int new_size = parray->curr_size + parray->grow_by;

    if (parray->num_elems < parray->curr_size)
	return 0;   /* Still space available */

    STDREALLOC(parray->elements,sizeof(void*) * new_size,-1);

    parray->curr_size = new_size;

    return 0;
}
static int
pa_shrink(PArray *parray)
{
    int new_size = parray->curr_size - parray->grow_by;

    STDREALLOC(parray->elements,sizeof(void*) * new_size,-1);

    parray->curr_size = new_size;

    return 0;
}
static int
pa_shift(PArray * parray,int from,int num)
{
    memmove(parray->elements + from,
    	    parray->elements + from + num,
	    (parray->num_elems - from - num) * sizeof(void*));

    parray->num_elems -= num;
    if (NeedsToShrink(parray))
	pa_shrink(parray);

    return 0;
}
/*----------------------------------------------------------------------*
 * Add an element to this array. Returns -1 on failure, the index in 	*
 * the array on success.						*
 *----------------------------------------------------------------------*/
int
paAdd(PARRAY pa,void * elem)
{
    PArray * parray = (PArray*) pa;

    if (NeedsToGrow(parray) && pa_grow(pa))
	return -1;

    /* Add the element to the end of the array */
    parray->elements[parray->num_elems] = elem;
    parray->curr = parray->num_elems;

    return parray->num_elems++;
}
void*
paRemove(PARRAY pa,int idx)
{
    PArray * parray = (PArray*) pa;
    void *data;

    if (idx < 0 || idx >= ((PArray*)pa)->num_elems)
	return NULL;

    data = parray->elements[idx];

    /* Shift all by one */

    pa_shift(parray,idx,1);

    return data;
}

int
paSize(PARRAY pa)
{
    return ((PArray*)pa)->num_elems;
}
void*
paReplace(PARRAY pa,int idx,void *new_elem)
{
    void * old_elem;
    PArray * parray = (PArray*) pa;

    if (idx < 0 || idx >= parray->num_elems)
	return NULL;
    old_elem = parray->elements[idx];
    parray->elements[idx] = new_elem;
    return old_elem;
}
int
paContains(PARRAY pa,int (*cmpfun)(void*,void*),void *elem)
{
    int i;
    PArray * parray = (PArray*) pa;

    for (i = 0; i < parray->num_elems; ++i)
	if (cmpfun(parray->elements[i],elem))
	    return i;
    return -1;
}
void*
paElementAt(PARRAY pa,int idx)
{
    if (idx < 0 || idx >= ((PArray*)pa)->num_elems)
	return NULL;
    return ((PArray*)pa)->elements[idx];
}
void*
paCurrent(PARRAY pa)
{
    PArray * parray = (PArray*)pa;

    if (parray->curr < 0)
	return NULL;
    return parray->elements[parray->curr];
}
void
paSetCurrent(PARRAY pa,int i)
{
    PArray * parray = (PArray*)pa;

    if (i < 0 || i >= parray->num_elems)
	i = -1;

    ((PArray*)pa)->curr = i;
}
void
paClearCurrent(PARRAY pa)
{
    paSetCurrent(pa,-1);
}
void*
paFirst(PARRAY pa)
{
    PArray * parray = (PArray*)pa;

    if (parray->num_elems < 1)
	return NULL;

    return parray->elements[parray->curr = 0];
}
void*
paLast(PARRAY pa)
{
    PArray * parray = (PArray*)pa;

    if (parray->num_elems < 1)
	return NULL;
    return parray->elements[parray->curr = parray->num_elems - 1];
}
/*
 * Return the next element in the array. If currency has not been set
 * then the first element is returned. If no next element is present.
 * null is returned.
 */
void*
paNext(PARRAY pa)
{
    PArray * parray = (PArray*)pa;

    if (parray->curr < 0)
	return paFirst(pa);
    if (parray->curr + 1 == parray->num_elems)
    {
	parray->curr = -1;
	return NULL;
    }

    return parray->elements[++parray->curr];
}
/*
 * Return the previous element in the array. If currency has not been set
 * then the last element is returned. If no previous element is present.
 * null is returned.
 */
void*
paPrev(PARRAY pa)
{
    PArray * parray = (PArray*)pa;

    if (parray->curr < 0)
	return paLast(pa);
    if (parray->curr - 1 == -1)
    {
	parray->curr = -1;
	return NULL;
    }

    return parray->elements[--parray->curr];
}
