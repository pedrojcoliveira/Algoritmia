#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOME 20




typedef enum _STATUS { ERROR, OK } STATUS;
typedef enum _BOOLEAN { FALSE, TRUE } BOOLEAN;

typedef struct _PLAYER
{
	char nome[MAX_NOME];
	char clube[MAX_NOME];
	int posicao;
	BOOLEAN titular;
}PLAYER;

typedef struct _LIST_NODE
{
	void* data;
	struct _LIST_NODE* next;
}LIST_NODE;

typedef LIST_NODE* LIST;

#define DATA(node) ((node)->data);
#define NEXT(node) ((node)->next);

LIST_NODE* NewNode(void* data);
LIST_NODE* InsertIni(LIST* list, void* data);
STATUS ReadFile(LIST* list, const char* filename);
void TrocarJogador(LIST list, const char* nome_antigo, const char* nome_novo);

int main()
{
	LIST list;
	PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));
	char nome_antigo[MAX_NOME];
	char nome_novo[MAX_NOME];

	//1
	printf("Nome do Jogador: ");
	scanf("%s", player->nome);
	
	printf("Nome do Clube: ");
	scanf("%s", player->clube);

	printf("Posicção do Jogador: ");
	scanf("%d", &player->posicao);

	printf("O Jogador é titular? (1-Sim/0-Não)");
	scanf("%d", &player->titular);
	if (player->titular == 1)
	{
		player->titular = TRUE;
	}
	else if(player->titular == 0)
	{
		player->titular = FALSE;
	}

	//InsertIni(&list, player);
	InsertEnd(&list, player);

	//2
	printf("Jogador a ser retirado");
	scanf("%s", nome_antigo);

	printf("Jogador a colocar a titular");
	scanf("%s", nome_novo);

	TrocarJogador(list, nome_antigo, nome_novo);
}

LIST_NODE* NewNode(void* data)
{
	LIST_NODE* new_node;
	if ((new_node = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
	{
		DATA(new_node);
		NEXT(new_node);
	}
}

LIST_NODE* InserIni(LIST* list, void* data)
{
	LIST_NODE* new_node;

	if ((new_node = NewNode(data)) != NULL)
	{
		(new_node->next) = *list;
		*list = new_node;

	}
	return(new_node);
}

//1
LIST_NODE InsertEnd(LIST* list, void* data)
{
	LIST_NODE* new_node, * temp;

	if((new_node = NewNode(data)) != NULL)
	{ 
		if (*list = NULL)
		{
			*list = new_node;
		}
		else
		{
			temp = *list;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = new_node;
		}
		return OK;
	}
	return ERROR;
}


//2
BOOLEAN MostrarTitulares(LIST list)
{
	while (list != NULL)
	{
		if (((PLAYER*)list->data)->titular = TRUE)
		{
			printf("Jogadores Titulares: %s", ((PLAYER*)list->data)->nome);
			
		}
		else
		{
			printf("Jogador não encontrado");
		}
		list = list->next;
	}
}

//3
void TrocarJogador(LIST list, char* nome_antigo, char* nome_novo)
{

	while (list != NULL)
	{
		if (strcmp(((PLAYER*)list->data)->nome, nome_antigo))
		{
			((PLAYER*)list->data)->titular = FALSE;
		}
		else if (strcmp(((PLAYER*)list->data)->nome, nome_novo))
		{
			((PLAYER*)list->data)->titular = TRUE;
		}
		list = list->next;
	}
}

