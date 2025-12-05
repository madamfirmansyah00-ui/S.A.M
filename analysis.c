/*
 * analysis.c
 * Implementation of text analysis functions
 */

#include "analysis.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Helper: count unique words
static int countUnique(TokenList *tl) {
    int unique = 0;
    for (int i = 0; i < tl->wordCount; i++) {
        int seen = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(tl->words[i], tl->words[j]) == 0) {
                seen = 1;
                break;
            }
        }
        if (!seen) unique++;
    }
    return unique;
}

AnalysisResult analyzeText(TokenList *tl, FileContent *fc) {
    AnalysisResult result = {0};

    if (!tl) return result;

    result.totalWords = tl->wordCount;
    result.uniqueWords = countUnique(tl);

    if (result.totalWords > 0) {
        result.lexicalDiversity = (double)result.uniqueWords / result.totalWords;
    }

    // Average word length
    int totalChars = 0;
    for (int i = 0; i < tl->wordCount; i++) {
        totalChars += strlen(tl->words[i]);
    }
    if (tl->wordCount > 0) {
        result.avgWordLength = (double)totalChars / tl->wordCount;
    }

    // Approximate average sentence length (words per line)
    if (fc && fc->lineCount > 0) {
        result.avgSentenceLength = (double)tl->wordCount / fc->lineCount;
    }

    return result;
}

void displayAnalysis(AnalysisResult result) {
    printf("\n--- General Text Analysis ---\n");
    printf("Total words: %d\n", result.totalWords);
    printf("Unique words: %d\n", result.uniqueWords);
    printf("Lexical diversity: %.2f\n", result.lexicalDiversity);
    printf("Average word length: %.2f\n", result.avgWordLength);
    printf("Average sentence length (words per line): %.2f\n", result.avgSentenceLength);
    printf("-----------------------------\n\n");
}
