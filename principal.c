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


int LeOpcao(){
/* Le a opcao digitada e a retorna como um 'int' */

    char opcao[5];
    scanf("%s", opcao);
    
    while(!VerificaDigitos(opcao)) {
       printf("%s", TXT_OUTPUT_INV); 
       scanf("%s", opcao);
    }
    
    return atoi(opcao);

} /* LeOpcao */


void Menu(Header* head, FILE* arqFix, FILE* arqDlm, char* nomeArqSaida, char separador,int numcampos){
/* Menu do programa */
     
     int opcao, tamanhofix;
     Boolean fim = false;
     
     tamanhofix = + head[numcampos-1].inicio+head[numcampos-1].tamanho;
     
     do {
         system("cls");
         printf("%s", TELA_PRINCIPAL);
         printf("%s", OPCAO_1);
         printf("%s", OPCAO_2);
         printf("%s", OPCAO_3);
         printf("%s", OPCAO_4);
         
         opcao = LeOpcao();
         while(opcao <= 0 || opcao > 4){   /* Verifica se é uma opção válida */
             printf("%s", TXT_OUTPUT_INV);
             opcao = LeOpcao();
         }
         
         switch(opcao){
             case 1:
                  fseek(arqFix, 0, SEEK_SET);
                  arqDlm = ConverteFixoDelim(nomeArqSaida, arqFix, separador, head, numcampos, tamanhofix);
                  printf("%s", TXT_OUTPUT_1); 
                  system("pause");
             break;
             case 2:
                  /* impressão dos campos do arquivo de tamanho fixo */
                  
                   fseek(arqFix, 0, SEEK_SET);
                   ImprimeArquivoFixo(arqFix, numcampos, head, tamanhofix);
                   
                   system("pause");
             break;
             case 3:
                  
                  #define ARQ_DLM_NULL "vc deve criar o arquivo primeiro\n\n"
                  if(arqDlm == NULL)
                      fprintf(stdout, "%s", ARQ_DLM_NULL);//****************************************************************************** 
                  else
                  //Listar arquivos de dados no formato variavel ****************************************************************
                  system("pause");
             break;
             case 4:
                  fim = true;
             break;
         }
     } while (!fim);
     
} /* Menu */


int main(int argc, char *argv[]) {
    /* variáveis */
    char separador;
    char fimRegistro;
    FILE* arqFix, * arqDlm, * arqCfg;
    char* delim;
    Header* head;
    int i, numcampos;
    
    /* checa linha de comando */
    if(argc != QTE_ARGUMENTOS)
       Erro(MSG_ERRO_NUM_ARGUMENTOS);

    /* arquivo de configuração */
    if(!LeConfig(&separador))
       Erro(MSG_ERRO_CONFIG); 

    /* abertura dos arquivos */
    AbreArquivoFixo(argv[1], &arqFix, &arqCfg);
    
    /* leitura dos campos */                        
    CarregaHeader(&head, &numcampos, arqCfg);   

/*    
    //impressão dos campos do arquivo delimitados
    while(!feof(arqDlm)) {
          registro = LeRegistroDelim(arqDlm, numcampos);
          for(i=0; i<numcampos; i++)
                   fprintf(stdout, "%s ", registro[i]);
          printf("\n");
          //LiberaRegistro(registro); ??
          }
*/    
    
    Menu(head, arqFix, arqDlm, argv[2], separador, numcampos);

    fclose(arqFix);
    //fclose(arqDlm);
    fclose(arqCfg);
    free(head);
    
    system("pause");
    return 0;

} /* main */
