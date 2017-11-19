//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<string.h>
#include"interface.h"


int sizeConversor(char textSize[]);

int main(){

	//declaraçoes:
	//numberOfOperations é o numero de operações por disco.
	//numberOfOperations = 0 também é condição de parada da leitura.
	//sizeArq e sizeDisk são as strings que representam os tamanhos do Arquivo
	//e do disco respectivamente.
	//SizeArqNum e sizeDiskNum são os valores numéricos(em Kb) que representam os
	//tamanhos do Arquivo e do disco, respectimente.
	//operation é a string que representa a operação a ser realizada no disco(insere
	//remove ou otimiza).

	int numberOfOperations, sizeDiskNum, sizeArqNum, j = 0;
	char operation[8], arqName[11], sizeArq[7], sizeDisk[7];

	//DISK é uma struct que contém informações sobre o disco.
	//contém o tamango do disco, um ponteiro para o começo da lista de arquivos
	//uma flag que indica se o disco está cheio.
	DISK *drive = NULL;

	//leitura das entradas
	while(scanf("%d", &numberOfOperations) && numberOfOperations != 0){
		scanf("%s", sizeDisk);
			//conversão da string do tamanho para um inteiro(em Kb).
		sizeDiskNum = sizeConversor(sizeDisk);
			//inicialização das informações do novo disco.
		diskInitializer(&drive, sizeDiskNum);

		for(j = 0; j < numberOfOperations; j++){
			scanf("%s", operation);

			if(strcmp(operation, "insere") == 0){
				scanf("%s", arqName);
				scanf("%s", sizeArq);
					//conversão da string do tamanho para um inteiro(em Kb).
				sizeArqNum = sizeConversor(sizeArq);
					//Verificação de disco cheio.
				if(drive->error == 0)
					ArchiveInsertion(drive, arqName, sizeArqNum);
			}else if(strcmp(operation, "remove") == 0){
				scanf("%s", arqName);
					//Verificação de disco cheio.
				if(drive->error == 0)
					ArchiveRemover(drive, arqName);
			}else if(strcmp(operation, "otimiza") == 0){
					//Verificação de disco cheio.
				if(drive->error == 0)
					otimize(drive);
			}else{
				printf("Operacao Inexistente, digite uma operacao valida.\n");
				printf("Tente: insere <nome> <tamanho>, remove <nome> ou otimiza\n");
				j--;
			}

		}

		if(drive->error == 0)
			EstimateUsage(drive);
		else if(drive->error == 1)
			printf("ERRO: disco cheio\n");

	}
		//libera memoria do ultimo disco inicializado.
	freeTheDisk(&drive);
	return 0;
}


//faz a conversão de uma string que representa um tamanho de bytes
//em um valor numérico representando o tamanho em Kb.
int sizeConversor(char textSize[]){

	int size = strlen(textSize);
	int power = 0, coeficient = 0, j = 1 ,i = 0;

	for (i = size; i >= 0; i--){
		if(textSize[i] == 'b')
			continue;
		else if(textSize[i] > 64 && textSize[i] < 91){

			if(textSize[i] == 'M')
				power = 10;
			if(textSize[i] == 'G')
				power = 20;

		}else if(textSize[i] > 47 && textSize[i] < 58){

			coeficient = coeficient + (textSize[i] - '0')*j;
			j*=10;

		}

	}
		size = coeficient*(1 << power);

	return size;
}
