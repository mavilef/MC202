#include<stdio.h>
#include<stdlib.h>

struct NODE{

  int id;
  struct NODE* next;
  int counter;

};

typedef struct NODE NODE;

void addElement(NODE** adress, int elementToAdd);
int MTF(NODE** adress, int elementToSearch);
int transpose(NODE** adress, int elementToSearch);
int count(NODE** adress, int elementToSearch);
void freeTheList(NODE **adress);
void refreshTheList(NODE **adress, int superiorLimit);


int main(){

  int   N, RElements, costMTF = 0, costT = 0;
  int* Requisitions = malloc(RElements * sizeof(int));
  NODE *node = NULL;
  NODE *i = NULL;

  scanf("%d %d", &N, &RElements);

  for(int j = 0; j < RElements; j++)
    scanf("%d", &Requisitions[j]);

    refreshTheList(&node, N);

    for(int j = 0; j < RElements; j++){
      costMTF = costMTF + MTF(&node ,Requisitions[j]);
    }
    printf("costMTF: %d\n", costMTF);
    refreshTheList(&node, N);

    for(int j = 0; j < RElements; j++){
      costT = costT + transpose(&node ,Requisitions[j]);
    }


    for(i = node; i != NULL; i = i->next)
      printf("%d ", i->id);
            printf("\n");

    printf("costT: %d\n", costT);


      freeTheList(&node);

  return 0;
}

void addElement(NODE** adress, int elementToAdd){
  NODE *newElement = malloc(sizeof(NODE));
  NODE *aux=*adress;

  newElement->id = elementToAdd;
  newElement->counter = 0;
  newElement->next = NULL;

  if(*adress == NULL){
    *adress = newElement;
    return;
  }

    while(aux->next != NULL)
      aux = aux->next;


  aux->next = newElement;
  return;

}

int MTF(NODE** adress, int elementToSearch){

  NODE *aux = *adress, *beforeTheLast = NULL;
  int counter = 1;


  while(aux->id != elementToSearch && aux->next != NULL){
      beforeTheLast = aux;
      aux = aux->next;
      counter++;
  }

  if(aux->id == elementToSearch && beforeTheLast == NULL){
      return counter;
  }else{

    beforeTheLast->next = aux->next;
    aux->next = *adress;
    *adress = aux;

  }

  return counter;
}

void freeTheList(NODE **adress){
  NODE *actual = NULL;
  NODE *afterActual;

  for(actual  = *adress, afterActual = NULL; actual != NULL; actual = actual->next){

    if(actual->next == NULL){
      free(actual);
      *adress = NULL;
      actual = NULL;
          break;
    }else{
      afterActual = actual->next;
      free(actual);
      actual = afterActual;
      afterActual = NULL;
    }

  }


}

void refreshTheList(NODE **adress, int superiorLimit){
  if(*adress = NULL){
    return;
  }else{
    freeTheList(adress);
    for(int j = 0; j < superiorLimit; j++){
      addElement(adress, j+1);
    }
  }
}

int transpose(NODE** adress, int elementToSearch){

  NODE *aux = *adress, *beforeTheLast = *adress, *beforeTheLast2 = *adress;
  int counter = 1;

  while(aux->id != elementToSearch && aux->next != NULL){
    aux = aux->next;
    if(counter > 1)
      beforeTheLast = beforeTheLast->next;
    if(counter > 2)
      beforeTheLast2 = beforeTheLast2->next;

    counter++;
  }

  beforeTheLast->next = aux->next;
    beforeTheLast2->next = aux;
    aux->next = beforeTheLast;

  return counter;
  printf("here\n");
}

int count(NODE** adress, int elementToSearch){
  return 0;




}
