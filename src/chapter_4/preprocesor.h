/*
 * preprocesor.h
 *
 *  Created on: Apr 2, 2021
 *      Author: anana
 */

#ifndef CHAPTER_4_PREPROCESOR_H_
#define CHAPTER_4_PREPROCESOR_H_

#include <stdio.h>

#define plus(a, b) a+b
#define OLA "Ola"
#define ZYCZENIA(cos) printf(#cos " dla %s %f", (OLA), (float)(cos))
//#define SWAP(t,x,y) {t _tmp;_tmp = (y);(y) = (x);(x) = _tmp;}

void swap_test(int a, int b)
{

	#if DEBUG
		// gcc main.c -D DEBUG=1 -o program
		printf("Dane wejscowe poprawne\n");
	#endif

	ZYCZENIA(12/5);
	//printf("%d %d", SWAP(int, a, b));
}


#endif /* CHAPTER_4_PREPROCESOR_H_ */
