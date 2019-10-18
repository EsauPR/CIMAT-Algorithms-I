/**
    ANSI C standard: c11
    task1.c
    Purpose: 0-1 Knapsack problem

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define NEXT(i) (((i) + 1) % 2)
#define CURRENT(i) ((i) % 2)


/* Solve the 0/1 knapsack problem with O(w) memory complexity*/
int knapsack(int dp[][2], int * w, int * v, int max_weight, int nitems) {

    for (int i = 0; i < max_weight + 1; i++) {
        dp[i][0] = dp[i][1] = 0;
    }

    int i = 1;
    for (; i <= nitems; i++) {
        for (int j = 1; j <= max_weight; j++) {
            // Take by default the max value for i-1 items for a knapsack with j as capacity
            dp[j][CURRENT(i)] = dp[j][NEXT(i)];
            // If we can take a item with weight i and have a knapsack with weight j
            if (w[i] <= j) {
                // Choose the best decision of take the max value
                // for i-1 items and a knapsack with j as capacity
                // or take the i-th item and the best value of solve the problem for weight j - w[i]
                dp[j][CURRENT(i)] = MAX(dp[j][CURRENT(i)], v[i] + dp[j - w[i]][NEXT(i)]);
            }
        }
    }

    return dp[max_weight][NEXT(i)];
}


int main(int argc, char const *argv[]) {

    int max_weight, nitems;
    // Read max_number of items and max weight to carry
    scanf("%d %d", &nitems, &max_weight);

    int w[nitems + 1]; // Array of weights
    int v[nitems + 1]; // Array of values

    // Memory for 2 * (max_weight + 1) integers
    // Then the algorithm have a memory complexity cost of O(max_weight)
    int dp[max_weight + 1][2];

    w[0] = v[0] = 0;
    memset(w, 0, sizeof(int) * (nitems + 1));
    memset(v, 0, sizeof(int) * (nitems + 1));

    // Read each value and weight
    for (int i = 1; i <= nitems; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }

    // Solution
    printf("Max Value: %d\n", knapsack(dp, w, v, max_weight, nitems));

    return 0;
}
