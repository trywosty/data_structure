#include <stdlib.h>
#include <stdio.h>
/* Minimal oriented simple Graph data structure
   /!\  #E must be equal to #V^2 ! (maybe dynamic growth will be added later)
 */
Graph* createGraph(unsigned char size); // Create Graph with a given number of Verctice
void  makeEdge(Graph *, unsigned char source, unsigned char destination); // Create an edge between two Verctic
void printGraph(Graph *); // Print the Edges of the Graph
void freeGraph(Graph *); /// Free graph
typedef struct
{
  unsigned char source, destination;
} Edge;
typedef struct _vertice
{
  Edge** omegaplus;
  // Data
} Verctice;
typedef struct
{
  Verctice** head;
  unsigned char size;
}Graph;
Verctice* createVerctice(unsigned char size) // Size = #V
{
  Verctice *myNewVerctice = malloc(sizeof(Verctice));
  if(!myNewVerctice)
    return NULL;
  myNewVerctice->omegaplus = malloc(size*size*sizeof(Edge*)); // Points nowhere at the beginning
  for(int i = 0; i < size*size; ++i)
    {
      myNewVerctice->omegaplus[i] = NULL;
    }
  return myNewVerctice;
}
Graph* createGraph(unsigned char size)
{
  Graph *myNewGraph = malloc(sizeof(Graph)); // Create Graph
  if(!myNewGraph)
    return NULL;
  myNewGraph->head = malloc(size*sizeof(Verctice*)); // Create array of pointer to Verctice
  myNewGraph->size = size;
  for(int i = 0; i < size; ++i)
    {
      myNewGraph->head[i] = createVerctice(size); // create init Verctice
      if(!myNewGraph->head[i]){
	for(int j = 0; j < i; ++j)
	  free(myNewGraph->head[j]);
	free(myNewGraph);
	return NULL;
      }
    }
  return myNewGraph;
}
void makeEdge(Graph* graph, unsigned char source, unsigned char destination)
{
  Edge* myNewEdge = malloc(sizeof(Edge)); // Create Edge on the heap
  myNewEdge->source  = source;         // Init data members
  myNewEdge->destination = destination;
  Edge** it = graph->head[source]->omegaplus;
  for(; *it != NULL; ++it)
    ;
  *it = myNewEdge;
  return ;
}
void printGraph(Graph *graph)
{
  for(unsigned char i = 0;  i != graph->size; ++i)
    {
      for( unsigned char j = 0; graph->head[i]->omegaplus[j] != NULL; ++j)
	printf("(%d -> %d)\n", i, graph->head[i]->omegaplus[j]->destination);
    }
}
void freeGraph(Graph *graph) // Note : This function is O(n^3) !!! not optimized
{
  for(int i = 0; i < graph->size; ++i)
    {
    for(int j = 0; j < graph->size * graph->size  ; ++j)
      free(graph->head[i]->omegaplus[j]);
  free(graph->head[i]);
    }
  free(graph);
}
int main()
{
/*
 Let's create this graph

 - - v          |---------------|
 | - 1--------->2<_             v
     ^         / _|             5
     |   _  _ /	 |
     |	 |	 |	
     3<--/       |
     ^---------4-|

*/
  Graph *g = createGraph(5);     
  makeEdge(g, 1, 1);
  makeEdge(g, 1, 2);
  makeEdge(g, 2, 3);
  makeEdge(g, 2, 5);
  makeEdge(g, 3, 1);
  makeEdge(g, 4, 3);
  makeEdge(g, 4, 2);
  printGraph(g);
  freeGraph(g);
}
