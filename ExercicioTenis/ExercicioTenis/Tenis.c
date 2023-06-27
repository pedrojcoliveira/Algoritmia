#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME 20
#define STAGES 15
typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;

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

BTREE_NODE* NewBtreeNode(void* data);
BTREE_NODE* AddBtreeNode(BTREE_NODE* upnode, BTREE_NODE* node, BTREE_LOCATION where);
int BtreeSize(BTREE btree);	//Número de nós
int BtreeDeep(BTREE btree); //profundidade <=> múmero de níveis
BOOLEAN BtreeLeaf(BTREE_NODE* node); //Se é folha
BTREE_NODE* InitNode(void*, BTREE_NODE*, BTREE_NODE*);  //1 ponteiro para dados e 2 ponteiros para os nós
BTREE_NODE* CreateBtree(void**, int, int);
STATUS ReadPlayersFromFile(void**, char*); //Ler de um ficheiro para um vetor
void PrintLeafs(BTREE);  //Imprime os nós folhas
void BtreeFree(BTREE);   //Liberta a memória da árvore
void PrintWinnerGames(BTREE);	//Imprime os jogos realizados pelo vencedor
int CountTotalSets(BTREE);		//Soma o total dos sets
int CountWinnerSets(BTREE, void*);  //Somar o total sets do vencedor
void PrintAllGames(BTREE);		//Mostrar todos os jogos
int CountLeafs(BTREE btree);
void PrintGame(BTREE btree);
void PrintPlayerGames(BTREE btree, char* nome);
int SetsGanhosPlayer(BTREE btree, char* nome);	//Numero de sets ganhos pelo jogador nome
int SetsJogadosPlayer(BTREE btree, char* nome);
void JogadorMaisDireita(BTREE btree);
void JogosEliminatoria(BTREE, int);
void EliminarJogador(BTREE, char*);
BOOLEAN MudarNomeJogador(BTREE, char*, char*);

