#include <stdio.h>
#include "genericLinkedList.h"
#include <math.h>
#include <stdlib.h>

// Define item printers
void printString(void* data) {
    printf("%s -> ", (char*) data);
}
void printChar(void* data) {
    printf("%c -> ", *((char*) data));
}
void printInt(void* data) {
    printf("%d -> ", *((int*) data));
}
void printDouble(void* data) {
    printf("%lf -> ", *((double*) data));
}

// Define an array that can be passed around as a (void*) and supports generics for its data elements. (But just printing, no real usefulness here...)
typedef struct struct_structuredArray {
    void** array;
    int length;
    void (*printDataFunction)(void* data);
} structuredArray;
void printStructuredArray(void* data) {
    int len = ((structuredArray*) data)->length;
    void** array = ((structuredArray*) data)->array;
    for (int i = 0; i < len; ++i) {
        void* item = (array + i);
        ((structuredArray*) data)->printDataFunction(item);
    }
    printf(" -> ");
}
void printIntArrayItem(void* data) {
    printf("%d, ", *((int*) data));
}

void runTests(){
    printf("Tests running...\n");

    //Test create and traverse
    printf("Test create and traverse one node:\n");
    listElement* l = createEl("Test String (1).", 30, &printString);
    printf("Newly created node:    My Address=%11p, Next Address=%11p, Data='%s'\n", l, l->next, (char*) l->data);
    traverse(l);
    printf("\n");

    //Test insert after with a char data and int data
    printf("Test create and traverse items of various types:\n");
    char a = 'a';
    int answer = 42;
    double pi = M_PI;
    listElement* elem2 = insertAfter(l, &a, sizeof(char), &printChar);
    listElement* elem3 = insertAfter(elem2, &answer, sizeof(int), &printInt);
    listElement* elem4 = insertAfter(elem3, &pi, sizeof(double), &printDouble);
    printf("Original node #0:      My Address=%11p, Next Address=%11p, Data='%s'\n", l, l->next, (char*) l->data);
    printf("Newly created node #1: My Address=%11p, Next Address=%11p, Data='%c'\n", elem2, elem2->next, *((char*) elem2->data));
    printf("Newly created node #2: My Address=%11p, Next Address=%11p, Data='%d'\n", elem3, elem3->next, *((int*) elem3->data));
    printf("Newly created node #3: My Address=%11p, Next Address=%11p, Data='%lf'\n", elem4, elem4->next, *((double*) elem4->data));
    traverse(l);
    printf("\n");

    // Test delete after
    printf("Test deleting item #2\n");
    deleteAfter(l); // NOTE: elem2 is now invalid memory
    traverse(l);
    printf("\n");

    // Test length
    printf("Test lengths: Full list=%d, from the middle of a list=%d, of NULL=%d\n", length(l), length(elem3), length(NULL));
    printf("\n");

    //Test pushing to the head of the list
    printf("Test push an int\n");
    int number = -128;
    push(&l, &number, sizeof(int), &printInt);
    traverse(l);
    printf("Length of list=%d\n", length(l));
    printf("\n");

    //Test popping
    printf("Test pop:\n");
    listElement* node = pop(&l);
    printf("Popped data='%d'\n", *((int*) node->data));
    freeListElement(node);
    traverse(l);
    printf("Length of list=%d\n", length(l));
    printf("\n");

    //Test enqueuing
    printf("Test enqueue two strings:\n");
    push(&l, "a new initial string (-1)", 30, &printString);
    push(&l, "an even more initial string (-2)", 40, &printString);
    traverse(l);
    printf("\n");

    //Test dequeue
    printf("Test dequeue\n");
    node = dequeue(&l);
    printf("Dequeued data='%lf'\n", *((double*) node->data));
    freeListElement(node);
    traverse(l);
    printf("\n");

    printf("Empty the list, then traverse it:\n");
    node = dequeue(&l);
    freeListElement(node);
    node = dequeue(&l);
    freeListElement(node);
    node = dequeue(&l);
    freeListElement(node);
    node = dequeue(&l);
    freeListElement(node);
    traverse(l);
    printf("Length of empty list=%d\n", length(l));
    printf("Attempt to dequeue an empty list, should not make an error: ");
    node = dequeue(&l);
    printf("Is the dequeued node null? %s, ", (node == NULL) ? "NULL" : "SOMETHING");
    printf("Is the list head pointer null? %s\n", (l == NULL) ? "NULL" : "SOMETHING");
    printf("Attempt to pop an empty list, should not make an error: ");
    node = pop(&l);
    printf("Is the popped node null? %s, ", (node == NULL) ? "NULL" : "SOMETHING");
    printf("Is the list head pointer null? %s\n", (l == NULL) ? "NULL" : "SOMETHING");
    printf("\n");

    printf("Testing array struct, which is passable as (void*):\n");
    // Create array struct
    structuredArray* arr = malloc(sizeof(structuredArray));
    arr->length = 4;
    arr->printDataFunction = &printIntArrayItem;
    arr->array = malloc(arr->length * sizeof(void));
    int first = 4, second = 3, third = 2, fourth = 1;
//    *(((int**) arr->array) + 0) = (void*) &first;
//    *(((int**) arr->array) + 1) = &second;
//    *(((int**) arr->array) + 2) = &third;
//    *(((int**) arr->array) + 3) = &fourth;
    *(((int**) arr->array) + 0) = 8;
    *(((int**) arr->array) + 1) = 9;
    *(((int**) arr->array) + 2) = 10;
    *(((int**) arr->array) + 3) = 11;
    printf("%d\n", *((int*) (((int**) (arr->array)) + 3)));
    // Create list with array struct in the middle
    l = createEl("First", 10, &printString);
    elem2 = insertAfter(l, &a, sizeof(char), &printChar);
    elem3 = insertAfter(elem2, &answer, sizeof(int), &printInt);
    elem4 = insertAfter(elem3, arr, sizeof(structuredArray), &printStructuredArray); // Shallow copy!
    listElement* elem5 = insertAfter(elem4, &pi, sizeof(double), &printDouble);
    // Print the whole list
    traverse(l);
    free(arr->array);

    printf("\nTests complete.\n");
}
