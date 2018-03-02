#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include "lab1.h"
#define DATA 26 // Max characters in a string
#define EXIT "exit" //String to end the processes of methods

/* Definition using 'typedef', of new lists to begin the database build */
typedef struct database Node;
typedef struct database* Pointer;

/* Main method that takes the users input, inserts the name into the database,
 * creates the possibility to delete the name, and prints the database. */
int main(){
    char empName[DATA] = {'\0'};
    Pointer head = NULL;
    printf("Welcome to the 3432 Employee Database!\n");

    /* loop that will insert a name into the database until user exits the database
     * Uses strcmp() and strcpy() found in C library (see Lab1 README) */
    while(strcmp(empName, EXIT) != 0){
        printf("Please enter an employee's name to add to the database or enter \"%s\" to exit:\n ", EXIT);
	scanf("%s", empName);
        if(0 != strcmp(empName, EXIT)){
            insert(empName, &head);
        }
    }
    print(head);
    
    strncpy(empName, "don't exit", DATA);
    printf("\n");
    while(strcmp(empName, EXIT) != 0 && head != NULL){
        printf("Please enter an employee's name to remove or enter \"%s\" to exit:\n ", EXIT);
	scanf("%s", empName);
        if(0 != strcmp(empName, EXIT)){
            delete(empName, &head);
        }
	print(head);
    }
    return 0;
} //end of main

/* Function that inserts a name into the linked list in alphabetical order
 * word: String
 * front: pointer to the first node in the list 
 * Uses strcmp() and strcpy() found in C library (see Lab1 README) */
void insert(char word[], Pointer *front){
    Pointer new = NULL;
    Pointer prev = NULL;
    Pointer curr = *front;

    new = malloc(sizeof(Node));
    // Checks if there is space to add a new name to the list
    if (new != NULL){
        strcpy(new->employeeNames, word);
        while(curr != NULL && strcmp(word, curr->employeeNames)>0){
            prev = curr; // moves previous node to the current node
            curr = curr->next;
        }
        // Inserts name at beginning of list
        if(prev ==  NULL){
            new->next = curr;
            *front = new;
        }
        else{
            // inserts between previous node and current node
            prev->next = new;
            new->next = curr;
        }
    }
}

/* Function that prints the contents of the database */
void print(Pointer curr){
    // checks if list is empty
    if(curr == NULL){
        printf("The database is empty.\n\n");
        return;
    }
    printf("Employee database: ");
    // loop to display each node with employee information
    while(curr != NULL){
        printf("%s, ", curr->employeeNames);
        curr = curr->next;
    }
    printf("\n\n");
} // end of print();

/* Function that deletes an employee node from the database.
 * str: String
 * start: points to the first node in the linked list */
void delete(char str[], Pointer *start){
    Pointer temp = NULL;
    Pointer prev = NULL;
    Pointer curr = *start;

    // check for an empty list
    if(curr == NULL){
        printf("The database is empty.\n\n");
        return;
    }
    /* This section of the function checks if the first node of the database can be deleted.
     * Utilizes the library concept free() (see Lab 1 README for library source page). */
    if(0 == strcmp(str, curr->employeeNames)){
        temp = curr;
        *start = curr->next;
        printf("Deleting \"%s\"...\n", temp->employeeNames);
        free(temp);
    }
    else{
        // loops the rest of the database to search the name to be deleted
        while(curr != NULL && 0 != strcmp(str, curr->employeeNames)){
            //printf("curr = %s\n", curr->employeeNames);
            //move to next
            prev = curr;
            curr = curr->next;
        }//end of while
        if(curr != NULL){
            //get current node's address and store in temp
            temp = curr;
            //printf("temp = %s\n", temp->employeeNames);
            //skip over current node
            prev->next = curr->next;
            printf("Deleting \"%s\"...\n", temp->employeeNames);
            free(temp);
        }//end of if
    }//end of else
}//end of delete()
