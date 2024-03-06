/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
*
* Parcurgere arbore binar iterativ vs recursiv, hibridizare quicksort
*
* Am implementat o structura pentru un nod din arborele binar si am construit un arbore binar dintr-un sir dat. Am traversat in inordine arborele binar in mod
* recursiv si in mod iterativ, facand cate o functie pentru fiecare traversare. Am demonstrat corectitudinea pe un arbore de dimensiune mica. Am analizat comparativ
* parcugerea iterativa si cea recursiva din punct de vedere al numarului de operatii(printarea cheii), variind dimensiunea arborelui intre 100 si 10000 si am observat
* ca se efectueaza acelasi numar de printari in ambele cazuri. Ambele parcurgeri au complexitatea 0(n).
* Am implementat metoda de sortare QuickSort hibridizata care utilizeaza sortarea prin insertie si am comparat-o cu QuickSort din punct de vedere al numarului de
* operatii si al timpului de executie. Complexitatea QuickSort in cazul mediu statistic este O(n log n), complexitatea QuickSort hibrid este O(n^2), complexitatea 
* sortarii prin insertie este O(n^2). Am observat ca QuickSort este mai eficient decat cel hibrid din punct de vedere al numarului de operatii, acesta fiind mai 
* mic la varianta normala. QuickSort hibrid este mai eficient din punct de vedere al timpului de executie.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

#define left(i) (2*i+1)
#define right(i) (2*i+2)
#define STEP_SIZE 100
#define MAX_SIZE 10000
#define NR_TESTS 5

int n;

Profiler p("Demo");

typedef struct node
{
	int key;
	node* first;
	node* second;
}NodeB;

NodeB* createNode(int key)
{
	NodeB* p = (NodeB*)malloc(sizeof(NodeB));
	p->key = key;
	p->first = NULL;
	p->second = NULL;
	return p;
}

NodeB* createBinaryTree(int* a, int i, int n)
{
	NodeB* rootB = NULL;
	if (i < n)
	{
		rootB = createNode(a[i]);
		rootB->first = createBinaryTree(a, left(i), n);
		rootB->second = createBinaryTree(a, right(i), n);
	}
	return rootB;
}

void traverse_recursive(NodeB* root)
{
	Operation op_recursive = p.createOperation("traverse-recursive", n);
	if (root != NULL)
	{
		traverse_recursive(root->first);
		op_recursive.count();
		printf("%d ", root->key);
		traverse_recursive(root->second);
	}
}

void traverse_iterative(NodeB* rootB)
{
	Operation op_iterative = p.createOperation("traverse_iterative", n);
	if (rootB == NULL)
		return;
	NodeB* q = (NodeB*)malloc(sizeof(NodeB));
	q = rootB;
	NodeB* p = (NodeB*)malloc(sizeof(NodeB));
	do
	{
		if (q->first == NULL)
		{
			op_iterative.count();
			printf("%d ", q->key);
			q = q->second;
		}
		else
		{
			p = q->first;
			while (p->second != NULL && p->second != q)
			{
				p = p->second;
			}
			if (p->second == NULL)
			{
				p->second = q;
				q = q->first;
			}
			else
			{
				p->second = NULL;
				op_iterative.count();
				printf("%d ", q->key);
				q = q->second;
			}
		}
	} while (q != NULL);
}

void demo_tree()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
	int n = sizeof(a) / sizeof(a[0]);
	NodeB* rootB = createBinaryTree(a, 0, n);
	//parcurgere iterativa
	printf("Parcurgere inordine a arborelui binar iterativ:\n");
	traverse_iterative(rootB);
	printf("\nParcurgere inordine a arborelui binar recursiv:\n");
	//parcurgerea recursiva
	traverse_recursive(rootB);
}

