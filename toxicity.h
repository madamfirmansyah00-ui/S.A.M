/*
 * toxicity.h
 * Header for toxic word detection
 * COMP1028 Cyberbullying Analyzer
 */

#ifndef TOXICITY_H
#define TOXICITY_H

#include "tokenizer.h"

// Structure to hold toxic word statistics
typedef struct {
    int totalToxic;       // total toxic words detected
    double toxicRatio;    // toxic words / total words
    int mildCount;        // optional severity categories
    int moderateCount;
    int severeCount;
} ToxicityResult;

/**
 * Analyze tokens for toxic words.
 * @param tl TokenList of words
 * @param toxicFile path to toxicwords.txt
 * @return ToxicityResult struct with counts and ratio
 */
ToxicityResult analyzeToxicity(TokenList *tl, const char *toxicFile);

/**
 * Display toxicity results to console.
 */
void displayToxicity(ToxicityResult result);

#endif
