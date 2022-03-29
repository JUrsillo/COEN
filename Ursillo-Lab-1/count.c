#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 30 //Sets max word length to 30


int readFile(char* fileName) { //File name passed in

    FILE* fptr; //Initializes a file pointer
    int count;
    int result = 0;

    char word[MAX_WORD_LENGTH];


    fptr = fopen(fileName, "r"); //Opens the file for reading

    if (fptr == NULL) { //If null program won't run

        printf("File is empty!");

    }

    while (result != EOF) { //Loops until end of file is reached

        result = fscanf(fptr, "%s", &word); //Scans each word in file

        count++;

    }

    fclose(fptr);
    return (count-1);


}

int main (int argc, char* argv[]) { //Takes arg from command line

    if (argc != 2) { //Exits program if incorrect # of args are inputted

	printf("Please include an argument\n");
	exit(0);

    }

    char* fileName = argv[1];

    int count; //Holds the number of words counted
    count = readFile(fileName); //Count receives the number from readFile function

    printf("Number of words: %d\n", count);


    return 0;

}
