#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

void printHeader(const char* title) {
    printf("\n=================================================\n");
    printf(" %s\n", title);
    printf("=================================================\n");
}

int main(){
    Matriz *m;
    int linhas = 5;
    int colunas = 3;
    int i, j, valor = 1;

    printHeader("GERENCIADOR DE MATRIZES - VERSAO INTERATIVA");

    printf("\n[+] Inicializando Matriz Padrao (5x3)...\n\n");
    m = criarMatriz(linhas, colunas);

    // PREENCHENDO A MATRIZ
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            inserirValor(m, i, j, valor++);
        }
    }
    
    printf("Matriz Atual:\n");
    imprimirMatriz(m);

    printHeader("ETAPA 1: REMOCAO DE LINHAS");
    int linhaRemover;
    for(i = 0; i < 2; i++){
        printf("\n[!] Operacao %d/2 - Remocao de Linha\n", i+1);
        printf(" -> Digite o indice da linha a remover (0 a %d): ", linhas - 1);
        scanf("%d", &linhaRemover);
        
        if(linhaRemover >= 0 && linhaRemover < linhas) {
            removerLinha(m, linhaRemover);
            linhas--;
            printf(" [OK] Linha %d removida com sucesso!\n", linhaRemover);
        } else {
            printf(" [ERRO] Linha invalida! A operacao foi ignorada.\n");
        }
    }

    printHeader("ETAPA 2: REMOCAO DE COLUNA");
    int colunaRemover;
    printf("\n -> Digite o indice da coluna a remover (0 a %d): ", colunas - 1);
    scanf("%d", &colunaRemover);
    
    if(colunaRemover >= 0 && colunaRemover < colunas) {
        removerColuna(m, colunaRemover);
        colunas--;
        printf(" [OK] Coluna %d removida com sucesso!\n", colunaRemover);
    } else {
        printf(" [ERRO] Coluna invalida! A operacao foi ignorada.\n");
    }
    
    printf("\nMatriz Apos Remocoes:\n");
    imprimirMatriz(m);

    printHeader("ETAPA 3: ADICAO DE LINHA E COLUNA");
    
    // ADICIONANDO UMA LINHA
    adicionarLinha(m);
    printf("\n[+] Nova Linha Adicionada (Indice %d)\n", linhas);
    printf(" -> Digite os %d valores para a nova linha:\n", colunas);
    for(j = 0; j < colunas; j++){
        int novoValor;
        printf("    Valor da coluna %d: ", j);
        scanf("%d", &novoValor);
        inserirValor(m, linhas, j, novoValor);
    }
    linhas++;

    // ADICIONANDO UMA COLUNA
    adicionarColuna(m);
    printf("\n[+] Nova Coluna Adicionada (Indice %d)\n", colunas);
    printf(" -> Digite os %d valores para a nova coluna:\n", linhas);
    for(i = 0; i < linhas; i++){
        int novoValor;
        printf("    Valor da linha %d: ", i);
        scanf("%d", &novoValor);
        inserirValor(m, i, colunas, novoValor);
    }
    colunas++;

    printf("\nMatriz Finalizada:\n");
    imprimirMatriz(m);

    // APAGANDO A PRIMEIRA MATRIZ
    desalocarMatriz(m);

    printHeader("ETAPA 4: CRIAR SUA PROPRIA MATRIZ");
    printf("\n -> Quantidade de linhas: ");
    scanf("%d", &linhas);
    printf(" -> Quantidade de colunas: ");
    scanf("%d", &colunas);

    m = criarMatriz(linhas, colunas);

    printf("\n[+] Preenchendo a nova matriz %dx%d:\n", linhas, colunas);
    for(i = 0; i < linhas; i++){
        for(j = 0; j < colunas; j++){
            int valorDigitado;
            printf("    Valor para a posicao (%d, %d): ", i, j);
            scanf("%d", &valorDigitado);
            inserirValor(m, i, j, valorDigitado);
        }
    }
    
    printf("\nSua Matriz:\n");
    imprimirMatriz(m);

    // MENU DE CONSULTAS
    int opcao = -1;
    while(opcao != 0){
        printHeader("MENU DE CONSULTAS");
        printf("  [1] Buscar por Valor\n");
        printf("  [2] Buscar por Coordenada\n");
        printf("  [0] Sair\n");
        printf("-------------------------------------------------\n");
        printf(" Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) break; // Tratamento de EOF de input

        if(opcao == 1){
            int valorBusca;
            printf("\n -> Digite o valor a ser buscado: ");
            scanf("%d", &valorBusca);

            Elemento *resultado = buscarValor(m, valorBusca);

            if(resultado != NULL){
                printf("\n [SUCESSO] Valor %d encontrado!\n", valorBusca);
                printf("  - Posicao: Linha %d, Coluna %d\n", resultado->info.linha, resultado->info.coluna);
                imprimirVizinhos(m, resultado->info.linha, resultado->info.coluna);
            } else {
                printf("\n [AVISO] Valor %d nao existe na matriz.\n", valorBusca);
            }
        }
        else if(opcao == 2){
            int linha, coluna;
            printf("\n -> Digite a linha: ");
            scanf("%d", &linha);
            printf(" -> Digite a coluna: ");
            scanf("%d", &coluna);

            int valorEncontrado = consultarCoordenada(m, linha, coluna);

            if(valorEncontrado != -1){
                printf("\n [SUCESSO] Valor encontrado: %d\n", valorEncontrado);
                imprimirVizinhos(m, linha, coluna);
            } else {
                printf("\n [AVISO] Coordenada (%d, %d) fora dos limites da matriz.\n", linha, coluna);
            }
        }
        else if (opcao != 0) {
            printf("\n [ERRO] Opcao invalida. Tente novamente.\n");
        }
    }

    printf("\n[+] Encerrando o programa e liberando memoria...\n");
    desalocarMatriz(m);

    return 0;
}
