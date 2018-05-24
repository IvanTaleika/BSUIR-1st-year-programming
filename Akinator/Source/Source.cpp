#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <assert.h>
#include "Tree.h"
#include "Game.h"

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	node* root = nullptr;
	FILE* source = fopen(DATA_FILE_NAME, "r+b");
	if (!source) {
		loadDefaultInfo(root);
		if (!root) {
			puts("Ошибка при загрузке информации. Продолжение игры невозможно.");
			system("pause");
			return 1;
		}
	} else {
		loadInfo(root, source);
		if (!root) {
			puts("Ошибка при загрузке информации. Продолжение игры невозможно.");
			system("pause");
			return 1;
		}
	}
	menu(root);
	FILE* dest = fopen(DATA_FILE_NAME, "wb");
	saveInfo(root, dest);
	return 0;
}