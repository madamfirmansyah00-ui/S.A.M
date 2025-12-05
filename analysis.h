/*
 * analysis.h
 * Header for text analysis functions
 * COMP1028 Cyberbullying Analyzer
 */

#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "tokenizer.h"

// Structure to hold analysis results
typedef struct {
    int totalWords;          // total number of words
    int uniqueWords;         // number of unique words
    double lexicalDiversity; // unique/total ratio
    double avgWordLength;    // average length of words
    double avgSentenceLength;// average words per sentence (approx.)
} AnalysisResult;

/**
 * Perform analysis on a TokenList.
 * @param tl TokenList of words
 * @param fc FileContent (for sentence-level stats)
 * @return AnalysisResult struct with computed metrics
 */
AnalysisResult analyzeText(TokenList *tl, FileContent *fc);

/**
 * Display analysis results to console.
 */
void displayAnalysis(AnalysisResult result);

#endif
