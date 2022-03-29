#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"

typedef struct node {

int studentID;
int age;
char name[8];

}NODE;

typedef struct list {

NODE** student;
int count;
int length;

}LIST;

//Complexity O(n)
//Creates an array of nodes
LIST* createDataSet(int maxElts) {

int i;

LIST* lt = malloc(sizeof(LIST));
lt->student = malloc(sizeof(NODE*) * maxElts);
lt->count = 0;
lt->length = maxElts;

//Initializes student nodes
for (i = 0; i < maxElts; i++) {

	lt->student[i] = malloc(sizeof(NODE));

}
return lt;
}

//Complexity O(n)
//Destroys an array of nodes
void destroyDataSet (LIST *lt) {

int i;

//If there is data in the array it will be freed first
for (i = 0; i < lt->length; i++) {

	if(lt->student[i] != NULL) {

	free(lt->student[i]);

	}

}

free(lt->student);
free(lt);

}


//Complexity O(n)
//Searches for a student in the array based on ID
int searchID (LIST* lt, int id) {
int i;
assert (lt != NULL);

printf("We are currently searching for student %d", id);
printf("\n");

//Loops through the array and returns the index if studentID matches the given ID
for (i = 0; i < lt->length; i++) {

	if (lt->student[i]->studentID == id) {

		printf("We found the student successfully.\n");
		return i;

	}

}

		printf("We did not find the student.\n");

		return -1;




}

//Complexity O(1)
//Adds a new student to the array
void insertion (LIST* lt, int id, int age, char* name) {

int i;

assert (lt != NULL);

lt->count++;
lt->student[lt->count-1]->studentID = id;
lt->student[lt->count-1]->age = age;
strcpy(lt->student[lt->count-1]->name, name);

}

//Complexity O(n)
//Removes students that contain the same ID as the given ID
void deletion (LIST* lt, int id) {

int i;
int val;
val = searchID(lt, id);

//Checks if the student was found
if (val == -1) {
return;
} else {

printf("We need to remove student %d from the list.", lt->student[val]->studentID);
printf("\n");

//Loops through the array starting at where the student was found and shifts nodes up
for (i = val; i < lt->length; i++) {

	lt->student[i] = lt->student[i+1];

}

//Removes the last element because it's data is copied over to the node infront when shifting nodes up
free(lt->student[lt->length-1]);
lt->count--;
lt->length--;
printf("Item successfully deleted.\n");
}
}
