#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

void free_mem_matrix(matrix_t *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
}

int main()
{
    // matrix_t A, B;
    // s21_create_matrix(2, 2, &A);
    // A.matrix[0][0] = 0.987654321;
    // A.matrix[0][1] = 2;
    // A.matrix[1][0] = 3;
    // A.matrix[1][1] = 4;
    // s21_create_matrix(2, 2, &B);
    // B.matrix[0][0] = 0.987654321;
    // B.matrix[0][1] = 2;
    // B.matrix[1][0] = 3;
    // B.matrix[1][1] = 4;
    // int ret1 = s21_eq_matrix(&A, &B);
    // printf("ret1: %d\n", ret1);
    // matrix_t A, B, C, RESULT;
    // s21_create_matrix(2, 2, &RESULT);
    // s21_create_matrix(2, 3, &A);
    // A.matrix[0][0] = 1;
    // A.matrix[0][1] = 2;
    // A.matrix[0][2] = 3;
    // A.matrix[1][0] = 4;
    // A.matrix[1][1] = 5;
    // A.matrix[1][2] = 6;
    // s21_create_matrix(3, 2, &B);
    // B.matrix[0][0] = 7;
    // B.matrix[0][1] = 8;
    // B.matrix[1][0] = 9;
    // B.matrix[1][1] = 1;
    // B.matrix[2][0] = 2;
    // B.matrix[2][1] = 3;
    // s21_create_matrix(2, 2, &C);
    // C.matrix[0][0] = 5;
    // C.matrix[0][1] = 5;
    // C.matrix[1][0] = 5;
    // C.matrix[1][1] = 5;
    // s21_mult_matrix(&A, &B, &RESULT);
    // free_mem_matrix(&A);
    // free_mem_matrix(&B);
    // free_mem_matrix(&C);
    // free_mem_matrix(&RESULT);
    // matrix_t A, C, B, RESULT;
    // s21_create_matrix(4, 4, &RESULT);
    // s21_create_matrix(4, 1, &A);
    // A.matrix[0][0] = 3;
    // A.matrix[1][0] = 2;
    // A.matrix[2][0] = 0;
    // A.matrix[3][0] = 1;
    // s21_create_matrix(1, 4, &B);
    // B.matrix[0][0] = -1;
    // B.matrix[0][1] = 1;
    // B.matrix[0][2] = 0;
    // B.matrix[0][3] = 2;
    // s21_create_matrix(4, 4, &C);
    // C.matrix[0][0] = -3;
    // C.matrix[0][1] = 3;
    // C.matrix[0][2] = 0;
    // C.matrix[0][3] = 6;
    // C.matrix[1][0] = -2;
    // C.matrix[1][1] = 2;
    // C.matrix[1][2] = 0;
    // C.matrix[1][3] = 4;
    // C.matrix[2][0] = 0;
    // C.matrix[2][1] = 0;
    // C.matrix[2][2] = 0;
    // C.matrix[2][3] = 0;
    // C.matrix[3][0] = -1;
    // C.matrix[3][1] = 1;
    // C.matrix[3][2] = 0;
    // C.matrix[3][3] = 2;
    // s21_mult_matrix(&A, &B, &RESULT);
    // free_mem_matrix(&A);
    // free_mem_matrix(&B);
    // free_mem_matrix(&C);
    // free_mem_matrix(&RESULT);

    matrix_t A, RESULT;
    s21_create_matrix(4, 4, &A);
    s21_create_matrix(4, 4, &RESULT);
    A.matrix[0][0] = 1;
    A.matrix[0][1] = 2;
    A.matrix[0][2] = 3;
    A.matrix[0][3] = 4;
    A.matrix[1][0] = 5;
    A.matrix[1][1] = 6;
    A.matrix[1][2] = 7;
    A.matrix[1][3] = 8;
    A.matrix[2][0] = 9;
    A.matrix[2][1] = 10;
    A.matrix[2][2] = 11;
    A.matrix[2][3] = 12;
    A.matrix[3][0] = 13;
    A.matrix[3][1] = 14;
    A.matrix[3][2] = 15;
    A.matrix[3][3] = 16;
    s21_calc_complements(&A, &RESULT);
    free_mem_matrix(&A);
    free_mem_matrix(&RESULT);
    return 0;
}