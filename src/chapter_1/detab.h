/*
 * detab.h
 *
 *  Created on: Mar 3, 2021
 *      Author: anana
 */

#ifndef CHAPTER_1_DETAB_H_
#define CHAPTER_1_DETAB_H_

#include "getline.h"

#define C_TABSIZE 	7
#define C_TAB		'\t'
#define C_NUL		'\0'
#define C_SPACE		' '
#define C_NEWLINE	'\n'

void detab(char data[], int rozmiar)
{
	/*
	 * 1.20
	 */
	char tmp[rozmiar];
	copychararr(tmp, data);

	int c, in = 0, out = 0;

	while(in < rozmiar && out < rozmiar && (c = tmp[in]) != C_NUL)
	{
		if(c == C_TAB)
		{
			c = C_SPACE;
			for(int t = 0 ; t < C_TABSIZE ; ++t)
			{
				data[out] = c;
				++out;
			}
			++in;
			continue;
		}

		data[out] = c;
		++in;
		++out;
	}

	data[out] = C_NUL;

	printchararr(data, rozmiar);
}

void entab(char data[], int rozmiar)
{
	/*
	 * 1.21
	 */

	char tmp[rozmiar];
	copychararr(tmp, data);

	int c, in = 0, out = 0, space_counter = 0, flaga_sapce_only = 0;

	while(in < rozmiar && out < rozmiar && (c = tmp[in]) != C_NUL)
	{
		if(c == C_SPACE)
		{
			space_counter++;
			flaga_sapce_only = 1;
		}
		else
		{
			space_counter = 0;
			flaga_sapce_only = 0;
		}

		if(flaga_sapce_only && space_counter != 0 && space_counter % C_TABSIZE == 0)
		{
			c = C_TAB;
			out = out - C_TABSIZE + 1;
			data[out] = c;
		}
		else
		{
			data[out] = c;
		}

		++in;
		++out;
	}

	data[out] = C_NUL;

	printchararr(data, rozmiar);
}

void podzielwiersz(char data[], int rozmiar)
{
	/*
	 * 1.22
	 */
	char tmp[rozmiar];
	copychararr(tmp, data);

	const int limit = 3;

	int c, in = 0, out = 0, white_char = 0;

	while(in < rozmiar && out < rozmiar && (c = tmp[in]) != C_NUL)
	{
		data[out] = c;

		if(in != 0 && ((in+1) % limit) == 0)
		{
			while(data[out] == C_SPACE || data[out] == C_TAB)
			{
				// ten if else jest do obslugi samych bialych znakow
				// jesli cale linie bialych znakow maja byc zachowane
				// zostawiamy tylko --out
				if(out > 0)
				{
					--out;
				}
				else
				{
					++in;
					white_char = 1;
					break;
				}
			}

			// ten if jest do obslugi samych bialych znakow
			// jesli cale linie bialych znakow maja byc zachowane
			// uwuwamy całość
			if(white_char && out == 0)
			{
				white_char = 0;
				continue;
			}

			++out;
			data[out] = C_NEWLINE;
		}

		++in;
		++out;
	}

	data[out] = C_NUL;

	printchararr(data, rozmiar);
}

void usuwaniekomentarzyc(char data[], int rozmiar)
{
	/*
	 * 1.23
	 */

	int c, in = 0, flaga_koment_start = 0;
	const char pusty = ' ';

	while(in < rozmiar && (c = data[in]) != C_NUL)
	{
		if(c == '/')
		{
			++flaga_koment_start;

			if(flaga_koment_start == 2)
			{
				// komentarz: //
				--in;
				while(data[in] != C_NEWLINE)
				{
					data[in] = pusty;
					++in;
				}
				flaga_koment_start = 0;
			}
		}
		else if(c == '*' && flaga_koment_start == 1)
		{
			// komentarz: /**/

			--in;
			while((in + 1) < rozmiar)
			{
				data[in] = pusty;
				++in;
				if(data[in] == '*' && data[in+1] == '/')
				{
					data[in] = pusty;
					data[in+1] = pusty;
					break;
				}
			}

			flaga_koment_start = 0;
		}
		else
		{
			// inny znak niż oczekiwany / lub *
			// wiec nie bedzie komentarza
			// czyscimy flage
			flaga_koment_start = 0;
		}

		++in;
	}

	printchararr(data, rozmiar);
}

void straznikskladnic(char data[], int rozmiar)
{
	/*
	 * 1.24
	 */
	int c_linia = 0;
	int c_kolumna = 0;
	int c_naw_okragle = 0;
	int c_naw_kwadrat = 0;
	int c_naw_klamra = 0;
	int c_apostrof = 0;
	int c_cudzyslow = 0;

	//int escape_seq = {'\a', '\b', '\e', '\f', '\n', '\r', '\t', '\v', '\\', '\'', '\"', '\?'};

	int c, in = 0;

	char tmp[rozmiar];
	copychararr(tmp, data);

	usuwaniekomentarzyc(tmp, rozmiar);

	while(in < rozmiar && (c = tmp[in]) != C_NUL)
	{
		if(c == C_NEWLINE)
		{
			++c_linia;
			c_kolumna = 0;
		}
		else
		{
			++c_kolumna;
		}

		if(c_cudzyslow % 2 == 0)
		{
			if(c == '(')
				++c_naw_okragle;
			if(c == '[')
				++c_naw_kwadrat;
			if(c == '{')
				++c_naw_klamra;
			if(c == ')')
				--c_naw_okragle;
			if(c == ']')
				--c_naw_kwadrat;
			if(c == '}')
				--c_naw_klamra;
		}

		if(c == '\"')
			if(in > 0 && tmp[in-1] != '\\')
				/*
				 *  zliczamy cudzyslowia rzeczywiscie otwierajace lub zamykajace
				 */
				++c_cudzyslow;
		if(c == '\'')
			if(in > 0 && tmp[in-1] != '\\')
				/*
				 *  zliczamy apostrofy rzeczywiscie otwierajace lub zamykajace
				 */
				++c_apostrof;

		++in;
	}

	printf("Cudzyslowia \"\t %d\t", c_cudzyslow);
	if(c_cudzyslow % 2 == 0)
		printf("OK\n");
	else
		printf("Warning\n");
	printf("Apostrofy \'\t %d\t", c_apostrof);
	if(c_apostrof % 2 == 0)
		printf("OK\n");
	else
		printf("Warning\n");
	printf("Nawiasy )( \t %d\t", c_naw_okragle);
	if(c_naw_okragle == 0)
		printf("OK\n");
	else
		printf("Warning\n");
	printf("Nawiasy ][ \t %d\t", c_naw_kwadrat);
	if(c_naw_kwadrat == 0)
		printf("OK\n");
	else
		printf("Warning\n");
	printf("Nawiasy }{ \t %d\t", c_naw_klamra);
	if(c_naw_klamra == 0)
		printf("OK\n");
	else
		printf("Warning\n");
}

#endif /* CHAPTER_1_DETAB_H_ */
