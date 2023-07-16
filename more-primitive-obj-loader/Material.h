//
//  Material.h
//  more-primitive-obj-loader
//
//  Created by Igor on 15/07/2023.
//

#ifndef Material_h
#define Material_h

#include <stdlib.h>
#include <string.h>

#include "Vec3.h"

typedef struct {
  char *name;
  char *diffuseMapPath;
  char *normalMapPath;
} Material;

void initMaterial(Material *m);
void freeMaterialName(Material *m);
void freeMaterialDiffuseMapPath(Material *m);
void freeMaterialNormalMapPath(Material *m);
void writeMaterialName(Material *m, const char *name);
void writeMaterialDiffuseMapPath(Material *m, const char *diffuseMapPath);
void writeMaterialNormalMapPath(Material *m, const char *normalMapPath);
void freeMaterial(Material *m);

#endif /* Material_h */
