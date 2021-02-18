
#define TYPE_LIST double
#include "list.h"
#undef TYPE_LIST

#define TYPE_LIST unsigned
#include "list.h"
#undef TYPE_LIST

typedef char * STR;

#define TYPE_LIST STR
#include "list.h"
#undef TYPE_LIST
int main()
{
  list_unsigned* myList = list_unsigned_init();
  list_unsigned_addElem(myList , 50);
  list_unsigned_free(myList);

  list_double *doubleList = list_double_init();
  list_double_addElem(doubleList, -3.05);
  list_double_addElem(doubleList, 103.5);
  list_double_free(doubleList);

  list_STR* STRList = list_STR_init();
  list_STR_addElem(STRList, "salut !");
  list_STR_free(STRList);
  return 0;
}
