#include "LineFunctions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define BUFF 256

line createLine() {
	line myLine;
	wordUnit* temp = (wordUnit*) malloc(sizeof(wordUnit));
	myLine.head = temp;
	myLine.tail = temp;
	temp->nextWord = nullptr;
	temp->info.word = nullptr;
	return myLine;
}

void fillLineFromFile(line &destination, FILE* source) {
	char buff[BUFF];
	int temp;
	wordUnit* p;
	while (true) {
		temp = fscanf(source, "%s", buff);
		if (temp != 1) {
			break;
		}
		p = shearchWord(destination, buff);
		if (p) {
			p->info.wordAmount++;
		} else {
			addWord(destination, buff);
		}
	}
	rewind(source);
}

void addWord(line& source, char* buff) {
	wordUnit* newWord = (wordUnit*) malloc(sizeof(wordUnit));
	if (!newWord) {
		puts("Memory error.");
		system("pause");
		abort();
	}
	addToTail(source, newWord);
	newWord->info.wordAmount = 1;
	newWord->info.wordSize = strlen(buff);
	newWord->info.word = (char*) malloc((newWord->info.wordSize+1) * sizeof(char));
	strcpy(newWord->info.word, buff);
}

void addToTail(line &source, wordUnit* element) {
	element->nextWord = nullptr;
	source.tail->nextWord = element;
	source.tail = element;
}

wordUnit* shearchWord(line wordsLine, char* buff) {
	for (wordUnit* p = wordsLine.head->nextWord; p != nullptr; p = p->nextWord) {
		if (!strcmp(p->info.word, buff)) {
			return p;
		}
	}
	return 0;
}

wordUnit* getMaxIterator(line source) {
	assert(source.head->nextWord != nullptr);
	wordUnit* iterator = source.head;
	for (wordUnit* p = source.head->nextWord; p->nextWord != nullptr; p = p->nextWord) {
		if (p->nextWord->info.wordAmount*p->nextWord->info.wordSize > iterator->nextWord->info.wordAmount*iterator->nextWord->info.wordSize) {
			iterator = p;
		}
	}
	return iterator;
}

wordUnit* getChangeIterator(line source, wordInfo compareInfo) {
	assert(source.head->nextWord != nullptr);
	wordUnit* iterator = nullptr;
	int temp = 2 * compareInfo.wordAmount * compareInfo.wordSize;
	for (wordUnit* p = source.head; p->nextWord != nullptr; p = p->nextWord) {
		if (compareInfo.wordSize * p->nextWord->info.wordAmount + compareInfo.wordAmount * p->nextWord->info.wordSize <
			compareInfo.wordAmount * compareInfo.wordSize + p->nextWord->info.wordAmount * p->nextWord->info.wordSize &&
			compareInfo.wordSize * p->nextWord->info.wordAmount + compareInfo.wordAmount * p->nextWord->info.wordSize < temp) {
			iterator = p;
			temp = compareInfo.wordSize * p->nextWord->info.wordAmount + compareInfo.wordAmount * p->nextWord->info.wordSize;
		}
	}
	return iterator;
}


wordUnit* extractWordUnit(line &source, wordUnit* iterator) {
	wordUnit* unit = iterator->nextWord;
	iterator->nextWord = unit->nextWord;
	unit->nextWord = nullptr;
	if (unit == source.tail) {
		source.tail = iterator;
	}
	return unit;
}

void createPairs(line&source) {
	line temp = createLine();
	while (source.head != source.tail) {
		wordUnit* iterator = getMaxIterator(source);
		wordUnit* element = extractWordUnit(source, iterator);
		if (element->info.wordAmount == 1) {
			destroyUnit(element);
			continue;
		}
		if (source.head == source.tail) {
			break;
		}
		iterator = getChangeIterator(source, element->info);
		if (iterator) {
			wordUnit *change = extractWordUnit(source, iterator);
			addToTail(temp, element);
			addToTail(temp, change);
		} else {
			destroyUnit(element);
		}
	}
	destroyLine(source);
	source = temp;
}

void destroyUnit(wordUnit* &source) {
	free(source->info.word);
	source->info.word = nullptr;
	free(source);
	source = nullptr;
}

void destroyLine(line &source) {
	while (source.head != nullptr) {
		wordUnit* structPointer = source.head;
		source.head = source.head->nextWord;
		destroyUnit(structPointer);
	}
	source.tail = nullptr;
}