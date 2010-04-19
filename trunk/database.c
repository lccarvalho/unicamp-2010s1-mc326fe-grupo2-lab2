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
 * database.c - conjunto de funções para manipulação de banco de dados
 */

#include "database.h"
#include "languages.h"


Boolean VerificaDigitos(char *string) {
/* Retorna "true" se a string só contém digitos de 0-9
   ou retorna "false" caso contrário */

    int i, tam = strlen(string);
    
    for(i = 0; i < tam; i++)
       if(!isdigit(string[i]))
          return false;
    
    return true;

} /* VerificaDigitos */


Boolean LeConfig(char *sep){
/* Procura o arquivo Config.l1b e carrega em lang e sep a lingua de interface 
   do programa e o caractere que deve separar os dados no arquivo de entrada. 
   Retorna erro se não encontrar o arquivo ou se o conteúdo for inválido */
   
    char lingua[5];
    FILE *arqConfig = fopen("Config.l1b", "rt");
    
    if (arqConfig == NULL) 
                        return false;     
   
    fgets(lingua, 5, arqConfig);  //leitura do br no arquivo                        
    fgets(sep, 5, arqConfig);       //leitura do separador no arquivo                           

    fclose(arqConfig); 
   
    Linguagem(lingua);

    return true;   
} /* LeConfig */


void AbreArquivoFixo(char* nome, FILE** arqFix, FILE** arqCfg){
/* Abre o arquivo de entrada (.fix com registros de tamanho fixo) e
   seu respectivo arquivo de configuração (.cfg) */   
   
   *arqFix = Fopen(nome, "r");    /* Abre arquivo de dados */
   
   /* abre arquivo de configuração (mesmo nome com extensão .cfg) */
   nome[strlen(nome)-3] = '\0';
   *arqCfg = Fopen(strcat(nome, "cfg"), "r");
   
} /* AbreArquivoFixo */
   
   
void TiraBrancosDoFinal(char* s){
/* Elimina todos os brancos em excesso no final de uma string. */
    
    int i = strlen(s) - 1;     //Último elemento da string
    while(i >= 0 && s[i] == branco)
       i--;
    s[i+1] = '\0';
    
} /* TiraBrancosDoFinal */


void CarregaHeader(Header** h, int* numcampos, FILE* arqCfg){
/* Carrega o vetor head com os campos do banco de dados definido por arqCfg */

    int i, final;
    char c;
    
    fscanf(arqCfg, "%d", numcampos);     /* Le número de campos */
    fseek(arqCfg, 2, SEEK_CUR);
    *h = malloc(sizeof(Header)*(*numcampos));     /* Aloca o vetor head */
    
    for(i = 0; i < *numcampos; i++) {
        
        /* Le nome */
        fread((*h+i)->nome, tamPrimCampoHd, 1, arqCfg);
        (*h+i)->nome[tamPrimCampoHd] = '\0';
        TiraBrancosDoFinal((*h+i)->nome);
    
        /* Le tipo */
        (*h+i)->tipo = fgetc(arqCfg);
        
        /* Le endereço de inicio e final de um campo e calcula seu tamanho */
        fscanf(arqCfg, "%d %d", &((*h+i)->inicio), &final);
        (*h+i)->tamanho = final - (*h+i)->inicio + 1;
        
        /* Le caractere de obrigatoriedade do campo */
        fseek(arqCfg, 1, SEEK_CUR);
        c = fgetc(arqCfg);
        if(c == 'S')
            (*h+i)->obrig = true;
        else
            (*h+i)->obrig = false;
            
        /* Le mensagem */    
        fseek(arqCfg, 1, SEEK_CUR);
        fread((*h+i)->msg, tamUltCampoHd, 1, arqCfg);
        (*h+i)->msg[tamUltCampoHd] = '\0';
        TiraBrancosDoFinal((*h+i)->msg);
    
        fseek(arqCfg, 2, SEEK_CUR);
    }
    
} /* CarregaHeader */

