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

void freeTheDisk(DISK **drive){
	if(*drive != NULL){
		NODE *aux = (*drive)->listHead;
		NODE *aux2 = NULL;
		while(aux->next != NULL){
			aux2 = aux;
			aux= aux->next;
			free(aux2);
		}
		free(aux);
		free(*drive);
		(*drive) = NULL;
	}
}

void otimize(DISK *drive){

	NODE *tail = drive->listHead;
	NODE *repositioner = drive->listHead;

	while(tail->next != NULL)
		tail= tail->next;

	while(repositioner != tail){
		if(repositioner->free == 1){
			if(repositioner->previous == NULL){
				drive->listHead = repositioner->next;
				drive->listHead->previous = NULL;
				repositioner->next = tail->next;
				repositioner->previous = tail;
				tail->next = repositioner;
				if(repositioner->next != NULL)
					repositioner->next->previous = repositioner;
				repositioner = drive->listHead;
			}else{
				repositioner->previous->next = repositioner->next;
				repositioner->next->previous = repositioner->previous;
				repositioner->next = tail->next;
				repositioner->previous = tail;
				tail->next = repositioner;
				if(repositioner->next != NULL)
					repositioner->next->previous = repositioner;
				repositioner = drive->listHead;
			}
		}else{
			repositioner = repositioner->next;
		}
	}
	catenateFreeSpaces(drive);
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
		otimize(drive);
		aux = drive->listHead;
		while(aux != NULL){
			if(aux->size >= ArchiveSize && aux->free == 1 && smallest == NULL){
				smallest = aux;
			}else if(aux->size >= ArchiveSize && aux->free == 1 && aux->size < smallest->size && smallest != NULL){
				smallest = aux;
			}
			aux = aux->next;
		}
		if(aux == NULL && smallest == NULL){
			drive->error = 1;
			return;
		}

		if(smallest->previous != NULL){
				smallest->size -= NewArchive->size;
				if(smallest->size == 0){
					smallest->previous->next = NewArchive;
					NewArchive->next = smallest->next;
					NewArchive->previous = smallest->previous;
					if (smallest->next != NULL)
						smallest->next->previous = NewArchive;
					free(smallest);
				}else{
					smallest->previous->next = NewArchive;
					NewArchive->next = smallest;
					NewArchive->previous = smallest->previous;
					smallest->previous = NewArchive;
				}
			}else if(smallest->previous == NULL){
				smallest->size -= NewArchive->size;
				if(smallest->size == 0){
					NewArchive->next = smallest->next;
					if(smallest->next != NULL)
						smallest->next->previous = NewArchive;
					drive->listHead = NewArchive;
					free(smallest);
				}else{
					smallest->previous = NewArchive;
					NewArchive->next = smallest;
					drive->listHead = NewArchive;
				}
			}

	}else{
		if(smallest->previous != NULL){
			smallest->size -= NewArchive->size;
			if(smallest->size == 0){
				smallest->previous->next = NewArchive;
				NewArchive->next = smallest->next;
				NewArchive->previous = smallest->previous;
				if (smallest->next != NULL)
					smallest->next->previous = NewArchive;
				free(smallest);
			}else{

				smallest->previous->next = NewArchive;
				NewArchive->next = smallest;
				NewArchive->previous = smallest->previous;
				smallest->previous = NewArchive;
			}
		}else if(smallest->previous == NULL){
			smallest->size -= NewArchive->size;
			if(smallest->size == 0){
				NewArchive->next = smallest->next;
				if(smallest->next != NULL)
					smallest->next->previous = NewArchive;
				drive->listHead = NewArchive;
				free(smallest);
			}else{
				smallest->previous = NewArchive;
				NewArchive->next = smallest;
				drive->listHead = NewArchive;
			}
		}
	}
}

void ArchiveRemover(DISK *drive, char archiveName[]){

	NODE *aux = drive->listHead;

	while(aux != NULL){
		if(strcmp(aux->arqName, archiveName) == 0){
			aux->free = 1;
			catenateFreeSpaceTest(aux);
			return;
		}
		aux = aux->next;
		
	}

} 

