#include "s21_matrix.h"

// определитель матрицы 2х2
void s21_determinant2x2(matrix_t *A, double *result) {
  *result =
      A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
}

// считаем минор для конкретного элемента
int calc_certain_minor(matrix_t *A, matrix_t *minor, int ind_i, int ind_j) {
  int status = s21_create_matrix(A->rows - 1, A->columns - 1, minor);
  if (status == OK) {
    for (int i = 0, k = 0; i < A->rows; i++) {
      if (i == ind_i) continue;
      for (int j = 0, m = 0; j < A->columns; j++) {
        if (j == ind_j) continue;
        minor->matrix[k][m] = A->matrix[i][j];
        m++;
        // (i >= ind_i) ? (i == 0) ?  i: i - 1: i
      }
      k++;
    }
  }
  return status;
}

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  if (result && !incorrect_matrix(A)) {
    if (is_nan_inf(A))
      status = ERROR_CALC;
    else {
      *result = 0;
      double buf = 0;
      // проверка на квадратность матрицы
      if ((A->rows == A->columns) && (A->rows >= 1)) {
        // для матрицы 1х1
        if (A->rows == 1 && A->columns == 1) {
          *result = A->matrix[0][0];
          // для матрицы 2х2
        } else if (A->rows == 2 && A->columns == 2) {
          s21_determinant2x2(A, result);
        } else {
          for (int i = 0; i < A->columns; i++) {
            matrix_t minor;
            // считаем минор для первой строки
            calc_certain_minor(A, &minor, 0, i);
            // рекурсией считаем определитель
            s21_determinant(&minor, &buf);
            s21_remove_matrix(&minor);
            *result += pow(-1., (double)i) * A->matrix[0][i] * buf;
          }
        }
      } else
        status = ERROR_CALC;
    }
  } else
    status = INCORRECT_M;
  return status;
}

// Минор матрицы, на выход матрица с минорами
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = OK;
  if (result && !incorrect_matrix(A)) {
    if (is_nan_inf(A) || (A->rows != A->columns) || (A->rows < 1) ||
        (A->rows == 1) || (A->columns == 1))
      status = ERROR_CALC;
    else {
      status = s21_create_matrix(A->rows, A->columns, result);
      if (status == OK) {
        matrix_t minor;
        double buf = 0;
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            calc_certain_minor(A, &minor, i, j);
            s21_determinant(&minor, &buf);
            result->matrix[i][j] = pow(-1., (double)(i + j)) * buf;
            buf = 0;
            s21_remove_matrix(&minor);
          }
        }
      }
    }
  } else
    status = INCORRECT_M;
  return status;
}

//обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = OK;
  int single_matrix = 0;

  // проверка на корректную матрицу
  if (A->rows <= 0 || A->columns <= 0) status = INCORRECT_M;

  // проверка на квадратную матрицу
  else if (A->rows != A->columns)
    status = ERROR_CALC;

  // проверка на матрицу из 1 элемента, для нее обртаная: 1/А
  else if (A->rows == 1 && A->columns == 1) {
    if (A->matrix[0][0] != 0) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1 / A->matrix[0][0];
      single_matrix = 1;
    } else
      status = ERROR_CALC;
  }

  if (status == OK && !single_matrix) {
    double det = 0;
    s21_determinant(A, &det);
    if (det != 0) {
      matrix_t buf1, buf2;
      s21_calc_complements(A, &buf1);
      s21_transpose(&buf1, &buf2);
      s21_mult_number(&buf2, 1 / det, result);
      s21_remove_matrix(&buf1);
      s21_remove_matrix(&buf2);
    } else
      status = ERROR_CALC;
  }
  return status;
}

// меняем знаки в матрице на противоположные
// void change_signs (matrix_t *A) {
//   for (int i = 0; i < A->rows; i++) {
//       for (int j = 0; j < A->columns; j++) {
//           A->matrix[i][j] = -A->matrix[i][j];
//       }
//   }
// }

// // печатаем матрицу
// void print_matrix (matrix_t *A) {
//   printf("\n");
//   for (int i = 0; i < A->rows; i++) {
//       for (int j = 0; j < A->columns; j++) {
//           printf("%lf ", A->matrix[i][j]);
//       }
//       printf("\n");
//   }
// }