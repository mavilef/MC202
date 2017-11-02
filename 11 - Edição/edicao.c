//Marcelo Martins Vilela Filho RA 202619 - Engenharia de Computação
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define WORDSIZE 21
#define DICTIONARYSIZE 20000

//struct dos indices ddos vizinhos de um vertice.
typedef struct listNode{
  //indice do vizinho ao vertice.
  int neighbor;
  struct listNode *next;

} listNode;

//struct dos vertices do grafo.
typedef struct listHeads{
  //palavra do dicionario.
  char *word;
  //lista com os vizinhos ao vertice.
  listNode *head;
} listHeads;

//struct do grafo.
typedef struct graph{
  //numero de vertices do grafo.
 int verticesNumber;
 //lista dos vertices presentes no grafo.
 struct listHeads *adjList;
} graph;

//fila usada para o BFS.
typedef struct queue{

  listNode *head;
  listNode *tail;

} queue;

int checkEditingStep(char *word1, char *word2);
int insertWord(graph *dictionary, char *word);
void DoTheConnections(graph *dictionary, char *word);
int FindTheLonguestShortestPath(graph *dictionary);
int BFS(graph *dictionary, int begin);
void enqueue(queue *Queue, int element);
int dequeue(queue *Queue);
graph *createGraph();
void IWantToBreakFree(graph **G);

int main(){

  //string que receberá cada palavra a ser adicionada no dicionario.
  char *word = malloc(WORDSIZE*sizeof(char));
  //ponteiro para o grafo que representa o dicionário.
  graph *dictionary;

  //inicialização do dicionario
  dictionary = createGraph();

  while(scanf("%s", word) != EOF){
    //Atualiza as conecções do grafo somente se a inserção for feita com sucesso.
    //, ou seja, se insertWord retornar 0.
    if(!insertWord(dictionary, word)){
      //realiza as conecções entre as palavras e as palavra que são seus passos
      //de edição.Basicamente atribui as arestas do vertice que esta sendo
      //adicionado.
      DoTheConnections(dictionary, word);
    }else{
      printf("Erro ao inserir!\n");
    }

  }
  //encontra o maior caminho entre os vertices, dois a dois e imprime o maior;
  printf("%d\n", FindTheLonguestShortestPath(dictionary));
  free(word);
  //libera memoria alocado pelo grafo.
  IWantToBreakFree(&dictionary);

  return 0;
}

//checa se a diferença entre duas palavras é de um caractere.
//então, retorna 0 caso seja um passo de edição e 1 caso não seja.
int checkEditingStep(char *word1, char *word2){

  if(strlen(word1) == strlen(word2)){
    int counter = 0;
    int size = strlen(word1);
    for(int i = 0; i < size; i++){
      if(word1[i]!=word2[i])
        counter++;
      if(counter > 1)
        return 1;
    }
    if(counter == 1)
      return 0;
  }
  return 1;

}

//inicializa o grafo
graph *createGraph(){
   graph *newG =  malloc(sizeof(graph));
  newG->verticesNumber = 0;

  newG->adjList = malloc(DICTIONARYSIZE * sizeof(listHeads));

  //inicializa o grafo com todos os vertices vazios.
  // o tamanho do grafo entao, será dado pelo campo
  //verticesNumber.
  for (int i = 0; i < DICTIONARYSIZE; i++)
      newG->adjList[i].head = NULL;

  return newG;

}

//insere um vertice no grafo, porém sem adicionar sua arestas.
int insertWord(graph *dictionary, char *word){
  dictionary->adjList[dictionary->verticesNumber].word = malloc(WORDSIZE*sizeof(char));
  if(!strcpy(dictionary->adjList[dictionary->verticesNumber].word, word))
    return 1;
  //atualiza o tamanho do grafo.
  dictionary->verticesNumber++;

  return 0;
}

