#include <stdio.h>
#include <stdlib.h>
#include "/home/billy/code.d/c.d/memMgt.d/memMgt.h"

//== Structs 
struct matrixType {
    int Nrows;
    int Ncols;
    double **matrix;
};

//== Function Prototypes
struct matrixType *newMatrix(int _rows, int _cols);
void initMatrix(struct matrixType *M, double *_data, int _size);
void showMatrix(struct matrixType *A, char *_header);
struct matrixType *addMatrix(struct matrixType *A, struct matrixType *B);
struct matrixType *subtractMatrix(struct matrixType *A, struct matrixType *B);
struct matrixType *scalarAddMatrix(struct matrixType *A, double _scalar);
struct matrixType *scalarMultMatrix(struct matrixType *A, double _scalar);
struct matrixType *transpose(struct matrixType *A);

//===================================




struct matrixType *multiMatrix(struct matrixType *A, struct matrixType *B) {
    
    // Make sure the the two matrices are compatable (i.e., A->Ncols == B->Nrows)
    if(A->Ncols != B->Nrows) {
        printf("ERROR: multiMatrix(): Mismatched matrix dimensions: A->Ncols: %d, B->Nrows: %d\n", A->Ncols, B->Nrows);
        return NULL;
    } else {
        printf("GOOD!! addMatrix(): Matched matrix dimensions: A->Ncols: %d, B->Nrows: %d\n", A->Ncols, B->Nrows);
    }

    //struct matrixType *Bt;
    //Bt = transpose(B);
    //showMatrix(Bt, "Bt: Used in multiMatrix");
    
    struct matrixType *C;
    C = newMatrix(A->Nrows, B->Ncols);
    if (C == NULL) {
        return NULL;
    }

    // Let's do a little dot product... of sorts. (Note: I should write a dot product function.
    for(int c = 0; c < B->Ncols; c++) {
        for(int r = 0; r < A->Nrows; r++) {
            C->matrix[r][c] = 0.0;
            for(int i = 0; i < A->Ncols; i++) {
                C->matrix[r][c] = C->matrix[r][c] + B->matrix[i][c] * A->matrix[r][i]; 
            }
        }
    }
    
    return C;
}


//===================================
int main() {
    printf("\n This is Memory Management test code. \n\n");
    memMgtInit(100);

    struct matrixType *A;
    struct matrixType *B;
    struct matrixType *C;

    A = newMatrix(2,2);
    initMatrix(A, (double []){1.0, 2.0, 3.0, 4.0}, 4);
    showMatrix(A, "Matrix A: Source matrix");
    
    B = newMatrix(2,2);
    initMatrix(B, (double []){1.5, 2, 2.5, 3}, 4);
    showMatrix(B, "Matrix B: Source matrix");

    C = multiMatrix(A, B);
    showMatrix(C, "Matrix C: multiMatrix matrix");
    
    /*
    struct matrixType *A;
    struct matrixType *B;
    struct matrixType *C;
    struct matrixType *D;
    struct matrixType *E;
    struct matrixType *F;
    struct matrixType *G;

    struct matrixType *AA;
    struct matrixType *AAt;
    struct matrixType *AAtt;

    
    A = newMatrix(2,2);
    initMatrix(A, (double []){1.0, 2.0, 3.0, 4.0}, 4);
    showMatrix(A, "Matrix A: Source matrix");
    
    B = newMatrix(2,2);
    initMatrix(B, (double []){10.0, 20.0, 30.0, 40.0}, 4);
    showMatrix(B, "Matrix B: Source matrix");

    C = addMatrix(A, B);
    showMatrix(C, "Matrix C: Matrix Addition");
    
    D = subtractMatrix(A, B);
    showMatrix(D, "Matrix D: Matrix Subtraction");

    E = scalarMultMatrix(A, 100.0);
    showMatrix(E, "Matrix E: Scalar Multiply");

    F = scalarMultMatrix(A, 0.1);
    showMatrix(F, "Matrix F: Scalar Multiply (Scalar < 0.0)");

    G = scalarAddMatrix(A, 0.07);
    showMatrix(G, "Matrix G: Scalar Add");

    //------------------------
    AA = newMatrix(2,3);
    initMatrix(AA, (double []){1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, 6);
    showMatrix(AA, "Matrix AA: Source matrix");

    AAt = transpose(AA);
    showMatrix(AAt, "Matrix AAt: Tranposed matrix");
 
    AAtt = transpose(AAt);
    showMatrix(AAtt, "Matrix AAt: Tranposed (Transposed matrix)");
    */

    memMgtExit();
    exit(0);
}


