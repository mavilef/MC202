#ifndef archives
#define  archives

//Representa cada arquivo da lista.
struct NODE{
	char arqName[11];
	int size;
	struct NODE *next;
	struct NODE *previous;
	//representa se tal arquivo é um espaço em livre ou não.
	int free;
};

typedef struct NODE NODE;

//Representa o Disco
struct DISK{
	//Tamanho total do disco.
	int diskSize;
	//Ponteiro para a cabeça da lista que representa o conteudo do disco.
	struct NODE *listHead;
	//Indicador caso o Disco haja erro por disco cheio.
	int error;

};

typedef struct DISK DISK;

//Representa uma célula do disco, ou seja, um Bloco de 1/8 do tamanho total
//do disco.
//Nota: struct usada somente na função EstimateUsage, usada para imprimir na tela
//o estado do disco em cada oitavo.
struct DISKUSAGE{

	int total;
	int freeSize;
	int usedSize;

};

typedef struct DISKUSAGE DISKUSAGE;


void diskInitializer(DISK **drive, int freeSpace);
void ArchiveInsertion(DISK *drive, char archiveName[], int ArchiveSize);
void ArchiveRemover(DISK *drive, char archiveName[]);
void otimize(DISK *drive);
void EstimateUsage(DISK *drive);
void printState(DISKUSAGE counter);
void freeTheDisk(DISK **drive);
void otimizeTest(DISK *drive);
void catenateFreeSpaces(NODE *candidate);

#endif
