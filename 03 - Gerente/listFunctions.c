#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"interface.h"

//Inicialização de um novo disco.
void diskInitializer(DISK **drive, int freeSpace){

	//Caso não haja um disco pré existente.
	if(*drive == NULL){
		*drive = malloc(sizeof(DISK));
		(*drive)->diskSize = freeSpace;
		(*drive)->listHead = NULL;
		(*drive)->error = 0;
		//adição do espaço livre do disco.
		NODE *freeSpaceDisk = malloc(sizeof(NODE));
		strcpy(freeSpaceDisk->arqName,"free");
		freeSpaceDisk->size = freeSpace;
		freeSpaceDisk->next = NULL;
		freeSpaceDisk->previous = NULL;
		freeSpaceDisk->free = 1;

		(*drive)->listHead = freeSpaceDisk;

		//caso já haja um disco criado anteriormente.
	}else{
		//caso o disco preexistente não tenha um lista de arquivos criada.
		if((*drive)->listHead == NULL){
			free(*drive);
		}else{
			//libera o disco preexistente e sua lista de arquivos.
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

		//reconstrução do novo disco.
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

//libera memoria de um disco criado junto com sua lista de Arquivos.
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

//Faz a inserção de arquivos no disco quando possivel(caso haja espaço).
void ArchiveInsertion(DISK *drive, char archiveName[], int ArchiveSize){
	//Declaraçôes:
	//NewArchive é o novo arquivo a ser adicionado.
	//aux é um ponteiro que percorrá a lista do disco buscando um espaço livre
	//de tamanho suficiente.
	//smallest é um ponteiro que após percorrer a lista, apontará para o
	//primeiro e menor espaço livre com tamanho igual ou maior ao arquivo a ser
	//adicionado.
	//tail é um ponteiro adicionado para otimização do código, caso a lista
	//seja percorrida e nenhum espaço livre compativel tenha sido encontrado,
	// a lista é otimizada(com a função otimize), e tail irá apontar para o penultimo
	// elemento da lista. será apartir dessa posição que aux irá buscar novamente
	//espaços livres compativeis.
	NODE *NewArchive = malloc(sizeof(NODE));
 	strcpy(NewArchive->arqName,archiveName);
	NewArchive->size = ArchiveSize;
	NewArchive->next = NULL;
	NewArchive->previous = NULL;
	NewArchive->free = 0;

	NODE *aux = drive->listHead;
	NODE *smallest = NULL;
	NODE *tail = drive->listHead;
	//busca de espaçps livres começando da cabeça.
	while(aux != NULL){
		//move smallest caso um espaço tenha sido encontrado.
		if(aux->size >= ArchiveSize && aux->free == 1 && smallest == NULL){
			smallest = aux;
		//move smallest caso haja um espaço menor que o espaço livre atual e
		//seja compativel com o arquivo a ser adicionado.
		}else if(aux->size >= ArchiveSize && aux->free == 1 && aux->size < smallest->size && smallest != NULL){
			smallest = aux;
		}
		//move tail para a ultima posição da lista.
		if(aux->next == NULL)
			tail = aux;
		aux = aux->next;
	}
	//caso não encontre espaços livre de tamanho suficiente em uma primeira passada
	if(aux == NULL && smallest == NULL){
		//move todos os espaços livres do disco para o fim.
		otimize(drive);
		//Faz com que a busca seja iniciada a partir da penultima posição da lista otimizada.
		aux = tail;
		//busca de espaços livres começando de tail.
		while(aux != NULL){
			//move smallest caso um espaço tenha sido encontrado.
			if(aux->size >= ArchiveSize && aux->free == 1 && smallest == NULL){
				smallest = aux;
			//move smallest caso haja um espaço menor que o espaço livre atual e
			//seja compativel com o arquivo a ser adicionado.
			}else if(aux->size >= ArchiveSize && aux->free == 1 && aux->size < smallest->size && smallest != NULL){
				smallest = aux;
			}
			aux = aux->next;
		}
		//caso não encontre na segunda passada é indicado erro de disco, setando
		//a flag error = 1 e é cancelada a operação.
		if(aux == NULL && smallest == NULL){
			drive->error = 1;
			return;
		}
		//caso encontre o espaço livre na segunda passada.
		//è feita a adição do arquivo antes do nó livre.
		if(smallest->previous != NULL){
				smallest->size -= NewArchive->size;
				//caso o arquivo consuma todo o espaço de um nó de espaço vazio
				//o nó livre é liberado.
				if(smallest->size == 0){
					smallest->previous->next = NewArchive;
					NewArchive->next = smallest->next;
					NewArchive->previous = smallest->previous;
					if (smallest->next != NULL)
						smallest->next->previous = NewArchive;
					free(smallest);
				//caso haja sobra de espaço no nó livre.
				}else{
					smallest->previous->next = NewArchive;
					NewArchive->next = smallest;
					NewArchive->previous = smallest->previous;
					smallest->previous = NewArchive;
				}
			}
	//caso encontre espaços livres na primeira passada.
	}else{
		//caso o espaço livre compativel não esteja na cabeça.
		if(smallest->previous != NULL){
			smallest->size -= NewArchive->size;
			//caso o arquivo consuma todo o espaço de um nó de espaço vazio
			//o nó livre é liberado.
			if(smallest->size == 0){
				smallest->previous->next = NewArchive;
				NewArchive->next = smallest->next;
				NewArchive->previous = smallest->previous;
				if (smallest->next != NULL)
					smallest->next->previous = NewArchive;
				free(smallest);
			//caso haja sobra de espaço no nó livre.
			}else{
				smallest->previous->next = NewArchive;
				NewArchive->next = smallest;
				NewArchive->previous = smallest->previous;
				smallest->previous = NewArchive;
			}
		//caso o espaço livre compativel esteja na cabeça.
		}else if(smallest->previous == NULL){
			smallest->size -= NewArchive->size;
			//caso o arquivo consuma todo o espaço de um nó de espaço vazio
			//o nó livre é liberado.
			if(smallest->size == 0){
				NewArchive->next = smallest->next;
				if(smallest->next != NULL)
					smallest->next->previous = NewArchive;
				drive->listHead = NewArchive;
				free(smallest);
			//caso haja sobra de espaço no nó livre.
			}else{
				smallest->previous = NewArchive;
				NewArchive->next = smallest;
				drive->listHead = NewArchive;
			}
		}
	}
}

//Procura um arquivo na lista e seta como nó livre caso encontre.
void ArchiveRemover(DISK *drive, char archiveName[]){

	NODE *aux = drive->listHead;
	//percorre a lista.
	while(aux != NULL){
		//verifica se o nó é o arquivo procurado.
		if(strcmp(aux->arqName, archiveName) == 0){
			//caso encontre, seta como espaço livre.
			aux->free = 1;
			strcpy(aux->arqName, "free");
			//Verifica se existem outros espaços livres adjascentes
			//e mescla eles em um nó unico.
			catenateFreeSpaces(aux);
			return;
		}
		aux = aux->next;

	}

}

//Verifica e imprime na tela o espaço ocupado em
//cada oitavo do tamanho total do disco.
void EstimateUsage(DISK *drive){
	//Declarações:
	//aux é um ponteiro auxiliar que percorre a lista.
	//count representa um oitavo do disco e é usado para
	//acumular espaços livres e ocupados de cada nó da lista
	//de arquivos.
	//blockDivision é um inteiro que representa um oitavo do tamanho total do
	//disco.
	//aux2 é usado para copiar o tamanho de cada nó na lista.
	NODE *aux = drive->listHead;
	DISKUSAGE count;
	int blockDivision = drive->diskSize/8;
	int aux2 = 0;

	count.total = 0;
	count.freeSize = 0;
	count.usedSize = 0;


		while(aux != NULL){
			aux2 = aux->size;
			//Vai acumulando em count até o tamanho do arquivo zerar.
			while(aux2 > 0){
				//Verifica se o count excede o tamanho de um oitavo do disco
				//caso seja adicionado a um no.
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
				//caso não exceda.
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

//Imprime a situação de um oitavo da disco
//Função usada por EstimateUsage.
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

//Procura espaços livres entre espaços ocupados e coloca-os
//todos no fim da lista de arquivos.(Desfragmenta o disco)
void otimize(DISK *drive){

	NODE *tail = drive->listHead;
	NODE *aux = NULL;
	int counter = 0;

	//Percorre a lista e acumula em counter o tamanho de todos os espaços livres.
	while(tail->next != NULL){
		//Acumula em counter o espaço de um nó livre encontrado
		//e destroi o nó de espaço livre.
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
	//caso haja um nó livre na ultima posição é adicionado counter(com todo o espaço livre)
	// ao nó livre.
	if(tail->free == 1){
		tail->size += counter;
	//caso o ultimo nó seja um espaço ocupado e haja espaço livre fragmentado
	//na lista de arquivos é criado um novo nó livre com todo espaço
	//livre na ultima posiçao da lista.
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

//Concatena espaços livres adjascentes.
//Função usada por ArchiveRemover.
void catenateFreeSpaces(NODE *candidate){
	NODE *begin = candidate, *aux = NULL, *end = NULL;
	//Confere se há espaços livres antes do nó procurado
	//para serem concatenados.
	if(candidate->previous != NULL)
		begin = candidate->previous;
	//Caso o espaço livre, candidato para mesclar, não seja o ultimo da lista.
	if(candidate->next != NULL){
		end = candidate->next;
		while(begin->next != end->next){
			if(begin->free == 1 && begin->next->free == 1){
				begin->size += begin->next->size;
				aux= begin->next;
				begin->next = begin->next->next;
				if(begin->next != NULL)
					begin->next->previous = begin;
				free(aux);
			}else{
				begin = begin->next;
			}
		}
	//Caso o espaço livre, candidato para mesclar, seja o ultimo da lista.
	}else{
		while(begin->next != end){
			if(begin->free == 1 && begin->next->free == 1){
				begin->size += begin->next->size;
				aux= begin->next;
				begin->next = begin->next->next;
				if(begin->next != NULL)
					begin->next->previous = begin;
				free(aux);
			}else{
				begin = begin->next;
			}
		}
	}

}
