#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "ListsChanging.h"
#include "Sorting.h"
#include "Notebooks.h"

void info(notebook&notebook){
	printf("�������� �������������: %s\n", notebook.brand);
	printf("�������� ������: %s\n", notebook.model);
	printf("Ƹ����� ����: %d GB\n", notebook.storage);
	printf("����� ����������� ������: %d GB\n", notebook.memory);
	printf("������ ������: %.1f\" \n", notebook.displaySize);
	printf("���� �������: %s\n", notebook.noteColor);
	printf("���� (���): %d\n", notebook.price);
	printf("������ �� �������: %s\n", notebook.link);
}

void popular(notebook* popularNotebooks, noteList&favoriteNotebooks){
	while (true){
		system("cls");
		for (int i = 0; i < POPULAR; i++){
			info(popularNotebooks[i]);
			puts("");
		}
		puts("1.�������� � ���������.");
		puts("0.� ����.");
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
			puts("����� ����� ������������ ������������� ���, � ����� ����������� ���� ������ ��������.");
			puts("\n0.� ����.");
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
			puts("1.�����������.");
			puts("2.������� ������.");
			puts("0.� ����.");
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
		puts("1.����������.");
		puts("2.�������� ������.");
		puts("3.���������.");
		puts("\n0.�����.");
		switch (getch()){
		case '1':
			system("cls");
			if (popularNotebooks){
				popular(popularNotebooks, favoriteNotebooks);
			} else {
				puts("��������� ����� �� ����������.");
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