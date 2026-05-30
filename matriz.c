    // Implementação da matriz com nós (ponteiros right e down)
/*  IMPLEMENTAÇÃO DA MATRIZ
        Cada elemento possui ponteiros para:
        - próximo elemento da mesma linha (prox).
        - elemento abaixo da mesma coluna (abaixo).

        A matriz é representada por:
        - inicio: canto superior esquerdo.
        - fim: canto inferior direito.
*/

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

/*  INICIALIZA A ESTRUTURA PRINCIPAL DA MATRIZ
        Cria a estrutura Matriz e define os ponteiros inicio e fim como NULL.
        Retorna:
        - ponteiro para a matriz criada.
*/
    Matriz* inicializarMatriz(){
        Matriz *m = (Matriz*)malloc(sizeof(Matriz));
        if(m != NULL){
            m->inicio = NULL;
            m->fim = NULL;
        }
        return m;
    }

//  VERIFICA SE A MATRIZ FOI INICIALIZADA OU NÃO.
    int matrizInicializada(Matriz *m){
        if(m == NULL){
            return 0; 
        }
        return 1; 
    }
//  VERIFICA SE A MATRIZ ESTA VAZIA OU NÃO (se tem ou não elementos nela).
    int matrizVazia(Matriz *m){

        if(m->inicio == NULL){
            return 1; 
        }
        return 0; 
    }

/*  PROCURA UM ELEMENTO PELAS CORDENADAS
        Percorre as linhas e colunas até encontrar a linha e coluna (x,y) buscado.
        Retorna:
        valor armazenado na posição.
        -1 se a coordenada não existir.
*/
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

/*  COLOCA OU ALTERA UM VALOR NUMA POSICAO
        Primeiro localiza a linha depois a coluna.
        Retorna:
        1 -> sucesso.
        0 -> posição não encontrada.
*/
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

    //Atualiza todos os índices (linha/coluna) e recalcula o ponteiro 'fim' da matriz.
/*  ATUALIZA TODAS AS CORDENADAS DA MATRIZ
        Usamos depois de remover linhas ou colunas.
        Também atualiza o ponteiro 'fim',
*/
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
/*  ADICIONA UMA LINHA NOVA NO FINAL DA MATIZ
        Cada novo elemento criado é conectado:
        Na Vertical: elemento acima -> novo elemento.
        Na Horizontal: elementos da nova linha entre si.
        Caso a matriz esteja vazia: cria o primeiro elemento (0,0).
*/
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
/*  ADICIONA UMA NOVA COLUNA NO FINAL(DIREITA).
        Cada novo elemento criado é conectado:
        Na Horizontal: elemento anterior -> novo elemento
        Na Vertical: elementos da nova coluna entre si
        Caso a matriz esteja vazia: cria o primeiro elemento (0,0).
*/
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
/*  REMOVE UMA LINHA DA MATRIZ E AJUSTA
        Remove a linha escolida.
        Após a remoção:
        - reconecta os elementos restantes
        - atualiza todas as coordenadas
        - recalcula o ponteiro 'fim'
        - libera a memória da linha removida
*/
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
/*  REMOVE UMA COLUNA DA MATRIZ E AJUSTA
        Mesmos passos que na remoção da linha só que ajustado para coluna.
*/    
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
/*  LIBERA TODA A MEMORIA USADA PELA MATRIZ
        Percorre linha a linha e coluna a coluna limopando e depois limpa a matriz tbm.
*/
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

/*  PROCURA UM ELEMNTO DA MATRIZ (fiz pra facilitar achar os vizinhos)
        1. Percorre as linhas até encontrar a linha desejada.
        2. Dentro da linha encontrada percorre as colunas.
        3. Retorna o endereço do elemento encontrado.
        4. Se não achar retorna NULL.
*/
Elemento* localizarElemento(Matriz *m, int linha, int coluna){

    // Matriz existe?
    if(matrizInicializada(m) == 0)
        return NULL;
    // Matriz vazia?
    if(matrizVazia(m))
        return NULL;

    // Ponteiro que percorre as linhas.
    Elemento *auxLinha = m->inicio;

    // Percorre as linhas até encontrar a linha desejada.
    while(auxLinha != NULL && auxLinha->info.linha != linha){
        auxLinha = auxLinha->abaixo;
    }

    // Se linha não existir.
    if(auxLinha == NULL)
        return NULL;

    // Ponteiro que percorrer as colunas.
    Elemento *auxColuna = auxLinha;

    // Percorre as colunas da linha encontrada.
    while(auxColuna != NULL && auxColuna->info.coluna != coluna){
        auxColuna = auxColuna->prox;
    }

    // Se encontrou retorna o endereço do elemento.
    if(auxColuna != NULL)
        return auxColuna;

    // Coordenada não encontrada.
    return NULL;
}

