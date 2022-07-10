#ifndef __MESH_H__
#define __MESH_H__

#include "face.h"
#include "face_array.h"
#include "tex2.h"
#include "tex2_array.h"
#include "vec3.h"
#include "vec3_array.h"

typedef struct {
    char *mtl_lib;
    char *name;

    vec3_array vertices;
    vec3_array normals;
    tex2_array uvs;

    face_array faces;
} mesh;

void init_mesh(mesh *m) {
    m->mtl_lib = NULL;
    m->name = NULL;
    init_vec3_array(&(m->vertices));
    init_vec3_array(&(m->normals));
    init_tex2_array(&(m->uvs));
    init_face_array(&(m->faces));
}

void free_mesh_mtl(mesh *m) {
    free(m->mtl_lib);
    m->mtl_lib = NULL;
}

void free_mesh_name(mesh *m) {
    free(m->name);
    m->name = NULL;
}

void write_mesh_mtl(mesh *m, const char *mtl_name) {
    if (m->mtl_lib != NULL) {
        free_mesh_mtl(m);
    }

    m->mtl_lib = malloc(sizeof(char) * strlen(mtl_name));
    strcpy(m->mtl_lib, mtl_name);
}

void write_mesh_name(mesh *m, const char *name) {
    if (m->name != NULL) {
        free_mesh_name(m);
    }

    m->name = malloc(sizeof(char) * strlen(name));
    strcpy(m->name, name);
}

void write_mesh_vertex(mesh *m, vec3 v) { write_vec3_array(&(m->vertices), v); }

void write_mesh_normal(mesh *m, vec3 n) { write_vec3_array(&(m->normals), n); }

void write_mesh_uv(mesh *m, tex2 t) { write_tex2_array(&(m->uvs), t); }

void write_mesh_face(mesh *m, face f) { write_face_array(&(m->faces), f); }

void free_mesh(mesh *m) {
    free_mesh_mtl(m);
    free_mesh_name(m);

    free_vec3_array(&(m->vertices));
    free_vec3_array(&(m->normals));
    free_tex2_array(&(m->uvs));

    free_face_array(&(m->faces));
}

#endif // __MESH_H__
