/*
*   Filename:               hw07.c
*   Date & time:            07/12/2021
*   Author:                 Adam Hajek
*
*   Short description:      This code is a solution for school assignment PROGTEST-HW07.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//////////////////////////////////////////////////////////////////////////////////////

 char * get_abbreviation(void)
{
    char * abbrev = NULL;
    size_t len = 0;


    getline(&abbrev, &len, stdin);
    int i = 0;
    while(abbrev[i] != '\n')
    {
        if(!isupper(abbrev[i]))
        {
            free(abbrev);
            printf("Nespravny vstup.\n");
            return 0;
        }
        i++;
    }
    /*
    for(int i = 0; i < abbrev_read; i++)
        if(abbrev[i] != toupper(abbrev[i]))
        {
            free(abbrev);
            printf("Nespravny vstup.\n");
            return 0;
        }
        */
    
    len = 0;

    return abbrev;
}

//////////////////////////////////////////////////////////////////////////////////////

int skip_to_space(char * expression, int tmp)
{
    
    while(!isspace(expression[tmp]))
    {
        tmp++;
    }

    return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////

void print_list(char * expression, int * to_upper)
{
    int temp = to_upper[0];
    int j = 0;
    int qmark_count = 0;

    
    for(int i = 0; qmark_count < 2; i++)
    {
        if(expression[i] == '"') qmark_count++;
        if(i == temp)
        {
            j++;
            temp = to_upper[j];
            printf("%c", toupper(expression[i]));
        }
        else
        {
        printf("%c", expression[i]);
        }    
    }
    printf("\n");
/*
    for(int i = 0; to_upper[i] != '\0'; i++)
    {
        fprintf(stderr,"%d ", to_upper[i]);
    }
    fprintf(stderr, "\n");
*/
}

int other_letters(char oper, int solutions_count, int * to_upper, char * abbrev, char * expression, int exp_position, int exp_read, int abbrev_position, int lett_in_w_curr, int letters_in_word)
{
    abbrev_position++;
    char current_letter = (tolower(abbrev[abbrev_position]));
    int i = exp_position; 
    int tmp;
    int haha;
    int abbrev_len = strlen(abbrev) - 1;

    if(!isalpha(current_letter)) 
    {
        solutions_count++;
        if(oper == '?')
        {
            print_list(expression, to_upper);
        }
        return solutions_count;
    }
    if(isspace(expression[i])) lett_in_w_curr = 0;
    while(i < exp_read - 1)
    {
        tmp = i;
        if(isspace(expression[i])) lett_in_w_curr = 0;
        
        if(expression[i] == current_letter)
        {
            to_upper[abbrev_position] = i;
            haha = lett_in_w_curr++;
            if((lett_in_w_curr == letters_in_word) && (abbrev_len > letters_in_word))
            {
                tmp = skip_to_space(expression, tmp);
                //printf("tmp: %d\n", tmp);
                lett_in_w_curr = 0;
            }
            solutions_count = other_letters(oper, solutions_count, to_upper, abbrev, expression, tmp + 1, exp_read, abbrev_position, lett_in_w_curr, letters_in_word);
            lett_in_w_curr = haha;
        }
        i++;
    }

    return solutions_count;
}


int list(char oper, char * expression, char * abbrev, int exp_read, int letters_in_word)
{
    int solutions_count = 0; 
    int j = 0;
    char abbrev_first = abbrev[j];
    int to_upper_t = strlen(abbrev);
    int * to_upper = (int *) calloc(to_upper_t, sizeof(int));
    char lower_abbrev_first = tolower(abbrev_first);
    int lett_in_w_curr = 0;
    int tmp;
    int haha;

    for(int i = 1; i < exp_read - 1; i++)
    {
        tmp = i;
        if(isspace(expression[i])) lett_in_w_curr = 0;
        if((expression[i]) == lower_abbrev_first)
        {
            to_upper[0] = i;
            haha = lett_in_w_curr++;

            if((lett_in_w_curr == letters_in_word) && (to_upper_t - 1 > letters_in_word))
            {
                tmp = skip_to_space(expression, tmp);
                lett_in_w_curr = 0;
            }

            solutions_count = other_letters(oper, solutions_count, to_upper, abbrev, expression, tmp + 1, exp_read, j, lett_in_w_curr, letters_in_word);
            lett_in_w_curr = haha;
        }
    }
    if(oper == '?')
    {
        printf("> %d\n", solutions_count);
    }
    else
    {
        printf("> limit %d: %d\n", letters_in_word, solutions_count);
    }
    free(to_upper);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////

int limit(char * expression, char * abbrev, int exp_read, int letters_in_word)
{
    for(int i = 1; i <= letters_in_word; i++)
    {
        list('#', expression, abbrev, exp_read, i);
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
int problem(char * abbrev, char oper, int letters_per_word)
{
    size_t len = 0;
    char * expression = NULL;
    ssize_t exp_read;
    int exp_first = 0; 
    int exp_last = 0;
    int i = 1;   

    exp_read = getline(&expression, &len, stdin);
    //mark first "
    while(expression[exp_first] != '"' && expression[exp_first] != '\0')
    {
        exp_first++;
    }
    exp_last = exp_first + 1;
    //mark second "
    while(expression[exp_last] != '"' && expression[exp_last] != '\0')
    {
        exp_last++;
    }
    //lower the expression
    i = exp_first;
    while(i < exp_last)
    {
        expression[i] = tolower(expression[i]);
        i++;
    }

    if(oper == '?' && letters_per_word > 0 && expression[exp_first] == '"' && expression[exp_last] == '"' && exp_read != 0)
    {
        list(oper, expression, abbrev, exp_read, letters_per_word);
    }
    else if(oper == '#' && letters_per_word > 0 && expression[exp_first] == '"' && expression[exp_last] == '"' && exp_read != 0)
    {
        limit(expression, abbrev, exp_read, letters_per_word);
    }
    else
    {
        printf("Nespravny vstup.\n");
        free(expression);
        return 1;
    }

    free(expression);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    int letters_per_word = 0;
    char oper = 0;
    char * abbrev = NULL;
    
    printf("Zkratka:\n");
    abbrev = get_abbreviation();
    if(abbrev == 0) {return 0; free(abbrev);}

    printf("Problemy:\n");
    while(~scanf("%c", &oper))
    {
        if(scanf(" %d ", &letters_per_word) != 1)
        {
            printf("Nespravny vstup.\n");
            free(abbrev);
            return 0;
        }
        if(problem(abbrev, oper, letters_per_word))
        {
            free(abbrev);
            return 0;
        } 
    }
    
    free(abbrev);
    return 0;
}
