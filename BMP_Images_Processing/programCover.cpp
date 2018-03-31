#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "BMP.h"
#include "auxiliaryFunctions.h"

void endProcessing(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable) {
	while (true) {
		puts("1. Save changes.");
		puts("2. Save as a new .bmp document.");
		puts("3. Don't save changes.");
		switch (getch()) {
		case '1':
			writeBMP(BMPHeader, BMPInfo, pixelArray, BMPFile, colorTable);
			memoryCleaning(BMPHeader, BMPInfo, pixelArray, BMPFile, BMPFile, colorTable);
			return;
		case '2': {
			system("cls");
			FILE* BMPSaveFile = getBMPSaveFile();
			if (!BMPSaveFile) {
				system("cls");
				puts("Can't save as a new file.");
				break;
			}
			writeBMP(BMPHeader, BMPInfo, pixelArray, BMPSaveFile, colorTable);
			memoryCleaning(BMPHeader, BMPInfo, pixelArray, BMPFile, BMPSaveFile, colorTable);
			return;
		}
		case '3':
			memoryCleaning(BMPHeader, BMPInfo, pixelArray, BMPFile, BMPFile, colorTable);
			return;
		}
	}
}

void grayscaleEffectMenu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable) {
	if (colorTable) {
		if (colorTableGrayscale(colorTable, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size)) {
			puts("Processing end correctly.\n");
		} else {
			puts("Processing error.\n");
		}
	} else if (pixelArrayGrayscale(pixelArray, BMPInfo->bV5BitCount, BMPInfo->bV5SizeImage)) {
		puts("Processing end correctly.\n");
	} else {
		puts("Processing error.\n");
	}

}

void negativeEffectMenu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable) {
	if (colorTable) {
		if (colorTableNegative(colorTable, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size)) {
			puts("Processing end correctly.\n");
		} else {
			puts("Processing error.\n");
		}
	} else if (pixelArrayNegative(pixelArray, BMPInfo->bV5BitCount, BMPInfo->bV5SizeImage)) {
		puts("Processing end correctly.\n");
	} else {
		puts("Processing error.\n");
	}

}

void medianFilterMenu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray) {
	int windowSize;
	puts("Enter the size of the side of the median filter window:");
	rewind(stdin);
	scanf("%d", &windowSize);
	system("cls");
	if (windowSize > 1 && windowSize <= BMPInfo->bV5Width && windowSize <= BMPInfo->bV5Height) {
		if (MedianFilter(pixelArray, windowSize, BMPInfo->bV5BitCount, BMPInfo->bV5Width, BMPInfo->bV5Height)) {
			puts("Processing end correctly.\n");
		} else {
			puts("Processing error.\n");
		}
	} else {
		puts("Illegal window size.\n");
	}
}

void gammaCorrectionMenu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable) {
	double y;
	puts("Enter the y value:");
	rewind(stdin);
	scanf("%lf", &y);
	system("cls");
	if (colorTable) {
		if (colorTableGammaCorrection(colorTable, BMPInfo->bV5ClrUsed, BMPInfo->bV5Size, y)) {
			puts("Processing end correctly.\n");
		} else {
			puts("Processing error.\n");
		}
	} else if (pixelArrayGammaCorrection(pixelArray, BMPInfo->bV5BitCount, BMPInfo->bV5SizeImage, y)) {
		puts("Processing end correctly.\n");
	} else {
		puts("Processing error.\n");
	}
}

void menu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable) {
	while (true) {
		puts("Process picture:");
		puts("1. Negative.");
		puts("2. Grayscale.");
		puts("3. Median filter.");
		puts("4. Gamma correction.");
		puts("0. End processing.");
		switch (getch()) {
		default:
			system("cls");
			break;
		case '1':
			system("cls");
			negativeEffectMenu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable);
			break;
		case '2':
			system("cls");
			grayscaleEffectMenu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable);
			break;
		case '3':
			system("cls");
			if (colorTable) {
				puts("Median filter doesn't support if color specify with a color table.\n");
				break;
			}
			medianFilterMenu(BMPHeader, BMPFile, BMPInfo, pixelArray);
			break;
		case '4':
			system("cls");
			gammaCorrectionMenu(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable);
			break;
		case '0':
			system("cls");
			endProcessing(BMPHeader, BMPFile, BMPInfo, pixelArray, colorTable);
			return;
		}
	}
}