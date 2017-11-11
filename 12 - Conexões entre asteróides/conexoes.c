#include<stdio.h>
#include<math.h>
#define numberOfParameters 6

typedef struct astheroid{
	short int x, y, z, vx, vy, vz;  
} astheroid;


double distanceBetweenTwoAstheroids(astheroid A, astheroid B);

int main(){
	int numberOfOperations;
	if(!scanf("%d", &numberOfOperations)){
		printf("0");
		return 0;
	}

	astheroid myAstheroids[numberOfOperations]; 


	for(int i = 0; i < numberOfOperations; i++)
		scanf("%hd %hd %hd %hd %hd %hd", &myAstheroids[i].x, &myAstheroids[i].y, &myAstheroids[i].z, &myAstheroids[i].vx, &myAstheroids[i].vy, &myAstheroids[i].vz);

	return 0;
}


double distanceBetweenTwoAstheroids(astheroid A, astheroid B){
	return sqrt(pow(A.x - B.x, 2) + pow(A.y- B.y, 2) + pow(A.z - B.z, 2)); 
}
