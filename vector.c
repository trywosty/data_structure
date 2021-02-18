
#define TYPE_VEC double
#include "vector.h"
#undef TYPE_VEC


int main()

{
  vector_double *dblVec = vector_double_init(1);
    for(int i = 0; i != 10; ++i)
   {
     printf("Iteration %u : ", i);
     printf("Size : %u", vector_double_size(dblVec));
     printf(" Capacity : %u", vector_double_capacity(dblVec));
     printf("\n\n");
     vector_double_push_back(dblVec, 1);
   }
  vector_double_free(dblVec);
  return 0;
}
