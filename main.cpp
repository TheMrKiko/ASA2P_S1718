/*******************************************************************************/
/*********************** ANALISE E SINTESE DE ALGORITMOS ***********************/
/********************************* 2o Projecto *********************************/
/*******************************************************************************/
/*******************************************************************************/
/*************************** JOAO DANIEL SILVA 86445 ***************************/
/**************************** FRANCISCO SOUSA 86416 ****************************/
/********************************** GRUPO 154 **********************************/
/*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define min(A, B) A < B ? A : B
#define FLOW 0
#define CAPACITY 1
#define pos(line, column) line * numCol + column

/********************************* ESTRUTURAS *********************************/
typedef struct vertice {
	int north[2];
	int south[2];
	int east[2];
	int west[2];
	int fsource[2];
	int target[2];
} Vertice;

/********************************* PROTOTIPOS *********************************/

/************************************ MAIN ************************************/
int main(int argc, char const* argv[]) {
    int numLin, numCol, numV, aux, l, c, v;
	Vertice* vertices;

    // LER INPUT
    // tamanhos iniciais das tabelas -------------
    if (!scanf("%d %d", &numLin, &numCol) || numLin <= 0 || numCol <= 0 ) {
		printf("Deu erro a ler\n");
	}

	numV = numLin * numCol;
	vertices = new vertice[numV + 1];

    // pesos do primeiro plano -------------
	// getchar();

	for (v = 0; v < numV; v++) {
		scanf("%d", &vertices[v].fsource[CAPACITY]);
		vertices[v].fsource[FLOW] = 0;
	}

    /*printf("plano:\n");
    for (v = 0; v < numV; v++) {
        printf("%d/%d-", vertices[v].fsource[FLOW], vertices[v].fsource[CAPACITY]);
    }
    printf("\n------\n");*/

	// pesos do cenario -------------
	// getchar();

	for (v = 0; v < numV; v++) {
		scanf("%d", &vertices[v].target[CAPACITY]);
		vertices[v].target[FLOW] = 0;
	}
    /*for (v = 0; v < numV; v++) {
        printf("%d-%d", vertices[v].target[FLOW], vertices[v].target[CAPACITY]);
    }
    printf("\n------\n");*/

    // pesos das vizinhancas horizontais -------------
    // getchar();
	for (l = 0; l < numLin; l++) {
		for (c = 0; c < numCol - 1; c++) {
			scanf("%d", &aux);
			vertices[pos(l, c)].east[CAPACITY] = aux;
			vertices[pos(l, c)].east[FLOW] = 0;
			vertices[pos(l, c+1)].west[CAPACITY] = aux;
			vertices[pos(l, c+1)].west[FLOW] = 0;
		}
	}

    // pesos das vizinhancas verticais
	// getchar();
	for (l = 0; l < numLin - 1; l++) {
		for (c = 0; c < numCol; c++) {
			scanf("%d", &aux);
			vertices[pos(l, c)].south[CAPACITY] = aux;
			vertices[pos(l, c)].south[FLOW] = 0;
			vertices[pos(l+1, c)].north[CAPACITY] = aux;
			vertices[pos(l+1, c)].north[FLOW] = 0;
		}
	}

	return 0;
}

/******************************* OUTRAS FUNCOES *******************************/
