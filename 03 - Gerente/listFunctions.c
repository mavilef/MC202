#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"interface.h"

void diskInitializer(DISK **drive, int freeSpace){

	if(*drive == NULL){
		*drive = malloc(sizeof(DISK));
		(*drive)->diskSize = freeSpace;
		(*drive)->listHead = NULL;
		(*drive)->error = 0;

		NODE *freeSpaceDisk = malloc(sizeof(NODE));
		strcpy(freeSpaceDisk->arqName,"free");
		freeSpaceDisk->size = freeSpace;
		freeSpaceDisk->next = NULL;
		freeSpaceDisk->previous = NULL;
		freeSpaceDisk->free = 1;

		(*drive)->listHead = freeSpaceDisk;


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
		(*drive)->diskSize= freeSpace;
		(*drive)->listHead = NULL;
		(*drive)->error = 0;

		NODE *freeSpaceDisk = malloc(sizeof(NODE));
		strcpy(freeSpaceDisk->arqName,"free");
		freeSpaceDisk->size = freeSpace;
		freeSpaceDisk->next = NULL;
		freeSpaceDisk->previous = NULL;
		freeSpaceDisk->free = 1;

		(*drive)->listHead = freeSpaceDisk;

	}

}


void ArchiveInsertion(DISK *drive, char archiveName[], int ArchiveSize){

	NODE *NewArchive = malloc(sizeof(NODE));
  strcpy(NewArchive->arqName,archiveName);
	NewArchive->size = ArchiveSize;
	NewArchive->next = NULL;
	NewArchive->previous = NULL;
	NewArchive->free = 0;

	NODE *aux = drive->listHead;
	NODE *smallest = NULL;

	while(aux != NULL){
		if(aux->size >= ArchiveSize && aux->free == 1 && smallest == NULL){
			smallest = aux;
		}else if(aux->size >= ArchiveSize && aux->free == 1 && aux->size < smallest->size && smallest != NULL){
			smallest = aux;
		}
		aux = aux->next;
	}
	if(aux == NULL && smallest == NULL){
		/*otimiza()
		while(aux != NULL){
			if(aux->size >= ArchiveSize && aux->free == 1 && smallest == NULL){
				smallest = aux;
			}else if(aux->size >= ArchiveSize && aux->free == 1 && aux->size < smallest && smallest != NULL){
				smallest = aux;
			}
			aux = aux->next;
		}

		//fazer caso não ache mesmo assim.
		*/
	}else{
		if(smallest->previous != NULL){
			smallest->size -= NewArchive->size;
			smallest->previous->next = NewArchive;
			NewArchive->next = smallest;
			NewArchive->previous = smallest->previous;
			smallest->previous = NewArchive;

		}else if(smallest->previous == NULL){
			smallest->size -= NewArchive->size;
			smallest->previous = NewArchive;
			NewArchive->next = smallest;
			drive->listHead = NewArchive;
		}
	}

}


void ArchiveRemover(DISK *drive, char archiveName[]){

	NODE *aux = drive->listHead;

	while(strcmp(aux->arqName, archiveName) != 0 && aux != NULL)
		aux = aux->next;

	if(aux == NULL){
		return;
	}else{
		aux->free = 1;
		strcpy(aux->arqName,"free");
		catenateFreeSpaces(drive);
	}
}

void catenateFreeSpaces(DISK *drive){
	NODE *aux = drive->listHead, *aux2 = NULL;

	while(aux->next != NULL){
		if(aux->free == 1 && aux->next->free == 1){
			aux->size += aux->next->size;
			aux2= aux->next;
			aux->next = aux->next->next;
			free(aux2);
			if(aux->next != NULL)
				aux->next->previous = aux;
		}else{
			aux = aux->next;
		}
	}

}
