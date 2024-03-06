/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
*
* Analiza si compararea metodelor avansate de sortare QuickSort si HeapSort, compararea dintre bubble sort versiunea iterativa si cea recursiva
*
* Am implementat metoda de sortare rapida-Quicksort. Pentru implementarea acesteia am folosit functia partition. Se alege ca pivot ultimul element din sir si se partitioneaza
* sirul in functie de acest pivot astfel incat elementele mai mici decat el sunt in stanga si cele mai mari decat el in dreapta acestuia si se aduce pivotul in pozitia corecta.
* Se apeleaza recursiv functia QuickSort pentru a ordona cele doua parti din sir. Complexitatea QuickSort in cazul mediu statistic este O(n log n).
* In cazul defavorabil(cand sirul este sortat crescator sau descrescator), complexitatea Quicksort este patratica-O(n^2) deoarece se alege ca pivot cel mai mic, respectiv cel mai mare
* element. Pentru cazul favorabil(cand pivotul este mijlocul sirului si sirul este sortat crescator), am implementat functia partition_bestCase in care am ales ca si pivot mijlocul
* sirului, iar complexitatea este O(n log n).
* Am implementat metoda de sortare Heapsort si am comparat-o cu Quicksort in cazul mediu statistic si am observat ca Quicksort este mai eficienta. Pentru implementarea HeapSort
* am folosit functiile maxHeapify si buildMaxHeap. Acest algoritm de sortare presupune construirea unui max heap dintr-un sir prin metoda bottom-up, apoi sortarea acestuia
* prin interschimbarea succesiva a ultimului element cu primul, apoi eliminarea ultimului element prin decrementarea dimensiunii heap-ului si aplicarea
* maxHeapify pe primul nod pentru a se pastra proprietatea de heap. Complexitatea Heapsort este 0(n).
* Am implementat metoda bulelor in varianta iterativa si recursiva si am facut analiza din punct de vedere al numarului de operatii si al timpului de rulare.
* Complexitatea pentru metoda bulelor este O(n^2). Din punct de vedere al numarului de operatii, varianta iterativa este mai eficienta.
* De asemenea, din punct de vedere al timpului de rulare, varianta iterativa este mai eficienta.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

#define MAX_SIZE 8000
#define STEP_SIZE 100
#define NR_TESTS 5

#define left(i) (2*i+1)
#define right(i) (2*i+2)

Profiler p("Sorting");

int array_size;

int partition(int* a, int m, int n)
{
	Operation op_QuickSort = p.createOperation("QuickSort", array_size);
	int pivot = a[n];
	int i = m - 1;
	for (int j = m; j < n; j++)
	{
		op_QuickSort.count();
		if (a[j] <= pivot)
		{
			i++;
			op_QuickSort.count(3);
			int aux = a[j];
			a[j] = a[i];
			a[i] = aux;
		}
	}
	op_QuickSort.count(3);
	int aux2 = a[i + 1];
	a[i + 1] = a[n];
	a[n] = aux2;
	return i + 1;
}

int partition_bestCase(int* a, int m, int n)
{
	Operation op_QuickSort_bestcase = p.createOperation("QuickSort-bestCase", array_size);
	int i = (m + n) / 2;
	int pivot = a[i];
	int l = m, r = n;
	while (l <= r)
	{
		op_QuickSort_bestcase.count();
		while (a[l] < pivot)
		{
			l++;
		}
		op_QuickSort_bestcase.count();
		while (a[r] > pivot)
		{
			r--;
		}
		if (l <= r)
		{
			op_QuickSort_bestcase.count(3);
			int aux = a[l];
			a[l] = a[r];
			a[r] = aux;
			l++;
			r--;
		}
	}
	return l;
}

void quickSort(int* a, int m, int n)
{
	if (m < n)
	{
		int p;
		p = partition(a, m, n);
		quickSort(a, m, p - 1);
		quickSort(a, p + 1, n);

	}
}

