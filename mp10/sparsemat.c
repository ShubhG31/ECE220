#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


/* Intro paragraph:
**
** Implemented load_tuples function by opening a file, reading the row and
** column size, then reading all the remaining elements and creating a dynamic
** matrix of type sp_tuples containing all the elements. If there is an error 
** in opening the file, return NULL. To create the matrix, the set_tuples
** function is called, which handles any insertions, deletions, and updating
** elements. Once finished reading the file, the function closes the file and 
** returns.
**
** Implemented gv_tuples function by traversing the list and searching for 
** an element with the given row and col. If we find a node satisfying the given
** row, col index, return that node. If not, then return 0. To check if the row
** col index is already beyond the row, col index of the current node, the 
** beyondIndex helper function is used.
**
** The beyondIndex helper function simply returns 1 if the row, col index
** of the node is greater than the row, col index given.
**
** Implemented the set_tuples function with the help of three helper functions: 
** beyondIndex, createNode, and isApproxZero. createNode creates a new node given 
** a matrix, a pointer to a pointer to a previous node, and a pointer to the next 
** node, as well as the row, col index and the value. The setTuples function handles 
** 5 different base cases differently:
    // Case 0: Element to be inserted is 0, and does not exist in list
    // Case 1: Empty list
    // Case 2: Insert at head
    // Case 3: Insert in between elements (the "expected normal")
    // Case 4: Element already exists
    // Case 5: Insert at tail
** The method of handling all of these cases are commented on the actual function 
** and provide more information.
**
** Implemented the save_tuples function by first opening the file. If the open fails, 
** the function returns NULL. If sucessful, first write out the dimensions of the matrix. 
** Then, traverse the list to write out all the values of the node in order. Once the 
** list is fully traversed, the function closes the file and returns.
**
** Implemented add_tuples function by first checking if addition is possible. If not 
** possible, return NULL. Then, we can create the return matrix by copying first matA 
** into the return matrix. Then, we traverse matB and call on set_tuples to handle adding 
** the element in matB into the return matrix. The value of the node to be inserted is 
** gotten using the gv_tuples function, added by the value of the element in matB. The 
** set_tuples function handles the possibility of a zero element to be inserted and the 
** deletion, while the gv_tuples function handles the possibility that the element in return 
** matrix does not exist and returns 0. Finally at the end, we return the return matrix created.
**
** Implemented the destroy_tuples function by checking if the input mat_t matrix is NULL. 
** If so, return NULL. Then, traverse the whole list and free each individual node, making
** sure to keep a temporary pointer pointing to the node to be deleted while the next pointer 
** is set to the next, next node, before calling free ** on the node to be deleted (which is 
** what the temp pointer points to). After freeing all the nodes, free the matrix mat_t itself, 
** and then return.
**
** Partners: htd2, clegras3
 */

// Test helper function to print matrix
void printMat(sp_tuples* mat_t) {
    printf("Printing matrix:\n");
    sp_tuples_node* currentNode = mat_t->tuples_head;
    while (currentNode != NULL) {
        printf("%d %d %lf\n", currentNode->row, currentNode->col, currentNode->value);
        currentNode = currentNode->next;
    }
    printf("End print matrix.\n");
}

sp_tuples * load_tuples(char* input_file) {
    FILE* inFilePtr = fopen(input_file, "r");

    if (inFilePtr == NULL) return NULL;

    int rowSize, colSize;

    fscanf(inFilePtr, "%d %d", &rowSize, &colSize);

    // printf("%d %d\n", rowSize, colSize);

    // Create the sp_tuples struct
    sp_tuples* matrix = (sp_tuples*)malloc(sizeof(sp_tuples));
    matrix->m = rowSize;
    matrix->n = colSize;
    matrix->nz = 0;
    matrix->tuples_head = NULL;

    int row, col;
    double value;
    // keep reading fscanf while it is sucessfull (3 reads)
    while (fscanf(inFilePtr, "%d %d %lf", &row, &col, &value) != EOF) {
        // printf("%d %d %lf \n", row, col, value);
        set_tuples(matrix, row, col, value);
        // printf("Sucess with %d %d %lf \n", row, col, value);
        // Print for test
        // printMat(matrix);
    }
    
    // Done reading, so close file and return the created matrix
    fclose(inFilePtr);
    return matrix;
}

