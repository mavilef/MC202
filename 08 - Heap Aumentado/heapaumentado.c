#include <stdio.h>
#include <stdlib.h>

struct HEAP{
  int *array;
  int capacity;
  int size;
  int type;// 0 - HEAP de maximo, 1 - HEAP de mínimo
}

int main(){





  return 0;
}

HEAP* createHeap(int n){
  HEAP *new = malloc(sizeof(HEAP));

  new->capacity = n;
  new->size = 0;
  new->type = 1;
  new->array = malloc(n*sizeof(int));

  return new;
}

HEAP* insertElement(HEAP *Helements , HEAP *Hpriority, int element, int priority){
  Helements->array[Helements->size] = element;
  Hpriority->array[Hpriority->size] = priority;
  



}
