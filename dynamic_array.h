#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#include <stdlib.h>

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (unsigned int)((capacity)*1.5))

#define GROW_ARRAY(type, pointer, newCount) \
    (type *)reallocate(pointer, sizeof(type) * (newCount))

#define FREE_ARRAY(pointer) reallocate(pointer, 0)

void *reallocate(void *pointer, size_t new_size) {
    if (new_size == 0) {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, new_size);
    if (result == NULL) {
        exit(1);
    }

    return result;
}

#endif // __DYNAMIC_ARRAY_H__
