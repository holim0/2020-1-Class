# include "ds.h"

typedef struct StackElement
{
    void *			seData;
    struct StackElement *	seNext;
} StackElement;
struct Stack
{
    int			stTotal;
    StackElement *	stTop;
};

# define ST_TOP(stack)	 ((Stack*)stack)->stTop
# define ST_TOTAL(stack) ((Stack*)stack)->stTotal

STACK stkMake(void)
{
    Stack *	stack;

    STDMALLOC(stack,sizeof(Stack),NULL);

    stack->stTop = NULL;
    stack->stTotal = 0;

    return (STACK)stack;
}
void stkCloseWithFunction(STACK stack,void (*fun)(void*))
{
    StackElement *	stelem;

    stelem = ST_TOP(stack);
    while (stelem)
    {
	StackElement *	tmp;

	tmp = stelem;
	stelem 	= stelem->seNext;

	if (fun)
	    fun(tmp->seData);
	STDFREE(tmp);
    }

    /* Free the stack pointer itself */
    STDFREE( (void*) stack);

    return;
}
void stkClose(STACK stack)
{
    stkCloseWithFunction(stack,NULL);
}
int stkPush(STACK stack,void *elem)
{
    StackElement *	stelem;

    STDMALLOC(stelem,sizeof(StackElement),-1);

    stelem->seData	= elem;
    stelem->seNext	= ST_TOP(stack);
    ST_TOP(stack)	= stelem;
    ++ST_TOTAL(stack);

    return 0;
}
void *stkPop(STACK stack)
{
    StackElement *	stelem;
    void *		data;

    /* Pop the top element from the stack, decrease the stack element
     * count and return the data stored with the top element of the
     * stack.
     */
    stelem = ST_TOP(stack);
    if (!stelem)
	return NULL;

    ST_TOP(stack) = stelem->seNext;
    --ST_TOTAL(stack);

    data = stelem->seData;

    /* Get rid of the top element of the stack */
    STDFREE( stelem );

    return data;
}
void* stkPeek(STACK stack)
{
    StackElement *	stelem;

    stelem = ST_TOP(stack);

    if (!stelem)
    	return NULL;

    return stelem->seData;
}
int stkSize(STACK stack) { return ((Stack*)stack)->stTotal; }
int stkEmpty(STACK stack) { return stkSize(stack) == 0; }
