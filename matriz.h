// as funões de alocação, leitura, escrita e liberação de memória
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

struct matriz{
    Elemento *inicio; // topo esquerdo da matriz
    Elemento *fim;    // inferior direito da matriz

};
typedef struct matriz Matriz;

//função para criar matriz
void desalocarMatriz(Matriz *m);
void adicionarLinha(Matriz *m);
void adicionarColuna(Matriz *m);
void removerLinha(Matriz *m);
void removerColuna(Matriz *m);
//função vazia
//funcao verificar existencia
//funcao consultar nó
//funcao insere final
//função insere início
//função tamanho matriz(x_y)
//primeiraCelulaLinha()