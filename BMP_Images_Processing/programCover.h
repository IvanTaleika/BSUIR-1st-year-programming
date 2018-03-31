#pragma once

void menu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable);
void endProcessing(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable);
void grayscaleEffectMenu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable);
void negativeEffectMenu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray, void* colorTable);
void medianFilterMenu(BITMAPFILEHEADER* BMPHeader, FILE* BMPFile, BITMAPV5HEADER* BMPInfo, void* pixelArray);