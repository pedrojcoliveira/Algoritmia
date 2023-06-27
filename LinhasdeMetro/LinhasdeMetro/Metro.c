#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define STRMAX 30

typedef struct _LIST_NODE {
	void* data;
	struct _LIST_NODE* next;
}LIST_NODE;


typedef LIST_NODE* LIST;

typedef enum {FALSE = 0, TRUE=1} BOOLEAN;
typedef enum{ERROR, OK}STATUS;

typedef struct {
	char nome[STRMAX];
	float custo;
	BOOLEAN ativa, ligacao;
}ESTACAO;

#define DATA(node) ((node)->data)
#define NEXT(node) ((node)->next)
#define EMPTY NULL

void initList(LIST* list);
BOOLEAN emptyList(LIST list);		//Não tem "*" pois não vamos alterar o valor da lista

LIST_NODE* newNode(void* data);
STATUS InsertIni(LIST* list, void* data);
STATUS InsertEnd(LIST* list, void* data);
STATUS InsertAtPos(LIST* list, void* data, char* nome);
int ListSize(LIST list);
void ShowStations(LIST list);
STATUS ReadFile(LIST* list, char* filename);		//Vai criar a lista daí o "*"
STATUS SaveFile(LIST list, char filename);
BOOLEAN DeleteStation(LIST* list);
void RemoveFirstNode(LIST* list);
void FreeList(LIST* list);
BOOLEAN StationExist(LIST list, char* nome);
ESTACAO* ReadStation();
BOOLEAN ActiveStation(LIST list, char* desig, BOOLEAN estado);
STATUS InvertList(LIST* list);


void initList(LIST* pL)
{
	*pL = NULL;
}

BOOLEAN emptyList(LIST L)
{
	return (L == NULL) ? TRUE : FALSE;
}

STATUS InsertIni(LIST* pL, void* pData)
{
	LIST_NODE* pNew;
	if ((pNew = newNode(pData)) == EMPTY)
		return ERROR;
	NEXT(pNew) = *pL;
	*pL = pNew;
	return OK;
}


STATUS InsertEnd(LIST* pL, void* pData)
{
	LIST_NODE* pNew, * pTemp;
	if ((pNew = newNode(pData)) == EMPTY)
		return ERROR;
	if (*pL == NULL)
		*pL = pNew;
	else
	{
		pTemp = *pL;
		while (NEXT(pTemp) != NULL)
			pTemp = NEXT(pTemp);
		NEXT(pTemp) = pNew;
	}
	return OK;
}

int ListSize(LIST L)
{
	LIST pTemp = L;
	int count = 0;
	while (pTemp != NULL)
	{
		count++;
		pTemp = NEXT(pTemp);
	}
	return count;
}

void ShowStations(LIST L)
{
	LIST pTemp = L;
	if (emptyList(pTemp) == TRUE)
	{
		printf("\nLista vazia.\n");
		return;
	}
	while (pTemp != NULL)
	{
		printf(" %s  %.2f-> %d", ((ESTACAO*)DATA(pTemp))->nome, ((ESTACAO*)DATA(pTemp))->custo, ((ESTACAO*)DATA(pTemp))->ativa);
		pTemp = NEXT(pTemp);
	}
	printf("\nFIM\n");
	return;
}

LIST_NODE* newNode(void* pData)
{
	LIST_NODE* pNew;
	if ((pNew = (LIST_NODE*)malloc(sizeof(LIST_NODE))) != NULL)
	{
		DATA(pNew) = pData;
		NEXT(pNew) = NULL;
	}
	return pNew;
}

STATUS ReadFile(LIST* list, char* filename) {
	FILE* fp;
	ESTACAO* ptr;

	if ((fp = fopen(filename, "r")))
	{
		while (!feof(fp)) {
			if((ptr = (ESTACAO*)malloc(sizeof(ESTACAO))) != NULL) {
				fscanf(fp, "%[^;];%f;%d;%d;\n", ptr->nome, &(ptr->custo), &(ptr->ativa), &(ptr->ligacao));  //o nome não leva "&" pois sendo char jã aponta para o seu valor
				InsertEnd(list, ptr);	
			}
			else {
				FreeList(list);
				//fclose(fp);
				return ERROR;
			}
		}
		fclose(fp);
		return OK;
	}
	else
		return ERROR;
}

