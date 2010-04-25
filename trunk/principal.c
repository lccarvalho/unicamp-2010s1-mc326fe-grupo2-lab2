/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laboratório    02 
   - Manipulacao de arquivos com registros de tamanho fixo, campos de tamanho
     fixo e campos de tamanho variavel.
   - Construcao de uma biblioteca de funcoes que permitam realizar as operacoes
     de pesquisa, alteracao, remocao e insercao de registros e campos em um
     arquivo.
     - Construcao de funcoes para criacao e pesquisa de indices;
/******************************************************************************/

              
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
     char chavePrim[6];
     Boolean fim = false;
     Record registro;
     int tamreg = TamMaxRegistro(head, numcampos);
     FILE *arqChaves;
     
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
         while(opcao <= 0 || opcao > 9){   /* Verifica se é uma opção válida */
             printf("%s", OPCAO_INV);
             opcao = LeOpcao();
         }
         
         switch(opcao){
             case 1:
                  /* converte um arquivo com campos de tamanho fixo para um de 
                     campos de tamanho variavel */
                  
                  fseek(arqFix, 0, SEEK_SET);
                  arqDlm = ConverteFixoDelim(nomeArqSaida, arqFix, separador, head, numcampos);
                  printf("\n%s\n\n", CONV_TERMINADA); 
                  
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
                  
                  printf("\n%s: ", PEDIR_CHAVE_PRIMARIA);
                  scanf("%s", chavePrim);
                  
                  if(VerificaStringNumericaNaoNula(chavePrim, 6)){                                  
                  
                     registro = PesquisaRegistro(nomeArqSaida, chavePrim, 
                                              separador, tamreg, numcampos);  
                     if(registro != NULL) {

                          printf("\n");
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
                  /* Extração das chaves primárias */
                  
                  arqDlm = Fopen(nomeArqSaida, "r");
                  ExtraiChaves(arqDlm, separador, head);
                  fclose(arqDlm);
                  printf("\n%s\n\n", ARQ_CHAVES_CRIADO);
                  
                  system("pause");
             break;
             case 6:
                  /* Classificação do arquivo das chaves */
                  
                  ClassificaChavePrimaria();
                  printf("\n%s\n\n", ARQ_CHAVES_CLASSIFICADO);
                  
                  system("pause");
             break;
             case 7:
                  /* Listar o arquivo com a extração das chaves geradas na opção 5*/
                  
                  arqChaves = Fopen("chaves.ind", "r");
                  
                  ImprimeChaves(arqChaves);
                  
                  fclose(arqChaves);
                  
                  system("pause");
             break;
             case 8:
                  /* Listar o arquivo com a extração das chaves classificadas
                     geradas na opção 6 */
                  
                  arqChaves = Fopen("chavesClas.ind", "r");
                  
                  ImprimeChaves(arqChaves);
                  
                  fclose(arqChaves);
                  
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

    LiberaMensagens();
    fclose(arqFix);
    free(head);
    
    system("pause");
    return 0;

} /* main */
