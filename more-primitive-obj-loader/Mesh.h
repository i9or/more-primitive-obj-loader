//
//  Mesh.h
//  more-primitive-obj-loader
//
//  Created by Igor on 15/07/2023.
//

#ifndef Mesh_h
#define Mesh_h

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

void initMesh(Mesh *m);
void freeMeshMtl(Mesh *m);
void freeMeshName(Mesh *m);
void writeMeshMtl(Mesh *m, const char *mtlName);
void writeMeshName(Mesh *m, const char *name);
void writeMeshVertex(Mesh *m, Vec3 v);
void writeMeshNormal(Mesh *m, Vec3 n);
void writeMeshUv(Mesh *m, Tex2 t);
void writeMeshFace(Mesh *m, Face f);
void freeMesh(Mesh *m);

#endif /* Mesh_h */
