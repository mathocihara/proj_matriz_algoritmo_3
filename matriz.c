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
        if (m->inicio == NULL) {
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
        m->fim = anterior;
    }

    /* Adiciona uma nova coluna a direita da matriz */
    void adicionarColuna(Matriz *m) {
        if (m->inicio == NULL) {
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
        m->fim = acima;
    }

    /* Remove a ultima linha da matriz */
    void removerLinha(Matriz *m) {
        if (m->inicio == NULL) return;

        if (m->inicio->abaixo == NULL) {
            Elemento *atual = m->inicio;
            while (atual != NULL) {
                Elemento *temp = atual;
                atual = atual->prox;
                free(temp);
            }
            m->inicio = NULL;
            m->fim = NULL;
            return;
        }

        Elemento *penultima = m->inicio;
        while (penultima->abaixo != NULL && penultima->abaixo->abaixo != NULL) {
            penultima = penultima->abaixo;
        }

        Elemento *atual = penultima->abaixo;
        while (atual != NULL) {
            Elemento *temp = atual;
            atual = atual->prox;
            free(temp);
        }

        while (penultima != NULL) {
            penultima->abaixo = NULL;
            if (penultima->prox == NULL) {
                m->fim = penultima;
            }
            penultima = penultima->prox;
        }
    }

    /* Remove a ultima coluna da matriz */
    void removerColuna(Matriz *m) {
        if (m->inicio == NULL) return;

        if (m->inicio->prox == NULL) {
            Elemento *atual = m->inicio;
            while (atual != NULL) {
                Elemento *temp = atual;
                atual = atual->abaixo;
                free(temp);
            }
            m->inicio = NULL;
            m->fim = NULL;
            return;
        }

        Elemento *penultima = m->inicio;
        while (penultima->prox != NULL && penultima->prox->prox != NULL) {
            penultima = penultima->prox;
        }

        Elemento *atual = penultima->prox;
        while (atual != NULL) {
            Elemento *temp = atual;
            atual = atual->abaixo;
            free(temp);
        }

        while (penultima != NULL) {
            penultima->prox = NULL;
            if (penultima->abaixo == NULL) {
                m->fim = penultima;
            }
            penultima = penultima->abaixo;
        }
    }

    /* Percorre a matriz e desaloca todos os nos e a estrutura base */
    void desalocarMatriz(Matriz *m) {
        if (m == NULL) return;

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

    //funcao insere final
    //função insere início
    //função tamanho matriz(x_y)
    //primeiraCelulaLinha()( ultima celula de cada lista tem que direcionar para a primeira celualr da litsa)