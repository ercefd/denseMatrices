#include "matrix.h"

/**
 * This function does level 0 testing for sets. It does not do a comprehensive test.
 */
void testSets() {
	Set set_1 = initSet();
	Element element_1 = createIntegerElement(5);
	insertElement(set_1, element_1);
	Element element_2 = createIntegerElement(4);
	insertElement(set_1, element_2);
	Element element_3 = createIntegerElement(5);
	insertElement(set_1, element_3);
	Element element_4 = createStringElement("Hello");
	insertElement(set_1, element_4);
	Element element_5 = createStringElement("Hello");
	insertElement(set_1, element_5);
	printf("Set 1: ");
	printSet(set_1);
	printf("\n");

	Set set_2 = initSet();
	insertElement(set_2, element_3);
	insertElement(set_2, element_4);
	Element element_6 = createIntegerElement(7);
	insertElement(set_2, element_6);
	Element element_7 = createIntegerElement(8);
	insertElement(set_2, element_7);
	printf("Set 2: ");
	printSet(set_2);
	printf("\n");

	Set unitedSet = unite(set_1, set_2);
	printf("United Set: ");
	printSet(unitedSet);
	printf("\n");

	Set intersectedSet = intersect(set_1, set_2);
	printf("Intersected Set: ");
	printSet(intersectedSet);
	printf("\n");

	Set substractedTest = substract(set_1, set_2);
	printf("Substructed Set: ");
	printSet(substractedTest);
	printf("\n");

	free(set_1);
	free(set_2);
	free(unitedSet);
	free(intersectedSet);
	//free(substractedTest);
}

/**
 * This function does level 0 testing for matrices. It does not do a comprehensive test.
 */
void testMatrices() {
	Set sparseMatrix1 = initSet();
	insertElement(sparseMatrix1, createMatrixPointElement(0, 0, 1));
	insertElement(sparseMatrix1, createMatrixPointElement(1, 2, 3));
	insertElement(sparseMatrix1, createMatrixPointElement(2, 2, 4));

	Set sparseMatrix2 = initSet();
	insertElement(sparseMatrix2, createMatrixPointElement(0, 0, 4));
	insertElement(sparseMatrix2, createMatrixPointElement(1, 1, 5));
	insertElement(sparseMatrix2, createMatrixPointElement(2, 2, -4));

	int columnLength = 4;
	int rowLength = 3;

	Set result = addSparseMatrices(sparseMatrix1, sparseMatrix2, columnLength, rowLength);
	printSet(result);
	printf("\n");

	freeSet(sparseMatrix1);
	freeSet(sparseMatrix2);
	freeSet(result);
}


int main() {
	testSets();
	testMatrices();
	return 0;
}
