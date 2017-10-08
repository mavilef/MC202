//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define EMPTY INT_MIN

typedef struct elementStructure{
  int key;
  int cost;
} elementStructure;

typedef struct HEAP{
  elementStructure *array;
  int capacity;
  int size;
  int type;// 0 - HEAP de maximo, 1 - HEAP de mínimo
} HEAP;

int createEnviroment(HEAP **heap, int **positionVector, int size);
int insertElement(HEAP *Helements , int *positionVector ,int element, int cost);
void minHeapify(HEAP *Helements, int *positionVector, int location);
void swap(elementStructure *element1, elementStructure *element2, int *positionVector);
int removeAndPrintMinimum(HEAP *heap, int *positionVector);
int decreasePriority(HEAP *heap, int *positionVector, int key, int newCost);

int main(){
  char operation;
  int size;
  //ponteiro da posiçoes no heap.
  int  *positionVector = NULL;
  //o heap em si.
  HEAP *heap = NULL;

  if(!scanf("%d",&size))
    return 1;

  if(createEnviroment(&heap, &positionVector, size))
    return 1;
  //leitura das operações.
  while(scanf(" %c",&operation) && operation != 't'){

    if(operation == 'i'){
      int k, c;

      if(scanf("%d %d", &k, &c) == 0)
        return 1;

      insertElement(heap, positionVector, k, c);

    }else if(operation == 'm'){
      if(removeAndPrintMinimum(heap, positionVector))
        printf("vazio\n");

    }else if(operation == 'd'){
      int k, c;
      if(scanf("%d %d", &k, &c) == 0)
        return 1;

      decreasePriority(heap, positionVector, k, c);

  }else if(operation == 's'){
    //operação criada á titulo de debug, para imprimir o heap e o vetor.
    for(int  i = 0; i < size; i++)
      printf("key:%d cost:%d\n", heap->array[i].key, heap->array[i].cost);
    printf("\n");
    for(int  i = 0; i < size; i++)
        printf("key:%d position: %d\n", i, positionVector[i]);
    printf("\n");

  }else{
      printf("Operação invalida!!\n");
    }

  }
  free(positionVector);
  free(heap->array);
  free(heap);
  return 0;
}

//createEnviroment aloca tanto o heap quanto o vetor de posições.
//iniciaiza com EMPTY indicando que os espaços vazios.
//retorna 0 se for bem sucedido e 1 se ocorrer algum problema.
int createEnviroment(HEAP **heap, int **positionVector, int size){
  HEAP *new = malloc(sizeof(HEAP));
  int *new2 = malloc(size*sizeof(int));

  //checa se a alocação ocorreu corretamente.
  if(!new || !new2)
    return 1;

  new->capacity = size;
  new->size = 0;
  new->type = 1;
  new->array = malloc(size*sizeof(elementStructure));

  if(!new->array)
    return 1;

  //inicializa tanto o heap e o vetor.
  for(int i = 0; i < size; i++){
    new->array[i].key = EMPTY;
    new->array[i].cost = EMPTY;
    new2[i] = EMPTY;
  }

  *heap = new;
  *positionVector = new2;

  return 0;
}
//insertElement insere elementos no heap e atualiza sua posição
//no vetor de posições.
//retorna 0, se houve inserção, retorna 1 se não houve;
int insertElement(HEAP *Helements , int *positionVector ,int element, int cost){

  //checa se há espaço para colocar.
  if(Helements->capacity == Helements->size)
    return 1;

  //checa se ja existe a chave.
  if(positionVector[element] != EMPTY)
    return 1;



  Helements->array[Helements->size].key = element;
  Helements->array[Helements->size].cost = cost;
  positionVector[element] = Helements->size;
  Helements->size++;
  //Percorre os pais do vetor acrescido, trocando de posição aqueles que
  //tem o custo menor.
  //Uma vez que o elemento é adicionado no fim do vetor com os elementos do heap,
  //essa operação é realizada afim de manter as propriedades do heap após a
  //inserção do heap.
  for(int i = Helements->size -1; i >= 0 && cost < Helements->array[(i-1)/2].cost; i = (i-1)/2)
    swap(&(Helements->array[i]), &(Helements->array[(i-1)/2]), positionVector);

  return 0;

}

