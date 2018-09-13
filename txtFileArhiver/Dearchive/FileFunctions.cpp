#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF 256

void getPath(char*&path, char*&pathWithoutType) {
	path = (char*) malloc(BUFF * sizeof(char));
	char *stop;
	do {
		rewind(stdin);
		gets_s(path, BUFF);
		stop = strstr(path, "_archive.txt");
		if (!stop) {
			system("cls");
			puts("This is not a archive file. Try again.");
		}
	} while (!stop);
	system("cls");
	pathWithoutType = (char*) calloc(strlen(path) - strlen(stop) + 1, sizeof(char));
	strncpy(pathWithoutType, path, strlen(path) - strlen(stop));
}

FILE* pathFopen(char*path, char*name, char*type) {
	char temp[BUFF];
	strcpy(temp, path);
	strcat(temp, name);
	FILE* file = fopen(temp, type);
	return file;
}

void dearchiving(FILE* destination, FILE* source, FILE* key) {
	char buff[BUFF];
	char keyWord[BUFF];
	char lastKeyWord[BUFF];
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
		while (true) {
			fscanf(key, "%s", keyWord);
			if (feof(key)) {
				break;
			}
			if (!strcmp(buff, keyWord)) {
				if (counter % 2 == 0) {
					fscanf(key, "%s", keyWord);
					fprintf(destination, "%s", keyWord);
				} else {
					fprintf(destination, "%s", lastKeyWord);
				}
				change = true;
				break;
			}
			strcpy(lastKeyWord, keyWord);
			counter++;
		}
		rewind(key);
		if (!change) {
			fprintf(destination, "%s", buff);
		}
	}
	rewind(destination);
}