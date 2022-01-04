#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "mesh.h"

#define MAX_LINE_WIDTH 1024
#define SPACE_DELIMITER " "
#define STRIP_NEWLINE(str) (str)[strcspn((str), "\r\n")] = '\0'

bool load_obj(const char *file_name, mesh *m) {
    init_mesh(m);

    FILE *fp = fopen(file_name, "r");
    if (!fp) {
        printf("Error loading file: %s\n", file_name);
        return false;
    }

    char line[MAX_LINE_WIDTH];
    int line_counter = 0;
    while (fgets(line, MAX_LINE_WIDTH, fp) != NULL) {
        char *token;

        token = strtok(line, SPACE_DELIMITER);

        if (strcmp(token, "mtllib") == 0) {
            token = strtok(NULL, SPACE_DELIMITER);
            STRIP_NEWLINE(token);
            write_mesh_mtl(m, token);
        } else if (strcmp(token, "o") == 0) {
            token = strtok(NULL, SPACE_DELIMITER);
            STRIP_NEWLINE(token);
            write_mesh_name(m, token);
        } else if (strcmp(token, "v") == 0) {
            char *x_str, *y_str, *z_str;

            x_str = strtok(NULL, SPACE_DELIMITER);
            y_str = strtok(NULL, SPACE_DELIMITER);
            z_str = strtok(NULL, SPACE_DELIMITER);

            vec3 v = {atof(x_str), atof(y_str), atof(z_str)};
            write_mesh_vertex(m, v);
        } else if (strcmp(token, "vn") == 0) {
            char *x_str, *y_str, *z_str;

            x_str = strtok(NULL, SPACE_DELIMITER);
            y_str = strtok(NULL, SPACE_DELIMITER);
            z_str = strtok(NULL, SPACE_DELIMITER);

            vec3 n = {atof(x_str), atof(y_str), atof(z_str)};
            write_mesh_normal(m, n);
        } else {
            puts("This token is not yet supported");
        }

        line_counter++;
    }

    if (!feof(fp)) {
        perror("Error loading a file");
    } else {
        puts("OBJ file loaded successfully");
        printf("Total number of lines are read: %d\n", line_counter);
    }

    fclose(fp);
    return true;
}

#endif // __OBJ_LOADER_H__
