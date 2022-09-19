#ifndef __TGA_IMAGE_H__
#define __TGA_IMAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void printTgaHeaderLine(char *label, int value) {
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

TgaPixel *initImageData(size_t numberOfPixels) {
	TgaPixel *result = malloc(numberOfPixels * sizeof(TgaPixel));

	for (size_t i = 0; i < numberOfPixels; ++i) {
		result[i].r = 0;
		result[i].g = 0;
		result[i].b = 0;
		result[i].a = 0;
	}

	return result;
}

void freeImageData(TgaPixel **data) {
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

#endif // __TGA_IMAGE_H__
