/*
 * tokenizer.c
 * Implementation of tokenization and normalization
 */

#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper: check if word is a stopword
static int isStopword(const char *word, char **stopwords, int stopCount) {
    for (int i = 0; i < stopCount; i++) {
        if (strcmp(word, stopwords[i]) == 0) return 1;
    }
    return 0;
}

// Load stopwords from file
static char** loadStopwords(const char *filename, int *count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Warning: Could not open stopwords file %s\n", filename);
        *count = 0;
        return NULL;
    }

    char buffer[MAX_WORD_LEN];
    char **stopwords = NULL;
    *count = 0;

    while (fgets(buffer, MAX_WORD_LEN, fp)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        char *word = malloc(strlen(buffer) + 1);
        strcpy(word, buffer);

        char **tmp = realloc(stopwords, (*count + 1) * sizeof(char*));
        stopwords = tmp;
        stopwords[*count] = word;
        (*count)++;
    }

    fclose(fp);
    return stopwords;
}

// Normalize word: lowercase, strip punctuation
static void normalize(char *word) {
    int j = 0;
    for (int i = 0; word[i]; i++) {
        if (isalpha((unsigned char)word[i])) {
            word[j++] = tolower((unsigned char)word[i]);
        }
    }
    word[j] = '\0';
}

TokenList* tokenize(FileContent *fc, const char *stopwordsFile) {
    if (!fc) return NULL;

    int stopCount = 0;
    char **stopwords = loadStopwords(stopwordsFile, &stopCount);

    TokenList *tl = malloc(sizeof(TokenList));
    tl->words = NULL;
    tl->wordCount = 0;

    for (int i = 0; i < fc->lineCount; i++) {
        char *line = fc->lines[i];
        char *token = strtok(line, " \t");

        while (token) {
            char buffer[MAX_WORD_LEN];
            strncpy(buffer, token, MAX_WORD_LEN - 1);
            buffer[MAX_WORD_LEN - 1] = '\0';

            normalize(buffer);

            if (strlen(buffer) > 0 && !isStopword(buffer, stopwords, stopCount)) {
                char *word = malloc(strlen(buffer) + 1);
                strcpy(word, buffer);

                char **tmp = realloc(tl->words, (tl->wordCount + 1) * sizeof(char*));
                tl->words = tmp;
                tl->words[tl->wordCount] = word;
                tl->wordCount++;
            }
            token = strtok(NULL, " \t");
        }
    }

    // Free stopwords
    for (int i = 0; i < stopCount; i++) free(stopwords[i]);
    free(stopwords);

    return tl;
}

void freeTokenList(TokenList *tl) {
    if (!tl) return;
    for (int i = 0; i < tl->wordCount; i++) {
        free(tl->words[i]);
    }
    free(tl->words);
    free(tl);
}
