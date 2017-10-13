#include<stdio.h>
#include<stdlib.h>
#define DICTIONARYSIZE 10000
#define WORDSIZE 250
#define REMOVED  -2
#define EMPTY -1

typedef struct DICTIONARY{
  unsigned long hashNumber;
  char *word;

} DICTIONARY;

unsigned long djb2(unsigned char *str);

int main(){

  DICTIONARY dictionary[DICTIONARYSIZE];
  char word[WORDSIZE];
  char operation;
  unsigned long hashNumber;

  while(scanf("%c", operation) && operation != 'f'){

    scanf("%s", word);
    hashNumber = djb2(word);

    if(operation == 'i'){


    }else if(operation  == 'b'){


    }else if(operation == 'r'){



    }

  }



  return 0;
}


//TESTAR COM INT.
unsigned long djb2(unsigned char *str){
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c

  return hash;
}

int hashingFunction(){



}


int h1(){



}

int h2(){




}
