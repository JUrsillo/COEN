//
// Created by Jack Ursillo on 1/14/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//Creates a set Struct
typedef struct set {

    int count;
    int length;
    char** data;

} SET;

//createSet runtime complexity O(1)
//initializes a new set
SET* createSet(int maxElts) {

    SET* sp;

    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);

    return sp;

}

//search runtime complexity O(n)
//Searches for a specific element in the set using linear search
static int search (SET* sp, char* elt) {

    int i;

    assert(sp != NULL);

    //Searches through each element in the array and returns the given element if found
    for (i = 0; i < sp->count; i++) {

        if (strcmp(sp->data[i], elt) == 0) {

            return i;

        }

    }
return -1;

}

//add element runtime complexity  O(n)
///Adds the given element to the given set
void addElement(SET* sp, char* elt) {

assert(sp != NULL);

int found = search(sp, elt);

//If the given element is not found, add it to the set
if (found < 0) {

    //if the set is full return without adding the given element
    if (sp->count == sp->length) {

        return;

    }


    sp->data[sp->count] = strdup(elt);

    sp->count++;


}


}


//destroySet runtime complexity O(n)
//Removes a set
void destroySet(SET* sp) {

    assert(sp != NULL);

    int i;

    //Loops through each element in the array and frees it
    for (i = 0; i < sp->count; i++) {

        free(sp->data[i]);

    }

	free(sp->data);
        free(sp);

}

//numElements runtime complexity O(1)
//Returns the number of elements in a set
int numElements(SET* sp) {

    assert(sp != NULL);

    return sp->count;

}

//findElement runtime complexity O(n)
//finds a specific element in the set
char* findElement(SET* sp, char* elt) {

        assert(sp != NULL);

	int found = search (sp, elt);

	//If the given element is found, return it else return null
	if (found != -1) {

		return sp->data[found];

	} else {

		return NULL;

	}

}


//removeElement runtime complexity O(n)
//Utilizes the search function and deletes element if found
void removeElement(SET *sp, char *elt) {

	int i;

        assert(sp != NULL);

	int found = search (sp, elt);

	//If the given element is found remove it
	if (found != -1) {

		//Shifts all elements after found down
		for (i = found; i < sp->count; i++) {

			sp->data[i] = sp->data[i+1];

		}

		sp->count--;

	}

}

//getElements runtime complexity O(n)
//gets elements from a set and returns them as a char**
char** getElements(SET* sp) {

        assert(sp != NULL);

	char** x;

	int i;

	x = malloc(sizeof(char*)*sp->count);

	return memcpy(x, sp->data, (sp->count*sizeof(char*)));

}

