/*
 ============================================================================
 Name        : ansic.c
 Author      : anana
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chapter_1/histogram.h"
#include "chapter_1/getline.h"
#include "chapter_1/detab.h"

int main(void)
{
	//test_histogram();
	//test_histogram_znaki();
	int rozmiar = 1000;
	char tab_1[rozmiar];
	char tab_2[rozmiar];

	setlinesfunc(tab_1, rozmiar);

	//findlongestline(tab_1, tab_2, rozmiar);
	//szukajchararrorozmiarze(tab_1, rozmiar, 2, 4);
	//usuwabialeznakinakoncuwiersza(tab_1, rozmiar);
	//reverschararr(tab_1);
	//detab(tab_1, rozmiar);
	//entab(tab_1, rozmiar);
	podzielwiersz(tab_1, rozmiar);

	return EXIT_SUCCESS;
}
