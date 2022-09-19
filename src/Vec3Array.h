#ifndef VEC3_ARRAY_H
#define VEC3_ARRAY_H

#include "DynamicArray.h"
#include "Vec3.h"

typedef struct {
	unsigned int count;
	unsigned int capacity;
	Vec3 *data;
} Vec3Array;

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

#endif // VEC3_ARRAY_H
