#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include <stdio.h>
#include <string.h>


#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pLeft)
#define RIGHT(node) ((node)->pRight)
typedef enum _STATUS { OK, ERROR } STATUS;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;



// Definição da estrutura PERSON
typedef struct _PERSON {
	char name[30];
	int age;
	BOOLEAN deceased;
} PERSON;


// Definição da estrutura BT_NODE
typedef struct _BT_NODE {
	void* pData;
	struct _BT_NODE* pLeft;
	struct _BT_NODE* pRight;
} BT_NODE;


typedef BT_NODE* BT;
//Declaração das funções
BT_NODE* initNode(void*, BT_NODE*, BT_NODE*);
BT_NODE* createNewBTNode(void*);
BT createBT(PERSON*, int, int);
BOOLEAN emptyBTree(BT);
BOOLEAN isLeaf(BT_NODE*);
void printPersonBTree(BT);
void changeExpenses(BT, float, float);
void changeStaff(BT);
BT transformBTree(BT);
#define NMAX 15


int main(int argc, char* argv[])
{
	BT T = NULL;
	char name[20];
	PERSON v[] = { "Xavier",45,FALSE,

	"Jorge",74,FALSE,"Luisa",69,FALSE,
	"Raul",58,TRUE,"Joaquina",72,TRUE,"Marco",77,TRUE,"Teresa",91,FALSE,
	"Antero",70,TRUE,"Maria",86,TRUE,"Carlos",81,TRUE,"Sandra",36,TRUE,
	"Duarte",72,TRUE,"Ilda",84,TRUE,"Alfredo",55,TRUE,"Francisca",77,TRUE };

	T = createBT(v, 0, NMAX); printPersonBTree(T);


	//1
	printParents(T, name);

	//2
	maxAgeGreatGreatParents(T);

		return 1;
}

// Função que verifica se uma árvore binária está vazia
BOOLEAN emptyBTree(BT T)
{
	return (T == NULL) ? TRUE : FALSE;
}
// Função que verifica se um nó é uma folha
BOOLEAN isLeaf(BT_NODE* pT)
{
	return ((LEFT(pT) == NULL) && (RIGHT(pT) == NULL)) ? TRUE : FALSE;
}
// Função que cria um nó
BT_NODE* createNewBTNode(void* pData)
{
	BT_NODE* pTemp;
	if ((pTemp = (BT_NODE*)malloc(sizeof(BT_NODE))) != NULL) {
		DATA(pTemp) = pData; LEFT(pTemp) = RIGHT(pTemp) = NULL;
	}
	return pTemp;
}
// Funções que criam a BST
BT createBT(PERSON v[], int i, int size)
{
	if (i >= size) return(NULL);
	else return(initNode(&v[i], createBT(v, 2 * i + 1, size), createBT(v, 2 * i + 2, size)));
}
BT_NODE* initNode(void* pData, BT_NODE* n1, BT_NODE* n2)
{
	BT_NODE* pTemp = NULL;
	pTemp = createNewBTNode(pData);
	LEFT(pTemp) = n1;
	RIGHT(pTemp) = n2;
	return(pTemp);
}
// Função que apresenta a árvore binária (de elementos de tipo PERSON)
void printPersonBTree(BT T)
{
	if (emptyBTree(T) == TRUE) return;
	printPersonBTree(LEFT(T));
	printf("\nnome : %s - idade : %d (%s)", ((PERSON*)DATA(T))->name,
		((PERSON*)DATA(T))->age, ((PERSON*)DATA(T))->deceased ? "falecido" : "vivo");
	printPersonBTree(RIGHT(T));
	return;
}

