/*
 * ui.c
 * Implementation of user interface functions
 */

#include "ui.h"
#include <stdio.h>

void printBanner() {
    printf("=========================================\n");
    printf("   Cyberbullying / Toxic Text Analyzer   \n");
    printf("   COMP1028 Coursework Autumn 2025       \n");
    printf("=========================================\n\n");
}

void printMenu() {
    printf("Menu Options:\n");
    printf("1. Load text file for analysis\n");
    printf("2. Display general word statistics\n");
    printf("3. Display toxic word analysis\n");
    printf("4. Sort and display top N words\n");
    printf("5. Save results to output file\n");
    printf("6. Exit program\n");
    printf("-----------------------------------------\n");
}

void displayBarChart(char **words, int *counts, int n) {
    printf("\n--- ASCII Bar Chart (Top %d Words) ---\n", n);
    for (int i = 0; i < n; i++) {
        printf("%-15s | ", words[i]);
        for (int j = 0; j < counts[i]; j++) {
            printf("*");
        }
        printf(" (%d)\n", counts[i]);
    }
    printf("--------------------------------------\n\n");
}
