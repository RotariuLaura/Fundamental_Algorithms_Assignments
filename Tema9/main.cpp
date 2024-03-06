/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
* 
* Multimi disjuncte
* 
* Am implementat o structura pentru un subset care are un parinte si un rang si am facut un vector din aceste noduri. Am implementat operatiile de baza pe multimi disjuncte folosind
* vectorul de subseturi- MAKE-SET, FIND-SET, LINK si UNION. Am demonstrat corectidiunea creand 10 multimi, aplicand UNION pe 5 elemente si executand FIND-SET. Am implementat o 
* structura pentru o muchie dintr-un graf ce are cele doua varfuri si un cost si o structura pentru un graf care are numarul de varfuri, numarul de muchii si muchiile. 
* Am facut o functie pentru a crea graful, una pentru a crea muchiile din graf, una pentru afisare si una pentru a sorta muchiile descrescator dupa cost. 
* Am implementat algoritmul lui Kruskal pentru gasirea arborelui de acoperire minima a grafului, folosind multimi disjuncte si am demonstrat corectitudinea pe un graf de dimensiuni mici.
* Pentru a evalua complexitatea operatiilor pe multimi disjuncte folosind algoritmul lui Kruskal, am variat n de la 100 la 1000 si am construit cate un graf de n noduri si n*4 muchii si 
* am aplicat Kruskal(punerea varfurilor grafului in propriul set va avea un total de O(v), trecerea prin muchiile grafului sortate descrecator dupa cost pentru a determina daca varfurile 
* unei muchii sunt din seturi distincte se va face cu doua apeluri la FIND-SET pentru fiecare muchie, O(1) pentru fiecare apel, unirea celor doua seturi distincte se face cu UNION care va
* fi apelata tot in O(1). Complexitatea pentru Kruskal este O(e log v). 
*/

#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

#define STEP_SIZE 100
#define MAX_SIZE 10000

Profiler p("Demo");

int n;

typedef struct
{
	int parent;
	int rank;
}Subset;

typedef struct
{
	int e1;
	int e2;
	int weight;
}Edge;

typedef struct
{
	int vertices;
	int edges;
	Edge* edge;
}Graph;

Graph* createGraph(int v, int e)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->vertices = v;
	graph->edges = e;
	graph->edge = (Edge*)malloc(e * sizeof(Edge));
	return graph;
}

void createEdges(Graph* graph)
{
	int v = graph->vertices;
	int e = graph->edges;
	for (int i = 0; i < e; i++)
	{
		graph->edge[i].e1 = (rand() % v);
		graph->edge[i].e2 = (rand() % v);
		graph->edge[i].weight = (rand() % 100);
	} 
}

Subset subsets[10000];

void MAKE_SET(int x)
{
	p.countOperation("Operatii pe multimi disjucte", n, 2);
	subsets[x].parent = x;
	subsets[x].rank = 0;
}

int FIND_SET(int x)
{
	p.countOperation("Operatii pe multimi disjucte", n, 1);
	if (subsets[x].parent != x)
	{
		p.countOperation("Operatii pe multimi disjucte", n, 1);
		subsets[x].parent = FIND_SET(subsets[x].parent);
	}
	return subsets[x].parent;
}

void LINK(int x, int y)
{
	p.countOperation("Operatii pe multimi disjucte", n, 1);
	if (subsets[x].rank > subsets[y].rank)
	{
		p.countOperation("Operatii pe multimi disjucte", n, 1);
		subsets[y].parent = x;
	}
	else
	{
		p.countOperation("Operatii pe multimi disjucte", n, 1);
		subsets[x].parent = y;
		p.countOperation("Operatii pe multimi disjucte", n, 1);
		if (subsets[x].rank == subsets[y].rank)
		{
			p.countOperation("Operatii pe multimi disjucte", n, 1);
			subsets[y].rank = subsets[y].rank + 1;
		}
	}
}

