#include <stdio.h>
#include <stdlib.h>

#include "src/Material.h"
#include "src/Mesh.h"
#include "src/constants.h"
#include "src/loadMtl.h"
#include "src/loadObj.h"

int main() {
	Mesh mesh;
	if (!loadObj("../assets/brick_cube.obj", &mesh)) {
		return EXIT_FAILURE;
	}

	printf("Material library: %s\n", mesh.mtlLib);
	printf("Name of the object: %s\n", mesh.name);
	printf("Number of vertices: %d\n", mesh.vertices.count);
	printf("Number of normals: %d\n", mesh.normals.count);
	printf("Number of texture coordinates: %d\n", mesh.uvs.count);
	printf("Number of faces: %d\n", mesh.faces.count);

	Material material;
	char mtlPath[MAX_FILE_PATH_LENGTH];
	sprintf(mtlPath, "%s%s", "../assets/", mesh.mtlLib);
	if (!loadMtl(mtlPath, &material)) {
		return EXIT_FAILURE;
	}

	printf("Material name: %s\n", material.name);
	printf("Material diffuse map: %s\n", material.diffuseMapPath);
	printf("Material normal map: %s\n", material.normalMapPath);

	// Clean up
	freeMaterial(&material);
	freeMesh(&mesh);
	return EXIT_SUCCESS;
}
