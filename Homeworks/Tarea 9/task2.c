/**
    ANSI C standard: c11
    task2.c
    Purpose: Find the Longest Palindromic Subsequence

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))


/*
    Find the max length of the a palindromic subsecuence

    This algorithm needs a squere matrix with dimentions equals to the string length.

    Each position (i,j) of the matrix represents the best solution for a substring
    with of length j-i, and characters positions given by the i-th character
    to the j-th character of the string.

    Note that if the size of the string is n, we need to compute n*(n+1)/2 values.
    So the time complexity is O(n^2)
    Also cause we need to store this values the space complexity is O(n^2) if we need
    to recover the palindromic substring or O(n) if we only need to know the max length
    of the palindormic substring.
*/
int find_max_palindromic_subsecuence(char * str, int size, int dp[][size]) {
    for (int i = 0; i < size; i++) {
        dp[i][i] = 1; // Each letter is a palindrome of lenght 1
    }

    // Generate substring of length 'length'
    for (int length = 1; length < size; length++) {
        // New substrings of length from i to i+length
        for (int i = 0; i + length < size; i++) {
            if (str[i] == str[i+length]) {
                // If the first and last letter of a substring are the same
                // the solution is 2 + the solution for the substring of length i+1 to i+length-1
                dp[i][i+length] = 2 + dp[i+1][i+length-1];
            } else {
                // If the first and last letter of a substring are diferents
                // the solution is the max length for the substring of length i+1 to i+length
                // or the substring of length i  to i+length-1
                dp[i][i+length] = MAX(dp[i][i+length-1], dp[i+1][i+length]);
            }
        }
    }

    // The solution is the value for a substring with dimensions 0 to size-1
    return dp[0][size-1];
}


/* Print the solution for the palindrome */
void print_palindrome(char * str, int size, int dp[][size], int i, int j) {
    if (i == j) {
        printf("%c", str[i]);
        return;
    }

    if (str[i] == str[j]) {
        printf("%c", str[i]);
        print_palindrome(str, size, dp, i+1, j-1);
        printf("%c", str[j]);
    } else if ( dp[i][j-1] > dp[i+1][j] ) {
           print_palindrome(str, size, dp, i, j-1);
    } else {
        print_palindrome(str, size, dp, i+1, j);
    }
}


int main(int argc, char const *argv[]) {
    int size;

    while(scanf("%d", &size) != EOF) {
        char str[size+1];
        scanf("%s", str);

        int dp[size][size];

        printf("Max length: %d, Palindrome: ", find_max_palindromic_subsecuence(str, size, dp));

        print_palindrome(str, size, dp, 0, size-1);
        puts("");
    }

    return 0;
}
