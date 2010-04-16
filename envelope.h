#include <stdio.h>
#include <stdlib.h>

/* envelope.h - conjunto de funções envelopadoras */



typedef enum {false, true} Boolean;


FILE * Fopen(char *arg1, char *arg2);
/* Abre um arquivo. Em caso de erro, imprime mensagem de erro e finaliza
   a execução do programa */

void * Malloc(int tamanho);
/* Aloca e retorna um espaço de memória de 'tamanho' bytes. Caso não haja
   memória suficiente, imprime mensagem de erro e finaliza a execução do
   programa */
