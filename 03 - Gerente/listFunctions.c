#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"interface.h"

void diskInitializer(DISK **drive, int freeSpace){

	if(*drive == NULL){
		*drive = malloc(sizeof(DISK));
		(*drive)->freeSpace = freeSpace;
		(*drive)->listHead = NULL;
		(*drive)->listTail = NULL;

	}else{
		if((*drive)->listHead == NULL){
			free(*drive);
		}else{
			NODE *aux = (*drive)->listHead;
			NODE *aux2 = NULL;

			while(aux->next != NULL){
				aux2 = aux;
				aux = aux->next;
				free(aux2);
			}

			free(aux);
			free(*drive);
		}

		*drive = malloc(sizeof(DISK));
		(*drive)->freeSpace = freeSpace;
		(*drive)->listHead = NULL;
		(*drive)->listTail = NULL;


	}

}

void sizeConversor(char size[]){






	
}
