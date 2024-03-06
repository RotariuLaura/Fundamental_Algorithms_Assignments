/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
*
* Inserarea si cautarea in tabele de dispersie
*
* Am implementat functiile de inserare si cautare intr-o tabela de dispersie ce foloseste adresarea deschisa cu verificare patratica.
* La operatia de inserare in tabela de dispersie, ideea este ca se adauga o cheie, verificandu-se pozitiile din tabela cu functia h_quadratic_probing pana cand una este
* goala, si se returneaza pozitia la care a fost inserata sau -1 daca tabela este plina. La operatia de cautare, se verifica pozitiile din tabela la fel ca la inserare 
* pana cand se gaseste elementul sau null deoarece acolo ar fi trebuit inserat elementul si se returneaza pozitia sau -1 daca nu a fost gasit. 
* Am demonstrat corectitudinea operatiilor de inserare si cautare pe doua exemple cu o tabela de dispersie de dimensiuni 20, respectiv 100 si factor de umplere 95%.
* Am evaluat operatia de cautare in cazul mediu statistic: am ales dimensiunea tabelei 9973 si am inserat elemente aleator in tabela astfel incat factorul de umplere sa 
* fie pe rand 0.8, 0.85, 0.9, 0.95, 0.99 si am cautat 3000 de elemente in fiecare caz (1500 gasite si 1500 negasite) si am determinat efortul mediu si efortul maxim
* pentru gasirea elementelor. Am implementat din nou functia de cautare si am numarat cate celule sunt accesate pana cand elementul este gasit pentru a masura efortul.
* Pentru a ma asigura ca cele 1500 de elemente gasite sunt generate uniform, am inserat din 5 in 5 elemente din tabela intr-un nou vector si le-am cautat. Pentru a ma
* asigura ca 1500 nu sunt gasite am inserat intr-un vector nou elemente dintr-un interval diferit de cel initial si le-am cautat in tabela.
*/ 

#include <stdio.h>
#include "Profiler.h"

#define NR_TESTS 5
int N = 9973;

typedef struct
{
	int key;
	char name[30];
}Entry;

int h(int k, int m)
{
	return k % m;
	return 0;
}

int h_quadratic_probing(int k, int m, int i)
{
	return (h(k, m) + i + i * i) % N;
	return 0;
}

void print(Entry* T)
{
	printf("\nTabela de dispersie:\n");
	for (int i = 0; i < N; i++)
	{
		if (T[i].key)
		{
			printf("T[%d]=%d\n", i, T[i].key);
		}
		else
		{
			printf("T[%d]=--\n", i);
		}
	}
}

void freeTable(Entry* T)
{
	for (int i = 0; i < N; i++)
	{
		T[i].key = NULL;
		strcpy_s(T[i].name, "FREE");
	}
}

int hashInsert(Entry* T, int k)
{
	int i = 0, j;
	do
	{
		j = h_quadratic_probing(k, N, i);
		if (T[j].key == NULL)
		{
			T[j].key = k;
			strcpy_s(T[i].name, "OCCUPIED");
			return j;
		}
		else
		{
			i++;
		}
	} while (i < N);
	return -1;
}

int hashSearch(Entry* T, int k)
{
	int i = 0, j;
	do
	{
		j = h_quadratic_probing(k, N, i);
		if (T[j].key == k)
		{
			return j;
		}
		i++;
	} while (T[j].key != NULL && i != N);
	return -1;
}

int hashSearch_effort(Entry* T, int k)
{
	int cnt = 0;
	int i = 0, j;
	do
	{
		j = h_quadratic_probing(k, N, i);
		cnt++;
		if (T[j].key == k)
		{
			break;
		}
		i++;
	} while (T[j].key != NULL && i != N);
	return cnt;
}

