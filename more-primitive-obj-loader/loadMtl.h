//
//  loadMtl.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef loadMtl_h
#define loadMtl_h

#include <stdbool.h>
#include <stdio.h>

#include "Material.h"
#include "constants.h"
#include "utilities.h"

#define MATERIAL_NAME_TOKEN "newmtl"
#define DIFFUSE_MAP_TOKEN "map_Kd"
#define NORMAL_MAP_TOKEN "map_Bump"

bool loadMtl(const char *fileName, Material *m);

#endif /* loadMtl_h */
