#include "s21_matrix.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = S21_MATRIX_OK;
  double **matrix = NULL;
  if ((rows <= 0 || columns <= 0) || !result) {
    ret = S21_MATRIX_WRONG;
    result->matrix = NULL;
  } else {
    matrix = (double **)calloc(rows, sizeof(double *));
    if (matrix == NULL) ret = S21_MATRIX_WRONG;
    for (int i = 0; i < rows && ret == S21_MATRIX_OK; i++) {
      matrix[i] = (double *)calloc(columns, sizeof(double));
      if (matrix[i] == NULL) {
        for (int j = 0; j < i; j++) free(matrix[j]);
        free(matrix);
        ret = S21_MATRIX_ERROR;
      }
    }
  }
  if (ret == S21_MATRIX_OK) {
    result->matrix = matrix;
    result->rows = rows;
    result->columns = columns;
  }
  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  char str_A[128], str_B[128];
  int ret = SUCCESS, is_equal = 0;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    ret = FAILURE;
  else if (A->columns != B->columns || A->rows != B->rows)
    ret = FAILURE;
  for (int i = 0; i < A->rows && ret == SUCCESS && is_equal == 0; i++) {
    for (int j = 0; j < A->columns; j++) {
      sprintf(str_A, "%lf", A->matrix[i][j]);
      sprintf(str_B, "%lf", B->matrix[i][j]);
      if (strcmp(str_A, str_B)) is_equal = 1;
      memset(str_A, 0, 128);
      memset(str_B, 0, 128);
    }
  }
  if (is_equal) ret = FAILURE;
  return ret;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = S21_MATRIX_OK;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      result == NULL)
    ret = S21_MATRIX_WRONG;
  else if (A->columns != B->columns || A->rows != B->rows)
    ret = S21_MATRIX_ERROR;
  else
    ret = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++) {
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }
  return ret;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = S21_MATRIX_OK;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      result == NULL)
    ret = S21_MATRIX_WRONG;
  else if (A->columns != B->columns || A->rows != B->rows)
    ret = S21_MATRIX_ERROR;
  else
    ret = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++) {
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }
  return ret;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = S21_MATRIX_OK;
  if (A == NULL || A->matrix == NULL || result == NULL)
    ret = S21_MATRIX_WRONG;
  else
    ret = s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++) {
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;
  }
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = S21_MATRIX_OK;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      result == NULL)
    ret = S21_MATRIX_WRONG;
  else if (A->columns != B->rows)
    ret = S21_MATRIX_ERROR;
  else
    ret = s21_create_matrix(A->rows, B->columns, result);
  for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    for (int j = 0; j < B->columns; j++)
      for (int k = 0; k < A->columns; k++)
        result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
  return ret;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = S21_MATRIX_OK;
  if (A == NULL || A->matrix == NULL || result == NULL)
    ret = S21_MATRIX_WRONG;
  else
    ret = s21_create_matrix(A->columns, A->rows, result);
  for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    for (int j = 0; j < A->columns; j++) result->matrix[j][i] = A->matrix[i][j];
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = S21_MATRIX_OK;
  if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0)
    ret = S21_MATRIX_WRONG;
  else if (A->rows != A->columns)
    ret = S21_MATRIX_ERROR;
  else
    ret = s21_create_matrix(A->rows, A->columns, result);
  if (ret == S21_MATRIX_OK) {
    if (A->rows == 1)
      result->matrix[0][0] = 1;
    else if (A->rows == 2) {
      result->matrix[0][0] = A->matrix[1][1];
      result->matrix[0][1] = (A->matrix[1][0] * -1);
      result->matrix[1][0] = (A->matrix[0][1] * -1);
      result->matrix[1][1] = A->matrix[0][0];
    }
  }
  for (int i = 0; i < A->rows && ret == S21_MATRIX_OK && A->rows > 2; i++) {
    for (int j = 0; j < A->columns && ret == S21_MATRIX_OK; j++) {
      matrix_t A_det;
      ret = s21_create_matrix(A->rows - 1, A->columns - 1, &A_det);
      if (ret == S21_MATRIX_OK) {
        s21_matrix_for_det(i, j, A, &A_det);
        double x = s21_determ_rec(&A_det);
        if ((i + j) % 2 != 0) x *= -1;
        result->matrix[i][j] = x;
        s21_remove_matrix(&A_det);
      }
    }
  }
  return ret;
}

int s21_determinant(matrix_t *A, double *result) {
  int ret = S21_MATRIX_OK;
  if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0)
    ret = S21_MATRIX_WRONG;
  else if (A->rows != A->columns)
    ret = S21_MATRIX_ERROR;
  else
    *result = s21_determ_rec(A);
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  double res;
  int ret = S21_MATRIX_OK;
  if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0)
    ret = S21_MATRIX_WRONG;
  else if (A->rows != A->columns)
    ret = S21_MATRIX_ERROR;
  else
    ret = s21_create_matrix(A->rows, A->columns, result);
  if (ret == S21_MATRIX_OK && A->rows == 1)
    result->matrix[0][0] = 1 / A->matrix[0][0];
  else if (ret == S21_MATRIX_OK) {
    s21_determinant(A, &res);
    if (res == 0)
      ret = S21_MATRIX_ERROR;
    else {
      matrix_t A_minor, A_transponse;
      s21_calc_complements(A, &A_minor);
      s21_transpose(&A_minor, &A_transponse);
      for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
          result->matrix[i][j] = A_transponse.matrix[i][j] * (1 / res);
      s21_remove_matrix(&A_minor);
      s21_remove_matrix(&A_transponse);
    }
  }
  return ret;
}