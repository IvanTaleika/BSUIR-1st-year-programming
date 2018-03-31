#include <stdio.h>
#include "BMP.h"
#include "auxiliaryFunctions.h"
#include "programCover.h"

#define BMP_FILE_ERROR 1
#define PROGRAM_SUPPORT_ERROR 2

int main(void) {
	FILE* BMPFile = BMPOpen();
	BITMAPFILEHEADER* BMPHeader = readBITMAPFILEHEADER(BMPFile);
	if (!BMPHeader) {
		showError(BMP_FILE_ERROR);
		return 0;
	}
	BITMAPV5HEADER* BMPInfo = (BITMAPV5HEADER*) readInBITMAPV5HEADER(BMPFile);
	if (!BMPInfo) {
		showError(BMP_FILE_ERROR);
		return 0;
	}
	switch (BMPFileVerification(BMPHeader, BMPInfo)) {
	case BMP_FILE_ERROR:
		showError(BMP_FILE_ERROR);
		return 0;
	case PROGRAM_SUPPORT_ERROR:
		showError(PROGRAM_SUPPORT_ERROR);
		return 0;
	}
	getSizeImage(BMPInfo);
	getClrUsed(BMPInfo);
	switch (BMPInfo->bV5BitCount) {
	default:
		showError(PROGRAM_SUPPORT_ERROR);
		return 0;
	case BIT_1: {
		pixel1* pixelArray = (pixel1*) readPixelMatrix(BMPFile, BMPHeader->bfOffBits, BMPInfo->bV5SizeImage, BMPInfo->bV5BitCount);
		if (!pixelArray) {
			break;
		}
		if (BMPInfo->bV5Size == VERSION_CORE) {
			pixel24* colorTable24 = (pixel24*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable24) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable24);

		} else {
			pixel32* colorTable32 = (pixel32*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable32) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable32);
		}
		return 0;
	}
	case BIT_2: {
		pixel2* pixelArray = (pixel2*) readPixelMatrix(BMPFile, BMPHeader->bfOffBits, BMPInfo->bV5SizeImage, BMPInfo->bV5BitCount);
		if (!pixelArray) {
			break;
		}
		if (BMPInfo->bV5Size == VERSION_CORE) {
			pixel24* colorTable24 = (pixel24*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable24) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable24);

		} else {
			pixel32* colorTable32 = (pixel32*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable32) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable32);
		}
		return 0;
	}
	case BIT_4: {
		pixel4* pixelArray = (pixel4*) readPixelMatrix(BMPFile, BMPHeader->bfOffBits, BMPInfo->bV5SizeImage, BMPInfo->bV5BitCount);
		if (!pixelArray) {
			break;
		}
		if (BMPInfo->bV5Size == VERSION_CORE) {
			pixel24* colorTable24 = (pixel24*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable24) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable24);

		} else {
			pixel32* colorTable32 = (pixel32*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable32) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable32);
		}
		return 0;
	}
	case BIT_8: {
		pixel8* pixelArray = (pixel8*) readPixelMatrix(BMPFile, BMPHeader->bfOffBits, BMPInfo->bV5SizeImage, BMPInfo->bV5BitCount);
		if (!pixelArray) {
			break;
		}
		if (BMPInfo->bV5Size == VERSION_CORE) {
			pixel24* colorTable24 = (pixel24*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable24) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable24);

		} else {
			pixel32* colorTable32 = (pixel32*) readColorTable(BMPFile, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size);
			if (!colorTable32) {
				break;
			}
			menu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable32);
		}
		return 0;
	}
		break;
	case BIT_16: {
		pixel16* pixelArray = (pixel16*) readPixelMatrix(BMPFile, BMPHeader->bfOffBits, BMPInfo->bV5SizeImage, BMPInfo->bV5BitCount);
		if (!pixelArray) {
			break;
		} 
		menu(BMPHeader, BMPFile, BMPInfo, pixelArray, nullptr);
	}
		return 0;
	case BIT_24: {
		pixel24* pixelArray = (pixel24*) readPixelMatrix(BMPFile, BMPHeader->bfOffBits, BMPInfo->bV5SizeImage, BMPInfo->bV5BitCount);
		if (!pixelArray) {
			break;
		}
		menu(BMPHeader, BMPFile, BMPInfo, pixelArray, nullptr);
		return 0;
	}
	}
	showError(BMP_FILE_ERROR);
	return 0;
}