/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/

/* languages.c - Módulo de configuração da lingua da interface */

#include "languages.h"


void LeMensagem(FILE *lang, char **msg){
/* Le uma mensagem no arquivo 'lang' e coloca em 'msg' */
     
     char buffer[256];
     fgets(buffer, 256, lang);
     *msg = Malloc(sizeof(char)*strlen(buffer));
     buffer[strlen(buffer)-1] = '\0';
     strcpy(*msg, buffer);

} /* LeMensagem */


void Linguagem(char *lingua){
/* Configura as mensagens de tela do programa conforme a lingua em uso, 
   identificada no arquivo config.l1b */        
   
   FILE *lang;
   strcat(lingua, ".lng");
   lang = fopen(lingua, "r");
   
   if(lang == NULL) {
      fprintf(stderr, "Language file not found\n");
      system("pause");
      exit (0);
   }
   
   LeMensagem(lang, &MSG_ERRO_NUM_ARGUMENTOS);
   LeMensagem(lang, &MSG_ERRO_CONFIG);
   LeMensagem(lang, &MSG_ERRO_ABERTURA_ARQUIVO);
   LeMensagem(lang, &MSG_ERRO_MEMORIA);
   LeMensagem(lang, &TELA_PRINCIPAL);
   LeMensagem(lang, &OPCAO_1);
   LeMensagem(lang, &OPCAO_2);
   LeMensagem(lang, &OPCAO_3);
   LeMensagem(lang, &OPCAO_4);
   LeMensagem(lang, &OPCAO_5);
   LeMensagem(lang, &OPCAO_6);
   LeMensagem(lang, &OPCAO_7);
   LeMensagem(lang, &OPCAO_8);
   LeMensagem(lang, &OPCAO_9);
   LeMensagem(lang, &CONV_TERMINADA);
   LeMensagem(lang, &OPCAO_INV);
   LeMensagem(lang, &PEDE_OPCAO);
   LeMensagem(lang, &NUM_REGS);
   LeMensagem(lang, &NUM_BYTES_FIX);
   LeMensagem(lang, &NUM_BYTES_DLM);
   LeMensagem(lang, &PEDIR_CHAVE_PRIMARIA);
   LeMensagem(lang, &REGISTRO_INEXISTENTE);
   LeMensagem(lang, &ARQ_CHAVES_CRIADO);
   LeMensagem(lang, &ARQ_CHAVES_CLASSIFICADO);
   LeMensagem(lang, &ERRO_RA);
   LeMensagem(lang, &ERRO_NOME);
   LeMensagem(lang, &ERRO_TEL);
   LeMensagem(lang, &ERRO_SEXO);
   LeMensagem(lang, &ERRO_CURSO);
   LeMensagem(lang, &CHAVE_PRIM);
   LeMensagem(lang, &ENDERECO);

   fclose(lang);
     
} /* Linguagem */


void LiberaMensagens(){
/* Libera o espaço alocado para as mensagens */

   free(&MSG_ERRO_NUM_ARGUMENTOS);
   free(&MSG_ERRO_CONFIG);
   free(&MSG_ERRO_ABERTURA_ARQUIVO);
   free(&MSG_ERRO_MEMORIA);
   free(&TELA_PRINCIPAL);
   free(&OPCAO_1);
   free(&OPCAO_2);
   free(&OPCAO_3);
   free(&OPCAO_4);
   free(&OPCAO_5);
   free(&OPCAO_6);
   free(&OPCAO_7);
   free(&OPCAO_8);
   free(&OPCAO_9);
   free(&CONV_TERMINADA);
   free(&OPCAO_INV);
   free(&PEDE_OPCAO);
   free(&NUM_REGS);
   free(&NUM_BYTES_FIX);
   free(&NUM_BYTES_DLM);
   free(&PEDIR_CHAVE_PRIMARIA);
   free(&REGISTRO_INEXISTENTE);
   free(&ARQ_CHAVES_CRIADO);
   free(&ARQ_CHAVES_CLASSIFICADO);
   free(&ERRO_RA);
   free(&ERRO_NOME);
   free(&ERRO_TEL);
   free(&ERRO_SEXO);
   free(&ERRO_CURSO);
   free(&CHAVE_PRIM);
   free(&ENDERECO);
   
   
} /* LiberaMensagens */

