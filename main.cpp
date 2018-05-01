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
#include <stack>
using namespace std;

#define min(A, B) A < B ? A : B
#define cp(A) A ? 'C' : 'P'
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
#define FOREGROUND 0
#define BACKGROUND 1
#define pos(line, column) ((line) * (numCol)) + (column)

/********************************* ESTRUTURAS *********************************/
typedef struct vertice {
	int north;
	int south;
	int east;
	int west;
	int fsource;
	int target;
}* Vertice;

typedef int* Table;

/********************************* PROTOTIPOS *********************************/
int EdmondzinhoSkarp(Vertice verts, Table d, int numLin, int numCol);
int pushFlow(Vertice verts, int numV);
int BFS(Vertice verts, Table pi, int numCol, int numLin);
void DFS(Vertice verts, Table disc, int numCol, int numLin);
char relatedPos(int from, int to, int numCol, int numLin);
void outpuThis(Table disc, int flow, int numLin, int numCol);
int getVertixInDir(int v, char dir, int numCol, int numLin);
int getDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts);
void setDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts, int df);
void printVertices(Vertice verts, int);
void pis(Table pi, int numV);

/************************************ MAIN ************************************/
int main(int argc, char const* argv[]) {
    int numLin, numCol, numV, aux, flow, l, c, v;
	Table disc;
	Vertice verts;

    // LER INPUT ---------------------------------------------------------------
    // tamanhos iniciais das tabelas -------------
    if (!scanf("%d %d", &numLin, &numCol) || numLin <= 0 || numCol <= 0) {
		printf("Deu erro a ler\n");
	}

	numV = numLin * numCol;
	verts = new vertice[numV + 1];
	disc = new int[numV + 1];

    // pesos do primeiro plano -------------
	// getchar();
	for (v = 0; v < numV; v++) {
		scanf("%d", &verts[v].fsource);
	}

	// pesos do cenario -------------
	// getchar();
	for (v = 0; v < numV; v++) {
		scanf("%d", &verts[v].target);
	}

    // pesos das vizinhancas horizontais -------------
    // getchar();
	for (l = 0; l < numLin; l++) {
		for (c = 0; c < numCol - 1; c++) {
			scanf("%d", &aux);
			verts[pos(l, c)].east = aux;
			verts[pos(l, c+1)].west = aux;
			//printf("%d %d: mete o e%d a %d/%d e o w%d a %d/%d\n", l, c, pos(l, c), 0, aux, pos(l, c+1), aux, aux);
		}
	}

    // pesos das vizinhancas verticais -------------
	// getchar();
	for (l = 0; l < numLin - 1; l++) {
		for (c = 0; c < numCol; c++) {
			scanf("%d", &aux);
			verts[pos(l, c)].south = aux;
			verts[pos(l+1, c)].north = aux;
			//printf("%d %d: mete o s%d a %d/%d e o n%d a %d/%d\n", l, c, pos(l, c), 0, aux, pos(l+1, c), aux, aux);

		}
	}
	//printVertices(verts, numV);
	// PUSHEI PUSHANDO da source para a target toda ----------------------------
	flow = pushFlow(verts, numV);

	// ALGORITMANDO ------------------------------------------------------------
	flow += EdmondzinhoSkarp(verts, disc, numLin, numCol);

	// IMPRIMINDO --------------------------------------------------------------
	outpuThis(disc, flow, numLin, numCol);
	//printVertices(verts, numV);
	//FREES
	return 0;
}

/********************************** ALGORITMO *********************************/
int EdmondzinhoSkarp(Vertice verts, Table disc, int numLin, int numCol) {
	int v, flow = 0, numV = numCol * numLin, df;
	Table pi = new int[numV + 1];

	while (BFS(verts, pi, numCol, numLin)) {
		df = verts[pi[TARGET_ID]].target;
		for (v = TARGET_ID; v != INVALID && v != SOURCE_ID; v = pi[v]) {//PODE-SE POUPAR AQUI IF NEED
			df = min(df, getDiffFromTo(pi[v], v,  numCol, numLin, verts));
		}
		for (v = TARGET_ID; v != INVALID && v != SOURCE_ID; v = pi[v]) {
			setDiffFromTo(pi[v], v,  numCol, numLin, verts, df);
		}
		flow += df;
	}
	DFS(verts, disc, numCol, numLin);

	return flow;
}

void outpuThis(Table disc, int flow, int numLin, int numCol) {
	int l, c;

	printf("%d\n\n", flow);
	for (l = 0; l < numLin; l++) {
		for (c = 0; c < numCol; c++) {
			printf("%c ", cp(disc[pos(l, c)]));
		}
		printf("\n");
	}
}

