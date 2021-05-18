/*
 * wskaznikidowskaznikow.h
 *
 *  Created on: Apr 3, 2021
 *      Author: anana
 */

#ifndef CHAPTER_5_WSKAZNIKIDOWSKAZNIKOW_H_
#define CHAPTER_5_WSKAZNIKIDOWSKAZNIKOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Paragraf 5.6
 */

void swap(char *tabptr[], int i, int j)
{
	/*
	 * zamienia miejscami stringi w tablicy wskaznikow
	 *
	 * tabptr[]={"ola", "ala", "ida"}
	 *            0123   4567   891011
	 */
	char *linia;
	linia = *(tabptr+i);
	*(tabptr+i) = *(tabptr+j);
	*(tabptr+j) = linia;

}

void quicksortstr(char *tab_pointerow[], int l, int p)
{
	char *pivot = tab_pointerow[(l + p)/2]; //srodek
	int il = l - 1, ip = p + 1; // indeksy lewy prawy

	if(l >= p)
	{
		// jesli lewy i prawy indeks mina konczymy
		return;
	}

	while(1)
	{
		while(tab_pointerow[++il] < pivot);

		while(pivot < tab_pointerow[--ip]);

		if(il <= ip) // jak liczniki mina sie to wchodzimy do break
			swap(tab_pointerow, il, ip);
		else
			break;
	}

	if(ip > l)
		quicksortstr(tab_pointerow, l, ip);
	if(il < p)
		quicksortstr(tab_pointerow, il, p);
}

/*
 * Paragraf 5.7
 *
 * zadanie_58
 */

#define MIESIACE 12
static int dni_roku[2][MIESIACE+1] = {
		{0,31,28,31,30,31,30,31,31,30,31,30,31},
		{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int sprawdz_czy_rok_jest_rzestepny(int rok)
{
	/*
	 * latami przestępnymi są te, których numeracja:
	 * -jest podzielna przez 4 i niepodzielna przez 100 lub
	 * -jest podzielna przez 400
	 */
	return ((rok % 4)==0 && (rok % 100) != 0) || (rok % 400)==0;
}

int dzien_roku(int rok, int miesiac, int dzien)
{
	// zwraca numer dnia roku
	int nd=0,m;

	// umownie przyjmujemy maksymalny rok na 9000
	if(rok < 1 || rok > 9000)
	{
		printf("Niepoprawny rok %d %d %d\n", rok, miesiac, dzien);
		return 0;
	}

	if(miesiac > MIESIACE || miesiac < 1)
	{
		printf("Niepoprawny miesiac %d %d %d\n", rok, miesiac, dzien);
		return 0;
	}

	int rp = sprawdz_czy_rok_jest_rzestepny(rok);

	if(dzien > dni_roku[rp][miesiac] || dzien < 1)
	{
		printf("Niepoprawny dzien %d %d %d\n", rok, miesiac, dzien);
		return 0;
	}

	for(m = 1 ; m < miesiac ; ++m)
		nd += dni_roku[rp][m];

	return nd+dzien;
}

void miesiac_dzien(int rok, int dzien_roku, int *m, int *d)
{
	int mies = 1;
	*m = *d = 0;
	// umownie przyjmujemy maksymalny rok na 9000
	if(rok < 1 || rok > 9000)
	{
		printf("Niepoprawny rok %d\n", rok);
		return;
	}

	int rp = sprawdz_czy_rok_jest_rzestepny(rok);
	int dzien_roku_sum = 0;
	for(mies=1 ; mies <= MIESIACE ; ++mies)
		dzien_roku_sum += dni_roku[rp][mies];
	if(dzien_roku > dzien_roku_sum || dzien_roku < 1)
	{
		printf("Niepoprawny dzien roku %d\n", dzien_roku);
		return;
	}

	while((dzien_roku -= dni_roku[rp][mies++]) > 0);
	*m = --mies;
	*d = dzien_roku + dni_roku[rp][mies];
}

char *nazwa_miesiaca(int nr_miesiaca)
{
	static char *miesiace[] = {
			"Error",
			"Styczen", "Luty", "Marzec",
			"Kwiecien", "Maj", "Czerwiec",
			"Lipiec", "Sierpien", "Wrzesien",
			"Pazdziernik", "Listopad", "Grudzien"
	};

	return (nr_miesiaca < 1 || nr_miesiaca > 12) ? miesiace[0]:miesiace[nr_miesiaca];
}

void rfgrep(int argc, char *slowo, char *s)
{
	/*
	 * rozdział 5.10
	 */
	int flaga_jest = 0, licznik = 0;
	if(argc == 3)
	{
		if(strlen(slowo) > strlen(s))
		{
			printf("Szukany string nie wystepuje\n");
		}
		else
		{
			while(*s != '\0' && !flaga_jest)
			{
				if(*(s+strlen(slowo)-1) == '\0')
					break;
				if(*slowo != *s)
				{
					printf("iteracja\n");
					s++;
				}
				else
				{
					printf("sprawdzanie\n");
					licznik = 0;
					while(1)
					{
						if(*(slowo+licznik) == '\0')
						{
							flaga_jest = 1;
							break;
						}
						else if(*(slowo+licznik) != *(s+licznik))
						{
							break;
						}
						licznik++;
					}
				}
			}
		}
	}
	else
	{
		printf("Podaj szukany i przeszukiwany\n");
	}

	if(flaga_jest)
	{
		printf("znaleziono\n");
	}
	else
	{
		printf("nie znaleziono\n");
	}

}

/*
 * zadanie_510
 */
#include "../stos/stos.h"

void notacja_polska(char *nota)
{
	struct stosi *st = nowy_stosi(15);
	char dana;
	int liczba = 0;
	while((dana = *nota) != '\0')
	{
		switch(dana)
		{
		case '+':
		printf("+\n");
		push_stosi(st, pop_stosi(st) + pop_stosi(st));
		break;

		case '-':
		printf("-\n");
		int d =pop_stosi(st);
		push_stosi(st, pop_stosi(st) - d);
		break;

		case '*':
		printf("-\n");
		push_stosi(st, pop_stosi(st) * pop_stosi(st));
		break;

		case '/':
		printf("/\n");
		int m = pop_stosi(st);
		if(m != 0)
			push_stosi(st, pop_stosi(st) / m);
		else
			printf("Error dzielenie przez zero\n");
		break;

		case ' ':
		printf("spacja\n");
		break;

		default:
			if(isdigit(dana))
			{
				printf("liczba %c\n", dana);
				while(isdigit(dana = *nota))
				{
					liczba = liczba * 10 + (dana - '0');
					nota++;
				}
				printf("push %d\n", liczba);
				push_stosi(st, liczba);
				liczba = 0;
				nota--;  // cofamy odczytany znak ktory niejest liczba
			}

		break;
		}
		// nastepny znak z notacji
		nota++;
	}
	printf("Wynik %d/n", pop_stosi(st));
}

void onp_cmd(int argc, char *argv[])
{
	int n=0;
	char notacja_bufor[1000];
	for(int i=1 ; i < argc ; ++i)
	{
		while(*argv[i] != '\0')
		{
			notacja_bufor[n++] = *argv[i]++;
		}
		notacja_bufor[n++] = ' ';
	}
	notacja_bufor[n++] = '\0';

	notacja_polska(notacja_bufor);
}

#endif /* CHAPTER_5_WSKAZNIKIDOWSKAZNIKOW_H_ */