void perf_tree()
{
	int a[MAX_SIZE], aux[MAX_SIZE];
	for (n = STEP_SIZE; n < MAX_SIZE; n += STEP_SIZE)
	{
		FillRandomArray(a, n);
		for (int k = 0; k < n; k++)
		{
			aux[k] = a[k];
		}
		NodeB* rootB = createBinaryTree(a, 0, n);
		traverse_recursive(rootB);
		traverse_iterative(rootB);
	}
	//p.createGroup("binary_tree_traversal", "traverse_recursive", "traverse_iterative");
	p.showReport();
}

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


void insertion_sort(int* a, int n)
{
	Operation op_QuickSortHibrid = p.createOperation("QuickSortHibrid", array_size);
	for (int i = 1; i < n; i++)
	{
		op_QuickSortHibrid.count();
		int x = a[i];
		int j = i - 1;
		op_QuickSortHibrid.count();
		while (j >= 0 && a[j] > x)
		{
			op_QuickSortHibrid.count();
			a[j + 1] = a[j];
			j--;
		}
		op_QuickSortHibrid.count();
		a[j + 1] = x;
	}
}

int partition_hibrid(int* a, int m, int n)
{
	int pivot = a[n];
	int i = m - 1;
	for (int j = m; j < n; j++)
	{
		p.countOperation("QuickSortHibrid", array_size, 1);
		if (a[j] <= pivot)
		{
			i++;
			p.countOperation("QuickSortHibrid", array_size, 3);
			int aux = a[j];
			a[j] = a[i];
			a[i] = aux;
		}
	}
	p.countOperation("QuickSortHibrid", array_size, 3);
	int aux2 = a[i + 1];
	a[i + 1] = a[n];
	a[n] = aux2;
	return i + 1;
}

void quickSort_hibrid(int* a, int m, int n)
{
	if (m < n)
	{
		if (n - m + 1 < 30)
		{
			insertion_sort(a, n);
		}
		else
		{

			int p;
			p = partition_hibrid(a, m, n);
			quickSort_hibrid(a, m, p - 1);
			quickSort_hibrid(a, p + 1, n);
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

void demo_quicksort()
{
	printf("\n");
	int a[] = { 8, 4, 6, 1, 0, 5, 2, 10 };
	int n = sizeof(a) / sizeof(a[0]);
	quickSort(a, 0, n - 1);
	printf("\nSortarea cu QuickSort:\n");
	print(a, n);
	quickSort_hibrid(a, 0, n - 1);
	printf("\nSortarea cu QuickSort hibrid:\n");
	print(a, n);
}

void perf_quicksort()
{
	p.reset("QuickSort-QuickSortHibrid");
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
			quickSort_hibrid(aux, 0, array_size - 1);
		}
	}
	p.divideValues("QuickSort", NR_TESTS);
	p.divideValues("QuickSortHibrid", NR_TESTS);
	p.createGroup("CompareQuickSort", "QuickSort", "QuickSortHibrid");
	p.showReport();
}


void perf_quicksort_time()
{
	p.reset("QuickSortTime");
	int a[2000], aux[2000];
	for (n = STEP_SIZE; n < 2000; n += STEP_SIZE)
	{
		p.startTimer("quickSort", n);
		for (int test_t = 0; test_t < 100; test_t++)
		{
			FillRandomArray(a, n);
			quickSort(a, 0, n - 1);
		}
		p.stopTimer("quickSort", n);

		p.startTimer("quickSort_hibrid", n);
		for (int test_t = 0; test_t < 100; test_t++)
		{
			FillRandomArray(aux, n);
			quickSort_hibrid(aux, 0, n - 1);
		}
		p.stopTimer("quickSort_hibrid", n);
	}
	p.divideValues("quickSort", 100);
	p.divideValues("quickSort_hibrid", 100);
	p.createGroup("RunningTime-QuickSort", "quickSort", "quickSort_hibrid");
	p.showReport();
}

int main()
{
	demo_tree();
	//perf_tree();
	demo_quicksort();
	//perf_quicksort();
	//perf_quicksort_time();
	return 0;
}