//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DICTIONARYSIZE 12037
#define WORDSIZE 250
#define REMOVED  -2
#define EMPTY -1
#define USED -3

typedef struct DICTIONARY{
  //indice da cadeia do elemento.
  unsigned short int chainIndex;
  //Estado -1 nó vazio, -2 removido e -3 Usado
  short int state;
  //Chave gerada apartir da conversão da string pela função djb2.
  unsigned long hashKey;
  //a string.
  unsigned char *word;
} DICTIONARY;

unsigned long djb2(unsigned char *str);
int initializeDictionary(DICTIONARY *dictionary);
int insertKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key, unsigned short chainIndex);
int searchKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key);
int removeKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key);
int hashingFunction(unsigned long key, int rehashIndex);
int h1(unsigned long key);
int h2(unsigned long key);

int main(){

  DICTIONARY dictionary[DICTIONARYSIZE];
  unsigned char word[WORDSIZE];
  char operation;
  unsigned long hashNumber;
  //indice da cadeia tal variavel é somada sequencialmente,
  //conforme enunciado
  int chainIndex = 0;

  if(initializeDictionary(dictionary))
    printf("MEM ERROR!!\nErro ao inicializar o dicionario!!\n");

//leitura das operações e chamada das funções.
  while(scanf(" %c", &operation) && operation != 'f'){

    if(operation == 'i'){

      if(!scanf("%s", word)){
        printf("Erro na leitura de word!!\n");
        return 1;
      }
      //converção da string lida.
      hashNumber = djb2(word);

      int check;
      check = insertKeyOnDictionary(dictionary, word, hashNumber, chainIndex);

      if(check == 0){
        chainIndex++;
      }else if(check == 1){
        printf("Tabela de hashing cheia!!\n");
        continue;
      }

    }else if(operation  == 'b'){

      if(!scanf("%s", word)){
        printf("Erro na leitura de word!!\n");
        return 1;
      }
      hashNumber = djb2(word);

      int check;
      check = searchKeyOnDictionary(dictionary, word, hashNumber);
      if(check != -1){
        printf("encontrado %d\n", check);
      }else{
        printf("nao encontrado\n");
      }

    }else if(operation == 'r'){

      if(!scanf("%s", word)){
        printf("Erro na leitura de word!!\n");
        return 1;
      }
      hashNumber = djb2(word);
      removeKeyOnDictionary(dictionary, word, hashNumber);

    //função de debug utilizada para inprimir na tela os elementos do dicionario.
    }else if(operation == 's'){

      int i;
      for(i = 0; i < DICTIONARYSIZE; i++){
        printf("state: %hi ", dictionary[i].state);
        if(dictionary[i].state == USED)
          printf("key: %lu word: %s chainIndex: %d",dictionary[i].hashKey, dictionary[i].word, dictionary[i].chainIndex);
        printf("\n");
      }
    }else{
      printf("Operação inexistente\n");
      continue;
    }

  }

  return 0;
}

//Método para conversão da string em uma chave(que é um unsigned long int).
unsigned long djb2(unsigned char *str){
  unsigned long hash = 6703;
  int c;

  while ((c = *str++))
    hash = ((hash << 7) + hash) + c;

  return hash;
}

//Tratamento de colisão por hashing duplo.
int hashingFunction(unsigned long key, int rehashIndex){
    return (h1(key) + rehashIndex*h2(key)) % DICTIONARYSIZE;
}

//h1 é a função de hashing em si(foi usado o método da multiplicação)
int h1(unsigned long key){
  return key % DICTIONARYSIZE;
}

//h2 é a função chamada para o tratamento de colisão.
//Gera um numero sempre Coprimo ao tamanho da tabela.
//(uma vez que o tamanho da tabela é um primo e
//h2 sempre gera um numero menor que o tamanho da tabela)
int h2(unsigned long key){
  return (key + 389) % DICTIONARYSIZE - 2;
}

//Inicializa o dicionario com todos os nós vazios.
//(com -1 ,conforme o define).
//retorna 0 se a inicialização foi um sucesso e 1 se houve problemas na alocação de memoria.
int initializeDictionary(DICTIONARY *dictionary){
  int i;
  for(i = 0; i < DICTIONARYSIZE; i++){
    dictionary[i].state = EMPTY;
    dictionary[i].word = malloc(WORDSIZE*sizeof(unsigned char));
    if(dictionary[i].word == NULL)
      return 1;
  }
  return 0;
}

