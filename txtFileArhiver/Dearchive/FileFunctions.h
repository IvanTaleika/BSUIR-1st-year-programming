#pragma once

FILE* pathFopen(char*path, char*name, char*type);
void dearchiving(FILE* destination, FILE* source, FILE* key);
void getPath(char*&path, char*&pathWithoutType);