//usado para conservar as propriedades do heap após um remoção.
void minHeapify(HEAP *Helements, int *positionVector, int location){
  int l, r, smallest;
  //acha os indices dos filhos de um nó.
  l = 2*location + 1;
  r = 2*location + 2;

  //seleciona o maior indice entre o nó atual, e os filhos.
  if(l < Helements->size && Helements->array[l].cost < Helements->array[location].cost){
    smallest = l;
  }
  else
    smallest = location;

  if(r < Helements->size && Helements->array[r].cost < Helements->array[smallest].cost){
    smallest = r;
  }
  //Caso o menor custo seja de um dos filhos, a propriedade do heap está
  //comprometida, assim precisamos trocar o pai e o filho de menor custo de lugar.
  if(smallest != location){
    elementStructure aux;
    int aux2;
    //Troca de posição nos elementos do heap.
    aux = Helements->array[smallest];
    Helements->array[smallest] = Helements->array[location];
    Helements->array[location] = aux;
    //troca de posição dos elementos no vetor de posições.
    aux2 = positionVector[Helements->array[smallest].key];
    positionVector[Helements->array[smallest].key] = positionVector[Helements->array[location].key];
    positionVector[Helements->array[location].key] = aux2;

    //chama a função para a posição onde o filho de menor custo estava
    //(foi trocado pelo pai). para checar se a propriedade do heap se conseva
    //e remanejar a variavel caso necessário.
    //Assume-se que as subarvores estão balanceadas antes da remoção do elemento.
    minHeapify(Helements,positionVector, smallest);
  }

}

//troca dois elementos de posição, trocando inclusive as posiçoes no
//vetor de posição.
void swap(elementStructure *element1, elementStructure *element2, int *positionVector){

  //Trocando o os elementos do heap de posição.
  elementStructure aux = *element1;
  *element1 = *element2;
  *element2 = aux;

  //Trocando os indices do vetor de posições.
  int aux2 = positionVector[(*element1).key];
  positionVector[(*element1).key] = positionVector[(*element2).key];
  positionVector[(*element2).key] = aux2;

}

//remove o menor elemento do heap de minimo e o remove,
//mantendo as propriedades do heap.
//retorna 0 se remover algo e 1 caso contrario.
int removeAndPrintMinimum(HEAP *heap, int *positionVector){

 //checa se o heap tem algum elemento.
  if(heap->size <= 0)
    return 1;

  //realiza a remoção do heap caso só haja 1 elemento.
  if(heap->size == 1){
    printf("minimo {%d,%d}\n", heap->array[0].key, heap->array[0].cost);
    heap->size--;
    //exclui no vetor posiçao.
    positionVector[heap->array[0].key] = EMPTY;
    //exclui no heap.
    heap->array[0].key = EMPTY;
    heap->array[0].cost = EMPTY;
    return 0;
  }

  printf("minimo {%d,%d}\n", heap->array[0].key, heap->array[0].cost);
  //exclui no vetor de posições.
  positionVector[heap->array[0].key] = EMPTY;
  //faz o ultimo elemento do heap que possui custo maior, ser a raiz,
  //onde deveria estar o menor elemento.(é necessário para minHeapify refazer
  // o heap para manter as propriedades.)
  heap->array[0] = heap->array[heap->size -1];
  heap->array[heap->size - 1].key = EMPTY;
  heap->array[heap->size - 1].cost = EMPTY;
  heap->size--;
  //mantem as propriedades do heap após a remoção.
  minHeapify(heap, positionVector, 0);


  return 0;
}

//Diminui a prioridade de uma chave, conservando a propriedade do heap.
int decreasePriority(HEAP *heap, int *positionVector, int key, int newCost){

  //altera a prioridade da chave no heap.
  heap->array[positionVector[key]].cost = newCost;
  //apartir do nó é percorrido os pais trocando que a nova prioridade for menor
  //do que a prioridade do pai, para conservar as propriedades da heap de minimo.
  for(int i = positionVector[key]; i >= 0 && newCost < heap->array[(i-1)/2].cost; i = (i-1)/2)
    swap(&(heap->array[i]), &(heap->array[(i-1)/2]), positionVector);

    return 0;

}