STATUS SaveFile(LIST list, char* filename) {
	FILE* fp;
	if ((fp = fopen(filename, "w")) != NULL) {

		while (list != NULL) {
			fprintf(fp, "%s;%.2f;%d;%d;\n",
				((ESTACAO*)DATA(list))->nome,
				((ESTACAO*)DATA(list))->custo,
				((ESTACAO*)DATA(list))->ativa,
				((ESTACAO*)DATA(list))->ligacao),
				list = NEXT(list);
		}
		fclose(fp);
		return OK;
	}
	else
		return ERROR;
}

float CustoTotal(LIST list) {

	float custo = 0.0;
	while (list != NULL)
	{
		custo += ((ESTACAO*)DATA(list))->custo, ((ESTACAO*)DATA(list))->custo ;
		list = NEXT(list);
	}
	return custo;
}

BOOLEAN StationExist(LIST list, char* nome) {
	return TRUE;
}

void RemoveFirstNode(LIST* list) {
	LIST_NODE* node;
	node = *list;
	*list = NEXT(*list);
	free(DATA(node));
	free(node);

}

void FreeList(LIST* list) {
	while (*list != NULL)
		RemoveFirstNode(list);
}

BOOLEAN DeleteStation(LIST* list, char* designacao) {	//designacao = nome da estacao
	LIST_NODE* ant, * node;
	node = *list;
	ant = node;
	while (node != NULL) {
		if (strcmp(((ESTACAO*)DATA(node))->nome, designacao) == 0) {
			if (node == *list)
				*list = NEXT(node);
			NEXT(ant) = NEXT(node);
			free(DATA(node));
			free(node);
			return TRUE;
		}
		else
		{
			ant = node;
			node = NEXT(node);
		}
	}
}

ESTACAO* ReadStation() {
	ESTACAO* ptr = NULL;
	char op;
	ptr = (ESTACAO*)malloc(sizeof(ESTACAO));
	if (ptr != NULL) {
		ptr->ativa = ptr->ligacao = FALSE;

		printf("Desigancao da estaca: ");
		gets_s(ptr->nome, STRMAX);
		printf("Custo: ");
		scanf("%f", &(ptr->custo));
		printf("Ativa [s/n]");
		while((getchar()) != '\n');
		scanf("%c", &op);
		if (op == 's')
			ptr->ativa = TRUE;
	}
	return ptr;
}

BOOLEAN ActiveStation(LIST list, char* desig, BOOLEAN estado) {
	while (list != NULL)
	{
		if(strcmp(((ESTACAO*)DATA(list))->nome, desig) == 0) {
			((ESTACAO*)DATA(list))->ativa = estado;
			return TRUE;
		}
		list = NEXT(list);
	}
	return FALSE;
}

STATUS InsertAtPos(LIST* list, void* data, char* nome)
{
	LIST_NODE* new_node, *temp;
	
	new_node = newNode(data);
	if (new_node == NULL)
		return ERROR;	
	temp = *list;
	while (strcmp(((ESTACAO*)temp->data)->nome, nome) != 0)
	{
		temp = temp->next;
	}
	new_node->next = temp->next;
	temp->next = new_node;
	return OK;
}

//STATUS InvertList(LIST* list)
//{
//	LIST nova;
//	LIST_NODE* temp;
//
//	while (*list != NULL)
//	{
//		InsertIni(&nova, (*list)->data);
//
//		(*list)->next;
//	}
//	*list = nova;
//	return OK;
//}

STATUS InvertList(LIST* list) {
	LIST nova = NULL;
	LIST_NODE* temp = NULL;
	LIST_NODE* pOrig = *list;

	while (*list != NULL) {
		InsertIni(&nova, DATA(pOrig));
		temp = pOrig;
		pOrig = NEXT(pOrig);
		free(temp);
	}

	*list = nova;
	return OK;
}


int main() {
	LIST linha1;
	ESTACAO* nova;

	initList(&linha1);
	if (ReadFile(&linha1, "Linha1.txt") == OK) {
		ShowStations(linha1);
		//SaveFile(list, "Linha1.txt");
		//RemoveFirstNode(&linha1);		//Leva o "&" pois vai fazer alterações na lista
		//printf("\nNumero de estacoes: %d\n", ListSize(linha1));
		if (DeleteStation(&linha1, "Lordelo")) {
			printf("Removida com sucesso");
		}
		else {
			printf("Estacao nao encontrada");
		}
		//nova = ReadStation();
		//InsertIni(&linha1, nova);

		ActiveStation(linha1, "Lordelo", FALSE);
		printf("\nO custo total da linha = %.2f", CustoTotal(linha1));

		printf("\n\n");
		ShowStations(linha1);
	};
	//SaveFile(linha1, "linha1_copy.txt");
	FreeList(&linha1);
	
}