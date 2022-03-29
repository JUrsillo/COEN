#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


typedef struct node NODE;

typedef struct list LIST;

LIST* createDataSet(int maxElts);

void destroyDataSet (LIST *lt);

int searchID (LIST* lt, int id);

void insertion (LIST* lt, int id, int age, char* name);

void deletion (LIST* lt, int id);

