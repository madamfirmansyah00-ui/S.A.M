/*
 * file_io.c
 * Implementation of file input/output functions
 */

#include "file_io.h"
#include <stdlib.h>
#include <string.h>

FileContent* loadFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }

    FileContent *fc = malloc(sizeof(FileContent));
    if (!fc) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    fc->lines = NULL;
    fc->lineCount = 0;

    char buffer[MAX_LINE_LEN];
    while (fgets(buffer, MAX_LINE_LEN, fp)) {
        // Remove newline
        buffer[strcspn(buffer, "\r\n")] = '\0';

        // Allocate space for new line
        char *line = malloc(strlen(buffer) + 1);
        if (!line) {
            fprintf(stderr, "Error: Memory allocation failed for line\n");
            freeFileContent(fc);
            fclose(fp);
            return NULL;
        }
        strcpy(line, buffer);

        // Expand array
        char **tmp = realloc(fc->lines, (fc->lineCount + 1) * sizeof(char*));
        if (!tmp) {
            fprintf(stderr, "Error: Memory allocation failed for lines array\n");
            free(line);
            freeFileContent(fc);
            fclose(fp);
            return NULL;
        }
        fc->lines = tmp;
        fc->lines[fc->lineCount] = line;
        fc->lineCount++;
    }

    fclose(fp);
    return fc;
}

void freeFileContent(FileContent *fc) {
    if (!fc) return;
    for (int i = 0; i < fc->lineCount; i++) {
        free(fc->lines[i]);
    }
    free(fc->lines);
    free(fc);
}
