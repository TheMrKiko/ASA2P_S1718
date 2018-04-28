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
#include <stack>
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
} * Vertice;

/********************************* PROTOTIPOS *********************************/
void printVertices(Vertice verts, int);

/************************************ MAIN ************************************/
int main(int argc, char const* argv[]) {
    int numLin, numCol, numV, aux, l, c, v, min;
	Vertice verts;

    // LER INPUT ---------------------------------------------------------------
    // tamanhos iniciais das tabelas -------------
    if (!scanf("%d %d", &numLin, &numCol) || numLin <= 0 || numCol <= 0 ) {
		printf("Deu erro a ler\n");
	}

	numV = numLin * numCol;
	verts = new vertice[numV + 1];

    // pesos do primeiro plano -------------
	// getchar();

	for (v = 0; v < numV; v++) {
		scanf("%d", &verts[v].fsource[CAPACITY]);
		verts[v].fsource[FLOW] = 0;
	}

    /*printf("plano:\n");
    for (v = 0; v < numV; v++) {
        printf("%d/%d-", verts[v].fsource[FLOW], verts[v].fsource[CAPACITY]);
    }
    printf("\n------\n");*/

	// pesos do cenario -------------
	// getchar();

	for (v = 0; v < numV; v++) {
		scanf("%d", &verts[v].target[CAPACITY]);
		verts[v].target[FLOW] = 0;
	}
    /*for (v = 0; v < numV; v++) {
        printf("%d-%d", verts[v].target[FLOW], verts[v].target[CAPACITY]);
    }
    printf("\n------\n");*/

    // pesos das vizinhancas horizontais -------------
    // getchar();
	for (l = 0; l < numLin; l++) {
		for (c = 0; c < numCol - 1; c++) {
			scanf("%d", &aux);
			verts[pos(l, c)].east[CAPACITY] = aux;
			verts[pos(l, c)].east[FLOW] = 0;
			verts[pos(l, c+1)].west[CAPACITY] = aux;
			verts[pos(l, c+1)].west[FLOW] = 0;
		}
	}

    // pesos das vizinhancas verticais -------------
	// getchar();
	for (l = 0; l < numLin - 1; l++) {
		for (c = 0; c < numCol; c++) {
			scanf("%d", &aux);
			verts[pos(l, c)].south[CAPACITY] = aux;
			verts[pos(l, c)].south[FLOW] = 0;
			verts[pos(l+1, c)].north[CAPACITY] = aux;
			verts[pos(l+1, c)].north[FLOW] = 0;
		}
	}

	// PUSHEI PUSHANDO da source para a target toda ----------------------------
	for (v = 0; v < numV; v++) {
		min = min(verts[v].fsource[CAPACITY], verts[v].target[CAPACITY]);
		verts[v].fsource[FLOW] = verts[v].target[FLOW] = min;
	}
	printVertices(verts, numV);

	return 0;
}

/******************************* OUTRAS FUNCOES *******************************/
void printVertices(Vertice verts, int numV) {
	int v;
	for (v = 0; v < numV; v++) {
		printf("V: %d - %d/%d | n%d/%d s%d/%d e%d/%d o%d/%d | %d/%d\n", v,
		verts[v].fsource[FLOW], verts[v].fsource[CAPACITY],
		verts[v].north[FLOW], verts[v].north[CAPACITY],
		verts[v].south[FLOW], verts[v].south[CAPACITY],
		verts[v].east[FLOW], verts[v].east[CAPACITY],
		verts[v].west[FLOW], verts[v].west[CAPACITY],
		verts[v].target[FLOW], verts[v].target[CAPACITY]);
	}
}


void Edmondzinho(Vertice verts, int numV, int numCol) {
	int i, flow = 0, targ = numV, pi[numV], foundPath = 1, df;

	for (i=0; i<numV; i++) {
		pi[i] = -1;
	}
	do {
		foundPath = bfs(verts, pi);
	} while (foundPath) {

		df = verts[pi[targ]].target[CAPACITY] - verts[pi[targ]].target[FLOW];
		for (v = pi[targ]; v != -1; v = pi[v]) {//PODE-SE POUPAR AQUI IF NEED
			df = min(df, getDiffFromTo(p[v], v,  numCol));
		}

	}

}

int getDiffFromTo(int from, int to, int numCol, Vertice verts) {
	switch (relatedPos(from, to, numCol)) {
		case 'd':
			return verts[from].east[CAPACITY] - verts[to].east[FLOW];
			break;
		case 'e':
			return verts[from].west[CAPACITY] - verts[to].west[FLOW];
			break;
		case 's':
			return verts[from].south[CAPACITY] - verts[to].south[FLOW];
			break;
		case 'n':
			return verts[from].north[CAPACITY] - verts[to].north[FLOW];
			break;
	}
}

void setDiffFromTo(int from, int to, int numCol, Vertice verts) {
	switch (relatedPos(from, to, numCol)) {
		case 'd':
			verts[from].east[CAPACITY] - verts[to].east[FLOW];
			break;
		case 'e':
			verts[from].west[CAPACITY] - verts[to].west[FLOW];
			break;
		case 's':
			verts[from].south[CAPACITY] - verts[to].south[FLOW];
			break;
		case 'n':
			verts[from].north[CAPACITY] - verts[to].north[FLOW];
			break;
	}
}

char relatedPos(int from, int to, int numCol) {
	if (to - from == 1 ) {
		return 'd'
	} else if (to - from == -1) {
		return 'e';
	} else if ( (to - from) > 0 && (to - from) % numCol == 0 ) {
		return 's';
	} else {
		return 'n';
	}
}

void joaochupaila()
