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

/* database.h - conjunto de funções para manipulação de banco de dados */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "languages.h"
#include "envelope.h"
#define branco ' '
#define tamPrimCampoHd 20
#define tamUltCampoHd 40

/*** Estruturas de dados ******************************************************/

/* Definição de tipo booleano */
typedef enum {false, true} Boolean;


/* Definição de um vetor de ponteiros para caractere. Uma vez inicializados,
   cada um dos ponteiros do vetor irá apontar para a posição inicial do
   conteúdo do campo[i] do registro correspondente. Caso seja necessário
   carregar mais de um registro do banco de dados na memória, cada um de seus 
   campos poderá ser acessado por: registro[m].campo[n]   */
typedef char** Record;


/* Definição de estrutura que armazena as características de um campo de um
   arquivo de dados. Estas características devem ser extraídas de um arquivo de
   configuração ou de uma seção específica do arquivo de dados */
typedef struct {
        char nome[tamPrimCampoHd+1];
        char tipo;
        int inicio;
        int tamanho;
        Boolean obrig;
        char msg[tamUltCampoHd+1];
        } Header;


/*** Funções ******************************************************************/

Boolean VerificaStringNumericaNaoNula(char *string, int nDig);
/* Verifica se string só contém números, se os números não são todos 0 e
   se string tem nDig. */

Boolean VerificaDigitos(char *string);
/* Retorna "true" se a string só contém digitos de 0-9
   ou retorna "false" caso contrário */

Boolean LeConfig(char *sep);
/* Procura o arquivo Config.l1b e carrega em lang e sep a lingua de interface 
   do programa e o caractere que deve separar os dados no arquivo de entrada. 
   Retorna erro se não encontrar o arquivo ou se o conteúdo for inválido */
     
void AbreArquivoFixo(char* nome, FILE** arqFix, FILE** arqCfg);
/* Abre o arquivo de entrada (.fix com registros de tamanho fixo) e
   seu respectivo arquivo de configuração (.cfg) */

void CarregaHeader(Header** h, int* numcampos, FILE* arqCfg);
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg */

Record LeRegistroFixo(char* linha, int n, Header* h);
/* Aloca a memória dinâmica necessária e carrega na mesma o conteúdo dos n 
   campos do registro corrente de um arquivo de dados em formato de campo fixo
   (arq). Carrega Record com os endereços do conteúdo de cada campo. 
   Deixa o ponteiro de arqFix na posição apropriada para a próxima leitura.
   Retorna NULL se houver algum erro no registro. */
   
FILE* ConverteFixoDelim(char* nome, FILE* arqFix, char sep, Header* head, int numcampos);
/* Converte um arquivo de campos de tamanho fixo em outro de campos de tamanho variavel.
   Despreza registros invalidos */   
 
void ImprimeArquivoFixo(FILE* arqFix, int numcampos, Header* head);
/* Imprime os dados de um arquivo de campos de tamanho fixo. Nao imprime
   registros invalidos */

void ImprimeArquivoDelim(FILE* arqDel, int numcampos, Header* head, char c);
/* Imprime os dados de um arquivo de campos de tamanho variavel */   

void LiberaRegistro(Record registro, int n);
/* Libera todas as strings apontadas por record e também os apontadores */
   
Record PesquisaRegistro(char* arq, char* key, char sep, int max, int n);
/* Procura pela chave primaria 'key' no arquivo de formato variavel
   separado por sep, com n campos e linha de tamanho máximo max.
   Se encontrar, coloca em 'registro' as informações e retorna true, caso 
   contrário retorna false */
   
void ImprimeRegistro(Record registro, Header* head, int numcampos);
/* Imprime todos os campos de um registro */

void ExtraiChaves(FILE *arqDlm, char* sep, Header* head);
/* Cria um arquivo 'chaves.ind' com as chaves primárias do arquivo de dados arqDlm,
   junto com os respectivos endereços dos registros no arquivo */
   
void ClassificaChavePrimaria();
/* Cria um arquivo 'chavesClas.ind' a partir do arquivo 'chaves.ind' já criado,
   classificando-o */

void ImprimeChaves(FILE *arq);
/* Imprime as chaves primarias e o endereço */


/*******************************NOVAS FUNÇÕES DO LAB2C*************************/
Record PesqIndexRegistro();
/* ESCREVER O QUE FAZ E INCLUIR OS PARÂMETROS */

void RemoveRegistro();
/* ESCREVER O QUE FAZ E INCLUIR PARÂMETROS E TIPO DA FUNÇÃO*/
