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
  TgaHeader header;
  unsigned char *imageData;
} TgaImage;

void printTgaHeader(TgaHeader header);
bool isTgaImageFormatSupported(TgaHeader header);
unsigned char *initImageData(size_t numberOfPixels);
void freeImageData(unsigned char **data);
void initTgaImage(TgaImage *img);
void freeTgaImage(TgaImage *img);

#endif /* TgaImage_h */
