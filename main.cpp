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

/********************************* ESTRUTURAS *********************************/
typedef struct vertice {
	
}
/********************************* PROTOTIPOS *********************************/

/************************************ MAIN ************************************/
int main(int argc, char const* argv[]) {
    int linhas, colunas, i=0, j=0, arrayIndex = 0;
    int* plano;
    // LER INPUT
    // tamanhos iniciais das tabelas
    if (!scanf("%d %d", &linhas, &colunas) || linhas <= 0 || colunas <= 0 ) {
		printf("Deu erro a ler\n");
	}

    // pesos do primeiro plano
    //TODO
    //getchar();
    plano = new int[linhas*colunas];
	for (i = 0; i<linhas; i++) {
		for (j = 0; j<colunas; j++) {
			scanf("%d", &plano[arrayIndex++]);
        }
	}

    printf("plano:\n");
    for(i=0;i<linhas*colunas;i++) {
        printf("%d", plano[i]);
    }
    printf("\n------\n");


    // pesos do cenario
    //TODO
    //getchar();
	//cenario = new int[linhas*colunas];

    // pesos das vizinhancas horizontais
    // TODO
    //getchar();

    // pesos das vizinhancas verticais
    // TODO


	return 0;
}

/******************************* OUTRAS FUNCOES *******************************/
