#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include "Tree.h"

node* createNode(char* key) {
	assert(key);
	node* newNode = (node*) malloc(sizeof(node));
	if (!newNode) {
		return nullptr;
	}
	strcpy(newNode->key, key);
	newNode->negative = newNode->positive = nullptr;
	return newNode;
}

node* extractNode(node* &leaf) {
	node* newNode = leaf;
	leaf = nullptr;
	return newNode;
}

node* &findNode(node* &tree) {
	if (!tree) {
		return tree;
	}
	puts(tree->key);
	puts("1. Да");
	puts("2. Нет");
	puts("3. Исправить.");
	while (true) {
		switch (getch()) {
		case '1':
			system("cls");
			return findNode(tree->positive);
		case '2':
			system("cls");
			return findNode(tree->negative);
		case '3':
			system("cls");
			return tree;
		}
	}
}

int saveTree(node* &tree, int level, FILE* destination) {
	assert(destination || tree);
	if (!tree) {
		return 0;
	}
	fwrite(&level, sizeof(int), 1, destination);
	fwrite(tree->key, BUFF, 1, destination);
	int count = saveTree(tree->negative, level + 1, destination);
	count += saveTree(tree->positive, level + 1, destination);
	return count + 1;
}

void loadTree(node* &root, int level, unit* source) {
	assert(source);
	static int counter = 0;
	if (source[counter].level < level) {
		return;
	}
	root = createNode(source[counter].key);
	counter++;
	loadTree(root->negative, level + 1, source);
	loadTree(root->positive, level + 1, source);
}