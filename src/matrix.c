#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<assert.h>

#define MAT_AT(m, i, j) (m)->data[(i) * (m)->cols + (j)]
#define MAT_PRINT(m) mat_print(m, #m)

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

/* Creating basic matrices */
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

// Unary operations
void mat_transpose(Matrix* dst, Matrix *m) {
  assert(dst->rows == m->cols);
  assert(dst->cols == m->rows);
  
  for(int i=0; i < m->rows; i++)
    for(int j=0; j < m->cols; j++)
      MAT_AT(dst, j, i) = MAT_AT(m, i, j);
}

// Binary operations
void mat_sum(Matrix* dst, Matrix* a, Matrix* b) {
  // Check dimensions of matrices are same
  assert(a->rows == b->rows && b->rows == dst->rows);
  assert(a->cols == b->cols && b->cols == dst->cols);

  for(int i = 0; i < dst->rows; i++)
    for (int j = 0; j < dst->cols; j++)
      MAT_AT(dst, i, j) = MAT_AT(a, i, j) + MAT_AT(b, i, j);
}

void mat_dot(Matrix* dst, Matrix* a, Matrix* b){
  assert(a->cols == b->rows);
  assert(dst->rows == a->rows);
  assert(dst->cols == b->cols);

  for(size_t i = 0; i < a->rows; i++){
    for(size_t j = 0; j < b-> cols; j++)
      
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

int main(){
  Matrix* m1 = mat_alloc(3, 3);

  mat_ones(m1);
  MAT_PRINT(m1);

  Matrix* m2 = mat_alloc(3, 3);
  MAT_PRINT(m2);

  Matrix* m3 = mat_alloc(5, 5);
  mat_eye(m3);
  MAT_PRINT(m3);

  srand(time(NULL));
  Matrix* mat_r = mat_alloc(5, 2);
  mat_randf(mat_r);
  MAT_PRINT(mat_r);

  printf("Matrix transpose\n");
  Matrix* A = mat_alloc(4, 3);
  mat_randf(A);
  MAT_PRINT(A);
  Matrix* AT = mat_alloc(3, 4); // Rows & colums have to be interchanged in transposed matrix
  mat_transpose(AT, A);
  MAT_PRINT(AT);

  mat_free(A);
  mat_free(AT);
  /*
  for(int i=0; i<9; i++)
    (m1->data)[i] = i*i;

  for(int i=0; i<9; i++)
    (m2->data)[i] = i*i*i;

  MAT_PRINT(m1);
  MAT_PRINT(m2);

  mat_sum(m3, m1, m2);
  MAT_PRINT(m3);
  mat_free(m3);
  */
  
  mat_free(m1);
  mat_free(m2);
  mat_free(m3);
  mat_free(mat_r);
  
  return 0;
}



