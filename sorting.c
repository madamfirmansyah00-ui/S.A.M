/*
 * sorting.c
 * Implementation of sorting and ranking functions
 */

#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Build frequency table
WordFreq* buildFrequencyTable(TokenList *tl, int *outCount) {
    if (!tl) {
        *outCount = 0;
        return NULL;
    }

    WordFreq *table = NULL;
    int count = 0;

    for (int i = 0; i < tl->wordCount; i++) {
        char *word = tl->words[i];
        int found = 0;

        for (int j = 0; j < count; j++) {
            if (strcmp(table[j].word, word) == 0) {
                table[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            WordFreq *tmp = realloc(table, (count + 1) * sizeof(WordFreq));
            if (!tmp) {
                fprintf(stderr, "Error: Memory allocation failed in frequency table\n");
                free(table);
                *outCount = 0;
                return NULL;
            }
            table = tmp;
            table[count].word = strdup(word);
            table[count].count = 1;
            count++;
        }
    }

    *outCount = count;
    return table;
}

// Alphabetical sort (Bubble Sort for simplicity)
void sortAlphabetical(WordFreq *table, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(table[j].word, table[j+1].word) > 0) {
                WordFreq tmp = table[j];
                table[j] = table[j+1];
                table[j+1] = tmp;
            }
        }
    }
}

// Frequency sort (descending, Bubble Sort)
void sortByFrequency(WordFreq *table, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (table[j].count < table[j+1].count) {
                WordFreq tmp = table[j];
                table[j] = table[j+1];
                table[j+1] = tmp;
            }
        }
    }
}

// Display top N words
void displayTopWords(WordFreq *table, int count, int N) {
    printf("\n--- Top %d Words ---\n", N);
    for (int i = 0; i < N && i < count; i++) {
        printf("%s : %d\n", table[i].word, table[i].count);
    }
    printf("-------------------\n\n");
}