//adiciona as arestas do vertice recentemente adicionado ao grafo.
void DoTheConnections(graph *dictionary, char *word){

  //visitada o todas as palavras do dicionario.
  for(int i = 0; i < dictionary->verticesNumber - 1; i++){
    //se houver ligação entre a palavra visitada e a palavra,
    //recentemente adicionada, adiciona mais um nó,
    //na lista que grava os vizinhos, com indice do vizinho;
    //*Lembrando que deve-se fazer uma aresta, nos dois vertices que são
    //passos de edição.
    if(!checkEditingStep(dictionary->adjList[i].word, word)){
      //adiciona na palavra visitada.
      listNode *newNode = malloc(sizeof(listNode));
      newNode->neighbor = dictionary->verticesNumber - 1;
      if(dictionary->adjList[i].head != NULL){
        newNode->next = dictionary->adjList[i].head->next;
        dictionary->adjList[i].head->next = newNode;
      //caso há lista de vizinhos esteja vazia.
      }else{
        newNode->next = NULL;
        dictionary->adjList[i].head = newNode;
      }
      //adiciona no grafo recém adicionado.
      newNode = malloc(sizeof(listNode));
      newNode->neighbor = i;

      if(dictionary->adjList[dictionary->verticesNumber - 1].head != NULL){
        newNode->next = dictionary->adjList[dictionary->verticesNumber - 1].head->next;
        dictionary->adjList[dictionary->verticesNumber - 1].head->next = newNode;
      //caso há lista de vizinhos esteja vazia.
      }else{
        newNode->next = NULL;
        dictionary->adjList[dictionary->verticesNumber - 1].head = newNode;
      }

    }
  }
}

//Realiza BFS para cada vertice e retorna a maior distancia entre dois vertices do grafo.
int FindTheLonguestShortestPath(graph *dictionary){
  int biggest = 0, aux;

  //chamada do BFS para cada vertice.
  for(int i = 0; i < dictionary->verticesNumber; i++){
    aux = BFS(dictionary, i);

    if(aux > biggest)
      biggest = aux;
  }
  return biggest;
}

//Busca no grafo por nivel(distancia)
//Basimente enfilera os vizinhos de um nó.
//Visita-os, e para cada visitado, enfilera seus vizinhos não visitados.
//retorna a distancia entre o vertice inicial e o vertice mais distante.
int BFS(graph *dictionary, int begin){
  //inicialização da fila
  queue *Queue = malloc(sizeof(queue));
  Queue->head = NULL;
  Queue->tail = NULL;
  //vetor boleano que grava se m dado vertice foi visitado ou não.
  int *visited = calloc(dictionary->verticesNumber,sizeof(int));
  //vetor de distancia entre o vertice inicial e todos os outros vertices.
  int *distance = calloc(dictionary->verticesNumber,sizeof(int));
  //variavel que grava o a maior distancia.
  int biggest = 0;


  enqueue(Queue, begin);
  visited[begin] = 1;

  //enfileiramento dos vizinhos.
  while(Queue->head != NULL){
    begin = dequeue(Queue);
    for(listNode *aux = dictionary->adjList[begin].head; aux != NULL; aux = aux->next)
      //enfilera somente se os vizinhos do vertice visitado não foram visitados anteriormente.
      if(!visited[aux->neighbor]){
        enqueue(Queue, aux->neighbor);
        visited[aux->neighbor] = 1;
        //atualiza o vetor de distancias.
        //A distancia de um vizinho é sempre a distancia do vertice visitado anteriormente + 1;
        distance[aux->neighbor] += distance[begin] +1;
        //aAtualiza o valor da maior distancia.
        if(distance[aux->neighbor] > biggest)
          biggest = distance[aux->neighbor];
      }
    }

  //libera a fila e os vetores de distancia e de visita.
  free(visited);
  free(distance);
  listNode *aux = Queue->head;
  listNode *aux2;
  while(aux != NULL){
    aux2 = aux;
    aux = aux->next;
    free(aux2);
  }
  free(Queue);

  return biggest;

}

//função de enfileirar dada uma fila.
void enqueue(queue *Queue, int element){

  listNode *newElement = malloc(sizeof(listNode));
  if(newElement == NULL){
    printf("Erro ao enfileirar\n");
    return;
  }

  newElement->neighbor = element;
  newElement->next = NULL;

  if(Queue->head == NULL)
    (Queue->tail) = (Queue->head) = newElement;
  else{
    (Queue->tail)->next = newElement;
    (Queue->tail) = (Queue->tail)->next;
  }

}

//função de desinfileirar dada uma fila.
int dequeue(queue *Queue){
  if(Queue->head == NULL)
    return -1;

  listNode *aux = NULL;
  int aux2;
  aux2 = (Queue->head)->neighbor;
  aux = (Queue->head);
  (Queue->head) = (Queue->head)->next;
  free(aux);

  return aux2;

}

//libera a memoria do grafo.
void IWantToBreakFree(graph **G){
  listNode *aux = NULL, *aux2;
  for(int i = 0; i < (*G)->verticesNumber; i++){
    aux = (*G)->adjList[i].head;
    while(aux != NULL){
      aux2 = aux;
      aux = aux->next;
      free(aux2);
    }
    free((*G)->adjList[i].word);
  }
    free((*G)->adjList);
    free(*G);
}
