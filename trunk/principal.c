/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laborat�rio    02A - Programa para leitura de dados de arquivo em formato  */
/*                      de campo fixo, convers�o para formato delimitado e    */
/*                      impress�o nos dois formatos                           */
/******************************************************************************/
/*
   1a vers�o de principal.c
   N�o implementa menus, apenas executa em sequencia 
   as tarefas das op��es 1, 2 e 3
   Para testes
              */
              
#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "languages.h"
#include "envelope.h"

/* o programa recebe os nomes dos arquivos de entrada e sa�da */
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
         while(opcao <= 0 || opcao > 4){   /* Verifica se � uma op��o v�lida */
             printf("%s", TXT_OUTPUT_INV);
             opcao = LeOpcao();
         }
         
         switch(opcao){
             case 1:
                  /* converte um arquivo com campos de tamanho fixo para um de 
                     campos de tamanho variavel */
                  
                  fseek(arqFix, 0, SEEK_SET);
                  ConverteFixoDelim(nomeArqSaida, arqFix, separador, head, numcampos, tamanhofix);
                  printf("%s", TXT_OUTPUT_1); 
                  
                  system("pause");
             break;
             case 2:
                  /* impress�o dos campos do arquivo de tamanho fixo */
                  
                   fseek(arqFix, 0, SEEK_SET);
                   ImprimeArquivoFixo(arqFix, numcampos, head, tamanhofix);
                   
                   system("pause");
             break;
             case 3:
                  /* impress�o dos campos do arquivo de tamanho variavel */
                  
                  arqDlm = Fopen(nomeArqSaida, "r");
                  ImprimeArquivoDelim(arqDlm, numcampos, head, separador);
                  fclose(arqDlm);
                  
                  system("pause");
             break;
             case 4:
                  fim = true;
             break;
         }
     } while (!fim);
     
} /* Menu */


int main(int argc, char *argv[]) {
    /* vari�veis */
    char separador;
    FILE *arqFix, *arqDlm, *arqCfg;
    Header* head;
    int numcampos;
    
    /* arquivo de configura��o */
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
