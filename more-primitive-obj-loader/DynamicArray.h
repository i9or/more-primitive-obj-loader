//
//  DynamicArray.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef DynamicArray_h
#define DynamicArray_h

#include <stdlib.h>

#define GROW_CAPACITY(capacity) \
  ((capacity) < 8 ? 8 : (unsigned int)((capacity)*1.5))

#define GROW_ARRAY(type, pointer, newCount) \
  (type *)reallocate(pointer, sizeof(type) * (newCount))

#define FREE_ARRAY(pointer) reallocate(pointer, 0)

void *reallocate(void *pointer, size_t newSize);

#endif /* DynamicArray_h */
