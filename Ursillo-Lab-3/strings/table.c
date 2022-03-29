//
// Created by Jack Ursillo on 1/29/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

//Creates a set struct
typedef struct set {

    int count;
    int length;
    char** data;
    char* flags;

} SET;

//createSet runtime complexity O(n)
//initializes a new set
SET* createSet(int maxElts) {

    SET* sp;
    int i;

    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    sp->flags = malloc(sizeof(char)*maxElts);
    for (i = 0; i < maxElts; i++) {
	sp->flags[i] = 'E';
    }
    return sp;

}

//strhash runtime complexity O(n)
//Creates a hash function
unsigned strhash (char *s) {

	unsigned hash = 0;

	while (*s != '\0') {

		hash = 31 * hash + *s++;

	}

	return hash;

}



//search runtime complexity O(n)
//Searches the array using hashing
static int search(SET* sp, char* elt, bool* found) {

    int i = 0;
    int check = -1;
    int k = 0;

    assert(sp != NULL);

    unsigned hashKey = strhash(elt) % sp->length;

     k = (hashKey + i) % sp->length;

    //Checks each flag for either E, D or F
    //Flag determines which case will run
    //Check checks if there is a duplicate in the array
    for (i = 0; i < sp->length; i++) {

	k = (k + i) % sp->length;

	//Checks if index is empty
	if (sp->flags[k] == 'E') {

	*found = false;

		//If the element was found check is returned
		if (check != -1) {

		return check;

		} else {

		return k;

		}

	}

	//Checks if index was deleted
	else if (sp->flags[k] == 'D') {

		//Checks if the element exists
		if (check == -1) {

		check = k;

		}

	}

	//If the element is found the index is returned
	else if (strcmp(sp->data[k], elt) == 0) {

		*found = true;
		return k;

	}

}

*found = false;
return check;

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

	free(sp->data[val]);

	sp->flags[val] = 'D';


        sp->count--;

    }

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

        sp->data[val] = strdup(elt);
	sp->flags[val] = 'F';
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

        if (sp->flags[i] == 'F') {

		free(sp->data[i]);

	}
    }

    free(sp->data);
    free(sp->flags);
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

    bool found;

    assert(sp != NULL && elt != NULL);

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
char **getElements(SET *sp){
char **elts;
int i, j;
assert(sp!= NULL);
elts= malloc(sizeof(char *) * sp->count);
assert(elts!= NULL);
for (i = 0, j = 0; i < sp->length; i ++){
if (sp->flags[i] == 'F') {

elts[j++] = sp->data[i];

}
}
return elts;
}
