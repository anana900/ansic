/*
 * drzewo_binarne.h
 *
 *  Created on: Apr 7, 2021
 *      Author: anana
 */

#ifndef DRZEWO_BINARNE_DRZEWO_BINARNE_H_
#define DRZEWO_BINARNE_DRZEWO_BINARNE_H_
#include <stdlib.h>
#include <stdio.h>

struct tnode {
	char *slowo;
	int wystapienia;
	struct tnode *lewe; // szukane slowo mniejsze od tego w wezle
	struct tnode *prawe; // szukane slowo wieksze od tego w wezle
};




#endif /* DRZEWO_BINARNE_DRZEWO_BINARNE_H_ */
