#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "mesh.h"

#define MAX_LINE_WIDTH 1024
#define SPACE_DELIMITER " "

bool load_obj(const char *file_name, mesh *m) {
    init_mesh(m);

    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        printf("Error loading file: %s\n", file_name);
        return false;
    }

    char line[MAX_LINE_WIDTH];
    unsigned int line_counter;
    while (fgets(line, MAX_LINE_WIDTH, fp) != NULL) {
        // printf("Read a line: %s", line);
        char *token;

        token = strtok(line, SPACE_DELIMITER);

        if (strcmp(token, "#") == 0) {
            puts("Skipping comment line");
        } else if (strcmp(token, "v") == 0) {
            puts("Found a vertex");
        } else {
            puts("This token is not yet supported");
        }

        line_counter++;
    }

    if (feof(fp)) {
        puts("Reached the end of the file");
        printf("Total number of lines are read: %d\n", line_counter);
    } else {
        perror("Error reading a line");
    }

    fclose(fp);
    return true;
}

#endif // __OBJ_LOADER_H__
