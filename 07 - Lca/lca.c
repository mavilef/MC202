#include<stdio.h>
//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdlib.h>
#include<string.h>

typedef struct forestStructure{
	int data;
	int fatherIndex;
} forestStructure;

forestStructure* createForest(int numberOfTrees);

int main(){

	int numberOfTrees, numberOfOperations;
	char operation[5];
	forestStructure* myForest = NULL;
	scanf("%d %d", &numberOfTrees, &numberOfOperations);

	if(!numberOfOperations)
		return 0;

	myForest = createForest(numberOfTrees);
	int i;
	for(i = 0; i < numberOfOperations; i++){
		scanf("%s", operation);

		if(!strcmp("cut", operation)){
			int element;
			scanf("%d", &element);
			myForest[element-1].fatherIndex = -1;
		}else if(!strcmp("link", operation)){
			int A, B;
			scanf("%d %d", &A, &B);
			myForest[A-1].fatherIndex = B;
		}else if(!strcmp("lca", operation)){
			int A, B;
			scanf("%d %d", &A, &B);
			int aux;
			int aux2;

			for(aux = A-1;  aux != -1; aux = myForest[aux].fatherIndex - 1){
				for(aux2 = B-1; aux2 != -1; aux2 = myForest[aux2].fatherIndex - 1){
					if(aux == aux2){
						printf("%d\n", myForest[aux2].data);
						break;
					}
				}
				if(aux == aux2)
					break;
			}
		}else{
			printf("Operação invalida\n");
			i--;
			continue;
		}
	}
	return 0;
}

forestStructure *createForest(int numberOfTrees){

	forestStructure *initialForest = malloc(numberOfTrees*sizeof(forestStructure));

	int i = 0;
	for(i = 0; i < numberOfTrees; i++){
		initialForest[i].data = i+1;
		initialForest[i].fatherIndex = -1;
	}

	return initialForest;
}