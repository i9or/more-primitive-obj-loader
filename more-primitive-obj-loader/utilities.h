//
//  utilities.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef utilities_h
#define utilities_h

#include <string.h>

#define STRIP_NEWLINE(str) (str)[strcspn((str), "\r\n")] = '\0'

#endif /* utilities_h */
