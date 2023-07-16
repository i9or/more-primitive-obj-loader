//
//  main.c
//  more-primitive-obj-loader
//
//  Created by Igor on 15/07/2023.
//

#include <GLUT/GLUT.h>
#include <stdio.h>
#include <stdlib.h>

#include "Material.h"
#include "Mesh.h"
#include "constants.h"
#include "loadMtl.h"
#include "loadObj.h"
#include "loadTga.h"

Mesh gMesh;
Material gMaterial;
TgaImage gDiffuseMap;
TgaImage gNormalMap;

void cleanUp(void);
bool loadAssets(void);
bool init(void);
void display(void);
void reshape(int w, int h);
void idle(void);
void keyDown(unsigned char key, int x, int y);

int main(int argc, char *argv[]) {
  if (atexit(cleanUp) != 0) {
    perror("Exit function registration failed...");
    return EXIT_FAILURE;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("More Primitive OBJ Loader");

  if (!init()) {
    exit(EXIT_FAILURE);
  }

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyDown);
  glutMainLoop();

  return EXIT_FAILURE; // Something terribly wrong happened if we ended up here
}

void cleanUp(void) {
  freeTgaImage(&gDiffuseMap);
  freeTgaImage(&gNormalMap);
  freeMaterial(&gMaterial);
  freeMesh(&gMesh);
}

bool loadAssets(void) {
  if (!loadObj("../assets/brick_cube.obj", &gMesh)) {
    return false;
  }

  printf("Material library: %s\n", gMesh.mtlLib);
  printf("Name of the object: %s\n", gMesh.name);
  printf("Number of vertices: %d\n", gMesh.vertices.count);
  printf("Number of normals: %d\n", gMesh.normals.count);
  printf("Number of texture coordinates: %d\n", gMesh.uvs.count);
  printf("Number of faces: %d\n", gMesh.faces.count);

  char mtlPath[MAX_FILE_PATH_LENGTH];
  sprintf(mtlPath, "%s%s", "../assets/", gMesh.mtlLib);
  if (!loadMtl(mtlPath, &gMaterial)) {
    return false;
  }

  printf("Material name: %s\n", gMaterial.name);
  printf("Material diffuse map: %s\n", gMaterial.diffuseMapPath);
  printf("Material normal map: %s\n", gMaterial.normalMapPath);

  char diffuseMapPath[MAX_FILE_PATH_LENGTH];
  char normalMapPath[MAX_FILE_PATH_LENGTH];
  sprintf(diffuseMapPath, "%s%s", "../assets/", gMaterial.diffuseMapPath);
  sprintf(normalMapPath, "%s%s", "../assets/", gMaterial.normalMapPath);

  if (!loadTga(diffuseMapPath, &gDiffuseMap)) {
    return false;
  }

  printTgaHeader(gDiffuseMap.header);

  if (!loadTga(normalMapPath, &gNormalMap)) {
    return false;
  }

  printTgaHeader(gNormalMap.header);

  return true;
}

bool init(void) {
  if (!loadAssets()) {
    return false;
  }

  glClearColor(0.f, 0.f, 0.f, 0.f);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  return true;
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw here

  glutSwapBuffers();
}

void idle(void) {
  glutPostRedisplay();
}

void reshape(int w, int h) {
  double width = (double)w;
  double height = h == 0 ? 1.0 : (double)h;

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, width / height, 0.1, 1000.0);
  gluLookAt(-25.0, 25.0, -25.0,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
}

void keyDown(unsigned char key, int x, int y) {
  if (key == 27) {
    exit(EXIT_SUCCESS);
  }
}
