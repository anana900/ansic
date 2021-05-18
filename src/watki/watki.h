/*
 * watki.h
 *
 *  Created on: Apr 12, 2021
 *      Author: anana
 *
 * Zrodlo: http://jedrzej.ulasiewicz.staff.iiar.pwr.wroc.pl/SystemyCzasuRzeczywistego/wyklad/W%B9tki25.pdf
 *
 */

#ifndef WATKI_WATKI_H_
#define WATKI_WATKI_H_

/*
 * POSIX P1003.4a (Portable Operating System Interface)
 *
 * W linux są 2 biblioteki dot wątów:
 * 1 - LinuxThreads - początkowa bibliteka
 * 2 - NPTL - Native Posix Threads Library - bardziej zgodna ze standardem Posix
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep

/*
 * Tworzenie i kończenie wątków:
 * pthread_create Tworzenie wątku
 * pthread_exit Jawne zakończenie wątku bieżącego
 * pthread_join Czekanie na zakończenie wątku
 * pthread_attr_init Inicjacja atrybutów wątku
 * pthread_self Pobranie identyfikatora wątku
 * pthread_yield Zwolnienie procesora
 * pthread_cancel Kasowanie innego wątku
 */


/*
 * ##### 001 Podstawy ##########################################################
 */
int losowa(int l, int t)
{
	srand(time(0));
	return (rand() % (t - l + 1)) + l;
}

void * funkcja_watek(void * arg)
{
	int czekam = losowa(1,3);
	int myid = (int)arg;
	sleep(czekam);
	printf("W watku %d czekalem %d \n", myid, czekam);
	pthread_exit(NULL);
	//return NULL;
}

void watki_podstawy_tworzenie()
{
	printf("Watek glowny, przed wątkami \n");

	pthread_t watek_id[4];
	for(int i=0 ; i < 4 ; i ++)
	{
		pthread_create(&watek_id[i], NULL, funkcja_watek, (void *)(i+1));
		//pthread_join(watek_id[i], NULL);
	}

	for(int i=0 ; i< 4 ; ++i)
	{
		sleep(1);
		printf("Watek glowny, czekam 1s\n");
	}

	printf("Watek glowny, po wykonaniu wszystkich watkow\n");
}

/*
 * ##### 002 Atrybuty ##########################################################
 */
void watki_podstawy_atrybuty()
{
	/*
	 * Atrybut 					Funkcja testowania 		Funkcja ustawiania
	 * Dołączalność				attr_getdetachstate() 	attr_settdetachstate()
	 * Strategia szeregowania	attr_getschedpolicy() 	attr_setschedpolicy()
	 * Parametry szeregowania	attr_getschedparam() 	attr_setschedparam()
	 * Rozmiar stosu			attr_getstacksize(),	attr_setstacksize()
	 * 							attr_getstacklazy(),	attr_setstacklazy()
	 * Adres stosu 				attr_getstackaddr() 	attr_setstackaddr()
	 */

	printf("Watek glowny, przed wątkami %lu\n", pthread_self());

	int status;
	struct sched_param param;
	pthread_attr_t watek_atrybuty;

	if(pthread_attr_init(&watek_atrybuty) == -1)
	{
		printf("Error inicjalizacja atrybutów watku\n");
		exit(1);
	}

	pthread_attr_setdetachstate(&watek_atrybuty, PTHREAD_CREATE_DETACHED);
	printf("Watek glowny,attr_getdetachstate() %d\n", \
			pthread_attr_getdetachstate(&watek_atrybuty, &status));
	printf("Watek glowny,attr_getschedpolicy() %d\n", \
			pthread_attr_getschedpolicy(&watek_atrybuty, &status));
	printf("Watek glowny,attr_getschedparam() %d\n", \
			pthread_attr_getschedparam(&watek_atrybuty, &param));

	pthread_t watek_id[4];
	for(int i=0 ; i < 4 ; i ++)
	{
		pthread_create(&watek_id[i], &watek_atrybuty, funkcja_watek, (void *)(i+1));
		//pthread_join(watek_id[i], NULL);
	}

	for(int i = 0 ; i < 4 ; ++i)
	{
		sleep(1);
		printf("Watek glowny, czekam 1s\n");
	}

	pthread_attr_destroy(&watek_atrybuty);
	printf("Watek glowny, po wykonaniu wszystkich watkow\n");
}

/*
 * ##### 003 Przekazywanie parametrow ############################################
 */

typedef struct {
	int poczatek;
	int koniec;
	int numer;
} watek_arg_struct;

