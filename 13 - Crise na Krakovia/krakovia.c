#include<stdio.h>
#include<stdlib.h>
#define MAXROOMS 50

typedef struct ROOM{
	int timeSoFar;
	int fatherIndex;
	int distanceToFather;
	int isItALeaf;
	int visited;
}	ROOM;

void quickSort_leafs(ROOM *base, int low, int high, int *leafs);
void swap_leafs(int * a, int * b);
int partition_leafs(ROOM *base, int low, int high, int *leafs);

int main(){

	ROOM *base = malloc(MAXROOMS*sizeof(ROOM));
	int *leafs = malloc(MAXROOMS*sizeof(int));
	int numberOfLeafs = 0;
	int operations, A, B, timer, totalTime;
	//leitura do input
	while(scanf("%d", &operations) && operations != 0){

		totalTime = 0;
		//inicializaçao do grafo.
		for(int i = 0; i < MAXROOMS; i++){
			base[i].timeSoFar = 0;
			base[i].fatherIndex = 0;
			base[i].visited = 0;
			base[i].distanceToFather = 0;
			base[i].isItALeaf = 0;
		}

		for(int i = 0; i < operations; i++){
			scanf("%d %d %d", &A, &B, &timer);
			base[B].fatherIndex = A;
			base[B].distanceToFather = timer;
			base[A].isItALeaf = 0;
			base[B].isItALeaf = 1;
			totalTime += 2*timer;
		}

		numberOfLeafs = 0;
		for(int i = 0; i < MAXROOMS; i++){
			if(base[i].isItALeaf == 1){
				leafs[numberOfLeafs] = i;
				numberOfLeafs++;
			}
		}

		int aux, counter;
		for(int i = 0; i < numberOfLeafs; i++){
			aux = leafs[i];
			counter = 0;
			while(aux != 0){
				counter += base[aux].distanceToFather;
				aux = base[aux].fatherIndex;
			}

			base[leafs[i]].timeSoFar = counter; 
		}


		quickSort_leafs(base, 0, numberOfLeafs-1, leafs);

		int aux2 = leafs[numberOfLeafs-1];

		while(aux2 != 0){
			totalTime -= base[aux2].distanceToFather;
			aux2 = base[aux2].fatherIndex;
		}
		printf("%d\n", totalTime);

	}
	free(base);
	return 0;
}

void quickSort_leafs(ROOM *base, int low, int high, int *leafs){
    if (low < high) {
		int pi = partition_leafs(base, low, high, leafs);

		quickSort_leafs(base, low, pi - 1, leafs);
		quickSort_leafs(base, pi + 1, high, leafs);
    }
}

void swap_leafs(int * a, int * b){
    int t = *a;
    *a = *b;
    *b = t;
}


int partition_leafs(ROOM *base, int low, int high, int *leafs){
    int pivot = base[leafs[high]].timeSoFar;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
		if (base[leafs[j]].timeSoFar <= pivot) {
		    i++;
		    swap_leafs(&leafs[i], &leafs[j]);
		}
    }
    swap_leafs(&leafs[i + 1], &leafs[high]);

    return (i + 1);
}
