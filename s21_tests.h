#ifndef S21_TESTS_H
#define S21_TESTS_H

#include <check.h>
#include <stdlib.h>  // для EXIT_SUCCESS : EXIT_FAILURE в s21_tests.c

#include "../s21_matrix.h"

Suite *suite_matrix(void);

#endif  // S21_TESTS_H