#ifndef archives
#define  archives

#include "listFunctions.c"

struct NODE{
	char arqName[11];
	int size;
	struct NODE *next;
	struct NODE *previous;
}


typedef struct NODE NODE;

struct DISK{

	int freeSpace;
	struct NODE *listHead;
	struct NODE *listTail;

}

typedef struct DISK DISK;

void diskInitializer(DISK **drive, int freeSpace);
void sizeConversor(char size[]);


#endif