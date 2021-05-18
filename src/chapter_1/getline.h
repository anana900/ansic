/*
 * getline.h
 *
 *  Created on: Feb 28, 2021
 *      Author: anana
 */

#ifndef CHAPTER_1_GETLINE_H_
#define CHAPTER_1_GETLINE_H_

#include <stdio.h>

int setlinesfunc(char wiersze[], int maxline)
{
	/*
	 * Funkcja pobiera z stdio ciagi znakow
	 * wraz ze znakami nowej lini, konczac
	 * dopiero po wprowadzeniu EOF, tzn
	 * Ctrl+D lub w przypadku przepelnienia
	 * maksymalnego rozmiaru tablicy
	 */
	int c, i = 0;
	while((c = getchar()) != EOF && i < maxline - 1)
	{
		wiersze[i] = c;
		i++;
	}

	wiersze[i]='\0';

	return i;
}

int findlongestline(char data[], char longest[], int maxsize)
{
	/*
	 * Funkcja z tablicy zawierajacej ciagi znakow,
	 * oddzielone znakiem nowej lini, wyszukuje
	 * najdluzszy ciag, zwracajac go za pomoca tablicy
	 * oraz zwracajac dlugosc tego ciagu przez return
	 */
	int max = 0, tmp_max = 0, max_start_index = 0;

	for(int i = 0 ; i < maxsize && data[i] != '\0' ; ++i)
	{
		if(data[i] == '\n')
		{
			if(tmp_max > max)
			{
				max = tmp_max;
				max_start_index = i - max;
			}

			tmp_max = 0;
		}
		else
		{
			tmp_max++;
		}
	}

	for(int i = 0 ; i <= max ; ++i)
	{
		longest[i] = data[i + max_start_index];
	}

	printf("%d: %s", max, longest);

	return max;
}

void usuwabialeznakinakoncuwiersza(char data[], int rozmiar)
{
	/*
	 * usuwanie bialych znakow na koncu wiersza
	 */

	printf("Przed:\t%s\n", data);

	char tmp_data[rozmiar];
	int c, kursor = 0, cofniecie = 0, flaga_znak = 0;

	copychararr(tmp_data, data);

	for(int i = 0 ; i < rozmiar && tmp_data[i] != '\0' ; ++i)
	{
		// "\n"
		// " \n"
		// "1 \n"
		c = tmp_data[i];

		if(c != '\n')
		{
			if(c == ' ' || c == '\t')
			{
				cofniecie++;
			}
			else
			{
				flaga_znak = 1;
				cofniecie = 0;
			}

			data[kursor] = c;
			kursor++;
		}
		else
		{
			if(cofniecie)
			{
				kursor = kursor - cofniecie;
			}

			if(flaga_znak)
			{
				flaga_znak = 0;
				data[kursor] = '\n';
				kursor++;
			}
		}
	}

	printf("Po:\t%s\n", data);
}

void szukajchararrorozmiarze(char data[], int rozmiar, int min, int max)
{
	int c, i = 0, tmp_index_start = 0, tmp_znaki = 0;

	for(; i < rozmiar && data[i] != '\0' ; ++i)
	{
		c = data[i];
		tmp_znaki++;

		if(c == '\n')
		{
			if(tmp_znaki >= min +1 && tmp_znaki <= max) // +1 w celu pominiecia znakow nowych linii
			{
				for(int z = tmp_index_start ; z < tmp_znaki + tmp_index_start ; ++z)
				{
					printf("%c", data[z]);
				}
				//printf("\n");
			}
			tmp_index_start += tmp_znaki;
			tmp_znaki = 0;
		}
	}
}

void copychararr(char to[], char from[])
{
	/*
	 * Kopiowanie tablic znakowych
	 */
	int i = 0;
	while((to[i] = from[i]) != '\0')
	{
		++i;
	}
}

void reverschararr(char data[])
{
	/*
	 * Tablica znakow rewers
	 */
	int i = 0;
	while(data[i] != '\0')
		++i;

	char tmp[i];
	copychararr(tmp, data);

	for(int j = 0 ; j < i - 1 ; ++j)
		data[j] = tmp[i - j - 2];

	data[i - 1] = '\n';
	data[i] = '\0';

	//printchararr(data, i);
}

void printchararr(char linie[], int rozmiar)
{
	/*
	 * Printowanie tablic znakowych
	 */
	for(int i = 0 ; i < rozmiar && linie[i] != '\0'; i++)
	{
		printf("%c", linie[i]);
	}
}

#endif /* CHAPTER_1_GETLINE_H_ */
