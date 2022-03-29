#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"
#include <math.h>

int MAX_STUDENTS = 3000;


int main () {

int i;

char ascii[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char* name = malloc(sizeof(char)*8);

LIST* lt = createDataSet(MAX_STUDENTS);

srand(time(NULL));

int val;
int previous;
int id;
int age;
int j;
int temp;

for (i = 0; i < 1000; i++) {

val = (rand() % 2) + 1;
previous += val;
for (j = 0; j < 8; j++) {

temp = rand()%26;
name[j] = ascii[temp];

}
age = (rand() % 13) + 18;

insertion (lt, previous, age, name);
}



id = (rand() % 2000) + 1;
age = (rand() % 13) + 18;
deletion (lt, id);
destroyDataSet(lt);

}
