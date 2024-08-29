#ifndef SRC_S21_TEST_H_
#define SRC_S21_TEST_H_

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

#define SUITE_NAME "Unit"
#define TCASE_NAME "Tests"

TCase *tests_s21_create_matrix(void);
TCase *tests_s21_equal_matrix(void);
TCase *tests_s21_sum_matrix(void);
TCase *tests_s21_sub_matrix(void);
TCase *tests_s21_mult_number_matrix(void);
TCase *tests_s21_mult_matrix(void);
TCase *tests_s21_trans_matrix(void);
TCase *tests_s21_det_matrix(void);
TCase *tests_s21_calc_complements(void);
TCase *tests_s21_inverse_matrix(void);

double get_rand(double min, double max);

#endif  // SRC_S21_TEST_H_