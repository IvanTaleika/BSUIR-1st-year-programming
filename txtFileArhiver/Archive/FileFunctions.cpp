#include "LineFunctions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF 256

FILE* pathFopen(char*path, char*name, char*type) {
	char temp[BUFF];
	strcpy(temp, path);
	strcat(temp, name);
	FILE* file = fopen(temp, type);
	return file;
}

void getPath(char*&path, char*&pathWithoutType) {
	path = (char*) malloc(BUFF * sizeof(char));
	char * stop;
	do {
		rewind(stdin);
		gets_s(path, BUFF);
		stop = strstr(path, ".txt");
		if (!stop) {
			system("cls");
			puts("Unavailable file type. Try again.");
		}
	} while (!stop);
	system("cls");
	pathWithoutType = (char*) calloc(strlen(path) - strlen(stop)+1 , sizeof(char));
	strncpy(pathWithoutType, path, strlen(path) - strlen(stop));
}

void keyFilling(FILE* destination, line &source) {
	for (wordUnit* p = source.head->nextWord; p != nullptr; p = p->nextWord) {
		fprintf(destination, "%s ", p->info.word);
	}
	rewind(destination);
}

void archiveFile(FILE* destination, FILE* source, line key) {
	char buff[BUFF];
	int counter;
	rewind(source);
	while (true) {
		fread(buff, 1, 1, source);
		while (strpbrk(buff, " \n\t")) {
			if (feof(source)) {
				break;
			}
			fwrite(buff, 1, 1, destination);
			fread(buff, 1, 1, source);
		}
		if (feof(source)) {
			break;
		}
		fseek(source, -1, SEEK_CUR);
		fscanf(source, "%s", buff);
		counter = 0;
		bool change = false;
		for (wordUnit* p = key.head; p->nextWord != nullptr; p = p->nextWord) {
			if (!strcmp(buff, p->nextWord->info.word)) {
				if (counter % 2 == 0) {
					fprintf(destination, "%s", p->nextWord->nextWord->info.word);
				} else {
					fprintf(destination, "%s", p->info.word);
				}
				change = true;
				break;
			}
			counter++;
		}
		if (!change) {
			fprintf(destination, "%s", buff);
		}			
	}
	rewind(destination);
}
