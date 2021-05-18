/*
 * stos.h
 *
 *  Created on: Apr 7, 2021
 *      Author: anana
 */

#ifndef STOS_STOS_H_
#define STOS_STOS_H_

#define STOS_MAX 5

/*
 * TABLICOWY
 */
int stos_tab[STOS_MAX];
int stos_tab_nast_wol_poz = 0;

int push_tab(int dana)
{
	if(stos_tab_nast_wol_poz < STOS_MAX)
	{
		stos_tab[stos_tab_nast_wol_poz++] = dana;
		return 0;
	}
	else
	{
		printf("Stos pelen\n");
		return 1;
	}
}

int pop_tab(void)
{
	if(stos_tab_nast_wol_poz > 0)
	{
		return stos_tab[--stos_tab_nast_wol_poz];
	}
	else
	{
		printf("Stos pusty\n");
		return -1;
	}
}

int stos_tab_peek(void)
{
	return stos_tab[stos_tab_nast_wol_poz];
}

int stos_tab_rozmiar()
{
	return stos_tab_nast_wol_poz;
}

int stos_tab_empty(void)
{
	return (stos_tab_nast_wol_poz == 0) ? 1 : 0;
}

/*
 * WSKAZNIKOWY
 */

struct stosi
{
	/*
	 * struktura reprezentujaca stos
	 * mozna na nim przechowywac tylko elementy typu int
	 */
	int maksymalny_rozmiar;
	int top;
	int *elementy; // tylko int
};

struct stosi* nowy_stosi(int rozmiar)
{
	/*
	 * inicjalizowanie stosu - wołamy tylko 1 raz
	 * Stos jest representowany tylko przez 1 element tej struktury
	 * W strukturze jest tablica: stosiptr->elementy o okresonym rozmiarze
	 * Inicjalizując stos element pierwszy jest ustawiony na -1
	 * Dodajac pierwszy element do stosu najpierw zwiekszamy top
	 * z -1 na 0, potem zapissujemy do tablicy dana:
	 * top = top +1;
	 * elementy[top] = dana;
	 */
	struct stosi *stosiptr = (struct stosi*)malloc(sizeof(struct stosi));

	stosiptr->maksymalny_rozmiar = rozmiar;
	stosiptr->top = -1;
	stosiptr->elementy = (int*)malloc(sizeof(int) * rozmiar);

	return stosiptr;
}

int stosi_rozmiar(struct stosi *ptr)
{
	return ptr->top+1;
}

int stosi_empty(struct stosi *ptr)
{
	return ptr->top == -1;
}

int stosi_full(struct stosi *ptr)
{
	return ptr->top == ptr->maksymalny_rozmiar-1;
}

int pop_peek(struct stosi *ptr)
{
	if(stosi_empty(ptr))
	{
		printf("Pusty stos\n");
		return 1;
	}
	else
	{
		return ptr->elementy[ptr->top];
	}
}

int push_stosi(struct stosi *ptr, int dana)
{
	if(stosi_full(ptr))
	{
		printf("Stos pełen\n");
		return 1;
	}
	else
	{
		ptr->elementy[++(ptr->top)] = dana;
		return 0;
	}
}

int pop_stosi(struct stosi *ptr)
{
	if(stosi_empty(ptr))
	{
		printf("Pusty stos\n");
		return 1;
	}
	else
	{
		return ptr->elementy[(ptr->top)--];
	}
}

#endif /* STOS_STOS_H_ */
