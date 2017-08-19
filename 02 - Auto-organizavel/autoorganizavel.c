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
// Retorna o custo ao procurar.

int MTF(NODE** adress, int elementToSearch){
// Inicialização de um auxiliar(aux) que percorrerá a lista para encontrar o elemento.
// beforeTheLast apontará para um elemento anterior da lista.
  NODE *aux = *adress, *beforeTheLast = NULL;
  int counter = 1;

  if(aux->id == elementToSearch && aux == *adress){
    return counter;
  }
//Percorre toda a lista até encontrar o elemento.
//mantém beforeTheLast uma posição antes do elemento.
  while(aux->id != elementToSearch && aux->next != NULL){
      beforeTheLast = aux;
      aux = aux->next;
//adiciona o custo a cada passada
      counter++;
  }

//trata o caso do elemento estar na primeira posição.
  if(aux->id == elementToSearch && beforeTheLast == NULL){
      return counter;
  }else{
//caso geral
    beforeTheLast->next = aux->next;
    aux->next = *adress;
    *adress = aux;

  }

  return counter;
}

//função que libera a lista.
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
//função que reseta a lista para os valores padrão.
//usado para aplicar outro método de busca
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


// Transpose procura elementos e rearranja de acordo com o método transpose.
// Retorna o custo ao procurar.

int transpose(NODE** adress, int elementToSearch){
	//aux é o ponteiro auxiliar que apontará para o elemento a ser procurado
	//beforeTarget apontará para a posição anterior ao aux.
	//beforeTarget2 apontará para a posição anterior a beforeTarget.	
  NODE *aux = *adress, *beforeTarget = *adress, *beforeTarget2 = *adress;
  int counter = 1;

//Percorre a lista para encontrar o elemento
//Mantendo beforeTarget e beforeTarget2 nass suas posições.
  while(aux->id != elementToSearch && aux->next != NULL){

    aux = aux->next;
	//Sincroniza o movimento de beforeTarget e beforeTarget2
	//de forma que percorra um estando com 1 poição adiantado em
	//relação ao outro. 
    if(beforeTarget->next != aux)
      beforeTarget = beforeTarget->next;
    if(beforeTarget2->next != beforeTarget && beforeTarget2->next !=aux)
      beforeTarget2 = beforeTarget2->next;
    counter++;
  }

//Tratamento de casos específicos:

//Caso o elemento procurado esteja na primeira posição da lista.
  if(aux == *adress){
    return counter;
//Caso o elemento esteja na segunda posição da lista.
  }else if(beforeTarget == *adress && beforeTarget2 == *adress && aux==(*adress)->next){
    beforeTarget->next = aux->next;
    aux->next = beforeTarget;
    *adress = aux;
//Caso o elemento esteja na terceira posição da lista.
  }else if (beforeTarget2 == *adress && beforeTarget == (*adress)->next && aux==beforeTarget->next){
    beforeTarget->next = aux->next;
    beforeTarget2->next = aux;
    aux->next = beforeTarget;
    *adress = beforeTarget2;
//Caso geral.
  }else{
    beforeTarget->next = aux->next;
    beforeTarget2->next = aux;
    aux->next = beforeTarget;
  }

  return counter;

}

// Count procura elementos e rearranja de acordo com o método count.
// Utiliza o campo counter da struct.
// Retorna o custo ao procurar.

int count(NODE** adress, int elementToSearch){
	// aux percorrerá a lista para busca do elemento, apontará para o elemento procurado.
	// beforeTarget apontará para um elemento antes da posição do elemento.
	//positioner é um ponteiro que percorrerá a lista para encontrar a posição anterior
	//de onde o elemento deve ser adicionado.

  NODE *aux = *adress, *beforeTarget = *adress, *positioner = *adress;
  int costCounter = 1;

//trata o caso do elemento estar na primeira posição.
  if(aux->id == elementToSearch && aux == *adress){
    aux->counter++;
    return costCounter;
  }
//Percorre a lista e posiciona aux no elemento e beforeTarget na
//posição anterior.
  while(aux->id != elementToSearch && aux->next != NULL){
    beforeTarget=aux;
    aux=aux->next;
    costCounter++;
  }
//caso não encontre o elemento.
  if(aux->id != elementToSearch && aux->next == NULL)
    return costCounter;

//retira o elemento da lista, para posterior reposicionamento.
  beforeTarget->next = aux->next;
  (aux->counter)++;

//trata o caso do elemento ter de ser adicionado na primeira posição.
  if(aux->counter >= positioner->counter){
    aux->next = positioner;
    *adress = aux;
    return costCounter;
  }

//Percorre a lista a fim de encontrar a posição onde o elemento deve ser adicionado.
//ou seja, na posição onde o próximo elemento possui counter maior ou igual 
//ao elemento a ser adicionado.
//positioner então termina em uma posição antes da posição onde deve ser adicionado o 
//novo elemento.
  while(positioner->next->counter > aux->counter && positioner->next != NULL)
    positioner = positioner->next;

//insere o elemento na posição encontrada. 
  aux->next = positioner->next;
  positioner->next = aux;
  return costCounter;


}
