/******************************************************************************/
/* ESTE ARQUIVO CONTEM SOMENTE O ENUNCIADO DA TAREFA                          */
/* AT… QUE A GENTE APRENDA A DOCUMENTAR DE FORMA MAIS APROPRIADA...           */
/******************************************************************************/


/*Lab02 - MC326
Unicamp 1o. semestre 2010
Prof. Sindo

- Manipulacao de arquivos com registros de tamanho fixo, campos de tamanho fixo e campos de tamanho variavel.
- Construcao de uma biblioteca de funcoes que permitam realizar as operacoes de pesquisa, alteracao, 
  remocao e insercao de registros e campos em um arquivo.
- Construcao de funcoes para criacao e pesquisa de indices;

3 Estudo e Pesquisa
Estude as seguintes funcoes
fread();
fwrite();
feof();


4 Problema
Suponha que a Unicamp mantem um arquivo com algumas informacoes dos seus alunos em arquivos de dados
de tamanho fixo, conforme ilustrado na tabela TAB-1. Para cada registro sao fornecidos:
- nome do campo
- tipo do campo (A- alfabetico, X-alfanumerico, N . numerico inteiro, D- numerico decimal, M .moeda)
- posicao inicial no registro
- posicao final no registro
- obrigatoriedade da presenca da informacao (S . obrigatorio, N . opcional)

Outras caracteristicas:
- Arquivo do tipo texto cujos campos sao de tamanho fixo. O final do arquivo e especificado pelo nome do
  campo especial Å"FimRegistro", normalmente colocado no final da tabela de descricao do registro do
  arquivo.
- Campos Alfanumericos com tamanho inferior ao tamanho reservado, sao preenchidos com Å"brancos" a
  direita;

TAB . 1 - Descricao do arquivo de entrada
Nome do Campo   Tipo     Posicao Inicial      Posicao Final         Obrigatorio?    Mensagem para Usuario
RA              N        1                    6                     S               RA deve ter 6 digitos
NOME            X        8                    31                    S               Nome deve ser fornecido
CIDADE          X        32                   46                    N
TEL Contato     X        47                   54                    S               Obrigatorio
TEL Alternativo X        56                   63                    N
Sexo            A        65                   65                    N               F ou M
Curso           N        67                   68                    S               Devem ser fornecidos 2 digitos
FimRegistro     X        69                   69                    S               #


5 Exemplo de um arquivo de entrada

Na Tabela TAB-2 abaixo segue um exemplo de arquivo que satisfaz a descricao constante de TAB . 1. As 3
primeiras linhas nao fazem parte do aquivo e foram adicionadas apenas como um cabecalho apenas para
identificar as posicoes (colunas) dentro do arquivo.

TAB . 2 . Exemplo de arquivo de entrada
                  1                   2                   3                   4                   5                   6
1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
0 9 2 3 7 3   M A U R I C I O   J O S E   Z A M B O N         I T A P E V A                 3 7 5 6 4 3 2 8   9 9 1 2 1 8 7 5   M   3 4 #
0 9 4 9 1 0   L U C A S   D E   M O R A E S   B E R T O       P I R A C I C A B A           2 1 2 2 1 1 2 2                     M   0 3 #
0 8 2 0 7 0   M A G D A   S I L V A                           A R A P O T I                 4 3 5 4 2 6 4 5                     F   4 2 #


= Funcionalidades do programa

- programa devera ser orientado por Å"cardapios" e deve ter, no minimo, as seguintes opcoes:

  1.1 Opcao 1: Conversao do arquivo de formato fixo para formato variavel
  Nesta opcao baseado no arquivo de configuracao do arquivo de dados, deve ser criado o arquivo no formato
  variavel de acordo com o seguinte formato
           - O registro de saida deve conter os seis digitos do RA, seguido do caractere separador Å"|", 
             seguido dos caracteres do NOME (removendo, se houver, os caracteres em branco ao final dos nomes), 
             seguido do separador "|", e assim sucessivamente ate o setimo campo. Para campos nulos voce deve 
             armazenar apenas o separador "|".
           - Ao final do registro armazenar o caractere definido no campo FIMREGISTRO. No caso acima esse
             caracter e Å"#"
           - Apos o caracter "#", adicionar "pular de linha".

  Para os 2 primeiros registros teremos a seguinte saida:

  092373|MAURICIO JOSE ZAMBON|ITAPEVA|37564328|99121875|M|34#
  094910|LUCAS DE MORAES BERTO|PIRACICABA|21221122||M|03#

  Ao final da conversao informe a quantidade de registros lidos, a quantidade de bytes do arquivo original e a
  quantidade de bytes do arquivo convertido.

  1.2 Opcao 2: Listar o arquivo de dados no formato fixo
  Nesta opcao deve ser mostrada uma lista dos registros do arquivo fixo com o objetivo de facilitar a visualizacao
  dos dados. Defina um formato de saida que tenha pelo menos o nome dos campos e o valor desses campos.
  Do arquivo de configuracao, por exemplo, podera ser extraido o nome do campo para mostrar os seu valor.
  Por exemplo, poderia ser uma Lista com NomeDoCampo=Valor. Voce pode sugerir uma outra formatacao que
  considerar mais apropriada. Por exemplo, um formato HTML que poderia ser aberto por um navegador que ja
  mostraria uma pagina bem bonita!

  1.3 Opcao 3: Listar o arquivo de dados no formato variavel
  Nesta opcao deve ser mostrada uma lista dos registros do arquivo de dados variavel. A lista deve conter todas
  as informacoes da estrutura definida no item 2. Com essa lista o usuario podera acompanhar e Å"debugar" se o
  arquivo esta no formato correto. Embora as informacoes dependam da estrutura escolhida no item 2, poderao
  ser uteis as seguintes informacoes: posicao (byte) do arquivo onde inicia o registro; situacao do registro
  ("removido" ou "valido"), tamanho, em bytes, do registro; campo, tamanho do campo, conteudo do campo.

  1.4 Opcao 4: Pesquisa de um determinado registro pela chave primaria
  Nesta opcao o programa deve pedir ao usuario o valor de uma chave primaria e o programa devera fazer uma
  pesquisa no arquivo de formato variavel e mostrar:
           - Caso o registro exista, os dados do registro no mesmo formato de apresentacao da opcao 3
           - Caso o registro nao exista, mensagem Å"Registro Inexistente";

  1.5 Opcao 5: Extracao das chaves
  Nesta opcao o programa devera criar um arquivo com a extracao das chaves primarias e o endereco fisico do
  registro no arquivo de dados. Este arquivo sera utilizado para criar um arquivo de indices

  1.6 Opcao 6: Classificacao do arquivo das chaves
  Nesta opcao o programa devera criar um arquivo classificado com chaves primarias extraidas na Opcao 6.
  (Esta opcao e para ser bem simples. Utilize a funcao system para chamar o programa sort. Nao deve ser
  implementado nenhum algoritmo de classificacao).

  1.7 Opcao 7: Listar o arquivo com a extracao das chaves geradas na opcao 3.6
  Este item tem que sair de graca! Basta ter projetado a opcao 2 generica o suficiente para ativa-la passando um
  nome de arquivo diferente e uma nova configuracao...
  
  1.8 Opcao 8: Listar o arquivo com a extracao das chaves classificadas geradas no item 3.7
  Se a opcao 7 saiu de graca, esta nem conta na avaliacao!

  1.9 Opcao 9: Criar o arquivo de indices
  Nesta opcao, voce devera criar o arquivo de indices para que possa ser pesquisado utilizando a tecnica de
  pesquisa binaria. Em disco!
  Sugestao: sera que voce ja nao pode considerar que ele foi criado em alguma opcao anterior?

  1.10 Opcao 10: Pesquisa utilizando o arquivo de indices
  Nesta opcao o programa deve pedir ao usuario o valor de uma chave primaria e o programa devera fazer uma
  pesquisa no arquivo de indices utilizando pesquisa binaria em disco e deverao ser mostrados:
           - Caso o registro exista, os dados do registro devem ser mostrados no mesmo formato de apresentacao da
             opcao 3
             - Caso o registro nao exista, mensagem ÅgRegistro InexistenteÅh;

  1.11 Opcao 11: Remocao de um registro
  Nesta opcao o programa deve pedir ao usuario o valor de uma chave primaria e o programa devera fazer uma
  pesquisa no arquivo de indices utilizando pesquisa binaria em disco
Å          - Caso o registro exista, ele devera ser excluido.
           - Caso o registro nao exista, mensagem Å"Registro Inexistente"


Cada grupo deve criar dois arquivos de entrada com os dados no formato definido acima.
     - Um arquivo com 3 registros contendo todos os possiveis erros de entrada;
     - Um outro arquivo com pelo menos 20 registros.

7 Exemplos de chamada do Programa

  Lab02A <arq_entrada> <arq saida>


8 Testes
- Antes de codificar ou estruturar seu programa pense em arquivos de dados que possibilitem testar seu
  programa de uma maneira abrangente.
- Voce deve consistir os dados de entrada e fornecer mensagens de erro/aviso para orientar o usuario.
- Os registros que apresentarem algum tipo de erro devem ser descartados.

9 Prazo de entrega
Sera considerada como data de entrega a data de deposito dos fontes no Teleduc.

Modulo                 Data entrega         Valor Maximo do Laboratorio
Lab2A - ate opcao  3   12/04/2010(Segunda)  10
Lab2B - ate opcao  9   21/04/2010(Quarta)   10
Lab2C - ate opcao 12   30/04/2009(Sexta)    10

10 O que deve ser entregue?

11 Os programas e os arquivos utilizados nos testes.

Questionamento:
1. Suponha que houve alteracoes no arquivo de entrada em relacao as posicoes de inicio e fim de cada
campo. Seu programa devera ser concebido para facilitar essa alteracao.

2. Faca seu programa para que o usuario possa trocar o carater separador, por exemplo, de Åg|Åh por Åg@Åh .

3. No proximo laboratorio voce devera ler os arquivos de saida que foram gerados neste laboratorio para
efetuar operacoes de pesquisa. Organize seu programa para reutilizar o codigo.

4. As rotinas de leitura de arquivo, gravacao de arquivo devem estar definidas em bibliotecas separadas
para serem reutilizadas nos proximos programas.

5. Embora na TAB-1 existam apenas 8 campos, seu programa devera ser concebido para possibilitar que
sejam definidos arquivos com um numero maior de campos.

6. Ainda deve ser considerada a possibilidade de mudanca de idioma.
*/
