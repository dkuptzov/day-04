#include <stdlib.h>

#include "../s21_matrix.h"
#include "s21_tests.h"

START_TEST(test_0) {
  // Матрица создана и просто проверяю один элемент
  int x = 1;
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  ck_assert_int_eq(x, A.matrix[0][0]);
  s21_remove_matrix(&A);
}

START_TEST(test_1) {
  // Матрица есть NULL
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}

START_TEST(test_2) {
  // Сравнение матриц 1 Равны
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_3) {
  // Сравнение матриц 2 Равны
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.123456789;
  A.matrix[0][1] = 2.234567890;
  A.matrix[1][0] = 3.345678901;
  A.matrix[1][1] = 4.456789012;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1.123456789;
  B.matrix[0][1] = 2.234567890;
  B.matrix[1][0] = 3.345678901;
  B.matrix[1][1] = 4.456789012;
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_4) {
  // Сравнение матриц 3 Равны
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 11111111111.123456789;
  A.matrix[0][1] = 22222222222.234567890;
  A.matrix[1][0] = 33333333333.345678901;
  A.matrix[1][1] = 44444444444.456789012;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 11111111111.123456789;
  B.matrix[0][1] = 22222222222.234567890;
  B.matrix[1][0] = 33333333333.345678901;
  B.matrix[1][1] = 44444444444.456789012;
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_5) {
  // Сравнение матриц 4 Не Равны
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 11111111111.123456789;
  A.matrix[0][1] = 22222222222.234567890;
  A.matrix[1][0] = 33333333333.345678901;
  A.matrix[1][1] = 44444444444.456789012;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 11111111111.123456789;
  B.matrix[0][1] = 22222222222.234567890;
  B.matrix[1][0] = 33333333333.345678901;
  B.matrix[1][1] = 44444444444.556789012;
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_6) {
  // Сравнение матриц 5 Не Равны
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.023456789;
  A.matrix[0][1] = 0.234567890;
  A.matrix[1][0] = 0.345678901;
  A.matrix[1][1] = 0.456789012;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.123456789;
  B.matrix[0][1] = 0.234567890;
  B.matrix[1][0] = 0.345678901;
  B.matrix[1][1] = 0.556789012;
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_7) {
  // Сравнение матриц 6 Не Равны
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.000001;
  A.matrix[0][1] = 0.000001;
  A.matrix[1][0] = 0.000001;
  A.matrix[1][1] = 0.000002;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.000001;
  B.matrix[0][1] = 0.000001;
  B.matrix[1][0] = 0.000001;
  B.matrix[1][1] = 0.000001;
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_8) {
  // Сложение матриц 1
  matrix_t A, B, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 1;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = 1;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 2;
  C.matrix[0][1] = 2;
  C.matrix[1][0] = 2;
  C.matrix[1][1] = 2;
  s21_sum_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_9) {
  // Сложение матриц 2
  matrix_t A, B, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 111.111;
  A.matrix[0][1] = 222.222;
  A.matrix[1][0] = 333.333;
  A.matrix[1][1] = 444.444;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 111.111;
  B.matrix[0][1] = 222.222;
  B.matrix[1][0] = 333.333;
  B.matrix[1][1] = 444.444;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 222.222;
  C.matrix[0][1] = 444.444;
  C.matrix[1][0] = 666.666;
  C.matrix[1][1] = 888.888;
  s21_sum_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_10) {
  // Сложение матриц 3
  matrix_t A, B, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 111.911999;
  A.matrix[0][1] = 222.922999;
  A.matrix[1][0] = 333.933999;
  A.matrix[1][1] = 444.944999;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 111.911999;
  B.matrix[0][1] = 222.922999;
  B.matrix[1][0] = 333.933999;
  B.matrix[1][1] = 444.944999;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 223.823998;
  C.matrix[0][1] = 445.845998;
  C.matrix[1][0] = 667.867998;
  C.matrix[1][1] = 889.889998;
  s21_sum_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_11) {
  // Сложение матриц 4
  matrix_t A, B, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.4567637658;
  A.matrix[0][1] = 0.56884756456;
  A.matrix[1][0] = 0.58624782375;
  A.matrix[1][1] = 0.34564385634;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.000001;
  B.matrix[0][1] = 0.000001;
  B.matrix[1][0] = 0.000001;
  B.matrix[1][1] = 0.000001;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 0.4567647658;
  C.matrix[0][1] = 0.56884856456;
  C.matrix[1][0] = 0.58624882375;
  C.matrix[1][1] = 0.34564485634;
  s21_sum_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_12) {
  // Вычитание матриц 1
  matrix_t A, B, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 10;
  A.matrix[0][1] = 10;
  A.matrix[1][0] = 10;
  A.matrix[1][1] = 10;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 9;
  B.matrix[0][1] = 9;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 9;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 1;
  C.matrix[1][0] = 1;
  C.matrix[1][1] = 1;
  s21_sub_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_13) {
  // Вычитание матриц 2
  matrix_t A, B, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 10.001;
  A.matrix[0][1] = 10.001;
  A.matrix[1][0] = 10.001;
  A.matrix[1][1] = 10.001;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 9.001;
  B.matrix[0][1] = 9.001;
  B.matrix[1][0] = 9.001;
  B.matrix[1][1] = 9.001;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 1;
  C.matrix[0][1] = 1;
  C.matrix[1][0] = 1;
  C.matrix[1][1] = 1;
  s21_sub_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_14) {
  // Умножение матрицы на число 1
  matrix_t A, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 5;
  C.matrix[0][1] = 5;
  C.matrix[1][0] = 5;
  C.matrix[1][1] = 5;
  s21_mult_number(&A, 5, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_15) {
  // Умножение матрицы на число 2
  matrix_t A, C, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 5.123;
  C.matrix[0][1] = 5.123;
  C.matrix[1][0] = 5.123;
  C.matrix[1][1] = 5.123;
  s21_mult_number(&A, 5.123, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_16) {
  // Умножение матриц 1
  matrix_t A, C, B, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = 7;
  B.matrix[0][1] = 8;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 1;
  B.matrix[2][0] = 2;
  B.matrix[2][1] = 3;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = 31;
  C.matrix[0][1] = 19;
  C.matrix[1][0] = 85;
  C.matrix[1][1] = 55;
  s21_mult_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_17) {
  // Умножение матриц 2
  matrix_t A, C, B, RESULT;
  s21_create_matrix(2, 2, &RESULT);
  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = -2;
  s21_create_matrix(3, 2, &B);
  B.matrix[0][0] = -7;
  B.matrix[0][1] = 5;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = -1;
  B.matrix[2][0] = 4;
  B.matrix[2][1] = 3;
  s21_create_matrix(2, 2, &C);
  C.matrix[0][0] = -16;
  C.matrix[0][1] = 16;
  C.matrix[1][0] = -35;
  C.matrix[1][1] = 15;
  s21_mult_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_18) {
  // Умножение матриц 3
  matrix_t A, C, B, RESULT;
  s21_create_matrix(4, 4, &RESULT);
  s21_create_matrix(4, 1, &A);
  A.matrix[0][0] = 3;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 0;
  A.matrix[3][0] = 1;
  s21_create_matrix(1, 4, &B);
  B.matrix[0][0] = -1;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 0;
  B.matrix[0][3] = 2;
  s21_create_matrix(4, 4, &C);
  C.matrix[0][0] = -3;
  C.matrix[0][1] = 3;
  C.matrix[0][2] = 0;
  C.matrix[0][3] = 6;
  C.matrix[1][0] = -2;
  C.matrix[1][1] = 2;
  C.matrix[1][2] = 0;
  C.matrix[1][3] = 4;
  C.matrix[2][0] = 0;
  C.matrix[2][1] = 0;
  C.matrix[2][2] = 0;
  C.matrix[2][3] = 0;
  C.matrix[3][0] = -1;
  C.matrix[3][1] = 1;
  C.matrix[3][2] = 0;
  C.matrix[3][3] = 2;
  s21_mult_matrix(&A, &B, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&C, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_19) {
  // Транспонировани матрицы 1
  matrix_t A, B, RESULT;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &RESULT);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 3;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 4;
  s21_transpose(&A, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&B, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_20) {
  // Транспонировани матрицы 2
  matrix_t A, B, RESULT;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &RESULT);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 4;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 8;
  B.matrix[2][0] = 3;
  B.matrix[2][1] = 6;
  B.matrix[2][2] = 9;
  s21_transpose(&A, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&B, &RESULT));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(test_21) {
  // Определитель матрицы 1
  matrix_t A;
  double result;
  s21_create_matrix(5, 5, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = -5;
  A.matrix[0][3] = 8;
  A.matrix[0][4] = 1;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = -6;
  A.matrix[1][4] = 1;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = -5;
  A.matrix[2][2] = -7;
  A.matrix[2][3] = 5;
  A.matrix[2][4] = 1;
  A.matrix[3][0] = -4;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = -6;
  A.matrix[3][4] = 2;
  A.matrix[4][0] = 1;
  A.matrix[4][1] = -1;
  A.matrix[4][2] = 1;
  A.matrix[4][3] = -1;
  A.matrix[4][4] = 1;
  s21_determinant(&A, &result);
  ck_assert_int_eq(178, result);
  s21_remove_matrix(&A);
}

START_TEST(test_22) {
  // Определитель матрицы 2
  matrix_t A;
  double result;
  s21_create_matrix(6, 6, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = -3;
  A.matrix[0][2] = -5;
  A.matrix[0][3] = 8;
  A.matrix[0][4] = 1;
  A.matrix[0][5] = 5;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = 0;
  A.matrix[1][4] = 1;
  A.matrix[1][5] = 4;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = -5;
  A.matrix[2][2] = -10;
  A.matrix[2][3] = 5;
  A.matrix[2][4] = 1;
  A.matrix[2][5] = -3;
  A.matrix[3][0] = 2;
  A.matrix[3][1] = 3;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = -6;
  A.matrix[3][4] = 2;
  A.matrix[3][5] = 10;
  A.matrix[4][0] = 2;
  A.matrix[4][1] = -10;
  A.matrix[4][2] = 6;
  A.matrix[4][3] = -5;
  A.matrix[4][4] = 1;
  A.matrix[4][5] = 2;
  A.matrix[5][0] = 1;
  A.matrix[5][1] = -1;
  A.matrix[5][2] = 0;
  A.matrix[5][3] = 4;
  A.matrix[5][4] = -1;
  A.matrix[5][5] = -2;
  s21_determinant(&A, &result);
  ck_assert_int_eq(-31693, result);
  s21_remove_matrix(&A);
}

START_TEST(test_23) {
  // Обратная матрица 1
  matrix_t A, B, RESULT;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &RESULT);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = -2;
  B.matrix[0][1] = 1;
  B.matrix[1][0] = 1.5;
  B.matrix[1][1] = -0.5;
  s21_inverse_matrix(&A, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&RESULT, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_24) {
  // Обратная матрица 2
  matrix_t A, B, RESULT;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &RESULT);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = -38;
  B.matrix[1][1] = 41;
  B.matrix[1][2] = -34;
  B.matrix[2][0] = 27;
  B.matrix[2][1] = -29;
  B.matrix[2][2] = 24;
  s21_inverse_matrix(&A, &RESULT);
  ck_assert_int_eq(1, s21_eq_matrix(&RESULT, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&RESULT);
}

START_TEST(test_25) {
  // Созадние матрицы 0 х 0
  int x = 1;
  matrix_t A;
  int ret = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(x, ret);
  s21_remove_matrix(&A);
}

START_TEST(test_26) {
  // Матрица NULL
  matrix_t A, B, RES;
  s21_create_matrix(2, 2, &A);
  A.matrix = NULL;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  int ret = s21_sum_matrix(&A, &B, &RES);
  ck_assert_int_eq(1, ret);
  ret = s21_sub_matrix(&A, &B, &RES);
  ck_assert_int_eq(1, ret);
  ret = s21_mult_number(&A, 5, &RES);
  ck_assert_int_eq(1, ret);
  ret = s21_mult_matrix(&A, &B, &RES);
  ck_assert_int_eq(1, ret);
  ret = s21_transpose(&A, &RES);
  ck_assert_int_eq(1, ret);
  ret = s21_calc_complements(&A, &RES);
  ck_assert_int_eq(1, ret);
  double x;
  ret = s21_determinant(&A, &x);
  ck_assert_int_eq(1, ret);
  ret = s21_inverse_matrix(&A, &RES);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

Suite *suite_matrix(void) {
  Suite *suite = suite_create("suite_matrix");
  TCase *tcase_core = tcase_create("core");

  tcase_add_test(tcase_core, test_0);
  tcase_add_test(tcase_core, test_1);
  tcase_add_test(tcase_core, test_2);
  tcase_add_test(tcase_core, test_3);
  tcase_add_test(tcase_core, test_4);
  tcase_add_test(tcase_core, test_5);
  tcase_add_test(tcase_core, test_6);
  tcase_add_test(tcase_core, test_7);
  tcase_add_test(tcase_core, test_8);
  tcase_add_test(tcase_core, test_9);
  tcase_add_test(tcase_core, test_10);
  tcase_add_test(tcase_core, test_11);
  tcase_add_test(tcase_core, test_12);
  tcase_add_test(tcase_core, test_13);
  tcase_add_test(tcase_core, test_14);
  tcase_add_test(tcase_core, test_15);
  tcase_add_test(tcase_core, test_16);
  tcase_add_test(tcase_core, test_17);
  tcase_add_test(tcase_core, test_18);
  tcase_add_test(tcase_core, test_19);
  tcase_add_test(tcase_core, test_20);
  tcase_add_test(tcase_core, test_21);
  tcase_add_test(tcase_core, test_22);
  tcase_add_test(tcase_core, test_23);
  tcase_add_test(tcase_core, test_24);
  tcase_add_test(tcase_core, test_25);
  tcase_add_test(tcase_core, test_26);

  suite_add_tcase(suite, tcase_core);
  return suite;
}