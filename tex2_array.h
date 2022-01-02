#ifndef __TEX2_ARRAY_H__
#define __TEX2_ARRAY_H__

#include "dynamic_array.h"
#include "tex2.h"

typedef struct {
    unsigned int count;
    unsigned int capacity;
    tex2 *data;
} tex2_array;

void init_tex2_array(tex2_array *arr) {
    arr->count = 0;
    arr->capacity = 0;
    arr->data = NULL;
}

void write_tex2_array(tex2_array *arr, tex2 t) {
    if (arr->capacity < arr->count + 1) {
        unsigned int old_capacity = arr->capacity;
        arr->capacity = GROW_CAPACITY(old_capacity);
        arr->data = GROW_ARRAY(tex2, arr->data, arr->capacity);
    }

    arr->data[arr->count] = t;
    arr->count++;
}

void free_tex2_array(tex2_array *arr) {
    FREE_ARRAY(arr->data);
    init_tex2_array(arr);
}

#endif // __TEX2_ARRAY_H__
