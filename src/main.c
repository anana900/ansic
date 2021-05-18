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
#include <time.h>

#include "chapter_1/histogram.h"
#include "chapter_1/getline.h"
#include "chapter_1/detab.h"
#include "chapter_2/typy.h"
#include "chapter_2/binarne.h"
#include "chapter_3/binarysearch.h"
#include "chapter_3/escape.h"
#include "chapter_4/szukaniesubstringu.h"
#include "sortowania/sortowania.h"
#include "sokety/sokety.h"
#include "chapter_4/preprocesor.h"
#include "chapter_5/wskazniki.h"
#include "chapter_5/wskaznikidowskaznikow.h"
#include "stos/stos.h"
#include "kolejka/kolejkafifo.h"
#include "watki/watki.h"
#include "stdi/wejscie.h"
#include "csv/csvhandle.h"
#include "testowanie_pointerow/test_pointer.h"

int main(int argc, char *argv[])
{
	//test_histogram();
	//test_histogram_znaki();
	int rozmiar = 1000;
	char tab_1[rozmiar];
	char tab_2[rozmiar];

	//setlinesfunc(tab_1, rozmiar);

	//findlongestline(tab_1, tab_2, rozmiar);
	//szukajchararrorozmiarze(tab_1, rozmiar, 2, 4);
	//usuwabialeznakinakoncuwiersza(tab_1, rozmiar);
	//reverschararr(tab_1);
	//detab(tab_1, rozmiar);
	//entab(tab_1, rozmiar);
	//podzielwiersz(tab_1, rozmiar);
	//usuwaniekomentarzyc(tab_1, rozmiar);
	//straznikskladnic(tab_1, rozmiar);
	//rozmiaryzmiennych();

	//htoi(tab_1, rozmiar);
	//char x[] = {'a', 'b'};
	//charremover(tab_1, x);
	//printf("%d ", anychar(tab_1, x));

	//printfb(10, 4);
	//printf("\n%d ",bitcountsr(456546));
	//printf("\n%d ",bitcountsr2(10000));
	//printf("\n%d ",bitcountsfast(1000045245));
	//porownaniebinarysearch();
	//escape(tab_1, tab_2);
	//long int d[8] = {6,5,4,33,3,1,9,7};
	//sortowanieshella(d,8);
	//itoa_space(-345, 10);

	//setlinesfunc(tab_1, rozmiar);
	//grep1(tab_1, "los");

	//printf("%f ", atofe(tab_1));

	//sort_test();

	//soket_serwer();
	//soket_client();

	//swap_test(10,20);

	//int a=12,b=33;printf("%d %d \n", a, b);swapp(&a,&b);printf("%d %d \n", a, b);

	//tablica_int();
	//tablica_float();

	//char a[20]="";
	//char b[20]=" ";
	//strkop(a,b);
	//zadanie_53(a,b);
	//printf("%d\n",zadanie_54(a,b));
	//for(int i = 0 ; i< 20 && a[i] != '\0' ; ++i)
	//	printf("%c",a[i]);

	//#define MAX 10
	//char *tabstringow[MAX] = {"ola", "al111a", "ida"};
	//quicksortstr(tabstringow, 0, 2);
	//swap(tabstringow, 0, 1);
	//for(int i = 0 ; i < MAX && *(tabstringow+i) != NULL ; i++)
	//	printf("%s\n",*(tabstringow+i));

	//printf("%d \n",dzien_roku(1999,dzien_roku(3,3,3),3));
	//printf("%d \n",dzien_roku(2021,0,3));
	//printf("%d \n",dzien_roku(2021,42,3));
	//printf("%d \n",dzien_roku(2021,4,35));
	//printf("%d \n",dzien_roku(0,4,3));
	//int d=0, m=0, *pd, *pm;
	//pd = &d;
	//pm = &m;
	//miesiac_dzien(2021, 60, pm, pd);
	//printf("%d %d \n",*pm, *pd);
	//miesiac_dzien(2021, 1260, pm, pd);
	//printf("%d %d \n",*pm, *pd);
	//miesiac_dzien(2021, 0, pm, pd);
	//printf("%d %d \n",*pm, *pd);
	//miesiac_dzien(0, 60, pm, pd);
	//printf("%d %d \n",*pm, *pd);

	//printf("%s\n",nazwa_miesiaca(13));

	//rfgrep(argc, argv[1], argv[2]);

	//struct stosi *stos = nowy_stosi(5);
	//pop_stosi(stos);
	//for(int d=10 ; d < 20 ; d++)
	//	push_stosi(stos, d);

	//notacja_polska("22 11 - 2 * 3 / 2 4 - - x");
	//onp_cmd(argc, argv);

	//struct point {
	//int x; int y;
	//} p1 = {10,33}, *pp = &p1, patab[5], pbtab[] = {0,0,1,1,2,2,3,3,4,4};

	//watki_zmienna_warunkowa();

	//test_czytanie();
	//test_czytanie_do_tablicy(argc, argv);

	//csv_read();

	test_pointer();

	printf("\nOK\n");
	return EXIT_SUCCESS;
}
