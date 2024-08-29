#ifndef S21_MATRIX
#define S21_MATRIX

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SUCCESS 1
#define FAILURE 0

// Все операции (кроме сравнения матриц) должны возвращать результирующий код:
// - 0 - OK
// - 1 - Ошибка, некорректная матрица
// - 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)
#define OK 0
#define INCORRECT_M 1
#define ERROR_CALC 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// переворачивание матрицы
int s21_transpose(matrix_t *A, matrix_t *result);
// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);
// Минор матрицы, на выход матрица с минорами
int s21_calc_complements(matrix_t *A, matrix_t *result);
// считаем минор для конкретного элемента
int calc_certain_minor(matrix_t *A, matrix_t *minor, int ind_i, int ind_j);
//обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

////////////// дополнительно /////////////////
// проверка на указатель, на rows и columns, 0 - все гуд
int incorrect_matrix(matrix_t *matrix);
// проверка матрицы на inf и nan, 1 - если есть
int is_nan_inf(matrix_t *A);
// определитель матрицы 2х2
void s21_determinant2x2(matrix_t *A, double *result);
// меняем знаки в матрице на противоположные
// void change_signs (matrix_t *A);
// // печатаем матрицу
// void print_matrix (matrix_t *A);

#endif  // S21_MATRIX
