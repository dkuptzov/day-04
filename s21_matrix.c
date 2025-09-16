#include "s21_matrix.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
rows - строка
Операции над матрицами

Все операции (кроме сравнения матриц) должны возвращать результирующий код:

0 — OK;
1 — Ошибка, некорректная матрица;
2 — Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т. д.).
*/

// Создание матриц (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result)
{
    int ret = S21_MATRIX_OK;
    double **matrix = NULL;
    if ((rows <= 0 || columns <= 0) || !result)
    {
        ret = S21_MATRIX_WRONG;
        result->matrix = NULL;
    }
    else
    {
        matrix = (double **)calloc(rows, sizeof(double *));
        if (matrix != NULL)
        {
            for (int i = 0; i < rows && ret == S21_MATRIX_OK; i++)
            {
                matrix[i] = (double *)calloc(columns, sizeof(double));
                if (matrix[i] == NULL)
                {
                    for (int j = 0; j < i; j++)
                        free(matrix[j]);
                    free(matrix);
                    ret = S21_MATRIX_ERROR;
                }
            }
        }
        else
            ret = S21_MATRIX_WRONG;
    }
    if (ret == S21_MATRIX_OK)
    {
        result->matrix = matrix;
        result->rows = rows;
        result->columns = columns;
    }
    return ret;
}

// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A)
{
    // if (A == NULL)
    //     return;
    // if (A->matrix != NULL && A->rows > 0)
    // {
    //     for (int i = 0; i < A->rows; i++)
    //         free(A->matrix[i]);
    //     free(A->matrix);
    //     A->matrix = NULL;
    // }
    // A->rows = 0;
    // A->columns = 0;
    if (A != NULL && A->matrix != NULL)
    {
        for (int i = 0; i < A->rows; i++)
            free(A->matrix[i]);
        free(A->matrix);
    }
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
}

// Сравнение матриц (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B)
{
    /*
    Две матрицы A, B совпадают |A = B|, если совпадают их размеры и соответствующие элементы равны,
    то есть при всех i, j A(i,j) = B(i,j).
    Сравнение должно происходить вплоть до шестого знака после запятой включительно.
    */
    char str_A[128], str_B[128];
    int ret = SUCCESS, is_equal = 0;
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL || A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
        ret = FAILURE;
    if (A->columns != B->columns || A->rows != B->rows)
        ret = FAILURE;
    for (int i = 0; i < A->rows && ret == SUCCESS && is_equal == 0; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            sprintf(str_A, "%lf", A->matrix[i][j]);
            sprintf(str_B, "%lf", B->matrix[i][j]);
            if (strcmp(str_A, str_B))
                is_equal = 1;
            memset(str_A, 0, 128);
            memset(str_B, 0, 128);
        }
    }
    if (is_equal)
        ret = FAILURE;
    return ret;
}

// Сложение (sum_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    /*
    Суммой двух матриц A = m × n и B = m × n одинаковых размеров называется матрица C = m × n = A + B тех же размеров,
    элементы которой определяются равенствами C(i,j) = A(i,j) + B(i,j).
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL || result == NULL)
        ret = S21_MATRIX_WRONG;
    else if (A->columns != B->columns || A->rows != B->rows)
        ret = S21_MATRIX_ERROR;
    if (ret == S21_MATRIX_OK)
        ret = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            // if (DBL_MAX > fabs(A->matrix[i][j] + B->matrix[i][j]) && DBL_MIN < fabs(A->matrix[i][j] + B->matrix[i][j]))
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            // else
            //     ret = S21_MATRIX_ERROR;
        }
    }
    return ret;
}

// Вычитание матриц (sub_matrix)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    /*
    Разностью двух матриц A = m × n и B = m × n одинаковых размеров называется матрица C = m × n = A - B тех же размеров,
    элементы которой определяются равенствами C(i,j) = A(i,j) - B(i,j).
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL || result == NULL)
        ret = S21_MATRIX_WRONG;
    else if (A->columns != B->columns || A->rows != B->rows)
        ret = S21_MATRIX_ERROR;
    if (ret == S21_MATRIX_OK)
        ret = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
    return ret;
}