int main(int argc, char* argv[])
{
	BTREE Btree;
	void* players[STAGES];
	char file_name[MAX_NAME];
	//printf("Nome do ficheiro: ");
	//scanf("%s", file_name);
	if (ReadPlayersFromFile(players, "torneio.txt"))
	{
		Btree = CreateBtree(players, 0, STAGES);
		printf("\nLista de participantes: %d\n", CountLeafs(Btree));
		PrintLeafs(Btree);
		printf("\nLista de Jogos:\n");
		PrintAllGames(Btree);
		printf("\nNúmero de eliminatórias: %d", BtreeDeep(Btree) - 1);
		printf("\nNúmero de Jogos: %d", BtreeSize(Btree) / 2);
		printf("\nNúmero de Sets: %d", CountTotalSets(Btree));
		printf("\nVencedor do torneio: %s\n", ((PLAYER*)DATA(Btree))->name);
		printf("\nJogos disputados pelo Vencedor:\n");
		PrintWinnerGames(Btree);
		printf("Jogos jogados pelo Jogador 2\n");
		PrintPlayerGames(Btree, "Jogador2");
		printf("\nSets Ganhos pelo Jogador: %d\n", SetsGanhosPlayer(Btree, "Jogador2"));
		printf("\nSets Jogados pelo Jogador: %d\n", SetsJogadosPlayer(Btree, "Jogador2"));
		printf("\nSets ganhos pelo Vencedor: %d\n", CountWinnerSets(Btree, DATA(Btree)));  //DATA(RIGHT(Btree))))   -> Jogador da Direita
		printf("\nJogador mais à direita:\n");
		JogadorMaisDireita(Btree);
		printf("\nJogo da final: \n");
		PrintGame(Btree);
		printf("\nJogos dos quartos final: \n");
		JogosEliminatoria(Btree, 1);

		if (MudarNomeJogador(Btree, "Jogador5", "XPTO") == TRUE)
		{
			printf("Troca efextuada\n");
		}
		else
		{
			printf("\nJogador não encontrado\n");
		}
		//MudarNomeJogador(Btree, "Jogador4", "XPTO");

		EliminarJogador(Btree, "Jogador7");
		printf("\nLista de Jogos:\n");
		PrintAllGames(Btree);
		BtreeFree(Btree);

	}
	else
		printf("ERRO na leitura do ficheiro\n");

	return 0;
}
BTREE_NODE* NewBtreeNode(void* data)
{
	BTREE_NODE* tmp_pt;
	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)
	{
		DATA(tmp_pt) = data;
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL;
	}
	return tmp_pt;
}
BTREE_NODE* AddBtreeNode(BTREE_NODE* upnode, BTREE_NODE* node, BTREE_LOCATION where)
{
	BTREE_NODE* tmp_pt = upnode;
	if (where == BTREE_LEFT)
	{
		if (LEFT(upnode) == NULL)
			LEFT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	else
	{
		if (RIGHT(upnode) == NULL)
			RIGHT(upnode) = node;
		else
			tmp_pt = NULL;
	}
	return tmp_pt;
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

void BtreeFree(BTREE btree)
{
	if (btree != NULL)
	{
		BtreeFree(LEFT(btree));
		BtreeFree(RIGHT(btree));
		free(btree);
	}
}
int BtreeSize(BTREE btree)
{
	int count = 0;
	if (btree != NULL)
		count = 1 + BtreeSize(LEFT(btree)) + BtreeSize(RIGHT(btree));
	return(count);

	//OU
	//return (btree == NULL) ? 0 : 1 + BtreeSize(LEFT(btree)) + BtreeSize(RIGHT(btree));
}
BOOLEAN BtreeLeaf(BTREE_NODE* btree)
{
	if ((LEFT(btree) == NULL) && (RIGHT(btree) == NULL))
		return(TRUE);
	else
		return(FALSE);

	//OU
	//return ((LEFT(btree) == NULL) && (RIGHT(btree) == NULL)) ? TRUE : FALSE;
}
int BtreeDeep(BTREE btree)
{
	int deep = 0, left, right;
	if (btree != NULL)
	{
		left = BtreeDeep(LEFT(btree));
		right = BtreeDeep(RIGHT(btree));
		deep = 1 + ((left > right) ? left : right);
	}
	return(deep);
}

STATUS ReadPlayersFromFile(void** players, char* file_name)
{
	FILE* fp;
	int j, i = 0;
	void* ptr_data;
	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = malloc(sizeof(PLAYER))) != NULL)
			{
				fscanf(fp, "%[^;];", ((PLAYER*)ptr_data)->name);
				fscanf(fp, "%d\n", &(((PLAYER*)ptr_data)->sets));
				players[i] = ptr_data;
				i++;
			}
			else
			{
				for (j = i; j >= 0; j--)
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}

void PrintLeafs(BTREE btree)
{
	if (BtreeLeaf(btree))
		printf("\n%s", ((PLAYER*)DATA(btree))->name);
	else {
		PrintLeafs(LEFT(btree));
		PrintLeafs(RIGHT(btree)); 
	}
	
}

void PrintWinnerGames(BTREE btree)
{
	if (btree != NULL && !BtreeLeaf(btree))
	{
		PrintGame(btree);
		if (!strcmp(((PLAYER*)DATA(LEFT(btree)))->name,((PLAYER*)DATA(btree))->name))
			PrintWinnerGames(LEFT(btree));
		else
			PrintWinnerGames(RIGHT(btree));
	}
}

int CountTotalSets(BTREE btree)
{
	if (btree != NULL)
	{
		return CountTotalSets(LEFT(btree)) + CountTotalSets(RIGHT(btree)) + ((PLAYER*)DATA(btree))->sets;  //Método Post-Order
	}
	return 0;
}

int CountWinnerSets(BTREE btree, void* winner)
{
	int total = 0;

	if (btree != NULL)
	{
		if (!strcmp(((PLAYER*)DATA(btree))->name, ((PLAYER*)winner)->name))   //(if (strcmp(((PLAYER*)DATA(btree))->name, ((PLAYER*)winner)->name) == FALSE))
		{
			total += ((PLAYER*)DATA(btree))->sets;
		}
		total += CountWinnerSets(LEFT(btree), winner) + CountWinnerSets(RIGHT(btree), winner);
	}
	return total;
}

void PrintAllGames(BTREE btree)
{
	if (btree != NULL && !BtreeLeaf(btree))
	{
		PrintAllGames(LEFT(btree));
		PrintAllGames(RIGHT(btree));
		PrintGame(btree);
	}
}

int CountLeafs(BTREE btree)
{
	if (BtreeLeaf(btree))
		return 1;
	return CountLeafs(LEFT(btree)) + CountLeafs(RIGHT(btree));
}

void PrintGame(BTREE btree)
{
	if (btree != NULL && !BtreeLeaf(btree))
	{
		printf("\t%s (%d) <--> (%d) %s\n", ((PLAYER*)DATA(LEFT(btree)))->name, ((PLAYER*)DATA(LEFT(btree)))->sets, ((PLAYER*)DATA(RIGHT(btree)))->sets, ((PLAYER*)DATA(RIGHT(btree)))->name);
	}
}

void PrintPlayerGames(BTREE btree, char* nome)
{
	if (btree != NULL && !BtreeLeaf(btree))
	{
		PrintPlayerGames(LEFT(btree), nome);
		PrintPlayerGames(RIGHT(btree), nome);
		if (!strcmp(((PLAYER*)DATA(LEFT(btree)))->name, nome) || !strcmp(((PLAYER*)DATA(RIGHT(btree)))->name, nome))
		{
			PrintGame(btree);
		}
	}

}

int SetsGanhosPlayer(BTREE btree, char* nome)
{
	int count = 0;
	if (btree != NULL)
	{
	if (!strcmp(((PLAYER*)DATA(btree))->name, nome))
		count += ((PLAYER*)DATA(btree))->sets;
	count += SetsGanhosPlayer(LEFT(btree), nome) + SetsGanhosPlayer(RIGHT(btree), nome);
	}
	return count;
}

int SetsJogadosPlayer(BTREE btree, char* nome)
{
	int count = 0;
	if (btree != NULL && !BtreeLeaf(btree))
	{
		if (!strcmp(((PLAYER*)DATA(LEFT(btree)))->name, nome) || !strcmp(((PLAYER*)DATA(RIGHT(btree)))->name, nome))
		{
			count += SetsJogadosPlayer(LEFT(btree), nome) + SetsJogadosPlayer(RIGHT(btree), nome);
		}
	}
	return count;
}

void JogadorMaisDireita(BTREE btree)
{
	if (btree != NULL)
	{
		if (RIGHT(btree) == NULL)
			printf("\O jogador mais à direita = %s", ((PLAYER*)DATA(btree))->name);
		JogadorMaisDireita(RIGHT(btree));
	}
}

void JogosEliminatoria(BTREE btree, int eliminatoria)
{
	if (btree != NULL && !BtreeLeaf(btree))
	{
		if (BtreeDeep(btree) == eliminatoria + 1)
			PrintGame(btree);
		JogosEliminatoria(LEFT(btree), eliminatoria);
		JogosEliminatoria(RIGHT(btree), eliminatoria);
	}
}

void EliminarJogador(BTREE btree, char* nome)
{
	if (btree != NULL && !BtreeLeaf(btree))
	{
		if (!strcmp(((PLAYER*)DATA(LEFT(btree)))->name, nome) || !strcmp(((PLAYER*)DATA(RIGHT(btree)))->name, nome))
		{
			BtreeFree(LEFT(btree));
			BtreeFree(RIGHT(btree));
			LEFT(btree) = NULL;
			RIGHT(btree) = NULL;
			return;
		}
		else
		{
			EliminarJogador(LEFT(btree), nome);
			EliminarJogador(RIGHT(btree), nome);
		}
	}
}

BOOLEAN MudarNomeJogador(BTREE btree, char* nome, char* novonome)
{
	BOOLEAN find = FALSE;

	if (btree != NULL)
	{
		if (!strcmp(((PLAYER*)DATA(btree))->name, nome))
		{
			strcpy(((PLAYER*)DATA(btree))->name, novonome);
			find = TRUE;
		}
		find = find || MudarNomeJogador(LEFT(btree), nome, novonome);
		find = find || MudarNomeJogador(RIGHT(btree), nome, novonome);
	}
	return find;
}