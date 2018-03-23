#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "ListsChanging.h"
#include "Sorting.h"
#include "Notebooks.h"

void info(notebook&notebook){
	printf("Компания производителя: %s\n", notebook.brand);
	printf("Название модели: %s\n", notebook.model);
	printf("Жёсткий диск: %d GB\n", notebook.storage);
	printf("Объём оперативной памяти: %d GB\n", notebook.memory);
	printf("Размер экрана: %.1f\" \n", notebook.displaySize);
	printf("Цвет корпуса: %s\n", notebook.noteColor);
	printf("Цена (РУБ): %d\n", notebook.price);
	printf("Ссылка на продукт: %s\n", notebook.link);
}

void popular(notebook* popularNotebooks, noteList&favoriteNotebooks){
	while (true){
		system("cls");
		for (int i = 0; i < POPULAR; i++){
			info(popularNotebooks[i]);
			puts("");
		}
		puts("1.Добавить в избранное.");
		puts("0.В меню.");
		switch (getch()){
		case '1':
			system("cls");
			cashing(popularNotebooks, favoriteNotebooks);
			break;
		case '0':
			system("cls");
			return;
		}
	}
}

void favorite(notebook* popularNotebooks, noteList&favoriteNotebooks){
	while (true){
		if (!favoriteNotebooks.size){
			puts("Здесь будут отображаться понравившиеся вам, а также добавленные вами модели ноубуков.");
			puts("\n0.В меню.");
			while (true){
				if (getch() == '0'){
					system("cls");
					return;
				}
			}
		}
		else {
			system("cls");
			for (int i = 0; i < favoriteNotebooks.size; i++){
				info(favoriteNotebooks.list[i]);
				puts("");
			}
			puts("1.Сортировать.");
			puts("2.Удалить модель.");
			puts("0.В меню.");
			switch (getch()){
			case '1':
				system("cls");
				sorting(favoriteNotebooks);
				break;
			case '2':{
				int number = deleteChoosing(favoriteNotebooks);
				if (number >= 0){
					unselect(favoriteNotebooks.list[number].link, popularNotebooks);
					deleting(favoriteNotebooks, number);
				}
				system("cls");
				break;
			}
			case '0':
				system("cls");
				return;
			}
		}
	}
}

void menu(notebook* popularNotebooks, noteList&favoriteNotebooks){
	while (true){
		puts("1.Популярное.");
		puts("2.Добавить модель.");
		puts("3.Избранное.");
		puts("\n0.Выход.");
		switch (getch()){
		case '1':
			system("cls");
			if (popularNotebooks){
				popular(popularNotebooks, favoriteNotebooks);
			} else {
				puts("Исходного файла не существует.");
			}
			break;
		case '2':
			system("cls");
			additing(favoriteNotebooks);
			myNoteFilling(favoriteNotebooks.list[0]);
			break;
		case '3':
			system("cls");
			favorite(popularNotebooks,favoriteNotebooks);
			break;
		case '0':
			return;
		default:
			system("cls");
			break;
		}
	}
}