/*  CRIA UMA MATRIZ COMPLETA COM AS DIMENSÕES INFORMADAS
        Cria uma matriz vazia e adiciona linhas e colunas até atingir o tamanho.
        Retorna:
        - ponteiro para a matriz criada.
        - NULL caso as dimensões sejam inválidas.
*/
Matriz* criarMatriz(int linhas, int colunas){

    // Não existe matriz com tamanho zero ou negativo.
    if(linhas <= 0 || colunas <= 0)
        return NULL;

    // Cria a estrutura principal da matriz.
    Matriz *m = inicializarMatriz();

    // Verifica se a alocação deu certo.
    if(m == NULL)
        return NULL;

    // A primeira chamada cria o elemento (0,0).
    adicionarLinha(m);

    /* Adiciona as colunas restantes.
        Se queremos 4 colunas e já existe 1, precisamos adicionar mais 3. */
    int i;
    for(i = 1; i < colunas; i++){
        adicionarColuna(m);
    }

    // Adiciona as linhas restantes.
    for(i = 1; i < linhas; i++){
        adicionarLinha(m);
    }

    return m;
}

/*  PROCURA UM VALOR EM TODA A MATRIZ
        Percorre linha por linha procurando o valor informado.
        Retorna:
        - endereço do elemento encontrado.
        - NULL caso o valor não exista na matriz.

        Exemplo: buscarValor(m, 10);
        Se encontrar o valor 10 retorna o nó(caixa na matriz) onde ele ta.
*/
Elemento* buscarValor(Matriz *m, int valor){

    // Matriz existe.
    if(matrizInicializada(m) == 0)
        return NULL;

    // Matriz vazia.
    if(matrizVazia(m))
        return NULL;

    // Ponteiro que percorre as linhas.
    Elemento *auxLinha = m->inicio;

    // Percorre todas as linhas da matriz.
    while(auxLinha != NULL){
        // Começa pela primeira coluna da linha atual.
        Elemento *auxColuna = auxLinha;

        // Percorre todas as colunas da linha.
        while(auxColuna != NULL){
            // Verifica se encontrou o valor procurado.
            if(auxColuna->info.valor == valor){
                return auxColuna;
            }

            // Avança para a próxima coluna.
            auxColuna = auxColuna->prox;
        }

        // Avança para a próxima linha.
        auxLinha = auxLinha->abaixo;
    }

    // Valor não encontrado.
    return NULL;
}

/*  IMPRIME OS 4 VIZINHOS DE UMA POSIÇÃO DA MATRIZ
        Caso algum vizinho não exista, não existe.
*/
void imprimirVizinhos(Matriz *m, int linha, int coluna){

    // Matriz existe.
    if(matrizInicializada(m) == 0){
        printf("Matriz nao inicializada.\n");
        return;
    }

    // Matriz está vazia.
    if(matrizVazia(m)){
        printf("Matriz vazia.\n");
        return;
    }

    // Procura o elemento.
    Elemento *centro = localizarElemento(m, linha, coluna);

    // Coordenada não encontrada.
    if(centro == NULL){
        printf("Posicao (%d,%d) nao encontrada.\n", linha, coluna);
        return;
    }

    // Procura os quatro vizinhos.
    Elemento *cima = localizarElemento(m, linha - 1, coluna);
    Elemento *baixo = localizarElemento(m, linha + 1, coluna);
    Elemento *esquerda = localizarElemento(m, linha, coluna - 1);
    Elemento *direita = localizarElemento(m, linha, coluna + 1);

    printf("\n");
    printf("Elemento (%d,%d) = %d\n",
            linha,
            coluna,
            centro->info.valor);

    printf("-------------------------\n");

    // Vizinho de cima.
    if(cima != NULL)
        printf("Cima: %d\n", cima->info.valor);
    else
        printf("Cima: NULL\n");

    // Vizinho de baixo.
    if(baixo != NULL)
        printf("Baixo: %d\n", baixo->info.valor);
    else
        printf("Baixo: NULL\n");

    // Vizinho da esquerda.
    if(esquerda != NULL)
        printf("Esquerda: %d\n", esquerda->info.valor);
    else
        printf("Esquerda: NULL\n");

    // Vizinho da direita.
    if(direita != NULL)
        printf("Direita: %d\n", direita->info.valor);
    else
        printf("Direita: NULL\n");
}

//Precisa imprimir

/*  IMPRIME TODA A MATRIZ
        Percorre linha por linha imprimindo os valores.
*/
void imprimirMatriz(Matriz *m){

    if(matrizInicializada(m) == 0){
        printf("Matriz nao inicializada.\n");
        return;
    }

    if(matrizVazia(m)){
        printf("Matriz vazia.\n");
        return;
    }

    Elemento *auxLinha = m->inicio;

    while(auxLinha != NULL){
        Elemento *auxColuna = auxLinha;
        while(auxColuna != NULL){
            printf("%4d", auxColuna->info.valor);
            auxColuna = auxColuna->prox;
        }
        printf("\n");
        auxLinha = auxLinha->abaixo;
    }
}