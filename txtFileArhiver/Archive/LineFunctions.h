#pragma once
#include <stdio.h>

struct wordInfo {
	char* word;
	int wordSize;
	int wordAmount;
};

struct wordUnit {
	wordInfo info;
	wordUnit *nextWord;
};

struct line {
	wordUnit *head;
	wordUnit *tail;
};

line createLine();
void addToTail(line &source, wordUnit* element);
wordUnit* shearchWord(line wordsLine, char* buff);
void addWord(line& source, char* buff);
void fillLineFromFile(line &destination, FILE* source);
wordUnit* getMaxIterator(line source);
wordUnit* extractWordUnit(line &source, wordUnit* iterator);
wordUnit* getChangeIterator(line source, wordInfo compareInfo);
void createPairs(line&source);
void destroyLine(line &source);
void destroyUnit(wordUnit* &source);