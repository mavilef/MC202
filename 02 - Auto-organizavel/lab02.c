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

  int   N, RElements, costMTF = 0, costT = 0, costC = 0;
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
    printf("costT: %d\n", costT);
    refreshTheList(&node, N);


    for(i = node; i != NULL; i = i->next)
      printf("%d ", i->id);
            printf("\n");




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

  NODE *aux = *adress, *beforeTarget = *adress, *beforeTarget2 = *adress;
  int counter = 1;

  while(aux->id != elementToSearch && aux->next != NULL){
    aux = aux->next;
    if(beforeTarget->next != aux)
      beforeTarget = beforeTarget->next;
    if(beforeTarget2->next != beforeTarget && beforeTarget2->next !=aux)
      beforeTarget2 = beforeTarget2->next;
    counter++;
  }

  if(aux == *adress){
    return counter;
  }else if(beforeTarget == *adress && beforeTarget2 == *adress && aux==(*adress)->next){
    beforeTarget->next = aux->next;
    aux->next = beforeTarget;
    *adress = aux;
  }else if (beforeTarget2 == *adress && beforeTarget == (*adress)->next && aux==beforeTarget->next){
    beforeTarget->next = aux->next;
    beforeTarget2->next = aux;
    aux->next = beforeTarget;
    *adress = beforeTarget2;

  }else{
    beforeTarget->next = aux->next;
    beforeTarget2->next = aux;
    aux->next = beforeTarget;
  }

  return counter;

}

int count(NODE** adress, int elementToSearch){
  return 0;




}