void UNION(int x, int y)
{
	LINK(FIND_SET(x), FIND_SET(y));
}

int compare2edges(const void* a, const void* b)
{
	Edge* e1 = (Edge*)a;
	Edge* e2 = (Edge*)b;
	return e1->weight > e2->weight;
}

void printGraph(Graph* graph)
{
	printf("\nGraful:\n");
	for (int i = 0; i < graph->edges; i++)
	{
		printf("%d -> %d \n", graph->edge[i].e1, graph->edge[i].e2);
	}
}

void Kruskal(Graph* graph)
{
	Operation op_multimi = p.createOperation("Operatii pe multimi disjucte", n);
	int ve = graph->vertices;
	qsort(graph->edge, graph->edges, sizeof(graph->edge[0]), compare2edges);
	Subset* subsets = (Subset*)malloc(ve * sizeof(Subset));
	Edge* KruskalResult = (Edge*)malloc(graph->edges * sizeof(Edge));

	int i = 0;
	int e = 0;
	for (int v = 0; v < ve; ++v)
	{
		MAKE_SET(v);
	}
	while (e < ve - 1)
	{
		Edge nextEdge = graph->edge[i++];
		if (FIND_SET(nextEdge.e1) != FIND_SET(nextEdge.e2))
		{
			KruskalResult[e++] = nextEdge;
			UNION(nextEdge.e1, nextEdge.e2);
		}
	}
	int cost = 0;
	printf("\nArborele de acoperire minima pentru graful dat:\n");
	for (int i = 0; i < e; ++i)
	{
		printf("%d -> %d \n", KruskalResult[i].e1, KruskalResult[i].e2);
		cost += KruskalResult[i].weight;
	}
	printf("Costul minim: %d", cost);
}

void demoOperations()
{
	Subset subset[10];
	for (int i = 0; i < 11; i++)
	{
		MAKE_SET(i);
	}
	for (int i = 0; i < 10; i += 2)
	{
			UNION(i, i+1);
	}
	printf("\nSet de %d: %d\n", 0, FIND_SET(0));
	printf("Set de %d: %d\n", 1, FIND_SET(1));
	printf("Set de %d: %d\n", 8, FIND_SET(8));
	printf("Set de %d: %d\n", 9, FIND_SET(9));
	printf("Set de %d: %d\n", 10, FIND_SET(10));
	UNION(0, 9);
	printf("Set de %d: %d\n", 0, FIND_SET(0));
	printf("Set de %d: %d\n", 1, FIND_SET(1));
}

void demoGraph()
{
	int v = 4, e = 5;
	Graph* graph = createGraph(4, 5);
	//createEdges(graph);

	graph->edge[0].e1 = 0;
	graph->edge[0].e2 = 1;
	graph->edge[0].weight = 10;

	graph->edge[1].e1 = 0;
	graph->edge[1].e2 = 2;
	graph->edge[1].weight = 6;

	graph->edge[2].e1 = 0;
	graph->edge[2].e2 = 3;
	graph->edge[2].weight = 4;

	graph->edge[3].e1 = 1;
	graph->edge[3].e2 = 3;
	graph->edge[3].weight = 15;

	graph->edge[4].e1 = 2;
	graph->edge[4].e2 = 3;
	graph->edge[4].weight = 5;

	printGraph(graph);
	Kruskal(graph);
}

void perf()
{
	for (n = STEP_SIZE; n <= 10000; n += STEP_SIZE)
	{
		int ne = n * 4;
		Graph* graph;
		graph = createGraph(n, 60000);
		createEdges(graph);
		Kruskal(graph);
	}
	p.showReport();
}

int main()
{
	//operatii
	printf("Demo corectitudine operatii MAKE-SET, FIND-SET, UNION:\n");
	demoOperations();
	//Kruskal
	printf("\nDemo corectitudine algoritmul lui Kruskal:\n");
	demoGraph();
	//evaluare
	//perf();
	return 0;
}