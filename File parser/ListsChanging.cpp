#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "Parsing.h"
#include "Notebooks.h"

void myNoteFilling(notebook&newNotebook){
	fflush(stdin);
	int check;
	puts("Компаня производитель:");
	gets(newNotebook.brand);
	system("CLS");
	puts("Название модели:");
	gets(newNotebook.model);
	system("CLS");
	do{
		puts("Объём оперативной памяти (GB):");
		fflush(stdin);
		check = scanf("%d", &newNotebook.memory);
		system("cls");
	} while (!check);
	do{
		puts("Объём жёсткого диска (GB):");
		fflush(stdin);
		check = scanf("%d", &newNotebook.storage);
		system("cls");
	} while (!check);
	do{
		puts("Диагональ экрана (дюймы):");
		fflush(stdin);
		check = scanf("%f", &newNotebook.displaySize);
		system("cls");
	} while (!check);
	do{
		puts("Цена продукта (РУБ):");
		fflush(stdin);
		check = scanf("%d", &newNotebook.price);
		system("cls");
	} while (!check);
	puts("Цвет ноутбука:");
	puts("1.Серебристый.");
	puts("2.Чёрный.");
	puts("3.Белый.");
	puts("4.Красный.");
	puts("5.Золотистый.");
	puts("6.Серый.");
	puts("7.Розовый.");
	puts("8.Синий.");
	puts("9.Другой цвет.");
	switch (getch()){
	case '1':
		strcpy(newNotebook.noteColor, "серебристый");
		newNotebook.colors = SILVER;
		break;
	case '2':
		strcpy(newNotebook.noteColor, "черный");
		newNotebook.colors = BLACK;
		break;
	case '3':
		strcpy(newNotebook.noteColor, "белый");
		newNotebook.colors = WHITE;
		break;
	case '4':
		strcpy(newNotebook.noteColor, "красный");
		newNotebook.colors = RED;
		break;
	case '5':
		strcpy(newNotebook.noteColor, "золотистый");
		newNotebook.colors = GOLD;
		break;
	case '6':
		strcpy(newNotebook.noteColor, "желтый");
		newNotebook.colors = GRAY;
		break;
	case '7':
		strcpy(newNotebook.noteColor, "розовый");
		newNotebook.colors = PINK;
		break;
	case '8':
		strcpy(newNotebook.noteColor, "синий");
		newNotebook.colors = BLUE;
		break;
	case '9':
		system("cls");
		fflush(stdin);
		puts("Цвет ноутбука:");
		gets(newNotebook.noteColor);
		newNotebook.colors = ELSE;
		break;
	}
	strcpy(newNotebook.link, "Мой ноутбук");
	newNotebook.selected = true;
	system("CLS");
}

void additing(noteList&list){
	list.size++;
	notebook* newList = (notebook*)malloc(list.size*sizeof(notebook));
	if (newList == nullptr){
		puts("Ошибка выделения памяти");
		return;
	}
	for (int i = 0; i < list.size - 1; i++){
		newList[i + 1] = list.list[i];
	}
	if (list.list){
		free(list.list);
	}
	list.list = newList;
}

void cashing(notebook* popularNotebooks, noteList&favoriteNotebooks){
	int number, check;
	do{
		puts("Введите порядковый номер модели, которую вы хотите добавить в избранное. Для выхода введите 0.\n");
		for (int i = 1; i < POPULAR + 1 ; i++){
			if (!popularNotebooks[i - 1].selected){
				printf("%d. %s %s.\n", i, popularNotebooks[i - 1].brand, popularNotebooks[i - 1].model);
			}
		}
		fflush(stdin);
		check = scanf("%d", &number);
		system("cls");
		if (check && number > 0 && number < POPULAR + 1 && !popularNotebooks[number - 1].selected){
			additing(favoriteNotebooks);
			popularNotebooks[number - 1].selected = true;
			favoriteNotebooks.list[0] = popularNotebooks[number - 1];
			puts("Модель добавлена в избранное.");
		}
	} while (number);
}

