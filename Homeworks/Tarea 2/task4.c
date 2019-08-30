/**
    ANSI C standard: c11
    task3.c
    Purpose: Get the exponent of the representation mantissa-exponent for a float

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>


char get_exponent(float num) {
    // Cast the memory address to unsigned int * to preserve the bits
    unsigned int * exp = (unsigned int *)&num;
    // Shift 23 positions to remove the mantisa and get the exponent
    *exp = (*exp) >> 23;
    // Substract 127 to get the exp e = k - (2^(q-1) - 1) con q = 8
    *exp = *exp - 127;
    // Cast to char * to get only the first 8 bits
    return *(char*)exp;
}

int main() {
    float num;

    printf("Obtener el exponente del float: ");
    scanf("%f", &num);
    printf("Exponente: %d\n", get_exponent(num));

    return 0;
}
