#ifndef archives
#define  archives

struct NODE{
	char arqName[11];
	int size;
	struct NODE *next;
	struct NODE *previous;
	int free;
};


typedef struct NODE NODE;

struct DISK{

	int diskSize;
	struct NODE *listHead;
	int error;

};

typedef struct DISK DISK;

void diskInitializer(DISK **drive, int freeSpace);
void ArchiveInsertion(DISK *drive, char archiveName[], int ArchiveSize);
void ArchiveRemover(DISK *drive, char archiveName[]);
void catenateFreeSpaces(DISK *drive);
void otimize(DISK *drive);

#include"listFunctions.c"

#endif
