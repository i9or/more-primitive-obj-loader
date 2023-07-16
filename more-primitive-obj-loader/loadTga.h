//
//  loadTga.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef loadTga_h
#define loadTga_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "TgaImage.h"

bool loadTga(const char *fileName, TgaImage *img);

#endif /* loadTga_h */