void EstimateUsage(DISK *drive){
	NODE *aux = drive->listHead;
	DISKUSAGE count;
	int blockDivision = drive->diskSize/8;
	int aux2 = 0;

	count.total = 0;
	count.freeSize = 0;
	count.usedSize = 0;


		while(aux != NULL){
			aux2 = aux->size;
			while(aux2 > 0){
				if(count.total + aux2 >= blockDivision){
					aux2 -= (blockDivision- count.total);
					if(aux->free == 1)
						count.freeSize += (blockDivision- count.total);
					else
						count.usedSize += (blockDivision- count.total);
					count.total += (blockDivision- count.total);
					printState(count);
					count.total = 0;
					count.freeSize = 0;
					count.usedSize = 0;

				}else{
					count.total += aux2;
					if(aux->free == 1)
						count.freeSize += aux2;
					else
						count.usedSize += aux2;
					aux2 = 0;

				}
			}
			aux=aux->next;
		}
		printf("\n");
}

void printState(DISKUSAGE counter){

	double check = (double)counter.freeSize/(double)counter.total;

	if(check <= .25){
		printf("[#]");
	}else if(check <= .75){
		printf("[-]");
	}else{
		printf("[ ]");
	}
}

void catenateFreeSpaces(DISK *drive){
	NODE *aux = drive->listHead, *aux2 = NULL;

	while(aux->next != NULL){
		if(aux->free == 1 && aux->next->free == 1){
			aux->size += aux->next->size;
			aux2= aux->next;
			aux->next = aux->next->next;
			if(aux->next != NULL)
				aux->next->previous = aux;
			free(aux2);
		}else{
			aux = aux->next;
		}
	}
}

void catenateFreeSpaceTest(NODE *candidate){

	NODE *aux = NULL;

	if((candidate)->next != NULL && (candidate)->next->free == 0 && (candidate)->previous != NULL && (candidate)->previous->free == 1){
		(candidate)->previous->size += (candidate)->size;
		(candidate)->previous->next = (candidate)->next;
		(candidate)->next->previous = (candidate)->previous;
		free(candidate);

	}else if((candidate)->next != NULL && (candidate)->next->free == 1 && (candidate)->previous != NULL && (candidate)->previous->free == 0){
		aux = (candidate)->next;
		(candidate)->next->size += (candidate)->size;
		(candidate)->previous->next = (candidate)->next;
		(candidate)->next->previous = (candidate)->previous;
		free(candidate);

	}else if((candidate)->next != NULL && (candidate)->next->free == 1 && (candidate)->previous != NULL && (candidate)->previous->free == 1){
		(candidate)->size += (candidate)->previous->size;
		(candidate)->size += (candidate)->next->size;
		if((candidate)->previous->previous != NULL)
			(candidate)->previous->previous->next = (candidate);
		aux = (candidate)->previous;
		(candidate)->previous = (candidate)->previous->previous;
		free(aux);
		aux = (candidate)->next;
		if((candidate)->next->next != NULL)
			(candidate)->next->next->previous = (candidate);
		(candidate)->next = (candidate)->next->next;
		free(aux);
	}
}


void otimizeTest(DISK *drive){

	NODE *tail = drive->listHead;
	NODE *aux = NULL;
	int counter = 0;

	while(tail->next != NULL){
		if(tail->free == 1){
			counter += tail->size;
			if(tail == drive->listHead){
				drive->listHead = tail->next;
			}
			if(tail->previous != NULL)
				tail->previous->next = tail->next;
			if(tail->next != NULL)
				tail->next->previous = tail->previous;
			aux = tail;
			tail= tail->next;
			free(aux);
		}else{
			tail= tail->next;
		}
	}

	if(tail->free == 1){
		tail->size += counter;
	}else if (tail->free == 0 && counter > 0){
		aux = malloc(sizeof(NODE));
		aux->size = counter;
		aux->next = NULL;
		aux->previous = tail;
		aux->free = 1;
		strcpy(aux->arqName, "free");
		tail->next = aux; 

	}

}