void demo()
{
	N = 20;
	Entry* T = (Entry*)malloc(N * sizeof(Entry));
	freeTable(T);
	int n = 19;
	double alfa = n / (double)N;
	alfa *= 100;
	printf("Factorul de umplere %.0f%c", alfa, '%');
	int a[] = { 19,36,5,21,4,26,14,17, 1, 10, 12, 14, 30, 6,2, 3, 11,7,13 };
	for (int i = 0; i < n; i++)
	{
		hashInsert(T, a[i]);
	}
	print(T);
	printf("Cautarea in tabela:\n");
	for (int i = 0; i < n; i++)
	{
		int p = hashSearch(T, a[i]);
		if (p != -1)
		{
			printf("%d pe pozitia %d\n", a[i], p);
		}
		else
		{
			printf("Elementul %d nu a fost gasit\n", a[i]);
		}
	}
	int p = hashSearch(T, 15);
	if (p != -1)
	{
		printf("15 pe pozitia %d\n", p);
	}
	else
	{
		printf("15 nu a fost gasit\n");
	}
}

void demo2(int n)
{
	N = 100;
	Entry* T = (Entry*)malloc(N * sizeof(Entry));
	freeTable(T);
	double alfa = (double)n / (double)N;
	printf("Factorul de umplere %.2f\n", alfa);
	int a[100];
	FillRandomArray(a, n, 0, 200, true, 0);
	for (int i = 0; i < n; i++)
	{
		hashInsert(T, a[i]);
	}
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	print(T);
	for (int i = 0; i < n; i++)
	{
		int p = hashSearch(T, a[i]);
		if (p != -1)
		{
			printf("%d pe pozitia %d\n", a[i], p);
		}
		else
		{
			printf("Elementul %d nu a fost gasit\n", a[i]);
		}
	}
}

void perf(int n)
{
	Entry* T = (Entry*)malloc(N * sizeof(Entry));
	freeTable(T);
	double alfa = (double)n / (double)N;
	int	efort_total_gasite = 0, efort_maxim_gasite = 0, efort_total_negasite = 0, efort_maxim_negasite = 0;
	for (int test = 0; test < NR_TESTS; test++)
	{
		int a[9973];
		FillRandomArray(a, n, 0, 10000, true, 0);
		for (int i = 0; i < n; i++)
		{
			hashInsert(T, a[i]);
		}
		int aux[3000];
		int nr = 0;
		for (int k = 0; k < n; k += 5)
		{
			aux[nr++] = a[k];
		}
		for (int cnt = 0; cnt < 1500; cnt++)
		{
			int efort = hashSearch_effort(T, aux[cnt]);
			efort_total_gasite += efort;
			if (efort > efort_maxim_gasite)
			{
				efort_maxim_gasite = efort;
			}
		}
		FillRandomArray(a, 1500, 10001, 12000, true, 0);
		for (int cnt = 0; cnt < 1500; cnt++)
		{
			int efort = hashSearch_effort(T, a[cnt]);
			efort_total_negasite += efort;
			if (efort > efort_maxim_negasite)
			{
				efort_maxim_negasite = efort;
			}
		}
	}
	double efort_mediu_gasite = (double)efort_total_gasite / (double)n;
	efort_mediu_gasite /= 5.0f;
	double efort_mediu_negasite = (double)efort_total_negasite / (double)n;
	efort_mediu_negasite /= 5.0f;
	printf("\n%10.2f %20.2f %20d %20.2f %20d \n", alfa, efort_mediu_gasite, efort_maxim_gasite, efort_mediu_negasite, efort_maxim_negasite);
}

int main()
{
	//Inserare si cautare in tabela de dispersie demonstratie pe factor de umplere 95%
	demo();
	//demo2(95);
	//Inserare si cautare in tabela de dispersie evaluare
	N = 9973;
	printf("\nFactor de umplere | Efort mediu gasite | Efort maxim gasite | Efort mediu negasite | Efort maxim negasite");
	//Factorul de umplere 0.8
	perf(7978);
	//Factorul de umplere 0.85
	perf(8477);
	//Factorul de umplere 0.9
	perf(8976);
	//Factorul de umplere 0.95
	perf(9474);
	//Factorul de umplere 0.99
	perf(9873);
	return 0;
}