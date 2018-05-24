#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Tree.h"
#include "Game.h"

void outputRules() {
	puts("Правила игры очень просты. Ты загадываешь слово и отвечаешь на мои вопросы, а я в свою очередь обещаю твоё слово");
	puts("отгадать (но это не точо).");
	puts("Вообще я специализируюсь на знаменитостях, но ты можешь загадать вообще что угодно. Если я вдруг не угадаю,");
	puts("то ты всегда можешь помочь мне узнать что-то новое. Удачной игры!");
	puts("\n1.Понятно!");
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
		printf("Это %s?\n", tree->key);
	} else {
		puts(tree->key);
	}
	puts("1. Да");
	puts("2. Нет");
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
	puts("Хочешь сыграть ещё раз?");
	puts("1. Да");
	puts("2. Нет");
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
	puts("Сдаюсь, ты выиграл! Но ты можешь помочь мне стать лучше. Просто скажи, что это за слово и как его отличить,");
	puts("и в следующий раз я обязательно его отгадаю.");
	puts("1. Естественно я тебя научу!");
	puts("2. Ну уж нет, теперь я здесь самый умный!");
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
	puts("Итак, правильный ответ был...");
	char answer[BUFF];
	gets_s(answer, BUFF);
	system("cls");
	printf("Чтобы понять, что это %s, надо ответить \"да\" на впорос:\n", answer);
	char question[BUFF];
	gets_s(question, BUFF);
	system("cls");
	node* oldLeaf = extractNode(leaf);
	leaf = createNode(question);
	if (!leaf) {
		puts("Ошибка при добавлении ответа.");
		return;
	}
	leaf->positive = createNode(answer);
	if (!leaf) {
		puts("Ошибка при добавлении ответа.");
		return;
	}
	leaf->negative = oldLeaf;
}

void playGame(node* tree) {
	while (true) {
		node* &leaf = askQuestions(tree);
		if (!leaf) {
			puts("Я победил! Что, в прочем, не удивительно.");
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
	printf("На что нужно поменять\n\"%s\"?\n", node->key);
	char newKey[BUFF];
	gets_s(newKey, BUFF);
	strcpy(node->key, newKey);
	system("cls");
}

void menu(node* tree) {
	puts("Привет! Для того, чтобы начать играть, нажимай 1.");
	while (true) {
		puts("1. Играть.");
		puts("2. Правила.");
		puts("3. Редактировать вопрос.");
		puts("0. Выход.");
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