int deleteChoosing(noteList&list){
	int number, check;
	do{
		system("cls");
		puts("Введите порядковый номер модели, которую вы хотите удалить. Для выхода введите 0.\n");
		for (int i = 1; i < list.size + 1; i++){
			printf("%d. %s %s.\n", i, list.list[i - 1].brand, list.list[i - 1].model);
		}
		fflush(stdin);
		check = scanf("%d", &number);
	} while (!check || number<0 || number>list.size);
	return number - 1;
}

void unselect(char* link, notebook* popularNotebooks){
	if (link != "Мой ноутбук"){
		for (int i = 0; i < POPULAR; i++){
			if (!strcmp(link,popularNotebooks[i].link)){
				popularNotebooks[i].selected = false;
				break;
			}
		}
	}
}

void deleting(noteList&list, int number){
	list.size--;
	notebook* newList = (notebook*)malloc(list.size*sizeof(notebook));
	if (newList == nullptr){
		puts("Ошибка выделения памяти");
		return;
	}
	for (int i = 0, j = 0; i < list.size + 1; i++, j++){
		if (i == number){
			j--;
			continue;
		}
		newList[j] = list.list[i];
	}
	if (list.list){
		free(list.list);
	}
	list.list = newList;
}

void colorCompare(notebook&note){
	if (!strcmp(note.noteColor, "серебристый")){
		note.colors = SILVER;
		return;
	}
	if (!strcmp(note.noteColor, "черный")){
		note.colors = BLACK;
		return;
	}
	if (!strcmp(note.noteColor, "белый")){
		note.colors = WHITE;
		return;
	}
	if (!strcmp(note.noteColor, "красный")){
		note.colors = RED;
		return;
	}
	if (!strcmp(note.noteColor, "золотистый")){
		note.colors = GOLD;
		return;
	}
	if (!strcmp(note.noteColor, "розовый")){
		note.colors = PINK;
		return;
	}
	if (!strcmp(note.noteColor, "серый")){
		note.colors = GRAY;
		return;
	}
	if (!strcmp(note.noteColor, "синий")){
		note.colors = BLUE;
		return;
	}
	note.colors = ELSE;
	return;
}

void popularFilling(notebook *note, FILE *site){
	char *str;
	for (int number = 0; number < POPULAR; number++){
		str = sringFinding(site, LINK, sizeof(LINK) - 1, '"');
		linkParse(note[number].link, str);
		str = sringFinding(site, PRICE, sizeof(PRICE) - 1, '&');
		priceParse(note[number].price, str);
		str = sringFinding(site, NAME, sizeof(NAME) - 1, '<');
		nameParse(note[number].brand, note[number].model, str);
		str = sringFinding(site, DESCRIPTION, sizeof(DESCRIPTION) - 1, '<');
		descriptionParce(note[number].displaySize, note[number].memory, note[number].storage, note[number].noteColor, str);
		colorCompare(note[number]);
		note[number].selected = false;
	}
}

void creating(notebook*&onlinerPopularNotebooks, FILE*&site, noteList&favoriteNotebooks){
	site = fopen(FILENAME, "r");
	if (site == nullptr){
		puts("Исходного файла не существует. Список популярных ноутбуков не будет создан.");
	}
	else{
		onlinerPopularNotebooks = (notebook*)malloc(POPULAR*sizeof(notebook));
		popularFilling(onlinerPopularNotebooks, site);
	}
	favoriteNotebooks.list = nullptr;
	favoriteNotebooks.size = 0;
}

void ending(notebook*&onlinerPopularNotebooks, FILE*&site, noteList&favoriteNotebooks){
	free(favoriteNotebooks.list);
	favoriteNotebooks.size = 0;
	favoriteNotebooks.list = nullptr;
	free(onlinerPopularNotebooks);
	onlinerPopularNotebooks = nullptr;
	if (site){
		fclose(site);
		site = nullptr;
	}
}