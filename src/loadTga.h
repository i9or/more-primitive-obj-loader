#ifndef __TGA_LOADER_H__
#define __TGA_LOADER_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "TgaImage.h"

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

	printTgaHeader(img->header);

	printf("TGA image %s is loaded successfully", fileName);
	fclose(pFile);
	return true;
}

#endif // __TGA_LOADER_H__
