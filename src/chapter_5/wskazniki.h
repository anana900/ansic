/*
 * wskazniki.h
 *
 *  Created on: Apr 2, 2021
 *      Author: anana
 */

#ifndef CHAPTER_5_WSKAZNIKI_H_
#define CHAPTER_5_WSKAZNIKI_H_

#include <stdio.h>

void swapp(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


/*
 * Idea getch i ungetch
 * to buforowanie
 * oczekiwane znaki sa odczytywane wbudowana funkcja getchar()
 * po odczytaniu niechcianego znaku zwracamy go do naszego bufora
 * w kolejnej iteracji w prgramie najpierw czytamy z bufora i
 * odpowiednio procesujemy niechciane znaki. Gdy bufor jest pusty,
 * czytamy znow za pomoca getchar()
 *
 */
#define BUFSIZE 8
char buf[BUFSIZE];
int bufp = 0; // nastepna wolna pozycja w buforze

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("przekroczony bufor\n");
	else
	{
		printf("dodaje do bufora %i \n", c);
		buf[bufp++] = c;
	}
}

int getch(void)
{
	//return (bufp > 0) ? buf[--bufp] : getchar();
	if(bufp > 0)
	{
		printf("zmniejszam bufor i zwracam zawartosc %d \n", bufp);
		return buf[--bufp];
	}
	else
	{
		printf("getchar() \n");
		return getchar();
	}
}

int getint(int *pn)
{
	int c, sign;

	// pomijamy biale znaki
	while(isspace(c = getch()));

	// znak nie jest liczbą
	// +
	if(!isdigit(c) && c!=EOF && c!= '+' && c!='-')
	{
		ungetch(c);
		return 0;
	}

	// znak jest + -
	sign = (c == '-') ? -1 : 1;
	if(c == '+' || c == '-')
	{
		c = getch();
	}

	// znak jest liczbą
	// w tym miejscu zawsze element z tablicy *pn
	// jest ustawiany poczatkowo na 0:
	// *pn=0
	// for( ; isdigit(c) ; c = getch())
	for(*pn = 0 ; isdigit(c) ; c = getch())
	{
		*pn = 10 * *pn + (c - '0');
	}

	*pn *= sign;

	if(c != EOF)
		ungetch(c);

	return c;
}

int zadanie_51(int *pn);

void tablica_int()
{
	const unsigned int SIZE = 10;
	int n, array[SIZE], getint(int *);

	for(n = 0 ; n < SIZE && zadanie_51(&array[n]) != EOF ; ++n)
		printf("loop-----------------\n");

	for(int e= 0 ; e < SIZE ; ++e)
		printf("%d ",array[e]);
}

int zadanie_51(int *pn)
{
	/*
	 * Nie jest zrobione
	 */
	int c, sign;

	// pomijamy biale znaki
	while(isspace(c = getch()));

	// znak nie jest liczbą
	// +
	if(!isdigit(c) && c!=EOF && c!= '+' && c!='-')
	{
		ungetch(c);
		return 0;
	}

	// znak jest + -
	sign = (c == '-') ? -1 : 1;
	if(c == '+' || c == '-')
	{
		c = getch();
		if(isspace(c) || c=='+' || c=='-')
		{
			ungetch(c);
			return 0;
		}
	}

	for(*pn = 0; isdigit(c) ; c = getch())
	{
		*pn = 10 * *pn + (c - '0');
	}

	*pn *= sign;

	if(c != EOF)
		ungetch(c);

	return c;
}

int zadanie_52(float *pf)
{
	int c;
	while(isspace(c=getch()));

	*pf = 0.0;
	float ulamek =1.0;
	int flaga_przecinek = 0;
	for(;isdigit(c) || c == '.'; c=getch())
	{
		printf("loop 1 %f \n", *pf);
		if(c=='.' && flaga_przecinek == 0)
		{
			flaga_przecinek += 1;
			continue;
		}
		if(flaga_przecinek != 2)
		{
			*pf = *pf * 10 + (c - '0');
			if(flaga_przecinek == 1)
				ulamek = ulamek * 10;
			continue;
		}
	}

	printf("loop 2 %f \n", *pf);
	*pf = *pf/ulamek;

	return c;
}

void tablica_float()
{
	const unsigned int SIZE = 10;
	float array[SIZE];
	int n;

	for(n = 0 ; n < SIZE && zadanie_52(&array[n]) != EOF ; ++n)
		printf("loop-----------------\n");

	for(int e= 0 ; e < SIZE ; ++e)
		printf("%f ",array[e]);
}

void strkop(char *wyj, char *z)
{
	while((*wyj++ = *z++) != '\0');
}

void zadanie_53(char *s, char *t)
{
	/*
	 * kopiuje ciag t na koniec ciagu s
	 * zakladamy ze s jest odpowiednio duze
	 */

	while(*s++);
	*s--;

	while((*s++ = *t++) != '\0');
}

int zadanie_54(char *s, char *t)
{
	/*
	 * szuka ciag t na koncu ciagu s
	 */

	while(*s++);

	int tsize = 1;
	while(*t++)
		tsize++;

	printf("%d\n", tsize);
	while(*s-- == *t--)
	{
		printf("s %c : t %c\n", *s, *t);
		if(tsize-- == 0)
			return 1;
	}
	return 0;
}



#endif /* CHAPTER_5_WSKAZNIKI_H_ */
