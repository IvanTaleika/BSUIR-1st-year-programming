#pragma once
#define BUFFSIZE 128
#define STRINGSIZE 1024
#define FILENAME "site.txt"
#define PRICE "'BYN')\">"
#define LINK "product.html_url}\" href=\""
#define NAME "product.full_name\">"
#define DESCRIPTION "product.description\">"
#define POPULAR 10

enum colorList{
	SILVER,
	BLACK,
	WHITE,
	RED,
	GOLD,
	PINK,
	GRAY,
	BLUE,
	ELSE
};

struct notebook{
	char brand[BUFFSIZE];
	char model[BUFFSIZE];
	int storage;
	int memory;
	int price;
	float displaySize;
	char noteColor[BUFFSIZE];
	colorList colors;
	char link[BUFFSIZE];
	bool selected;
};

struct noteList{
	notebook* list;
	int size;
};