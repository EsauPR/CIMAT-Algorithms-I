/**
    ANSI C standard: c11
    main.c
    Purpose: Tarea 5

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 30

/* Transform a character to lowercase and ignore non alphabetic characters */
char parse_char(char c) {
    if (65 <= c && c <= 90) {
        return c + 32;
    }

    if (97 <= c && c <= 122) {
        return c;
    }

    return ' ';
}

/* Read 'nwords' from a file and return the number of already read words */
int read_words(const char * file_name, char words[][WORD_SIZE], int nwords) {
    FILE *fp = fopen(file_name, "r");
    char tmp ;

    int nwords_read = 0;
    for (int i = 0, char_pos = 0; i < nwords; i++, char_pos = 0) {
        while(fscanf(fp, "%c", &tmp) != EOF) {
            tmp = parse_char(tmp);
            if (tmp == ' ') { // End of word
                if (char_pos == 0) { // unread word
                    i--;
                }
                break;
            }
            words[i][char_pos++] = tmp;
        }
        if (char_pos != 0) { // There is a new Word
            words[i][char_pos] = '\0';
            nwords_read++;
        }
    }

    fclose(fp);

    return nwords_read;
}

/* Merge implementation for Merge Sort Algorithm */
void merge(char words[][WORD_SIZE], int nwords, int middle) {
    char tmp[nwords][WORD_SIZE];

    for (int i = 0, j = middle, k = 0; k < nwords; k++) {
        if (j == nwords) {
            strcpy(tmp[k], words[i++]);
        } else if (i == middle) {
            strcpy(tmp[k], words[j++]);
        } else if (strcmp(words[i], words[j]) <= 0) {
            strcpy(tmp[k], words[i++]);
        } else {
            strcpy(tmp[k], words[j++]);
        }
    }

    for (int i = 0; i < nwords; i++) {
        strcpy(words[i], tmp[i]);
    }
}


/* Merge Sort Algorithm implementation for a words array */
void merge_sort(char words[][WORD_SIZE], int nwords) {
    if (nwords < 2) return;
    int middle = nwords / 2;
    merge_sort(words, middle);
    merge_sort(words + middle, nwords - middle);
    merge(words, nwords, middle);
}

/*
    Copy the 'words' without out repetitions to 'unq_words'
    The 'words' array must be ordered
    Return the number of unique words
*/
int copy_unique_words(char words[][WORD_SIZE], char unq_words[][WORD_SIZE], int nwords) {
    int nunq_words = 0;

    for (int i = 0; i < nwords; i++) {
        if (nunq_words > 0 && strcmp(unq_words[nunq_words - 1], words[i]) == 0) {
            // Same word
            continue;
        }
        strcpy(unq_words[nunq_words++], words[i]);
    }

    return nunq_words;
}

/* Binary Search implementation to look for a 'word' in 'words' array */
int search_word(char words[][WORD_SIZE], int nwords, char * word) {
    int i = 0, j = nwords, middle, cmp;

    while(i <= j) {
        middle = (i + j) / 2;
        cmp = strcmp(words[middle], word);

        if (cmp == 0) return 1;

        if (cmp < 0) {
            i = middle + 1;
        } else {
            j = middle - 1;
        }
    }

    return 0;
}

/* Print the 'words' array */
void print_words(char words[][WORD_SIZE], int nwords) {
    for (int i = 0; i < nwords; i++) {
        printf("%s ", words[i]);
    }
    puts("\n");
}

/* Quick search menu */
void search_menu(char words[][WORD_SIZE], int nwords) {
    char word[WORD_SIZE], option;

    while(1) {
        printf("\nMenu:\n\t1) Exit\n\t2) Search a word\noption: ");
        scanf("\n%c", &option);

        if (option == '1') break;
        if (option != '2') continue;


        printf("Word to search: ");
        scanf("%s", word);
        if(search_word(words, nwords, word)) {
            printf("The word '%s' exists into the dictionary\n", word);
        } else {
            printf("The word '%s' doest not exists into the dictionary\n", word);
        }
    }
}


int main(int argc, char const *argv[]) {
    if (argc < 2) {
        puts("Missing input file");
        return EXIT_FAILURE;
    }

    int nwords = 0;
    printf("Number of words to read: ");
    scanf("%d", &nwords);

    char words[nwords][WORD_SIZE];
    nwords = read_words(argv[1], words, nwords);
    puts("\nWords read:");
    print_words(words, nwords);

    puts("Ordered words:");
    merge_sort(words, nwords);
    print_words(words, nwords);

    char unq_words[nwords][WORD_SIZE];
    int nunq_words = copy_unique_words(words, unq_words, nwords);
    printf("Unique ordered words: %d\n", nunq_words);
    print_words(unq_words, nunq_words);

    search_menu(unq_words, nunq_words);

    return EXIT_SUCCESS;
}
