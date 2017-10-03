#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genericLinkedList.h"

//Creates a new linked list element with given content of size
//Returns a pointer to the element
listElement* createEl(void* data, size_t size, void (*printer)(void*)) {
    // Create node
    listElement* e = malloc(sizeof(listElement));
    if (e == NULL) { //malloc has had an error
        return NULL; //return NULL to indicate an error.
    }

    // Create space to hold the data
    char* dataPointer = malloc(size);
    if (dataPointer == NULL){ //malloc has had an error
        free(e); //release the previously allocated memory
        return NULL; //return NULL to indicate an error.
    }

    // Copy the data into the new memory space
    memcpy(dataPointer, data, size);

    // store the information in the new node
    e->data = dataPointer;
    e->size = size;
    e->printDataFunction = printer;
    e->next = NULL;
    return e;
}

//Prints out each element in the list
void traverse(listElement* start){
    listElement* current = start;
    while(current != NULL){
        current->printDataFunction(current->data);
        current = current->next;
    }
    printf("EOL\n");
}

//Inserts a new element after the given el
//Returns the pointer to the new element
listElement* insertAfter(listElement* el, void* data, size_t size, void (*printer)(void*)){
    listElement* newEl = createEl(data, size, printer);
    listElement* next = el->next;
    newEl->next = next;
    el->next = newEl;
    return newEl;
}


//Delete the element after the given el
void deleteAfter(listElement* after){
    listElement* delete = after->next;
    listElement* newNext = delete->next;
    after->next = newNext;
    //need to free the memory because we used malloc
    free(delete->data);
    free(delete);
}

//Determine how many elements are in a list, assuming the element passes as an argument is the head of that list
int length(listElement* list) {
    if (list == NULL) {
        return 0;
    } else {
        return 1 + length(list->next);
    }
}

//Push a new element onto the head of a list
void push(listElement** list, void* data, size_t size, void (*printer)(void*)) {
    // NOTE: list is a pointer to a pointer, so:
    //       **list is the actual node (head of list)
    //       *list is a memory address (the pointer to that head of list) and modifying this changes what the calling function believes is the node acting as the list's head

    // Guard against if the list pointer itself is empty, which is a usage error for this function
    if (list == NULL) {
        return;
    }

    // Create the new element
    listElement* newHead = createEl(data, size, printer);

    // Insert it at the head of the list
    newHead->next = *list;
    *list = newHead;
}

//Pop an element from the head of a list
listElement* pop(listElement** list) {
    // Guard against an already empty list or an error if the list pointer itself is empty
    if (list == NULL || *list == NULL) {
        return NULL;
    }
    listElement* oldHead = *list;
    *list = oldHead->next; // reassign the list's head pointer. This will also work to empty the list if the item was previously the tail of the list
    oldHead->next = NULL; // Design decision: since the whole node is being returned from this function rather than just data, to proactively prevent errors, the node is un-coupled from the list

    return oldHead;
}

//Enqueue a new element onto the head of the list
void enqueue(listElement** list, void* data, size_t size, void (*printer)(void*)) {
    push(list, data, size, printer);
}

//Dequeue an element from the tail of the list, and return that element
listElement* dequeue(listElement** list) {
    // Design decision: If I knew that this code was going to be primarily a Queue with many dequeue ops, I would change the internal design to be a doubly-linked list with a stored tail pointer
    //                  But, I did not want to add that overhead and complexity w/o a good reason

    // Guard against an already empty list or an error if the list pointer itself is empty
    if (list == NULL || *list == NULL) {
        return NULL;
    }

    // Find tail of list iteratively:
    listElement* tail = *list;
    // as well as the element before it:
    listElement* newTail = NULL;
    while (tail->next != NULL) {
        newTail = tail;
        tail = tail->next;
    }

    // Detect if there was only one item in the list, or there are more left
    if (newTail == NULL) {
        // Reassign the list's head pointer to reflect a newly emptied list
        *list = NULL;
    } else {
        // Remove tail from the list
        newTail->next = NULL;
    }

    // Return the removed node
    return tail;
}

void freeListElement(listElement* delete) {
    //need to free the memory because we used malloc
    free(delete->data);
    free(delete);
}
