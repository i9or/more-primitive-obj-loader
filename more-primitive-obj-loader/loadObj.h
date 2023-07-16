//
//  loadObj.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef loadObj_h
#define loadObj_h

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "Mesh.h"
#include "constants.h"
#include "utilities.h"

#define MATERIAL_LIBRARY_NAME_TOKEN "mtllib"
#define OBJECT_NAME_TOKEN "o"
#define VERTEX_COORDINATES_TOKEN "v"
#define VERTEX_NORMAL_COORDINATES_TOKEN "vn"
#define VERTEX_TEXTURE_COORDINATES_TOKEN "vt"
#define FACE_INDICES_TOKEN "f"

bool loadObj(const char *fileName, Mesh *m);

#endif /* loadObj_h */
