#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BMP.h"
#include "auxiliaryFunctions.h"

BITMAPFILEHEADER* readBITMAPFILEHEADER(FILE* source) {
	rewind(source);
	BITMAPFILEHEADER* BMPHeader = (BITMAPFILEHEADER*) malloc(sizeof(BITMAPFILEHEADER));
	if (fread(BMPHeader, sizeof(BITMAPFILEHEADER), 1, source)) {
		return BMPHeader;
	} else {
		return nullptr;
	}
}

unsigned long int readBMPVertion(FILE* source) {
	rewind(source);
	fseek(source, sizeof(BITMAPFILEHEADER), SEEK_CUR);
	unsigned long int BMPVertion = 0;
	fread(&BMPVertion, sizeof(BMPVertion), 1, source);
	return BMPVertion;
}

void* readInBITMAPV5HEADER(FILE* source) {
	unsigned long int BMPVertion = readBMPVertion(source);
	fseek(source, -sizeof(BMPVertion), SEEK_CUR);
	BITMAPV5HEADER* BMPInfo = (BITMAPV5HEADER*) calloc(1, sizeof(BITMAPV5HEADER));
	if (fread(BMPInfo, BMPVertion, 1, source)) {
		return BMPInfo;
	} else {
		return nullptr;
	}
}

unsigned long int getSizeImage(BITMAPV5HEADER* info) {
	if (info->bV5SizeImage == 0) {
		if (info->bV5Width % 4) {
			int tempWidth = info->bV5Width / 4;
			tempWidth++;
			tempWidth *= 4;
			info->bV5SizeImage = tempWidth * abs(info->bV5Height) * info->bV5BitCount / BIT_8;
		} else {
			info->bV5SizeImage = info->bV5Width * abs(info->bV5Height)	* info->bV5BitCount / BIT_8;
		}
	}
	return info->bV5SizeImage;	
}

unsigned long int getClrUsed(BITMAPV5HEADER* info) {
	if (info->bV5BitCount <= 8 && !info->bV5ClrUsed) {
		info->bV5ClrUsed = pow(BIT_2, info->bV5BitCount);
	}
	return info->bV5ClrUsed;
}

void* readPixelMatrix(FILE* source, int bfOffBits, unsigned long int sizeImage, unsigned short int bitCount) {
	rewind(source);
	fseek(source, bfOffBits, SEEK_CUR);
	switch (bitCount) {
	default:
		return nullptr;
	case BIT_1: {
		pixel1* pixelArray = (pixel1*) malloc(sizeImage);
		if (!fread(pixelArray, sizeImage, 1, source)) {
			return nullptr;
		}
		return pixelArray;
	}
	case BIT_2: {
		pixel2* pixelArray = (pixel2*) malloc(sizeImage);
		if (!fread(pixelArray, sizeImage, 1, source)) {
			return nullptr;
		}
		return pixelArray;
	}
	case BIT_4: {
		pixel4* pixelArray = (pixel4*) malloc(sizeImage);
		if (!fread(pixelArray, sizeImage, 1, source)) {
			return nullptr;
		}
		return pixelArray;
	}
	case BIT_8: {
		pixel8* pixelArray = (pixel8*) malloc(sizeImage);
		if (!fread(pixelArray, sizeImage, 1, source)) {
			return nullptr;
		}
		return pixelArray;
	}
	case BIT_16: {
		pixel16* pixelArray = (pixel16*) malloc(sizeImage);
		if (!fread(pixelArray, sizeImage, 1, source)) {
			return nullptr;
		}
		return pixelArray;
	}
	case BIT_24: {
		pixel24* pixelArray = (pixel24*) malloc(sizeImage);
		if (!fread(pixelArray, sizeImage, 1, source)) {
			return nullptr;
		}
		return pixelArray;
	}
	}
}

void* readColorTable(FILE* source, unsigned long int clrUsed, unsigned short int BMPVertion) {
	rewind(source);
	fseek(source, sizeof(BITMAPFILEHEADER) + BMPVertion, SEEK_CUR);
	if (BMPVertion == VERSION_CORE) {
		pixel24* colorTable = (pixel24*) malloc(clrUsed * sizeof(pixel24));
		if (fread(colorTable, clrUsed * sizeof(pixel24), 1, source)) {
			return colorTable;
		} else {
			return nullptr;
		}
	}
	if (BMPVertion == VERSION_3 || BMPVertion == VERSION_4 || BMPVertion == VERSION_5) {
		pixel32* colorTable = (pixel32*) malloc(clrUsed * sizeof(pixel32));
		if (fread(colorTable, clrUsed * sizeof(pixel32), 1, source)) {
			return colorTable;
		} else {
			return nullptr;
		}
	} else {
		return nullptr;
	}
}

