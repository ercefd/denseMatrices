#ifndef MATRIX_H
#define MATRIX_H

#include "set.h"

typedef struct DenseMatrix_s {
	int** matrix;
	int columnLength;
	int rowLength;
} DenseMatrix_t;
typedef DenseMatrix_t* DenseMatrix;

DenseMatrix initDenseMatrix(int columnLength, int rowLength);
void freeDenseMatrix(DenseMatrix denseMatrix);
DenseMatrix parseMatrixToDenseMatrix(Set parseMatrix, int columnLength, int rowLength);
Set denseMatrixToParseMatrix(DenseMatrix denseMatrix);
DenseMatrix addDenseMatrices(DenseMatrix dm1, DenseMatrix dm2);
Set addSparseMatrices(Set sm1, Set sm2, int columnLength, int rowLength);

#endif
