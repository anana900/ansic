/*
 * szukaniesubstringu.h
 *
 *  Created on: Mar 10, 2021
 *      Author: anana
 */

#ifndef CHAPTER_4_SZUKANIESUBSTRINGU_H_
#define CHAPTER_4_SZUKANIESUBSTRINGU_H_

#include <stdio.h>
#include <ctype.h>

int grep1(char d[], char s[])
{
	/*
	 * 4.1
	 * funkcja ma zwrocic index ostatniego wystapienia substringu w danej lini
	 * 1. zbieramy dane do tablicy - i przesylamy ja do tej funkcji
	 * 2. po kolei bierzemy kolejne linijki i w kazdej linice szukamy od konca?
	 * 3. jesli jest zwracamy indeks (albo indeksy wiersz kursor)
	 * 4. jesli nie ma zwracamy -1
	 *
	 * kosa ma sake i osaka
	 * ['s', 'a']
	 */

	int c, i = 0, j = 0, potencjalny_index = -1, linia = 0, kursor = 0;

	while((c = d[i]) != '\0')
	{
		while((c = d[i]) != '\0' && c != '\n' && c == s[j])
		{
			//printf("sprawdzam %d: %c == %c i=%d, j=%d\n", linia,  d[i], s[j], i, j);
			kursor++;
			if(strlen(s) - 1 == j)
			{
				//printf("jest\n");
				potencjalny_index = i - j;
				j = 0;
			}
			i++;
			j++;
		}

		if(c == '\n')
		{
			if(potencjalny_index != -1)
				printf("JEST linia %d index %d kursor %d\n",linia,  potencjalny_index, (int)(kursor - strlen(s)));
			potencjalny_index = -1;
			kursor = 0;
			++linia;
		}

		i++;
		j = 0;
		//printf("linia=%d, i=%d, j=%d\n", linia, i, j);
	}

	return -1;
}

double atofe(char dana[])
{
	/*
	 * 6.2
	 * obsługa notacji wykładniczej E-3 e+3
	 *
	 *  - brak obslugi wykladnikow > 9
	 *  - brak obslugi notacji bez .
	 */

	double val = 0.0, power, sign;
	int i, c;

	for(i = 0 ; isspace(dana[i]) ; i++)
		;

	sign = (dana[i] == '-' ? -1.0 : 1.0);
	if(dana[i] == '+' || dana[i] == '-')
		++i;

	// czesc calkowita
	for(val = 0.0 ; isdigit(dana[i]) ; i++)
		val = 10.0 * val + (dana[i] - '0');

	// kropka
	if(dana[i] == '.')
		++i;

	//czesc ulamkowa
	int nota_wyklad = 0, znak = 1;
	power = 1.0;
	while((c = dana[i]) != '\0' && c != '\n')
	{
		if(isdigit(c))
		{
			if(nota_wyklad == 0)
			{
				val = 10.0 * val + (c - '0');
				power *= 10;
			}
			else
			{
				for(int z = 0 ; z < (int)(c - '0') ; z++)
					nota_wyklad *= 10;
			}
		}
		else if((c == 'E' || c == 'e') && nota_wyklad == 0)
		{
			nota_wyklad = 1;
		}
		else if(c == '-')
			znak = -1;
		else if(c == '+')
			znak = 1;
		else
		{
			break;
		}
		++i;
	}

	if(znak < 0 && nota_wyklad)
		return sign * val / power / nota_wyklad;
	else if (znak > 0 && nota_wyklad)
		return sign * val / power * nota_wyklad;
	else
		return sign * val / power;
}



#endif /* CHAPTER_4_SZUKANIESUBSTRINGU_H_ */