//Insere uma chave no dicionario utilizando as funções de hashing.
//Primeiro é procurado um espaço na tabela com estado vazio,
//se, não houver espaços vazios é utilizado espaços que foram removidos
//(ou seja, espaços onde haviam elementos mas foram removidos)
//retorna 0 se foi inserido com sucesso, 1 se a lista está cheia e -1 se a chave já estava na tabela.
int insertKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key, unsigned short chainIndex){

  int rehashIndex = 0, CandidateIndex, firstRemoved = REMOVED;
  CandidateIndex = hashingFunction(key, 0);

  while(rehashIndex != DICTIONARYSIZE - 1){
    //grava o primeiro espaço removido, para utilizar
    //posteriormente, caso não encontremos espaços vazio.
    if(firstRemoved < 0 && dictionary[CandidateIndex].state == REMOVED)
      firstRemoved = CandidateIndex;
    //caso a chave ja esteja no dicionario.
    if(dictionary[CandidateIndex].hashKey == key && dictionary[CandidateIndex].state == USED){
      return -1;
    //caso encontremos um espaço vazio.
    }else if(dictionary[CandidateIndex].state == EMPTY){
      memcpy(dictionary[CandidateIndex].word, word, strlen((char*)word)+1);
      dictionary[CandidateIndex].state = USED;
      dictionary[CandidateIndex].hashKey = key;
      dictionary[CandidateIndex].chainIndex = chainIndex;
      return 0;
    //rehashing para checar o proximo elemento, gerado pelo hashing.
    }else{
        rehashIndex++;
        CandidateIndex = hashingFunction(key,rehashIndex);
    }
  }

  //Caso não haja espaços vazios disponíveis, gravamos no
  //primeiro espaço com estado removido.
  //Observe que esse trecho só será executado, após o termino,
  //do ultimo loop, ou seja, após checarmos toda tabela de hashing
  //e não encontradmos espaços vazios.
  if(firstRemoved != REMOVED){
    //copia de dados(usado no lugar de strcpy, pois este necessita de,
    //variaveis char, e estamos usando unsigned char.)
    memcpy(dictionary[firstRemoved].word, word, strlen((char*)word)+1);

    dictionary[firstRemoved].state = USED;
    dictionary[firstRemoved].hashKey = key;
    dictionary[firstRemoved].chainIndex = chainIndex;
    return 0;

  }


    return 1;
}

//Procura uma chave na tabela de hashing.
//retorna o indice da cadeia se foi encontrado, e -1 caso contrario.
int searchKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key){

  int rehashIndex = 0, CandidateIndex;
  CandidateIndex = hashingFunction(key, 0);

  while(rehashIndex != DICTIONARYSIZE - 1){
    //caso o indice na tabela de hashing esteja ocupada, ainda precisamos
    //conferir se é a chave procurada.
    if(dictionary[CandidateIndex].state == USED){

      //caso seja a chave procurada.
      if(key == dictionary[CandidateIndex].hashKey){
        return dictionary[CandidateIndex].chainIndex;
      //do contrario, continuamos o processo de hashing.
      }else{
        rehashIndex++;
        CandidateIndex = hashingFunction(key, rehashIndex);
        continue;
      }

    //caso o indice gerado pela função de hashing esteja vazia,
    //podemos parar a busca aqui, pois , procuramos a chave
    //pela mesma função de hashing da inserção, assim é
    //se chegamos em um estado vazio, a função de inserção
    //também não, logo a chave nunca foi adicionada.
    }else if(dictionary[CandidateIndex].state == EMPTY){
      return -1;
    //caso seja uma chave removida,
    //não podemos parar a busca aqui,
    //pois uma chave que possui o mesmo hashkey de outra
    //pode ter sido removida, porém podem existir as chaves,
    //nos indices ggerados por rehash.
    }else{
      rehashIndex++;
      CandidateIndex = hashingFunction(key, rehashIndex);
      continue;
    }
  }
  return -1;
}

//Remoção de uma chave.
//Basicamente marcamos a chave como removida.
//retorna 0 se tiver feita a remoção e 1 cas contrario.
int removeKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key){
    //o algoritmo é mesmo da busca, no entanto,
    //marcamos a posição do elemento procurado
    //como Removido(REMOVED), ao inves retornar o indice da cadeia do elemento.
    int rehashIndex = 0, CandidateIndex;
    CandidateIndex = hashingFunction(key, 0);

    while(rehashIndex != DICTIONARYSIZE -1){

      if(dictionary[CandidateIndex].state == USED){

        if(key == dictionary[CandidateIndex].hashKey){
          dictionary[CandidateIndex].state = REMOVED;
          return 0;
        }else{
          rehashIndex++;
          CandidateIndex = hashingFunction(key, rehashIndex);
          continue;
        }

      }else if(dictionary[CandidateIndex].state == EMPTY){
        return 1;
      }else{
        rehashIndex++;
        CandidateIndex = hashingFunction(key, rehashIndex);
        continue;
      }
    }
    return 1;
}
