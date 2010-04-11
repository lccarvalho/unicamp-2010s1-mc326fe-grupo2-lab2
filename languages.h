/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/
/* Laboratório    01B - Apresentação de Nome e RA de alunos                   */
/*                      a partir de dados lidos em arquivo e com múltiplas    */
/*                      opções de lingua de interface                         */
/******************************************************************************/
/*
 * languages.h - Módulo de configuração da lingua da interface
 */

#include <string.h>



/* Mensagens de erro em main */
char * MSG_ERRO_NUM_ARGUMENTOS;
char * MSG_ERRO_CONFIG;
char * MSG_ERRO_ABERTURA_ARQUIVO;
char * MSG_ERRO_ARQ_CFG_BDADOS;


/* Mensagens de erro na validação de dados de entrada
   para os códigos previstos em alunos.h */
char *msg_erro[6];

/* Menu Principal */
char * TELA_PRINCIPAL;
char * OPCAO_1;
char * OPCAO_2;
char * OPCAO_3;
char * OPCAO_4;
char * OPCAO_5;

/* Textos da função Opcoes */
char * TXT_OUTPUT_1;
char * TXT_OUTPUT_2;
char * TXT_OUTPUT_3;
char * TXT_OUTPUT_4;
char * TXT_OUTPUT_INV;
char * PEDE_OPCAO;




     
void Linguagem(char *lingua);
/* Configura as mensagens de tela do programa conforme a lingua em uso, 
   identificada no arquivo config.l1b
*/        
