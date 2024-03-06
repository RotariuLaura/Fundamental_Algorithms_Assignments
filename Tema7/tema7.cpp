/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
* 
* Statistici dinamice de ordine
* 
* Am definit o structura pentru un nod din arborele binar de cautare echilibrat care contine o cheie, 2 pointeri catre cei doi fii si un pointer catre parinte 
* si un camp cu dimensiunea subarborelui ce are ca radacina nodul respectiv. Am implementat o functie care transforma un sir sortat de numere intr-un arbore 
* binar de cautare echilibrat, astfel: am facut ca radacina arborelui sa fie mijlocul sirului si am repetat aceasta operatie pentru copilul din stanga pe
* prima jumatate a sirului si pentru copilul din dreapta pe a doua jumatate a sirului, in mod recursiv si am initializat campul size pentru fiecare nod. 
* Am construit un arbore de 11 elemente si am facut afisarea folosind functia pretty-print. Am implementat functia OS-Select care cauta elementul cu a 
* i-a cea mai micã cheie si am demonstrat corectitudinea cautand 3 indecsi selectati aleator. Am implementat functia OS-Delete care sterge un anumit nod din 
* arbore folosind stergerea de la arbori binari de cautare si modificand campul size dupa stergere si am demonstrat corectitudinea stergand 3 indecsi selectati 
* aleator. Pentru functia OS-Delete, am implementat si functiile pentru gasirea succesorului unui nod, a minimului dintr-un arbore si pentru actualizarea campului size.
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
	int key;
	node* first;
	node* second;
	int size;
	node* parent;
}NodeB;

NodeB* createBBST(int a[], int l, int r, NodeB* rootB, NodeB* parent)
{
	if (r < l)
	{
		return NULL;
	}
	int m = (l + r) / 2;
	rootB->key = a[m];
	rootB->first = (NodeB*)malloc(sizeof(NodeB));
	rootB->second = (NodeB*)malloc(sizeof(NodeB));
	rootB->parent = (NodeB*)malloc(sizeof(NodeB));
	rootB->parent = parent;
	rootB->first = createBBST(a, l, m - 1, rootB->first, rootB);
	rootB->second = createBBST(a, m+1, r, rootB->second, rootB);
	if (rootB->first == NULL && rootB->second == NULL)
		rootB->size = 1;
	else if (rootB->first == NULL && rootB->second != NULL)
		rootB->size = rootB->second->size + 1;
	else if(rootB->first != NULL && rootB->second == NULL)
		rootB->size = rootB->first->size + 1;
	else
		rootB->size = rootB->first->size + rootB->second->size + 1;
	return rootB;
}

void pretty_print_BinaryTree(NodeB* rootB, int level)
{
	for (int i = 0; i < level; i++)
	{
		printf("%c", '\t');
	}
	printf("%d--%d\n", rootB->key, rootB->size);
	if (rootB->first != NULL)
	{
		pretty_print_BinaryTree(rootB->first, level + 1);
	}
	if (rootB->second != NULL)
	{
		pretty_print_BinaryTree(rootB->second, level + 1);
	}
}

NodeB* OS_Select(NodeB* root, int i)
{
	int r;
	if (root->first != NULL)
		r = root->first->size + 1;
	else
		r = 1;
	if (i == r)
	{
		return root;
	}
	else if (i < r)
	{
		return OS_Select(root->first, i);
	}
	else
	{
		return OS_Select(root->second, i - r);
	}
}

NodeB* min(NodeB* x)
{
	while (x->first != NULL)
	{
		x = x->first;
	}
	return x;
}

NodeB* successor(NodeB* x)
{
	if (x->second != NULL)
	{
		return min(x->second);
	}
	NodeB* y;
	y = x->parent;
	while (y != NULL && x == y->second)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

void newSize(NodeB* x)
{
	while (x != NULL)
	{
		x->size--;
		x = x->parent;
	}
}

void OS_Delete(NodeB* root, NodeB* x)
{
	NodeB* y;
	if (x->first == NULL || x->second == NULL)
		y = x;
	else
		y = successor(x);
	NodeB* z;
	if (y->first != NULL)
		z = y->first;
	else
		z = y->second;
	if (z != NULL)
		z->parent = y->parent;
	if (y->parent == NULL)
		root = z;
	else if (y == y->parent->first)
		y->parent->first = z;
	else
		y->parent->second = z;
	x->key = y->key;
	newSize(x);
}

int main()
{
	//construire arbore binar de cautare echilibrat
	int a[] = { 1,2,3,4,5,6,7,8, 9, 10, 11 };
	int size = sizeof(a) / sizeof(a[0]);
	NodeB* root = (NodeB*)malloc(sizeof(NodeB));
	root = createBBST(a, 0, size - 1, root, NULL);
	//pretty-print
	printf("Arborele binar de cautare echilibrat:\n");
	pretty_print_BinaryTree(root, 0);
	//demo select
	printf("Demonstratie OS-SELECT:\n");
	NodeB* p = (NodeB*)malloc(sizeof(NodeB));
	NodeB* q = (NodeB*)malloc(sizeof(NodeB));
	NodeB* t = (NodeB*)malloc(sizeof(NodeB));
	p = OS_Select(root, 2);
	printf("Elementul cu indexul al 2-lea: %d", p->key);
	q = OS_Select(root, 3);
	printf("\nElementul cu indexul al 3-lea: %d", q->key);
	t = OS_Select(root, 10);
	printf("\nElementul cu indexul al 10-lea: %d\n", t->key);
	//demo delete
	printf("\nDemonstratie OS-DELECT:\n");
	printf("Arborele dupa stergerea cheii 2:\n");
	OS_Delete(root, p);
	pretty_print_BinaryTree(root, 0);
	printf("Arborele dupa stergerea cheii 3:\n");
	OS_Delete(root, q);
	pretty_print_BinaryTree(root, 0);
	printf("Arborele dupa stergerea cheii 10:\n");
	OS_Delete(root, t);
	pretty_print_BinaryTree(root, 0);
	return 0;
}