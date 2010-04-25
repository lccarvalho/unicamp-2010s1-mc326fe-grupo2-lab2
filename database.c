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

/* database.c - conjunto de funções para manipulação de banco de dados */

#include "database.h"
#include "languages.h"


/* Funções Auxiliares (não incluídas em database.h) ***************************/

void TiraBrancosDoFinal(char* s){
/* Elimina todos os brancos em excesso no final de uma string. */
    
    int i = strlen(s) - 1;     //Último elemento da string
    while(i >= 0 && s[i] == branco)
       i--;
    s[i+1] = '\0';
    
} /* TiraBrancosDoFinal */


int TamMaxRegistro(Header* h, int campos){
/* Calcula o tamanho máximo do registro de um arquivo de dados configurado por 
   head, com n campos */
   int i, tam = 0;
   for(i=0;i<campos;i++) tam += h[i].tamanho;
   tam += campos;                            //para caber os delimitadores
   return tam;
   
} /* TamMaxRegistro */


Boolean SoZeros(char *string) {
/* Função auxiliar: Retorna "true" se a string só contém zeros ou
   "false" caso contrário. */
   
   char *s1, s2[10] = "123456789";
   s1 = strpbrk(string, s2);
   
   if(s1 == NULL)
      return true;
   
   return false;
    
} /* SoZeros */


Boolean ValidaDados(Record reg, Header *h, int numcampos) {
/* Retorna 'true' se os dados de um registro forem válidos ou 'false'
   caso contrário */
        
     int i;
     
     /* Verifica se não falta nenhum dado obrigatorio */
     for(i = 0; i < numcampos; i++)
        if(reg[i][0] == '\0' && h[i].obrig == true) {
            printf("%s\n\n", ERRO_DADOS_OBRIG);
            return false;
        }
     
     /* Verifica RA */
     if(!VerificaStringNumericaNaoNula(reg[0], 6)) {
        printf("%s: %s\n\n", ERRO_RA, reg[0]);
        return false;
     }
     
     /* Verifica telefone contato */
     if(!VerificaStringNumericaNaoNula(reg[3], 8)) {
        printf("%s: %s\n\n", ERRO_TEL, reg[3]);
        return false;
     }
     
     /* Verifica telefone alternativo */
     if(reg[4][0] != '\0' && !VerificaStringNumericaNaoNula(reg[4], 8)) {
        printf("%s: %s\n\n", ERRO_TEL, reg[4]);
        return false;
     }
     
     /* Verifica sexo */
     if(reg[5][0] != '\0' && reg[5][0] != 'M' && reg[5][0] != 'F') {
        printf("%s: %s\n\n", ERRO_SEXO, reg[5]);
        return false;
     }
     
     /* Verifica curso */
     if(!VerificaStringNumericaNaoNula(reg[6], 2)) {
        printf("%s: %s\n\n", ERRO_CURSO, reg[6]);
        return false;
     }
     
     return true;
     
} /* ValidaDados */

/*************************** Funções Auxiliares (não incluídas em database.h) */


Boolean VerificaStringNumericaNaoNula(char *string, int nDig){
/* Verifica se string só contém números, se os números não são todos 0 e
   se string tem nDig. */

    int i, tam = strlen(string);
    
    if(tam != nDig || SoZeros(string) || !VerificaDigitos(string))
       return false;
    
    return true;
    
} /* VerificaStringNumericaNaoNula */


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
   
    fscanf(arqConfig, "%s", lingua);  //leitura do br no arquivo                        
    fseek(arqConfig, 2, SEEK_CUR);
    *sep = fgetc(arqConfig);   //leitura do separador
    
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
   para a próxima leitura. Retorna NULL se houver algum erro no registro. */
   
   
   int i;
   Record registro;
   
   registro = malloc(sizeof(char*)*n);
   
   for(i=0;i<n;i++){
                    
      registro[i] = (char*)malloc(sizeof(char)*(h[i].tamanho+1));
      strncpy(registro[i], &linha[h[i].inicio-1], h[i].tamanho);
      registro[i][h[i].tamanho] = '\0';              
      TiraBrancosDoFinal(registro[i]);
   
   }
   
   if(!ValidaDados(registro, h, n)) {
       LiberaRegistro(registro, n);
       return NULL;
   }
       
   return registro;
   
}/* LeRegistroFixo */
   

