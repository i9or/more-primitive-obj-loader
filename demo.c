#include <stdio.h>
#include <string.h>

#include "obj_loader.h"
#include "tex2.h"
#include "tex2_array.h"
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

    mesh bunny;
    tex2 t1 = {1.0f, 0.5f};
    tex2 t2 = {-0.1f, 0.3f};

    init_mesh(&bunny);
    write_vertex(&bunny, v1);
    write_normal(&bunny, v2);
    write_uv(&bunny, t1);
    write_uv(&bunny, t2);

    printf("v1: (%f %f %f)\n", bunny.vertices.data[0].x,
           bunny.vertices.data[0].y, bunny.vertices.data[0].z);
    printf("n1: (%f %f %f)\n", bunny.normals.data[0].x, bunny.normals.data[0].y,
           bunny.normals.data[0].z);
    printf("uv1: (%f %f)\n", bunny.uvs.data[0].u, bunny.uvs.data[0].v);
    printf("uv1: (%f %f)\n", bunny.uvs.data[1].u, bunny.uvs.data[1].v);

    free_vec3_array(&vertices);
    free_mesh(&bunny);
    return 0;
}
