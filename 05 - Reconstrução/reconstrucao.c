#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct treeNode{
  char letter;
  struct treeNode *left;
  struct treeNode *right;
} treeNode;

treeNode *rebuildTree(char *preOrder, char *inOrder, int sequenceStart, int sequenceEnd);
void postOrderPrint(treeNode *tree);
void destroyTree(treeNode *tree);

int idx;

int main(){

  char preOrderSequence[53], inOrderSequence[53];
  treeNode *tree = NULL;
  while(scanf("%s %s", preOrderSequence, inOrderSequence) != EOF){
    idx = 0;
    tree = rebuildTree(preOrderSequence, inOrderSequence, 0, strlen(preOrderSequence) - 1);
    postOrderPrint(tree);
    destroyTree(tree);
    printf("\n");
}

  return 0;
}



treeNode *rebuildTree(char *preOrder, char *inOrder, int sequenceStart, int sequenceEnd){

  if(sequenceStart > sequenceEnd)
    return NULL;

  int nextEnd = 0;
  treeNode *newElement = malloc(sizeof(treeNode));
  newElement->letter = preOrder[idx++];
  newElement->left = NULL;
  newElement->right = NULL;

  if(sequenceStart == sequenceEnd)
    return newElement;

  int i;
  for(i = sequenceStart; i <= sequenceEnd; i++)
    if(newElement->letter == inOrder[i]){
      nextEnd = i;
      break;
    }

  newElement->left = rebuildTree(preOrder, inOrder, sequenceStart, nextEnd - 1);
  newElement->right = rebuildTree(preOrder, inOrder, nextEnd + 1, sequenceEnd);
  return newElement;

}

void postOrderPrint(treeNode *tree){

  if(tree == NULL)
    return;

  postOrderPrint(tree->left);
  postOrderPrint(tree->right);
  printf("%c", tree->letter);

}

void destroyTree(treeNode *tree){

  if(tree == NULL)
    return;

  destroyTree(tree->left);
  destroyTree(tree->right);
  free(tree);

}
