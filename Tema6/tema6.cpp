/*
* @autor Rotariu Laura-Alexandra
* @grupa 30224
* 
* Arbori multicai
* 
* Am implementat o functie pentru pretty-print la reprezentarea parinte. Am folosit memorie aditionala deoarece am stocat copiii fiecarui parinte intr-un alt vector pentru afisare.
* Am implementat o functie createMultiWayTree pentru a transforma un vector de parinti intr-un arbore multicai.
* Am implementat o structura NodeM pentru un nod din arborele multicai care contine o cheie, un numar de copii si un vector de noduri care sunt copiii.
* Am folosit un vector de noduri de acest tip pentru a stoca toate nodurile din arborele multicai.
* Pentru aceastra transformare, am initializat fiecare nod din vector, pe rand, cu valoarea indicilor elementelor din vectorul de parinti si am dat numarului de copii valoarea 0.
* Am parcurs vectorul de parinti si am gasit radacina: indicele elementului -1. Pentru fiecare parinte din vectorul dat de parinti, am adaugat nodul cu valoarea
* indicelul, in vectorul de copii al nodului corespunzator acestuia din vectorul listMWTree si am incrementat numarul de copii.
* Am implementat o functie de pretty-print pentru arborele multicai.
* Am implementat functia createBinaryTree care transforma un arbore multicai in arbore binar. Am implementat o structura NodeB pentru un nod din aborele binar care contine
* cheia si doi pointeri, unul catre fiul din stanga si unul pentru fiul din dreapta. Nodul radacina va fi acelasi ca in celalt arbore. Regula pentru construire este
* urmatoarea: primul fiu va fi cel mai din stanga copil al nodului si al doilea fiu va fi fratele din dreapta al nodului curent. Am implementat o
* functie de pretty-print pentru arborele binar. 
* Am atins O(n).
*/

#include <stdio.h>
#include <stdlib.h>

void search(int* a, int key, int n, int* aux, int* size)
{
	for (int i = 1; i <= n; i++)
	{
		if (a[i] == key)
		{
			aux[(*size)++] = i;
		}
	}
}

void pretty_print(int a[], int n, int root, int level)
{
	for (int i = 0; i < level; i++)
	{
		printf("%c", '\t');
	}
	printf("%d\n", root);
	int vec[10], size = 0;
	search(a, root, n, vec, &size);
	for (int j = 0; j < size; j++)
	{
		pretty_print(a, n, vec[j], level + 1);
	}
}

typedef struct nodeMultiWays
{
	int key;
	int nrChildren;
	struct nodeMultiWays* children[10];
}NodeM;//un nod din arbore multicai are o cheie, nr de copii si un vector de copii sub forma de noduri 

NodeM* listMWTree[50];//un vector de noduri pt reprezentare arbore multicai
int rootMW;//radacina vector parinti

void initMWTree(int n)
{
	for (int i = 1; i <= n; i++)
	{
		listMWTree[i] = (NodeM*)malloc(sizeof(NodeM));
		listMWTree[i]->key = i;
		listMWTree[i]->nrChildren = 0;
	}
}

void createMultiWayTree(int parinti[], int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (parinti[i] == -1)
		{
			rootMW = i;
		}
		else
		{
			listMWTree[parinti[i]]->children[listMWTree[parinti[i]]->nrChildren] = listMWTree[i];
			listMWTree[parinti[i]]->nrChildren++;
		}
	}
}

void pretty_print_MWTree(NodeM* rootMW, int level)
{
	for (int i = 0; i < level; i++)
	{
		printf("%c", '\t');
	}
	printf("%d\n", rootMW->key);
	for (int i = 0; i < rootMW->nrChildren; i++)
	{
		pretty_print_MWTree(rootMW->children[i], level + 1);
	}
}

typedef struct nodeBinaryTree
{
	int key;
	nodeBinaryTree* first;
	nodeBinaryTree* second;
}NodeB;//cheia si fii din stanga si dreapta

NodeB* rootB;

NodeB* createBinaryTree(NodeM* rootMW)
{
	NodeB* rootB = (NodeB*)malloc(sizeof(NodeB));
	NodeB* p = (NodeB*)malloc(sizeof(NodeB));
	rootB->first = rootB->second = NULL;
	rootB->key = rootMW->key;
	if (rootMW->nrChildren >= 1)
	{
		rootB->first = createBinaryTree(rootMW->children[0]);
		p = rootB->first;
		if (rootMW->nrChildren <= 1)
		{
			p->second = NULL;
		}
		else
		{
			for (int i = 1; i < rootMW->nrChildren; i++)
			{
				p->second = createBinaryTree(rootMW->children[i]);
				p = p->second;
			}
		}
	}
	return rootB;
}

void pretty_print_BinaryTree(NodeB* rootB, int level)
{
	for (int i = 0; i < level; i++)
	{
		printf("%c", '\t');
	}
	printf("%d\n", rootB->key);
	if (rootB->first != NULL)
	{
		pretty_print_BinaryTree(rootB->first, level + 1);
	}
	if (rootB->second != NULL)
	{
		pretty_print_BinaryTree(rootB->second, level + 1);
	}
}

int main()
{
	int p[10];
	p[1] = 2, p[2] = 7, p[3] = 5, p[4] = 2, p[5] = 7, p[6] = 7, p[7] = -1, p[8] = 5, p[9] = 2;
	int size = 9;
	//reprezentarea parinte
	int root;
	for (int i = 1; i <= size; i++)
	{
		if (p[i] == -1)
		{
			root = i;
		}
	}
	printf("Pretty-print la reprezentarea parinte:\n");
	pretty_print(p, size, root, 0);
	//transformarea T1 din vector parinti in arbore multicai
	printf("Printarea pentru arborele multicai:\n");
	initMWTree(size);
	createMultiWayTree(p, size);
	NodeM* MW = (NodeM*)malloc(sizeof(NodeM));
	MW = listMWTree[rootMW];
	pretty_print_MWTree(MW, 0);
	//transformarea T2 din arbore multicai in arbore binar
	printf("Printarea pentru arborele binar:\n");
	rootB = createBinaryTree(MW);
	pretty_print_BinaryTree(rootB, 0);
	return 0;
}