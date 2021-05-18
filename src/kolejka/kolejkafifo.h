/*
 * kolejkafifo.h
 *
 *  Created on: Apr 14, 2021
 *      Author: anana
 *
 * https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
 */

#ifndef KOLEJKA_KOLEJKAFIFO_H_
#define KOLEJKA_KOLEJKAFIFO_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * FIFO cykliczna z zabezpieczeniem przed pustą lub pełną.
 */

struct kolejka_t{
	/*
	 * kolejka FIFO do przechowywania danych typu int.
	 */
	int zajete;
	int ogon;
	int glowa;
	unsigned rozmiar;
	int *dane;
};

struct kolejka_t *kolejka_inicjalozacja(unsigned rozmiar)
{
	// tworzymy 1 element samej kolejki
	struct kolejka_t *kolejka = (struct kolejka_t*)malloc(sizeof(struct kolejka_t));
	kolejka->rozmiar = rozmiar;
	kolejka->glowa = kolejka->zajete = 0;
	kolejka->ogon = -1;

	// w 1 elemencie kolejki prawidlowy rozmiar tablicy danych
	kolejka->dane = (int*)malloc(sizeof(int) * rozmiar);

	return kolejka;
}

int kolejka_pelna(struct kolejka_t *kolejka)
{
	return (kolejka->rozmiar == kolejka->zajete);
}

int kolejka_pusta(struct kolejka_t *kolejka)
{
	return (kolejka->zajete == 0);
}

void dodaj_element(struct kolejka_t *kolejka, int dana)
{
	if(kolejka_pelna(kolejka))
	{
		printf("Kolejka pelna\n");
		return;
	}

	kolejka->ogon = (kolejka->ogon + 1) % kolejka->rozmiar;
	kolejka->dane[kolejka->ogon] = dana;
	kolejka->zajete++;
	//printf("Dodano do kolejki %d\n", dana);
}

int pobierz_element(struct kolejka_t *kolejka)
{
	if(kolejka_pusta(kolejka))
	{
		printf("Kolejka pusta\n");
		return -1;
	}

	int dana = kolejka->dane[kolejka->glowa];
	kolejka->glowa = (kolejka->glowa + 1) % kolejka->rozmiar;
	kolejka->zajete--;

	//printf("Odczytano z kolejki %d\n", dana);
	return dana;
}

void test_kolejki_fifo()
{
	struct kolejka_t *kolejka = kolejka_inicjalozacja(5);

	for(int i = 0; i < 6 ; ++i)
		dodaj_element(kolejka, i);

	for(int i = 0; i < 6 ; ++i)
		printf("Pobieram %d\n",pobierz_element(kolejka));
}

#endif /* KOLEJKA_KOLEJKAFIFO_H_ */
