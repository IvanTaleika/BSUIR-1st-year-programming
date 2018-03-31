#pragma once

FILE* BMPOpen();
FILE* getBMPSaveFile();
void insertionSort(unsigned char* ms, int size);
int BMPFileVerification(BITMAPFILEHEADER* BMPHeader, BITMAPV5HEADER* BMPInfo);
void memoryCleaning(BITMAPFILEHEADER* BMPHeader, void* BMPInfo, void* pixelArray, FILE* source, FILE* SaveDestination, void* colorTable);
void showError(int errorType);