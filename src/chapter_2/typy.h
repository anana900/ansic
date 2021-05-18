/*
 * typy.h
 *
 *  Created on: Mar 5, 2021
 *      Author: anana
 */

#ifndef CHAPTER_2_TYPY_H_
#define CHAPTER_2_TYPY_H_

#define BITS(x) (sizeof(x) * 8)

void rozmiaryzmiennych()
{
	/*
	 * 2.1
	 */
	char c;
	unsigned char uc;
	signed char sc;

	short s; // domyslnie typ int
	long l; // domyslnie typ int

	int i;
	unsigned int ui;
	signed int si;
	unsigned long int uli;
	unsigned short int usi;
	signed long int sli;
	signed short int ssi;

	float f;

	double d;
	long double ld;

	int max = 0;
	int min = 0;

	min = -(1LLU << (BITS(double)));
	max = (1LLU << (BITS(double)))-1;
	printf("min %llu \n", min);
	printf("max %llu \n", max);

	printf("char\t%d \n", sizeof(char));
	printf("unsigned char\t%d \n", sizeof(uc));
	printf("signed char\t%d \n", sizeof(sc));

	printf("short\t%d \n", sizeof(s));
	printf("long\t%d \n", sizeof(l));

	printf("int\t%d \n", sizeof(i));
	printf("int\t%d \n", sizeof(ui));
	printf("int\t%d \n", sizeof(si));
	printf("int\t%d \n", sizeof(uli));
	printf("int\t%d \n", sizeof(usi));
	printf("int\t%d \n", sizeof(sli));
	printf("int\t%d \n", sizeof(ssi));

	printf("float\t%d \n", sizeof(f));
	printf("double\t%d \n", sizeof(d));
	printf("long double\t%d \n", sizeof(ld));

}

int powerf(int l, int p)
{
	if(p == 0)
		return 1;
	else
		return (l * powerf(l, --p));
}

int htoi(char liczba[], int rozmiar)
{
	/*
	 * 2.3
	 * do poprawy wybieranie podstringow!!
	 */

	int c, i = 0, iterator_ciag_hex = 0, flaga_gotowe = 0;
	char hex[rozmiar];

	while(i < rozmiar && (c = liczba[i]) != '\0')
	{

		if((c <= '9' && c >= '0') || (c <='F' && c >= 'A') || (c <= 'f' && c >= 'a'))
		{
			if( 0 == iterator_ciag_hex && '0' == c )
			{
				if(i > 0 && (liczba[i-1] == 'x' || liczba[i-1] == 'X'))
				{
					// 0x lub 0X
					++i;
					continue;
				}
			}

			if(!flaga_gotowe && '0' == c && i + 1 < rozmiar && (liczba[i+1] == 'x' || liczba[i+1] == 'X'))
			{
				flaga_gotowe = 1;
				--i;	// cofniecie o 1 gdyż 0 juz nie nalezy do liczby a bedzie potrzeben do detekcji startu
				continue;
			}

			hex[iterator_ciag_hex] = c;
			++iterator_ciag_hex;
		}
		else if(iterator_ciag_hex)
		{
			flaga_gotowe = 1;
		}

		if(flaga_gotowe)
		{
			flaga_gotowe = 0;
			printf("%s ", hex);

			int liczba = 0, n = 0;
			for(int k = iterator_ciag_hex - 1 ; k >= 0 ; --k, ++n)
			{
				c = hex[k];

				if(c <= '9' && c >= '0')
				{
					liczba = liczba + powerf(16,n) * (c - '0');
				}
				else if(c <='F' && c >= 'A')
				{
					liczba = liczba + powerf(16,n) * (c - 55);
				}
				else if(c <= 'f' && c >= 'a')
				{
					liczba = liczba + powerf(16,n) * (c - 87);
				}
			}
			iterator_ciag_hex = 0;
			printf("Wynik: %d \n", liczba);
		}

		++i;
	}

	return 1;
}

void operatoryporownania(int lim)
{
	/*
	 * 2.2
	 */
	char s[lim];
	int c, i;
//	for(i=0 ; i < lim - 1 && (c = getchar()) != '\n' && c!= EOF ; ++i)
//	{
//		s[i] = c;
//	}

	for(i=0 ; i < lim - 1 ; ++i)
	{
		if((c = getchar()) != '\n')
		{
			if(c != EOF)
			{
				s[i] = c;
			}
			else
			{
				break;
			}
		}
		else
		{
			break;
		}
	}
}

void charremover(char wynik[], char usun[])
{
	/*
	 * 2.4
	 */
	int c, i, j, u = 0;

	while((c = usun[u++]) != '\0')
	{
		for(i = 0, j = 0 ; wynik[i] != '\0' ; ++i)
		{
			if(c != wynik[i])
			{
				wynik[j++] = wynik[i];
			}
		}
		wynik[j] = '\0';
	}

	printf("%s ", wynik);
}

int anychar(char wynik[], char usun[])
{
	/*
	 * 2.5
	 */
	int c, i, j, u = 0;

	while((c = usun[u++]) != '\0')
	{
		for(i = 0, j = 0 ; wynik[i] != '\0' ; ++i)
		{
			if(c == wynik[i])
			{
				return i;
			}
		}
		wynik[j] = '\0';
	}

	return -1;
}

#endif /* CHAPTER_2_TYPY_H_ */
