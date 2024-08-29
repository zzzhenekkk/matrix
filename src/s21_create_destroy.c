#include "s21_matrix.h"

// Все операции (кроме сравнения матриц) должны возвращать результирующий код:
// - 0 - OK
// - 1 - Ошибка, некорректная матрица
// - 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int incorrect_matrix(matrix_t *matrix) {
  int status = OK;
  if (!matrix)
    status = INCORRECT_M;
  else if (matrix->rows < 1 || matrix->columns < 1) {
    status = INCORRECT_M;
  }
  return status;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = OK;
  if (!result || rows < 1 || columns < 1) {
    status = INCORRECT_M;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (!result->matrix)
      status = INCORRECT_M;
    else
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (!result->matrix[i]) {
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
          status = INCORRECT_M;
        }
      }
  }

  if (!status) {
    result->rows = rows;
    result->columns = columns;
  }

  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (!incorrect_matrix(A)) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}