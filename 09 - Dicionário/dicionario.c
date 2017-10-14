#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DICTIONARYSIZE 12037
#define WORDSIZE 250
#define REMOVED  -2
#define EMPTY -1
#define USED -3

typedef struct DICTIONARY{
  unsigned short int chainIndex;
  short int state;
  unsigned long hashKey;
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
  int chainIndex = 0;

  if(initializeDictionary(dictionary))
    printf("MEM ERROR!!\nErro ao inicializar o dicionario!!\n");

  while(scanf(" %c", &operation) && operation != 'f'){

    if(operation == 'i'){

      if(!scanf("%s", word)){
        printf("Erro na leitura de word!!\n");
        return 1;
      }
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

unsigned long djb2(unsigned char *str){
  unsigned long hash = 6703;
  int c;

  while ((c = *str++))
    hash = ((hash << 7) + hash) + c;

  return hash;
}

int hashingFunction(unsigned long key, int rehashIndex){
    return (h1(key) + rehashIndex*h2(key)) % DICTIONARYSIZE;
}

int h1(unsigned long key){
  return key % DICTIONARYSIZE;
}

int h2(unsigned long key){
  return (key + 389) % DICTIONARYSIZE - 2;
}

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

//retorna 0 se foi inserido com sucesso, 1 se a lista está cheia e -1 se a chave já estava na tabela.
int insertKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key, unsigned short chainIndex){

  int rehashIndex = 0, CandidateIndex, firstRemoved = REMOVED;
  CandidateIndex = hashingFunction(key, 0);

  while(rehashIndex != DICTIONARYSIZE - 1){

    if(firstRemoved < 0 && dictionary[CandidateIndex].state == REMOVED)
      firstRemoved = CandidateIndex;

    if(dictionary[CandidateIndex].hashKey == key && dictionary[CandidateIndex].state == USED){
      return -1;
    }else if(dictionary[CandidateIndex].state == EMPTY){
      memcpy(dictionary[CandidateIndex].word, word, strlen((char*)word)+1);
      dictionary[CandidateIndex].state = USED;
      dictionary[CandidateIndex].hashKey = key;
      dictionary[CandidateIndex].chainIndex = chainIndex;
      return 0;
    }else{
        rehashIndex++;
        CandidateIndex = hashingFunction(key,rehashIndex);
    }
  }

  if(firstRemoved != REMOVED){
    memcpy(dictionary[firstRemoved].word, word, strlen((char*)word)+1);
    dictionary[firstRemoved].state = USED;
    dictionary[firstRemoved].hashKey = key;
    dictionary[firstRemoved].chainIndex = chainIndex;
    return 0;

  }


    return 1;
}

//retorna o indice da cadeia se foi encontrado, e -1 caso contrario.
int searchKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key){

  int rehashIndex = 0, CandidateIndex;
  CandidateIndex = hashingFunction(key, 0);

  while(rehashIndex != DICTIONARYSIZE - 1){

    if(dictionary[CandidateIndex].state == USED){

      if(key == dictionary[CandidateIndex].hashKey){
        return dictionary[CandidateIndex].chainIndex;
      }else{
        rehashIndex++;
        CandidateIndex = hashingFunction(key, rehashIndex);
        continue;
      }

    }else if(dictionary[CandidateIndex].state == EMPTY){
      return -1;
    }else{
      rehashIndex++;
      CandidateIndex = hashingFunction(key, rehashIndex);
      continue;
    }
  }
  return -1;
}

int removeKeyOnDictionary(DICTIONARY *dictionary, unsigned char *word, unsigned long key){

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
