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
 * languages.c - Módulo de configuração da lingua da interface
 */

#include "languages.h"

void Linguagem(char *lingua){
/* Configura as mensagens de tela do programa conforme a lingua em uso, 
   identificada no arquivo config.l1b
   */        
   
   int opcao = (int)(lingua[0])*1000 + (int)(lingua[1]);

   switch(opcao){


/********* 1 - INGLÊS EUA *****************************************************/  
   case 101110:   //ingles - en           
     
MSG_ERRO_NUM_ARGUMENTOS   = "command line should contain (1)file to be opened and (2)created";
MSG_ERRO_CONFIG           = "Error in file config.l1b";
MSG_ERRO_ABERTURA_ARQUIVO = "Data file not found or corrupted\n";

/* Mensagens de erro ...??? */
msg_erro[0]               = "Insufficient data in the input file.";
msg_erro[1]               = "Invalid name.";
msg_erro[2]               = "RA invalid.";
msg_erro[3]               = "Invalid character in name: ";
msg_erro[4]               = "Invalid character in RA: ";
msg_erro[5]               = "Invalid character to be searched: ";

/* Menu Principal */
TELA_PRINCIPAL            = "Project 2a\n\nOptions\n";
OPCAO_1                   = "1: Create delimited data file from fixed length field data file\n";
OPCAO_2                   = "2: Print data from fixed length field data file\n";
OPCAO_3                   = "3: Print data from delimited data file\n";
OPCAO_4                   = "4: Quit\n";

/* Textos da função Opcoes */

TXT_OUTPUT_1 = "\nFile conversion success\n";
TXT_OUTPUT_2 = "\n  \n";
TXT_OUTPUT_3 = "\n  \n";
TXT_OUTPUT_4 = "\n  ";
TXT_OUTPUT_INV = "\n Invalid option (1-4) \n";
PEDE_OPCAO = "\n Select an option: ";
NUM_REGS = "\nNumber of registers: ";
NUM_BYTES_FIX = "Number of bytes of original file: ";
NUM_BYTES_DLM = "Number of bytes of converted file: ";
 
/**********************************************************INGLÊS EUA *********/  
  
     break;
     
     
     
/******2 - PORTUGUÊS BRASIL****************************************************/  
     default:    //brasil - br   ou vazio
  
MSG_ERRO_NUM_ARGUMENTOS   = "linha de comando deve conter (1)arquivo a ser aberto e (2)criado";
MSG_ERRO_CONFIG           = "Erro no arquivo config.l1b";
MSG_ERRO_ABERTURA_ARQUIVO = "Arquivo de dados não encontrado ou defeituoso\n";

/* Mensagens de erro ...??? */
msg_erro[0]               = "Dados insuficientes no arquivo de entrada.";
msg_erro[1]               = "Nome invalido.";
msg_erro[2]               = "RA invalido.";
msg_erro[3]               = "Caractere inválido no nome: ";
msg_erro[4]               = "Caractere inválido no RA: ";
msg_erro[5]               = "Caractere invalido a ser procurado: ";


/* Menu Principal */
TELA_PRINCIPAL            = "Projeto 2a\n\nOpcoes\n";
OPCAO_1                   = "1: Criar arquivo delimitado a partir de arquivo de campo fixo\n";
OPCAO_2                   = "2: Imprimir os dados a partir de do arquivo de campo fixo\n";
OPCAO_3                   = "3: Imprimir os dados a partir de do arquivo de campo delimitado\n";
OPCAO_4                   = "4: Encerrar\n";

/* Textos da função Opcoes */

TXT_OUTPUT_1 = "\nConversao terminada\n";
TXT_OUTPUT_2 = "\n  \n";
TXT_OUTPUT_3 = "\n  \n";
TXT_OUTPUT_4 = "\n  ";
TXT_OUTPUT_INV = "\n Opcao invalida (1-4)\n";    
PEDE_OPCAO     = "\n Escolha a opcao desejada: ";
NUM_REGS = "\nNumero de registros: ";
NUM_BYTES_FIX = "Numero de bytes do arquivo original: ";
NUM_BYTES_DLM = "Numero de bytes do arquivo convertido: ";

/******************************************************PORTUGUÊS BRASIL********/  

     } /* switch */       
     
} /* Linguagem */

