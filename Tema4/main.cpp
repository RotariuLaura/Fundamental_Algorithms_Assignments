/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
*
* Interclasarea eficienta a k siruri ordonate
*
* Am implementat functia createList care implementeaza o lista simplu inlantuita luand elementele dintr-un sir transmis ca parametru.
* Am implementat algoritmul de interclasare a doua liste sortate care primeste pointeri la cele doua liste si returneaza un pointer la noua lista.
* Daca una dintre liste este goala, se va returna cealalta. Initializam un pointer care va fi radacina listei obtinute prin interclasare(root), comparam primul element
* din cele doua liste si initializam inca un pointer (list) in care punem cea mai mica valoare, apoi facem ca radacina sa pointeze la aceasta valoare si pointerul de la lista respectiva
* va trece la urmatorul element. Cat timp mai sunt elemente in liste, daca elementul din prima lista este mai mic, list->next va pointa la acel element, si pointerul listei va trece
* mai departe, la fel in caz contrar. Daca prima lista ajunge la final, nodul ramas din cealalta va fi pus in noua lista, la fel invers. Am demonstrat corectitudiunea algoritmului
* interclasand doua liste de dimensiuni mici.
* Am implementat functiile necesare pentru a construi un min Heap prin metoda bottom up (minHeapify, buildMinHeap) si functia heapExtractMin care elimina minimul din heap.
* Am implementat functia mergeLists pentru interclasarea a k liste care primeste un vector de liste. Aceasta functie foloseste un min-heap. Prima data construim un min heap in
* care inseram primul element din cele k liste. Cat timp mai sunt elemente in min heap: eliminam radacina din heap(este cel mai mic element din min-heap) si o punem in noua lista.
* Daca exista un element dupa elementul eliminat, il adaugam in min heap si apelam minHeapify pentru a pastra proprietatea de minHeap, altfel extragem minimul din heap si il adaugam
* in noua lista. In final, returnam pointer la lista obtinuta prin interclasarea a k liste sortate.
* Am analizat algoritmul de interclasare a k liste sortate in cazul mediu statistic, repetand masuratorile de 5 ori.
* Am ales, pe rand, 3 valori constante pentru k(5, 10, 100) si am variat valoarea lui n(numarul de elemente) intre 100 si 10000 si am observat despre complexitatea algoritmului ca 
* este O(n log k) si cu cat k este mai mare(k=nr de liste), numarul de operatii creste, complexitatea depinzand de numarul de liste ce trebuie interclasate. Am ales valoarea 
* 10000 pentru n si am variat valoarea lui k intre 10 si 500, numarul de operatii crescand cand numarul de liste este mai mare.
*/


#include <stdio.h>
#include "Profiler.h"

#define STEP_SIZE 100
#define MAX_SIZE 10000
#define NR_TESTS 5

#define left(i) (2*i)
#define right(i) (2*i+1)
#define parent(i) (i/2)

Profiler p("Lists");

int k, n, mergedLists[100000];

typedef struct node
{
	int key;
	node* next;
}Node;

Node* createList(int* a, int n)
{
	Node* root, * p, * q;
	root = (Node*)malloc(sizeof(Node));
	p = (Node*)malloc(sizeof(Node));
	root->key = a[1];
	root->next = NULL;
	p = root;
	for (int i = 2; i <= n; i++)
	{
		q = (Node*)malloc(sizeof(Node));
		q->key = a[i];
		q->next = NULL;
		p->next = q;
		p = p->next;
	}
	return root;
}

void printList(Node* root)
{
	Node* p;
	for (p = root; p != NULL; p = p->next)
	{
		printf("%d ", p->key);
	}
	printf("\n");
}

