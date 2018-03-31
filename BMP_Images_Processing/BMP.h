#pragma once

#include <stdio.h>

#define VERSION_CORE 12
#define VERSION_3 40
#define VERSION_4 108
#define VERSION_5 124
#define BIT_1 1
#define BIT_2 2
#define BIT_4 4
#define BIT_8 8
#define BIT_16 16
#define BIT_24 24
#define BIT_32 32
#define BIT_48 48
#define BIT_64 64
#define BIT_8_MAX 255
#define BIT_4_MAX 31

#define SIZEIMAGE_FIELD_POSITION 34

#define GRAYSCALE_RED 0.3
#define GRAYSCALE_GREEN 0.59
#define GRAYSCALE_BLUE 0.11

#pragma pack(push, 1)

struct BITMAPFILEHEADER {
	unsigned short int bfType;
	unsigned long int bfSize;
	unsigned short int bfReserved1;
	unsigned short int bfReserved2;
	unsigned long int bfOffBits;
};

struct BITMAPCOREHEADER {
	unsigned long int bcSize;
	unsigned short int bcWidth;
	unsigned short int bcHeight;
	unsigned short int bcPlanes;
	unsigned short int bcBitCount;
};

struct BITMAPINFOHEADER {
	unsigned long int biSize;
	int biWidth;
	int biHeight;
	unsigned short int biPlanes;
	unsigned short int biBitCount;
	unsigned long int biCompression;
	unsigned long int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned long int biClrUsed;
	unsigned long int biClrImportant;
};

struct CIEXYZ {
	float ciexyzX;
	float ciexyzY;
	float ciexyzZ;
};
/*int - заглушка типа PXPT2DOT30 (это 32-битное беззнаковое число с фиксированной запятой, 
у которого 2 старших бита отводятся под целую часть, а 30 младших — под дробную).*/

struct CIEXYZTRIPLE {
	CIEXYZ ciexyzRed;
	CIEXYZ ciexyzGreen;
	CIEXYZ ciexyzBlue;
};

struct BITMAPV4HEADER {
	unsigned long int bV4Size;
	int bV4Width;
	int bV4Height;
	unsigned short int bV4Planes;
	unsigned short int bV4BitCount;
	unsigned long int bV4Compression;
	unsigned long int bV4SizeImage;
	int bV4XPelsPerMeter;
	int bV4YPelsPerMeter;
	unsigned long int bV4ClrUsed;
	unsigned long int bV4ClrImportant;
	unsigned long int bV4RedMask;
	unsigned long int bV4GreenMask;
	unsigned long int bV4BlueMask;
	unsigned long int bV4AlphaMask;
	unsigned long int bV4CSType;
	CIEXYZTRIPLE bV4Endpoints_PLUG;
	unsigned long int bV4GammaRed;
	unsigned long int bV4GammaGreen;
	unsigned long int bV4GammaBlue;
};

struct BITMAPV5HEADER {
	unsigned long int bV5Size;
	int bV5Width;
	int bV5Height;
	unsigned short int bV5Planes;
	unsigned short int bV5BitCount;
	unsigned long int bV5Compression;
	unsigned long int bV5SizeImage;
	int bV5XPelsPerMeter;
	int bV5YPelsPerMeter;
	unsigned long int bV5ClrUsed;
	unsigned long int bV5ClrImportant;
	unsigned long int bV5RedMask;
	unsigned long int bV5GreenMask;
	unsigned long int bV5BlueMask;
	unsigned long int bV5AlphaMask;
	unsigned long int bV5CSType;
	CIEXYZTRIPLE bV5Endpoints_PLUG;
	unsigned long int bV5GammaRed;
	unsigned long int bV5GammaGreen;
	unsigned long int bV5GammaBlue;
	unsigned long int bV5Intent;
	unsigned long int bV5ProfileData;
	unsigned long int bV5ProfileSize;
	unsigned long int bV5Reserved;
};

struct pixel32 {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char reserved;
};

struct pixel24 {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct pixel16 {
	unsigned short int blue : 5;
	unsigned short int green : 5;
	unsigned short int red : 5;
	unsigned short int reserved : 1;
};

struct pixel8 {
	unsigned char colorNumber;
};

struct pixel4 {
	unsigned char colorNumber : 4;
	unsigned char reserved : 4;
};

struct pixel2 {
	unsigned char colorNumber : 2;
	unsigned char reserved : 6;
};

struct pixel1 {
	unsigned char colorNumber : 1;
	unsigned char reserved : 7;
};

#pragma pack(pop)

bool pixelArrayNegative(void* pixelArray, int bitCount, int SizeImage);
bool pixelArrayGrayscale(void* pixelArray, int bitCount, int SizeImage);
bool MedianFilter(void* pixelArray, int windowSize, int bitCount, int imageWidth, int imageHeight);
bool pixelArrayGammaCorrection(void* pixelArray, int bitCount, int SizeImage, double y);
bool colorTableGammaCorrection(void* colorArray, int clrUsed, int BMPVersion, double y);
bool colorTableNegative(void* colorArray, int clrUsed, int BMPVersion);
bool colorTableGrayscale(void* colorArray, int clrUsed, int BMPVersion);
BITMAPFILEHEADER* readBITMAPFILEHEADER(FILE* source);
unsigned long int readBMPVertion(FILE* source);
unsigned long int getSizeImage(BITMAPV5HEADER* info);
unsigned long int getClrUsed(BITMAPV5HEADER* info);
void* readInBITMAPV5HEADER(FILE* source);
void* readPixelMatrix(FILE* source, int bfOffBits, unsigned long int sizeImage, unsigned short int bitCount);
void* readColorTable(FILE* source, unsigned long int clrUsed, unsigned short int BMPVertion);
void writeBMP(BITMAPFILEHEADER* BMPHeader, BITMAPV5HEADER* BMPInfo, void* pixelArray, FILE* destination, void* colorTable);
