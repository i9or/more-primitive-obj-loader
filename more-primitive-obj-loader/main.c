//
//  main.c
//  more-primitive-obj-loader
//
//  Created by Igor on 15/07/2023.
//

#include <stdio.h>
#include <stdlib.h>

#include "Material.h"
#include "Mesh.h"
#include "constants.h"
#include "loadMtl.h"
#include "loadObj.h"
#include "loadTga.h"

int main(int argc, char *argv[]) {
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

  TgaImage diffuseMap;
  TgaImage normalMap;
  char diffuseMapPath[MAX_FILE_PATH_LENGTH];
  char normalMapPath[MAX_FILE_PATH_LENGTH];
  sprintf(diffuseMapPath, "%s%s", "../assets/", material.diffuseMapPath);
  sprintf(normalMapPath, "%s%s", "../assets/", material.normalMapPath);

  if (!loadTga(diffuseMapPath, &diffuseMap)) {
    return EXIT_FAILURE;
  }

  if (!loadTga(normalMapPath, &normalMap)) {
    return EXIT_FAILURE;
  }

  // Clean up
  freeTgaImage(&diffuseMap);
  freeTgaImage(&normalMap);
  freeMaterial(&material);
  freeMesh(&mesh);

  return EXIT_SUCCESS;
}