void writeBMP(BITMAPFILEHEADER* BMPHeader, BITMAPV5HEADER* BMPInfo, void* pixelArray, FILE* destination, void* colorTable) {
	rewind(destination);
	fwrite(BMPHeader, sizeof(BITMAPFILEHEADER), 1, destination);
	fwrite(BMPInfo, BMPInfo->bV5Size, 1, destination);
	if (colorTable) {
		if (BMPInfo->bV5Size == VERSION_CORE) {
			fwrite(colorTable, BMPInfo->bV5ClrUsed * sizeof(pixel24), 1, destination);
		} else {
			fwrite(colorTable, BMPInfo->bV5ClrUsed * sizeof(pixel32), 1, destination);
		}
	}
	fwrite(pixelArray, ((BITMAPV5HEADER*) BMPInfo)->bV5SizeImage, 1, destination);
	return;
}

bool pixelArrayNegative(void* pixelArray, int bitCount, int SizeImage) {
	switch (bitCount) {
	default:
		return false;
	case BIT_16:
		for (int i = 0; i < SizeImage / bitCount * BIT_8; i++) {
			((pixel16*) pixelArray)[i].red = BIT_4_MAX - ((pixel16*) pixelArray)[i].red;
			((pixel16*) pixelArray)[i].green = BIT_4_MAX - ((pixel16*) pixelArray)[i].green;
			((pixel16*) pixelArray)[i].blue = BIT_4_MAX - ((pixel16*) pixelArray)[i].blue;
		}
		return true;
	case BIT_24:
		for (int i = 0; i < SizeImage / bitCount * BIT_8; i++) {
			((pixel24*) pixelArray)[i].red = BIT_8_MAX - ((pixel24*) pixelArray)[i].red;
			((pixel24*) pixelArray)[i].green = BIT_8_MAX - ((pixel24*) pixelArray)[i].green;
			((pixel24*) pixelArray)[i].blue = BIT_8_MAX - ((pixel24*) pixelArray)[i].blue;
		}
		return true;
	}
}

bool colorTableNegative(void* colorArray, int clrUsed, int BMPVersion) {
	if (BMPVersion == VERSION_CORE) {
		for (int i = 0; i < clrUsed; i++) {
			((pixel24*) colorArray)[i].red = BIT_8_MAX - ((pixel24*) colorArray)[i].red;
			((pixel24*) colorArray)[i].green = BIT_8_MAX - ((pixel24*) colorArray)[i].green;
			((pixel24*) colorArray)[i].blue = BIT_8_MAX - ((pixel24*) colorArray)[i].blue;
		}
		return true;
	} else if (BMPVersion == VERSION_3 || BMPVersion == VERSION_4 || BMPVersion == VERSION_4) {
		for (int i = 0; i < clrUsed; i++) {
			((pixel32*) colorArray)[i].red = BIT_8_MAX - ((pixel32*) colorArray)[i].red;
			((pixel32*) colorArray)[i].green = BIT_8_MAX - ((pixel32*) colorArray)[i].green;
			((pixel32*) colorArray)[i].blue = BIT_8_MAX - ((pixel32*) colorArray)[i].blue;
		}
		return true;
	} else {
		return false;
	}
}

bool pixelArrayGrayscale(void* pixelArray, int bitCount, int SizeImage) {
	switch (bitCount) {
	default:
		return false;
	case BIT_16:
		for (int i = 0; i < SizeImage / bitCount * BIT_8; i++) {
			float gray = GRAYSCALE_RED * ((pixel16*) pixelArray)[i].red + GRAYSCALE_GREEN * ((pixel16*) pixelArray)[i].green + GRAYSCALE_BLUE * ((pixel16*) pixelArray)[i].blue;
			((pixel16*) pixelArray)[i].red = gray;
			((pixel16*) pixelArray)[i].green = gray;
			((pixel16*) pixelArray)[i].blue = gray;
		}
		return true;
	case BIT_24:
		for (int i = 0; i < SizeImage / bitCount * BIT_8; i++) {
			float gray = GRAYSCALE_RED * ((pixel24*) pixelArray)[i].red + GRAYSCALE_GREEN * ((pixel24*) pixelArray)[i].green + GRAYSCALE_BLUE * ((pixel24*) pixelArray)[i].blue;
			((pixel24*) pixelArray)[i].red = gray;
			((pixel24*) pixelArray)[i].green = gray;
			((pixel24*) pixelArray)[i].blue = gray;
		}
		return true;
	}
}

