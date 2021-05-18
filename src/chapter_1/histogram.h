/*
 * histogram.h
 *
 *  Created on: Feb 28, 2021
 *      Author: anana
 */

#ifndef CHAPTER_1_HISTOGRAM_H_
#define CHAPTER_1_HISTOGRAM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SLOWO 15
#define MAX_ZNAKI 256

int najwieksza_wartosc_tablicy(int *arr, int arr_size)
{
	int max = arr[0];
	for(int i = 0 ; i < arr_size - 1 ; ++i)
	{
		if(max < arr[i+1])
			max = arr[i+1];
	}

	return max;
}
void histogram_pionowy(int *data, int data_rozmiar)
{
	for(int i = 1 ; i < data_rozmiar ; ++i)
	{
		printf("%d\t%6d:\t|", i, data[i]);
		for(int d = 0 ; d < data[i] ; ++d)
		{
			printf("-");
		}
		printf("|\n");
	}
}

void histogram_poziomy(int *data, int data_rozmiar)
{
	int najwiekszy = najwieksza_wartosc_tablicy(data, data_rozmiar);

	for(int h = najwiekszy ; h >0 ; --h)
	{
		for(int i = 1 ; i < data_rozmiar ; ++i)
		{
			if(data[i] >= h)
			{
				printf("  |");
			}
			else
			{
				printf("   ");
			}
		}
		printf("\n");
	}
	printf("\n");

	for(int i = 1 ; i < data_rozmiar ; ++i)
	{
		printf("%3d", data[i]);
	}
	printf("\n");

	for(int i = 1 ; i < data_rozmiar ; ++i)
	{
		printf("%3d", i);
	}
	printf("\n");
}

void histogram(char *data, int rozmiar)
{
	int dlugosci_slow[MAX_SLOWO] = {0};
	int c, licznik_znakow_w_slowie = 0, flaga_pierwszy_bialy = 0;

	for(int i =0 ; i < rozmiar ; ++i)
	{
		c =data[i];

		if(c == '\n' || c == '\t' || c == ' ' || c == '\0')
		{
			if (flaga_pierwszy_bialy == 0)
			{
				if(licznik_znakow_w_slowie < MAX_SLOWO)
				{
					++dlugosci_slow[licznik_znakow_w_slowie];
				}
				else
				{
					printf("Error: index out of range %d\n", licznik_znakow_w_slowie);
				}

				flaga_pierwszy_bialy = 1;
				licznik_znakow_w_slowie = 0;
			}
			continue;
		}
		else
		{
			flaga_pierwszy_bialy = 0;
			++licznik_znakow_w_slowie;
		}
	}

	histogram_pionowy(dlugosci_slow, MAX_SLOWO);
	histogram_poziomy(dlugosci_slow, MAX_SLOWO);
}

void histogram_znaki(char *data, int rozmiar)
{
	int dlugosci_slow[MAX_ZNAKI] = {0};
	int c;

	for(int i =0 ; i < rozmiar ; ++i)
	{
		c =data[i];
		++dlugosci_slow[c];
	}

	histogram_poziomy(dlugosci_slow, MAX_ZNAKI);
}

int test_histogram(void)
{
	char data_test[] = "OK, but";
	histogram(data_test, sizeof(data_test));

	return EXIT_SUCCESS;
}

int test_histogram_znaki(void)
{
	char data_test[] = "to jest jakis zart, Nie zamierzam patrzec jak ktoś marnuje moje dane.. / zreszta kogoto obochodzi dzisiaj, i po co !!! jaj sie mecze";
	histogram_znaki(data_test, sizeof(data_test));

	return EXIT_SUCCESS;
}

#endif /* CHAPTER_1_HISTOGRAM_H_ */
