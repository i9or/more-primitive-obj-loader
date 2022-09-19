#ifndef UTILITIES_H
#define UTILITIES_H

#include <string.h>

#define STRIP_NEWLINE(str) (str)[strcspn((str), "\r\n")] = '\0'

#endif // UTILITIES_H
