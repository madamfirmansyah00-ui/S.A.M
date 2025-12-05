/*
 * main.c
 * Entry point for Cyberbullying / Toxic Text Analyzer
 * COMP1028 Coursework Autumn 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_io.h"
#include "tokenizer.h"
#include "analysis.h"
#include "toxicity.h"
#include "sorting.h"
#include "report.h"
#include "ui.h"

#define MAX_FILENAME 256

int main(void) {
    char filename[MAX_FILENAME];
    int choice;
    int running = 1;

    // Global state
    FileContent *fc = NULL;
    TokenList *tl = NULL;
    AnalysisResult analysis = {0};
    ToxicityResult toxicity = {0};
    WordFreq *freqTable = NULL;
    int freqCount = 0;

    printBanner();

    while (running) {
        printMenu();
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (choice) {
            case 1: // Load text file
                printf("Enter filename to load: ");
                scanf("%s", filename);

                if (fc) freeFileContent(fc);
                if (tl) freeTokenList(tl);
                if (freqTable) {
                    for (int i = 0; i < freqCount; i++) free(freqTable[i].word);
                    free(freqTable);
                }

                fc = loadFile(filename);
                if (!fc) {
                    fprintf(stderr, "Error: Could not open %s\n", filename);
                } else {
                    tl = tokenize(fc, "stopwords.txt");
                    printf("File %s loaded and tokenized successfully.\n", filename);
                }
                break;

            case 2: // General word statistics
                if (tl) {
                    analysis = analyzeText(tl, fc);
                    displayAnalysis(analysis);
                } else {
                    printf("No file loaded. Please load a file first.\n");
                }
                break;

            case 3: // Toxic word analysis
                if (tl) {
                    toxicity = analyzeToxicity(tl, "toxicwords.txt");
                    displayToxicity(toxicity);
                } else {
                    printf("No file loaded. Please load a file first.\n");
                }
                break;

            case 4: { // Sorting and top N words
                if (tl) {
                    int n;
                    printf("Enter N (top words to display): ");
                    scanf("%d", &n);

                    if (freqTable) {
                        for (int i = 0; i < freqCount; i++) free(freqTable[i].word);
                        free(freqTable);
                    }

                    freqTable = buildFrequencyTable(tl, &freqCount);
                    sortByFrequency(freqTable, freqCount);
                    displayTopWords(freqTable, freqCount, n);

                    // Optional ASCII chart
                    // int counts[n]; char *words[n];
                    // fill arrays from freqTable[0..n-1] then call displayBarChart(words, counts, n);
                } else {
                    printf("No file loaded. Please load a file first.\n");
                }
                break;
            }

            case 5: // Save results
                if (tl && freqTable) {
                    saveReport("output/analysis_report.txt", analysis, toxicity, freqTable, freqCount);
                } else {
                    printf("No analysis results to save. Please load and analyze a file first.\n");
                }
                break;

            case 6: // Exit
                printf("Exiting program. Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    // Cleanup
    if (fc) freeFileContent(fc);
    if (tl) freeTokenList(tl);
    if (freqTable) {
        for (int i = 0; i < freqCount; i++) free(freqTable[i].word);
        free(freqTable);
    }

    return 0;
}
