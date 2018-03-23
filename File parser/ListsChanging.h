#pragma once
#include "Notebooks.h"
#include <stdio.h>
void myNoteFilling(notebook&newNotebook);
void additing(noteList&list);
void cashing(notebook* popularNotebooks, noteList&favoriteNotebooks);
void unselect(char* link, notebook* popularNotebooks);
void deleting(noteList&list, int number);
int deleteChoosing(noteList&list);
void colorCompare(notebook&note);
void popularFilling(notebook *note, FILE *site);
void creating(notebook*&onlinerPopularNotebooks, FILE*&site, noteList&favoriteNotebooks);
void ending(notebook*&onlinerPopularNotebooks, FILE*&site, noteList&favoriteNotebooks);
