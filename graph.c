#define TYPE_VERTEX int
#include "graph.h"
#undef TYPE_VERTEX

int main()
{
  Graph_int* myGraph = graph_int_init(5);
   graph_int_add_edge(myGraph,0,2, -1);
  graph_int_print(myGraph);
  graph_int_free(myGraph);
}