void * znajdz(void *arg)
{
	sleep(2);
	int x, y, num, ret;
	watek_arg_struct *par;
	par = (watek_arg_struct *) arg;
	x = par->poczatek;
	y = par->koniec;
	num = par->numer;
	printf("Watek: %d %d %d \n", x, y, num);
	ret = x + y +num;
	return ((void *) ret);
}

void watki_podstawy_przekazywanie_parametrow()
{
	/*
	 * Zeby przekazać więcej niż 1 parametr kożystamy:
	 * - struktury
	 * - tablicy
	 *
	 * Wątek zwraca wskaźnik na void na 2 sposoby:
	 * - return ret
	 * - pthread_exit((void *) ret)
	 * Zwracana wartość może być odczytana w pthread_join
	 * w jej 2 parametrze
	 */
	printf("Watek glowny, przed wątkami \n");
	watek_arg_struct data1;

	pthread_t watek_id[4];
	for(int i = 0 ; i < 4 ; ++i)
	{
		data1.koniec = 1+i;
		data1.poczatek = -1*i;
		data1.numer = 2343%(i+22);
		pthread_create(&watek_id[i], NULL, znajdz, (void *)&data1);
		sleep(1); // bez tego sleepa wszystkie watki maja takie same dane
		//pthread_join(watek_id[i], NULL);
	}

	// Czekanie na koniec
	int wynik;
	for(int i=0 ; i< 4 ; ++i)
	{
		sleep(1);
		printf("Watek glowny, czekam 1s\n");
		pthread_join(watek_id[i], (void *)&wynik);
		printf("W: %d \n",wynik);
	}

	printf("Watek glowny, po wykonaniu wszystkich watkow\n");
}

/*
 * Zakończenie wątku:
 * 1 sam:
 * - return
 * - pthread_exit
 * 2 inny watek:
 * - pthread_cancel
 *
 * przydaje się do czyszczenia zaosobów po zatrzymanym wątku.
 * - pthread_cleanup_push
 * - pthread_cleanup_pop
 */

/*
 * ##### 004 MUTEX ##########################################################
 * http://jedrzej.ulasiewicz.staff.iiar.pwr.wroc.pl/KomputeroweSystSter/wyklad/Synchronizacja15.pdf
 */
#include "../kolejka/kolejkafifo.h"

#define ROZMIAR 5
struct kolejka_t *bufor;

pthread_t pis, czy, pis2, czy2, czy3;
pthread_mutex_t mutex;

void *pisanie(void *arg);
void *czytanie(void *arg);

void watki_dostep_do_wspolnych_danych_mutex()
{
	/*
	 * ochrona przed jednoczesnym kożystaniem ze wspólnych danych
	 * MUTEX - od MUTual EXlusion - wzajemne wykluczenie
	 *
	 * pthread_mutex_init Inicjacja muteksu
	 * pthread_mutex_lock Zajęcie muteksu
	 * Pthread_mutex_timedlock Zajęcie muteksu – czekanie ograniczone czasowo
	 * pthread_mutex_unlock Zwolnienie muteksu
	 * pthread_mutex_destroy Skasowanie muteksu
	 *
	 * MUTEX na przykładzie problemu producenta - konsumenta.
	 * Rozwiązanie z odpytywaniem.
	 */

	bufor = kolejka_inicjalozacja(ROZMIAR);

	printf("Teraz watek glowny create:\n");
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&pis, NULL, pisanie, NULL);
	pthread_create(&czy, NULL, czytanie, NULL);
/*	pthread_create(&pis2, NULL, pisanie, NULL);
	pthread_create(&czy2, NULL, czytanie, NULL);
	pthread_create(&czy3, NULL, czytanie, NULL);*/
	//pthread_join(pis, NULL);
	//pthread_join(czy, NULL);

	// wypisywanei przez watek glowny zajetosci kolejki
	int ostatnie_zajete = 0;
	while(1)
	{
		if(bufor->zajete != ostatnie_zajete)
		{
			ostatnie_zajete = bufor->zajete;
			pthread_mutex_lock(&mutex);
			printf("MAIN: elementy w kolejce %d ", ostatnie_zajete);
			for(int i = 0 ; i < ostatnie_zajete ; ++i)
				printf("-");
			printf("\n");
			pthread_mutex_unlock(&mutex);
		}
	}

	printf("Teraz watek glowny\n");
}

