//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct forestStructure{
	int data;
	int fatherIndex;
} forestStructure;

forestStructure* createForest(int numberOfTrees);

//Forma de implementação:
// Foi usada uma implementação de vetores, onde cada elemento do vetor possui
//a chave(data) e o indice do pai daquele nó.
int main(){
	//declarações:
	// numberOftree será o numero de arvores da nossa floresta, elas são
	//inicializadas sem filhos.
	// numberOfOperations indica o numero de operações para realizarmos na floresta,
	//é a condição de parada na leitura das operações.
	//operation corresponde a string digitada pelo usuario, que correponde,
	//à operação desejada.

	int numberOfTrees, numberOfOperations;
	char operation[5];
	forestStructure* myForest = NULL;
	//leitura dos inputs.
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
			//Faz o elemento selecionado pelo usuario, perder a conecção pai-filho,
			//o elemento agora será uma outra arvore.
			myForest[element-1].fatherIndex = -1;
		}else if(!strcmp("link", operation)){
			int A, B;
			scanf("%d %d", &A, &B);
			//Altera o indice do pai de A(digitado pelo usuario) como sendo B.
			myForest[A-1].fatherIndex = B;
		}else if(!strcmp("lca", operation)){
			int A, B;
			scanf("%d %d", &A, &B);
			int aux;
			int aux2;

			//Através de um método brute force, seleciona B e vai percorrendo os pais
			//até que encontre A, caso não encontre numa passada, é selecionado o pai de A
			//e reinicia-se o processo com B, até que se encontre um A == B, como o processo
			//se inicia do da base temos o menor ancestral.
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
	free(myForest);
	return 0;
}

//CreateForest cria o vetor inicial com todas as arvores, que possuem só raiz.
forestStructure *createForest(int numberOfTrees){

	forestStructure *initialForest = malloc(numberOfTrees*sizeof(forestStructure));

	int i = 0;
	for(i = 0; i < numberOfTrees; i++){
		//chaves de 1 á N
		initialForest[i].data = i+1;
		//-1 indica que o nó não possui pai.
		initialForest[i].fatherIndex = -1;
	}

	return initialForest;
}
