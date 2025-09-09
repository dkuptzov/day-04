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
    if ((rows < 0 || columns < 0) || !result)
        ret = S21_MATRIX_WRONG;
    else
    {
        matrix = (double **)calloc(rows, sizeof(double *));
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
    if (A != NULL && A->matrix != NULL)
    {
        for (int i = 0; i < A->rows; i++)
        {
            free(A->matrix[i]);
        }
        free(A->matrix);
        A->matrix = NULL;
        A->rows = 0;
        A->columns = 0;
    }
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
    int ret = S21_MATRIX_OK, is_equal = 0;
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
        ret = S21_MATRIX_WRONG;
    else if (A->columns != B->columns || A->rows != B->rows)
        ret = S21_MATRIX_ERROR;
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK && is_equal == 0; i++)
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
    if (is_equal && ret == S21_MATRIX_OK)
        ret = FAILURE;
    else if (ret == S21_MATRIX_OK)
        ret = SUCCESS;
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
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
        ret = S21_MATRIX_WRONG;
    else if (A->columns != B->columns || A->rows != B->rows)
        ret = S21_MATRIX_ERROR;
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns && ret == S21_MATRIX_OK; j++)
        {
            if (DBL_MAX > fabs(A->matrix[i][j] + B->matrix[i][j]) && DBL_MIN < fabs(A->matrix[i][j] + B->matrix[i][j]))
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            else
                ret = S21_MATRIX_ERROR;
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
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
        ret = S21_MATRIX_WRONG;
    else if (A->columns != B->columns || A->rows != B->rows)
        ret = S21_MATRIX_ERROR;
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns && ret == S21_MATRIX_OK; j++)
        {
            if (DBL_MAX > fabs(A->matrix[i][j] - B->matrix[i][j]) && DBL_MIN < fabs(A->matrix[i][j] - B->matrix[i][j]))
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            else
                ret = S21_MATRIX_ERROR;
        }
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
    if (A == NULL || A->matrix == NULL)
        ret = S21_MATRIX_WRONG;
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns && ret == S21_MATRIX_OK; j++)
        {
            if (DBL_MAX > fabs(A->matrix[i][j] * number) && DBL_MIN < fabs(A->matrix[i][j] * number))
                result->matrix[i][j] = A->matrix[i][j] * number;
            else
                ret = S21_MATRIX_ERROR;
        }
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
    if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
        ret = S21_MATRIX_WRONG;
    else if (A->columns != B->rows || A->rows != B->columns)
        ret = S21_MATRIX_ERROR;
    if (ret == S21_MATRIX_OK)
        s21_zero_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < B->columns && ret == S21_MATRIX_OK; j++)
        {
            for (int k = 0; k < A->columns; k++)
            {
                result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
                // printf("i: %d, j: %d, k: %d\n", i, j, k);
                // printf("%lf %lf %lf\n", A->matrix[i][k], B->matrix[k][j], result->matrix[i][j]);
                // int a;
                // scanf("%d", &a);
            }
        }
    }
    // for (int i = 0; i < 4 && ret == S21_MATRIX_OK; i++)
    //     for (int j = 0; j < 4 && ret == S21_MATRIX_OK; j++)
    //         printf("%lf ", result->matrix[i][j]);
    return ret;
}

// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result)
{
    /*
    Транспонирование матрицы А заключается в замене строк этой матрицы ее столбцами с сохранением их номеров.
    */
    int ret = S21_MATRIX_OK;
    if (A == NULL || A->matrix == NULL || A->rows != result->columns || A->columns != result->rows)
        ret = S21_MATRIX_WRONG;
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns && ret == S21_MATRIX_OK; j++)
        {
            result->matrix[j][i] = A->matrix[i][j];
        }
    }
    return ret;
}

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result)
{
    /*
    Минором M(i,j) называется определитель (n-1)-го порядка, полученный вычёркиванием из матрицы A i-й строки и j-го столбца.
    */
    result = 0;
    double det = 0;
    int ret = S21_MATRIX_OK;
    if (A == NULL || A->matrix == NULL)
        ret = S21_MATRIX_WRONG;
    for (int i = 0; i < A->rows && ret == S21_MATRIX_OK; i++)
    {
        for (int j = 0; j < A->columns && ret == S21_MATRIX_OK; j++)
        {
            matrix_t A_det;
            s21_create_matrix(A->rows - 1, A->columns - 1, &A_det);
            s21_matrix_for_det(i, j, A, &A_det);
            // for (int i = 0; i < A_det.rows; i++)
            // {
            //     for (int j = 0; j < A_det.columns; j++)
            //         printf("%lf", A_det.matrix[i][j]);
            //     printf("\n");
            // }
            s21_minor(&A_det, &det);
            printf("%lf\n", det);
            int a;
            scanf("%d", &a);
            s21_free_mem_matrix(&A_det);
        }
    }
    // удалить потом
    result->columns++;
    // удалить потом
    return 0;
}

// Определитель матрицы (determinant)
// int s21_determinant(matrix_t *A, double *result)
// {
//     /*
//     Определитель (детерминант) — это число, которое ставят в соответствие каждой квадратной матрице
//     и вычисляют из элементов по специальным формулам.
//     Tip: определитель может быть вычислен только для квадратной матрицы.
//     Определитель матрицы равен сумме произведений элементов строки (столбца) на соответствующие алгебраические дополнения.
//     */
// }

// // Обратная матрица (inverse_matrix)
// int s21_inverse_matrix(matrix_t *A, matrix_t *result)
// {
//     /*
//     Матрицу A в степени -1 называют обратной к квадратной матрице А,
//     если произведение этих матриц равняется единичной матрице.
//     Обратной матрицы не существует, если определитель равен 0.
//     */
// }