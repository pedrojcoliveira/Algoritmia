#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20
#define STAGES 15
typedef struct _DIR
{
	char deig[MAX];
	int tamanho, kb;
}DIR;

typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;

typedef BTREE_NODE* BTREE;
typedef enum _BTREE_LOCATION { BTREE_LEFT, BTREE_RIGHT } BTREE_LOCATION;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)

#define EMPTY NULL
#define NO_LINK NULL

int main(int argc, char* argv[])
{
	BTREE btree = NULL;
	if ((CreateBtree(&btree)))
	{


	}


	return 1;
}

//1
void ListarMais20Ficheiros(BTREE btree)
{
	if (btree != NULL)
	{
		if (((DIR*)DATA(btree))->tamanho > 20)
		{
			printf("Diretoria %s, tamanho = %d, kb = %d\n", (((DIR*)DATA(btree))->deig), ((DIR*)DATA(btree))->tamanho,
				((DIR*)DATA(btree))->kb);
		}
		ListarMais20Ficheiros(LEFT(btree));
		ListarMais20Ficheiros(RIGHT(btree));
	}
}

//2
int NumeroTotalKb(BTREE btree)
{
	int total_kb = 0;

	if (btree != NULL)
	{
		if (((DIR*)DATA(btree))->tamanho > 10)
		{
			total_kb += (((DIR*)DATA(btree))->kb);
		}
		total_kb += NumeroTotalKb(LEFT(btree));
		total_kb += NumeroTotalKb(RIGHT(btree));
	}
	return total_kb;
}


//3
int CalcularTotalKb(BTREE btree, char* designacao)
{
	int total_kb = 0;
	if (btree != NULL)
	{

		if (!strcmp(((DIR*)DATA(btree))->deig, designacao))
		{
			total_kb += (((DIR*)DATA(btree))->kb) + CalcularTotalKb(LEFT(btree), designacao) + CalcularTotalKb(RIGHT(btree), designacao);
		}

		total_kb += CalcularTotalKb(LEFT(btree), designacao);
		total_kb += CalcularTotalKb(RIGHT(btree), designacao);

	}

	return total_kb;
}