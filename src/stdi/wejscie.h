/*
 * wejscie.h
 *
 *  Created on: Apr 15, 2021
 *      Author: anana
 */

#ifndef STDI_WEJSCIE_H_
#define STDI_WEJSCIE_H_

void czytanie_argv_znaki(int argc, char *argv[])
{
	char c;
	for(int i = 1 ; i < argc ; ++i)
	{
		while((c = *argv[i]++) != '\0')
			printf("%c", c);
		printf(" ");
	}
}

void czytanie_argv_do_tablicy(int argc, char *argv[], char *bufor[])
{
	int i;
	for(i = 1 ; i < argc ; ++i)
	{
		bufor[i-1] = argv[i];
	}
	bufor[i-1] = NULL;
}

void czytanie_std(char *bufor)
{
	/*
	 * zapisuje slowo po znaku nowej lini
	 */
	char c;

	while((c = getchar()) != '\n')
		*bufor++ = c;
	*bufor++ = '\0';
}

void czytanie_std_do_tablicy(char *bufor[])
{
	static const int rr = 100;
	char c, buf[rr];
	int i = 0;

	while( !isspace((c = getchar())) && i < rr)
		buf[i++] = c;
	buf[i] = '\0';
	if(c == EOF)
		*bufor-- = NULL;
}

#define RR 100

void test_czytanie()
{
	char buf2[RR];
	czytanie_std(buf2);
	printf("%s", buf2);
}

void test_czytanie_do_tablicy(int argc, char *argv[])
{
	char *buf[RR];
	czytanie_argv_do_tablicy(argc, argv, buf);
	for(int i = 0 ; i < RR && *(buf+i) != NULL ; i++)
		printf("%s\n",*(buf+i));
}

#endif /* STDI_WEJSCIE_H_ */
