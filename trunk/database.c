/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laboratório    02A - Programa para leitura de dados de arquivo em formato  */
/*                      de campo fixo, conversão para formato delimitado e    */
/*                      impressão nos dois formatos                           */
/******************************************************************************/
/*
 * database.c - conjunto de funções para manipulação de banco de dados
 */

#include "database.h"



Boolean LeConfig(char * sep, char * lingua){
/* Procura o arquivo Config.l1b e carrega em sep o caractere que deve separar 
   os dados no arquivo de entrada e em lingua o identificador da linua de 
   interface. Retorna erro se não encontrar o arquivo ou se o conteúdo 
   for inválido */
   
   return true;
}
   
   
void Linguagem(char *lingua){
/* Configura as mensagens de tela do programa conforme a lingua em uso, 
   identificada por lingua
*/ 
   return;
}

       
Boolean AbreArquivoFixo(char * nomeArq, FILE * arqFix, FILE * arqCfg) {
/* Abre para leitura os arquivos a serem apontados por arqFix e arqCfg, 
   representados por nomeArq, respectivamente acrescidos das extensões 
   ".fix" e ".cfg". Retorna false no insucesso da abertura de qualquer
   dos 2 arquivos */
   
   return true;
}

   
int CarregaHeader(Header* head, FILE* arqCfg){
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg
   retorna a quantidade de campos */

   return 0;
}
   

Record LeRegistroFixo(FILE* arqFix, int n, Header* h) {
/* Aloca a memória dinâmica necessária e carrega na mesma o conteúdo dos n 
   campos do registro corrente de arqFix. Carrega Record com os endereços do 
   conteúdo de cada campo. Deixa o ponteiro de arqFix na posição apropriada
   para a próxima leitura */
   
   int i;
   Record registro;
   
   for(i=0;i<n;i++){
   registro[i] = malloc(sizeof(char*)*h[i].tamanho);
   registro[i] = "valor";              
                    
   }
   
   return registro;
}
   

FILE* ConverteFixoDelim(char* nome, FILE* arq, char c){
/* Retorna o ponteiro para um arquivo de "nome.dlm", com os mesmos registros de 
   arq, separados pelo delimitador c. Para tanto, invoca RemoveBrancos para
   compactar os campos que não preenchem todo o espaço do campo fixo */
   FILE* dlm;
   return dlm;
}   
   
   
Record LeRegistroDelim(FILE* arq, int n){
/* Aloca a memória dinâmica necessária e carrega na mesma o conteúdo dos n 
   campos do registro corrente de um arquivo de dados em formato delimitado
   (arq). Carrega Record com os endereços do conteúdo de cada campo. 
   Deixa o ponteiro de arqFix na posição apropriada para a próxima leitura */
   
   Record registro;
   return registro;
}
      
   
   
