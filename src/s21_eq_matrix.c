#include "s21_matrix.h"

// Все операции (кроме сравнения матриц) должны возвращать результирующий код:
// - 0 - OK
// - 1 - Ошибка, некорректная матрица
// - 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (!incorrect_matrix(A) && !incorrect_matrix(B)) {
    if ((A->columns != B->columns) || (A->rows != B->rows))
      result = FAILURE;
    else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
            result = FAILURE;
            break;
          }
        }
      }
    }
  } else
    result = FAILURE;
  return result;
}