Node* merge2lists(Node* l1, Node* l2)
{
	Node* list = (Node*)malloc(sizeof(Node));
	Node* root = (Node*)malloc(sizeof(Node));
	list = root = NULL;
	if (l1 == NULL)
	{
		return l2;
	}
	else if (l2 == NULL)
	{
		return l1;
	}
	else
	{
		if (l1->key <= l2->key)
		{
			list = l1;
			l1 = l1->next;

		}
		else
		{
			list = l2;
			l2 = l2->next;
		}
	}
	root = list;
	while (l1 != NULL && l2 != NULL)
	{
		if (l1->key <= l2->key)
		{
			list->next = l1;
			list = l1;
			l1 = l1->next;
		}
		else
		{
			list->next = l2;
			list = l2;
			l2 = l2->next;
		}
	}
	if (l1 == NULL)
	{
		list->next = l2;
	}
	if (l2 == NULL)
	{
		list->next = l1;
	}
	return root;
}

int heap_size;

void minHeapify(Node* lists[502], int i)
{
	Operation op_merge1 = p.createOperation("MergeLists-n varies", n);
	Operation op_merge2 = p.createOperation("MergeLists-k varies", k);
	int min = i;
	int l = left(i);
	int r = right(i);
	if (l <= heap_size)
	{
		op_merge1.count();
		op_merge2.count();
		if (lists[l]->key < lists[i]->key) 
		{

			{
				min = l;
			}
		}
	}
	if (r <= heap_size)
	{
		op_merge1.count();
		op_merge2.count();
		if (lists[r]->key < lists[i]->key)
		{
			{
				min = r;
			}
		}
	}
	if (min != i)
	{
		op_merge1.count(3);
		op_merge2.count(3);
		Node* aux = (Node*)malloc(sizeof(Node));
		aux = lists[i];
		lists[i] = lists[min];
		lists[min] = aux;
		minHeapify(lists, min);
	}
}

void buildMinHeap(Node* lists[502])
{
	for (int i = heap_size / 2; i >= 1; i--)
	{
		minHeapify(lists, i);
	}
}

int heapExtractMin(Node* lists[502])
{
	if (heap_size < 1)
	{
		printf("eroare");
		return -1;
	}
	int min = lists[1]->key;
	p.countOperation("MergeLists-n varies", n, 1);
	p.countOperation("MergeLists-k varies", k, 1);
	lists[1] = lists[heap_size];
	heap_size--;
	minHeapify(lists, 1);
	return min;
}

Node* mergeLists(Node* lists[502], int k)
{
	buildMinHeap(lists);
	heap_size = k;
	int min, i = 1;
	while (heap_size > 0)
	{
		p.countOperation("MergeLists-n varies", n, 1);
		p.countOperation("MergeLists-k varies", k, 1);
		if (lists[1]->next != NULL)
		{
			mergedLists[i] = lists[1]->key;
			i++;
			p.countOperation("MergeLists-n varies", n, 1);
			p.countOperation("MergeLists-k varies", k, 1);
			lists[1] = lists[1]->next;
			minHeapify(lists, 1);
		}
		else
		{
			min = heapExtractMin(lists);
			mergedLists[i] = min;
			i++;
		}
	}
	Node* newList = (Node*)malloc(sizeof(Node));
	newList = createList(mergedLists, i - 1);
	return newList;
}

void demo_2_lists()
{
	//interclasarea a doua liste
	Node* l1 = (Node*)malloc(sizeof(Node));
	Node* l2 = (Node*)malloc(sizeof(Node));
	Node* list = (Node*)malloc(sizeof(Node));
	int* a;
	a = (int*)malloc(10 * sizeof(int));
	FillRandomArray(a, 6, 0, 10, true, 1);
	l1 = createList(a, 5);
	FillRandomArray(a, 6, 0, 10, true, 1);
	l2 = createList(a, 5);
	printf("Cele doua liste sortate:\n");
	printList(l1);
	printList(l2);
	printf("Interclasarea celor doua liste sortate:\n");
	list = merge2lists(l1, l2);
	printList(list);
}

