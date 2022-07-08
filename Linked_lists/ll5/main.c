#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct POly
{
    struct POly *   m_next;
    int             m_pow;
    int             m_digit;
}POLY_t;

POLY_t * createPoly(int pow, int digit, POLY_t * next)
{
    POLY_t * res = (POLY_t *) malloc(sizeof(POLY_t));

    res->m_digit = digit;
    res->m_pow = pow;
    res->m_next = next;
    
    return res;
}

void destroyAll(POLY_t * HEAD)
{
    POLY_t * next = NULL;

    while (HEAD)
    {
        next = HEAD->m_next;

        free(HEAD);
        
        HEAD = next; 
    }
}

int comparator(int a, int b)
{
    int res = a - b;

    if(res > 0) return 1;
    else if(res < 0) return -1;
    else return 0;
}

POLY_t * polyAdd(POLY_t * a, POLY_t * b)
{
    POLY_t * res = NULL;

    if(a || b)
    {
        int cmp;

        if(a && b) cmp = comparator(a->m_pow, b->m_pow);
        else if(a) cmp = -1;
        else cmp = 1;

        switch (cmp)
        {
            case 1:
                res = createPoly(b->m_pow, b->m_digit, polyAdd(a, b->m_next));
                break;
        
            case -1:        
                res = createPoly(a->m_pow, a->m_digit, polyAdd(a->m_next, b));
                break;
        
            default:
                res = createPoly(b->m_pow, b->m_digit + a->m_digit, polyAdd(a->m_next, b->m_next));
                break;
        } 
    }
    
    return res;
}

void printList (POLY_t * head)
{
    while (head)
    {
        fprintf(stderr, "%d * x^%d\n", head->m_digit, head->m_pow);

        head = head->m_next;
    }

    fprintf(stderr, "NULL\n");
}

int main(void)
{
    POLY_t * a = NULL;
    POLY_t * b = NULL;
    POLY_t * res = NULL;

    a = createPoly(0, 9, createPoly(1, 3, createPoly(4, 6, NULL)));
    b = createPoly(0, 2, createPoly(2, -3, createPoly(4, 3, NULL)));

    res = polyAdd(a, b);
    //printList(res);

    assert(res->m_digit == 11 && res->m_pow == 0);
    assert(res->m_next->m_digit == 3 && res->m_next->m_pow == 1);
    assert(res->m_next->m_next->m_digit == -3 && res->m_next->m_next->m_pow == 2);
    assert(res->m_next->m_next->m_next->m_digit == 9 && res->m_next->m_next->m_next->m_pow == 4);

    a = NULL;
    b = NULL;
    res = NULL;

    a = createPoly((rand()), 0, createPoly(500,78 , createPoly(50588, 98, NULL)));
    b = createPoly(10000, 8, createPoly((rand() %10000000), (rand() %10000000), createPoly(50588, 2, createPoly(87878,-500, createPoly(88900,58,NULL)))));

    res = polyAdd(a, b);
    printList (a);
    printList(b);
    printList(res);

    destroyAll(a);
    destroyAll(b);
    destroyAll(res);

    a = NULL;
    b = NULL;
    res = NULL;

    res = polyAdd(a, b);
    //printList (a);
    //printList(b);
    //printList(res);

    destroyAll(a);
    destroyAll(b);
    destroyAll(res);
}
