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
        if(aif(auxColuna != NULL && auxColuna->info.coluna == b &&
           auxLinha->info.linha == a)){
            return auxColuna->info.valor;
        }


        /* coordenada não encontrada */
        return -1;
    }
    //funcao insere final
    //função insere início
    //função tamanho matriz(x_y)
    //primeiraCelulaLinha()( ultima celula de cada lista tem que direcionar para a primeira celualr da litsa)