/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
*
* Analiza si compararea metodelor directe de sortare
*
* Am implementat 3 variante de sortare. Prima metoda de sortare este sortarea bulelor si complexitatea acesteia in cazul mediu statistic este patratica.
* In cazul favorabil(sir ordonat crescator) complexitatea este constanta pentru atribuiri si liniara pentru comparatii si pentru suma lor, iar in cazul defavorabil
* (sir ordonat descrescator) este patratica.
* A doua metoda de sortare implementata este sortarea prin insertie. Complexitatea acesteia in cazul mediu statistic prin insumare este patratica, pentru atribuiri este patratica,
* iar pentru comparatii este liniara. In cazul favorabil(sir ordonat crescator) complexitatea este liniara si pentru atribuiri si pentru comparatii, iar in cazul defavorabil
* (sir ordonat descrescator) este patratica prin insumare, patratica pentru atribuiri si liniara pentru comparatii.
* A treia metoda de sortare implementata este sortarea prin selectie. Complexitatea acesteia in cazul mediu statistic prin insumare este patratica, pentru atribuiri este liniara,
* iar pentru comparatii este patratica. In cazul favorabil(sir ordonat crescator) complexitatea este patratica pentru comparatii si constanta pentru atribuiri si patratica prin insumare,
* iar in cazul defavorabil (sir ordonat descrescator) este patratica prin insumare, liniara pentru atribuiri si patratica pentru comparatii.
* Comparand cele 3 metode de sortare, in cazul mediu statistic, sortarea prin insertie este cea mai eficienta din punct de vedere al sumei si al comparatiilor, iar din punct de vedere
* al atribuirilor cea prin selectie. In cazul favorabil, sortarea bulelor este cea eficienta uitandu-ne la suma, la atribuiri sortarea prin selectie si sortarea bulelor, la comparatii
* sortarea bulelor si sortarea prin insertie. In cazul defavorabil, sortarea prin selectie este mai eficienta la suma si la atribuiri, sortarea prin insertie la comparatii.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler p("Sorting");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5


void bubble_sort(int* a, int n)
{
	Operation op_comp = p.createOperation("bubble-comp", n);
	Operation op_attr = p.createOperation("bubble-attr", n);
	int ok;
	do
	{
		ok = 1;
		for (int i = 0; i < n - 1; i++)
		{
			op_comp.count();
			if (a[i] > a[i + 1])
			{
				op_attr.count();
				int aux = a[i];
				op_attr.count();
				a[i] = a[i + 1];
				op_attr.count();
				a[i + 1] = aux;
				ok = 0;
			}
		}
	} while (ok == 0);
}

void insertion_sort(int* a, int n)
{
	Operation op_comp = p.createOperation("insertion-comp", n);
	Operation op_attr = p.createOperation("insertion-attr", n);
	for (int i = 1; i < n; i++)
	{
		op_attr.count();
		int x = a[i];
		int j = i - 1;
		op_comp.count();
		while (j >= 0 && a[j] > x)
		{
			op_attr.count();
			a[j + 1] = a[j];
			j--;
		}
		op_attr.count();
		a[j + 1] = x;
	}
}

void selection_sort(int* a, int n)
{
	Operation op_comp = p.createOperation("selection-comp", n);
	Operation op_attr = p.createOperation("selection-attr", n);
	for (int i = 0; i < n - 1; i++)
	{
		int imin = i;
		for (int j = i + 1; j < n; j++)
		{
			op_comp.count();
			if (a[j] < a[imin])
				imin = j;
		}
		if (i != imin)
		{
			op_attr.count(3);
			int aux = a[i];
			a[i] = a[imin];
			a[imin] = aux;
		}

	}
}

void print(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}

void demo()
{
	int a[] = { 5, 2, 3, 1, 6 };
	int n = sizeof(a) / sizeof(a[0]);
	int aux1[10], aux2[10];
	for (int i = 0; i < n; i++)
	{
		aux1[i] = a[i];
		aux2[i] = a[i];
	}
	printf("Sortarea bulelor: ");
	bubble_sort(aux1, n);
	print(aux1, n);
	printf("\nSortarea prin insertie: ");
	insertion_sort(aux2, n);
	print(aux2, n);
	printf("\nSortarea prin selectie: ");
	selection_sort(a, n);
	print(a, n);
}

void perf(int order)
{
	int a[MAX_SIZE], aux1[MAX_SIZE], aux2[MAX_SIZE], i;
	for (i = STEP_SIZE; i < MAX_SIZE; i += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(a, i, 10, 50000, false, order);
			for (int k = 0; k < i; k++)
			{
				aux1[k] = a[k];
				aux2[k] = a[k];
			}
			bubble_sort(aux1, i);
			insertion_sort(aux2, i);
			selection_sort(a, i);
		}
	}
	p.divideValues("bubble-comp", NR_TESTS);
	p.divideValues("bubble-attr", NR_TESTS);
	p.addSeries("bubble", "bubble-comp", "bubble-attr");

	p.divideValues("insertion-comp", NR_TESTS);
	p.divideValues("insertion-attr", NR_TESTS);
	p.addSeries("insertion", "insertion-comp", "insertion-attr");

	p.divideValues("selection-comp", NR_TESTS);
	p.divideValues("selection-attr", NR_TESTS);
	p.addSeries("selection", "selection-comp", "selection-attr");

	p.createGroup("attr", "bubble-attr", "insertion-attr", "selection-attr");
	p.createGroup("comp", "bubble-comp", "insertion-comp", "selection-comp");
	p.createGroup("total", "bubble", "insertion", "selection");
}

void perf_all()
{
	perf(UNSORTED);
	p.reset("best");
	perf(ASCENDING);
	p.reset("worst");
	perf(DESCENDING);
	p.showReport();
}

int main() {
	demo();
	//perf_all();
	return 0;
}
