#include <stdio.h>
#include <stdbool.h>

int main(void){
    //defining condition statements
    int logs[1000000];
    int numerosity[100000];
    bool query[100000];
    char o;
    int id, from, to, sum, from_to_difference;
    int logs_counter = 0;

    //program starts interacting with the user here
    printf("Pozadavky:\n");

    //if stdins buffer has + or ? program won't end itself and will process the input
    while (~scanf(" %c", &o)){
        // ? -> query for logs
        if (o == '?'){
            //securing the user input
            if (scanf (" %d %d", &from, &to) != 2 || from > to || to >= logs_counter || from < 0) {
                printf("Nespravny vstup.\n");
                return 0;
            }
            //this is a statement used later in this code
            from_to_difference = to - from + 1;

            //counting logs[i] from from_id to to
            sum = 0;
            for (int i = from; i <= to; i++) {
                if (query[logs[i]] == 0){
                    sum++;
                }
                query[logs[i]] = 1;
            }
            //lowering to querry[i]if > 1 to 1(uniq); sum of the lowered array query; null of array querry[i]
            for (int i = from; i <= to; i++) {
                query[logs[i]] = 0;
            }
            //program output for ?
            printf("> %d / %d\n", sum, from_to_difference);
        // + -> user input
        }else if (o == '+'){
            // securing the user input
            if (scanf(" %d", &id) != 1 || id > 99999 || id < 0) {
                printf("Nespravny vstup.\n");
                return 0;
            }

            //writing to array logs and raising numerosity of an id by 1
            logs[logs_counter] = id;
            numerosity[id]++;

            //prvni navsteva or nav. #numerrosity of id
            if (numerosity[id] == 1) {
                printf("> prvni navsteva\n");
            } else {
                printf("> navsteva #%d\n", numerosity[id]);
            }
            //condition statement for wrtiting in to logs
            logs_counter++;
        // lulw user = dumb
        }else {
            printf ("Nespravny vstup.\n");
            return 0;
        }
    }
    //this is literally useless right now...
    return 0;
}