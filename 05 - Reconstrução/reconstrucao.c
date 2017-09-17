//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SETSIZE 53

typedef struct treeNode {

    char letter;
    struct treeNode *left;
    struct treeNode *right;

} treeNode;

treeNode *rebuildTree(char *preOrder, char *inOrder, int sequenceStart, int sequenceEnd, int **idx);
void postOrderPrint(treeNode * tree);
void destroyTree(treeNode * tree);

int main()
{
  //declarações:
  //*preOrderSequence é uma string que armazenará o input de pré-ordem.
  //*InOrderSequence é uma string que armazenará o input de em-ordem.
  //*tree será a raiz da arvore binária e apartir dela estruturaremos a arvore
  //idx é uma variável que servira para alterar indices durante a recursão
  //do rebuildTree.É utilizada como ponteiro para zerarmos de uma entrada para outra, mas não
  //durante as chamadas, ou seja a cada chamada(independente se for esquerda ou direita) idx é sempre acrescido.


    char *preOrderSequence = malloc(SETSIZE*sizeof(char));
    char *inOrderSequence = malloc(SETSIZE*sizeof(char));
    treeNode *tree = NULL;
	int *idx = malloc(sizeof(int));
    //leitura dos inputs até o fim do buffer de entrada.
    while (scanf("%s %s", preOrderSequence, inOrderSequence) != EOF) {
  		idx[0] = 0;
      //reconstrução da arvore apartir de preOrderSequence e InOrderSequence.
  		tree = rebuildTree(preOrderSequence, inOrderSequence, 0, strlen(preOrderSequence) - 1, &idx);
      //imprimir em pós ordem
  		postOrderPrint(tree);
      //destruir a arvore.
  		destroyTree(tree);
     	 tree = NULL;
  		printf("\n");
    }

	free(preOrderSequence);
	free(inOrderSequence);
	free(idx);
    return 0;
}


//reconstrução da arvore, aqui a lógica é usar as informações de pré-ordem e
//em-ordem para gerar a arvore que as construiu.Sabemos que o primeiro caracter
//de pré ordem é o pai(ou raiz), e as posições á esquerda da mesma chave em
//em-ordem são os filhos á esquerda, do selecionado em pré-ordem, assim como
//os da direita, estão á direita da chave de em-ordem.
//Dentro dos filhos á direita e á esquerda aplicamos o mesmo algoritmo,
//obtendo os outros pais e filhos recursivamente..
treeNode *rebuildTree(char *preOrder, char *inOrder, int sequenceStart, int sequenceEnd, int **idx){

    //checa se estamos ultrapassando os limites da string, caso esteja não coloca
    //nada no nó(NULL).
    if (sequenceStart > sequenceEnd)
		  return NULL;
    //Armazena o indice do meio da string analisada
    int nextEnd = 0;
    //alocação do novo elemento e seleciona elemento em pré ordem.
    treeNode *newElement = malloc(sizeof(treeNode));
    newElement->letter = preOrder[(*idx)[0]];
    newElement->left = NULL;
    newElement->right = NULL;
	(*idx)[0]++;

    //quando a string analisada só possui um elemento.
    if (sequenceStart == sequenceEnd)
		  return newElement;

    int i;
    //encontra em em-ordem a primeira chave de pré ordem selecionada.
    for (i = sequenceStart; i <= sequenceEnd; i++)
  		if (newElement->letter == inOrder[i]) {
  		    nextEnd = i;
  		    break;
  		}
    //preenche recursivamente os filhos de cada nó.
    newElement->left = rebuildTree(preOrder, inOrder, sequenceStart, nextEnd - 1, idx);
    newElement->right = rebuildTree(preOrder, inOrder, nextEnd + 1, sequenceEnd, idx);
    return newElement;

}

//Percorre a arvore no algoritmo pós ordem para impressão.
void postOrderPrint(treeNode *tree){

    if (tree == NULL)
		  return;

    postOrderPrint(tree->left);
    postOrderPrint(tree->right);
    printf("%c", tree->letter);

}

//Percorre a arvore no algoritmo pós ordem liberar cada nó da arvore.
void destroyTree(treeNode *tree){

    if (tree == NULL)
		  return;

    destroyTree(tree->left);
    destroyTree(tree->right);
    free(tree);

}
