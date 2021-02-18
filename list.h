#include <stdlib.h>
#include <stdio.h>
#ifndef TYPE_LIST
#define TYPE_LIST int
#endif
#define GET_NAME_OP(x,y) list_##x##_##y
#define LIST_OP(T, n) GET_NAME_OP(T, n)
#define LIST_NAME(n, T) n##T
#define LIST(T) LIST_NAME(list_, T)
typedef struct LIST_OP(TYPE_LIST, node_)
{
  TYPE_LIST data;
  struct LIST_OP(TYPE_LIST, node_)* next;
  
}LIST_OP(TYPE_LIST, node);

typedef struct {
  LIST_OP(TYPE_LIST, node )* head;

} LIST(TYPE_LIST);
LIST(TYPE_LIST)* LIST_OP(TYPE_LIST, init) (void)
{
  LIST(TYPE_LIST)* new =  malloc(sizeof(LIST(TYPE_LIST)));
		      if ( !new)
			     {
			       printf("Error : can't create list");
				   return NULL;
				 }
	new->head = NULL;
			       return new;
}

void LIST_OP(TYPE_LIST, addNode) (LIST(TYPE_LIST)* list , LIST_OP(TYPE_LIST , node) *node)
    {
      if(!node)
	{
	  printf("Error : empty node !");
	  return;
	}
      LIST_OP(TYPE_LIST, node)* temp  = list->head;
      list->head = node;
      
    }
  LIST_OP(TYPE_LIST, node)*  LIST_OP(TYPE_LIST, createNode) (TYPE_LIST elem)
  {
    LIST_OP(TYPE_LIST, node)* ptrElem = malloc(sizeof(LIST_OP(TYPE_LIST, node)));
    if(!ptrElem)
      {
	printf("Error : faild to allocate a node  !");
	  return NULL;
      }
    ptrElem->data = elem;
    ptrElem->next = NULL;
    return ptrElem;
  }

  void LIST_OP(TYPE_LIST, addElem) (LIST(TYPE_LIST) *list, TYPE_LIST elem)
  {
    LIST_OP(TYPE_LIST, node) *myNode = LIST_OP(TYPE_LIST, createNode)(elem);
    if(!myNode)
      {
	printf("Can't add element");
	  return;
      }
    LIST_OP(TYPE_LIST, addNode)(list, myNode);
  }

  void LIST_OP(TYPE_LIST, free)(LIST(TYPE_LIST) *list)
  {
    for(LIST_OP(TYPE_LIST, node)* it = list->head; it != NULL;)
      {
	LIST_OP(TYPE_LIST, node) *temp = it;
	it = it->next;
	free(temp);
      }
  }

