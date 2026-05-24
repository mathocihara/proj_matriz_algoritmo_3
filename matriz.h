// as funões de alocação, leitura, escrita e liberação de memória
struct matriz{
    struct elemento *inicio;
    struct elemento *fim;

}
typedef struct matriz Matriz;

struct elemento {
    int linha;
    int coluna;
    int valor;

    struct elemento *prox;
    struct elemento *abaixo;
}

typedef struct elemento Elemento;

//função para criar matriz
//função vazia
//funcao verificar existencia
//funcao consultar nó
//funcao insere final
//função insere início
//função tamanho matriz(x_y)
//primeiraCelulaLinha()