Record LeRegistroFixo(char* linha, int n, Header* h) {
/* Aloca a memória dinâmica necessária e carrega na mesma o conteúdo dos n 
   campos do registro corrente de arqFix. Carrega Record com os endereços do 
   conteúdo de cada campo. Deixa o ponteiro de arqFix na posição apropriada
   para a próxima leitura */
   
   
   int i;
   Record registro;
   
   registro = malloc(sizeof(char*)*n);
   
   for(i=0;i<n;i++){
                    
   registro[i] = (char*)malloc(sizeof(char)*(h[i].tamanho+1));
   strncpy(registro[i], &linha[h[i].inicio-1], h[i].tamanho);
   registro[i][h[i].tamanho] = '\0';              
   TiraBrancosDoFinal(registro[i]);
   }
   
   return registro;
}
   

void ConverteFixoDelim(char* nome, FILE* arqFix, char sep, Header* head, int numcampos, int tamanhofix){
/* Converte um arquivo de campos de tamanho fixo em outro de campos de tamanho variavel */
   

   FILE* dlm;
   int i, numRegs = 0, numBytesFix, numBytesDlm;
   char *linha;
   char fimReg;
   Record registro;
   
   dlm = Fopen(nome, "w");
   
   fimReg = head[numcampos-1].msg[0];

   linha = malloc(sizeof(char)*(tamanhofix));
                  
   /* Escreve os dados no novo arquivo */
   while(!feof(arqFix)) {
                                       
       numRegs++;
       
       fread(linha, tamanhofix, 1, arqFix);
       
       registro = LeRegistroFixo(linha, numcampos, head);
       
       for(i=0; i<numcampos-1; i++)
           fprintf(dlm, "%s|", registro[i]);     
       
       fprintf(dlm, "%s\n", registro[i]);
   
       LiberaRegistro(registro, numcampos);
   }
   
   numBytesFix = ftell (arqFix); /* Conta os bytes do arquivo original */
   numBytesDlm = ftell (dlm);  /* Conta os bytes do arquivo convertido */
   

   fprintf(stdout, "%s %d\n", NUM_REGS, numRegs);
   fprintf(stdout, "%s %d\n", NUM_BYTES_FIX, numBytesFix);
   fprintf(stdout, "%s %d\n", NUM_BYTES_DLM, numBytesDlm);
   
   free(linha);                 
   fclose(dlm);
}   
   
   
      
void ImprimeArquivoFixo(FILE* arqFix, int numcampos, Header* head, int tamanhofix){
/* Imprime os dados de um arquivo de campos de tamanho fixo */

     int i;
     char *linha;
     Record registro;
     printf("\n");
                  
     linha = malloc(sizeof(char)*(tamanhofix));
                  
     while(!feof(arqFix)) {
                                       
        fread(linha, tamanhofix, 1, arqFix);
                      
        registro = LeRegistroFixo(linha, numcampos, head);
                      
        /* imprime o nome do campo e seu respectivo valor */
        for(i=0; i<numcampos-1; i++) {
           fprintf(stdout, "%s: ", head[i].nome);
           fprintf(stdout, "%s \n", registro[i]);
        }
        printf("\n");
                      
        LiberaRegistro(registro, numcampos);
     }
                   
     free(linha);
                   
     fseek(arqFix, 0, SEEK_SET);     /* Volta para o inicio do arquivo */ 
      
} /* ImprimeArquivoFixo */


void ImprimeArquivoDelim(FILE* arqDel, int numcampos, Header* head, char c){
/* Imprime os dados de um arquivo de campos de tamanho variavel */

     int i, j;
     char aux[300];
     char g;
     printf("\n");
                  
                
     while(!feof(arqDel)) {
                                       
                  
        /* imprime o nome do campo e seu respectivo valor */
        for(i=0; i<numcampos-2; i++) {
           
           g=fgetc(arqDel);
           j=0;
            
           while (g!=c){
                aux[j]=g;
                j++; 
                 
           } 
           
           aux[j]='\0';
                 
           fprintf(stdout, "%s: ", head[i].nome);
           fprintf(stdout, "%s \n", aux);
        }
        g=fgetc(arqDel);
        printf("\n");
                      
     }
                   
                   
     fseek(arqDel, 0, SEEK_SET);     /* Volta para o inicio do arquivo */ 
      
} /* ImprimeArquivoVariavel */
      
      
void LiberaRegistro(Record registro, int n){
/* Libera todas as strings apontadas por record e também os apontadores */
     
     int i;
     for(i = 0; i < n; i++)
        free(registro[i]);
     free(registro);
     
} /* LiberaRegistro */
   
