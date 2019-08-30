/**
    ANSI C standard: c11
    task3.c
    Purpose: Rewrite sentences "for" by "do while"

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>


int main() {
    // for (int i = 0; i < 100; i += 2) {
    //     if (i % 7 == 0) {
    //         continue;
    //     }
    //     printf("%d\n", ++i);
    // }

    int i=0;

    do {
        if (i % 7 == 0) {
            i += 2;
            continue;
        }
        printf("%d\n", ++i);
        i += 2;
    } while (i < 100);


    return 0;
}