// Helper function for set_tuples and gv_tuples

// Returns 1 if the index of the node given is greater than the single index of the provided row, col values
int beyondIndex(sp_tuples_node* node, int row, int col) {
    return (node->row > row || (node->row == row && node->col > col));
}

double gv_tuples(sp_tuples* mat_t, int row, int col) {
    // gv_tuples is never called with invalid matrix, but just in case
    // return 0 if the matrix is invalid
    if (mat_t == NULL) return 0;

    // create pointer to node so we can traverse the list
    sp_tuples_node* currentNode = mat_t->tuples_head;
    // traverse over the matrix, searching for the row and col
    // Assume the list is null terminated and fits within the bounds
    while (currentNode != NULL) {
        if (currentNode->row == row && currentNode->col == col) {
            // found the coordinate needed, so return its value
            return currentNode->value;
        }
        // Check if the bounds are beyond the current index,
        // meaning the node does not exist to avoid extra searches
        if (beyondIndex(currentNode, row, col)) {
            return 0;
        }
        // Move current node pointer forward
        currentNode = currentNode->next;
    }
    // if the coordinate doesn't exist, the value is 0
    // so return 0
    return 0;
}

// Helper functions for set_tuples

// Creates a new node and inserts it in between previousNode and nextNode with the given row, col, and value
// Assumes the node to be inserted is given in the right position relative to previousNode and nextNode
// Will handle NULL cases
// Will NOT handle deleting cases
// If inserting at head, previousNode is supposed to be NULL
void createNode(sp_tuples* mat_t, sp_tuples_node** previousNode, sp_tuples_node* nextNode, int row, int col, double value) {
    // Create the new node
    
    // printf("createNode called for %d %d %lf\n", row, col, value);

    sp_tuples_node* newNode = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;

    // Set the previous node to point to the new node
    // Check if previous node is the NULL, which means modifying the head is needed
    if (previousNode == NULL) {
        mat_t->tuples_head = newNode;
    } else {
        // Insert new node, whether at the head, between nodes, or at the end of the list
        (*previousNode)->next = newNode;
    }
    // Set new node's next pointer to the given nextNode
    newNode->next = nextNode;

    // update the nz count
    mat_t->nz += 1;
    return;
}

