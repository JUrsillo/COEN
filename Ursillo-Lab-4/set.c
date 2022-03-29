#include <stdlib.h>
#include <stdio.h>
#include "set.h"
#include "list.h"
#include <string.h>
#include <assert.h>


typedef struct set {

int count;
int length;
LIST **lists;
int (*compare)();
unsigned (*hash)();

} SET;

//complexity O(n)
//Initializes a new set
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {

assert(compare != NULL);
assert(hash != NULL);
    int i;
    SET *sp;
    assert(compare != NULL && hash != NULL);
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
//initialize length; count; compare and hash
    sp->length = (maxElts/20);
    sp->compare = compare;
    sp->hash = hash;
    sp->count = 0;
    sp->lists = malloc(sizeof(LIST*) * sp->length);
//Creates the nodes within sp
    for (i = 0; i < sp->length; i++) {
	sp->lists[i] = createList(compare);
	}

//initialize array of lists: allocating memory for it.
// for each element in the lists array (e.g. sp->lists[i]), create a list, 
//and let sp->lists[i] point to it. 
    return sp;

}

//complexity O(n)
//Removes a set
void destroySet(SET *sp) {
assert(sp != NULL);
int i;
//Removes the nodes within sp
for (i = 0; i < sp->length; i++) {
	free(sp->lists[i]);
}
free(sp);

}

//complexity O(1)
//Returns the number of elements
int numElements(SET *sp) {

assert(sp != NULL);

return sp->count;

}

//complexity O(n)
//Uses hashkey for index and find item to add an element
void addElement(SET *sp, void *elt) {

assert(sp != NULL && elt != NULL);

unsigned int num = (*sp->hash)(elt) % sp->length;

if (findItem((sp->lists[num]), elt) == NULL) {

	addFirst(sp->lists[num], elt);

}

sp->count++;

}


//complexity O(n)
//Removes an element from sp
void removeElement(SET *sp, void *elt) {

assert(sp != NULL && elt != NULL);

unsigned int num = (*sp->hash)(elt) % sp->length;

if (findItem(sp->lists[num], elt) != NULL) {

	removeItem(sp->lists[num], elt);

}

sp->count--;

}

//complexity O(n)
//Uses findItem function to find an element within sp
void *findElement(SET *sp, void *elt) {

assert(sp != NULL && elt != NULL);

unsigned int num = (*sp->hash)(elt) % sp->length;

return (findItem(sp->lists[num], elt));



}

//complexity O(n^2)
//Gets elements from nodes and sp
void *getElements(SET *sp) {

int i;
int j;
int k;

assert (sp != NULL);

void** arrayList = malloc(sizeof(void*) * sp->count);
void** elements;

//Loops through sp
for (i = 0; i < sp->length; i++) {

	if (sp->lists[i] != NULL) {

	elements = getItems(sp->lists[i]);

	//loops through nodes
	for (j = 0; j < numItems(sp->lists[i]); j++) {

		arrayList[k] = elements[j];
		k++;


	}
}

}

return arrayList;

}
