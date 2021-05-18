/*
 * binarysearch.h
 *
 *  Created on: Mar 9, 2021
 *      Author: anana
 */

#ifndef CHAPTER_3_BINARYSEARCH_H_
#define CHAPTER_3_BINARYSEARCH_H_
#include <time.h>
int binarysearch(long int zbior[], long int target, long int rozmiar)
{
	/*
	 * 3.1
	 * tablica musi byc posortowana
	 */
	long int low, mid, high;
	low = 0;
	high = rozmiar - 1;

	while(low <= high)
	{
		mid = (low + high) / 2;
		if(target < zbior[mid])
		{
			high = mid;
		}
		else if(target > zbior[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int binarysearch2(long int zbior[], long int target, long int rozmiar)
{
	/*
	 * 3.1
	 * tablica musi byc posortowana
	 */
	long int low, mid, high;
	low = 0;
	high = rozmiar - 1;
	mid = (low + high) >> 1;

	while(low <= high && target != zbior[mid])
	{
		if(target < zbior[mid])
		{
			high = mid;
		}
		else
		{
			low = mid + 1;
		}
		mid = (low + high) >> 1;
	}

	if(target == zbior[mid])
		return mid;
	else
		return -1;
}

void porownaniebinarysearch()
{
	/*
	 * time, comparison, porownanie, performance, wydajnosc szybkosc
	 */
	const long int roz = 1000000;
	int long dana[roz];
	for(long int i = 0 ; i < roz ; ++i)
		dana[i] = i;

	clock_t begin = clock();
	//printf("%d ", binarysearch2(dana, 22, roz));
	binarysearch(dana, 22, roz);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("%f ", time_spent);

	begin = clock();
	//printf("%d ", binarysearch(dana, 22, roz));
	binarysearch2(dana, 22, roz);
	end = clock();
	double time_spent1 = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("%f ", time_spent1);
}

#endif /* CHAPTER_3_BINARYSEARCH_H_ */
