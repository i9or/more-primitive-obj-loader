//
//  Vec3Array.c
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#include "Vec3Array.h"

void initVec3Array(Vec3Array *arr) {
  arr->count = 0;
  arr->capacity = 0;
  arr->data = NULL;
}

void writeVec3Array(Vec3Array *arr, Vec3 v) {
  if (arr->capacity < arr->count + 1) {
    unsigned int oldCapacity = arr->capacity;
    arr->capacity = GROW_CAPACITY(oldCapacity);
    arr->data = GROW_ARRAY(Vec3, arr->data, arr->capacity);
  }

  arr->data[arr->count] = v;
  arr->count++;
}

void freeVec3Array(Vec3Array *arr) {
  FREE_ARRAY(arr->data);
  initVec3Array(arr);
}
