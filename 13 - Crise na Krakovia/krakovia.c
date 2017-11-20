//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<stdlib.h>
#define MAXROOMS 50

typedef struct ROOM{
	//tamanho das arestas acumulado
	int timeSoFar;
	//indice do pai
	int fatherIndex;
	//tamanho da areta pai-filho
	int distanceToFather;
	//Armazena se determinado nó, é ou não uma folha
	int isItALeaf;
	//verifica se ja foi visitado!
	int visited;
}	ROOM;

void quickSort_leafs(ROOM *base, int low, int high, int *leafs);
void swap_leafs(int * a, int * b);
int partition_leafs(ROOM *base, int low, int high, int *leafs);


//A Solução deste laboratório consiste em somar todas arestas e encontrar
//a folha mais distante da raiz da arvore.
// assim fazemos 2*(soma de todas as arestas) - (soma das arestas até chegar na folha mais distante).
// é necessário fazer a subtração pois não é preciso voltar à sala inicial depois de percorrer todas as salas.
// e para minizar o tempo, deixamos a sala mais distante por ultimo, para n ser preciso voltar.
int main(){
	//grava as informações da arvore(grafo).
	ROOM *base = malloc(MAXROOMS*sizeof(ROOM));
	//grava informações sobre as folhas da arvore.
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
		//Leitura dos input com criação do grafo
		for(int i = 0; i < operations; i++){
			scanf("%d %d %d", &A, &B, &timer);
			base[B].fatherIndex = A;
			base[B].distanceToFather = timer;
			base[A].isItALeaf = 0;
			base[B].isItALeaf = 1;
			totalTime += 2*timer;
		}
		//grava o indice das folhas no vetor de folhas
		//e conta quantas folhas tem.
		numberOfLeafs = 0;
		for(int i = 0; i < MAXROOMS; i++){
			if(base[i].isItALeaf == 1){
				leafs[numberOfLeafs] = i;
				numberOfLeafs++;
			}
		}

		int aux, counter;
		//preenche as folhas com o  tempo necessário para chegar nelas.
		for(int i = 0; i < numberOfLeafs; i++){
			aux = leafs[i];
			counter = 0;
			while(aux != 0){
				counter += base[aux].distanceToFather;
				aux = base[aux].fatherIndex;
			}

			base[leafs[i]].timeSoFar = counter; 
		}

		//ordena o vetor de folhas pelo por tempo acumulado.
		quickSort_leafs(base, 0, numberOfLeafs-1, leafs);

		//percorre o caminho da maior folha subtraindo as arestas do 
		//tamanho total.
		int aux2 = leafs[numberOfLeafs-1];
		while(aux2 != 0){
			totalTime -= base[aux2].distanceToFather;
			aux2 = base[aux2].fatherIndex;
		}
		printf("%d\n", totalTime);

	}
	free(leafs);
	free(base);
	return 0;
}

//quickSort alterado para ordenar as folhas por tempo acumulado.
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
