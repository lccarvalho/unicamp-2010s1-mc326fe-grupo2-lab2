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
                    
     case 101110:   //ingles - en           
     
MSG_ERRO_NUM_ARGUMENTOS = "The command line should contain only the name of the file to be opened";
MSG_ERRO_CONFIG = "Error in file config.l1b";
MSG_ERRO_ABERTURA_ARQUIVO = "Data file not found or defective";

/* Mensagens de erro na validação de dados de entrada
   para os códigos previstos em alunos.h */
msg_erro[0] = "Insufficient data in the input file.";
msg_erro[1] = "Invalid name.";
msg_erro[2] = "RA invalid.";
msg_erro[3] = "Invalid character in name: ";
msg_erro[4] = "Invalid character in RA: ";
msg_erro[5] = "Invalid character to be searched: ";


/* Menu Principal */
TELA_PRINCIPAL = "Project 1b\n\nOptions\n";
OPCAO_1 = "1: Present your data Student\n";
OPCAO_2 = "2: Provide the name of the student converted to upper case\n";
OPCAO_3 = "3: Present the parts (words) that make up the name\n";
OPCAO_4 = "4: Display frequency of a character in the name\n";
OPCAO_5 = "5: Quit\n";

/* Textos da função Opcoes */
TXT_OUTPUT_1 = "\n Student Data: \n";
TXT_OUTPUT_2 = "\n Conversion of the name to uppercase: \n";
TXT_OUTPUT_3 = "\n Separate words: \n";
TXT_OUTPUT_4 = "\n Number of occurrences of ";
TXT_OUTPUT_INV = "\n Option invalidate (1-5) \n";
PEDE_OPCAO = "\n Select the option you want: ";    
  
     break;
  
     case 101115:    //espanhol - es              
     
MSG_ERRO_NUM_ARGUMENTOS = "La linea de comandos debe contener solo el nombre del archivo que se abrira";
MSG_ERRO_CONFIG = "Error en el archivo config.l1b";
MSG_ERRO_ABERTURA_ARQUIVO = "Los datos no se encuentra el archivo o malo";

/* Mensagens de erro na validação de dados de entrada
   para os códigos previstos em alunos.h */
msg_erro[0] = "Escasez de datos en el archivo de entrada.";
msg_erro[1] = "Nombre no valido.";
msg_erro[2] = "RA no valido.";
msg_erro[3] = "Caracter no valido en el nombre: ";
msg_erro[4] = "Caracter no valido en la RA: ";
msg_erro[5] = "Caracter no valido a buscar: ";


/* Menu Principal */
TELA_PRINCIPAL = "Proyecto 1b\n\nOpciones:\n";
OPCAO_1 = "1: Presentar datos de los estudiante \n";
OPCAO_2 = "2: Presentar el nombre del estudiante convierte a mayusculas \n";
OPCAO_3 = "3: Presentar las partes (palabras) que componen el nombre de estudiante \n";
OPCAO_4 = "4: Frecuencia de la pantalla de un caracter en el nombre de estudiante \n";
OPCAO_5 = "5: Salir \n";

/* Textos da função Opcoes */
TXT_OUTPUT_1 = "\n Datos del estudiante: \n";
TXT_OUTPUT_2 = "\n Conversion del nombre en mayusculas: \n";
TXT_OUTPUT_3 = "\n Palabras por separado: \n";
TXT_OUTPUT_4 = "\n Numero de casos de ";
TXT_OUTPUT_INV = "\n Invalidar la opcion (1-5) \n";
PEDE_OPCAO = "\n Seleccione la opcion que desee: ";  

     break;
  
     default:    //brasil - br   ou vazio
  
MSG_ERRO_NUM_ARGUMENTOS = "A linha de comando deve conter apenas o nome do arquivo a ser aberto";
MSG_ERRO_CONFIG = "Erro no arquivo config.l1b";
MSG_ERRO_ABERTURA_ARQUIVO = "Arquivo de dados não encontrado ou defeituoso";

/* Mensagens de erro na validação de dados de entrada
   para os códigos previstos em alunos.h */
msg_erro[0] = "Dados insuficientes no arquivo de entrada.";
msg_erro[1] = "Nome invalido.";
msg_erro[2] = "RA invalido.";
msg_erro[3] = "Caractere inválido no nome: ";
msg_erro[4] = "Caractere inválido no RA: ";
msg_erro[5] = "Caractere invalido a ser procurado: ";


/* Menu Principal */
TELA_PRINCIPAL = "Projeto 1b\n\nOpcoes\n";
OPCAO_1 = "1: Apresentar os dados do Aluno\n";
OPCAO_2 = "2: Apresentar o nome do Aluno Convertido para letras Maiusculas\n";
OPCAO_3 = "3: Apresentar as partes (palavras) que compoem o nome\n";
OPCAO_4 = "4: Apresentar frequencia de um caractere em nome\n";
OPCAO_5 = "5: Encerrar\n";

/* Textos da função Opcoes */
TXT_OUTPUT_1   = "\n Dados do Aluno:\n  ";
TXT_OUTPUT_2   = "\n Conversao do nome para Maiuscula:\n  ";
TXT_OUTPUT_3   = "\n Palavras Separadas:\n"; 
TXT_OUTPUT_4   = "\n Numero de ocorrencias de ";
TXT_OUTPUT_INV = "\n Opcao invalida (1-5)\n";    
PEDE_OPCAO     = "\n Escolha a opcao desejada: ";  

     }        
     
}