void quickSort_bestCase(int* a, int m, int n)
{
	if (m < n)
	{
		int p;
		p = partition_bestCase(a, m, n);
		quickSort_bestCase(a, m, p - 1);
		quickSort_bestCase(a, p, n);
	}
}

void maxHeapify(int* a, int n, int i)
{
	Operation op_HeapSort = p.createOperation("HeapSort", array_size);
	int max = i;
	int l = left(i);
	int r = right(i);
	if (l < n)
	{
		op_HeapSort.count();
		if (a[l] > a[max])
		{
			max = l;
		}
	}
	if (r < n)
	{
		op_HeapSort.count();
		if (a[r] > a[max])
		{
			max = r;
		}
	}
	if (max != i)
	{
		op_HeapSort.count(3);
		int aux = a[i];
		a[i] = a[max];
		a[max] = aux;
		maxHeapify(a, n, max);
	}
}

void builMaxHeap(int* a, int n)
{
	for (int i = (n / 2) - 1; i >= 0; i--)
	{
		maxHeapify(a, n, i);
	}
}

void heapSort(int* a, int n)
{
	builMaxHeap(a, n);
	for (int i = n - 1; i >= 0; i--)
	{
		p.countOperation("HeapSort", array_size, 3);
		int aux = a[0];
		a[0] = a[i];
		a[i] = aux;
		n = n - 1;
		maxHeapify(a, n, 0);
	}
}

void bubble_sort_iterative(int* a, int n)
{
	Operation op_bubble_i = p.createOperation("BubbleSort-iterative", array_size);
	int ok = 1;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			op_bubble_i.count();
			if (a[i] > a[j])
			{
				op_bubble_i.count(3);
				int aux = a[i];
				a[i] = a[j];
				a[j] = aux;
				ok = 0;
			}
		}
		if (ok == 1)
			break;
	}
}

void bubble_sort_recursive(int* a, int n)
{
	Operation op_bubble_r = p.createOperation("BubbleSort-recursive", array_size);
	if (n == 1)
	{
		return;
	}
	int ok = 1;
	for (int i = 0; i < n - 1; i++)
	{
		op_bubble_r.count();
		if (a[i] > a[i + 1])
		{
			op_bubble_r.count(3);
			int aux = a[i];
			a[i] = a[i + 1];
			a[i + 1] = aux;
			ok = 0;
		}
	}
	if (ok == 1) return;
	bubble_sort_recursive(a, n - 1);
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
	int a[] = { 8, 4, 6, 1, 0, 5, 2, 10 }, aux1[10], aux2[10], aux3[10], aux4[10];
	int n = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < n; i++)
	{
		aux1[i] = a[i];
		aux2[i] = a[i];
		aux3[i] = a[i];
		aux4[i] = a[i];
	}
	//quicksort
	quickSort(a, 0, n - 1);
	printf("Sortarea cu QuickSort: ");
	print(a, n);
	//quicksort-best case
	printf("\nSortarea cu QuickSort in cazul favorabil: ");
	quickSort_bestCase(aux1, 0, n - 1);
	print(aux1, n);
	//quicksort-worst case
	printf("\nSortarea cu Quicksort in cazul defavorabil: ");
	int w[] = { 10,8,6,4,5,2,1,0 };
	int m = sizeof(w) / sizeof(w[0]);
	quickSort(w, 0, m - 1);
	print(w, m);
	//heapsort
	printf("\nSortarea cu HeapSort: ");
	heapSort(aux2, n);
	print(aux2, n);
	//bubble sort-varianta iterativa
	printf("\nSortarea bulelor - varianta iterativa: ");
	bubble_sort_iterative(aux3, n);
	print(aux3, n);
	//bubble sort-varianta recursiva
	printf("\nSortarea bulelor - varianta recursiva: ");
	bubble_sort_recursive(aux4, n);
	print(aux4, n);
}

