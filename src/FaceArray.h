#ifndef FACE_ARRAY_H
#define FACE_ARRAY_H

#include "DynamicArray.h"
#include "Face.h"

typedef struct {
	unsigned int count;
	unsigned int capacity;
	Face *data;
} FaceArray;

void initFaceArray(FaceArray *arr) {
	arr->count = 0;
	arr->capacity = 0;
	arr->data = NULL;
}

void writeFaceArray(FaceArray *arr, Face f) {
	if (arr->capacity < arr->count + 1) {
		unsigned int oldCapacity = arr->capacity;
		arr->capacity = GROW_CAPACITY(oldCapacity);
		arr->data = GROW_ARRAY(Face, arr->data, arr->capacity);
	}

	arr->data[arr->count] = f;
	arr->count++;
}

void freeFaceArray(FaceArray *arr) {
	FREE_ARRAY(arr->data);
	initFaceArray(arr);
}

#endif // FACE_ARRAY_H
