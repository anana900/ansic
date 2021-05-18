/*
 * sortowania.h
 *
 *  Created on: Mar 11, 2021
 *      Author: anana
 */

#ifndef SORTOWANIA_SORTOWANIA_H_
#define SORTOWANIA_SORTOWANIA_H_

void zamiana(int a[], unsigned long l, unsigned long p)
{
	unsigned long tmp = a[l];
	a[l] = a[p];
	a[p] = tmp;
}

void printinta(int d[], unsigned long s)
{
	for(unsigned long i = 0 ; i < s ; ++i)
	{
		printf("%d ", d[i]);
		if(i != 0 && i%40 == 0)
			printf("\n");
	}
	printf("\n");
}

void babelkowe(int a[], unsigned long r)
{
	/*
	 * sortowanie bąbelkowe
	 * kazdy z kazdym porownujemy
	 * ptele porownawcza powtarzamy dopuki nie bedzie ani jednego porownania
	 */
	int flag_posortowane = 0;
	unsigned long i = 0;

	while(!flag_posortowane)
	{
		flag_posortowane = 1;
		i = 0;
		while(i < r - 1)
		{
			if(a[i] > a[i+1])
			{
				flag_posortowane = 0;
				zamiana(a, i, i+1);
			}
			++i;
		}
	}
}

void przezwstawianie(int a[], unsigned long r)
{
	/*
	 * lecimy po tablicy i kazdy kolejny element
	 * porownujemy z poprzednimi elementami
	 */

	unsigned long mlodszy, starszy;

}

void quicksort(int a[], unsigned long l, unsigned long p)
{
	/*
	 * quicksort, sortowanie szybkie, rekurencyjne
	 * p - l to indeksy tablicy skrajene - prawa i lewa strona
	 * jako wartosci startowe dla l =0 a dla p = max-1
	 */

	unsigned long pivot = a[(l + p)/2]; //srodek

	unsigned long il = l - 1, ip = p + 1;

	if(l >= p)
	{
		// jesli lewy i prawy indeks mina konczymy
		return;
	}

	while(1)
	{
		while(a[++il] < pivot);

		while(pivot < a[--ip]);

		if(il <= ip) // jak liczniki mina sie to wchodzimy do break
			zamiana(a, il, ip);
		else
			break;
	}

	if(ip > l)
		quicksort(a, l, ip);
	if(il < p)
		quicksort(a, il, p);
}

void sort_test()
{
	time_t t;
	srand((unsigned) time(&t));
	unsigned long s = 20000;
	int d[s];
	for(unsigned long i = 0 ; i < s ; ++i)
		d[i] = rand()%127;

	printinta(d,s);

	//quicksort(d, 0, s - 1);
	//babelkowe(d, s);

	printinta(d,s);
}

#endif /* SORTOWANIA_SORTOWANIA_H_ */