void perf_QuickSort(int order)
{
	int* a;
	for (array_size = STEP_SIZE; array_size < MAX_SIZE; array_size += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			a = (int*)malloc(array_size * sizeof(int));
			FillRandomArray(a, array_size, 10, 50000, true, order);
			quickSort(a, 0, array_size - 1);
		}
	}
	p.divideValues("QuickSort", NR_TESTS);
	if (order == 1)
	{
		p.createGroup("QuickSort-worstCase", "QuickSort");
	}
	free(a);
}

void perf2_QuickSort()
{
	perf_QuickSort(UNSORTED);
	p.reset("QuickSort-worstCase");
	perf_QuickSort(ASCENDING);
	//perf_QuickSort(DESCENDING);
}

void perf_best_QuickSort()
{
	p.reset("QuickSort-bestCase");
	int* a;
	for (array_size = STEP_SIZE; array_size < MAX_SIZE; array_size += STEP_SIZE)
	{
		a = (int*)malloc(sizeof(int) * array_size);
		FillRandomArray(a, array_size, 10, 50000, true, 1);
		quickSort_bestCase(a, 0, array_size - 1);
	}
	free(a);
	//p.showReport();
}

void compare_QuickSort_HeapSort()
{
	p.reset("QuickSort-HeapSort");
	int a[MAX_SIZE], aux[MAX_SIZE];
	for (array_size = STEP_SIZE; array_size < MAX_SIZE; array_size += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(a, array_size);
			for (int k = 0; k < array_size; k++)
			{
				aux[k] = a[k];
			}
			quickSort(a, 0, array_size - 1);
			heapSort(aux, array_size);
		}
	}
	p.divideValues("QuickSort", NR_TESTS);
	p.divideValues("HeapSort", NR_TESTS);
	p.createGroup("Average", "QuickSort", "HeapSort");
	//p.showReport();
}

void perf_BubbleSort()
{
	p.reset("BubbleSort");
	int a[MAX_SIZE], aux[MAX_SIZE];
	for (array_size = STEP_SIZE; array_size < MAX_SIZE; array_size += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(a, array_size);
			for (int k = 0; k < array_size; k++)
			{
				aux[k] = a[k];
			}
			bubble_sort_iterative(a, array_size);
			bubble_sort_recursive(aux, array_size);
		}
	}
	p.divideValues("BubbleSort-iterative", NR_TESTS);
	p.divideValues("BubbleSort-recursive", NR_TESTS);
	p.createGroup("NrOfOperations-BubbleSort", "BubbleSort-iterative", "BubbleSort-recursive");
	//p.showReport();
}

void perf_BubbleSort_time()
{
	int a[2000], aux[2000];
	for (array_size = STEP_SIZE; array_size < 2000; array_size += STEP_SIZE)
	{
		p.startTimer("bubble_sort_iterative", array_size);
		for (int test_t = 0; test_t < 100; test_t++)
		{
			FillRandomArray(a, array_size);
			bubble_sort_iterative(a, array_size);
		}
		p.stopTimer("bubble_sort_iterative", array_size);

		p.startTimer("bubble_sort_recursive", array_size);
		for (int test_t = 0; test_t < 100; test_t++)
		{
			FillRandomArray(aux, array_size);
			bubble_sort_recursive(aux, array_size);
		}
		p.stopTimer("bubble_sort_recursive", array_size);
	}
	p.divideValues("bubble_sort_iterative", 100);
	p.divideValues("bubble_sort_recursive", 100);
	p.createGroup("RunningTime-BubbleSort", "bubble_sort_iterative", "bubble_sort_recursive");
	p.showReport();
}

int main()
{
	//demo();
	//average and worst case for QuickSort
	perf2_QuickSort();
	//best case for QuickSort
	perf_best_QuickSort();
	//average case QuickSort and HeapSort 
	compare_QuickSort_HeapSort();
	//number of operations bubble sort iterative and recursive
	perf_BubbleSort();
	//running time for bubble sort iterative and recursive
	perf_BubbleSort_time();
	return 0;
}