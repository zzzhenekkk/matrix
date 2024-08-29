#include "s21_matrix.h"

// переворачивание матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (result && !incorrect_matrix(A)) {
    if (is_nan_inf(A))
      status = ERROR_CALC;
    else {
      int status = s21_create_matrix(A->columns, A->rows, result);
      if (status == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[j][i] = A->matrix[i][j];
          }
        }
      }
    }
  } else
    status = INCORRECT_M;
  return status;
}
