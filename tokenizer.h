/*
 * tokenizer.h
 * Header for tokenization and word normalization
 * COMP1028 Cyberbullying Analyzer
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "file_io.h"

// Maximum word length
#define MAX_WORD_LEN 64

// Structure to hold tokenized words
typedef struct {
    char **words;     // dynamic array of words
    int wordCount;    // total number of words
} TokenList;

/**
 * Tokenizes all lines from a FileContent into words.
 * @param fc FileContent struct from file_io
 * @param stopwordsFile path to stopwords.txt
 * @return TokenList struct with words and count
 */
TokenList* tokenize(FileContent *fc, const char *stopwordsFile);

/**
 * Frees memory allocated for TokenList
 */
void freeTokenList(TokenList *tl);

#endif
