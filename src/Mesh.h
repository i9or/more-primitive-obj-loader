#ifndef MESH_H
#define MESH_H

#include <string.h>

#include "Face.h"
#include "FaceArray.h"
#include "Tex2.h"
#include "Tex2Array.h"
#include "Vec3.h"
#include "Vec3Array.h"

typedef struct {
	char *mtlLib;
	char *name;

	Vec3Array vertices;
	Vec3Array normals;
	Tex2Array uvs;

	FaceArray faces;
} Mesh;

void initMesh(Mesh *m) {
	m->mtlLib = NULL;
	m->name = NULL;
	initVec3Array(&(m->vertices));
	initVec3Array(&(m->normals));
	initTex2Array(&(m->uvs));
	initFaceArray(&(m->faces));
}

void freeMeshMtl(Mesh *m) {
	free(m->mtlLib);
	m->mtlLib = NULL;
}

void freeMeshName(Mesh *m) {
	free(m->name);
	m->name = NULL;
}

void writeMeshMtl(Mesh *m, const char *mtlName) {
	if (m->mtlLib != NULL) {
		freeMeshMtl(m);
	}

	m->mtlLib = malloc(sizeof(char) * strlen(mtlName));
	strcpy(m->mtlLib, mtlName);
}

void writeMeshName(Mesh *m, const char *name) {
	if (m->name != NULL) {
		freeMeshName(m);
	}

	m->name = malloc(sizeof(char) * strlen(name));
	strcpy(m->name, name);
}

void writeMeshVertex(Mesh *m, Vec3 v) { writeVec3Array(&(m->vertices), v); }

void writeMeshNormal(Mesh *m, Vec3 n) { writeVec3Array(&(m->normals), n); }

void writeMeshUv(Mesh *m, Tex2 t) { writeTex2Array(&(m->uvs), t); }

void writeMeshFace(Mesh *m, Face f) { writeFaceArray(&(m->faces), f); }

void freeMesh(Mesh *m) {
	freeMeshMtl(m);
	freeMeshName(m);

	freeVec3Array(&(m->vertices));
	freeVec3Array(&(m->normals));
	freeTex2Array(&(m->uvs));

	freeFaceArray(&(m->faces));
}

#endif // MESH_H
