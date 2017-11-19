//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct forestStructure{
	int data;
	struct forestStructure *child;
	struct forestStructure *sibling;
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
		}else if(!strcmp("link", operation)){
			int A, B;
			scanf("%d %d", &A, &B);
		}else if(!strcmp("lca", operation)){
			int A, B;
			scanf("%d %d", &A, &B);


		}else{
			printf("Operação invalida\n");
			i--;
			continue;
		}
	}
	return 0;
}

forestStructure *createForest(int numberOfTrees){

	forestStructure *forestBegin = NULL;
	forestStructure *newNode = malloc(sizeof(forestStructure));
	newNode->data = numberOfTrees;
	newNode->child = NULL;
	newNode->sibling = NULL;
	forestBegin = newNode;
	int i = 0;
	for(i = numberOfTrees-1; i > 0; i--){
		newNode = malloc(sizeof(forestStructure));
		newNode->data = i;
		newNode->child = NULL;
		newNode->sibling = forestBegin;
		forestBegin = newNode;

	}

	return forestBegin;
}
 void cut();
 void link();
 int lca();