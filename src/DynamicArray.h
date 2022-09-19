#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (unsigned int)((capacity)*1.5))

#define GROW_ARRAY(type, pointer, newCount) \
	(type *)reallocate(pointer, sizeof(type) * (newCount))

#define FREE_ARRAY(pointer) reallocate(pointer, 0)

void *reallocate(void *pointer, size_t newSize) {
	if (newSize == 0) {
		free(pointer);
		return NULL;
	}

	void *result = realloc(pointer, newSize);
	if (result == NULL) {
		exit(1);
	}

	return result;
}

#endif // DYNAMIC_ARRAY_H
