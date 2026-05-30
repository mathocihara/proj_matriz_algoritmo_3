/*
Compilar:
*/

/* Exemplo de uso da matriz (x,y) usando nós */

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(){

    Matriz *m;
    int linhas = 5;
    int colunas = 3;

    int i;
    int j;
    int valor = 1;

    // CRIANDO MATRIZ 5x3
    printf("\nCRIANDO MATRIZ 5x3\n\n");
    m = criarMatriz(linhas,colunas);

    // PREENCHENDO A MATRIZ
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            inserirValor(m,i,j,valor);
            valor++;
        }
    }
    imprimirMatriz(m);
    printf("Matriz preenchida.\n");

    // REMOVENDO DUAS LINHAS
    int linhaRemover;
    for(i = 0; i < 2; i++){
        printf("\nDigite a linha para remover: ");
        scanf("%d",&linhaRemover);
        removerLinha(m,linhaRemover);
        linhas--;
    }

    // REMOVENDO UMA COLUNA
    int colunaRemover;
    printf("\nDigite a coluna para remover: ");
    scanf("%d",&colunaRemover);
    removerColuna(m,colunaRemover);
    colunas--;
    imprimirMatriz(m);

    //ADICIONANDO UMA LINHA
    printf("\nDigite os valores da nova linha:\n");

    for(j = 0; j < colunas; j++){
        int novoValor;
        scanf("%d",&novoValor);
        inserirValor(m, linhas, j, novoValor);
    }
    linhas++;

    // ADICIONANDO UMA COLUNA
    adicionarColuna(m);
    printf("\nDigite os valores da nova coluna:\n");

    for(i = 0; i < linhas; i++){
        int novoValor;
        scanf("%d",&novoValor);
        inserirValor(m, i, colunas, novoValor);
    }
    colunas++;

    printf("\n");
    imprimirMatriz(m);
    printf("\n");

    // APAGANDO A PRIMEIRA MATRIZ
    desalocarMatriz(m);

    // CRIANDO UMA NOVA MATRIZ
    printf("\nQuantidade de linhas: ");
    scanf("%d",&linhas);
    printf("Quantidade de colunas: ");
    scanf("%d",&colunas);

    m = criarMatriz(linhas,colunas);

    // PREENCHENDO A NOVA MATRIZ
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            int valorDigitado;
            printf("Valor (%d,%d): ",i,j);
            scanf("%d",&valorDigitado);
            inserirValor(m, i, j, valorDigitado);
        }
    }
    printf("\n");
    imprimirMatriz(m);
    printf("\n");

    //MENU DE CONSULTAS
    int opcao = -1;

    while(opcao != 0){
        printf("\n1 - Buscar valor\n");
        printf("2 - Buscar coordenada\n");
        printf("0 - Sair\n");
        scanf("%d",&opcao);

        //BUSCA POR VALOR
        if(opcao == 1){
            int valorBusca;
            printf("Valor: ");
            scanf("%d",&valorBusca);

            Elemento *resultado = buscarValor(m,valorBusca);

            if(resultado != NULL){
                printf("\nValor encontrado.\n");
                printf("Linha: %d\n", resultado->info.linha);
                printf("Coluna: %d\n", resultado->info.coluna);
                imprimirVizinhos(m, resultado->info.linha, resultado->info.coluna);
            }
            else{
                printf("Valor nao encontrado.\n");
            }
        }


        //BUSCA POR COORDENADA
        if(opcao == 2){
            int linha;
            int coluna;

            printf("Linha: ");
            scanf("%d",&linha);
            printf("Coluna: ");
            scanf("%d",&coluna);

            int valorEncontrado = consultarCoordenada(m, linha, coluna);

            if(valorEncontrado != -1){
                printf("\nValor encontrado: %d\n", valorEncontrado);
                imprimirVizinhos(m, linha, coluna);
            }
            else{
                printf("Coordenada nao encontrada.\n");
            }
        }
    }

    //LIBERANDO MEMORIA
    desalocarMatriz(m);

    return 0;
}