#include <stdio.h>
#include "tests.h"
#include "linkedList.h"

void runTests(){
  printf("Tests running...\n");
  printf("Test create\n");
  listElement* l = createEl("Test String (1).", 30);
  printf("%s\n%p\n", l->data, l->next);
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

  //Test popping off the head
  printf("Test pop, new list:\n");
  listElement* node = pop(&l);
  traverse(l);
  printf("Test length of list=%d\n", length(l));
  printf("Popped data='%s'\n", node->data);
  printf("\n");

  //Test enqueuing
  printf("Test enqueue\n");
  push(&l, "a new initial string (-1)", 30);
  push(&l, "an even more initial string (-2)", 30);
  traverse(l);
  printf("Test length of list=%d\n", length(l));
  printf("\n");

  //Test dequeue
  printf("Test dequeue\n");
  node = dequeue(&l);
  traverse(l);
  printf("Test length of list=%d\n", length(l));
  printf("Dequeued data='%s'\n", node->data);
  printf("Dequeue all items\n");
  node = dequeue(&l);
  node = dequeue(&l);
  node = dequeue(&l);
  traverse(l);
  printf("Test length of list=%d\n", length(l));
  printf("Dequeued data='%s'\n", node->data);
  printf("Dequeue an empty list\n");
  node = dequeue(&l);
  printf("Is the dequeued node null? %s\n", (node == NULL) ? "NULL" : "SOMETHING");
  printf("Is the list head pointer null? %s\n", (l == NULL) ? "NULL" : "SOMETHING");
  printf("\n");


  printf("\nTests complete.\n");
}
