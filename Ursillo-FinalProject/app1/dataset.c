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
void destroyDataSet (LIST* lt) {

assert (lt != NULL);

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
//Search for a student(s) based on age
int searchAge (LIST* lt, int age) {

int i;
assert (lt != NULL);

//Loops through array and returns index if student's age matches the age being searched for
for (i = 0; i < lt->length; i++) {

	if (lt->student[i]->age == age) {


		return i;

	}

}
return -1;

}

//Complexity O(n)
//Returns the max age gap in the array of nodes
int maxAgeGap (LIST* lt) {


	assert (lt != NULL);
	int i;
	int max = 0;
	int min = 50;

	//Loops through array checking which student has the lowest and highest age in the array
	for (i = 0; i < lt->length; i++) {

		if ((lt->student[i]->age < min) && (lt->student[i]->age != 0)) {

			min = lt->student[i]->age;

		}

		if (lt->student[i]->age > max) {

			max = lt->student[i]->age;

		}

	}
return (max-min);

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

//Compelxity O(n^2)
//Removes all students with the same age as the age being searched for
void deletion (LIST* lt, int age) {

int i;
int val;
int j;
assert (lt != NULL);

printf("We need to remove students with age %d from the list.", age);
printf("\n");

	//Loops through the whole array
	for (i = 0; i < lt->length; i++) {

		val = searchAge(lt, age);
			if (val == -1) {
				return;
			} else {

			//If the student's age matches the age they will be removed
			if (lt->student[i]->age == age) {

				printf("Student %s, ID %d, age %d removed from list.", lt->student[i]->name, lt->student[i]->studentID, lt->student[i]->age);
        			printf("\n");

				//Loops through the array and shifts all nodes up
				//The node to be deleted is overwritten
				for (j = i; j < lt->length; j++) {

	        			lt->student[j] = lt->student[j+1];

				}
				//Removes the last element because it's data is copied over to the node infront when shifting the nodes
				free(lt->student[lt->length-1]);
				lt->count--;
				lt->length--;
				i--;

			}

			}

	}

}
