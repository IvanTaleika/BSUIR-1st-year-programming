#pragma once

#include <stdio.h>
#include "LineFunctions.h"
FILE* pathFopen(char*path, char*name, char*type);
void getPath(char*&path, char*&pathWithoutType);
void keyFilling(FILE* destination, line &source);
void archiveFile(FILE* destination, FILE* source, line key);