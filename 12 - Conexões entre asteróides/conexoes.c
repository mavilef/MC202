//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define POSSIBLETIMES 400000

typedef struct astheroid{
	double x, y, z, vx, vy, vz;
} astheroid;

typedef struct distanceFactors{
	int firstFactor, secondFactor, thirdFactor;
	int from;
	int to;

} distanceFactors;

typedef struct checkTime{
	double t;
	int newSegment, oldSegment;

} checkTime;

double distanceBetweenTwoAstheroids(astheroid A, astheroid B);
int findset(int x, int **vector);
void swap_checkTime(checkTime* a, checkTime* b);
int partition_checkTime (checkTime arr[], int low, int high);
void quickSort_checkTime(checkTime arr[], int low, int high);
void swap_distanceFactors(distanceFactors* a, distanceFactors* b);
int partition_distanceFactors (distanceFactors arr[], int low, int high);
void quickSort_distanceFactors(distanceFactors arr[], int low, int high);


int main(){
	int numberOfOperations;
	if(!scanf("%d", &numberOfOperations)){
			printf("Erro na leitura de input!\n");
		return 1;
	}

	astheroid myAstheroids[numberOfOperations];
	distanceFactors distances[numberOfOperations*(numberOfOperations+1)*2];
	checkTime tests[POSSIBLETIMES];
	for(int i = 0; i < POSSIBLETIMES; i++){
		tests[i].t = 0;
		tests[i].newSegment = 0;
		tests[i].oldSegment = 0;
	}
	int endIdx = 0;

	for(int i = 0; i <= numberOfOperations; i++)
		if(!scanf("%lf %lf %lf %lf %lf %lf", &myAstheroids[i].x, &myAstheroids[i].y, &myAstheroids[i].z, &myAstheroids[i].vx, &myAstheroids[i].vy, &myAstheroids[i].vz)){
			printf("Erro na leitura de input!\n");
			return 1;
		}

	int counterDistances = 0;
	for(int i = 0; i < numberOfOperations; i++){
		for(int j = i+1; j < numberOfOperations; j++){
			distances[counterDistances].firstFactor = pow(myAstheroids[i].vx-myAstheroids[j].vx,2)+pow(myAstheroids[i].vy-myAstheroids[j].vy,2)+pow(myAstheroids[i].vz-myAstheroids[j].vz,2);
			distances[counterDistances].secondFactor = 2*((myAstheroids[i].x-myAstheroids[j].x)*(myAstheroids[i].vx-myAstheroids[j].vx)+(myAstheroids[i].y-myAstheroids[j].y)*(myAstheroids[i].vy-myAstheroids[j].vy)+(myAstheroids[i].z-myAstheroids[j].z)*(myAstheroids[i].vz - myAstheroids[j].vz));
			distances[counterDistances].thirdFactor = pow(myAstheroids[i].x-myAstheroids[j].x,2)+pow(myAstheroids[i].y-myAstheroids[j].y,2)+pow(myAstheroids[i].z-myAstheroids[j].z,2);
			distances[counterDistances].from = i;
			distances[counterDistances].to = j;
			counterDistances++;
		}
	}
	quickSort_distanceFactors(distances, 0, counterDistances-1);

  /* //  **TRECHO USADO PARA DEBUG**
	for(int i = 0; i < counterDistances; i++){
		printf("indice: %d , distancia: %d, origem: %d, destino:%d\n", i, distances[i].firstFactor+distances[i].secondFactor+distances[i].thirdFactor, distances[i].from, distances[i].to);
	}
	*/

	for(int i = 0; i < counterDistances; i++){
		for(int j = i+1; j < counterDistances; j++){
			int solution1 = i, solution2 = j;
			if (distances[solution1].firstFactor - distances[solution2].firstFactor < 0) {
				solution1 = j;
				solution2 = i;
			}

			double a, b ,c;
			a = distances[solution1].firstFactor - distances[solution2].firstFactor;
			b = distances[solution1].secondFactor - distances[solution2].secondFactor;
			c = distances[solution1].thirdFactor - distances[solution2].thirdFactor;

			if(abs(a)< pow(M_E, -6)){
				if(abs(b) < pow(M_E, -6))
					continue;

				if(b>0){
					int aux;
					aux = solution1;
					solution1 = solution2;
					solution2 = aux;
					b = -b;
					c = -c;
				}

				if(c>0){
					tests[endIdx].t = (-c)/b;
					tests[endIdx].newSegment = solution1;
					tests[endIdx].oldSegment = solution2;
					endIdx++;
				}
				continue;
			}

			double delta = b*b - 4*a*c;
			if(delta < pow(M_E, -6))
				continue;

			delta = sqrt(delta);
			double t1, t2;
			t1 = (-b - delta)/(2*a);
			t2 = (-b + delta)/(2*a);
			if(t1 > 0){
				tests[endIdx].t = t1;
				tests[endIdx].newSegment = solution1;
				tests[endIdx].oldSegment = solution2;
				endIdx++;

			}
			if(t2 > 0){
				tests[endIdx].t = t2;
				tests[endIdx].newSegment = solution2;
				tests[endIdx].oldSegment = solution1;
				endIdx++;

			}
		}
	}
	quickSort_checkTime(tests, 0, endIdx-1);

 /*  // **TRECHO USADO PARA DEBUG**
	for(int i = 0; i < endIdx; i++){
		printf("indice: %d , tempo: %lf, indices das arestas envolvidas no vetor de distancias %d %d\n", i, tests[i].t, tests[i].newSegment, tests[i].oldSegment);
	}
	*/

	int pos[numberOfOperations*(numberOfOperations+1)*2];
	int vertices[numberOfOperations];
	int *verticesIndex = malloc(numberOfOperations*sizeof(int));

	for(int i = 0; i < numberOfOperations; i++)
		verticesIndex[i]= i;

	for(int i = 0; i < counterDistances; i++)
		pos[i] = 0;

	int idx = 0;
	for(int i = 0; i < counterDistances; i++){
		int u = findset(distances[i].from,&verticesIndex), v = findset(distances[i].to,&verticesIndex);
		if(u != v){
			vertices[pos[i]=++idx]=i;
			verticesIndex[u]= v;
		}
	}

	int reconfigurations = 1;
	for(int i = 0; i < endIdx; i++){
		if(pos[tests[i].oldSegment]&&(!pos[tests[i].newSegment])){

			for(int i = 0; i < numberOfOperations; i++)
				verticesIndex[i]= i;

			int oldpos = pos[tests[i].oldSegment];
			for(int j = 1; j < numberOfOperations; j++){
				if(j != oldpos){
					int u = findset(distances[vertices[j]].from,&verticesIndex), v = findset(distances[vertices[j]].to,&verticesIndex);

					if(u != v){
						verticesIndex[u] = v;
					}
				}
			}
			int u = findset(distances[tests[i].newSegment].from,&verticesIndex), v = findset(distances[tests[i].newSegment].to,&verticesIndex);
			if(u != v){
				reconfigurations++;
				pos[tests[i].newSegment]= oldpos;
				vertices[oldpos]=tests[i].newSegment;
				pos[tests[i].oldSegment]=0;
			}
		}
	}

	printf("%d\n", reconfigurations);
	free(verticesIndex);
	return 0;
}

