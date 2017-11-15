#include<stdio.h>
#include<stdlib.h>
#define ROOMMAX 50

typedef struct EDGE{
	int room;
	struct EDGE *next;
} EDGE;

typedef struct GRAPH{
	unsigned verticesNumber;
	EDGE **edge;
} GRAPH;

GRAPH *initGraph();
void addToGraph(GRAPH *base, int roomA, int roomB);
void refreshWeightAcumulator(int* weightAcumulator, int *edgeWeight, int roomA, int roomB, int distance);

int main(){

	GRAPH *base = initGraph();

	int operations, roomA, roomB, distance;
	int *weightAcumulator = malloc(ROOMMAX*sizeof(int));
	int *edgeWeight = malloc(ROOMMAX*sizeof(int)); 

	while(scanf("%d", &operations) && operations != 0){
		for(int i = 0; i < operations; i++){	
			scanf("%d %d %d", &roomA, &roomB, &distance);
			addToGraph(base, roomA, roomB);
			refreshWeightAcumulator(weightAcumulator , edgeWeight, roomA, roomB, distance);
		}
		printf("%d", customDFS(base, weightAcumulator));
		PrepareForTheNext(base);
	}
	freeGraph(&base);

	return 0;
}

GRAPH *initGraph(){
	GRAPH *new = malloc(sizeof(GRAPH));
	new->verticesNumber = 0;
	new->edge = malloc(ROOMMAX*sizeof(EDGE*));

	return new;
}

void addToGraph(GRAPH *base, int roomA, int roomB){
	EDGE *new = malloc(sizeof(EDGE));
	new->room = roomB;

	for(EDGE *p = base->edge[roomB]; p->next != NULL; p = p->next)

	p->next = new;

}

void refreshWeightAcumulator(int* weightAcumulator, int *edgeWeight, int roomA, int roomB, int distance){
	weightAcumulator[roomA] += distance;
	edgeWeight[roomB] = distance;

}

int customDFS(GRAPH *base, int weightAcumulator){




}
