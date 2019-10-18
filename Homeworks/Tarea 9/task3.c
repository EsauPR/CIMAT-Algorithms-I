/**
    ANSI C standard: c11
    task3.c
    Purpose: Problem 3

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compute the Probability */
double prob(int n, int p, int a, double dp[n][n]) {
    if (p == a) {
        return 0.5;
    }

    if (p == n) {
        return 1.0;
    }

    if (a == n) {
        return 0.0;
    }

    if (dp[p][a] != -1.0) {
        return dp[p][a];
    }

    return dp[p][a] = 0.5 * prob(n, p+1, a, dp) + 0.5 * prob(n, p, a+1, dp);
}


int main(int argc, char const *argv[]) {
    int n, p, a;

    while (scanf("%d %d %d", &n, &p, &a) != EOF) {
        double dp[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = -1.0;
            }
        }

        printf("Prob: %lf\n", prob(n, p, a, dp));
    }

    return 0;
}
