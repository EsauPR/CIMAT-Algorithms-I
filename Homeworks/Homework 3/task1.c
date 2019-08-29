/**
    ANSI C standard: c11
    task1.c
    Purpose: c structure padding

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>

int main() {
    struct myStruct {
        char a;
        char * b;
        char c;
    } ms;

    printf("Structure Size %lu\n\n", sizeof ms);
    printf("'a' adress %p\n", &ms.a);
    printf("'b' adress %p\n", &ms.b);
    printf("'c' adress %p\n", &ms.c);

    return 0;
}
