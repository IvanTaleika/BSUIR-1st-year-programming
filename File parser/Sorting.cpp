#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "Menu.h"
#include "Notebooks.h"

void sortPointChoise(char* comparePoints){
	for (int i = 0; i < 2 && comparePoints[i] != 13; i++){
		puts("Сортировка по (до 2-ух эллементов):");
		if (comparePoints[0] != '1'){
			puts("1.Цене.");
		}
		if (comparePoints[0] != '2'){
			puts("2.Объёму оперативной памяти.");
		}
		if (comparePoints[0] != '3'){
			puts("3.Объёму жёсткого диска.");
		}
		if (comparePoints[0] != '4'){
			puts("4.Диагонали экрана.");
		}
		if (comparePoints[0] != '5'){
			puts("5.Цвету.");
		}
		if (comparePoints[0] == 0){
			puts("\n0. Назад.");
		}
		else{
			puts("\n0. Сортировать.");
		}
		do{
			comparePoints[i] = getch();
		} while ((comparePoints[i] < '1' || comparePoints[i] > '5' || comparePoints[0] == comparePoints[1]) && comparePoints[i] != '0');
		system("cls");
		if (comparePoints[0] == '0'){
			return;
		}
	}
}

int secondSorting(notebook note1, notebook note2, char comparePoint){
	switch (comparePoint){
	case '1':
		if (note1.price > note2.price){
			return 1;
		}
		else{
			return 0;
		}
	case '2':
		if (note1.memory > note2.memory){
			return 1;
		}
		else{
			return 0;
		}
	case '3':
		if (note1.storage > note2.storage){
			return 1;
		}
		else{
			return 0;
		}
	case '4':
		if (note1.displaySize > note2.displaySize){
			return 1;
		}
		else{
			return 0;
		}
	case '5':
		if (note1.colors > note2.colors){
			return 1;
		}
		else{
			return 0;
		}
	}
}

void sorting(noteList&list){
	char comparePoints[2] = { 0, 0 };
	sortPointChoise(comparePoints);
	if (!comparePoints[0]){
		return;
	}
	notebook temp;
	int j;
	for (int i = 1; i < list.size; i++){
		j = i - 1;
		temp = list.list[i];
		switch (comparePoints[0]){
		case '1':
			while (j >= 0 && list.list[j].price <= temp.price){
				if (comparePoints[1]!='0' && list.list[j].price == temp.price && secondSorting(list.list[j], temp, comparePoints[1])){
					break;
				}
				list.list[j + 1] = list.list[j];
				j--;
			}
			break;
		case '2':
			while (j >= 0 && list.list[j].memory <= temp.memory){
				if (comparePoints[1] != '0' && list.list[j].memory == temp.memory && secondSorting(list.list[j], temp, comparePoints[1])){
					break;
				}
				list.list[j + 1] = list.list[j];
				j--;
			}
			break;
		case '3':
			while (j >= 0 && list.list[j].storage <= temp.storage){
				if (comparePoints[1] != '0' && list.list[j].storage == temp.storage && secondSorting(list.list[j], temp, comparePoints[1])){
					break;
				}
				list.list[j + 1] = list.list[j];
				j--;
			}
			break;
		case '4':
			while (j >= 0 && list.list[j].displaySize <= temp.displaySize){
				if (comparePoints[1] != '0' && list.list[j].displaySize == temp.displaySize && secondSorting(list.list[j], temp, comparePoints[1])){
					break;
				}
				list.list[j + 1] = list.list[j];
				j--;
			}
			break;
		case '5':
			while (j >= 0 && list.list[j].colors <= temp.colors){
				if (comparePoints[1] != '0' && list.list[j].colors == temp.colors && secondSorting(list.list[j], temp, comparePoints[1])){
					break;
				}
				list.list[j + 1] = list.list[j];
				j--;
			}
			break;
		}
		list.list[j + 1] = temp;
	}
}