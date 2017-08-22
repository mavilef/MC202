
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"interface.h"


int main(){

	int numberOfOperations, size;
	char operation[8], arqName[11], sizeArq[7], sizeDisk[7];
	DISK *drive = NULL;


	for(int i = 0; numberOfOperations != 0; i++){   
		scanf("%d", &numberOfOperations);
		scanf("%s", sizeDisk);
		size = sizeConversor(sizeDisk);
		//diskInitializer(&drive, size);
		for(int j = 0; j < numberOfOperations; j++){
			scanf("%s", operation);

			if(strcmp(operation, "insere") == 0){
				scanf("%s", arqName);
				scanf("%s", sizeArq);
				size = sizeConversor(sizeDisk);
				//insert();
			}else if(strcmp(operation, "remove") == 0){
				scanf("%s", arqName);
				//remove();
			}else if(strcmp(operation, "otimiza") == 0){
				//otimize();
			}
			
		}

	}	

	return 0;

}
