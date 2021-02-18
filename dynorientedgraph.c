#include <stdlib.h>
#include <stdio.h>
/* Multi oriented graph

 */
typedef struct
{
  unsigned char source, destination;
  // Data
  int weight; // for unweight graph -> weight = 1
} Edge;
typedef struct _vertice
{
  Edge** omegaplus;
  Edge **first_free, **cap;
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
  myNewVerctice->omegaplus = NULL; // Points nowhere at the beginning
  myNewVerctice->first_free = NULL;
  myNewVerctice->cap = NULL;
  myNewVerctice->weight = -1;
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
unsigned char reallocate(Verctice *v, unsigned char new_size)
{
  Edge **newTab = realloc( v->omegaplus, new_size * sizeof(Edge*));
  if(!newTab)
    {
      printf("Realloc failed ! \n");
      return 0;
    }
  // Update Pointer
  v->cap = v->omegaplus + new_size;
  printf("Realloc successful ! \n");
  return 1;
}
void chk_n_alloc(Graph *g,unsigned char source)
{
  unsigned char size = g->head[source]->first_free - g->head[source]->omegaplus;
  unsigned char capacity = g->head[source]->cap - g->head[source]->omegaplus;
  if(size == capacity)
    {
  unsigned char new_size = size ? 2*size : 1;
  reallocate(g->head[source], new_size);
    }
}
void pushBackEdge(Graph *g, Edge *e, unsigned char source, unsigned char destination)
{
  chk_n_alloc(g, source);
  g->head[source]->first_free[] = e;
  
}
void makeEdge(Graph* graph, unsigned char source, unsigned char destination)
{
  Edge* myNewEdge = malloc(sizeof(Edge)); // Create Edge on the heap
  myNewEdge->source  = source;         // Init data members
  myNewEdge->destination = destination;
  pushBackEdge(graph, myNewEdge, source , destination);
  /*  Edge** it = graph->head[source]->omegaplus;
  for(; *it != NULL; ++it)
    ;
  *it = myNewEdge;
  */
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
