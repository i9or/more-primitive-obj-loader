//
//  TgaImage.h
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#ifndef TgaImage_h
#define TgaImage_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char idLength;
  char colorMapType;
  char imageType;
  short colorMapFirstEntryIndex;
  short colorMapLength;
  char colorMapEntrySize;
  short xOrigin;
  short yOrigin;
  short width;
  short height;
  char pixelDepth;
  char imageDescriptor;
} TgaHeader;

typedef struct {
  unsigned char r, g, b, a;
} TgaPixel;

typedef struct {
  TgaHeader header;
  TgaPixel *imageData;
} TgaImage;

void printTgaHeader(TgaHeader header);
bool isTgaImageFormatSupported(TgaHeader header);
TgaPixel *initImageData(size_t numberOfPixels);
void freeImageData(TgaPixel **data);
void initTgaImage(TgaImage *img);
void freeTgaImage(TgaImage *img);

#endif /* TgaImage_h */
