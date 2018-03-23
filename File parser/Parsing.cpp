#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Notebooks.h"

char* sringFinding(FILE* source, char* expression, int sizeOfExpression, char symbol){
	char *p1, *p2;
	char buff[STRINGSIZE];
	do{
		fgets(buff, STRINGSIZE, source);
		p1 = strstr(buff, expression);
	} while (!p1);
	p1 = p1 + sizeOfExpression;
	p2 = p1;
	int size = 0;
	while (*p2 != symbol){
		size++;
		p2++;
	}
	char* str = (char*)malloc(size+1*sizeof(char));
	int i = 0;
	while(i < size){
		str[i] = p1[i];
		i++;
	}
	str[i] = 0;
	return str;
}

void priceParse(int&price, char* str){
	price = atoi(str);
	free(str);
}

void linkParse(char* link, char* str){
	strcpy(link, str);
	link[strlen(str)] = 0;
	free(str);
}

void nameParse(char* brand, char* model, char* str){
	int i = 0;
	while (str[i] != ' ' && i < BUFFSIZE){
		brand[i] = str[i];
		i++;
	}
	brand[i] = 0;
	i++;
	int j = 0;
	while (str[i] && i < BUFFSIZE){
		model[j] = str[i];
		i++;
		j++;
	}
	model[j] = 0;
	free(str);
}

void descriptionParce(float&displaySize, int&memory, int&storage, char* noteColor, char* str){
	displaySize = atof(str);
	char* p = strstr(str, "ГБ");
	while (*p != ','){
		p--;
	}
	p++;
	memory = atoi(p);
	while (*p != ','){
		p++;
	}
	p++;
	storage = atoi(p);
	p = strstr(str, "цвет корпуса");
	p = p + sizeof("цвет корпуса");
	int i = 0;
	while (p[i] && i < BUFFSIZE){
		noteColor[i] = p[i];
		i++;
	}
	noteColor[i] = 0;
	free(str);
}