void *pisanie(void* arg)
{
	while(1)
	{
		sleep(0.01 * losowa(30,70));

		pthread_mutex_lock(&mutex);
		dodaj_element(bufor, losowa(1,1000));
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void *czytanie(void* arg)
{
	while(1)
	{
		sleep(0.01 * losowa(30,72));

		pthread_mutex_lock(&mutex);
		pobierz_element(bufor);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

/*
 * ##### 005 ZMIENNE WARUNKOWE ###################################################
 *
 * Muteksy są narzędziem zapewniającym ochronę sekcji krytycznej.
 * Jak postąpić gdy wewnątrz sekcji krytycznej wymagane jest oczekiwanie
 * na spełnienie pewnego warunku a więc synchronizacja z innym wątkiem.
 *
 * Zmienna warunkowa deklaracja: pthreads_cond_t
 *
 * pthread_cond_init Inicjacja zmiennej warunkowej.
 * pthread_cond_wait Czekanie na zmiennej warunkowej
 * pthread_cond_timedwait Czekanie na zmiennej warunkowej z przeterminowaniem
 * pthread_cond_signal Wznowienie wątku zawieszonego na zmiennej warunkowej.
 * pthread_cond_brodcast Wznowienie wszystkich wątków zawieszonych w kolejce danej zmiennej warunkowej.
 * pthread_cond_destroy Skasowanie zmiennej warunkowej z zwolniene jej zasobów.
 */
void *producent(void* arg);
void *konsument(void* arg);

pthread_cond_t bufor_pusty;
pthread_cond_t bufor_zapelniony;

void watki_zmienna_warunkowa()
{
	/*
	 * Problem producenta konsumenta
	 * Dodatkowo zmienna warunkowa zatrzymyje proces gdy pusta lub pelna kolejka.
	 */
	printf("Teraz watek glowny create:\n");

	bufor = kolejka_inicjalozacja(ROZMIAR);

	pthread_mutex_init(&mutex, NULL);

	pthread_cond_init(&bufor_pusty,NULL);
	pthread_cond_init(&bufor_zapelniony,NULL);

	pthread_create(&pis, NULL, producent, NULL);
	pthread_create(&czy, NULL, konsument, NULL);

	// wypisywanei przez watek glowny zajetosci kolejki
	int ostatnie_zajete = 0;
	while(1)
	{
		if(bufor->zajete != ostatnie_zajete)
		{
			ostatnie_zajete = bufor->zajete;
			pthread_mutex_lock(&mutex);
			printf("MAIN: elementy w kolejce %d ", ostatnie_zajete);
			for(int i = 0 ; i < ostatnie_zajete ; ++i)
				printf("-");
			printf("\n");
			pthread_mutex_unlock(&mutex);
		}
	}

	printf("Teraz watek glowny\n");
}

void *producent(void* arg)
{
	while(1)
	{
		sleep(0.01 * losowa(30,70));

		pthread_mutex_lock(&mutex);
		if(bufor->zajete >= bufor->rozmiar)
			pthread_cond_wait(&bufor_zapelniony, &mutex);
		dodaj_element(bufor, losowa(1,1000));
		pthread_cond_signal(&bufor_pusty);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void *konsument(void* arg)
{
	while(1)
	{
		sleep(0.01 * losowa(30,72));

		pthread_mutex_lock(&mutex);
		if(bufor->zajete <= 0)
			pthread_cond_wait(&bufor_pusty, &mutex);
		pobierz_element(bufor);
		pthread_cond_signal(&bufor_zapelniony);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

/*
 * ##### 006 BLOKADY CZYTELNIKOW PISARZY ################################
 *
 * pthread_rwlock_init inicjalizacja
 * pthread_rwlock_rdlock zalozenie blokady do odczytu
 * pthread_rwlock_wrlock zalozenie blokady do zapisu
 * pthread_rwlock_unlock zdjecie blokady do zapisu/odczytu
 */


/*
 * ##### 007 BARIERY ####################################################
 *
 * służą do synchr procesów w ramach grup.
 * Blokowanie grupy watkuw dopuki okreslona liczba
 * nie bedzie czekac na wykonanie zadania.
 *
 * pthread_barrier_init (pthread_barrier_t, pthread_barrierattr_t, unsigned int)
 * pthread_barrier_wait - blokuje watek na barierze, gdy inne watki zblokuja sie
 * i ich suma bedzie odpowiednia, nastapisodblokowanie
 *
 */



/*
 * ##### 008 WIRUJACE BLOKADY ############################################
 *
 * tak jak MUTEXY zabezpieczaja czesc krytyczna.
 * NIE MA PRZELACZANIA KONTEKSTU. Wir blokady sa aktywne, czekanie.
 */


/*
 * ##### 009 Watki w srodowiku wieloprocesorowym ##########################
 *
 */

/*
 * ##### 010 Suspend Continue #############################################
 *
 * pthread_suspend - zawiedzenie watku
 * pthread_continue - kontynuacja watku
 */

/*
 * ##### 011 SEMAFORY #####################################################
 *
 *
 */

#endif /* WATKI_WATKI_H_ */