int findset(int x, int **vector){
	if((*vector)[x] == x){
		return x;
	}else{
		(*vector)[x]=findset((*vector)[x], &(*vector));
		return (*vector)[x];
	}
}

void swap_checkTime(checkTime* a, checkTime* b){
    checkTime t = *a;
    *a = *b;
    *b = t;
}


int partition_checkTime (checkTime arr[], int low, int high){
    checkTime pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].t <= pivot.t)
        {
            i++;
            swap_checkTime(&arr[i], &arr[j]);
        }
    }
    swap_checkTime(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort_checkTime(checkTime arr[], int low, int high){
    if (low < high)
    {
        int pi = partition_checkTime(arr, low, high);

        quickSort_checkTime(arr, low, pi - 1);
        quickSort_checkTime(arr, pi + 1, high);
    }
}

void swap_distanceFactors(distanceFactors* a, distanceFactors* b){
    distanceFactors t = *a;
    *a = *b;
    *b = t;
}


int partition_distanceFactors (distanceFactors arr[], int low, int high){
    distanceFactors pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j].thirdFactor <= pivot.thirdFactor)
        {
            i++;
            swap_distanceFactors(&arr[i], &arr[j]);
        }
    }
    swap_distanceFactors(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort_distanceFactors(distanceFactors arr[], int low, int high){
    if (low < high)
    {
        int pi = partition_distanceFactors(arr, low, high);

        quickSort_distanceFactors(arr, low, pi - 1);
        quickSort_distanceFactors(arr, pi + 1, high);
    }
}
