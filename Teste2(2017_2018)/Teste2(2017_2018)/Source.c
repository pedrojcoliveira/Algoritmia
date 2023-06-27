#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)


typedef struct _PERSON {
	char nome[50];
	int age;
	BOOLEAN alive;
}PERSON;
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
	void* persons[15];
	char file_name[20];
	char nome;
	char novo_nome;



	printf("Nome do ficheiro: ");
	scanf("%s", file_name);
	if (ReadFile(persons, file_name))
	{
		btree = CreateBtree(persons, 0, 15);

		//2
		printf("Indique o nome da pessoa que deseja alterar o nome: ");
		scanf("%s", nome);

		printf("Indique o novo nome: ");
		scanf("%s", novo_nome);

		AlterarNome(btree, nome, novo_nome);

		//3
		IntroduzirNos(btree);


		BtreeFree(btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n");
	return 1;
}


BTREE_NODE* NewBtreeNode(void* data)
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

STATUS ReadFile(void** persons, char* file_name)
{
	FILE* fp;
	int aux, j, i = 0;
	void* ptr_data;

	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!fopen(fp))
		{
			if ((ptr_data = malloc(sizeof(PERSON))) != NULL)
			{
				fscanf(fp, "%[^;];%d;%d\n", ((PERSON*)ptr_data)->nome, &((PERSON*)ptr_data)->age, &aux);
				if (aux) ((PERSON*)ptr_data)->alive = TRUE;
				else ((PERSON*)ptr_data)->alive = FALSE;
				persons[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j > 0; j--)
					free(persons[j]);
				return ERROR;
			}
			fclose(fp);
			return OK;
		}
	}
	else
	{
		return ERROR;
	}
}




BTREE_NODE* CreateBtree(void** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size)));
}


//1
int PessoasVivas(BTREE btree)
{
	int count = 0;

	if (((PERSON*)DATA(btree))->alive == TRUE)
	{
		count += 1;
	}

	count += PessoasVivas(LEFT(btree));
	count += PessoasVivas(RIGHT(btree));
	return count;
}

//2 - Perguntar ao stor como fica a chamada no Main
BOOLEAN AlterarNome(BTREE btree, char* name, char* novo_nome)
{
	BOOLEAN find = FALSE;
	if (btree != NULL)
	{
		if (!strcmp(((PERSON*)DATA(btree))->nome, name))
		{
			strcpy(((PERSON*)DATA(btree))->nome, novo_nome);
			find = TRUE;
		}
		AlterarNome(LEFT(btree), name, novo_nome);
		AlterarNome(RIGHT(btree), name, novo_nome);
	}
	return find;
}


//3
void IntroduzirNos(BTREE btree)
{
	if (btree != NULL)
	{
		if (RIGHT(btree) == NULL)
		{
			BTREE new_node1 = NewBtreeNode(NULL);
			BTREE new_node2 = NewBtreeNode(NULL);

			RIGHT(btree) = new_node1;
			LEFT(btree) = new_node2;

			printf("Introduza os dados para o primeiro novo nó:\n");
			scanf("%s", new_node1->data);

			printf("Introduza os dados para o segundo novo nó:\n");
			scanf("%s", new_node2->data);

		}
	}
}