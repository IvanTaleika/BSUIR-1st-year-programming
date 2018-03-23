#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "Parsing.h"
#include "Notebooks.h"

void myNoteFilling(notebook&newNotebook){
	fflush(stdin);
	int check;
	puts("������� �������������:");
	gets(newNotebook.brand);
	system("CLS");
	puts("�������� ������:");
	gets(newNotebook.model);
	system("CLS");
	do{
		puts("����� ����������� ������ (GB):");
		fflush(stdin);
		check = scanf("%d", &newNotebook.memory);
		system("cls");
	} while (!check);
	do{
		puts("����� ������� ����� (GB):");
		fflush(stdin);
		check = scanf("%d", &newNotebook.storage);
		system("cls");
	} while (!check);
	do{
		puts("��������� ������ (�����):");
		fflush(stdin);
		check = scanf("%f", &newNotebook.displaySize);
		system("cls");
	} while (!check);
	do{
		puts("���� �������� (���):");
		fflush(stdin);
		check = scanf("%d", &newNotebook.price);
		system("cls");
	} while (!check);
	puts("���� ��������:");
	puts("1.�����������.");
	puts("2.׸����.");
	puts("3.�����.");
	puts("4.�������.");
	puts("5.����������.");
	puts("6.�����.");
	puts("7.�������.");
	puts("8.�����.");
	puts("9.������ ����.");
	switch (getch()){
	case '1':
		strcpy(newNotebook.noteColor, "�����������");
		newNotebook.colors = SILVER;
		break;
	case '2':
		strcpy(newNotebook.noteColor, "������");
		newNotebook.colors = BLACK;
		break;
	case '3':
		strcpy(newNotebook.noteColor, "�����");
		newNotebook.colors = WHITE;
		break;
	case '4':
		strcpy(newNotebook.noteColor, "�������");
		newNotebook.colors = RED;
		break;
	case '5':
		strcpy(newNotebook.noteColor, "����������");
		newNotebook.colors = GOLD;
		break;
	case '6':
		strcpy(newNotebook.noteColor, "������");
		newNotebook.colors = GRAY;
		break;
	case '7':
		strcpy(newNotebook.noteColor, "�������");
		newNotebook.colors = PINK;
		break;
	case '8':
		strcpy(newNotebook.noteColor, "�����");
		newNotebook.colors = BLUE;
		break;
	case '9':
		system("cls");
		fflush(stdin);
		puts("���� ��������:");
		gets(newNotebook.noteColor);
		newNotebook.colors = ELSE;
		break;
	}
	strcpy(newNotebook.link, "��� �������");
	newNotebook.selected = true;
	system("CLS");
}

void additing(noteList&list){
	list.size++;
	notebook* newList = (notebook*)malloc(list.size*sizeof(notebook));
	if (newList == nullptr){
		puts("������ ��������� ������");
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
		puts("������� ���������� ����� ������, ������� �� ������ �������� � ���������. ��� ������ ������� 0.\n");
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
			puts("������ ��������� � ���������.");
		}
	} while (number);
}

int deleteChoosing(noteList&list){
	int number, check;
	do{
		system("cls");
		puts("������� ���������� ����� ������, ������� �� ������ �������. ��� ������ ������� 0.\n");
		for (int i = 1; i < list.size + 1; i++){
			printf("%d. %s %s.\n", i, list.list[i - 1].brand, list.list[i - 1].model);
		}
		fflush(stdin);
		check = scanf("%d", &number);
	} while (!check || number<0 || number>list.size);
	return number - 1;
}

void unselect(char* link, notebook* popularNotebooks){
	if (link != "��� �������"){
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
		puts("������ ��������� ������");
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
	if (!strcmp(note.noteColor, "�����������")){
		note.colors = SILVER;
		return;
	}
	if (!strcmp(note.noteColor, "������")){
		note.colors = BLACK;
		return;
	}
	if (!strcmp(note.noteColor, "�����")){
		note.colors = WHITE;
		return;
	}
	if (!strcmp(note.noteColor, "�������")){
		note.colors = RED;
		return;
	}
	if (!strcmp(note.noteColor, "����������")){
		note.colors = GOLD;
		return;
	}
	if (!strcmp(note.noteColor, "�������")){
		note.colors = PINK;
		return;
	}
	if (!strcmp(note.noteColor, "�����")){
		note.colors = GRAY;
		return;
	}
	if (!strcmp(note.noteColor, "�����")){
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
		puts("��������� ����� �� ����������. ������ ���������� ��������� �� ����� ������.");
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