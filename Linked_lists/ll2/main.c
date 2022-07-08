#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct TItem {
 struct TItem * m_Next;
  char *m_Word;
}TITEM;

TITEM * createItem(char * Word, TITEM * Next)
{
    TITEM * res = (TITEM *) malloc(sizeof(TITEM));
    res->m_Word = (char *) malloc(strlen(Word) + 1);

    strcpy(res->m_Word, Word);
    res->m_Next = Next;

    return res;
}
 
TITEM* StringToList( const char * string )
{
    TITEM * res = NULL;
    TITEM * HEAD = NULL;
    int cWLen = 1;
    char * currWord = (char *) malloc(cWLen);
    int i = 0;
    bool flag = 0;

    while(string[i] != '\0')
    {
        if(isspace(string[i]))
        {
            if(flag)
            {
                flag = 0;
                currWord[cWLen - 1] = '\0';

                if(res)
                {
                    HEAD->m_Next = createItem(currWord, NULL);
                    HEAD = HEAD->m_Next;
                }
                else
                {
                    res = createItem(currWord, NULL);
                    HEAD = res;
                }

                free(currWord);
                cWLen = 1;
                currWord = (char *) malloc(cWLen);
            }
        }
        else
        {
            flag = 1;
            cWLen++;
            currWord = (char *)realloc(currWord, cWLen);

            currWord[cWLen - 2] = string[i];
        }

        i++;
    }

    free(currWord);
    
    return res;
}
 
void FreeList ( TITEM* List )
{
    if(!List) return;

    FreeList(List->m_Next);

    free(List->m_Word);
    free(List);
}

void printList(TITEM * head)
{
	while(head)
    {
	    printf("word: \"%s\" ",head->m_Word);
	    head = head->m_Next;
	}
	printf("\n");
}

int main (void)
{
	TITEM * l;
	l = StringToList("     T \tishfjh  s s  S hjgyc uytfutycjhcv yfyvkhv vouogoug b   kug     ukgkug  h   ");	
	printList(l);
	FreeList(l);
	return 0;
}