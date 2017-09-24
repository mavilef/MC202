//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct binaryTreeNode{

  int data;
  struct binaryTreeNode *left;
  struct binaryTreeNode *right;

} binaryTreeNode;

typedef struct list{

  binaryTreeNode *node;
  struct list *next;

} list;

typedef struct queue{

  list *head;
  list *tail;

} queue;

binaryTreeNode* insertElementIntheTree(binaryTreeNode *root, int elementToAdd);
void searchElementIntheTree(binaryTreeNode *root, int elementToSearch);
binaryTreeNode *deleteElementIntheTree(binaryTreeNode *root, int elementToDelete);
void minimumElement(binaryTreeNode *root);
void maximumElement(binaryTreeNode *root);
void postOrderTraversal(binaryTreeNode *root);
void inOrderTraversal(binaryTreeNode *root);
void preOrderTraversal(binaryTreeNode *root);
void levelOrderTraversal(binaryTreeNode *root);
void destroyTree(binaryTreeNode *root);
void enqueue(queue *Queue, binaryTreeNode *node);
binaryTreeNode* dequeue(queue *Queue);

int main(){

  //Declarações:
  //operation lerá a string que corresponde a operação.
  //root raiz da arvore.
  char operation[50];
  binaryTreeNode *root = NULL;

  while(scanf("%s", operation) != EOF){

    if(!strcmp(operation, "inserir")){
      int element;
      if(scanf("%d", &element))
        root = insertElementIntheTree(root, element);
      else
        printf("Erro na leitura do elemento(inserção)");

    }else if(!strcmp(operation, "excluir")){
      int element;
      if(scanf("%d", &element))
        root = deleteElementIntheTree(root, element);
      else
        printf("Erro na leitura do elemento(excluir)");

    }else if(!strcmp(operation, "buscar")){
      int element;

      if(scanf("%d", &element))
        searchElementIntheTree(root, element);
      else
        printf("Erro na leitura do elemento(busca)");

    }else if(!strcmp(operation, "minimo")){
      minimumElement(root);

    }else if(!strcmp(operation, "maximo")){
      maximumElement(root);

    }else if(!strcmp(operation, "pos-ordem")){
      if(root)
        postOrderTraversal(root);
      else
        printf("vazia");
      printf("\n");

    }else if(!strcmp(operation, "em-ordem")){
      if(root)
        inOrderTraversal(root);
      else
        printf("vazia");
      printf("\n");

    }else if(!strcmp(operation, "pre-ordem")){
      if(root)
        preOrderTraversal(root);
      else
        printf("vazia");
      printf("\n");

    }else if(!strcmp(operation, "largura")){
      if(root)
        levelOrderTraversal(root);
      else
        printf("vazia");
      printf("\n");


    }else if(!strcmp(operation, "terminar")){
      destroyTree(root);
      break;
    }


  }

  return 0;
}

//insertElementIntheTree faz a inserção de Elementos na arvore, seguindo
//a propriedade da arvore binária de busca onde, se o elemento é maior
// é colocado a direita, se for menor , á esquerda.
binaryTreeNode* insertElementIntheTree(binaryTreeNode *root, int elementToAdd){

  //primeira inserção na arvore(sem nós)
  if(root == NULL){
    root = malloc(sizeof(binaryTreeNode));
    if(root == NULL){
      printf("memoria insuficiente\n");
    }else{

      root->data = elementToAdd;
      root->left = NULL;
      root->right = NULL;
    }

  //demais nós
  }else{

    if(elementToAdd < root->data)
      root->left =  insertElementIntheTree(root->left, elementToAdd);
    else if(elementToAdd > root->data)
      root->right = insertElementIntheTree(root->right, elementToAdd);
  }
  return root;
}

//busca de elementos na arvore.
void searchElementIntheTree(binaryTreeNode *root, int elementToSearch){
  if(root == NULL){
    printf("nao pertence\n");
    return;
  }else{
    while(root != NULL){
      if(elementToSearch == root->data){
        printf("pertence\n");
        return;
      }else if(elementToSearch > root->data){
        root = root->right;
      }else{
        root = root->left;
      }
    }
    printf("nao pertence\n");
    return;
  }

}

