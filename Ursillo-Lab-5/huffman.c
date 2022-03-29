#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"
#include "pack.h"

typedef struct node NODE;

int arr[257];
NODE* nodes[257];

//Complexity O(n)
//Opens the input file and stores the values and their frequency
void fileOpen (char* infile) {

FILE* fptr;
//char word;
//char temp;

fptr = fopen(infile, "r");

if (fptr == NULL) {

	printf("File is empty!");
	exit(1);

}

int j;
//Makes sure arr values are initialized
for (j = 0; j < 257; j++) {

arr[j] = 0;

}

char temp = fgetc(fptr);
//Stores values and frequency in arr
while (temp != EOF) {
arr[(int)(temp)]++;
temp = fgetc(fptr);
}


fclose(fptr);




}

//Complexity O(1)
//Creates a new node and has the left and right nodes point to the parent
NODE* newNode (int count, NODE* left, NODE* right) {

        NODE* ch = malloc(sizeof(NODE));
        ch->parent = NULL;
        ch->count = count;
	if (left != NULL) {

		left->parent = ch;
}
		if (right != NULL) {

			right->parent = ch;

		}



	return ch;

}

//Complexity O(1)
//Compares the two nodes and returns 1,0, or -1 depending on which is larger or smaller
int compareNodes (NODE* firstNode, NODE* secondNode) {

if (firstNode->count > secondNode->count) {
        return 1;
    } else if (secondNode->count > firstNode->count) {
        return -1;
    }
    return 0;

}

//Complexity O(1)
//Returns the depth of the huffman tree
int depth(NODE* node) {

if (node->parent == NULL) {

	return 0;

}

return (depth(node->parent)+1);


}

//Complexity O(n^2)
//Calls other functions and returns output.txt
int main (int argc, char* argv[]) {

//Takes first arg and opens file
fileOpen(argv[1]);
int i;


//Creates a new priority queue and calls compareNodes function
PQ *pq = createQueue(compareNodes);


//Adds new node to priority queue for all non-zero values
for (i = 0; i < 256; i++) {

if (arr[i] > 0) {

nodes[i] = newNode(arr[i], NULL, NULL);
addEntry(pq, nodes[i]);



}
}


nodes[256] = newNode (0, NULL, NULL);

addEntry(pq, nodes[256]);

//Combines node1 and node2 into new main node
while (numEntries(pq) > 1) {

NODE* node1 = removeEntry(pq);
NODE* node2 = removeEntry(pq);

//Creates a new node combining the value of node1 and node2
//Still retains the values of node1 and node2 and these point to the new parent
NODE* mainNode = newNode((node1->count + node2->count), node1, node2);


addEntry(pq, mainNode);

}

int j = 0;
    for (j=0; j <= 256; j++) {
        if (nodes[j] != NULL) {
            printf(isprint(j) ? "%c" : "%03o", j);
            printf(": %d x %d bits = %d bits\n", arr[j], depth(nodes[j]), arr[j]*depth(nodes[j]));
        }
 }
    pack(argv[1], argv[2], nodes);
    destroyQueue(pq);
    return 1;



}


