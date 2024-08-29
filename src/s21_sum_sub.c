#include "s21_matrix.h"

// Все операции (кроме сравнения матриц) должны возвращать результирующий код:
// - 0 - OK
// - 1 - Ошибка, некорректная матрица
// - 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (!incorrect_matrix(A) && !incorrect_matrix(B) && result) {
    if (!(A->columns == B->columns) || !(A->rows == B->rows) || is_nan_inf(A) ||
        is_nan_inf(B))
      status = ERROR_CALC;
    else {
      int status = s21_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    }
  } else
    status = INCORRECT_M;
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (!incorrect_matrix(A) && !incorrect_matrix(B) && result) {
    if ((A->columns != B->columns) || (A->rows != B->rows) || is_nan_inf(A) ||
        is_nan_inf(B))
      status = ERROR_CALC;
    else {
      int status = s21_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    }
  } else
    status = INCORRECT_M;
  return status;
}

int is_nan_inf(matrix_t *A) {
  int status = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) {
        status = 1;
        break;
      }
      if (status) break;
    }
  }
  return status;
}