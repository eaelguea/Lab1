#ifndef LAB1_H_
#define LAB1_H_
#include <stdio.h>
#include <stdlib.h>
#define DATA 26

struct database{
  char employeeNames[DATA];
  struct database* next;
} database;

typedef struct database Node;
typedef struct database* Pointer;

void insert(char[], Pointer*);
void print(Pointer);
void delete(char[], Pointer*);

#endif /* LAB1_H_ */
