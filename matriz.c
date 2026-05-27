    // Implementação da matriz com nós (ponteiros right e down)

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

    Matriz* inicializarMatriz(){
        Matriz *m = (Matriz*)malloc(sizeof(Matriz));
        if(m != NULL){
            m->inicio = NULL;
            m->fim = NULL;
        }
        return m;
    }

    int matrizInicializada(Matriz *m){
        if(m == NULL){
            return 0; 
        }
        return 1; 
    }

    int matrizVazia(Matriz *m){

        if(m->inicio == NULL){
            return 1; 
        }
        return 0; 
    }

    int consultarCoordenada(Matriz *m, int a, int b){

        Elemento *auxLinha;
        Elemento *auxColuna;

        if(matrizInicializada(m) == 0){
            return -1;
        }

        if(matrizVazia(m)){
            return -1;
        }

        if(m->inicio->info.linha == a && m->inicio->info.coluna == b){
            return m->inicio->info.valor;
        }

        if(m->fim->info.linha == a && m->fim->info.coluna == b){
            return m->fim->info.valor;
        }

        auxLinha = m->inicio;

        while(auxLinha != NULL && auxLinha->info.linha != a){
            auxLinha = auxLinha->abaixo;

            }
        if(auxLinha == NULL){
            return -1;
        }

        auxColuna = auxLinha;

        while(auxColuna != NULL && auxColuna->info.coluna != b){
            auxColuna = auxColuna->prox;
    }
        if(auxColuna != NULL && auxColuna->info.coluna == b &&
           auxLinha->info.linha == a){
            return auxColuna->info.valor;
        }


        /* coordenada não encontrada */
        return -1;
    }

    int inserirValor(Matriz *m, int linha, int coluna, int valor) {
        if (!matrizInicializada(m) || matrizVazia(m)) return 0;

        Elemento *auxLinha = m->inicio;
        while (auxLinha != NULL && auxLinha->info.linha != linha) {
            auxLinha = auxLinha->abaixo;
        }
        if (auxLinha == NULL) return 0; // linha não encontrada

        Elemento *auxColuna = auxLinha;
        while (auxColuna != NULL && auxColuna->info.coluna != coluna) {
            auxColuna = auxColuna->prox;
        }
        if (auxColuna == NULL) return 0; // coluna não encontrada

        auxColuna->info.valor = valor;
        return 1;
    }

    /* Atualiza todos os índices (linha/coluna) e recalcula o ponteiro 'fim' da matriz */
    void atualizarCoordenadas(Matriz *m) {
        if (!matrizInicializada(m)) return;

        if (matrizVazia(m)) {
            m->fim = NULL;
            return;
        }

        int linhaIndex = 0;
        Elemento *linhaAtual = m->inicio;
        Elemento *ultimoElemento = NULL;

        while (linhaAtual != NULL) {
            int colunaIndex = 0;
            Elemento *colunaAtual = linhaAtual;
            while (colunaAtual != NULL) {
                colunaAtual->info.linha = linhaIndex;
                colunaAtual->info.coluna = colunaIndex;
                ultimoElemento = colunaAtual;
                colunaAtual = colunaAtual->prox;
                colunaIndex++;
            }
            linhaAtual = linhaAtual->abaixo;
            linhaIndex++;
        }
        m->fim = ultimoElemento;
    }

    /* Auxiliar: Cria e inicializa um novo elemento */
    Elemento* criarElemento(int linha, int coluna) {
        Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
        if (novo != NULL) {
            novo->info.linha = linha;
            novo->info.coluna = coluna;
            novo->info.valor = 0;
            novo->prox = NULL;
            novo->abaixo = NULL;
        }
        return novo;
    }

    /* Adiciona uma nova linha na parte inferior da matriz */
    void adicionarLinha(Matriz *m) {
        if (!matrizInicializada(m)) return;

        if (matrizVazia(m)) {
            Elemento *novo = criarElemento(0, 0);
            m->inicio = novo;
            m->fim = novo;
            return;
        }

        Elemento *atual = m->inicio;
        while (atual->abaixo != NULL) {
            atual = atual->abaixo;
        }

        Elemento *anterior = NULL;
        while (atual != NULL) {
            Elemento *novo = criarElemento(atual->info.linha + 1, atual->info.coluna);
            atual->abaixo = novo;

            if (anterior != NULL) {
                anterior->prox = novo;
            }
            anterior = novo;
            atual = atual->prox;
        }
    
        // Atualizar m->fim para o último elemento inserido (que já está em 'anterior')
        m->fim = anterior;
    }

    /* Adiciona uma nova coluna a direita da matriz */
    void adicionarColuna(Matriz *m) {
        if (!matrizInicializada(m)) return;

        if (matrizVazia(m)) {
            Elemento *novo = criarElemento(0, 0);
            m->inicio = novo;
            m->fim = novo;
            return;
        }

        Elemento *atual = m->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        Elemento *acima = NULL;
        while (atual != NULL) {
            Elemento *novo = criarElemento(atual->info.linha, atual->info.coluna + 1);
            atual->prox = novo;

            if (acima != NULL) {
                acima->abaixo = novo;
            }
            acima = novo;
            atual = atual->abaixo;
        }
    
        // Atualizar m->fim
        m->fim = acima;
    }

    /* Remove uma linha específica da matriz pelo seu índice */
    void removerLinha(Matriz *m, int linha_alvo) {
        if (!matrizInicializada(m) || matrizVazia(m)) return;

        Elemento *atual = m->inicio;
        Elemento *acima = NULL;

        // Procura o início da linha alvo
        while (atual != NULL && atual->info.linha != linha_alvo) {
            acima = atual;
            atual = atual->abaixo;
        }

        if (atual == NULL) return; // linha não encontrada

        if (acima == NULL) {
            // Caso acima for nulo, quer dizer que não iteramos sobre a matriz, logo removemos a primeira linha
            m->inicio = atual->abaixo;
        } else {
            // Removendo do meio ou fim: reconectar verticalmente
            Elemento *auxAcima = acima;
            Elemento *auxAtual = atual;
            while (auxAcima != NULL && auxAtual != NULL) {
                auxAcima->abaixo = auxAtual->abaixo;
                auxAcima = auxAcima->prox;
                auxAtual = auxAtual->prox;
            }
        }

        // Reindexa toda a matriz e ajusta o ponteiro 'fim' automaticamente
        atualizarCoordenadas(m);

        // Libera a memória da linha
        Elemento *liberar = atual;
        while (liberar != NULL) {
            Elemento *temp = liberar;
            liberar = liberar->prox;
            free(temp);
        }
    }

    /* Remove uma coluna específica da matriz pelo seu índice */
    void removerColuna(Matriz *m, int coluna_alvo) {
        if (!matrizInicializada(m) || matrizVazia(m)) return;

        Elemento *atual = m->inicio;
        Elemento *anterior = NULL;

        // Procura o topo da coluna alvo
        while (atual != NULL && atual->info.coluna != coluna_alvo) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual == NULL) return; // coluna não encontrada

        if (anterior == NULL) {
            // Caso anterior for nulo, então não iteramos, logo removemos a primeira coluna
            m->inicio = atual->prox;
        } else {
            // Removendo do meio ou fim: reconectar horizontalmente
            Elemento *auxAnterior = anterior;
            Elemento *auxAtual = atual;
            while (auxAnterior != NULL && auxAtual != NULL) {
                auxAnterior->prox = auxAtual->prox;
                auxAnterior = auxAnterior->abaixo;
                auxAtual = auxAtual->abaixo;
            }
        }

        // Reindexa toda a matriz e ajusta o ponteiro 'fim' automaticamente
        atualizarCoordenadas(m);

        // Libera a memória da coluna
        Elemento *liberar = atual;
        while (liberar != NULL) {
            Elemento *temp = liberar;
            liberar = liberar->abaixo;
            free(temp);
        }
    }

    /* Percorre a matriz e desaloca todos os nos e a estrutura base */
    void desalocarMatriz(Matriz *m) {
        if (!matrizInicializada(m)) return;

        Elemento *linhaAtual = m->inicio;
        while (linhaAtual != NULL) {
            Elemento *colunaAtual = linhaAtual;
            linhaAtual = linhaAtual->abaixo;

            while (colunaAtual != NULL) {
                Elemento *temp = colunaAtual;
                colunaAtual = colunaAtual->prox;
                free(temp);
            }
        }
        free(m);
    }
