#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)


typedef struct _DIR {
	char nome[20];
	int n_fich;
	int n_Kb;
}DIR;
typedef struct _BTREE_NODE
{
	void* data;
	struct _BTREE_NODE* left;
	struct _BTREE_NODE* right;
} BTREE_NODE;
#define DATA(node) ((node)->data)
#define LEFT(node) ((node)->left)
#define RIGHT(node) ((node)->right)
typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;
int main(int argc, char* argv[])
{
	BTREE btree;
	void* dirs[15];
	char file_name[20];
	char diretoria[20];


	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(dirs, file_name))
	{
		btree = CreateBtree(dirs, 0, 15);

		//2
		printf("Escolha a diretoria desejada: \n");
		ApresentarTotalFicheiros(btree, diretoria);

		BtreeFree(btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	return 1;
}


BTREE_NODE * NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL) {
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}
void BtreeFree(BTREE btree)
{
	if (btree != NULL) {
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(DATA(btree));
		free(btree);
	}
}
BTREE_NODE* InitNode(void* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2)
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}
BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}

//1
void PrintKbMaior1000(BTREE btree)
{
	if (btree != NULL)
	{
		if (((DIR*)DATA(btree))->n_Kb > 1000)
		{
			printf("Diretorias com mais de 1000 kbytes: ", (((DIR*)DATA(btree))->nome));
		}
		PrintKbMaior1000(LEFT(btree));
		PrintKbMaior1000(RIGHT(btree));
	}
}

//2
float ApresentarTotalFicheiros(BTREE btree, char* nome)
{
	float total_ficheiros = 0.0;

	if (btree != NULL)
	{
		if (!strcmp(((DIR*)DATA(btree))->nome, nome))
		{
			total_ficheiros = (((DIR*)DATA(btree))->n_fich + (((DIR*)DATA(LEFT(btree)))->n_fich) + (((DIR*)DATA(RIGHT(btree)))->n_fich));
		}
	}
	return total_ficheiros;
}

//3		????
int BtreeLeaf(BTREE_NODE* btree) {
	if (btree == NULL) {
		return 0;
	}

	if (LEFT(btree) == NULL && RIGHT(btree) == NULL) {
		return 1;  // Nó folha
	}

	int count = 0;

	count += BtreeLeaf(LEFT(btree));
	count += BtreeLeaf(RIGHT(btree));

	printf("Número de diretorias vazia: %d", count);
}
