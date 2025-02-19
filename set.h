#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Type_e {
	INTEGER,
	FLOAT,
	STRING,
	MATRIX_POINT
} Type;

typedef struct Element_s {
	Type type;
	void* data;
} Element_t;
typedef Element_t* Element;

typedef struct Set_s {
	Element* elements;
	int cardinality;
} Set_t;
typedef Set_t* Set;

Set initSet();
Element createIntegerElement(int data);
Element createFloatElement(float data);
Element createStringElement(char* data);
Element createMatrixPointElement(int x, int y, int data);
void freeElement(Element element);
void freeSet(Set set);
int isSame(Element e1, Element e2);
int in(Set set, Element element);
int insertElement(Set set, Element element);
int removeElement(Set set, Element element);
Set unite(Set s1, Set s2);
Set intersect(Set s1, Set s2);
Set substract(Set s1, Set s2);
void printElement(Element element);
void printSet(Set set);
void freeSet(Set set);

#endif
