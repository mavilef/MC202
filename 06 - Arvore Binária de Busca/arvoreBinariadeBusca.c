#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct binaryTreeNode{

  int data;
  struct binaryTreeNode *left;
  struct binaryTreeNode *right;

} binaryTreeNode;


int insertElementIntheTree(binaryTreeNode **root, int elementToAdd);
int searchElementIntheTree(binaryTreeNode *root, int elementToSearch);
binaryTreeNode *deleteElementIntheTree(binaryTreeNode *root, int elementToDelete);
int minimumElement(binaryTreeNode *root);
int maximumElement(binaryTreeNode *root);
void postOrderTraversal(binaryTreeNode *root);
void inOrderTraversal(binaryTreeNode *root);
void preOrderTraversal(binaryTreeNode *root);

int main(){

  char operation[50];
  binaryTreeNode *root = NULL;

  while(scanf("%s", operation) != EOF){

    if(!strcmp(operation, "inserir")){
      int element;
      scanf("%d", &element);
      insertElementIntheTree(&root, element);

    }else if(!strcmp(operation, "excluir")){
      int element;
      scanf("%d", &element);
      deleteElementIntheTree(root, element);


    }else if(!strcmp(operation, "buscar")){
      int element;
      scanf("%d", &element);
      searchElementIntheTree(root, element);


    }else if(!strcmp(operation, "minimo")){


    }else if(!strcmp(operation, "maximo")){


    }else if(!strcmp(operation, "pos-ordem")){


    }else if(!strcmp(operation, "em-ordem")){


    }else if(!strcmp(operation, "pre-ordem")){


    }else if(!strcmp(operation, "largura")){

    }else if(!strcmp(operation, "terminar")){


    }


  }

  return 0;
}

int insertElementIntheTree(binaryTreeNode **root, int elementToAdd){

  binaryTreeNode *newNode = malloc(sizeof(binaryTreeNode));
  if(newNode == NULL){
    printf("memoria insuficiente\n");
    return 0;
  }

  newNode->data = elementToAdd;
  newNode->left = NULL;
  newNode->right = NULL;

  if((*root) == NULL)
      (*root) = newNode;

  if((*root)->data > elementToAdd)
    insertElementIntheTree((&(*root)->right), elementToAdd);
  else if((*root)->data < elementToAdd)
    insertElementIntheTree((&(*root)->left), elementToAdd);

    return 1;
}

int searchElementIntheTree(binaryTreeNode *root, int elementToSearch){
  if(root == NULL){
    return 0;
  }else{
    while(root != NULL){
      if(elementToSearch == root->data){
        printf("pertence\n");
        return 1;
      }else if(elementToSearch > root->data){
        root = root->left;
      }else{
        root = root->right;
      }
    }
    printf("nao pertence\n");
    return 0;
  }

}

binaryTreeNode* deleteElementIntheTree(binaryTreeNode *root , int elementToDelete){

  binaryTreeNode *aux = NULL;

  if(root == NULL){
    return root;
  }else if(root->data > elementToDelete){
    root->left = deleteElementIntheTree(root->left, elementToDelete);
  }else if(root->data < elementToDelete){
    root->right = deleteElementIntheTree(root->right, elementToDelete);
  }else{
    if(root->left != NULL && root->right != NULL){
      aux = root->left;
      while(aux->right != NULL)
        aux = aux->right;
      root->data =  aux->data;
      root->left = deleteElementIntheTree(root->left, root->data);
    }else{
      aux = root;
      if(root->left == NULL)
        root = root->right;
      if(root->right == NULL)
        root = root->left;
        free(aux);
    }
  }

  return root;

}

int minimumElement(binaryTreeNode *root){
  if(root == NULL)
    return 0;
  if(root->left == NULL)
    return root->data;
  while(root->left != NULL)
    root = root->left;

  return root->data;
}

int maximumElement(binaryTreeNode *root){
  if(root == NULL)
    return 0;
  if(root->right == NULL)
    return root->data;
  while(root->right != NULL)
    root = root->right;

  return root->data;
}

void postOrderTraversal(binaryTreeNode *root){

  if(root == NULL)
    return;
  preOrderTraversal(root->left);
  preOrderTraversal(root->right);
  printf("%d ", root->data);

}

void inOrderTraversal(binaryTreeNode *root){

  if(root == NULL)
    return;
  preOrderTraversal(root->left);
  printf("%d ", root->data);
  preOrderTraversal(root->right);

}

void preOrderTraversal(binaryTreeNode *root){
  if(root == NULL)
    return;
  printf("%d ", root->data);
  preOrderTraversal(root->left);
  preOrderTraversal(root->right);

}

void levelOrderTraversal(binaryTreeNode *root){



}
