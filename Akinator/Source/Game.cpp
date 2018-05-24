#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Tree.h"
#include "Game.h"

void outputRules() {
	puts("������� ���� ����� ������. �� ����������� ����� � ��������� �� ��� �������, � � � ���� ������� ������ ��� �����");
	puts("�������� (�� ��� �� ����).");
	puts("������ � ��������������� �� �������������, �� �� ������ �������� ������ ��� ������. ���� � ����� �� ������,");
	puts("�� �� ������ ������ ������ ��� ������ ���-�� �����. ������� ����!");
	puts("\n1.�������!");
	while (getch() != '1');
	system("cls");
	return;
}

void loadDefaultInfo(node* &root) {
	unit defaultTreeInfo[DEFAULT_TREE_ELEMENT_NUMBER] = DEFAULT_TREE;
	loadTree(root, 0, defaultTreeInfo);
}

void saveInfo(node* &tree, FILE* destination) {
	assert(destination);
	fseek(destination, sizeof(int), SEEK_SET);
	int size = saveTree(tree, 0, destination);
	fseek(destination, 0, SEEK_SET);
	fwrite(&size, sizeof(int), 1, destination);
	return;
}

void loadInfo(node* &root, FILE* source) {
	assert(source);
	int size;
	fread(&size, sizeof(int), 1, source);
	unit* treeInfo = (unit*) malloc(size * sizeof(unit));
	if (fread(treeInfo, sizeof(unit), size, source) != size) {
		return;
	}
	loadTree(root, 0, treeInfo);
}

node* &askQuestions(node* &tree) {
	assert(tree);
	if (!tree->positive && !tree->negative) {
		printf("��� %s?\n", tree->key);
	} else {
		puts(tree->key);
	}
	puts("1. ��");
	puts("2. ���");
	while (true) {
		switch (getch()) {
		case '1':
			system("cls");
			if (!tree->positive && !tree->negative) {
				return tree->positive;
			}
			return askQuestions(tree->positive);
		case '2':
			system("cls");
			if (!tree->positive && !tree->negative) {
				return tree;
			}
			return askQuestions(tree->negative);
		}
	}
}

bool playAgain() {
	puts("������ ������� ��� ���?");
	puts("1. ��");
	puts("2. ���");
	while (true) {
		switch (getch()) {
		case '1':
			system("cls");
			return true;
		case '2':
			system("cls");
			return false;
		}
	}
}

bool lose() {
	puts("������, �� �������! �� �� ������ ������ ��� ����� �����. ������ �����, ��� ��� �� ����� � ��� ��� ��������,");
	puts("� � ��������� ��� � ����������� ��� �������.");
	puts("1. ����������� � ���� �����!");
	puts("2. �� �� ���, ������ � ����� ����� �����!");
	while (true) {
		switch (getch()) {
		case '1':
			system("cls");
			return true;
		case '2':
			system("cls");
			return false;
		}
	}
}

void addAnswer(node* &leaf) {
	assert(leaf);
	puts("����, ���������� ����� ���...");
	char answer[BUFF];
	gets_s(answer, BUFF);
	system("cls");
	printf("����� ������, ��� ��� %s, ���� �������� \"��\" �� ������:\n", answer);
	char question[BUFF];
	gets_s(question, BUFF);
	system("cls");
	node* oldLeaf = extractNode(leaf);
	leaf = createNode(question);
	if (!leaf) {
		puts("������ ��� ���������� ������.");
		return;
	}
	leaf->positive = createNode(answer);
	if (!leaf) {
		puts("������ ��� ���������� ������.");
		return;
	}
	leaf->negative = oldLeaf;
}

void playGame(node* tree) {
	while (true) {
		node* &leaf = askQuestions(tree);
		if (!leaf) {
			puts("� �������! ���, � ������, �� �����������.");
		} else {
			if (lose()) {
				addAnswer(leaf);
			}
		}
		if (!playAgain()) {
			return;
		}
	}
}

void editKey(node* tree) {
	node* &node = findNode(tree);
	if (!node) {
		return;
	}
	printf("�� ��� ����� ��������\n\"%s\"?\n", node->key);
	char newKey[BUFF];
	gets_s(newKey, BUFF);
	strcpy(node->key, newKey);
	system("cls");
}

void menu(node* tree) {
	puts("������! ��� ����, ����� ������ ������, ������� 1.");
	while (true) {
		puts("1. ������.");
		puts("2. �������.");
		puts("3. ������������� ������.");
		puts("0. �����.");
		char i = getch();
		system("cls");
		switch (i) {
		case '1':
			playGame(tree);
			break;
		case '2':
			outputRules();
			break;
		case '3':
			editKey(tree);
			break;
		case '0':
			return;
		}
	}
}