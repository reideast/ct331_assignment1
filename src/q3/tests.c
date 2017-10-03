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

// Define an array that can be passed around as a (void*). (But just printing, no real usefulness here...)
typedef struct struct_structuredIntArray {
    int* array;
    int length;
} structuredIntArray;
void printStructuredIntArray(void* data) {
    int len = ((structuredIntArray*) data)->length;
    int* array = ((structuredIntArray*) data)->array;
    for (int i = 0; i < len; ++i) {
        printf("%d", array[i]);
        if (i != len - 1) {
            printf(",");
        }
    }
    printf(" -> ");
}

void runTests(){
    printf("Tests running...\n");

    //Test insert with int, char, double, and string
    printf("Test create and traverse items of various types:\n");
    listElement* l = createEl("Test String (1).", 30, &printString);
    printf("Newly created node:    My Address=%11p, Next Address=%11p, Data='%s'\n", l, l->next, (char*) l->data);
    traverse(l);
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
    structuredIntArray* arr = malloc(sizeof(structuredIntArray));
    arr->length = 4;
    arr->array = malloc(arr->length * sizeof(int));
    *(arr->array + 0) = 8;
    *(arr->array + 1) = 9;
    *(arr->array + 2) = 10;
    *(arr->array + 3) = 11;
    // Create list with array struct in the middle
    l = createEl("First", 10, &printString);
    insertAfter(l, &a, sizeof(char), &printChar);
    enqueue(&l, &answer, sizeof(int), &printInt);
    push(&l, arr, sizeof(structuredIntArray), &printStructuredIntArray); // Shallow copy!
    free(arr); // free original struct now that it's been copied
    push(&l, &pi, sizeof(double), &printDouble);
    // Print the whole list
    traverse(l);
    // Empty the list
    node = dequeue(&l); // char
    freeListElement(node);
    node = dequeue(&l); // string
    freeListElement(node);
    node = pop(&l); // double
    freeListElement(node);
    node = pop(&l); // structuredIntArray
    free(((structuredIntArray*) (node->data))->array); // Have to free the data we malloc'd above (that wasn't included in the shallow copy)
    freeListElement(node);
    node = pop(&l); // int
    freeListElement(node);

    printf("\nTests complete.\n");
}
