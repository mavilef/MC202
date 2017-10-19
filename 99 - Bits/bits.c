#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define BYTESIZE 8.0


int createBitVector(char **bitPointer, int size);
void addElement(char *bitVector, int elementToSet);

int main(){
  char *bitVector = NULL;
  char operation[12];

  while(scanf("%s",operation) && strcmp(operation, "exit")){

    if(!strcmp(operation, "create")){
      int n;
      if(!scanf("%d", &n)){
        printf("Erro na leitura do input!!\n");
        break;
      }

      if(createBitVector(&bitVector, n)){
        printf("Erro na criação do Vetor!!\n");
        break;
      }

    }else if(!strcmp(operation, "add")){
      int n;

      if(!scanf("%d", &n)){
        printf("Erro na leitura do input!!\n");
        break;
      }
      addElement(bitVector, n);

    }else if(!strcmp(operation, "remove")){


    }else if(!strcmp(operation, "in")){


    }else if(!strcmp(operation, "rank")){


    }else if(!strcmp(operation, "select")){


    }else if(!strcmp(operation, "print")){


    }else{
      printf("Operação inexistente!!\n");
      continue;
    }
  }

  if(bitVector != NULL)
    free(bitVector);

  return 0;

}

int createBitVector(char **bitPointer, int size){

  if(*bitPointer != NULL)
    free(*bitPointer);


  int correctSize = (int)ceil(size/BYTESIZE);
  char *new = calloc(correctSize,sizeof(char));
  *bitPointer = new;

  if(!new)
    return 1;
  else
    return 0;
}

//Terminar!!!
void addElement(char *bitVector, int elementToSet){
  int macroPositioner, microPositioner;
  macroPositioner = (int)elementToSet/BYTESIZE;
  microPositioner = (elementToSet % (int)BYTESIZE) - 1;



}
