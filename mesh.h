#ifndef __MESH_H__
#define __MESH_H__

#include "tex2.h"
#include "tex2_array.h"
#include "vec3.h"
#include "vec3_array.h"

typedef struct {
    vec3_array vertices;
    vec3_array normals;
    tex2_array uvs;
} mesh;

void init_mesh(mesh *m) {
    init_vec3_array(&(m->vertices));
    init_vec3_array(&(m->normals));
    init_tex2_array(&(m->uvs));
}

void write_vertex(mesh *m, vec3 v) { write_vec3_array(&(m->vertices), v); }

void write_normal(mesh *m, vec3 n) { write_vec3_array(&(m->normals), n); }

void write_uv(mesh *m, tex2 t) { write_tex2_array(&(m->uvs), t); }

void free_mesh(mesh *m) {
    free_vec3_array(&(m->vertices));
    free_vec3_array(&(m->normals));
    free_tex2_array(&(m->uvs));
}

#endif // __MESH_H__
