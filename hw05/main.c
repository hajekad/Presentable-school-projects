/*
*   Filename:               hw05.c
*   Date & time:            25/11/2021
*   Author:                 Adam Hajek
*
*   Short description:      This code is a solution for school assignment PROGTEST-HW05.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define T_MAX 100

typedef struct 
{
    int quantity;
    char type[T_MAX];
} ITEM;

int sortbyquantity (const void * a, const void * b)
{ 
    
    const ITEM *p = (const ITEM *) a;
    const ITEM *q = (const ITEM *) b;

    if (p->quantity > q->quantity) {
        return -1;
    
    } else if (p->quantity < q->quantity) {
        return 1;
    
    } else {
        return 0;
    }
}

int main ()
{
    
    char o, tmp[101];
    int displayed_items, j = 0, to;
    
    bool QWS = false;
    int I_S_size = 100;

    ITEM *ITEM_SUMMARY = (ITEM *) calloc(I_S_size, sizeof(ITEM));
    
    //output + 1st user input + output
    printf("Pocet sledovanych:\n");

    if(scanf("%d", &displayed_items) != 1 || displayed_items <= 0)
    {
        printf("Nespravny vstup.\n");
        free(ITEM_SUMMARY);
        return 0;
    }
    printf("Pozadavky:\n");

    //some interesting stuff
    while(~scanf(" %c", &o)) 
    {
        //new input, yay!!! reallocation does not work the array of all inputs is just 10 strings
        if(o == '+') 
        {
            if(scanf(" %100s ", tmp) != 1 || (int)strlen(tmp) > 99) 
            {
                printf("Nespravny vstup.\n");
                free(ITEM_SUMMARY);
                return 0;
            }

            //quantity got a raise, yaaaaaaay!!!
            for(int i = 0; i < j; i++)
            {
                if( strncmp(tmp, ITEM_SUMMARY[i].type, sizeof(tmp)) == 0)
                {
                    ITEM_SUMMARY[i].quantity++;
                    QWS = 1;
                    
                    break;
                }
            }

            //new product line for our trade 
            if(QWS == 0)
            {
                if(j == I_S_size - 1)
                {
                    I_S_size += 10;
                    ITEM_SUMMARY= (ITEM *) realloc(ITEM_SUMMARY, I_S_size  * sizeof(ITEM));
                }
                
                strcpy(ITEM_SUMMARY[j].type, tmp);
                ITEM_SUMMARY[j].quantity = 1;
                j++;
            }
            //flag 
            QWS = 0;
        
        //here starts #
        } else if(o == '#')
        {
            qsort(ITEM_SUMMARY, j, sizeof(ITEM), sortbyquantity);
            
            if (displayed_items > j) to = j;
            else to = displayed_items;
            int sum_of_disp = 0;

            
            for(int i = 0; i < to; i++)
            {
                int repeator = 0;

                sum_of_disp += ITEM_SUMMARY[i].quantity;

                for (int u = i; ITEM_SUMMARY[u].quantity == ITEM_SUMMARY[u + 1].quantity; u++)
                {
                    repeator++;
                }

                if (repeator == 0)
                {
                    printf ("%d. %s, %dx\n", i + 1, ITEM_SUMMARY[i].type, ITEM_SUMMARY[i].quantity);
                } 
                else
                {
                    for (int q = 0; q <= repeator; q++)
                    {
                        printf("%d.-%d. %s, %dx\n", i + 1, i + 1 + repeator, ITEM_SUMMARY[i + q].type, ITEM_SUMMARY[i + q].quantity);
                    }
                    i += repeator;

                    sum_of_disp += ITEM_SUMMARY[i].quantity * repeator;
                }

                if (i == to - 1 && ITEM_SUMMARY[i].quantity == ITEM_SUMMARY[i + 1].quantity) to++;
            }

            printf("Nejprodavanejsi zbozi: prodano %d kusu\n", sum_of_disp);                
            
        } else if(o == '?')
        {
            qsort(ITEM_SUMMARY, j, sizeof(ITEM), sortbyquantity);
            
            if (displayed_items > j) to = j;
            else to = displayed_items;
            int sum_of_disp = 0;

            
            for(int i = 0; i < to; i++)
            {
                int repeator = 0;

                sum_of_disp += ITEM_SUMMARY[i].quantity;

                for (int u = i; ITEM_SUMMARY[u].quantity == ITEM_SUMMARY[u + 1].quantity; u++)
                {
                    repeator++;
                }

                if (repeator != 0)
                {                
                    i += repeator;

                    sum_of_disp += ITEM_SUMMARY[i].quantity * repeator;
                }

                if (i == to - 1 && ITEM_SUMMARY[i].quantity == ITEM_SUMMARY[i + 1].quantity) to++;
            }

            printf("Nejprodavanejsi zbozi: prodano %d kusu\n", sum_of_disp);
        }
        else
        {
            //Nespravny vstup.\n
            printf("Nespravny vstup.\n");
            free(ITEM_SUMMARY);
            return 0;
        }
    }

    free(ITEM_SUMMARY);
    return 0;
}
