/*
 * sorting.h
 * Header for sorting and ranking functions
 * COMP1028 Cyberbullying Analyzer
 */

#ifndef SORTING_H
#define SORTING_H

#include "tokenizer.h"

// Structure to hold word + frequency
typedef struct {
    char *word;
    int count;
} WordFreq;

/**
 * Build frequency table from TokenList.
 * @param tl TokenList of words
 * @return dynamically allocated array of WordFreq, with size stored in outCount
 */
WordFreq* buildFrequencyTable(TokenList *tl, int *outCount);

/**
 * Sort frequency table alphabetically.
 */
void sortAlphabetical(WordFreq *table, int count);

/**
 * Sort frequency table by frequency (descending).
 */
void sortByFrequency(WordFreq *table, int count);

/**
 * Display top N words from frequency table.
 */
void displayTopWords(WordFreq *table, int count, int N);

#endif
