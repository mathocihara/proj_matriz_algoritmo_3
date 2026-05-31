/* Pra rodar
gcc main.c matriz.c -o output\main.exe
.\output\main.exe
*/

/* Exemplo de uso da matriz (x,y) usando nós */

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

    int main(){

    Matriz *m;

    int linhas, colunas;

    printf("Linhas: ");
    scanf("%d",&linhas);

    printf("Colunas: ");
    scanf("%d",&colunas);

    m = criarMatriz(linhas, colunas);

    executar(m, &linhas, &colunas);

    desalocarMatriz(m);

    return 0;
}