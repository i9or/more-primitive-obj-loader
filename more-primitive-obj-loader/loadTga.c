//
//  loadTga.c
//  more-primitive-obj-loader
//
//  Created by Igor on 16/07/2023.
//

#include "loadTga.h"

bool loadTga(const char *fileName, TgaImage *img) {
  initTgaImage(img);

  FILE *pFile = fopen(fileName, "r");
  if (!pFile) {
    printf("Error loading file: %s\n", fileName);
    return false;
  }

  img->header.idLength = (char)fgetc(pFile);
  img->header.colorMapType = (char)fgetc(pFile);
  img->header.imageType = (char)fgetc(pFile);
  fread(&(img->header.colorMapFirstEntryIndex), 2, 1, pFile);
  fread(&(img->header.colorMapLength), 2, 1, pFile);
  img->header.colorMapEntrySize = (char)fgetc(pFile);
  fread(&(img->header.xOrigin), 2, 1, pFile);
  fread(&(img->header.yOrigin), 2, 1, pFile);
  fread(&(img->header.width), 2, 1, pFile);
  fread(&(img->header.height), 2, 1, pFile);
  img->header.pixelDepth = (char)fgetc(pFile);
  img->header.imageDescriptor = (char)fgetc(pFile);

  if (isTgaImageFormatSupported(img->header)) {
    size_t numberOfPixels = img->header.width * img->header.height;
    img->imageData = initImageData(numberOfPixels);

    size_t bytesToRead = img->header.pixelDepth / 8;
    unsigned char rawPixel[4];

    for (size_t i = 0; i < numberOfPixels; ++i) {
      if (fread(rawPixel, 1, bytesToRead, pFile) != bytesToRead) {
        perror("Unexpected end of file");
        freeImageData(&img->imageData);
        return false;
      }

      img->imageData[i].r = rawPixel[2];
      img->imageData[i].g = rawPixel[1];
      img->imageData[i].b = rawPixel[0];

      if (bytesToRead == 4) {
        img->imageData[i].a = rawPixel[3];
      } else {
        img->imageData[i].a = 255;
      }
    }
  }

  printf("TGA image %s is loaded successfully\n", fileName);
  fclose(pFile);

  return true;
}
