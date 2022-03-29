
//
// Created by Jack Ursillo on 1/14/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//Creates a set struct
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

//search runtime complexity O(logn)
//Searches the array using binary search
static int search(SET* sp, char* x, bool* found) {
    int lo, hi, mid;
    lo = 0; hi = sp->count-1;

    assert(sp != NULL);

    //while lo is less than highest value mid will become the avg of lo + hi
    while(lo <= hi) {
        mid = (lo + hi) / 2;

	//compares index char and x
        if (strcmp(sp->data[mid], x) < 0) {
            hi = mid - 1;
        }
	//compares index char and x
        else if(strcmp(sp->data[mid], x) > 0)
        {
            lo = mid + 1;
	//if strcmp == 0
        } else {

            *found = true;
            return mid;
        }
    }

	*found = false;
	return lo;
}

//addElement runtime complexity O(n)
//Adding to an sorted set
void addElement(SET* sp, char* elt) {

    int i;
    bool found;

    assert(sp != NULL);

    int val = search(sp, elt, &found);

    //if the element is not found in the set
    if (!found) {

	//Shifts elements up starting at lo
        for (i=sp->count; i > val; i--) {
            sp->data[i] = sp->data[i - 1];
        }

	sp->data[val] = strdup(elt);
        sp->count++;


    }


}


//destroySet runtime complexity O(n)
//Removes a set
void destroySet(SET* sp) {

    assert(sp != NULL);

    int i;

    //frees the memory held by each element in the array
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

//findElement runtime complexity O(logn)
//finds a specific element in the set
char* findElement(SET* sp, char* elt) {

    bool found;

    assert(sp != NULL);

    int val = search (sp, elt, &found);

    //If the element is found return it else return null
    if (found) {

        return sp->data[val];

    } else {

        return NULL;

    }

}


//removeElement runtime complexity O(n)
//Utilizes the search function and deletes element if found
void removeElement(SET *sp, char *elt) {

    int i;
    bool found;

    assert(sp != NULL);

    int val = search (sp, elt, &found);

    //If the element is found then remove it
    if (found) {

	//Shifts all elements after val down
        for (i = val +1; i < sp->count; i++) {

            sp->data[i - 1] = sp->data[i];

        }
        sp->count--;

    }

}

//getElement runtime complexity O(n)
//gets elements from a set and returns them as a char**
char** getElements(SET* sp) {

    assert(sp != NULL);

    char** x;

    int i;

    x = malloc(sizeof(char*)*sp->count);

    return memcpy(x, sp->data, (sp->count*sizeof(char*)));

}




