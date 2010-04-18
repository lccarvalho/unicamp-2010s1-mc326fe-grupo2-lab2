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

/* Só pra compilar ******************************************************************************************************/
#define OPCAO_INVALIDA "op inv\n\n"
#define ARQ_CONVERTIDO "arq\n\n"


int LeOpcao(){
/* Le a opcao digitada e a retorna como um 'int' */

    char opcao[5];
    scanf("%s", opcao);
    
    while(!VerificaDigitos(opcao)) {
       printf("%s", OPCAO_INVALIDA); //OPCAO INVALIDA = "\nSua opcao deve conter somente numeros\nTente novamente:\n\n" ****************************************************************
       scanf("%s", opcao);
    }
    
    return atoi(opcao);

} /* LeOpcao */


void Menu(Header* head, FILE* arqFix, FILE* arqDlm, char* nomeArqSaida, char separador){
/* Menu do programa */
     
     int opcao;
     Boolean fim = false;
     
     do {
         system("cls");
         printf("%s", TELA_PRINCIPAL);
         printf("%s", OPCAO_1);
         printf("%s", OPCAO_2);
         printf("%s", OPCAO_3);
         printf("%s", OPCAO_4);  //OPCAO_4 neste caso é "Encerrar" ****************************************************************
         
         opcao = LeOpcao();
         while(opcao <= 0 || opcao > 4){   /* Verifica se é uma opção válida */
             printf("%s", TXT_OUTPUT_INV);  //Alterar a mensagem ****************************************************************
             opcao = LeOpcao();
         }
         
         switch(opcao){
             case 1:
                  arqDlm = ConverteFixoDelim(nomeArqSaida, arqFix, separador);
                  printf("%s", ARQ_CONVERTIDO); //ARQ_CONVERTIDO = "Arquivo convertido\n" ****************************************************************
                  system("pause");
             break;
             case 2:
                  //Listar arquivos de dados no formato fixo ****************************************************************
                  system("pause");
             break;
             case 3:
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
    char lingua[5];
    char separador;
    char fimRegistro;
    FILE* arqFix, * arqDlm, * arqCfg;
    char* delim;
    Header* head;
    int i, j, numcampos, tamanhofix;
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
    AbreArquivoFixo(argv[1], &arqFix, &arqCfg);
    
    /* leitura dos campos */                        
    CarregaHeader(&head, &numcampos, arqCfg);
    
    Menu(head, arqFix, arqDlm, argv[2], separador);
    
    tamanhofix=0;
    
    for(i = 0; i < numcampos; i++)
       tamanhofix = tamanhofix + head[i].tamanho;   
    
    j=0;   
    //impressão dos campos do arquivo de tamanho fixo
    while(!feof(arqFix)) {
    //      linha = fread(string, 65, 1, arqFix);               
          registro = LeRegistroFixo(arqFix, numcampos, head);
          for(i=0; i<numcampos; i++)
                   fprintf(stdout, "%s ", registro[i]);
          printf("\n");
          //LiberaRegistro(registro); ??
          j++;
          }
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
    
    fclose(arqFix);
    fclose(arqDlm);
    fclose(arqCfg);
    free(head);
//    free(???); LiberaRegistro(????); ***********************************************************************************
    
    system("pause");
    return 0;

} /* main */
