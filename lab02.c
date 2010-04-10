/* Primeiro teste para o Lab02 - MC326 - Unicamp 1o. sem 2010 */


#include <stdio.h>
#include <string.h>

/*** Estruturas de dados ******************************************************/
typedef enum {false, true} Boolean;

typedef char * String;

typedef struct {
        char nome[20];
        char tipo;
//        int inicio;
char inicio[3];
//        int fim;
char fim[3];

        int tam;
        Boolean obrig;
        char msg[30];
        } Header;

typedef struct {
        String * campo;
        } Record;
/****************************************************** Estruturas de dados ***/


/*** Funções Auxiliares *******************************************************/
int converteInt(FILE *f, int tam) {  // le e converte uma string em inteiro
      char c;  int i, res = 0;
      for(i = 1; i <= tam; i++){
           c = fgetc(f);
           res = res* 10 + ((int) c - 48);
      }
      return res;
} /*converteInt*/


void prox_linha(FILE *f) {              // avanço de linha no arquivo
     char c;
     do {fscanf(f,"%c", &c);} while((c != '\n') && (c != feof(f)));
} /*prox_linha*/
/******************************************************* Funções Auxiliares ***/



int main() {
    // Declaração de Variáveis
    FILE * f = fopen("teste1.txt", "rt");
    FILE * config = fopen("config.txt", "rt");
    char * linha;
    int i = 0;
    int qtecampos = 0;
    int tamrec = 0;
    int reccount = 1;
    int fimAnt;
    char c;
    Record rec;
    
    //Leitura da quantidade de campos do arquivo de dados
    while(!feof(config)) {
          fgets(linha, 80, config);
          qtecampos++;
    }
    rewind(config);
    //Descarte do campo FimRegistro
    qtecampos--;

printf("qtecampos: %d\n", qtecampos);
//system("pause");

    //Armazenamento em memória das informações sobre os campos
    Header head[qtecampos];

    for(i=0; i<qtecampos; i++) {

          fgets(head[i].nome, 21, config);
printf("Nome do Campo: %s\n", head[i].nome);          
          fscanf(config, "%c", &(head[i].tipo));
printf("Tipo: %c\n", head[i].tipo);          
//          fgetc(config);
//          head[i].inicio = converteInt(config, 3);
          fgets(head[i].inicio, 4, config);
printf("Posição inicial: %s\n", head[i].inicio);          
//          head[i].fim    = converteInt(config, 3);
          fgets(head[i].fim, 4
          , config);
printf("Posição final: %s\n", head[i].fim);          
//          head[i].tam    = head[i].fim - head[i].inicio + 1;
          fscanf(config, "%c", &c);
printf("Obrigatorio(S/N): %c\n", c);          
          if(c == 'S') head[i].obrig = true;
          else         head[i].obrig = false;
          fgets(head[i].msg, 30, config);
printf("Mensagem: %s\n\n", head[i].msg);

          //Alocação de memória para o registro de dados a ser lido
          rec.campo[i] = malloc(sizeof(char)*head[i].tam);
          
printf("cheguei\n");
          
//          prox_linha(config);          
printf("cheguei\n");

    }

system("pause");


    //Determinação do tamanho da linha do registro
    /* poderia ser alternativamente obtido no arquivo config, acrescentando
       2 ao fim do último campo (caracters de fim de registro e line feed */
    do {
        fscanf(f,"%c", &c);
        tamrec++;
    } while(c != '\n');
    rewind(f);

    //Leitura e impressão dos registros do arquivo de tamanho fixo
    printf("\nListagem do arquivo em formato de campo fixo:\n");
    
/*    while(!feof(f)) {
                   fimAnt = 0;
                   for(i=0; i<qtecampos; i++) {
                            printf("Registro: %d\n", reccount);
                            fseek ( f, head[i].inicio - fimAnt, SEEK_CUR );
                            fread (rec.campo[i], sizeof(char), head[i].tam, f);
                            fimAnt = head[i].fim;
                            printf("%s: %s\n", head[i].nome, rec.campo[i]);
                   }
                   i--;
                   fseek ( f, tamrec+1-head[i].fim , SEEK_CUR );
                   reccount++;
                   printf("\n");
    }    
    
*/    
    fclose(f);
    system("pause");
    return 0;
}