// Умножение матрицы на число (mult_number).
int s21_mult_number(matrix_t *A, double number, matrix_t *result)
{
    /*
    Произведением матрицы A = m × n на число λ называется матрица B = m × n = λ × A,
    элементы которой определяются равенствами B = λ × A(i,j).
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || A->matrix == NULL || result == NULL)
        ret = S21_MATRIX_WRONG;
    if (ret == S21_MATRIX_OK)
        ret = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] * number;
    }
    return ret;
}

// Умножение двух матриц (mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    /*
    Произведением матрицы A = m × k на матрицу B = k × n называется матрица C = m × n = A × B размера m × n,
    элементы которой определяются равенством C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + … + A(i,k) × B(k,j).
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL || result == NULL)
        ret = S21_MATRIX_WRONG;
    else if (A->columns != B->rows)
        ret = S21_MATRIX_ERROR;
    if (ret == S21_MATRIX_OK)
        ret = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < B->columns; j++)
        {
            for (int k = 0; k < A->columns; k++)
                result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
        }
    }
    return ret;
}

// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result)
{
    /*
    Транспонирование матрицы А заключается в замене строк этой матрицы ее столбцами с сохранением их номеров.
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || A->matrix == NULL || result == NULL)
        ret = S21_MATRIX_WRONG;
    if (ret == S21_MATRIX_OK)
        ret = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns; j++)
            result->matrix[j][i] = A->matrix[i][j];
    }
    return ret;
}

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result)
{
    /*
    Минором M(i,j) называется определитель (n-1)-го порядка, полученный вычёркиванием из матрицы A i-й строки и j-го столбца.
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
        ret = S21_MATRIX_WRONG;
    if (A->rows != A->columns)
        ret = S21_MATRIX_ERROR;
    if (ret == S21_MATRIX_OK)
        ret = s21_create_matrix(A->rows, A->columns, result);
    if (ret == S21_MATRIX_OK)
    {
        if (A->rows == 1)
            result->matrix[0][0] = 1;
        else if (A->rows == 2)
        {
            result->matrix[0][0] = A->matrix[1][1];
            result->matrix[0][1] = (A->matrix[1][0] * -1);
            result->matrix[1][0] = (A->matrix[0][1] * -1);
            result->matrix[1][1] = A->matrix[0][0];
        }
        else
        {
            for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
            {
                for (int j = 0; j < A->columns && ret == S21_MATRIX_OK; j++)
                {
                    matrix_t A_det;
                    ret = s21_create_matrix(A->rows - 1, A->columns - 1, &A_det);
                    if (ret == S21_MATRIX_OK)
                    {
                        s21_matrix_for_det(i, j, A, &A_det);
                        double x = s21_determ_rec(&A_det);
                        if ((i + j) % 2 != 0) // матрица алгебраических дополнений
                            x *= -1;
                        result->matrix[i][j] = x;
                        // s21_free_mem_matrix(&A_det);
                        s21_remove_matrix(&A_det);
                    }
                }
            }
        }
    }
    // s21_remove_matrix(result);
    return ret;
}

// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result)
{
    /*
    Определитель (детерминант) — это число, которое ставят в соответствие каждой квадратной матрице
    и вычисляют из элементов по специальным формулам.
    Tip: определитель может быть вычислен только для квадратной матрицы.
    Определитель матрицы равен сумме произведений элементов строки (столбца) на соответствующие алгебраические дополнения.
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
        ret = S21_MATRIX_WRONG;
    if (A->rows != A->columns)
        ret = S21_MATRIX_ERROR;
    if (ret == S21_MATRIX_OK)
        *result = s21_determ_rec(A);
    return ret;
}

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result)
{
    /*
    Матрицу A в степени -1 называют обратной к квадратной матрице А,
    если произведение этих матриц равняется единичной матрице.
    Обратной матрицы не существует, если определитель равен 0.
    */
    double res;
    int ret = S21_MATRIX_OK;
    if (A == NULL || A->matrix == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
        ret = S21_MATRIX_WRONG;
    if (A->rows != A->columns)
        ret = S21_MATRIX_ERROR;
    if (ret == S21_MATRIX_OK)
        ret = s21_create_matrix(A->rows, A->columns, result);
    if (ret == S21_MATRIX_OK && A->rows == 1)
        result->matrix[0][0] = 1 / A->matrix[0][0];
    else if (ret == S21_MATRIX_OK)
    {
        // matrix_t A_minor, A_transponse;
        // s21_create_matrix(A->rows, A->columns, &A_minor);
        // s21_create_matrix(A->rows, A->columns, &A_transponse);
        // double res;
        s21_determinant(A, &res);
        // printf("res: %2.0lf\n", res);
        if (res == 0)
            ret = S21_MATRIX_ERROR;
        // }
        // if (ret == S21_MATRIX_OK)
        // {
        else
        {
            matrix_t A_minor, A_transponse;
            // s21_create_matrix(A->rows, A->columns, &A_minor);
            s21_calc_complements(A, &A_minor);
            s21_transpose(&A_minor, &A_transponse);
            for (int i = 0; i < result->rows; i++)
            {
                for (int j = 0; j < result->columns; j++)
                {
                    result->matrix[i][j] = A_transponse.matrix[i][j] * (1 / res);
                }
            }
            s21_remove_matrix(&A_minor);
            s21_remove_matrix(&A_transponse);
        }
        // s21_free_mem_matrix(&A_minor);
        // s21_free_mem_matrix(&A_transponse);
        // s21_remove_matrix(&A_minor);
        // s21_remove_matrix(&A_transponse);
    }
    // *result = A_transponse;
    // s21_free_mem_matrix(&A_minor);
    // s21_free_mem_matrix(&A_transponse);
    return ret;
}