//1
void printParents(BT T, char* name)
{
	if (T == NULL)
	{
		printf("A arvore esta vazia");
	}

	BT_NODE* current = T;
	BT_NODE* parent = NULL;

	while (current != NULL)
	{
		if (!strcmp(((PERSON*)DATA(current))->name, name))
		{
			if (parent != NULL)
			{
				printf("Pai do %s: %s\n", name, ((PERSON*)DATA(parent))->name);
			}
			else
			{
				printf("%s nao tem pais na arvore.\n", name);
			}
			return;
		}
		else if (!strcmp(((PERSON*)DATA(current))->name, name) > 0)
		{
			parent = current;
			current = LEFT(current);
		}
		else
		{
			parent = current;
			current = RIGHT(current);
		}
	}
	printf("%s nao foi encontrado na arvore.\n", name);
}

//1
void PrintParents(BT T, char* name)
{
	if (T != NULL && !isLeaf)
	{
		if (!strcmp(((PERSON*)DATA(T))->name, name))
		{
			printPersonBTree(name);
		}
		else
		{
			printf("Não há informações sobre os pais de %s.\n", name);
		}
		PrintParents(LEFT(T), name);
		PrintParents(RIGHT(T), name);
	}
}


//OUTRA PROPOSTA
//void printParents(BT T, char* name)
//{
//	if (T == NULL) {
//		printf("Não existe informação sobre essa pessoa.\n");
//		return;
//	}
//
//	if (strcmp(((PERSON*)DATA(T))->name, name) == 0) {
//		// Encontrou a pessoa cujos pais deseja imprimir
//		if (LEFT(T) != NULL && RIGHT(T) != NULL) {
//			PERSON* father = LEFT(T)->pData;
//			PERSON* mother = RIGHT(T)->pData;
//			printf("Pais de %s: Pai - %s, Mãe - %s\n", name, father->name, mother->name);
//		}
//		else {
//			printf("Não há informação sobre os pais de %s.\n", name);
//		}
//		return;
//	}
//
//	// Procurar na subárvore esquerda
//	printParents(LEFT(T), name);
//
//	// Procurar na subárvore direita
//	printParents(RIGHT(T), name);
//}



//2
int maxAgeGreatGreatParents(BT T)
{
	if (T == NULL)
	{
		return -1;

		int maxAge = 0;

		//verificar bisavô paterno
		if (LEFT(T) != NULL && LEFT(LEFT(T)) != NULL)
		{
			PERSON* paternGrandfather = LEFT(LEFT(T))->pData;
			if (paternGrandfather->age > maxAge)
			{
				maxAge = paternGrandfather->age;
			}
		}
		// Verificar bisavó paterna
		if (LEFT(T) != NULL && LEFT(RIGHT(T)) != NULL) {
			PERSON* paternalGrandmother = LEFT(RIGHT(T))->pData;
			if (paternalGrandmother->age > maxAge) {
				maxAge = paternalGrandmother->age;
			}
		}

		// Verificar bisavô materno
		if (RIGHT(T) != NULL && RIGHT(LEFT(T)) != NULL) {
			PERSON* maternalGrandfather = RIGHT(LEFT(T))->pData;
			if (maternalGrandfather->age > maxAge) {
				maxAge = maternalGrandfather->age;
			}
		}

		// Verificar bisavó materna
		if (RIGHT(T) != NULL && RIGHT(RIGHT(T)) != NULL) {
			PERSON* maternalGrandmother = RIGHT(RIGHT(T))->pData;
			if (maternalGrandmother->age > maxAge) {
				maxAge = maternalGrandmother->age;
			}
		}
		return maxAge;
	}
}



//3
int maxAgeSide(BT T)
{
	int maxAgePaterno = maxAgeGreatGreatParents(LEFT(T));  //Idade máxima no lado paterno
	int maxAgeMaterno = maxAgeGreatGreatParents(RIGHT(T));	//Idade máxima do lado materno

	if (maxAgePaterno >= maxAgeMaterno)
	{
		return 0;	//Lado paterno tem a pessoa que viveu mais anos
	}
	else
	{
		return 1;	//Lado materno tem a pessoa que viveu mais anos
	}
}