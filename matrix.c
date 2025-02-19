#include "matrix.h"

/**
 * This function initializes and returns a dense matrix 
 * as a dynamic two-dimensional array.
 */
DenseMatrix initDenseMatrix(int columnLength, int rowLength) {
    DenseMatrix denseMatrix = (DenseMatrix)malloc(sizeof(DenseMatrix_t));
    if (denseMatrix == NULL) {
        return NULL;
    }

    denseMatrix->columnLength = columnLength;
    denseMatrix->rowLength = rowLength;


    denseMatrix->matrix = (int**)malloc(rowLength * sizeof(int*));
    if (denseMatrix->matrix == NULL) {
        free(denseMatrix);
        return NULL;
    }

    for (int i = 0; i < rowLength; i++) {
        denseMatrix->matrix[i] = (int*)malloc(columnLength * sizeof(int));
        if (denseMatrix->matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(denseMatrix->matrix[j]);
            }
            free(denseMatrix->matrix);
            free(denseMatrix);
            return NULL;
        }
    }

    return denseMatrix;
}

/**
 * This function deallocates all the rows and 
 * columns of the given dense matrix.
 */
void freeDenseMatrix(DenseMatrix denseMatrix) {
    if (denseMatrix == NULL) {
        return;
    }

    for (int i = 0; i < denseMatrix->rowLength; i++) {
        free(denseMatrix->matrix[i]);
    }

    free(denseMatrix->matrix);

    free(denseMatrix);
}

/**
 * This function creates a dense matrix and fills 
 * the elements in the given parse matrix as a set.
 */
DenseMatrix parseMatrixToDenseMatrix(Set parseMatrix, int columnLength, int rowLength) {
    if (parseMatrix == NULL || columnLength <= 0 || rowLength <= 0) {
        return NULL;
    }

    DenseMatrix denseMatrix = initDenseMatrix(columnLength, rowLength);
    if (denseMatrix == NULL) {
        return NULL;
    }

    for (int i = 0; i < rowLength; i++) {
        for (int j = 0; j < columnLength; j++) {
            denseMatrix->matrix[i][j] = 0; 
        }
    }

    for (int i = 0; i < parseMatrix->cardinality; i++) {
        Element elem = parseMatrix->elements[i];
        
        if (elem->type == MATRIX_POINT) { 
            int x = ((int*)elem->data)[0];
            int y = ((int*)elem->data)[1];
            int value = ((int*)elem->data)[2];

            if (x >= 0 && x < rowLength && y >= 0 && y < columnLength) {
                denseMatrix->matrix[x][y] = value;
            }
        }
    }

    return denseMatrix;
}


/**
 * This function creates and returns a parse matrix 
 * as a set depending on the given dense matrix's elements.
 */
Set denseMatrixToParseMatrix(DenseMatrix denseMatrix) {
    if (denseMatrix == NULL) {
        return NULL;
    }

    Set parseMatrix = initSet();
    if (parseMatrix == NULL) {
        return NULL;
    }

    int rowLength = denseMatrix->rowLength;
    int columnLength = denseMatrix->columnLength; 

    for (int i = 0; i < rowLength; i++) {
        for (int j = 0; j < columnLength; j++) {
            int value = denseMatrix->matrix[i][j];

            if (value != 0) {
                Element newElement = createMatrixPointElement(i, j, value);
                if (newElement == NULL || insertElement(parseMatrix, newElement) == 0) {
                    freeSet(parseMatrix);
                    return NULL;
                }
            }
        }
    }

    return parseMatrix;
}


/**
 * This matrix creates a new dense matrix, and the 
 * matrix is the addition of the given two matrices.
 */
DenseMatrix addDenseMatrices(DenseMatrix dm1, DenseMatrix dm2) {
    if (dm1 == NULL || dm2 == NULL || 
        dm1->columnLength != dm2->columnLength || 
        dm1->rowLength != dm2->rowLength) {
        return NULL;
    }

    DenseMatrix resultMatrix = initDenseMatrix(dm1->columnLength, dm1->rowLength);
    if (resultMatrix == NULL) {
        return NULL; 
    }

    for (int i = 0; i < dm1->rowLength; i++) {
        for (int j = 0; j < dm1->columnLength; j++) {
            resultMatrix->matrix[i][j] = dm1->matrix[i][j] + dm2->matrix[i][j];
        }
    }

    return resultMatrix;
}

/**
 * This function creates a new sparse matrix as a set, 
 * and the matrix is the addition of the given 
 * two sparse matrices.
 */
Set addSparseMatrices(Set sm1, Set sm2, int columnLength, int rowLength) {
    if (sm1 == NULL || sm2 == NULL) {
        return NULL;
    }

    Set resultSet = initSet();
    if (resultSet == NULL) {
        return NULL;
    }

    for (int i = 0; i < sm1->cardinality; i++) {
        insertElement(resultSet, sm1->elements[i]);
    }

    for (int i = 0; i < sm2->cardinality; i++) {
        Element elem = sm2->elements[i];

        if (elem->type == MATRIX_POINT) {
            int x = *(int*)(elem->data);
            int y = *((int*)(elem->data) + 1);
            int value = *((int*)(elem->data) + 2);

            if (value == 0) {
                continue;
            }

            int exists = 0; 

            for (int j = 0; j < resultSet->cardinality; j++) {
                Element resultElem = resultSet->elements[j];
                if (resultElem->type == MATRIX_POINT) {
                    int resultX = *(int*)(resultElem->data);
                    int resultY = *((int*)(resultElem->data) + 1);

                    if (resultX == x && resultY == y) {
                        *((int*)(resultElem->data) + 2) += value;
                        exists = 1;
                        break;
                    }
                }
            }

            if (!exists) {
                insertElement(resultSet, elem);
            }
        }
    }
    for (int i = 0; i < resultSet->cardinality; i++) {
        Element elem = resultSet->elements[i];

        if (elem->type == MATRIX_POINT) {
            int value = *((int*)(elem->data) + 2);
         
            if (value == 0) {
                freeElement(elem); 
                
                for (int j = i; j < resultSet->cardinality - 1; j++) {
                    resultSet->elements[j] = resultSet->elements[j + 1];
                }
                resultSet->cardinality--;
                i--;
            }
        }
    }

    return resultSet;
}