void demo_k_lists()
{
	//k=4, n=20
	printf("\nInterclasarea a k liste sortate cu n elemente:\n");
	int l1[6], l2[6], l3[6], l4[6];
	l1[1] = 1, l1[2] = 2, l1[3] = 3, l1[4] = 6, l1[5] = 8;
	l2[1] = 7, l2[2] = 9, l2[3] = 10, l2[4] = 11, l2[5] = 12;
	l3[1] = 5, l3[2] = 14, l3[3] = 15, l3[4] = 16, l3[5] = 20;
	l4[1] = 8, l4[2] = 9, l4[3] = 10, l4[4] = 12, l4[5] = 18;
	Node* l[5]; //vector de 4 liste
	l[1] = (Node*)malloc(sizeof(Node));
	l[1] = createList(l1, 5);
	l[2] = (Node*)malloc(sizeof(Node));
	l[2] = createList(l2, 5);
	l[3] = (Node*)malloc(sizeof(Node));
	l[3] = createList(l3, 5);
	l[4] = (Node*)malloc(sizeof(Node));
	l[4] = createList(l4, 5);
	k = 4;
	Node* merged = mergeLists(l, k);
	printList(merged);
}

void perf_n_varies()
{
	int* a;
	k = 5;
	//n = 100..10000
	for (int test = 1; test <= NR_TESTS; test++)
	{
		for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
		{
			Node* l[6];//vector de 5 liste cu n elemente
			for (int j = 1; j <= k; j++)
			{
				l[j] = (Node*)malloc(sizeof(Node));
				a = (int*)malloc(((n / k) + 1) * sizeof(int));
				FillRandomArray(a, n / k + 1, 0, 50000, false, 1);
				l[j] = createList(a, n / k);
			}
			mergeLists(l, k);
		}
	}
	p.divideValues("MergeLists-n varies", NR_TESTS);
	p.createGroup("MergeLists_for_k_5", "MergeLists-n varies");

	p.reset("n_varies_k_10");
	k = 10;
	//n = 100...10000
	for (int test = 1; test <= NR_TESTS; test++)
	{
		for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
		{
			Node* l[12];//vector de 10 liste
			for (int j = 1; j <= k; j++)
			{
				l[j] = (Node*)malloc(sizeof(Node));
				a = (int*)malloc(((n / k) + 1) * sizeof(int));
				FillRandomArray(a, n / k + 1, 0, 50000, true, 1);
				l[j] = createList(a, n / k);
			}
			mergeLists(l, k);
		}
	}
	p.divideValues("MergeLists-n varies", NR_TESTS);
	p.createGroup("MergeLists_for_k_10", "MergeLists-n varies");

	p.reset("n_varies_k_100");
	k = 100;
	//n=100...10000
	for (int test = 1; test <= NR_TESTS; test++) {
		for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
		{
			Node* l[102];//vector de 100 liste
			for (int j = 1; j <= k; j++)
			{
				l[j] = (Node*)malloc(sizeof(Node));
				a = (int*)malloc(((n / k) + 1) * sizeof(int));
				FillRandomArray(a, n / k + 1, 0, 50000, true, 1);
				l[j] = createList(a, n / k);
			}
			mergeLists(l, k);
		}
	}
	p.divideValues("MergeLists-n varies", NR_TESTS);
	p.createGroup("MergeLists_for_k_100", "MergeLists-n varies");
	//p.showReport();

}

void perf_k_varies()
{
	p.reset("k_varies_n_10000");
	int* a;
	n = 10000;
	//k=10...500
	for (int test = 1; test <= NR_TESTS; test++)
	{
		for (k = 10; k <= 500; k += 10)
		{
			Node* l[502];
			for (int j = 1; j <= k; j++)
			{
				l[j] = (Node*)malloc(sizeof(Node));
				a = (int*)malloc(((n / k) + 1) * sizeof(int));
				FillRandomArray(a, n / k + 1, 0, 50000, true, 1);
				l[j] = createList(a, n / k);
			}
			mergeLists(l, k);
		}
	}
	p.divideValues("MergeLists-k varies", NR_TESTS);
	p.createGroup("MergeLists_for_n_10000", "MergeLists-k varies");
	p.showReport();
}

int main()
{
	//interclasarea a doua liste
	demo_2_lists();
	//interclasarea a k liste cu n elemente; k=4, n=20;
	demo_k_lists();
	////n variaza intre 100 si 10000, k ia 3 valori constante(5, 10, 100)
	//perf_n_varies();
	////n=10000, k variaza intre 10 si 500
	//perf_k_varies();
	return 0;
}