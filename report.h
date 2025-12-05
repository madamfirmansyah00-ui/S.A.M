/*
 * report.h
 * Header for saving analysis and toxicity results
 * COMP1028 Cyberbullying Analyzer
 */

#ifndef REPORT_H
#define REPORT_H

#include "analysis.h"
#include "toxicity.h"
#include "sorting.h"

/**
 * Save analysis and toxicity results into a text file.
 * @param filename Output file name
 * @param analysis AnalysisResult struct
 * @param toxicity ToxicityResult struct
 * @param table Word frequency table
 * @param count Number of entries in frequency table
 */
void saveReport(const char *filename,
                AnalysisResult analysis,
                ToxicityResult toxicity,
                WordFreq *table,
                int count);

#endif
