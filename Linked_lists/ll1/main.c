#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct TNode
{
    struct TNode * m_Next;
    char           m_Digit;
} TNODE;
 
TNODE * createNode ( char digit, TNODE * next )
{
    TNODE * n = (TNODE *) malloc (sizeof ( *n ));
    n -> m_Digit = digit;
    n -> m_Next = next;
    return n;
}
 
void deleteList (TNODE * l)
{
    while (l)
    {
        TNODE * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}

TNODE * copyList(TNODE * src, int * flag)
{
    if(src == NULL) return NULL;

    TNODE * des = NULL;

    des = createNode(src->m_Digit, copyList(src->m_Next, flag));

    if(des->m_Digit == 0 && des->m_Next == NULL) {*flag = 1; fprintf(stderr,"FLAG = 1\n");}

    return des;
}

int evaluate(char digit)
{
    if(isdigit(digit)) {return (digit - '0');}
    
    switch(digit)
    {
        case 'a':
            return 10;
        case 'b':
            return 11;
        case 'c':
            return 12;
        case 'd':
            return 13;
        case 'e':
            return 14;
        case 'f':
            return 15;
    }

    return 0;
}

char deevaluate(int digit)
{
    if(digit < 10){return (digit + '0');}

    switch (digit)
    {
    case 10:
        return 'a';
    case 11:
        return 'b';
    case 12:
        return 'c';
    case 13:
        return 'd';
    case 14:
        return 'e';
    case 15:
        return 'f';
    }

    return 'g';
}

TNODE * shiftRec(TNODE * res, unsigned int shift, int overflow)
{
    if(res == NULL) 
    {
        if(overflow){fprintf(stderr,"overflow\n"); return createNode(deevaluate(overflow), NULL);}
        else return NULL;
    }

    int val, valMod;

    val = evaluate(res->m_Digit);

    val =  (val << shift) + overflow;

    fprintf(stderr, "   val: %d\n", val);

    overflow = 0;

    valMod = val % 16;

    fprintf(stderr, "   valMod: %d\n", valMod);

    overflow = (val - valMod) >> 4;

    fprintf(stderr, "   overflow: %d\n", overflow);

    res->m_Digit = deevaluate(valMod);

    fprintf(stderr, "res->m_Digit: %c\n\n", res->m_Digit);

    res->m_Next = shiftRec(res->m_Next, shift, overflow);

    return res;
}

TNODE * shiftLeft ( TNODE * a, unsigned int shift )
{
    TNODE * res = NULL;
    int flag = 0;

    res = copyList(a, &flag);

    if(flag) return NULL;
    
    shiftRec(res, shift, 0);
    
    fprintf(stderr, "\n\n");

    return res;
}

int main (int argc, char * argv [])
{
TNODE * a = NULL, * res = NULL;
a = createNode ( '3',
      createNode ( '2',
        createNode ( '1', NULL )));
res = shiftLeft ( a, 1 );
assert ( res -> m_Digit == '6' );
assert ( res -> m_Next -> m_Digit == '4' );
assert ( res -> m_Next -> m_Next -> m_Digit == '2' );
assert ( res -> m_Next -> m_Next -> m_Next == NULL );
deleteList ( a );
deleteList ( res );
 
a = createNode ( 'f',
      createNode ( 'a',
        createNode ( '1', NULL )));
res = shiftLeft ( a, 3 );
assert ( res -> m_Digit == '8' );
assert ( res -> m_Next -> m_Digit == '7' );
assert ( res -> m_Next -> m_Next -> m_Digit == 'd' );
assert ( res -> m_Next -> m_Next -> m_Next == NULL );
deleteList ( a );
deleteList ( res );
 
a = createNode ( 'c',
      createNode ( '5',
        createNode ( '4',
          createNode ( 'd',
            createNode ( '1', NULL )))));
res = shiftLeft ( a, 5 );
assert ( res -> m_Digit == '0' );
assert ( res -> m_Next -> m_Digit == '8' );
assert ( res -> m_Next -> m_Next -> m_Digit == 'b' );
assert ( res -> m_Next -> m_Next -> m_Next -> m_Digit == '8' );
assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == 'a' );
assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Digit == '3' );
assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
deleteList ( a );
deleteList ( res );
 
a = createNode ( 'a',
      createNode ( 'w',
        createNode ( '0', NULL )));
res = shiftLeft ( a, 12 );
assert ( res == NULL );
deleteList ( a );
 
a = NULL;
res = shiftLeft ( a, 1 );
assert ( res == NULL );
return 0;
}