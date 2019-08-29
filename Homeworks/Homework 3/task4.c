/**
    ANSI C standard: c11
    task1.c
    Purpose: Pascal triangle with dynamic memory

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>


int ** allocate_pascal_triangle(int n) {
    int ** pascal_triangle = (int **) malloc(sizeof(int *) * n);
    *pascal_triangle = (int *) malloc(sizeof(int) * n * (n + 1) / 2);

    for (int i = 0, jump = 0; i < n; i++, jump += i) {
        pascal_triangle[i] = *pascal_triangle + jump;
    }
    return pascal_triangle;
}


void fill_pascal_triangle(int ** pascal_triangle, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                pascal_triangle[i][j] = 1;
                continue;
            }
            pascal_triangle[i][j] = pascal_triangle[i-1][j] + pascal_triangle[i-1][j-1];
        }
    }
}


void print_pascal_triangle(int ** pascal_triangle, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", pascal_triangle[i][j]);
        }
        puts("");
    }
}


int main() {
    int n = 0;

    scanf("%d", &n);

    int ** pascal_triangle = allocate_pascal_triangle(n);
    fill_pascal_triangle(pascal_triangle, n);
    print_pascal_triangle(pascal_triangle, n);

    free(pascal_triangle[0]);
    free(pascal_triangle);

    return 0;
}
