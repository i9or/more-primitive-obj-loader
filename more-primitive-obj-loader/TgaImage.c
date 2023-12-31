//
//  TgaImage.c
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#include "TgaImage.h"

static void printTgaHeaderLine(char *label, int value) {
  printf("%-30s%d\n", label, value);
}

void printTgaHeader(TgaHeader header) {
  printTgaHeaderLine("ID Length:", header.idLength);
  printTgaHeaderLine("Color Map Type:", header.colorMapType);
  printTgaHeaderLine("Image Type:", header.imageType);
  printTgaHeaderLine("Color Map First Entry Index:",
                     header.colorMapFirstEntryIndex);
  printTgaHeaderLine("Color Map Length:", header.colorMapLength);
  printTgaHeaderLine("Color Map Entry Size:", header.colorMapEntrySize);
  printTgaHeaderLine("X Origin:", header.xOrigin);
  printTgaHeaderLine("Y Origin:", header.yOrigin);
  printTgaHeaderLine("Width:", header.width);
  printTgaHeaderLine("Height:", header.height);
  printTgaHeaderLine("TgaPixel Depth:", header.pixelDepth);
  printTgaHeaderLine("Image Descriptor:", header.imageDescriptor);

  if (((header.imageDescriptor >> 4) & 1) == 1) {
    printf("Image is right-to-left\n");
  } else {
    printf("Image is left-to-right\n");
  }

  if (((header.imageDescriptor >> 5) & 1) == 1) {
    printf("Image is top-to-bottom\n");
  } else {
    printf("Image is bottom-to-top\n");
  }
}

bool isTgaImageFormatSupported(TgaHeader header) {
  if (header.imageType != 2) {
    perror("Uncompressed true-color image are supported only");

    return false;
  }

  if (header.pixelDepth != 24 && header.pixelDepth != 32) {
    perror("Pixel depths of 24 bits and 32 bits supported only");

    return false;
  }

  if (header.colorMapType != 0) {
    perror("Images without color map are supported only");

    return false;
  }

  return true;
}

unsigned char *initImageData(size_t numberOfPixels) {
  unsigned char *result = malloc(numberOfPixels * sizeof(unsigned char) * 4);

  for (size_t i = 0; i < numberOfPixels * 4; i += 4) {
    result[i] = 0;
    result[i + 1] = 0;
    result[i + 2] = 0;
    result[i + 3] = 0;
  }

  return result;
}

void freeImageData(unsigned char **data) {
  free(*data);
  *data = NULL;
}

void initTgaImage(TgaImage *img) {
  img->header.idLength = 0;
  img->header.colorMapType = 0;
  img->header.imageType = 0;
  img->header.colorMapFirstEntryIndex = 0;
  img->header.colorMapLength = 0;
  img->header.colorMapEntrySize = 0;
  img->header.xOrigin = 0;
  img->header.yOrigin = 0;
  img->header.width = 0;
  img->header.height = 0;
  img->header.pixelDepth = 0;
  img->header.imageDescriptor = 0;

  img->imageData = NULL;
}

void freeTgaImage(TgaImage *img) {
  freeImageData(&img->imageData);
  initTgaImage(img);
}