//===============================

struct matrixType *newMatrix(int _rows, int _cols) {
    struct matrixType *M;
    double **A;
    int size;
    
    size = _rows * sizeof(double *);
    //printf("newMatrix(): Rows: %d, size: %d\n", _rows, size);
    
    A = (double **)memMgtAlloc(size);
    if (A != NULL) {
        size = _cols * sizeof(double);
        //printf("newMatrix(): colss: %d, size: %d\n", _cols, size);
        for(int r = 0; r < _rows; r++) {
            A[r] = (double *)memMgtAlloc(size);
            if (A == NULL) {
                return NULL;
            }
        }
        M = (struct matrixType *)memMgtAlloc(sizeof(struct matrixType));
        M->Nrows = _rows;
        M->Ncols = _cols;
        M->matrix = A;
        return M;
    }     
    return NULL;
}




void initMatrix(struct matrixType *M, double *_data, int _size) {
    int i = 0;
    
    for(int r = 0; r < M->Nrows; r++) {
        for(int c = 0; c < M->Ncols; c++) {
            if (i < _size) {
                M->matrix[r][c] = _data[i++];
            } else {
                return;
            }
        }
    }
    return;
}


void showMatrix(struct matrixType *A, char *_header) {
    if (_header != NULL) {
        printf("%s\n", _header);
    }
    
    if (A == NULL) {
        printf("Error: showMatrix(): Source matrix is NULL ***\n");
        return;
    }
    
    for(int r = 0; r < A->Nrows; r++) {
        for(int c = 0; c < A->Ncols; c++) {
            printf(" %f ", A->matrix[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}


struct matrixType *addMatrix(struct matrixType *A, struct matrixType *B) {
    if((A->Nrows != B->Nrows) || (A->Ncols != B->Ncols)) {
        printf("ERROR: addMatrix(): Mismatched matrix sizes\n");
        return NULL;
    }
    
    struct matrixType *C;
    C = newMatrix(A->Nrows, A->Ncols);
    if (C == NULL) {
        return NULL;
    }
    
    for(int r = 0; r < C->Nrows; r++) {
        for(int c = 0; c < C->Ncols; c++) {
            C->matrix[r][c] = A->matrix[r][c] + B->matrix[r][c];
        }
    }

    return C;
}

struct matrixType *subtractMatrix(struct matrixType *A, struct matrixType *B) {
    if((A->Nrows != B->Nrows) || (A->Ncols != B->Ncols)) {
        printf("ERROR: addMatrix(): Mismatched matrix sizes\n");
        return NULL;
    }
    
    struct matrixType *C;
    C = newMatrix(A->Nrows, A->Ncols);
    if (C == NULL) {
        return NULL;
    }
    
    for(int r = 0; r < C->Nrows; r++) {
        for(int c = 0; c < C->Ncols; c++) {
            C->matrix[r][c] = A->matrix[r][c] - B->matrix[r][c];
        }
    }

    return C;
}


struct matrixType *scalarAddMatrix(struct matrixType *A, double _scalar) {
    struct matrixType *C;
    C = newMatrix(A->Nrows, A->Ncols);
    if (C == NULL) {
        return NULL;
    }
    
    for(int r = 0; r < C->Nrows; r++) {
        for(int c = 0; c < C->Ncols; c++) {
            C->matrix[r][c] = A->matrix[r][c] + _scalar;
        }
    }

    return C;
}


struct matrixType *scalarMultMatrix(struct matrixType *A, double _scalar) {
    struct matrixType *C;
    C = newMatrix(A->Nrows, A->Ncols);
    if (C == NULL) {
        return NULL;
    }
    
    for(int r = 0; r < C->Nrows; r++) {
        for(int c = 0; c < C->Ncols; c++) {
            C->matrix[r][c] = A->matrix[r][c] * _scalar;
        }
    }

    return C;
}


struct matrixType *transpose(struct matrixType *A) {
    if(A == NULL) {
        printf("ERROR: transpose(): NULL inpute matrix.\n");
        return NULL;
    }
    
    struct matrixType *C;

    C = newMatrix(A->Ncols, A->Nrows);
    if (C == NULL) {
        return NULL;
    }
    
    for(int r = 0; r < A->Nrows; r++) {
        for(int c = 0; c < A->Ncols; c++) {
            C->matrix[c][r] = A->matrix[r][c];
        }
    }

    return C;
}