// Returns 1 if the double value is approximately zero
// Specifically, if value is within the range |value| < 10e-7
int isApproxZero(double value) {
    return (value > -10e-7 && value < 10e-7);
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value) {
    // There are multiple cases to handle:
    // Case 0: Element to be inserted is 0, and does not exist in list
    // Case 1: Empty list
    // Case 2: Insert at head
    // Case 3: Insert in between elements (the "expected normal")
    // Case 4: Element already exists
    // Case 5: Insert at tail

    // Create current and previous node pointers to traverse through the list
    sp_tuples_node* currentNode = mat_t->tuples_head;
    sp_tuples_node* previousNode = NULL;

    // Handle case 0: Element to be inserted is 0, and does not exist in list
    if (isApproxZero(value)) {
        if (isApproxZero(gv_tuples(mat_t, row, col))) {
            // Don't insert anything and return
            return;
        }
    }

    // Handle case 1: empty list
    if (currentNode == NULL) {
        createNode(mat_t, NULL, NULL, row, col, value);
        // Return since done
        return;
    }

    // Traverse the list, looking for suitable place
    while (currentNode != NULL) {
        // printf("Traversing...\n");
        // Check if current node is the same index as the new node to be inserted
        if (currentNode->row == row && currentNode->col == col) {
            // Handle case 4: Element already exists
            // The node exists, so overwrite the data if value is nonzero, or delete node if value is zero
            // We cannot directly test if a double is exactly 0, so we use the helper func isApproxZero
            // to approximate if value is 0
            if (!isApproxZero(value)) {
                currentNode->value = value;
            } else {
                // Handle deleting the node
                // Check if previous node was NULL or not
                if (previousNode == NULL) {
                    // This means that we have to handle deleting at the head
                    mat_t->tuples_head = currentNode->next;
                } else {
                    // This means we can handle deleting the node normally, ie the node is after an existing node
                    previousNode->next = currentNode->next;
                }
                // Free the current node
                free(currentNode);
            }
            // Return since we're done
            return;
        }

        // Check if current node index is already beyond node index to insert
        // This means we have to create the new node, at the position before the current node
        if (beyondIndex(currentNode, row, col)) {
            // Handle inserting the node
            // Create the new node
            // Check if previous node was NULL or not
            if (previousNode != NULL) {
                // Handle case 3: insert in between two nodes
                createNode(mat_t, &previousNode, currentNode, row, col, value);
            } else {
                // This means we have to handle inserting at the head
                // Handle case 2: Insert at head
                createNode(mat_t, NULL, currentNode, row, col, value);
            }
            // Done inserting, so return
            return;
        }

        // Continue traversing list since suitable position to insert node was not found
        // Set previous node to current node, then current node to next node
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    // The node is to be inserted has index greater than all the existing nodes
    // Handle case 5: Insert at tail
    // Create the new node
    createNode(mat_t, &previousNode, NULL, row, col, value);
    
    // MARVEL AT THIS WORK OF ART AND RETURN
    return;
}



void save_tuples(char* file_name, sp_tuples * mat_t) {
    // if mat_t is NULL, return
    if (mat_t == NULL) return;

    FILE* outFilePtr = fopen(file_name, "w");
    if (outFilePtr == NULL) return;
    
    // write out the dimensions
    fprintf(outFilePtr, "%d %d\n", mat_t->m, mat_t->n);

    sp_tuples_node* currentNode = mat_t->tuples_head;
    // traverse the list
    while (currentNode != NULL) {
        fprintf(outFilePtr, "%d %d %lf\n", currentNode->row, currentNode->col, currentNode->value);
        currentNode = currentNode->next;
    }

    // Done writing all elements in list, so close file and return
    fclose(outFilePtr);
	return;
}



sp_tuples* add_tuples(sp_tuples* matA, sp_tuples* matB) {
    // check if size of matA matches size of matB
    // If the size is not the same, addition is not possible, and return NULL
    if (matA->m != matB->m || matA->n != matB->n) return NULL;

    // create the return matrix
    sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
    retmat->m = matA->m;
    retmat->n = matA->n;
    retmat->nz = 0;
    retmat->tuples_head = NULL;

    // traverse over matA
    sp_tuples_node* currentNode = matA->tuples_head;
    while (currentNode != NULL) {
        set_tuples(retmat, currentNode->row, currentNode->col, currentNode->value);
        currentNode = currentNode->next;
    }

    // traverse over matB and add the values to retmat
    currentNode = matB->tuples_head;
    int curRow, curCol;
    double addValue;
    while (currentNode != NULL) {
        curRow = currentNode->row;
        curCol = currentNode->col;
        addValue = gv_tuples(retmat, curRow, curCol) + currentNode->value;
        set_tuples(retmat, curRow, curCol, addValue);
        currentNode = currentNode->next;
    }

	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB) { 
    // always return NULL since function is optional anyway
    return NULL;
}


	
void destroy_tuples(sp_tuples* mat_t) {
    // Check if mat_t is NULL
    // if so, simply return
    if (mat_t == NULL) return;

    // Traverse the whole list and free all nodes
	sp_tuples_node* currentNode = mat_t->tuples_head;
    sp_tuples_node* tmp;
    while (currentNode != NULL) {
        tmp = currentNode;
        currentNode = currentNode->next;
        free(tmp);
    }

    // Finally free the actual sp_tuples matrix itself
    free(mat_t);

    return;
}  