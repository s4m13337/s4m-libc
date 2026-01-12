#ifndef MATRIX_H
#define MATRIX_H

#include<stddef.h>    // size_t

#define MAT_AT(m, i, j) (m)->data[(i) * (m)->cols + (j)]
#define MAT_PRINT(m) mat_print(m, #m)

/* Matrix structure */
typedef struct Matrix Matrix;

/* Allocation & freeing function */
Matrix* mat_alloc(size_t rows, size_t cols);
void mat_free(Matrix* m);

/* Print matrix */
void mat_print(Matrix* m, const char* c);

/* Generating basic matrices */
void mat_ones(Matrix* m);    // Matrix with all ones
void mat_eye(Matrix* m);     // Identity matrix
void mat_randf(Matrix* m);   // Matrix with random float elements

/* Operations */
void mat_transpose(Matrix* dst, const Matrix* m);            // Transpose
void mat_sum(Matrix* dst, const Matrix* a, const Matrix* b); // Matrix sum
void mat_dot(Matrix* dst, const Matrix* a, const Matrix* b); // Dot product

/*=================================IMPLEMENTATION=================================*/
#ifdef MATRIX_IMPLEMENTATION

/* Implementation headers */
#include<stdio.h>    // printf
#include<stdlib.h>   // malloc, calloc, free
#include<assert.h>   // assert
#include<time.h>     
#include<math.h>

typedef struct Matrix {
  size_t rows, cols;
  float *data;
} Matrix;

Matrix* mat_alloc(size_t rows, size_t cols){
  Matrix* mat = malloc(sizeof *mat);
  if(!mat){
    perror("Failed to initialize matrix");
    return NULL;
  }

  mat->rows = rows;
  mat->cols = cols;
  mat->data = calloc(rows * cols, sizeof(float)); // Everything is initialized to 0.
  if(!mat->data){
    perror("Failed to initialize matrix data");
    free(mat);
    return NULL;
  }
  return mat;
}

void mat_free(Matrix* mat){
  if(!mat){
    return;
  }
  free(mat->data);
  free(mat);
}

void mat_ones(Matrix* m) {
  for(int i=0; i < m->rows; i++)
    for(int j=0; j < m->cols; j++)
      MAT_AT(m, i, j) = 1.;
}

void mat_eye(Matrix* m) {
  assert(m->rows == m->cols); // Identiy matrix is possible only for square matrices
  for(int i=0; i < m->rows; i++)
    MAT_AT(m, i, i) = 1.;
}

/*
  A simple function to return a random number
  TODO: Create better random number generators. This function is only for prototyping.
 */
float randf() {
  return (float) rand()/RAND_MAX; 
}

void mat_randf(Matrix* m) {
  for(int i=0; i < m->rows; i++)
    for(int j=0; j < m->cols; j++)
      MAT_AT(m, i, j) = randf();
}

void mat_transpose(Matrix* dst, const Matrix *m) {
  assert(dst->rows == m->cols);
  assert(dst->cols == m->rows);
  
  for(int i=0; i < m->rows; i++)
    for(int j=0; j < m->cols; j++)
      MAT_AT(dst, j, i) = MAT_AT(m, i, j);
}

void mat_sum(Matrix* dst, const Matrix* a, const Matrix* b) {
  // Check dimensions of matrices are same
  assert(a->rows == b->rows && b->rows == dst->rows);
  assert(a->cols == b->cols && b->cols == dst->cols);

  for(int i = 0; i < dst->rows; i++)
    for (int j = 0; j < dst->cols; j++)
      MAT_AT(dst, i, j) = MAT_AT(a, i, j) + MAT_AT(b, i, j);
}

void mat_dot(Matrix* dst, const Matrix* a, const Matrix* b){
  assert(a->cols == b->rows);
  assert(dst->rows == a->rows);
  assert(dst->cols == b->cols);

  for(size_t i = 0; i < a->rows; i++){
    for(size_t j = 0; j < b-> cols; j++){
      for(size_t k = 0; k < a->cols; k++){
	MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k , j);
      }
    }
  }
}

void mat_print(Matrix* mat, const char* c){
  printf("%s = [\n", c);
  for(int i=0; i < mat->rows; i++){
    for(int j=0; j < mat->cols; j++){
      printf("\t%f", MAT_AT(mat, i, j));
    }
    printf("\n");
  }
  printf("]\n");
}

#endif // MATRIX_IMPLEMENTATION
#endif // MATRIX_H
