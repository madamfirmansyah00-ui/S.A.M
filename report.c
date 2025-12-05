/*
 * report.c
 * Implementation of persistent storage for analyzer results
 */

#include "report.h"
#include <stdio.h>

void saveReport(const char *filename,
                AnalysisResult analysis,
                ToxicityResult toxicity,
                WordFreq *table,
                int count) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error: Could not open %s for writing\n", filename);
        return;
    }

    fprintf(fp, "=== Cyberbullying Text Analyzer Report ===\n\n");

    // General analysis
    fprintf(fp, "Total words: %d\n", analysis.totalWords);
    fprintf(fp, "Unique words: %d\n", analysis.uniqueWords);
    fprintf(fp, "Lexical diversity: %.2f\n", analysis.lexicalDiversity);
    fprintf(fp, "Average word length: %.2f\n", analysis.avgWordLength);
    fprintf(fp, "Average sentence length: %.2f\n\n", analysis.avgSentenceLength);

    // Toxicity analysis
    fprintf(fp, "Total toxic words: %d\n", toxicity.totalToxic);
    fprintf(fp, "Toxic ratio: %.2f\n", toxicity.toxicRatio);
    if (toxicity.mildCount + toxicity.moderateCount + toxicity.severeCount > 0) {
        fprintf(fp, "Severity breakdown:\n");
        fprintf(fp, "  Mild: %d\n", toxicity.mildCount);
        fprintf(fp, "  Moderate: %d\n", toxicity.moderateCount);
        fprintf(fp, "  Severe: %d\n", toxicity.severeCount);
    }
    fprintf(fp, "\n");

    // Top words
    fprintf(fp, "--- Word Frequencies ---\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s : %d\n", table[i].word, table[i].count);
    }

    fclose(fp);
    printf("Report successfully saved to %s\n", filename);
}
