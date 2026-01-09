#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<assert.h>

#define MAT_GET(m, i, j) (m)->data[(i) * (m)->cols + (j)]
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
  mat->data = calloc(rows * cols, sizeof(float));
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

void mat_sum(Matrix* dst, Matrix* a, Matrix* b) {
  // Check dimensions of matrices are same
  assert(a->rows == b->rows && b->rows == dst->rows);
  assert(a->cols == b->cols && b->cols == dst->cols);

  for(int i = 0; i < dst->rows; i++)
    for (int j = 0; i < dst->cols; j++)
      MAT_GET(dst, i, j) = MAT_GET(a, i, j) + MAT_GET(b, i, j);
}

void mat_print(Matrix* mat, const char* c){
  printf("%s = [\n", c);
  for(int i=0; i < mat->rows; i++){
    for(int j=0; j < mat->cols; j++){
      printf("\t%f", MAT_GET(mat, i, j));
    }
    printf("\n");
  }
  printf("]\n");
}

int main(){
  Matrix* m1 = mat_alloc(3, 3);
  Matrix* m2 = mat_alloc(3, 3);
  Matrix* m3 = mat_alloc(3, 3);
  
  for(int i=0; i<9; i++)
    (m1->data)[i] = i*i;

  for(int i=0; i<9; i++)
    (m2->data)[i] = i*i*i;

  MAT_PRINT(m1);
  MAT_PRINT(m2);

  mat_sum(m3, m1, m2);
  MAT_PRINT(m3);
  
  mat_free(m1);
  mat_free(m2);
  mat_free(m3);
  
  return 0;
}



