
#include <stdlib.h>
#include <stdio.h>
#ifndef TYPE_VERTEX
#define TYPE_VERTEX int
#endif

typedef struct {
  size_t vertexIndex;
  int weight;
} Data;
#define TYPE_LIST Data
#include "list.h"
#undef TYPE_VECTOR
typedef list_Data* ptrList;
#define TYPE_VEC ptrList
#include "vector.h"
#undef TYPE_VEC
  

#define TOKEN_PAST(x,y) x##y
#define GRAPH(TYPE) TOKEN_PAST(Graph_, TYPE)
#define GET_NAME_OP_GRAPH(x, y) graph_##x##_##y
#define GRAPH_OP(TYPE, OPERATION) GET_NAME_OP_GRAPH(TYPE, OPERATION)
typedef struct{
  vector_ptrList* graph;
  } GRAPH(TYPE_VERTEX);

GRAPH(TYPE_VERTEX)* GRAPH_OP(TYPE_VERTEX, init)( size_t initSize)
{
  GRAPH(TYPE_VERTEX)* Graph = malloc(sizeof(GRAPH(TYPE_VERTEX)));
  Graph->graph = vector_ptrList_init(initSize);
  for( int i = 0; i != initSize; ++i)
    {
      // For debugging purpose: 
      printf("Size : %u , capacity : %u \n", vector_ptrList_size(Graph->graph), vector_ptrList_capacity(Graph->graph));
      vector_ptrList_push_back(Graph->graph, list_Data_init());
    }
  return Graph;
}

void GRAPH_OP(TYPE_VERTEX, add_edge)(GRAPH(TYPE_VERTEX)* Graph, size_t src, size_t dst, int weight)
{
  if( src >= vector_ptrList_size(Graph->graph) &&  dst >= vector_ptrList_size(Graph->graph))
    {
      printf("Invalid value :  out of bound !");
      return ;
    }
  if(weight < 0)
    weight = -1;
  Data newData = {dst, weight};
  list_Data_addElem( vector_ptrList_at(Graph->graph, src), newData);
  
}
void GRAPH_OP(TYPE_VERTEX, print)(GRAPH(TYPE_VERTEX)* Graph)
{
  int i = 0;
  for( ptrList *it = vector_ptrList_begin(Graph->graph), *end = vector_ptrList_end(Graph->graph); it != end; ++it)
    {
      for( list_Data_node* list_it = (*it)->head; list_it != NULL;)
	{
	  printf("(%u -> %u ) : weight = %d\n", i, list_it->data.vertexIndex, list_it->data.weight);
	  list_it = list_it->next;
	}
      ++i;
    }
}
void GRAPH_OP(TYPE_VERTEX, free)(GRAPH(TYPE_VERTEX)* Graph)
{
  for(ptrList *it = vector_ptrList_begin(Graph->graph), *end = vector_ptrList_end(Graph->graph); it != end ; ++it)
    {
      list_Data_free(*it);
    }
  vector_ptrList_free(Graph->graph);
  free(Graph);
}
void GRAPH_OP(TYPE_VERTEX, add_vertex)(GRAPH(TYPE_VERTEX)* Graph)
{
  ptrList newList = list_Data_init();
  vector_ptrList_push_back(Graph->graph, newList); 
}
