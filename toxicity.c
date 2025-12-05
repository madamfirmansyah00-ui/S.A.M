/*
 * toxicity.c
 * Implementation of toxic word detection
 */

#include "toxicity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper: load toxic words (with optional severity tags)
static char** loadToxicWords(const char *filename, int *count) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Warning: Could not open toxic words file %s\n", filename);
        *count = 0;
        return NULL;
    }

    char buffer[128];
    char **toxicWords = NULL;
    *count = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (strlen(buffer) == 0) continue;

        char *word = malloc(strlen(buffer) + 1);
        strcpy(word, buffer);

        char **tmp = realloc(toxicWords, (*count + 1) * sizeof(char*));
        toxicWords = tmp;
        toxicWords[*count] = word;
        (*count)++;
    }

    fclose(fp);
    return toxicWords;
}

ToxicityResult analyzeToxicity(TokenList *tl, const char *toxicFile) {
    ToxicityResult result = {0};
    if (!tl) return result;

    int toxicCount = 0;
    char **toxicWords = NULL;
    int dictSize = 0;

    toxicWords = loadToxicWords(toxicFile, &dictSize);

    for (int i = 0; i < tl->wordCount; i++) {
        for (int j = 0; j < dictSize; j++) {
            if (strcmp(tl->words[i], toxicWords[j]) == 0) {
                toxicCount++;
                // Optional: severity categorization
                if (strstr(toxicWords[j], "(mild)")) result.mildCount++;
                else if (strstr(toxicWords[j], "(moderate)")) result.moderateCount++;
                else if (strstr(toxicWords[j], "(severe)")) result.severeCount++;
            }
        }
    }

    result.totalToxic = toxicCount;
    if (tl->wordCount > 0) {
        result.toxicRatio = (double)toxicCount / tl->wordCount;
    }

    // Free dictionary
    for (int i = 0; i < dictSize; i++) free(toxicWords[i]);
    free(toxicWords);

    return result;
}

void displayToxicity(ToxicityResult result) {
    printf("\n--- Toxic Word Analysis ---\n");
    printf("Total toxic words: %d\n", result.totalToxic);
    printf("Toxic ratio: %.2f\n", result.toxicRatio);
    if (result.mildCount + result.moderateCount + result.severeCount > 0) {
        printf("Severity breakdown:\n");
        printf("  Mild: %d\n", result.mildCount);
        printf("  Moderate: %d\n", result.moderateCount);
        printf("  Severe: %d\n", result.severeCount);
    }
    printf("---------------------------\n\n");
}
