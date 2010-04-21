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
    printf("\n%s: ", PEDE_OPCAO);
    scanf("%s", opcao);
    
    while(!VerificaDigitos(opcao)) {
       printf("%s", OPCAO_INV); 
       scanf("%s", opcao);
    }
    
    return atoi(opcao);

} /* LeOpcao */


void Menu(Header* head, FILE* arqFix, FILE* arqDlm, char* nomeArqSaida, char separador,int numcampos){
/* Menu do programa */
     
     int opcao;
     char *chavePrim;
     Boolean fim = false;
     Record registro;
     
     do {
         system("cls");
         printf("%s\n\n", TELA_PRINCIPAL);
         printf("%s\n", OPCAO_1);
         printf("%s\n", OPCAO_2);
         printf("%s\n", OPCAO_3);
         printf("%s\n", OPCAO_4);
         printf("%s\n", OPCAO_5);
         printf("%s\n", OPCAO_6);
         printf("%s\n", OPCAO_7);
         printf("%s\n", OPCAO_8);
         printf("%s\n", OPCAO_9);
         
         opcao = LeOpcao();
         while(opcao <= 0 || opcao > 9){   /* Verifica se � uma op��o v�lida */
             printf("%s", OPCAO_INV);
             opcao = LeOpcao();
         }
         
         switch(opcao){
             case 1:
                  /* converte um arquivo com campos de tamanho fixo para um de 
                     campos de tamanho variavel */
                  
                  fseek(arqFix, 0, SEEK_SET);
                  ConverteFixoDelim(nomeArqSaida, arqFix, separador, head, numcampos);
                  printf("\n%s\n\n", CONV_TERMINADA); 
                  
                  system("pause");
             break;
             case 2:
                  /* impress�o dos campos do arquivo de tamanho fixo */
                  
                   fseek(arqFix, 0, SEEK_SET);
                   ImprimeArquivoFixo(arqFix, numcampos, head);
                   
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
                  /* pesquisa um registro pela chave prim�ria */
                  
                  printf("%s :", PEDIR_CHAVE_PRIMARIA);
                  scanf("%s", chavePrim);
                  
                  if(VerificaRA(chavePrim)){
                     
                     if(PesquisaRegistro(nomeArqSaida, chavePrim, &registro)){
                         ImprimeRegistro(registro, head, numcampos);
                         LiberaRegistro(registro, numcampos);
                     }
                     else
                         printf("\n%s\n\n", REGISTRO_INEXISTENTE);
                  }
                  else
                      printf("\n%s\n\n", ERRO_RA);   /* RA Invalido */
                         
                  
                  system("pause");
             break;
             case 5:
                  /* Extra��o das chaves prim�rias */
                  
                  ExtraiChaves(arqFix, head);
                  printf("\n%s\n\n", ARQ_CHAVES_CRIADO);
                  
                  system("pause");
             break;
             case 6:
                  /* Classifica��o do arquivo das chaves */
                  
                  ClassificaChavePrimaria();
                  printf("\n%s\n\n", ARQ_CHAVES_CLASSIFICADO);
                  
                  system("pause");
             break;
             case 7:
                  /* Listar o arquivo com a extra��o das chaves geradas na op��o 5*/
                  
                  
                  
                  system("pause");
             break;
             case 8:
                  /* Listar o arquivo com a extra��o das chaves classificadas
                     geradas na op��o 6*/
                  
                  
                  
                  system("pause");
             break;
             case 9:
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

    LiberaMensagens();
    fclose(arqFix);
    free(head);
    
    system("pause");
    return 0;

} /* main */