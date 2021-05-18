/*
 * escape.h
 *
 *  Created on: Mar 9, 2021
 *      Author: anana
 */

#ifndef CHAPTER_3_ESCAPE_H_
#define CHAPTER_3_ESCAPE_H_

#include <stdio.h>

void escape(char out[], char in[])
{
	/*
	 * 3.2
	 */

	int c, i = 0;
	const int r = 1000;
	// zczytanie danych z wejscia
	while((c = getchar()) != EOF && i < r)
	{
		switch(c)
		{
		case '\n':
			in[i++] = '\\';
			in[i++] = 'n';
			break;
		case '\t':
			in[i++] = '\\';
			in[i++] = 't';
			break;
		default:
			in[i++] = c;
			break;
		}
	}
	in[i] = '\0';

	i = 0;
	while(in[i] != '\0')
		printf("%c", in[i++]);

	// wypisanie danych na wyjscie
	//...
}

void sortowanieshella(long int d[], long int r)
{
	/*
	 * shella 1 TODO
	 */
	long int i = 0, j = 0, p;

	p = r/2;
	int tmp;

	for(i = 0 ; i < p ; ++i)
	{
		if(d[i] > d[i + p])
		{
			tmp = d[i];
			d[i] = d[i + p];
			d[i + p] = tmp;
		}
	}

	i = 0;
	while(d[i] != '\0')
		printf("%d ", d[i++]);

}

void itoa_space(int liczba, int szerokosc)
{
	/*
	 * 3.6
	 * -232 -> [' ', ' ', ' ', '-', '2', '3', '2']
	 */

	char la[szerokosc];
	int i = 0, sign = 0;

	if(liczba < 0)
	{
		sign = -1;
		liczba *= -1;
	}

	do {
		if(liczba == 0 && sign == -1)
		{
			la[szerokosc-i-1] = '-';
			sign = 0;
		}
		else if(liczba == 0 && sign == 0)
		{
			la[szerokosc-i-1] = ' ';
		}
		else
		{
			la[szerokosc-i-1] = (liczba % 10) + '0';
		}
		liczba /= 10;
	} while( i++ < szerokosc);

	printf("\n");
	for(i = 0 ; i < szerokosc ; ++i)
		printf("%c", la[i]);
}

#endif /* CHAPTER_3_ESCAPE_H_ */
