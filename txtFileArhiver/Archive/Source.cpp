#include <stdio.h>
#include <stdlib.h>
#include "LineFunctions.h"
#include "FileFunctions.h"

#define KEY_NAME "_key.txt"
#define ARCHIVE_NAME "_archive.txt"
//d:/test.txt
void endProgram(char*&path, char*&pathWithoutType, FILE*&source, FILE*&key, FILE*&archiveFile, line &wordsLine);

int main() {
	char *path, *pathWithoutType;
	FILE* source;
	puts("Enter file path.");
	do {
		rewind(stdin);
		getPath(path, pathWithoutType);
		source = fopen(path, "r");
		if (!source) {
			system("cls");
			puts("File doesn't exist. Try another path.");
		}
	} while (!source);
	system("cls");
	line wordsLine = createLine();
	fillLineFromFile(wordsLine, source);
	createPairs(wordsLine);
	if (wordsLine.head->nextWord == nullptr) {
		puts("There are nothing to archivate in your file.");
		system("pause");
		return 0;
	}
	FILE* key = pathFopen(pathWithoutType, KEY_NAME, "w");
	FILE* archive = pathFopen(pathWithoutType, ARCHIVE_NAME, "w");
	archiveFile(archive, source, wordsLine);
	keyFilling(key, wordsLine);
	endProgram(path, pathWithoutType, source, key, archive, wordsLine);
	return 0;
}

void endProgram(char*&path, char*&pathWithoutType, FILE*&source, FILE*&key, FILE*&archiveFile, line &wordsLine) {
	free(pathWithoutType);
	pathWithoutType = nullptr;
	free(path);
	path = nullptr;
	fclose(source);
	source = nullptr;
	fclose(key);
	key = nullptr;
	fclose(archiveFile);
	archiveFile = nullptr;
	destroyLine(wordsLine);
}