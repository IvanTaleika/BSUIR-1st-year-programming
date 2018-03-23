#pragma once
#include "Notebooks.h"
#include <stdio.h>
char* sringFinding(FILE* source, char* expression, int sizeOfExpression, char symbol);
void priceParse(int&price, char* str);
void linkParse(char* link, char* str);
void nameParse(char* brand, char* model, char* str);
void descriptionParce(float&displaySize, int&memory, int&storage, char* noteColor, char* str);