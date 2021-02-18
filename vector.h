#include <stdlib.h>
#include <stdio.h>
#ifndef TYPE_VEC
#define TYPE_VEC int
#endif
#define GET_NAME_VEC_OP(x, y) vector_##x##_##y
#define VECTOR_OP(TYPE, op) GET_NAME_VEC_OP(TYPE, op)
#define VECTOR_NAME(PREFIX, SUFFIXE) PREFIX##SUFFIXE
#define VECTOR(TYPE) VECTOR_NAME(vector_, TYPE)
#define LENGTH(FIRST, LAST) ((LAST)-(FIRST))
typedef struct {
  TYPE_VEC  *elem, *first_free, *cap;
} VECTOR(TYPE_VEC);

VECTOR(TYPE_VEC)* VECTOR_OP(TYPE_VEC, init)(size_t initSize)
{
  VECTOR(TYPE_VEC)* newVec = malloc(sizeof(VECTOR(TYPE_VEC)));
  if(!initSize)
    {
      printf("Error : initSize must bec > 0"); //will handle this case later
      return NULL;
    }
  newVec->elem = newVec->first_free = malloc(initSize * sizeof(TYPE_VEC));
  newVec->cap = newVec->elem + initSize;
  return newVec;
}
void VECTOR_OP(TYPE_VEC, realloc)(VECTOR(TYPE_VEC)* vec)
{
  size_t oldSize = LENGTH(vec->elem, vec->first_free);
  size_t newSize = (LENGTH(vec->elem, vec->cap)) ? (LENGTH(vec->elem, vec->cap)) * 2 : 1;
  TYPE_VEC* temp = realloc(vec->elem, newSize*sizeof(TYPE_VEC));
  if(!temp)
    {
      printf("Reallocation failed ! ");
      return ;
    }
  vec->elem = temp;
  vec->first_free = vec->elem + oldSize;
  vec->cap = vec->elem + newSize;
}
void VECTOR_OP(TYPE_VEC, chk_n_alloc)(VECTOR(TYPE_VEC)* vec)
{
  if(vec->first_free == vec->cap)
    {
      VECTOR_OP(TYPE_VEC, realloc)(vec);
    }

}
void VECTOR_OP(TYPE_VEC, push_back)(VECTOR(TYPE_VEC)* vec,  TYPE_VEC element)
{
  VECTOR_OP(TYPE_VEC, chk_n_alloc)(vec);
  vec->first_free[0] = element;
  ++vec->first_free;
}
void VECTOR_OP(TYPE_VEC, free)(VECTOR(TYPE_VEC)* vec)
{
  free(vec->elem);
  free(vec);
}
size_t VECTOR_OP(TYPE_VEC, size)(VECTOR(TYPE_VEC)* vec)
{
  return LENGTH(vec->elem, vec->first_free);
}
size_t VECTOR_OP(TYPE_VEC, capacity)(VECTOR(TYPE_VEC)* vec)
{
  return LENGTH(vec->elem, vec->cap);
}
