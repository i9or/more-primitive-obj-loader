#ifndef __FACE_ARRAY_H__
#define __FACE_ARRAY_H__

#include "dynamic_array.h"
#include "face.h"

typedef struct {
    unsigned int count;
    unsigned int capacity;
    face *data;
} face_array;

void init_face_array(face_array *arr) {
    arr->count = 0;
    arr->capacity = 0;
    arr->data = NULL;
}

void write_face_array(face_array *arr, face f) {
    if (arr->capacity < arr->count + 1) {
        unsigned int old_capacity = arr->capacity;
        arr->capacity = GROW_CAPACITY(old_capacity);
        arr->data = GROW_ARRAY(face, arr->data, arr->capacity);
    }

    arr->data[arr->count] = f;
    arr->count++;
}

void free_face_array(face_array *arr) {
    FREE_ARRAY(arr->data);
    init_face_array(arr);
}

#endif // __FACE_ARRAY_H__
