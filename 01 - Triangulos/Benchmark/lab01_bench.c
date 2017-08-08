//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){

  int order = 20000;
	//scanf("%d", &order);

	int i, j, k;
//Alocação da matriz
  double **restrict matrix = malloc(order*sizeof(double*));

  if(matrix == NULL)
    printf("Erro ao alocar a matriz!\n");

//Coloca os inputs na matriz
  for (i = 0, j = 1; i < order; i++, j++){
    matrix[i] = malloc(j*sizeof(double));
    for(k = 0; k < j; k++){
      matrix[i][k] = rand() % 3;
    }
  }

double avarage = 0, standartDeviation = 0;
int numberOfElements = (pow(order, 2)+order)/2;
//Faz o somatório dos elementos.

  for(i = 0, j = 1; i < order; i++, j++ ){
    for(k = 0; k < j; k++){
      avarage = avarage + matrix[i][k];
    }
  }
//Faz a média em si.(divide o resultado anterior pelo numero de elementos)
  avarage = avarage/numberOfElements;
//Calculo do somatório (x - média)²
  for(i = 0, j = 1; i < order; i++, j++ ){
    for(k = 0; k < j; k++){
      standartDeviation = standartDeviation + pow((matrix[i][k] - avarage),2);
    }
  }
/* Divide o resultado anterior pelo numero de elementos e tira a raiz, terminando
 * o calculo do desvio padrão
 */
  standartDeviation = sqrt(standartDeviation/numberOfElements);

/* Impressão de (x - m)/d onde x é o elemento correspodente, m é a média
 * aritmética dos elementos(avarage) e d é desvio padrão dos elementos(standartDeviation)
 */
  for(i = 0, j = 1; i < order; i++, j++ ){
    for(k = 0; k < j; k++){
      matrix[i][k]=(matrix[i][k] - avarage)/standartDeviation;
    }
  }

//liberação da memoria alocada para matriz.
	for(i = 0; i < order; i++){
		  free(matrix[i]);
	}
	free(matrix);

  return 0;
}
