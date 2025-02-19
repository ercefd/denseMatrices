#include "set.h"

/**
 * This function initializes a set without an element and returns it.
 */
Set initSet() {
    Set newSet = malloc(sizeof(Set_t));

    if (newSet == NULL) {
        return NULL;
    }

    newSet->elements = NULL;
    newSet->cardinality = 0;
    return newSet;
}



/**
 * This function creates an integer-typed element and returns it. 
 * It allocates memory for both the element and the integer.
 */
Element createIntegerElement(int data) {
    Element newElement = malloc(sizeof(Element_t));

    if (newElement == NULL) {
        return NULL;
    }

    newElement->type = INTEGER;
    newElement->data = malloc(sizeof(int));

    if (newElement->data == NULL) {
        free(newElement);
        return NULL;
    }

    *(int*)(newElement->data) = data;
    return newElement;
}


/**
 * This function creates an float-typed element and returns it. 
 * It allocates memory for both the element and the float.
 */
Element createFloatElement(float data) {
    Element newElement = malloc(sizeof(Element_t));

    if (newElement == NULL) {
        return NULL;
    }

    newElement->type = FLOAT;
    newElement->data = malloc(sizeof(float));

    if (newElement->data == NULL) {
        free(newElement);
        return NULL;
    }

    *(float*)(newElement->data) = data;

    return newElement;
}


/**
 * This function creates an string-typed element and returns it. 
 * It allocates memory for both the element and the string.
 * This function uses the `strlen` and the `strcpy` functions.
 */
Element createStringElement(char* data) {
    Element newElement = malloc(sizeof(Element_t));

    if (newElement == NULL) {
        return NULL;
    }

    newElement->type = STRING;

    size_t length = strlen(data) + 1;

    newElement->data = malloc(length);

    if (newElement->data == NULL) {
        free(newElement);
        return NULL;
    }

    strcpy((char*)newElement->data, data);
    return newElement;
}

/**
 * This function creates an matrix-point-typed element and returns it. 
 * It allocates memory for both the element and the matrix point.
 */
Element createMatrixPointElement(int x, int y, int data) {

    Element newElement = malloc(sizeof(Element_t));
    if (newElement == NULL) {
        return NULL;
    }

    newElement->type = MATRIX_POINT;

    int* matrixPoint = malloc(3 * sizeof(int));
    if (matrixPoint == NULL) {
        free(newElement);
        return NULL;
    }

    matrixPoint[0] = x;
    matrixPoint[1] = y;
    matrixPoint[2] = data;

    newElement->data = matrixPoint;

    return newElement;
}


/**
 * This function compares two elements to see if they are identical. 
 * First, it checks if the types are identical. If they are the same, 
 * it checks if the data are the same. However, this function does not 
 * compare addresses because the value from two different addresses 
 * can be the same. It returns one if the elements are the same; 
 * otherwise, it returns zero. This function uses the `strcmp` function.
 */
int isSame(Element e1, Element e2) {
    if (e1->type != e2->type) {
        return 0;
    }

    switch (e1->type) {
        case INTEGER: {

            int val1 = *(int*)(e1->data);
            int val2 = *(int*)(e2->data);
            return (val1 == val2) ? 1 : 0; 
        }

        case FLOAT: {

            float val1 = *(float*)(e1->data);
            float val2 = *(float*)(e2->data);
            return (val1 == val2) ? 1 : 0; 
        }

        case STRING: {
            char* str1 = (char*)e1->data;
            char* str2 = (char*)e2->data;
            return (strcmp(str1, str2) == 0) ? 1 : 0;
        }

        case MATRIX_POINT: {
            int* point1 = (int*)e1->data;
            int* point2 = (int*)e2->data;
            return (point1[0] == point2[0] && point1[1] == point2[1] && point1[2] == point2[2]) ? 1 : 0;
        }

        default:
            return 0;
    }
}


/**
 * This function checks if the given element is in the set or not. 
 * It does not compare the addresses. It returns one if the given 
 * element is in the set; otherwise, it returns zero.
 */
int in(Set set, Element element) {
    for (int i = 0; i < set->cardinality; i++) {
        if (isSame(set->elements[i], element)) {
            return 1;
        }
    }
    return 0;
}

/**
 * This function inserts a new element into the specified set. 
 * It's important to note that the same element cannot appear more than once in the set. 
 * If the insertion is successful, the function returns 1; otherwise, it returns 0. 
 * We’ll be using the realloc function to handle memory allocation dynamically.
 */
