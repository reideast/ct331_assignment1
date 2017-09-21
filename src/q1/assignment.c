#include <stdio.h>

int main(int arg, char* argc[]){
  printf("Hello assignment1.\n");

  int i = 42;
  int* iPtr = &i;
  long l = 9000;
//  double d = 3.14159;
  double* dPtr;
  char** strings;

  printf("i %lu\n", sizeof(i));
  printf("iPtr %lu\n", sizeof(iPtr));
  printf("l %lu\n", sizeof(l));
  printf("dPtr %lu\n", sizeof(dPtr));
  printf("strings %lu\n", sizeof(strings));

  return 0;
}
