#pragma once

#include <stdlib.h>

#define BUFF 128

struct node {
	char key[BUFF];
	node* negative;
	node* positive;
};

struct unit {
	int level;
	char key[BUFF];
};

node* createNode(char* key);
node* extractNode(node* &leaf);
int saveTree(node* &tree, int level, FILE* destination);
void loadTree(node* &root, int level, unit* source);
node* &findNode(node* &tree);
