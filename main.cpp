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

/********************************* PROTOTIPOS *********************************/

/************************************ MAIN ************************************/
int main(int argc, char const* argv[]) {
    int altura, largura, i=0, j=0, arrayIndex = 0;
    int* plano;
    char c;
    // LER INPUT
    // tamanhos iniciais das tabelas
    if (!scanf("%d %d", &altura, &largura) || altura <= 0 || largura <= 0 ) {
		printf("Deu erro a ler\n");
	}

    // pesos do primeiro plano
    //TODO
    //getchar();
    plano = new int[altura*largura];
    while(i<altura) {
        getchar();
        //printf("NOVA LINHA %d\n", i);
        j = 0;
        while (j<largura) {
            //printf("NOVA COLUNA %d\n", j);
            c = getchar();
            if('0'<= c && c<='9') {
                // printf("char %c\n", c);
                plano[arrayIndex++] = atoi(&c);
                j++;
            }
        }
        i++;
    }
    printf("plano:\n");
    for(i=0;i<altura*largura;i++) {
        printf("%d", plano[i]);
    }
    printf("\n------\n");


    // pesos do cenario
    //TODO
    //getchar();

    // pesos das vizinhancas horizontais
    // TODO
    //getchar();

    // pesos das vizinhancas verticais
    // TODO


	return 0;
}

/******************************* OUTRAS FUNCOES *******************************/
