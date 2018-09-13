#include <stdio.h>
#include <stdlib.h>
#include "FileFunctions.h"

#define KEY_NAME "_key.txt"
#define DEARCHIVE_NAME "_dearchive.txt"
//d:/test_archive.txt
void endProgram(char* &path, char* &pathWithoutType, FILE* &source, FILE* &key, FILE* &dearchiveFile);

int main(void) {
	char* path, *pathWithountType;
	FILE* source;
	FILE* key;
	puts("Enter file path.");
	do {
		rewind(stdin);
		getPath(path, pathWithountType);
		source = pathFopen(path, "", "r");
		key = pathFopen(pathWithountType, KEY_NAME,"r");
		if (!key || !source) {
			system("cls");
			puts("Key or source file doesn't exist. Dearchiving is inmpossible. Try again.");
		}
	} while (!key || !source);
	system("cls");
	FILE* dearchiveFile = pathFopen(pathWithountType, DEARCHIVE_NAME, "w");
	dearchiving(dearchiveFile, source, key);
	endProgram(path, pathWithountType, source, key, dearchiveFile);
	return 0;
}

void endProgram(char*&path, char* &pathWithountType, FILE*&source, FILE*&key, FILE*&dearchiveFile) {
	free(path);
	path = nullptr;
	free(pathWithountType);
	pathWithountType = nullptr;
	fclose(source);
	source = nullptr;
	fclose(key);
	key = nullptr;
	fclose(dearchiveFile);
	dearchiveFile = nullptr;
}