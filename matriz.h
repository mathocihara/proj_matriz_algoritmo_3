struct informacao {
    int linha;
    int coluna;
    int valor;
};

struct elemento {
    struct informacao info;
    struct elemento *prox;
    struct elemento *abaixo;
};

typedef struct elemento Elemento;

struct matriz {
    Elemento *inicio; // topo esquerdo da matriz
    Elemento *fim;    // inferior direito da matriz
};
typedef struct matriz Matriz;

Matriz* inicializarMatriz();
int matrizInicializada(Matriz *m);
int matrizVazia(Matriz *m);
int consultarCoordenada(Matriz *m, int a, int b);
int inserirValor(Matriz *m, int linha, int coluna, int valor);
void atualizarCoordenadas(Matriz *m);

Elemento* criarElemento(int linha, int coluna);
void adicionarLinha(Matriz *m);
void adicionarColuna(Matriz *m);
void removerLinha(Matriz *m, int linha_alvo);
void removerColuna(Matriz *m, int coluna_alvo);
void desalocarMatriz(Matriz *m);

// atualizado
Elemento* localizarElemento(Matriz *m, int linha, int coluna);
Matriz* criarMatriz(int linhas, int colunas);
Elemento* buscarValor(Matriz *m, int valor);
void imprimirVizinhos(Matriz *m, int linha, int coluna);
void imprimirMatriz(Matriz *m);