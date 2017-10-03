#ifndef CT331_ASSIGNMENT_LINKED_LIST
#define CT331_ASSIGNMENT_LINKED_LIST

typedef struct listElementStruct{
  void* data;
  size_t size;
  struct listElementStruct* next;
} listElement;
// Note: The full definition of this struct was moved here so that all files that use nodes, such as test.c, can read its contents. This prevents the "dereferencing pointer to incomplete type" comelier msg
//typedef struct listElementStruct listElement;

//Creates a new linked list element with given content of size
//Returns a pointer to the element
listElement* createEl(void* data, size_t size);

//Prints out each element in the list
void traverse(listElement* start);

//Inserts a new element after the given el
//Returns the pointer to the new element
listElement* insertAfter(listElement* after, void* data, size_t size);

//Delete the element after the given el
void deleteAfter(listElement* after);

//Determine how long a list is, assuming the element passes as an argument is the head of that list
int length(listElement* list);

//Push a new element onto the head of a list
void push(listElement** list, void* data, size_t size);

//Pop an element from the head of a list
listElement* pop(listElement** list);

//Enqueue a new element onto the head of the list
void enqueue(listElement** list, void* data, size_t size);

//Dequeue an element from the tail of the list, and return that element
// Note: The assignment asked for the signature of this function to call for a listElement pointer, not a pointer to a listElement pointer
//       I have made the design decision to change this functionality. This allows the function to handle the edge case of the list having a single element, and then that element is removed, leaving the list empty.
listElement* dequeue(listElement** list);

#endif
