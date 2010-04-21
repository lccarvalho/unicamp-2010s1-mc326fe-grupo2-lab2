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

#define PEDIR_CHAVE_PRIMARIA "" //TEMPORARIO**********************************************************************************
#define REGISTRO_INEXISTENTE ""
#define ARQ_CHAVES_CRIADO ""
#define ARQ_CHAVES_CLASSIFICADO ""
#define OPCAO_4 "4\n"
#define OPCAO_5 "5\n"
#define OPCAO_6 "6\n"
#define OPCAO_7 "7\n"
#define OPCAO_8 "8\n"

void Menu(Header* head, FILE* arqFix, FILE* arqDlm, char* nomeArqSaida, char separador,int numcampos){
/* Menu do programa */
     
     int opcao;
     char *chavePrim;
     Boolean fim = false;
     Record registro;
     
     do {
         system("cls");
         printf("%s", TELA_PRINCIPAL);
         printf("%s", OPCAO_1);
         printf("%s", OPCAO_2);
         printf("%s", OPCAO_3);
         printf("%s", OPCAO_4);
         printf("%s", OPCAO_5);
         printf("%s", OPCAO_6);
         printf("%s", OPCAO_7);
         printf("%s", OPCAO_8);
         printf("%s", OPCAO_9);
         
         opcao = LeOpcao();
         while(opcao <= 0 || opcao > 9){   /* Verifica se é uma opção válida */
             printf("%s", TXT_OUTPUT_INV);
             opcao = LeOpcao();
         }
         
         switch(opcao){
             case 1:
                  /* converte um arquivo com campos de tamanho fixo para um de 
                     campos de tamanho variavel */
                  
                  fseek(arqFix, 0, SEEK_SET);
                  ConverteFixoDelim(nomeArqSaida, arqFix, separador, head, numcampos);
                  printf("%s", TXT_OUTPUT_1); 
                  
                  system("pause");
             break;
             case 2:
                  /* impressão dos campos do arquivo de tamanho fixo */
                  
                   fseek(arqFix, 0, SEEK_SET);
                   ImprimeArquivoFixo(arqFix, numcampos, head);
                   
                   system("pause");
             break;
             case 3:
                  /* impressão dos campos do arquivo de tamanho variavel */
                  
                  arqDlm = Fopen(nomeArqSaida, "r");
                  ImprimeArquivoDelim(arqDlm, numcampos, head, separador);
                  fclose(arqDlm);
                  
                  system("pause");
             break;
             case 4:
                  /* pesquisa um registro pela chave primária */
                  
                  printf("%s :", PEDIR_CHAVE_PRIMARIA);
                  scanf("%s", chavePrim);
                  
                  if(VerificaRA(chavePrim)){
                     
                     if(PesquisaRegistro(nomeArqSaida, chavePrim, &registro)){
                         ImprimeRegistro(registro, head, numcampos);
                         LiberaRegistro(registro, numcampos);
                     }
                     else
                         printf("%s", REGISTRO_INEXISTENTE);
                  }
                  else
                      printf("%s", msg_erro[2]);   /* RA Invalido */
                         
                  
                  system("pause");
             break;
             case 5:
                  /* Extração das chaves primárias */
                  
                  ExtraiChaves(arqFix, head);
                  printf("%s", ARQ_CHAVES_CRIADO);
                  
                  system("pause");
             break;
             case 6:
                  /* Classificação do arquivo das chaves */
                  
                  ClassificaChavePrimaria();
                  printf("%s", ARQ_CHAVES_CLASSIFICADO);
                  
                  system("pause");
             break;
             case 7:
                  /* Listar o arquivo com a extração das chaves geradas na opção 5*/
                  
                  
                  
                  system("pause");
             break;
             case 8:
                  /* Listar o arquivo com a extração das chaves classificadas
                     geradas na opção 6*/
                  
                  
                  
                  system("pause");
             break;
             case 9:
                  fim = true;
             break;
         }
     } while (!fim);
     
} /* Menu */


int main(int argc, char *argv[]) {
    /* variáveis */
    char separador;
    FILE *arqFix, *arqDlm, *arqCfg;
    Header* head;
    int numcampos;
    
    /* arquivo de configuração */
    if(!LeConfig(&separador))
       Erro(MSG_ERRO_CONFIG);
    
    /* checa linha de comando */
    if(argc != QTE_ARGUMENTOS)
       Erro(MSG_ERRO_NUM_ARGUMENTOS);

    /* abertura dos arquivos */
    AbreArquivoFixo(argv[1], &arqFix, &arqCfg);
    
    /* leitura dos campos */                        
    CarregaHeader(&head, &numcampos, arqCfg);       
    
    Menu(head, arqFix, arqDlm, argv[2], separador, numcampos);

    fclose(arqFix);
    free(head);
    
    system("pause");
    return 0;

} /* main */
