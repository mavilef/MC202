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

int main(){

  char operation[50];
  binaryTreeNode *root = NULL;

  while(scanf("%s", operation) != EOF && strcmp(operation, "terminar") != 0){
    if(!strcmp(operation, "inserir")){
      int element;
      scanf("%d", &element);
      insertElementIntheTree(&root, element);

    }else if(!strcmp(operation, "excluir")){
      int element;
      scanf("%d", &element);
    //  deleteElementIntheTree(&root, element);


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
