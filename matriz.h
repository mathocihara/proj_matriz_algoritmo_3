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
    Elemento *inicio;
    Elemento *fim;

};
typedef struct matriz Matriz;

//função para criar matriz
//função vazia
//funcao verificar existencia
//funcao consultar nó
//funcao insere final
//função insere início
//função tamanho matriz(x_y)
//primeiraCelulaLinha()