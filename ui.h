/*
 * ui.h
 * Header for user interface functions
 * COMP1028 Cyberbullying Analyzer
 */

#ifndef UI_H
#define UI_H

/**
 * Print welcome banner.
 */
void printBanner();

/**
 * Print main menu options.
 */
void printMenu();

/**
 * Display an ASCII bar chart for top words.
 * @param words array of word strings
 * @param counts array of frequencies
 * @param n number of entries
 */
void displayBarChart(char **words, int *counts, int n);

#endif
