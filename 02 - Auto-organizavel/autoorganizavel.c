//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
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
  // Leitura da entrada, N e o numero de requisições (RElements).
  // costMTF, costT e costC armazenarão os custos dos métodos
  // Move-to-front, transpose e count respectivamente.
  int   N, RElements, costMTF = 0, costT = 0, costC = 0 , j;
  scanf("%d %d", &N, &RElements);

  int *Requisitions = malloc(RElements*sizeof(int));
// Ponteiro que inicializa a lista(node).
  NODE *node = NULL;

// Leitura das requisições.
  for(j = 0; j < RElements; j++)
    scanf("%d", &Requisitions[j]);

// refreshList coloca os elementos padrão na lista caso a lista não haja elementos
// e caso haja libera a lista antiga e recria com elementos padrão.
  refreshTheList(&node, N);

// Calcula o custo da função MTF(esta retorna  um int, que é o custo do método Move-to-front).
    for(j = 0; j < RElements; j++){
      costMTF = costMTF + MTF(&node ,Requisitions[j]);
   }

  refreshTheList(&node, N);
// Calcula o custo da função transpose(esta retorna  um int).
    for(j = 0; j < RElements; j++){
      costT = costT + transpose(&node ,Requisitions[j]);
	}

  refreshTheList(&node, N);
// Calcula o custo da função count(esta retorna  um int).
    for(j = 0; j < RElements; j++){
      costC = costC + count(&node ,Requisitions[j]);
    }
    printf("%d %d %d\n", costMTF, costT, costC);
// Libera a lista.
      freeTheList(&node);

  return 0;
}

//addElement adiciona elementos a uma lista (optei por adicionar no final da lista)
void addElement(NODE** adress, int elementToAdd){
  NODE *newElement = malloc(sizeof(NODE));
  NODE *aux=*adress;
// newElement é um auxiliar que recebe os valores do novo elemento
// e é integrado na lista depois.
  newElement->id = elementToAdd;
  newElement->counter = 0;
  newElement->next = NULL;

// Verifica se a lista não tem elementos.
// caso não haja adiciona o novo elemento e coloca a cabeça como
// esse novo elemento.

  if(*adress == NULL){
    *adress = newElement;
    return;
  }
// Percorre a lista para encontrar o ultimo elemento
    while(aux->next != NULL)
      aux = aux->next;

// Neste ponto aux apontará para ultimo elemento
// bastando assim atribuir o novo elemento ao próximo de aux.
  aux->next = newElement;
  return;

}
// MTF procura elementos e rearranja de acordo com o método move-to-front.
// retorna o custo para procurar.

int MTF(NODE** adress, int elementToSearch){
// inicialização de um auxiliar(aux) que percorrerá a lista para encontrar o elemento.
// beforeTheLast apontará para um elemento anterior da lista.
  NODE *aux = *adress, *beforeTheLast = NULL;
  int counter = 1;

  if(aux->id == elementToSearch && aux == *adress){
    return counter;
  }

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
  NODE *actual = *adress;
  NODE *beforeActual = NULL;

  while(actual != NULL){
    if(actual->next == NULL){
      free(actual);
      *adress = NULL;
      actual = NULL;
      break;
    }else{
      beforeActual = actual;
			actual = actual->next;
      free(beforeActual);
      beforeActual = NULL;
    }

  }


}

void refreshTheList(NODE **adress, int superiorLimit){
	int j = 0;
  if(*adress == NULL){

    for(j = 0; j < superiorLimit; j++)
      addElement(adress, j+1);
    return;
  }else{
    freeTheList(adress);
    for(j = 0; j < superiorLimit; j++){
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
  NODE *aux = *adress, *beforeTarget = *adress, *positioner = *adress;
  int costCounter = 1;

  if(aux->id == elementToSearch && aux == *adress){
    aux->counter++;
    return costCounter;
  }

  while(aux->id != elementToSearch && aux->next != NULL){
    beforeTarget=aux;
    aux=aux->next;
    costCounter++;
  }

  if(aux->id != elementToSearch && aux->next == NULL)
    return costCounter;

  beforeTarget->next = aux->next;
  (aux->counter)++;

  if(aux->counter >= positioner->counter){
    aux->next = positioner;
    *adress = aux;
    return costCounter;
  }

  while(positioner->next->counter > aux->counter && positioner->next != NULL)
    positioner = positioner->next;

  aux->next = positioner->next;
  positioner->next = aux;
  return costCounter;


}
