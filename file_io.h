/*
 * file_io.h
 * Header for file input/output functions
 * COMP1028 Cyberbullying Analyzer
 */

#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>

// Maximum line length for reading
#define MAX_LINE_LEN 1024

// Structure to hold file content (array of lines)
typedef struct {
    char **lines;     // dynamic array of strings
    int lineCount;    // number of lines read
} FileContent;

/**
 * Loads a text file into memory line by line.
 * @param filename Name of the file to load
 * @return FileContent struct with lines and count, or NULL on failure
 */
FileContent* loadFile(const char *filename);

/**
 * Frees memory allocated for FileContent
 */
void freeFileContent(FileContent *fc);

#endif