FILE* ConverteFixoDelim(char* nome, FILE* arqFix, char sep, Header* head, int numcampos){
/* Converte um arquivo de campos de tamanho fixo em outro de campos de tamanho variavel.
   Despreza registros invalidos */      

   FILE* dlm;
   int i, numRegs = 0, numBytesFix, numBytesDlm, tamanhofix, regInv = 0;
   char *linha;
   char fimReg;
   Record registro;
   
   dlm = Fopen(nome, "w");
   
   fimReg = head[numcampos-1].msg[0];

   tamanhofix = + head[numcampos-1].inicio+head[numcampos-1].tamanho;
   
   linha = malloc(sizeof(char)*(tamanhofix));
                  
   /* Escreve os dados no novo arquivo */
   while(!feof(arqFix)) {
                                       
       numRegs++;
       
       fread(linha, tamanhofix, 1, arqFix);
       
       registro = LeRegistroFixo(linha, numcampos, head);
       
       if(registro != NULL) {
       
           for(i=0; i<numcampos-1; i++)
               fprintf(dlm, "%s%c", registro[i], sep);     
       
           fprintf(dlm, "%s\n", registro[i]);
   
           LiberaRegistro(registro, numcampos);
        }
        else
            regInv++;
   }
   
   numBytesFix = ftell (arqFix); /* Conta os bytes do arquivo original */
   numBytesDlm = ftell (dlm);  /* Conta os bytes do arquivo convertido */
   
   fprintf(stdout, "\n%s: %d\n", NUM_REGS, numRegs);
   fprintf(stdout, "%d %s\n", regInv, NUM_REG_INV);
   fprintf(stdout, "%s: %d\n", NUM_BYTES_FIX, numBytesFix);
   fprintf(stdout, "%s: %d\n", NUM_BYTES_DLM, numBytesDlm);
   
   free(linha);                 
   fclose(dlm);
   return dlm;
}   
   
   
      
void ImprimeArquivoFixo(FILE* arqFix, int numcampos, Header* head){
/* Imprime os dados de um arquivo de campos de tamanho fixo. Nao imprime
   registros invalidos */

     int i, tamanhofix, regInv = 0;
     char *linha;
     Record registro;
     printf("\n");
                  
     tamanhofix = + head[numcampos-1].inicio+head[numcampos-1].tamanho;
     
     linha = malloc(sizeof(char)*(tamanhofix));
     
     while(!feof(arqFix)) {
                                       
        fread(linha, tamanhofix, 1, arqFix);  /* pega uma linha do arquivo */
                      
        registro = LeRegistroFixo(linha, numcampos, head); /*transforma em um registro */
                      
        if(registro != NULL) {
            ImprimeRegistro(registro, head, numcampos); /* imprime */
            LiberaRegistro(registro, numcampos);
        }
        else
            regInv++;
     }
     
     printf("%d %s\n\n", regInv, NUM_REG_INV);
                   
     free(linha);
                   
     fseek(arqFix, 0, SEEK_SET);     /* Volta para o inicio do arquivo */ 
      
} /* ImprimeArquivoFixo */


