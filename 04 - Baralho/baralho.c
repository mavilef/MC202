//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<stdlib.h>

typedef  struct vector{	
	int capacity;
	int size;
	int *numbers;
} vector;

void refreshVector(vector *vec, int *begin, int *end);

int main (){

	//declarações:
	//flag é usado para identificar quando é o momento de excluir a carta(flag = 0)
	//ou quando é o momento de colocar a carta por ultimo.
	//begin é um indice que indicará o começo do vetor.
	//end é um indice que indicará o fim do vetor.
	//numberOfElements representa o numero de cartas.
	// i é um indice para loop.
	//Cards armazenará o a capacidade do vetor, seu tamanho e o endereço do 
	//vetor.

	int flag, begin, end , numberOfElements, i;
	vector *cards = malloc(sizeof(vector));

	//leitura das entradas até encontrar 0;
	while(scanf("%d", &numberOfElements) && numberOfElements != 0){
		//parametros iniciais da entrada depois de cada numero de cartas
		flag = 0;
		cards->capacity = numberOfElements;
		cards->size = numberOfElements;
		cards->numbers = malloc(numberOfElements*sizeof(int));
		begin = 0;
		end = numberOfElements - 1;
		for(i = 0; i < numberOfElements; i++)
			cards->numbers[i]= i+1;
		printf("Cartas jogadas:");
		//roda o loop até que só haja um elemento
		//ou seja o inicio é igual ao fim.
		while( begin != end){
			//exclusão de carta.
			if(flag == 0){
				printf(" %d",cards->numbers[begin]);
				cards->numbers[begin] = 0;
				cards->size--;
				//faz com que um indice volte para a primeira posição caso passe do tamanho do vetor.
				begin = (begin + 1)% numberOfElements;
				flag = 1;
			//inserir a carta no fim.
			}else{
				printf(",");
				end = (end + 1)% numberOfElements;
				cards->numbers[end] = cards->numbers[begin];
				cards->numbers[begin] = 0;
				begin = (begin + 1)% numberOfElements;
				flag = 0;
				//checa se o tamanho do vetor é igual a 1/4
				//da capacidade total e faz um novo vetor com um quarto do tamanho.
				refreshVector(cards, &begin, &end);

			}
		}			
			printf("\nCarta restante: %d\n", cards->numbers[begin]);
			free(cards->numbers);
	}

			free(cards);



	return 0;
}

//atualiza a capacidade do vetor caso necessário.
void refreshVector(vector *vec, int *begin, int *end){

	if(vec->size < (vec->capacity)/4){
		int *newSize = malloc((vec->capacity/2)*sizeof(int));
		int i , j;
		//copia os elementos do antigo vetor para o novo vetor 
		//com o tamanho atualizado.
		for(i = *begin, j = 0; i != *end; i++, j++){
			if(i > vec->capacity - 1)
				i %= vec->capacity;
			newSize[j] = vec->numbers[i];
		}
		newSize[j] = vec->numbers[i];

		free(vec->numbers);
		vec->numbers = newSize;
		vec->capacity = vec->capacity/2;

		//atualiza os indices do começo do vetor e do fim.
		(*begin) = 0;
		(*end) = j;

	}
}
