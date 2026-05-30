#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nPressione ENTER para voltar ao menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer
    getchar(); // Espera o enter
}

int main() {
    int linhas = 3;
    int colunas = 3;
    Matriz *m = criarMatriz(linhas, colunas);

    // PREENCHENDO A MATRIZ (PADRAO 3x3)
    int valor = 1;
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            inserirValor(m, i, j, valor++);
        }
    }

    int opcao = -1;
    while(opcao != 0) {
        limparTela();
        printf("=======================================\n");
        printf("        GERENCIADOR DE MATRIZES        \n");
        printf("=======================================\n\n");
        
        printf("ESTADO ATUAL DA MATRIZ (%dx%d):\n", linhas, colunas);
        printf("---------------------------------------\n");
        if(linhas == 0 || colunas == 0 || matrizVazia(m)) {
            printf(" Matriz Vazia.\n");
        } else {
            imprimirMatriz(m);
        }
        printf("---------------------------------------\n\n");

        printf("OPERACOES DISPONIVEIS:\n");
        printf("  [1] Inserir / Atualizar Valor\n");
        printf("  [2] Adicionar Linha\n");
        printf("  [3] Adicionar Coluna\n");
        printf("  [4] Remover Linha\n");
        printf("  [5] Remover Coluna\n");
        printf("  [6] Buscar Valor\n");
        printf("  [7] Consultar Coordenada (Vizinhos)\n");
        printf("  [0] Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) break;

        if (opcao == 0) {
            break;
        } else if (opcao == 1) {
            int l, c, v;
            printf("\nDigite a linha (1 a %d): ", linhas);
            scanf("%d", &l);
            printf("Digite a coluna (1 a %d): ", colunas);
            scanf("%d", &c);
            printf("Digite o novo valor: ");
            scanf("%d", &v);
            
            l--; // Converter para indice 0
            c--; // Converter para indice 0
            
            if(l >= 0 && l < linhas && c >= 0 && c < colunas) {
                inserirValor(m, l, c, v);
                printf("[OK] Valor inserido.\n");
            } else {
                printf("[ERRO] Coordenada invalida!\n");
            }
            pausar();
        } else if (opcao == 2) {
            adicionarLinha(m);
            printf("\n[+] Adicionando Linha %d\n", linhas + 1);
            for(int j = 0; j < colunas; j++){
                int novoValor;
                printf("Valor para a coluna %d: ", j + 1);
                scanf("%d", &novoValor);
                inserirValor(m, linhas, j, novoValor);
            }
            linhas++;
            printf("[OK] Linha adicionada.\n");
            pausar();
        } else if (opcao == 3) {
            adicionarColuna(m);
            printf("\n[+] Adicionando Coluna %d\n", colunas + 1);
            for(int i = 0; i < linhas; i++){
                int novoValor;
                printf("Valor para a linha %d: ", i + 1);
                scanf("%d", &novoValor);
                inserirValor(m, i, colunas, novoValor);
            }
            colunas++;
            printf("[OK] Coluna adicionada.\n");
            pausar();
        } else if (opcao == 4) {
            int l;
            printf("\nDigite a linha a remover (1 a %d): ", linhas);
            scanf("%d", &l);
            l--; // Converter para indice 0
            if(l >= 0 && l < linhas) {
                removerLinha(m, l);
                linhas--;
                printf("[OK] Linha removida.\n");
            } else {
                printf("[ERRO] Linha invalida!\n");
            }
            pausar();
        } else if (opcao == 5) {
            int c;
            printf("\nDigite a coluna a remover (1 a %d): ", colunas);
            scanf("%d", &c);
            c--; // Converter para indice 0
            if(c >= 0 && c < colunas) {
                removerColuna(m, c);
                colunas--;
                printf("[OK] Coluna removida.\n");
            } else {
                printf("[ERRO] Coluna invalida!\n");
            }
            pausar();
        } else if (opcao == 6) {
            int v;
            printf("\nDigite o valor a buscar: ");
            scanf("%d", &v);
            Elemento *res = buscarValor(m, v);
            if(res != NULL) {
                printf("[SUCESSO] Valor %d encontrado na posicao (Linha %d, Coluna %d).\n", v, res->info.linha + 1, res->info.coluna + 1);
            } else {
                printf("[ERRO] Valor %d nao encontrado.\n", v);
            }
            pausar();
        } else if (opcao == 7) {
            int l, c;
            printf("\nDigite a linha: ");
            scanf("%d", &l);
            printf("Digite a coluna: ");
            scanf("%d", &c);
            
            l--; // Converter para indice 0
            c--; // Converter para indice 0
            
            int v = consultarCoordenada(m, l, c);
            if(v != -1) {
                printf("\n[SUCESSO] Elemento (Linha %d, Coluna %d) = %d\n", l + 1, c + 1, v);
                imprimirVizinhos(m, l, c);
            } else {
                printf("[ERRO] Coordenada invalida ou nao encontrada.\n");
            }
            pausar();
        } else {
            printf("[ERRO] Opcao invalida.\n");
            pausar();
        }
    }

    limparTela();
    printf("Encerrando e liberando memoria...\n");
    desalocarMatriz(m);
    return 0;
}
