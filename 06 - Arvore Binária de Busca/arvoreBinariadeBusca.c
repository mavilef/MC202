#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct binaryTreeNode{

  int data;
  struct binaryTreeNode *left;
  struct binaryTreeNode *right;

} binaryTreeNode;

typedef struct queue{
  int cap;
  int size;
  binaryTreeNode *vector;

} queue;

binaryTreeNode* insertElementIntheTree(binaryTreeNode *root, int elementToAdd);
void searchElementIntheTree(binaryTreeNode *root, int elementToSearch);
binaryTreeNode *deleteElementIntheTree(binaryTreeNode *root, int elementToDelete);
void minimumElement(binaryTreeNode *root);
void maximumElement(binaryTreeNode *root);
void postOrderTraversal(binaryTreeNode *root);
void inOrderTraversal(binaryTreeNode *root);
void preOrderTraversal(binaryTreeNode *root);
void destroyTree(binaryTreeNode *root);

int main(){

  char operation[50];
  binaryTreeNode *root = NULL;
  int numberOfnodes = 0;

  while(scanf("%s", operation) != EOF){

    if(!strcmp(operation, "inserir")){
      int element;
      scanf("%d", &element);
      root = insertElementIntheTree(root, element);

    }else if(!strcmp(operation, "excluir")){
      int element;
      scanf("%d", &element);
      root = deleteElementIntheTree(root, element);


    }else if(!strcmp(operation, "buscar")){
      int element;
      scanf("%d", &element);
      searchElementIntheTree(root, element);


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

    }else if(!strcmp(operation, "terminar")){
      destroyTree(root);
      break;
    }


  }

  return 0;
}

binaryTreeNode* insertElementIntheTree(binaryTreeNode *root, int elementToAdd){

  if(root == NULL){
    root = malloc(sizeof(binaryTreeNode));
    if(root == NULL){
      printf("memoria insuficiente\n");
    }else{

      root->data = elementToAdd;
      root->left = NULL;
      root->right = NULL;
    }

  }else{

    if(elementToAdd < root->data)
      root->left =  insertElementIntheTree(root->left, elementToAdd);
    else if(elementToAdd > root->data)
      root->right = insertElementIntheTree(root->right, elementToAdd);
  }
  return root;
}

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

binaryTreeNode* deleteElementIntheTree(binaryTreeNode *root , int elementToDelete){

  binaryTreeNode *aux = NULL;

  if(root == NULL){
    return root;
  }else if(elementToDelete > root->data){
    root->right = deleteElementIntheTree(root->right, elementToDelete);
  }else if(elementToDelete < root->data){
    root->left = deleteElementIntheTree(root->left, elementToDelete);
  }else{

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
    while(aux->left != NULL)
      aux = aux->left;

    root->data =  aux->data;
    root->right = deleteElementIntheTree(root->right, root->data);

  }

  return root;

}

void minimumElement(binaryTreeNode *root){
  if(root == NULL){
    printf("vazia\n");
    return;
  }
  if(root->left == NULL){
    printf("%d\n", root->data);
    return;
  }
  while(root->left != NULL)
    root = root->left;

  printf("%d\n", root->data);
}

void maximumElement(binaryTreeNode *root){
  if(root == NULL){
    printf("vazia\n");
    return;
  }
  if(root->right == NULL){
    printf("%d\n", root->data);
    return;
  }
  while(root->right != NULL)
    root = root->right;

  printf("%d\n", root->data);
}

void postOrderTraversal(binaryTreeNode *root){

  if(root == NULL)
    return;
  postOrderTraversal(root->left);
  postOrderTraversal(root->right);
  printf("%d ", root->data);

}

void inOrderTraversal(binaryTreeNode *root){

  if(root == NULL)
    return;
  inOrderTraversal(root->left);
  printf("%d ", root->data);
  inOrderTraversal(root->right);

}

void preOrderTraversal(binaryTreeNode *root){
  if(root == NULL)
    return;
  printf("%d ", root->data);
  preOrderTraversal(root->left);
  preOrderTraversal(root->right);

}

void levelOrderTraversal(binaryTreeNode *root){

  binaryTreeNode *aux = root;
  queue levelOrderQueue;
  levelOrderQueue->cap = 2;
  levelOrderQueue->size = 1
  levelOrderQueue->vector = calloc(2*sizeof(binaryTreeNode));

  levelOrderQueue->vector[0] = aux; 
  while(size != 0){
    aux = levelOrderQueue->vector[0];
    printf("%d ", aux->data);
    levelOrderQueue->vector[]




  }

}

void destroyTree(binaryTreeNode *root){

    if (root == NULL)
		  return;

    destroyTree(root->left);
    destroyTree(root->right);
    free(root);

}
