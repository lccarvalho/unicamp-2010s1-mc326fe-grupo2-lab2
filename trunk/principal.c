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
   1a versão de principal.c
   Não implementa menus, apenas executa em sequencia 
   as tarefas das opções 1, 2 e 3
   Para testes
              */
              
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "languages.h"
#include "envelope.h"

/* o programa recebe os nomes dos arquivos de entrada e saída */
#define QTE_ARGUMENTOS 3


void Erro(char * msgErro) {
     printf("%s\n",msgErro); 
     system("pause");
     exit(0);
}


int main(int argc, char *argv[]) {
    /* variáveis */
    char lingua[5];
    char separador;
    char fimRegistro;
    FILE* arqFix, * arqDlm, * arqCfg;
    char* delim;
    Header* head;
    int i, numcampos;
    Record registro;
    
    /* checa linha de comando */
    if(argc != QTE_ARGUMENTOS)
       Erro(MSG_ERRO_NUM_ARGUMENTOS);

    /* arquivo de configuração */
    if(!LeConfig(&separador, lingua))
       Erro(MSG_ERRO_CONFIG); 

    /* definição da lingua de interface */
    Linguagem(lingua);

    /* abertura dos arquivos */
    arqFix = Fopen(argv[1], "r");
    arqCfg = Fopen("header.cfg", "r");
    
    /* leitura dos campos */                        
    CarregaHeader(&head, &numcampos, arqCfg);
    

    //impressão dos campos do arquivo de tamanho fixo
    while(!feof(arqFix)) {
          registro = LeRegistroFixo(arqFix, numcampos, head);
          for(i=0; i<numcampos; i++)
                   fprintf(stdout, "%s ", registro[i]);
          printf("\n");
          //LiberaRegistro(registro); ??
          }

    //criação do arquivo delimitado
    arqDlm = ConverteFixoDelim(argv[2], arqFix, separador);
    
    //impressão dos campos do arquivo delimitados
    while(!feof(arqDlm)) {
          registro = LeRegistroDelim(arqDlm, numcampos);
          for(i=0; i<numcampos; i++)
                   fprintf(stdout, "%s ", registro[i]);
          printf("\n");
          //LiberaRegistro(registro); ??
          }
    
    
    fclose(arqFix);
    fclose(arqDlm);
    fclose(arqCfg);
    free(head);
//    free(???); LiberaRegistro(????);
    
    system("pause");
    return 0;

} /* main */
