#include<stdio.h>
#include<stdlib.h>

struct NODE{

  int id;
  struct NODE* next;
  int counter;

};

typedef struct NODE NODE;

void addElement(NODE** adress, int elementToAdd);

int main(){

  int   N, RElements;
  int* Requisitions = malloc(RElements * sizeof(int));
  NODE *node = NULL;
  NODE *i = NULL;

  scanf("%d %d", &N, &RElements);

  for(int i = 0; i < RElements; i++)
    scanf("%d", &Requisitions[i]);

    for(int i = 0; i < N; i++){
      addElement(&node, i+1);
    }

      for(i = node; i != NULL; i = i->next)
        printf("%d ", i->id);
      printf("\n");
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
//vou ter que criar um ponteiro que armazena o elemento procurado e o proximo
  NODE *aux = *adress;
  int counter = 1;

  while(aux->id != elementToSearch){
      aux = aux->next
      counter++;
  }







}
