//
//  Vec3Array.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef Vec3Array_h
#define Vec3Array_h

#include "DynamicArray.h"
#include "Vec3.h"

typedef struct {
  unsigned int count;
  unsigned int capacity;
  Vec3 *data;
} Vec3Array;

void initVec3Array(Vec3Array *arr);
void writeVec3Array(Vec3Array *arr, Vec3 v);
void freeVec3Array(Vec3Array *arr);

#endif /* Vec3Array_h */
