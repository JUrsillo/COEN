#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <string.h>
#include <assert.h>


typedef struct node {

    void *data;
    struct node *next;
    struct node *prev;

    } NODE;

typedef struct list {

    int count;
    struct node *head;
    int (*compare)(); // function pointer

    } LIST;

//typedef struct list LIST; //list.h

//complexity O(1)
//Initializes a list
extern LIST *createList(int (*compare)()) {

	struct list *lp;
	lp = malloc(sizeof(struct list));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(struct node));
	assert(lp->head != NULL);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;

}

//complexity O(n)
//destroys all nodes
extern void destroyList(LIST *lp) {
    assert(lp != NULL);
    NODE *pPrev;
    NODE *pDel = lp->head->prev;

        while (pDel!=lp->head) {
            pPrev = pDel->prev;
            free(pDel);
            pDel = pPrev;
        }

	free(pDel);
	free(lp);

}

//complexity O(1)
//Returns the number of items
extern int numItems(LIST*lp) {

assert(lp != NULL);
return lp->count;

}

//complexity O(1)
//Adds a new node to the front of the list
extern void addFirst(LIST*lp, void*item) {


NODE* temp = malloc(sizeof(NODE*));
NODE* newNode = malloc(sizeof(NODE*));

assert(lp != NULL);
assert(item != NULL);

temp = lp->head->next;
newNode->data = item;
newNode->next = temp;
temp->prev = newNode;
newNode->prev = lp->head;
lp->head->next = newNode;
lp->count++;

}

//complexity O(1)
//Adds a new node to the end of the list
extern void addLast(LIST*lp, void*item) {

NODE* temp = malloc(sizeof(NODE*));
NODE* newNode = malloc(sizeof(NODE*));

assert(lp != NULL);
assert(item != NULL);

temp = lp->head->prev;
newNode->data = item;
newNode->next = lp->head;
newNode->prev = temp;
temp->next = newNode;
lp->head->prev = newNode;
lp->count++;
}

//complexity O(1)
//removes the first node in the list
extern void *removeFirst(LIST*lp) {

NODE* temp = malloc(sizeof(NODE*));
//NODE* newNode = malloc(sizeof(NODE*));
NODE* current = malloc(sizeof(NODE*));
void* currentData;

assert(lp != NULL);

current = lp->head->next;
temp = current->next;
temp->prev = lp->head;
lp->head->next = temp;//
currentData = current->data;
free(current);
lp->count--;
return currentData;


}

//complexity O(1)
//removes the last node in the list
extern void *removeLast(LIST*lp) {

NODE* temp = malloc(sizeof(NODE*));
//NODE* newNode = malloc(sizeof(NODE*));
NODE* current = malloc(sizeof(NODE*));
void* currentData;

assert(lp != NULL);

current = lp->head->prev;
temp = current->prev;
temp->next = lp->head;
lp->head->prev = temp;
currentData = current->data;
free(current);
lp->count--;
return currentData;

}



//complexity O(1)
//Returns the data in the first node in the list
extern void *getFirst(LIST*lp) {

NODE* current = malloc(sizeof(NODE*));

assert(lp != NULL);

current = lp->head->next;


return current->data;

}

//complexity O(1)
//Returns the data in the last node in the list
extern void *getLast(LIST*lp) {

NODE* current = malloc(sizeof(NODE*));

assert(lp != NULL);

current = lp->head->prev;


return current->data;


}

//complexity O(n)
//Removes a specific node in the list
extern void removeItem(LIST*lp, void*item) {

NODE* current = malloc(sizeof(NODE*));
NODE* prev = malloc(sizeof(NODE*));
NODE* after = malloc(sizeof(NODE*));

assert(lp != NULL);
assert(item != NULL);

current = lp->head->next;
prev = lp->head;
after = current->next;

int i;

//loops through nodes in the list
for (i = 0; i < lp->count; i++) {

if ((*lp->compare)(item, current->data) == 0) {

prev->next = after;
after->prev = prev;
free(current);
lp->count--;
return;

}

prev = current;
current = current->next;
after = current->next;

}

}

//complexity O(n)
//Finds a specific item in the list
extern void *findItem(LIST*lp, void*item) {

NODE* current = malloc(sizeof(NODE*));
assert(lp != NULL);
assert(item != NULL);
current = lp->head->next;
int i;

//loops through nodes in the list
for (i = 0; i < lp->count; i++) {

if ((*lp->compare)(item, current->data) == 0) {

return current->data;

}
current = current->next;

}

return NULL;

}

//complexity O(n)
//gets all items in the list
extern void *getItems(LIST*lp) {

NODE* current = malloc(sizeof(NODE*));
assert(lp != NULL);
void** array = malloc(sizeof(void*) * lp->count);
int i;

current = lp->head->next;

//Loops through nodes in the list
for (i = 0; i < lp->count; i++) {

array[i] = current->data;

current = current->next;

}

return array;

}
