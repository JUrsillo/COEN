#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#include <string.h>
#include <assert.h>


typedef struct pqueue {

	int count;/* number of entries in array */
	int length;/* length of allocated array  */
	void **data;/* allocated array of entries */
	int (*compare)();/* comparison function*/

} PQ;


//Complexity O(1)
//Creates the priority queue
PQ *createQueue(int (*compare)()) {

PQ* pq = malloc(sizeof(PQ));
pq->length = 10;
pq->count = 0;
pq->data = (void*) malloc(sizeof(void*) * pq->length);
pq->compare = compare;

return pq;

}

//Complexity O(n)
//Destroys the priority queue
void destroyQueue(PQ* pq) {

int i;

assert (pq != NULL);

for (i = 0; i < pq->count; i++) {

	free(pq->data[i]);

}

free(pq);


}

//Complexity O(1);
//Returns number of entries in the priority queue
int numEntries(PQ* pq) {

return pq->count;

}

//Complexity O(logn)
//Adds an entry to the priority queue
void addEntry(PQ* pq, void* entry) {

int i;
void* temp;

assert(pq != NULL);
assert(entry != NULL);

//If priority queue is full, the array is increased
if (pq->count == pq->length) {

pq->length *= 2;

pq->data = realloc(pq->data, sizeof(void*)*pq->length);

}


pq->data[pq->count] = entry;
pq->count++;

//Travels down the array parent nodes until the entry is less than node
//Sorts to min max
for (i = pq->count-1; i > 0; i = ((i-1)/2)) {

if (pq->compare(entry, pq->data[(i-1)/2]) == -1) {

temp = pq->data[(i-1)/2];
pq->data[i] = temp;
pq->data[(i-1)/2] = entry;

}


}

}

//Complexity O(n)
//Returns the removed root
void* removeEntry(PQ *pq) {

assert(pq != NULL);

void* root;
void* temp;
int i = 0;

root = pq->data[0];
pq->data[0] = pq->data[pq->count - 1];

pq->count--;

//checks if left node exists
while ((2*i)+1 < pq->count) {

int check = -1;

//Checks if right node exists
if ((2*i)+2 < pq->count) {

void* left = pq->data[((2*i)+1)];
void* right = pq->data[((2*i)+2)];
check = pq->compare(left, right);

}

//if left node exists
if (check <= 0) {

//Checks if left node is less than new node
if (pq->compare(pq->data[((2*i)+1)], pq->data[i]) == -1) {
	//if (pq->compare(pq->data[((2*i)+1)], pq->data[((2*i)+2)]) == -1) {

temp = pq->data[((2*i)+1)];
pq->data[((2*i)+1)] = pq->data[i];
pq->data[i] = temp;

i = (2*i)+1;
} else {
return root;
}
}
//Checks if right node is less than new node
else { if (pq->compare(pq->data[((2*i)+2)], pq->data[i]) == -1) {
	//if (pq->compare(pq->data[((2*i)+2)], pq->data[((2*i)+1)]) == -1) {

temp = pq->data[((2*i)+2)];
pq->data[((2*i)+2)] = pq->data[i];
pq->data[i] = temp;
i = (2*i)+2;
 }else {
return root;
}
}

}
return root;

}