//exclusão de elementos na arvore.
binaryTreeNode* deleteElementIntheTree(binaryTreeNode *root , int elementToDelete){

  binaryTreeNode *aux = NULL;

  if(root == NULL){
    return root;
  }else if(elementToDelete > root->data){

    //encontrar o elemento recursivamente.
    root->right = deleteElementIntheTree(root->right, elementToDelete);
  }else if(elementToDelete < root->data){
    //encontrar o elemento recusivamente.
    root->left = deleteElementIntheTree(root->left, elementToDelete);
  }else{
    //Nesse ponto encontramos o nó a ser apagado.
    if(root->left == NULL){
      aux = root->right;
      free(root);
      return aux;
    }else if(root->right == NULL){
      aux = root->left;
      free(root);
      return aux;
    }
    aux = root->right;
    //encontra o sucessor do elemento
    while(aux->left != NULL)
      aux = aux->left;
    //substitui o elemento a ser deletado pelo sucessor.
    root->data =  aux->data;
    //exclui o nó do sucessor.
    root->right = deleteElementIntheTree(root->right, root->data);

  }

  return root;

}

//minimumElement procura o menor elemento da arvore/subarvore.
//o menor elemento é sempre o elemento mais a esquerda da arvore,
//conforme propriedade da arvore binaria de busca.
void minimumElement(binaryTreeNode *root){
  if(root == NULL){
    printf("vazia\n");
    return;
  }
  if(root->left == NULL){
    printf("%d\n", root->data);
    return;
  }
  //chega no elemento mais a esquerda
  //percorrendo iterativamente.
  while(root->left != NULL)
    root = root->left;

  printf("%d\n", root->data);
}

//maximumElement procura o maior elemento da arvore/subarvore.
//o maior elemento é sempre o elemento mais a direita da arvore,
//conforme propriedade da arvore binaria de busca.
void maximumElement(binaryTreeNode *root){
  if(root == NULL){
    printf("vazia\n");
    return;
  }
  if(root->right == NULL){
    printf("%d\n", root->data);
    return;
  }
  //chega no elemento mais a esquerda
  //percorrendo iterativamente.
  while(root->right != NULL)
    root = root->right;

  printf("%d\n", root->data);
}

//postOrderTraversal percorre a lista recursivamente,
//de acordo com o método pós-ordem.
void postOrderTraversal(binaryTreeNode *root){

  if(root == NULL)
    return;
  postOrderTraversal(root->left);
  postOrderTraversal(root->right);
  printf("%d ", root->data);

}

//inOrderTraversal percorre a lista recursivamente,
//de acordo com o método em-ordem.
void inOrderTraversal(binaryTreeNode *root){

  if(root == NULL)
    return;
  inOrderTraversal(root->left);
  printf("%d ", root->data);
  inOrderTraversal(root->right);

}

//preOrderTraversal percorre a lista recursivamente,
//de acordo com o método pré-ordem.
void preOrderTraversal(binaryTreeNode *root){
  if(root == NULL)
    return;
  printf("%d ", root->data);
  preOrderTraversal(root->left);
  preOrderTraversal(root->right);

}

//levelOrderTraversal percorre a lista iterativamente,
//visitando os nós por nivel.
//Tal função foi feita iterativamente, utilizando filas,
//e duas funções da fila: enfileirar(enqueue) e desinfileirar(dequeue);
//basicamente a fila vai armazenando os nós(endereços) de cada nivel em ordem,
//desinfileirando, obtendo os filhos de cada nó, após o desinfileiramento.
void levelOrderTraversal(binaryTreeNode *root){

  binaryTreeNode *aux = root;
  //criação da fila.
  queue *Queue = malloc(sizeof(queue));
  Queue->head = NULL;
  Queue->tail = NULL;

  enqueue(Queue, root);

  while(Queue->head != NULL){
    aux = dequeue(Queue);
    printf("%d ", aux->data);
    if(aux->left != NULL)
      enqueue(Queue, aux->left);
    if(aux->right != NULL)
      enqueue(Queue, aux->right);
  }
  free(Queue);
}

//destroyTree libera a memoria de todos os nós da arvore,
//segue o pós-ordem porém liberando memoria.
void destroyTree(binaryTreeNode *root){

    if (root == NULL)
		  return;

    destroyTree(root->left);
    destroyTree(root->right);
    free(root);

}

//função de enfileirar.
void enqueue(queue *Queue, binaryTreeNode *node){

  list *newElement = malloc(sizeof(list));
  if(newElement == NULL){
    printf("Erro ao enfileirar\n");
    return;
  }

  newElement->node = node;
  newElement->next = NULL;

  if(Queue->head == NULL)
    (Queue->tail) = (Queue->head) = newElement;
  else{
    (Queue->tail)->next = newElement;
    (Queue->tail) = (Queue->tail)->next;
  }

}

//desinfileirar
binaryTreeNode* dequeue(queue *Queue){
  if(Queue->head == NULL)
    return NULL;

  list *aux = NULL;
  binaryTreeNode *aux2 = NULL;
  aux2 = (Queue->head)->node;
  aux = (Queue->head);
  (Queue->head) = (Queue->head)->next;
  free(aux);

  return aux2;

}
