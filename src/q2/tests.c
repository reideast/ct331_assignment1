#include <stdio.h>
#include "tests.h"
#include "linkedList.h"

void runTests(){
  printf("Tests running...\n");
  printf("Test create\n");
  listElement* l = createEl("Test String (1).", 30);
//  printf("%s\n%p\n", l->data, l->next);
  //Test create and traverse
  printf("Test traverse one item\n");
  traverse(l);
  printf("\n");

  //Test insert after
  listElement* l2 = insertAfter(l, "another string (2)", 30);
  listElement* l3 = insertAfter(l2, "a final string (3)", 30);
  printf("Test traverse 3 items\n");
  traverse(l);
  printf("\n");

  // Test delete after
  printf("Test deleting item #2\n");
  deleteAfter(l); // NOTE: l2 is now invalid memory
  traverse(l);
  printf("\n");

  // Test length
  printf("Test length of list=%d\n", length(l));
  printf("Test length of partial list=%d\n", length(l3));
  printf("Test length of empty list=%d\n", length(NULL));
  printf("\n");

  //Test pushing to the head of the list
  printf("Test push\n");
  push(&l, "an initial string (0)", 30);
  traverse(l);
  printf("Test length of list=%d\n", length(l));
  printf("\n");

  printf("\nTests complete.\n");
}
