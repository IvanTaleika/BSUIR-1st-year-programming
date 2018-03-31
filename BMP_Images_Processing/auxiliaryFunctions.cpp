#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BMP.h"

#define BUFFSIZE 256

void insertionSort(unsigned char* ms, int size) {
	int temp, j;
	for (int i = 1; i < size; i++) {
		j = i - 1;
		temp = ms[i];
		while (j >= 0 && temp < ms[j]) {
			ms[j + 1] = ms[j];
			j--;
		}
		ms[j + 1] = temp;
	}
}

void memoryCleaning(BITMAPFILEHEADER* BMPHeader, void* BMPInfo, void* pixelArray, FILE* source, FILE* SaveDestination, void* colorTable) {
	free(BMPHeader);
	BMPHeader = nullptr;
	free(BMPInfo);
	BMPInfo = nullptr;
	free(pixelArray);
	pixelArray = nullptr;
	fclose(source);
	source = nullptr;
	if (SaveDestination) {
		fclose(SaveDestination);
		SaveDestination = nullptr;
	}
	if (colorTable) {
		free(colorTable);
		colorTable = nullptr;
	}
}

FILE* BMPOpen() {
	char path[BUFFSIZE];
	FILE* file = nullptr;
	do {
		puts("Enter file path:");
		rewind(stdin);
		gets_s(path, BUFFSIZE);
		if (!strstr(path, ".bmp")) {
			system("cls");
			puts("Please, open only .bmp files.");
		} else {
			file = fopen(path, "r+b");
			if (!file) {
				system("cls");
				puts("file doesn't exist. Try another path.");
			}
		}
	} while (!file);
	system("cls");
	return file;
}

FILE* getBMPSaveFile() {
	char path[BUFFSIZE];
	FILE* file = nullptr;
	do {
		puts("Enter save path and a file name:");
		rewind(stdin);
		gets_s(path, BUFFSIZE);
		if (!strstr(path, ".bmp")) {
			system("cls");
			puts("Please, save your file as a BMP file.");
		} else {
			file = fopen(path, "wb");
			if (!file) {
				system("cls");
				puts("Path is incorrect. Try another path.");
			}
		}
	} while (!file);
	system("cls");
	return file;
}

void showError(int errorType) {
	switch (errorType) {
	default:
		return;
	case 1:
		puts("Your file is corrupted. Processing is imposible.");
		system("pause");
		return;
	case 2:
		puts("This vertion doesn't support. Processing is imposible.");
		system("pause");
		return;
	}
}

int BMPFileVerification(BITMAPFILEHEADER* BMPHeader, BITMAPV5HEADER* BMPInfo) {
	if (BMPHeader->bfType != 0x4d42 && BMPHeader->bfType != 0x424d) {
		return 1;
	}
	if (BMPInfo->bV5Compression != 0) {
		return 2;
	}
	if (BMPInfo->bV5CSType != 0) {
		return 2;
	}
	if (BMPInfo->bV5BitCount > BIT_8 && BMPInfo->bV5ClrUsed != 0) {
		return 2;
	}
	return 0;
}