bool colorTableGrayscale(void* colorArray, int clrUsed, int BMPVersion) {
	if (BMPVersion == VERSION_CORE) {
		for (int i = 0; i < clrUsed; i++) {
			float gray = GRAYSCALE_RED * ((pixel24*) colorArray)[i].red + GRAYSCALE_GREEN * ((pixel24*) colorArray)[i].green + GRAYSCALE_BLUE * ((pixel24*) colorArray)[i].blue;
			((pixel24*) colorArray)[i].red = gray;
			((pixel24*) colorArray)[i].green = gray;
			((pixel24*) colorArray)[i].blue = gray;
		}
		return true;
	} else if (BMPVersion == VERSION_3 || BMPVersion == VERSION_4 || BMPVersion == VERSION_4) {
		for (int i = 0; i < clrUsed; i++) {
			float gray = GRAYSCALE_RED * ((pixel32*) colorArray)[i].red + GRAYSCALE_GREEN * ((pixel32*) colorArray)[i].green + GRAYSCALE_BLUE * ((pixel32*) colorArray)[i].blue;
			((pixel32*) colorArray)[i].red = gray;
			((pixel32*) colorArray)[i].green = gray;
			((pixel32*) colorArray)[i].blue = gray;
		}
		return true;
	} else {
		return false;
	}
}

bool MedianFilter(void* pixelArray, int windowSize, int bitCount, int imageWidth, int imageHeigth) {
	if (imageWidth % 4) {
		int temp = imageWidth / 4;
		imageWidth = (temp + 1) * 4;
	}
	switch (bitCount) {
	default:
		return false;
	case BIT_16: {
		unsigned char* maskRed = (unsigned char*) malloc(windowSize * windowSize * sizeof(unsigned char));
		unsigned char* maskGreen = (unsigned char*) malloc(windowSize * windowSize * sizeof(unsigned char));
		unsigned char* maskBlue = (unsigned char*) malloc(windowSize * windowSize * sizeof(unsigned char));
		int elementCount = 0;
		int string = 0;
		for (int i = 0; string < imageHeigth; i++) {
			for (int XWindowSize = -windowSize / 2; XWindowSize <= windowSize / 2; XWindowSize++) {
				if (i + XWindowSize >= 0 && i + XWindowSize < imageWidth) {
					for (int YWindowSize = -windowSize / 2; YWindowSize <= windowSize / 2; YWindowSize++) {
						if (string + YWindowSize >= 0 && string + YWindowSize < imageHeigth) {
							maskRed[elementCount] = ((pixel16*) pixelArray)[i + XWindowSize + (string + YWindowSize) * imageWidth].red;
							maskGreen[elementCount] = ((pixel16*) pixelArray)[i + XWindowSize + (string + YWindowSize) * imageWidth].green;
							maskBlue[elementCount] = ((pixel16*) pixelArray)[i + XWindowSize + (string + YWindowSize) * imageWidth].blue;
						}
						elementCount++;
					}
				}
			}
			insertionSort(maskRed, elementCount);
			insertionSort(maskGreen, elementCount);
			insertionSort(maskBlue, elementCount);
			if (elementCount % 2) {
				((pixel16*) pixelArray)[i + string * imageWidth].red = maskRed[elementCount / 2];
				((pixel16*) pixelArray)[i + string * imageWidth].green = maskGreen[elementCount / 2];
				((pixel16*) pixelArray)[i + string * imageWidth].blue = maskBlue[elementCount / 2];
			} else {
				((pixel16*) pixelArray)[i + string * imageWidth].red = (maskRed[elementCount / 2] + maskRed[elementCount / 2 - 1]) / 2;
				((pixel16*) pixelArray)[i + string * imageWidth].green = (maskGreen[elementCount / 2] + maskGreen[elementCount / 2 - 1]) / 2;
				((pixel16*) pixelArray)[i + string * imageWidth].blue = (maskBlue[elementCount / 2] + maskBlue[elementCount / 2 - 1]) / 2;
			}
			elementCount = 0;
			if (i == imageWidth - 1) {
				string++;
				i = -1;
			}
		}
		free(maskRed);
		free(maskGreen);
		free(maskBlue);
		return true;
	}
	case BIT_24: {
		unsigned char* maskRed = (unsigned char*) malloc(windowSize * windowSize * sizeof(unsigned char));
		unsigned char* maskGreen = (unsigned char*) malloc(windowSize * windowSize * sizeof(unsigned char));
		unsigned char* maskBlue = (unsigned char*) malloc(windowSize * windowSize * sizeof(unsigned char));
		int elementCount = 0;
		int string = 0;
		for (int i = 0; string < imageHeigth; i++) {
			for (int XWindowSize = -windowSize / 2; XWindowSize <= windowSize / 2; XWindowSize++) {
				if (i + XWindowSize >= 0 && i + XWindowSize < imageWidth) {
					if (i + XWindowSize >= 0 && i + XWindowSize < imageWidth) {
						for (int YWindowSize = -windowSize / 2; YWindowSize <= windowSize / 2; YWindowSize++) {
							if (string + YWindowSize >= 0 && string + YWindowSize < imageHeigth) {
								maskRed[elementCount] = ((pixel24*) pixelArray)[i + XWindowSize + (string + YWindowSize) * imageWidth].red;
								maskGreen[elementCount] = ((pixel24*) pixelArray)[i + XWindowSize + (string + YWindowSize) * imageWidth].green;
								maskBlue[elementCount] = ((pixel24*) pixelArray)[i + XWindowSize + (string + YWindowSize) * imageWidth].blue;
							}
							elementCount++;
						}
					}
				}
			}
			insertionSort(maskRed, elementCount);
			insertionSort(maskGreen, elementCount);
			insertionSort(maskBlue, elementCount);
			if (elementCount % 2) {
				((pixel24*) pixelArray)[i + string * imageWidth].red = maskRed[elementCount / 2];
				((pixel24*) pixelArray)[i + string * imageWidth].green = maskGreen[elementCount / 2];
				((pixel24*) pixelArray)[i + string * imageWidth].blue = maskBlue[elementCount / 2];
			} else {
				((pixel24*) pixelArray)[i + string * imageWidth].red = (maskRed[elementCount / 2] + maskRed[elementCount / 2 - 1]) / 2;
				((pixel24*) pixelArray)[i + string * imageWidth].green = (maskGreen[elementCount / 2] + maskGreen[elementCount / 2 - 1]) / 2;
				((pixel24*) pixelArray)[i + string * imageWidth].blue = (maskBlue[elementCount / 2] + maskBlue[elementCount / 2 - 1]) / 2;
			}
			elementCount = 0;
			if (i == imageWidth - 1) {
				string++;
				i = -1;
			}
		}
		free(maskRed);
		free(maskGreen);
		free(maskBlue);
		return true;
	}
	}
}

