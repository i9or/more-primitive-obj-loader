#ifndef __VEC3_ARRAY_H__
#define __VEC3_ARRAY_H__

#include "dynamic_array.h"
#include "vec3.h"

typedef struct {
    unsigned int count;
    unsigned int capacity;
    vec3 *data;
} vec3_array;

void init_vec3_array(vec3_array *arr) {
    arr->count = 0;
    arr->capacity = 0;
    arr->data = NULL;
}

void write_vec3_array(vec3_array *arr, vec3 v) {
    if (arr->capacity < arr->count + 1) {
        unsigned int old_capacity = arr->capacity;
        arr->capacity = GROW_CAPACITY(old_capacity);
        arr->data = GROW_ARRAY(vec3, arr->data, arr->capacity);
    }

    arr->data[arr->count] = v;
    arr->count++;
}

void free_vec3_array(vec3_array *arr) {
    FREE_ARRAY(arr->data);
    init_vec3_array(arr);
}

#endif // __VEC3_ARRAY_H__
