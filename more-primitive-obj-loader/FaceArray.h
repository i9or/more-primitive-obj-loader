//
//  FaceArray.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef FaceArray_h
#define FaceArray_h

#include "DynamicArray.h"
#include "Face.h"

typedef struct {
  unsigned int count;
  unsigned int capacity;
  Face *data;
} FaceArray;

void initFaceArray(FaceArray *arr);
void writeFaceArray(FaceArray *arr, Face f);
void freeFaceArray(FaceArray *arr);

#endif /* FaceArray_h */
