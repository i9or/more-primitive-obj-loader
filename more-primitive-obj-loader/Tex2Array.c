//
//  Tex2Array.c
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#include "Tex2Array.h"

void initTex2Array(Tex2Array *arr) {
  arr->count = 0;
  arr->capacity = 0;
  arr->data = NULL;
}

void writeTex2Array(Tex2Array *arr, Tex2 t) {
  if (arr->capacity < arr->count + 1) {
    unsigned int oldCapacity = arr->capacity;
    arr->capacity = GROW_CAPACITY(oldCapacity);
    arr->data = GROW_ARRAY(Tex2, arr->data, arr->capacity);
  }

  arr->data[arr->count] = t;
  arr->count++;
}

void freeTex2Array(Tex2Array *arr) {
  FREE_ARRAY(arr->data);
  initTex2Array(arr);
}