int insertElement(Set set, Element element) {
    if (set == NULL || element == NULL || in(set, element)) {
        return 0; 
    }

    Element* newElements = realloc(set->elements, (set->cardinality + 1) * sizeof(Element));
    if (newElements == NULL) {
        return 0;
    }

    set->elements = newElements;

    Element newElement = malloc(sizeof(Element_t));
    if (newElement == NULL) {
        return 0;
    }

    *newElement = *element;
    if (newElement->type == MATRIX_POINT) {
        int* newMatrixPoint = malloc(3 * sizeof(int));
        if (newMatrixPoint == NULL) {
            free(newElement);
            return 0;
        }
        memcpy(newMatrixPoint, element->data, 3 * sizeof(int));
        newElement->data = newMatrixPoint;
    }

    set->elements[set->cardinality] = newElement;
    set->cardinality++;

    return 1;
}







/**
 * This function removes the given element in the set. 
 * It returns one if removal is successful; otherwise, 
 * it returns zero. This function uses the `realloc` function.
 */
int removeElement(Set set, Element element) {
    if (set == NULL || element == NULL) {
        return 0; 
    }

    int index = -1; 
    
    for (int i = 0; i < set->cardinality; i++) {
        if (isSame(set->elements[i], element)) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return 0;
    }

    for (int i = index; i < set->cardinality - 1; i++) {
        set->elements[i] = set->elements[i + 1];
    }

    set->cardinality--;

    Element* newElements = realloc(set->elements, set->cardinality * sizeof(Element));
    if (set->cardinality > 0 && newElements == NULL) {
        return 0;
    }
    
    set->elements = newElements;

    return 1;
}

/**
 * This function creates and returns a new set, which is united of the given sets.
 */
Set unite(Set s1, Set s2) {
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }

    Set newSet = initSet();
    if (newSet == NULL) {
        return NULL;
    }

    for (int i = 0; i < s1->cardinality; i++) {
        insertElement(newSet, s1->elements[i]);
    }

    for (int i = 0; i < s2->cardinality; i++) {
        if (!in(newSet, s2->elements[i])) {
            insertElement(newSet, s2->elements[i]);
        }
    }

    return newSet;
}

/**
 * This function creates and returns a new set, which is intersected of the given sets.
 */
/**
 * This function creates and returns a new set, which is intersected of the given sets.
 */
Set intersect(Set s1, Set s2) {
    if (s1 == NULL || s2 == NULL) {
        return NULL;
    }

    Set newSet = initSet();
    if (newSet == NULL) {
        return NULL;
    }

    for (int i = 0; i < s1->cardinality; i++) {
        for (int j = 0; j < s2->cardinality; j++) {
            if (isSame(s1->elements[i], s2->elements[j])) {
                insertElement(newSet, s1->elements[i]);
                break;
            }
        }
    }

    return newSet;
}


/**
 * This function creates and returns a new set, which is 
 * subtracted from the first given set by the second one.
 */
Set substract(Set s1, Set s2) {
    Set newSet = initSet();
    if (newSet == NULL || s1 == NULL || s2 == NULL) {
        freeSet(newSet);
        return NULL;
    }

    for (int i = 0; i < s1->cardinality; i++) {
        if (!in(s2, s1->elements[i])) {
            insertElement(newSet, s1->elements[i]);
        }
    }

    return newSet;
}


/**
 * This function prints the given element depending on its type.
 */
void printElement(Element element) {
    if (element == NULL) {
        printf("Element is NULL.\n");
        return;
    }

    switch (element->type) {
        case INTEGER:
            printf("Integer: %d\n", *(int*)(element->data));
            break;
        case FLOAT:
            printf("Float: %.2f\n", *(float*)(element->data));
            break;
        case STRING:
            printf("String: %s\n", (char*)(element->data));
            break;
        case MATRIX_POINT: {
            int* matrixPointData = (int*)(element->data);
            printf("Matrix Point: (%d, %d, %d)\n", matrixPointData[0], matrixPointData[1], matrixPointData[2]);
            break;
        }
        default:
            printf("Unknown type.\n");
            break;
    }
}


/**
 * This function prints the given set element by element depending on its type.
 */
void printSet(Set set) {
    if (set == NULL) {
        printf("Set is NULL.\n");
        return;
    }

    printf("Set contains %d elements:\n", set->cardinality);

    for (int i = 0; i < set->cardinality; i++) {
        printf("Element %d: ", i + 1); 
        printElement(set->elements[i]);
    }
}

void freeElement(Element element) {
    if (element == NULL) {
        return;
    }

    switch (element->type) {
        case INTEGER:
            free(element->data);
            break;
        case FLOAT:
            free(element->data);
            break;
        case STRING:
            free(element->data);
            break;
        case MATRIX_POINT:
            free(element->data);
            break;
        default:
            break;
    }

    free(element);
}




/**
 * This element deallocates all data in the given set and the set itself.
 */
void freeSet(Set set) {
    if (set == NULL) {
        return;
    }

    for (int i = 0; i < set->cardinality; i++) {
        freeElement(set->elements[i]);
    }

    free(set->elements);
    free(set);
}

