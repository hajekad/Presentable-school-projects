#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct TItem {
    struct TItem * m_Next;
    char m_Val;
} TITEM;
 
TITEM * createItem (char val, TITEM * next)
{
    TITEM * n = (TITEM *) malloc(sizeof (TITEM));

    n->m_Val = val;
    n->m_Next = next;
    
    return n;
}

bool isPattern(TITEM * src, TITEM * last)
{
    //fprintf(stderr, "isPattern\n");
    TITEM * start = src;
    TITEM * HEAD = start;

    while(src)
    {
        //fprintf(stderr, "   HEAD: %c - src: %c\n", HEAD->m_Val, src->m_Val);

        if(HEAD == last)
        {
            if(HEAD->m_Val != src->m_Val) return 0;
            HEAD = start;
        }
        else if(HEAD->m_Val != src->m_Val)
        {
            //fprintf(stderr, "   return 0\n\n");
            return 0;
        }
        else HEAD = HEAD->m_Next;

        src = src->m_Next;
    }

    //fprintf(stderr, "\n");

    return 1;    
}

TITEM * createRes(TITEM * src, TITEM * last)
{
    TITEM * res = NULL;
    
    if(src == last)
    {
        res = createItem(src->m_Val, NULL);
        return res;
    }

    res = createItem(src->m_Val, createRes(src->m_Next, last));
    
    return res;
}
 
TITEM * getSeed (TITEM * x)
{
    TITEM * res = NULL;
    TITEM * HEAD = x;

    while(HEAD)
    {
        if(isPattern(x, HEAD))
        {
            res = createRes(x, HEAD);
            return res;
        }

        HEAD = HEAD->m_Next;
    }

    return res;
}

void deleteList (TITEM * list)
{
    //fprintf(stderr, "delList\n");
    if(list == NULL) return;

    deleteList(list->m_Next);

    free(list);
}

int main(void) {
 
    TITEM * root = createItem('a', createItem('2', createItem('3', createItem('a', createItem('2', createItem('3', createItem('a', createItem('2', createItem('3', createItem('a', createItem('2', createItem('3', NULL))))))))))));
    
    TITEM * output = getSeed(root);
    TITEM * tmp = root;

    while (tmp) {
        printf("%c ", tmp->m_Val);
        tmp = tmp->m_Next;
    }
 
    deleteList(root);

    printf("\n");
    
    tmp = output;
    while (tmp) {
        printf("%c ", tmp->m_Val);
        tmp = tmp->m_Next;
    }

    deleteList(output);
    return 0;
}