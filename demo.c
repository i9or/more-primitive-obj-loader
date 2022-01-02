#include <stdio.h>
#include <string.h>

#include "vec3.h"
#include "vec3_array.h"

int main() {
    vec3 v1 = {1.23f, 4.56f, 7.89f};
    vec3 v2 = {2.34f, 5.67f, 8.90f};

    vec3_array vertices;
    init_vec3_array(&vertices);
    write_vec3_array(&vertices, v1);
    write_vec3_array(&vertices, v2);

    printf("v1: (%f %f %f)\n", vertices.data[0].x, vertices.data[0].y,
           vertices.data[0].z);
    printf("v2: (%f %f %f)\n", vertices.data[1].x, vertices.data[1].y,
           vertices.data[1].z);

    free_vec3_array(&vertices);
    return 0;
}
