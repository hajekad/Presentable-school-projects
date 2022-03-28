#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TNode
{
    struct TNode * p_Next;
    int m_Value;
} TNODE;

/* Lze připsat i další metody */

bool isNeedle(TNODE * hayStack, TNODE * needle)
{
    while(needle)
    {
        if(hayStack->m_Value != needle->m_Value) return 0;

        hayStack = hayStack->p_Next;
        needle = needle->p_Next;
    }

    fprintf(stderr, "NEEDLE\n");

    return 1;
}

TNODE ** search(TNODE * hayStack, TNODE * needle)
{
    TNODE ** res = (TNODE **) malloc(sizeof(TNODE *));
    int noNeedles = 0;

    while(hayStack)
    {
        if(hayStack->m_Value ==  needle->m_Value)
        {
            if(isNeedle(hayStack, needle))
            {
                res[noNeedles] = (TNODE *) malloc(sizeof(TNODE));
                res = (TNODE **) realloc(res, (noNeedles + 2) * sizeof(TNODE *));

                res[noNeedles] = hayStack;
                
                noNeedles++;
            }
        }

        hayStack = hayStack->p_Next;
    }

    res[noNeedles] = NULL;

    return res;
}

int main(void)
{
 
    //1-2-1-2-3-4-1-2-3-8
 
    TNODE *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
    TNODE *x, *y, *z;
 
    a = (TNODE *) malloc(sizeof(TNODE));
    b = (TNODE *) malloc(sizeof(TNODE));
    c = (TNODE *) malloc(sizeof(TNODE));
    d = (TNODE *) malloc(sizeof(TNODE));
    e = (TNODE *) malloc(sizeof(TNODE));
    f = (TNODE *) malloc(sizeof(TNODE));
    g = (TNODE *) malloc(sizeof(TNODE));
    h = (TNODE *) malloc(sizeof(TNODE));
    i = (TNODE *) malloc(sizeof(TNODE));
    j = (TNODE *) malloc(sizeof(TNODE));
 
    a->m_Value = 1;
    a->p_Next = b;
    b->m_Value = 2;
    b->p_Next = c;
    c->m_Value = 1;
    c->p_Next = d;
    d->m_Value = 2;
    d->p_Next = e;
    e->m_Value = 3;
    e->p_Next = f;
    f->m_Value = 4;
    f->p_Next = g;
    g->m_Value = 1;
    g->p_Next = h;
    h->m_Value = 2;
    h->p_Next = i;
    i->m_Value = 3;
    i->p_Next = j;
    j->m_Value = 8;
    j->p_Next = NULL;
 
    x = (TNODE *) malloc(sizeof(TNODE));
    y = (TNODE *) malloc(sizeof(TNODE));
    z = (TNODE *) malloc(sizeof(TNODE));
 
    x->m_Value = 1;
    x->p_Next = y;
    y->m_Value = 2;
    y->p_Next = z;
    z->m_Value = 3;
    z->p_Next = NULL;
 
    TNODE ** aa = search(a, x);
 
    if (!aa) {
        printf("NULL\n");
        return 0;
    }
 
    printf("%p -- %p\n\n", (void *) c, (void *) g);
 
    for (int k = 0; aa[k] != NULL ; ++k) {
        printf("%d (%p) ", aa[k]->m_Value, (void *) aa[k]);
    }
 
    return 0;
}