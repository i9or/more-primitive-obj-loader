//
//  Tex2Array.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef Tex2Array_h
#define Tex2Array_h

#include "DynamicArray.h"
#include "Tex2.h"

typedef struct {
  unsigned int count;
  unsigned int capacity;
  Tex2 *data;
} Tex2Array;

void initTex2Array(Tex2Array *arr);
void writeTex2Array(Tex2Array *arr, Tex2 t);
void freeTex2Array(Tex2Array *arr);

#endif /* Tex2Array_h */
