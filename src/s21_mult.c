#include "s21_matrix.h"

// Все операции (кроме сравнения матриц) должны возвращать результирующий код:
// - 0 - OK
// - 1 - Ошибка, некорректная матрица
// - 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = OK;
  if (result && !incorrect_matrix(A)) {
    if (is_nan_inf(A))
      status = ERROR_CALC;
    else {
      int status = s21_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
          }
        }
      }
    }
  } else
    status = INCORRECT_M;
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = OK;
  if (result && !incorrect_matrix(A) && !incorrect_matrix(B)) {
    if (is_nan_inf(A) || is_nan_inf(B))
      status = ERROR_CALC;
    else {
      if ((A->columns == B->rows)) {
        status = s21_create_matrix(A->rows, B->columns, result);
        // строки А (строки С)
        for (int i = 0; i < A->rows; i++) {
          // столбцы B (столбцы С)
          for (int j = 0; j < B->columns; j++) {
            // общий столбцы А == строки В
            for (int k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      } else
        status = ERROR_CALC;
    }
  } else
    status = INCORRECT_M;
  return status;
}