/********************************** BFS E DFS *********************************/
int BFS(Vertice verts, Table pi, int numCol, int numLin) {
	queue<int> queueV;
	int v, d, nextV, numV = numCol * numLin;
	char dirs[5] = {NORTH, SOUTH, EAST, WEST, TARGET};

	pi[numV] = INVALID;
	for (v = 0; v < numV; v++) {
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
		for(d = 0; d < 5; d++) {
			nextV = getVertixInDir(v, dirs[d], numCol, numLin);
			if (nextV != INVALID && pi[nextV] == INVALID && getDiffFromTo(v, nextV, numCol, numLin, verts)) {
				queueV.push(nextV);
				pi[nextV] = v;
			}
		}
	}
	return pi[TARGET_ID] != INVALID;
}

void DFS(Vertice verts, Table disc, int numCol, int numLin) {
	stack<int> stackV;
	int v, d, numV = numCol * numLin, nextV;
	char dirs[5] = {NORTH, SOUTH, EAST, WEST, TARGET};

	for (v = 0; v < numV; v++) {
		//printf("oi caralho %d %d\n", verts[v].fsource, getDiffFromTo(SOURCE_ID, v, numCol, numLin, verts) );
		if (getDiffFromTo(SOURCE_ID, v, numCol, numLin, verts)) {
			stackV.push(v);
			disc[v] = FOREGROUND;
		}
	}
	while (stackV.size()) {
		v = stackV.top();
		stackV.pop();
		if (disc[v] == FOREGROUND) {
			disc[v] = BACKGROUND;
			//printf("fui descoberto %d\n", v);
			for (d = 0; d < 5; d++) {
				nextV = getVertixInDir(v, dirs[d], numCol, numLin);
				//printf("%d a encontrar %d\n", v, nextV);
				if (nextV != INVALID && getDiffFromTo(v, nextV, numCol, numLin, verts)) {
					stackV.push(nextV);
				}
			}
		}
	}
}

/******************************* OUTRAS FUNCOES *******************************/
int pushFlow(Vertice verts, int numV) {
	int min, v, flow = 0;

	for (v = 0; v < numV; v++) {
		min = min(verts[v].fsource, verts[v].target);
		verts[v].fsource -=  min;
		verts[v].target -= min;
		flow += min;
	}
	return flow;
}

void printVertices(Vertice verts, int numV) {
	/*int v;

	for (v = 0; v < numV; v++) {
		printf("V: %d - %d/%d | n%d/%d s%d/%d e%d/%d w%d/%d | %d/%d\n", v+1,
		verts[v].fsource[FLOW], verts[v].fsource[CAPACITY],
		verts[v].north[FLOW], verts[v].north[CAPACITY],
		verts[v].south[FLOW], verts[v].south[CAPACITY],
		verts[v].east[FLOW], verts[v].east[CAPACITY],
		verts[v].west[FLOW], verts[v].west[CAPACITY],
		verts[v].target[FLOW], verts[v].target[CAPACITY]);
	}*/
}

void pis(Table pi, int numV) {
	int v;

	for (v = 0; v < numV + 1; v++) {
		printf("Pi[%d]: %d\n", v, pi[v]);
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

int getVertixInDir(int v, char dir, int numCol, int numLin) {
	switch (dir) {
		case EAST:
			return (v + 1) % numCol ? v + 1 : INVALID;
			break;
		case WEST:
			return v % numCol ? v - 1 : INVALID;
			break;
		case SOUTH:
			return numCol * (numLin - 1) <= v ? INVALID : v + numCol;
			break;
		case NORTH:
			return v < numCol ? INVALID : v - numCol;
			break;
		case TARGET:
			return TARGET_ID;
			break;
		default:
			return INVALID;
			break;
	}
}

int getDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts) {
	switch (relatedPos(from, to, numCol, numLin)) {
		case SOURCE:
			return verts[to].fsource;
			break;
		case EAST:
			return verts[from].east;
			break;
		case WEST:
			return verts[from].west;
			break;
		case SOUTH:
			return verts[from].south;
			break;
		case NORTH:
			return verts[from].north;
			break;
		case TARGET:
			return verts[from].target;
			break;
		default:
			return INVALID;
			break;
	}
}

void setDiffFromTo(int from, int to, int numCol, int numLin, Vertice verts, int df) {
	switch (relatedPos(from, to, numCol, numLin)) {
		case SOURCE:
			verts[to].fsource -= df;
			break;
		case EAST:
			verts[from].east -= df;
			verts[to].west += df;
			break;
		case WEST:
			verts[from].west -= df;
			verts[to].east += df;
			break;
		case SOUTH:
			verts[from].south -= df;
			verts[to].north += df;
			break;
		case NORTH:
			verts[from].north -= df;
			verts[to].south += df;
			break;
		case TARGET:
			verts[from].target -= df;
			break;
		default:
			break;
	}
}
