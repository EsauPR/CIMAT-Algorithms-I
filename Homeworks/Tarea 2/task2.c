/**
    ANSI C standard: c11
    task2.c
    Purpose: Implementation for SWAP macros

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>

#define GSWAP(a, b) {typeof(a) tmp = a; a = b; b = tmp;}
#define SWAP(a, b) (a ^= b ^= a ^= b)

int main() {
    int a1 = 4;
    int b1 = 5;
    double a2 = 4.0;
    double b2 = 5.0;

    puts("SWAP");
    printf("%d %d\n", a1, b1);
    SWAP(a1, b1);
    printf("%d %d\n", a1, b1);

    puts("\nSWAP Generic, int");
    printf("%d %d\n", a1, b1);
    GSWAP(a1, b1);
    printf("%d %d\n", a1, b1);

    puts("\nSWAP Generic, double");
    printf("%lf %lf\n", a2, b2);
    GSWAP(a2, b2);
    printf("%lf %lf\n", a2, b2);

    return 0;
}
