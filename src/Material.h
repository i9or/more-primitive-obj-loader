#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdlib.h>
#include <string.h>

#include "Vec3.h"

typedef struct {
	char *name;
	char *diffuseMapPath;
	char *normalMapPath;
} Material;

void initMaterial(Material *m) {
	m->name = NULL;
	m->diffuseMapPath = NULL;
	m->normalMapPath = NULL;
}

void freeMaterialName(Material *m) {
	free(m->name);
	m->name = NULL;
}

void freeMaterialDiffuseMapPath(Material *m) {
	free(m->diffuseMapPath);
	m->diffuseMapPath = NULL;
}

void freeMaterialNormalMapPath(Material *m) {
	free(m->normalMapPath);
	m->normalMapPath = NULL;
}

void writeMaterialName(Material *m, const char *name) {
	if (m->name != NULL) {
		freeMaterialName(m);
	}

	m->name = malloc(sizeof(char) * strlen(name));
	strcpy(m->name, name);
}

void writeMaterialDiffuseMapPath(Material *m, const char *diffuseMapPath) {
	if (m->diffuseMapPath != NULL) {
		freeMaterialDiffuseMapPath(m);
	}

	m->diffuseMapPath = malloc(sizeof(char) * strlen(diffuseMapPath));
	strcpy(m->diffuseMapPath, diffuseMapPath);
}

void writeMaterialNormalMapPath(Material *m, const char *normalMapPath) {
	if (m->normalMapPath != NULL) {
		freeMaterialNormalMapPath(m);
	}

	m->normalMapPath = malloc(sizeof(char) * strlen(normalMapPath));
	strcpy(m->normalMapPath, normalMapPath);
}

void freeMaterial(Material *m) {
	freeMaterialName(m);
	freeMaterialDiffuseMapPath(m);
	freeMaterialNormalMapPath(m);
}

#endif // MATERIAL_H
