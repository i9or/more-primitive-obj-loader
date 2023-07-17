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
#include "Tex2.h"
#include "Vec3.h"
#include "constants.h"
#include "loadMtl.h"
#include "loadObj.h"
#include "loadTga.h"

Mesh gMesh;
Material gMaterial;
TgaImage gDiffuseMap;
GLuint gDiffuseMapHandle;
TgaImage gNormalMap;
GLuint gNormalMapHandle;

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

  glGenTextures(1, &gDiffuseMapHandle);
  glBindTexture(GL_TEXTURE_2D, gDiffuseMapHandle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               gDiffuseMap.header.width, gDiffuseMap.header.height,
               0, GL_RGBA, GL_UNSIGNED_BYTE,
               gDiffuseMap.imageData);

  return true;
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3f(0.7f, 0.7f, 0.7f);

  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, gDiffuseMapHandle);

  glBegin(GL_TRIANGLES);

  for (size_t i = 0; i < gMesh.faces.count; ++i) {
    Face f = gMesh.faces.data[i];

    Vec3 n1 = gMesh.normals.data[f.n1];
    Vec3 n2 = gMesh.normals.data[f.n2];
    Vec3 n3 = gMesh.normals.data[f.n3];

    Tex2 uv1 = gMesh.uvs.data[f.uv1];
    Tex2 uv2 = gMesh.uvs.data[f.uv2];
    Tex2 uv3 = gMesh.uvs.data[f.uv3];

    Vec3 v1 = gMesh.vertices.data[f.v1];
    Vec3 v2 = gMesh.vertices.data[f.v2];
    Vec3 v3 = gMesh.vertices.data[f.v3];

    glNormal3f(n1.x, n1.y, n1.z);
    glTexCoord2f(uv1.u, uv1.v);
    glVertex3f(v1.x, v1.y, v1.z);

    glNormal3f(n2.x, n2.y, n2.z);
    glTexCoord2f(uv2.u, uv2.v);
    glVertex3f(v2.x, v2.y, v2.z);

    glNormal3f(n3.x, n3.y, n3.z);
    glTexCoord2f(uv3.u, uv3.v);
    glVertex3f(v3.x, v3.y, v3.z);
  }

  glEnd();

  glutSwapBuffers();

  glDisable(GL_TEXTURE_2D);
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
  gluLookAt(-2.5, 2.5, -2.5,
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);
}

void keyDown(unsigned char key, int x, int y) {
  if (key == 27) {
    exit(EXIT_SUCCESS);
  }
}
