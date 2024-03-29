/******************************************************************************/
/* Grupo 2:                                                                   */
/*          Felipe Augusto da Silva    RA 096993                              */
/*          Lucas Barbi Rezende        RA 097042                              */
/*          Luiz Claudio Carvalho      RA 800578                              */
/*                                                                            */
/* MC236EF  1o semestre 2010                                           UNICAMP*/

/* languages.h - M�dulo de configura��o da lingua da interface */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "envelope.h"


/* Mensagens de erro em main */
char * MSG_ERRO_NUM_ARGUMENTOS;
char * MSG_ERRO_CONFIG;
char * MSG_ERRO_ABERTURA_ARQUIVO;
char * MSG_ERRO_ARQ_CFG_BDADOS;
char * MSG_ERRO_MEMORIA;

/* Menu Principal */
char * TELA_PRINCIPAL;
char * OPCAO_1;
char * OPCAO_2;
char * OPCAO_3;
char * OPCAO_4;
char * OPCAO_5;
char * OPCAO_6;
char * OPCAO_7;
char * OPCAO_8;
char * OPCAO_9;
char * OPCAO_10;
char * OPCAO_11;
char * OPCAO_12;

char * OPCAO_INV;
char * CONV_TERMINADA;
char * PEDE_OPCAO;
char * NUM_REGS;
char * NUM_BYTES_FIX;
char * NUM_BYTES_DLM;
char * PEDIR_CHAVE_PRIMARIA;
char * PEDIR_REG_A_REMOVER;
char * REGISTRO_INEXISTENTE;
char * ARQ_CHAVES_CRIADO;
char * ARQ_CHAVES_CLASSIFICADO;
char * CHAVE_PRIM;
char * ENDERECO;
char * REG_REMOVIDO;

/* erros nos registros */
char * ERRO_RA;
char * ERRO_NOME;
char * ERRO_TEL;
char * ERRO_SEXO;
char * ERRO_CURSO;
char * NUM_REG_INV;
char * ERRO_DADOS_OBRIG;



     
void Linguagem(char *lingua);
/* Configura as mensagens de tela do programa conforme a lingua em uso, 
   identificada no arquivo config.l1b */        

void LiberaMensagens();
/* Libera o espa�o alocado para as mensagens */

