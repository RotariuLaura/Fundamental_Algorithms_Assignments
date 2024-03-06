/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
*
* Analiza si compararea a doua metode de construire a structurii de date Heap, implementarea Heapsort
*
* Am implementat metodele bottom-up si top-down de construire a unui heap. Complexitatea primei metode am observat ca este liniara-O(n).
* In cazul defavorabil(cand sirul este sortat crescator), complexitatea este liniara-O(n).
* Am implementat algoritmul heapsort si am demonstrat corectitudinea acestuia pe un vector de dimensiuni mici.
* La metoda top-down complexitatea este O(n log n) in cazul mediu statistic si liniara-O(n) in cazul defavorabil(cand sirul este sortat crescator).
* Comparand cele 2 metode de construire a unui heap, am observat ca cea bottom-up este mai eficienta si in cazul mediu statistic si in cel defavorabil, numarul de operatii
* la metoda top-down fiind mult mai mare in ambele cazuri fata de cel de la metoda bottom-up.
*/

#include <stdio.h>
#include "Profiler.h"

#define left(i) (2*i+1)
#define right(i) (2*i+2)
#define parent(i) ((i-1)/2)

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

Profiler p("Heap");

void maxHeapify(int* a, int n, int i)
{
	Operation op_BottomUp = p.createOperation("BuildHeap_BottomUp", n);
	int max = i;
	int l = left(i);
	int r = right(i);
	if (l < n) {
		op_BottomUp.count();
		if (a[l] > a[max])
		{
			max = l;
		}
	}
	if (r < n)
	{
		op_BottomUp.count();
		if (a[r] > a[max])
		{
			max = r;
		}
	}
	if (max != i)
	{
		op_BottomUp.count();
		int aux = a[i];
		op_BottomUp.count();
		a[i] = a[max];
		op_BottomUp.count();
		a[max] = aux;
		maxHeapify(a, n, max);
	}
}

void buildMaxHeapBottomUp(int* a, int n)
{
	int j = (n / 2) - 1;
	for (int i = j; i >= 0; i--)
	{
		maxHeapify(a, n, i);
	}
}

void heapsort(int* a, int n)
{
	buildMaxHeapBottomUp(a, n);
	for (int i = n - 1; i >= 0; i--)
	{
		int aux = a[0];
		a[0] = a[i];
		a[i] = aux;
		n = n - 1;
		maxHeapify(a, n, 0);
	}
}

int heap_size;

void heapIncreaseKey(int* a, int n, int i, int key)
{
	Operation op_TopDown = p.createOperation("BuildHeap_TopDown", n);
	if (key < a[i])
	{
		printf("Cheia noua este mai mica decat cheia curenta.");
	}
	a[i] = key;
	while (i > 0 && a[parent(i)] < a[i])
	{
		op_TopDown.count(4);
		int aux = a[parent(i)];
		a[parent(i)] = a[i];
		a[i] = aux;
		i = parent(i);
	}
	if (i > 0)
		op_TopDown.count();
}

void maxHeapInsert(int* a, int n, int key)
{
	heap_size++;
	a[heap_size] = -192726382;
	heapIncreaseKey(a, n, heap_size, key);

}

void buildMaxHeapTopDown(int* a, int n)
{
	heap_size = 0;
	for (int i = 1; i < n; i++)
		maxHeapInsert(a, n, a[i]);
}

void printHeap(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
}

void demo()
{
	int a[] = { 2, 4, 8, 3, 10 }, aux1[10], aux2[10];
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n; i++)
	{
		aux1[i] = a[i];
		aux2[i] = a[i];
	}
	printf("Construirea heap-ului prin metoda bottom-up: ");
	buildMaxHeapBottomUp(a, n);
	printHeap(a, n);
	printf("\nHeapsort: ");
	heapsort(aux1, n);
	printHeap(aux1, n);
	printf("\nConstruirea heap-ului prin metoda top-down: ");
	buildMaxHeapTopDown(aux2, n);
	printHeap(aux2, n);
}

void perf_average()
{
	int a[MAX_SIZE], aux[MAX_SIZE], i;
	for (i = STEP_SIZE; i < MAX_SIZE; i += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(a, i);
			for (int k = 0; k < i; k++)
			{
				aux[k] = a[k];
			}
			buildMaxHeapBottomUp(a, i);
			buildMaxHeapTopDown(aux, i);
		}
	}
	p.divideValues("BuildHeap_BottomUp", NR_TESTS);
	p.divideValues("BuildHeap_TopDown", NR_TESTS);
	p.createGroup("BuildHeap-Average", "BuildHeap_BottomUp", "BuildHeap_TopDown");
	//p.showReport();
}

void perf_worst()
{
	p.reset("worst");
	int a[MAX_SIZE], aux[MAX_SIZE], i;
	for (i = STEP_SIZE; i < MAX_SIZE; i += STEP_SIZE)
	{
		FillRandomArray(a, i, 10, 50000, true, 1);
		for (int k = 0; k < i; k++)
		{
			aux[k] = a[k];
		}
		buildMaxHeapBottomUp(a, i);
		buildMaxHeapTopDown(aux, i);
	}
	p.createGroup("BuildHeap-Worst", "BuildHeap_BottomUp", "BuildHeap_TopDown");
	p.showReport();
}

int main()
{
	//demo();
	perf_average();
	perf_worst();
	return 0;
}