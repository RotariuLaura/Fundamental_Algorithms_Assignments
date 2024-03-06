/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
* 
* Cautarea in adancime DFS
* 
* Am implementat algoritmul de cautarea in adancime DFS. Am implementat o structura care are cheia, timpul de inceput si de finalizare, culoarea, un pointer la varful adiacent
* si unul la parinte. Am folosit un vector de noduri de acest tip. Am initialiazat toate nodurile. Am folosit liste de adiacenta si am facut o functie de afisare pe care am folosit-o
* pentru fiecare nod. Am facut o functie pentru a adauga un nod in lista de adiacenta a unui nod. Am aplicat DFS pe un graf de dimensiune mica si am demonstrat corectidiunea afisand
* nodurile dupa vizitare. Am implementat o lista si functia de adaugare a unui nod in lista la inceput pe care le-am folosit la sortarea topologica. Am facut sortarea topologica astfel: 
* se aplica DFS pentru a seta timpul de finalizare pentru fiecare varf si pe masura ce un varf este finalizat, se insereaza la inceputul unei liste inlantuite si am afisat lista cu 
* cheia si timpii. Nodurile apar in ordinea descrescatoare a timpilor de finalizare. DFS are complexitate O(V+E) si sortarea topologica are tot complexitatea O(V+E) deoarece se executa
* DFS si inserarea fiecarui varf la inceputul listei se face in O(1).
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int key;
	int d, f;
	char color[10];
	node* next;
	node* parent;
}Node;

#define MAX_SIZE 200
Node* list[MAX_SIZE];
int vertices;

typedef struct node_list
{
	int key, d, f;
	node_list* next;
}NodeList;

NodeList* first = NULL, * last = NULL;

NodeList* nodNou(int key, int d, int f)
{
	NodeList* p = (NodeList*)malloc(sizeof(NodeList*));
	p->key = key;
	p->d = d; 
	p->f = f;
	p->next = NULL;
	return p;
}

void printList(NodeList* first)
{
	for (NodeList* aux = first; aux != NULL; aux = aux->next)
		printf("nod: %d, d: %d, f: %d\n", aux->key, aux->d, aux->f);
}

void insert_first(NodeList** first, NodeList** last, int key, int d, int f)
{
	NodeList* aux = nodNou(key, d, f);
	if (*first == NULL)
	{
		*first = aux;
		*last = aux;
	}
	else
	{
		aux->next = *first;
		*first = aux;
	}
}

void init()
{
	for (int i = 0; i < vertices; i++)
	{
		list[i] = (Node*)malloc(sizeof(Node));
		list[i]->key = i;
		list[i]->parent = NULL;
		strcpy(list[i]->color, "WHITE");
		list[i]->d = list[i]->f = 0;
		list[i]->next = NULL;
	}
}

void addNode(Node* x, int key)
{
	Node* aux = (Node*)malloc(sizeof(Node));
	strcpy(aux->color, "WHITE");
	aux->d = aux->f = 0;
	aux->key = key;
	aux->parent = NULL;
	aux->next = NULL;
	if (x->next == NULL)
	{
		x->next = aux;
	}
	else
	{
		Node* aux2 = (Node*)malloc(sizeof(Node));
		aux2 = x;
		while (aux2->next != NULL)
		{
			aux2 = aux2->next;
		}
		aux2->next = aux;
	}
}

int time;

void DFS_VISIT(int i)
{
	time++;
	list[i]->d = time;
	strcpy(list[i]->color, "GRAY");
	printf("%d\n", list[i]->key);
	Node* aux = (Node*)malloc(sizeof(Node));
	aux = list[i]->next;
	while (aux != NULL)
	{
		if (strcmp(list[aux->key]->color, "WHITE") == 0)
		{
			list[aux->key]->parent = list[i];
			DFS_VISIT(aux->key);
		}
		aux = aux->next;
	}
	strcpy(list[i]->color, "BLACK");
	time++;
	list[i]->f = time;
	insert_first(&first, &last, list[i]->key, list[i]->d, list[i]->f);
}

 void DFS()
 {
	 for (int i = 0; i < vertices; i++)
	 {
		 strcpy(list[i]->color, "WHITE");
		 list[i]->parent = NULL;
	 }
	 time = 0;
	 for (int i = 0; i < vertices; i++)
	 {
		 if (strcmp(list[i]->color, "WHITE") == 0)
		 {
			 DFS_VISIT(i);
		 }
	 }
 }
 
 void printAdjList(Node *aux)
 {
	 while (aux != NULL)
	 {
		 printf("%d ", aux->key);
		 aux = aux->next;
	 }
	 printf("\n");
 }

 void demo()
 {
	 vertices = 5;
	 init();
	 addNode(list[0], 1);
	 addNode(list[0], 2);
	 addNode(list[0], 3);
	 //addNode(list[1], 0);
	 addNode(list[1], 2);
	 //addNode(list[2], 0);
	 //addNode(list[2], 1);
	 addNode(list[2], 4);
	 //addNode(list[3], 0);
	 //addNode(list[4], 2);
	 printf("Varfurile din graf si varfurile adiacente lor:\n");
	 for (int i = 0; i < vertices; i++)
	 {
		 Node* aux = (Node*)malloc(sizeof(Node));
		 aux = list[i];
		 printAdjList(aux);
	 }
	 //DFS
	 printf("\nCautarea in adancime DFS:\n");
	 DFS();
	 printf("\n");
	 //sortarea topologica
	 printf("Sortarea topologica:\n");
	 printList(first);
 }

int main()
{
	demo();
	return 0;
}
