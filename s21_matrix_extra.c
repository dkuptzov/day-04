#include <stdio.h>
#include <stdlib.h>

#include "s21_matrix.h"

void s21_matrix_for_det(int not_use_i, int not_use_j, matrix_t *A,
                        matrix_t *A_det) {
  int x = 0, y = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (not_use_i != i && not_use_j != j) {
        A_det->matrix[x][y] = A->matrix[i][j];
        if (y < A_det->columns - 1)
          y++;
        else if (x < A_det->rows && y == A_det->columns - 1) {
          y = 0;
          x++;
        }
      }
    }
  }
}

void s21_minor(matrix_t *A, double *result) {
  int step = A->columns, x = 0, y = 0;
  double part_det_1 = 0.0, part_det_2 = 0.0, temp_det = 1.0;
  if (A->rows == 1)
    *result = 1;
  else if (A->rows == 2)
    *result = (A->matrix[0][0] * A->matrix[1][1]) -
              (A->matrix[0][1] * A->matrix[1][0]);
  else {
    for (int j = 0; j < A->columns; j++) {
      x = 0;
      y = j;
      while (step > 0) {
        temp_det *= A->matrix[x][y];
        x++;
        y = (y == A->rows - 1) ? 0 : y + 1;
        step--;
      }
      step = A->columns;
      part_det_1 += temp_det;
      temp_det = 1.0;
    }
    step = A->columns;
    x = 0;
    y = A->columns - 1;
    temp_det = 1.0;
    for (int j = A->columns - 1; j >= 0; j--) {
      x = 0;
      y = j;
      while (step > 0) {
        temp_det *= A->matrix[x][y];
        x++;
        y = (y == 0) ? A->columns - 1 : y - 1;
        step--;
      }
      step = A->columns;
      part_det_2 += temp_det;
      temp_det = 1.0;
    }
    *result = part_det_1 - part_det_2;
  }
}

void s21_zero_in_str(matrix_t *A, int *row_or_col, int *zero) {
  int counter_zero_row = 0, counter_zero_col = 0, zero_row = 0, zero_col = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (A->matrix[i][j] == 0) counter_zero_row++;
      if (A->matrix[j][i] == 0) counter_zero_col++;
    }
    if (counter_zero_row > zero_row && counter_zero_row > zero_col) {
      zero_row = counter_zero_row;
      *row_or_col = S21_ROW;
      *zero = i;
    }
    if (counter_zero_col > zero_col && counter_zero_col > zero_row) {
      zero_col = counter_zero_col;
      *row_or_col = S21_COL;
      *zero = i;
    }
    counter_zero_row = 0;
    counter_zero_col = 0;
  }
}

void s21_del_row(matrix_t *A, matrix_t *RESULT, int row) {
  for (int i = 0; i < A->rows; i++) {
    if (i != row) {
      for (int j = 0; j < A->columns; j++) {
        if (i > row)
          RESULT->matrix[i - 1][j] = A->matrix[i][j];
        else
          RESULT->matrix[i][j] = A->matrix[i][j];
      }
    }
  }
}

void s21_del_col(matrix_t *A, matrix_t *RESULT, int col) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (j != col) {
        if (j > col)
          RESULT->matrix[i][j - 1] = A->matrix[i][j];
        else
          RESULT->matrix[i][j] = A->matrix[i][j];
      }
    }
  }
}

double s21_determ_rec(matrix_t *A) {
  double minor = 0;
  int row_or_col = S21_ROW, str_zero = 0, its_row_col = -1;
  if (A->rows == 1)
    minor = 1;
  else if (A->rows == 2)
    minor = (A->matrix[0][0] * A->matrix[1][1]) -
            (A->matrix[0][1] * A->matrix[1][0]);
  else if (A->columns == 3)
    s21_minor(A, &minor);
  else if (A->columns > 3) {
    s21_zero_in_str(A, &row_or_col, &str_zero);
    its_row_col = (row_or_col == S21_ROW) ? A->columns : A->rows;
    for (int j = 0; j < its_row_col; j++) {
      if ((A->matrix[str_zero][j] != 0 && row_or_col == S21_ROW) ||
          (row_or_col == S21_COL && A->matrix[j][str_zero] != 0)) {
        matrix_t A_new, A_new_2;
        s21_create_matrix(A->rows, A->columns, &A_new);
        s21_create_matrix(A->rows, A->columns, &A_new_2);
        if (row_or_col == S21_ROW)
          s21_del_row(A, &A_new, str_zero);
        else
          s21_del_row(A, &A_new, j);
        A_new.rows--;
        s21_copy_matrix(&A_new_2, &A_new);
        A_new.columns--;
        if (row_or_col == S21_ROW)
          s21_del_col(&A_new_2, &A_new, j);
        else
          s21_del_col(&A_new_2, &A_new, str_zero);
        if ((str_zero + j) % 2 == 0 && row_or_col == S21_ROW)
          minor += (A->matrix[str_zero][j] * s21_determ_rec(&A_new));
        else if (row_or_col == S21_ROW)
          minor -= (A->matrix[str_zero][j] * s21_determ_rec(&A_new));
        else if ((str_zero + j) % 2 == 0 && row_or_col == S21_COL)
          minor += (A->matrix[j][str_zero] * s21_determ_rec(&A_new));
        else if (row_or_col == S21_COL)
          minor -= (A->matrix[j][str_zero] * s21_determ_rec(&A_new));
        A_new.rows++;
        A_new.columns++;
        s21_remove_matrix(&A_new);
        s21_remove_matrix(&A_new_2);
      }
    }
  }
  return minor;
}

void s21_copy_matrix(matrix_t *A, matrix_t *B) {
  for (int i = 0; i < B->rows; i++)
    for (int j = 0; j < B->columns; j++) A->matrix[i][j] = B->matrix[i][j];
}