bool pixelArrayGammaCorrection(void* pixelArray, int bitCount, int SizeImage, double y) {
	switch (bitCount) {
	default:
		return false;
	case BIT_16:
		for (int i = 0; i < SizeImage / bitCount * BIT_8; i++) {
			((pixel16*) pixelArray)[i].red = pow((double) ((pixel16*) pixelArray)[i].red / (double) BIT_4_MAX, y) * BIT_4_MAX;
			((pixel16*) pixelArray)[i].green = pow((double) ((pixel16*) pixelArray)[i].green / (double) BIT_4_MAX, y) * BIT_4_MAX;
			((pixel16*) pixelArray)[i].blue = pow((double) ((pixel16*) pixelArray)[i].blue / (double) BIT_4_MAX, y) * BIT_4_MAX;
		}
		return true;
	case BIT_24:
		for (int i = 0; i < SizeImage / bitCount * BIT_8; i++) {
			((pixel24*) pixelArray)[i].red = pow((double) ((pixel24*) pixelArray)[i].red / (double) BIT_8_MAX, y) * BIT_8_MAX;
			((pixel24*) pixelArray)[i].green = pow((double) ((pixel24*) pixelArray)[i].green / (double) BIT_8_MAX, y) * BIT_8_MAX;
			((pixel24*) pixelArray)[i].blue = pow((double) ((pixel24*) pixelArray)[i].blue / (double) BIT_8_MAX, y) * BIT_8_MAX;
		}
		return true;
	}
}

bool colorTableGammaCorrection(void* colorArray, int clrUsed, int BMPVersion, double y) {
	if (BMPVersion == VERSION_CORE) {
		for (int i = 0; i < clrUsed; i++) {
			((pixel24*) colorArray)[i].red = pow((double) ((pixel24*) colorArray)[i].red / (double) BIT_8_MAX, y) * BIT_8_MAX;
			((pixel24*) colorArray)[i].green = pow((double) ((pixel24*) colorArray)[i].green / (double) BIT_8_MAX, y) * BIT_8_MAX;
			((pixel24*) colorArray)[i].blue = pow((double) ((pixel24*) colorArray)[i].blue / (double) BIT_8_MAX, y) * BIT_8_MAX;
		}
		return true;
	} else if (BMPVersion == VERSION_3 || BMPVersion == VERSION_4 || BMPVersion == VERSION_4) {
		for (int i = 0; i < clrUsed; i++) {
			((pixel32*) colorArray)[i].red = pow((double) ((pixel32*) colorArray)[i].red / (double) BIT_8_MAX, y) * BIT_8_MAX;
			((pixel32*) colorArray)[i].green = pow((double) ((pixel32*) colorArray)[i].green / (double) BIT_8_MAX, y) * BIT_8_MAX;
			((pixel32*) colorArray)[i].blue = pow((double) ((pixel32*) colorArray)[i].blue / (double) BIT_8_MAX, y) * BIT_8_MAX;
		}
		return true;
	} else {
		return 0;
	}
}