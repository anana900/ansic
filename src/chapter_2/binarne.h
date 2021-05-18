/*
 * binarne.h
 *
 *  Created on: Mar 8, 2021
 *      Author: anana
 */

#ifndef CHAPTER_2_BINARNE_H_
#define CHAPTER_2_BINARNE_H_

void printfb(unsigned int liczba, int bity)
{
	/*
	 * Wyświetlanie liczby w postaci bin
	 */
	if(bity < 1)
	{
		printf("Liczba bitow zbyt mala, minimum 1\n");
		exit(1);
	}

	if(liczba > 1 && --bity > 0)
	{
		printfb(liczba / 2, bity);
	}
	else
	{
		printf("\n");
		while(--bity > 0)
			printf("0");
	}

	printf("%d", liczba % 2);
}

int count_1 = 0;
int bitcountsr(unsigned l)
{
	/*
	 * zliczanie bitow 1 w liczbie
	 */
	count_1 = 0;
	if(l > 1)
		bitcountsr(l / 2);

	if(l % 2)
		++count_1;
	return count_1;
}

int bitcountsr2(unsigned l)
{
	/*
	 * zliczanie bitow 1 w liczbie
	 */
	int count_1 = 0;

	for(; l != 0 ; l >>= 1)
	{
		if(l & 01)
			count_1 += 1;
	}
	return count_1;
}

int bitcountsfast(unsigned l)
{
	/*
	 * 2.9
	 */
	int wynik = 0;
	while(l)
	{
		wynik++;
		l &= l-1;
	}
	return wynik;
}

#endif /* CHAPTER_2_BINARNE_H_ */