void ImprimeArquivoDelim(FILE* arqDel, int numcampos, Header* head, char c){
/* Imprime os dados de um arquivo de campos de tamanho variavel */

     int i, j;
     char aux[300];
     char g, f;
     printf("\n");
     
     rewind(arqDel);
     f=fgetc(arqDel);                  
                
     while(!feof(arqDel)) {
                          
                                       

        /* imprime o nome do campo e seu respectivo valor */
        for(i=0; i<numcampos-1; i++) {
           
           //primeiro caracter da palavra
           if(i==0)
              g=f;
           else   
              g=fgetc(arqDel);
              
           j=0;
          
           //forma a palavra
           while (g!=c){
                aux[j]=g;
                j++; 
                g=fgetc(arqDel);
                 
           } 
           
           aux[j]='\0';
           
           /* imprime o nome do campo e seu respectivo valor */      
           fprintf(stdout, "%s: ", head[i].nome);
           fprintf(stdout, "%s \n", aux);
        }

        g=fgetc(arqDel); /* Avanca o # */ 
        g=fgetc(arqDel);
        f=fgetc(arqDel); /* Verifica se o arquivo cheogou ao final */ 


       
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


Record PesquisaRegistro(char* arq, char* key, char sep, int max, int n){
/* Procura pela chave primaria 'key' no arquivo de formato variavel
   separado por sep, com n campos e linha de tamanho máximo max.
   Se encontrar, coloca em 'registro' as informações e retorna true, caso 
   contrário retorna false */

   FILE* f = Fopen(arq, "rt");
   char* linha = malloc(sizeof(char)*max);
   int i = 0;
   Record rec = malloc(sizeof(char*)*n);

   while(!feof(f)) {
                    fgets(linha, max, f);
                    rec[0] = strtok(linha,&sep);

                    if (strcmp(rec[0],key) == 0) {     //achou a chave

                       for(i=0;i<n-1;i++){
                             //se próximo campo é vazio             
                             if(*(rec[i]+strlen(rec[i])+1)==sep){
                                     *(rec[i]+strlen(rec[i])+1) = '\0';
                                     i++;
                                     rec[i] = (rec[i-1]+strlen(rec[i-1])+1);
                             }

                             rec[i+1] = strtok (rec[i]+strlen(rec[i])+1, &sep);

                       }
                    return rec;
    
                    }
   }
   return NULL;  

} /* PesquisaRegistro */


void ImprimeRegistro(Record registro, Header *head, int numcampos){
/* Imprime todos os campos de um registro */
   int i;
   
   for(i=0; i<numcampos-1; i++) {
       fprintf(stdout, "%s: ", head[i].nome);
       fprintf(stdout, "%s \n", registro[i]);
   }
   printf("\n");
   
} /* ImprimeRegistro */


void ExtraiChaves(FILE *arqDlm, char separador, Header* head){
/* Cria um arquivo 'chaves.ind' com as chaves primárias do arquivo de
   dados arqDlm, junto com os respectivos endereços dos registros no arquivo */
   
   separador = '#';
   FILE* ind;
   int i, tamra;
   char g, f;
   char *ra;
   long pos;
   Boolean pri = false;
   
     ind = Fopen("chaves.ind", "w");
                  
     tamra = head[0].tamanho;
     ra = malloc(sizeof(char)*(tamra-1));
     rewind(arqDlm);

     f=fgetc(arqDlm);
     fread(ra, tamra-1, 1, arqDlm);     
         
                
     while(!feof(arqDlm)) {

       

     if(g==separador){

        g=fgetc(arqDlm);
        f=fgetc(arqDlm);
        if(!feof(arqDlm)){     
             pos=ftell(arqDlm);  
             fread(ra, tamra-1, 1, arqDlm);   
             fprintf(ind, "%c%s %ld\n",f, ra, pos);
        }
                          
     }else if(pri == false){
        pri=true;
        fprintf(ind, "%c%s 0\n",f, ra);       
     }
              
              
              
        g=fgetc(arqDlm);
                    
     }
           
    fclose(ind);
    free(ra);

}/* ExtraiChaves */


void ClassificaChavePrimaria(){
/* Cria um arquivo 'chavesClas.ind' a partir do arquivo 'chaves.ind' já criado,
   classificando-o */
   
   system("sort chaves.ind /o chavesClas.ind");

} /* ClassificaChavePrimaria */


void ImprimeChaves(FILE *arq){
/* Imprime as chaves primarias e o endereço */

   char *leArq[16];
   
   while(!feof(arq)){ 
      fscanf(arq, "%s", leArq);
      if(feof(arq))
         break;
      printf("\n%s: %s\n", CHAVE_PRIM, leArq);
      fscanf(arq, "%s", leArq);
      printf("%s: %s\n", ENDERECO, leArq);
   }
   printf("\n");
   
} /* ImprimeChaves */
