#include <Windows.h>
#include "Notebooks.h"
#include "Menu.h"
#include "ListsChanging.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	notebook* onlinerPopularNotebooks = nullptr;
	FILE *site = nullptr;
	noteList favoriteNotebooks;
	creating(onlinerPopularNotebooks, site, favoriteNotebooks);
	menu(onlinerPopularNotebooks, favoriteNotebooks);
	ending(onlinerPopularNotebooks, site, favoriteNotebooks);
	return 0;
}