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
#include <queue>
using namespace std;

#define min(A, B) A < B ? A : B
#define FLOW 0
#define CAPACITY 1
#define SOURCE 'f'
#define NORTH 'n'
#define SOUTH 's'
#define EAST 'd'
#define WEST 'e'
#define TARGET 't'
#define INVALID -1
#define SOURCE_ID -2
#define TARGET_ID numCol * numLin
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
int Edmondzinho(Vertice verts, int numLin, int numCol);
int getDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts);
void setDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts, int df);
char relatedPos(int from, int to, int numCol, int numLin);
int getVOfDir(int v, char dir, int numCol, int numLin);
int bfs(Vertice verts, int* pi, int numCol, int numLin);

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
	// ALGORITMANDO ------------------------------------------------------------
	Edmondzinho(verts, numLin, numCol);

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


int Edmondzinho(Vertice verts, int numLin, int numCol) {
	int v, flow = 0, numV = numCol * numLin, pi[numV + 1], df;

	while (bfs(verts, pi, numCol, numLin)) {
		df = verts[pi[TARGET_ID]].target[CAPACITY] - verts[pi[TARGET_ID]].target[FLOW];
		for (v = pi[TARGET_ID]; v != -1; v = pi[v]) {//PODE-SE POUPAR AQUI IF NEED
			df = min(df, getDiffFromTo(pi[v], v,  numCol, numLin, verts));
		}
		for (v = pi[TARGET_ID]; v != -1; v = pi[v]) {
			setDiffFromTo(pi[v], v,  numCol, numLin, verts, df);
		}
		flow += df;
	}
	return flow;
}


int getDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts) {
	switch (relatedPos(from, to, numCol, numLin)) {
		case SOURCE:
			return verts[to].fsource[CAPACITY] - verts[to].fsource[FLOW];
			break;
		case EAST:
			return verts[from].east[CAPACITY] - verts[from].east[FLOW];
			break;
		case WEST:
			return verts[from].west[CAPACITY] - verts[from].west[FLOW];
			break;
		case SOUTH:
			return verts[from].south[CAPACITY] - verts[from].south[FLOW];
			break;
		case NORTH:
			return verts[from].north[CAPACITY] - verts[from].north[FLOW];
			break;
		case TARGET:
			return verts[from].target[CAPACITY] - verts[from].target[FLOW];
			break;
		default:
			return INVALID;
			break;
	}
}

void setDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts, int df) {
	switch (relatedPos(from, to, numCol, numLin)) {
		case SOURCE:
			verts[to].fsource[FLOW] += df;
			break;
		case EAST:
			verts[from].east[FLOW] += df;
			verts[to].west[FLOW] -= df;
			break;
		case WEST:
			verts[from].west[FLOW] += df;
			verts[to].east[FLOW] -= df;
			break;
		case SOUTH:
			verts[from].south[FLOW] += df;
			verts[to].north[FLOW] -= df;
			break;
		case NORTH:
			verts[from].north[FLOW] += df;
			verts[to].south[FLOW] -= df;
			break;
		case TARGET:
			verts[from].target[FLOW] += df;
			break;
		default:
			break;
	}
}

char relatedPos(int from, int to, int numCol, int numLin) {
	if (from == SOURCE_ID) {
		return SOURCE;
	} else if (to == TARGET_ID) {
		return TARGET;
	} else if (to - 1 == from) {
		return EAST;
	} else if (to + 1 == from) {
		return WEST;
	} else if ( (to - from) > 0 && (to - from) % numCol == 0 ) {
		return SOUTH;
	} else {
		return NORTH;
	}
}

int getVOfDir(int v, char dir, int numCol, int numLin) {
	switch (dir) {
		case EAST:
			return (v + 1) % numCol ? -1 : v + 1;
			break;
		case WEST:
			return v % numCol ? -1 : v - 1;
			break;
		case SOUTH:
			return numCol * (numLin - 1) <= v ? -1 : v + numCol;
			break;
		case NORTH:
			return v < numCol ? -1 : v - numCol;
			break;
		case TARGET:
			return TARGET_ID;
			break;
		default:
			return INVALID;
			break;
	}
}


int bfs(Vertice verts, int* pi, int numCol, int numLin) {
	queue<int> queueV;
	int v, d, nextV, numV = numCol * numLin;
	char dirs[5] = {NORTH, SOUTH, EAST, WEST, TARGET};

	for(v = 0; v<numV; v++) {
		if (getDiffFromTo(SOURCE_ID, v, numCol, numLin, verts)) {
			queueV.push(v);
			pi[v] = SOURCE_ID;
		} else {
			pi[v] = INVALID;
		}
	}

	while (queueV.size()) {
		v = queueV.front();
		queueV.pop();
		for(d = 0; d<5; d++) {
			nextV = getVOfDir(v, dirs[d], numCol, numLin);
			if (nextV != INVALID && pi[nextV] == INVALID && getDiffFromTo(v, nextV, numCol, numLin, verts)) {
				queueV.push(nextV);
				pi[nextV] = v;
			}
		}
	}
	return pi[TARGET_ID] != INVALID;
}
