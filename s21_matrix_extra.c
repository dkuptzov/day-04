#include "s21_matrix.h"

#include <stdio.h>
#include <stdlib.h>

void s21_zero_matrix(int rows, int columns, matrix_t *A)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            A->matrix[i][j] = 0;
    }
}

void s21_matrix_for_det(int not_use_i, int not_use_j, matrix_t *A, matrix_t *A_det)
{
    int x = 0, y = 0;
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            if (not_use_i != i && not_use_j != j)
            {
                A_det->matrix[x][y] = A->matrix[i][j];
                if (y < A_det->columns - 1)
                    y++;
                else if (x < A_det->rows && y == A_det->columns - 1)
                {
                    y = 0;
                    x++;
                }
            }
        }
    }
}

void s21_free_mem_matrix(matrix_t *matrix)
{
    if (matrix->matrix != NULL)
    {
        for (int i = 0; i < matrix->rows; i++)
        {
            free(matrix->matrix[i]);
        }
        free(matrix->matrix);
    }
}

void s21_minor(matrix_t *A, double *result)
{
    int step = A->columns, x = 0, y = 0;
    double part_det_1 = 0.0, part_det_2 = 0.0, temp_det = 1.0;
    if (A->rows == 1)
        *result = 1;
    else if (A->rows == 2)
        *result = (A->matrix[0][0] * A->matrix[1][1]) - (A->matrix[0][1] * A->matrix[1][0]);
    else
    {
        for (int j = 0; j < A->columns; j++)
        {
            x = 0;
            y = j;
            while (step > 0)
            {
                // printf("STEP: %d %lf\n", step, A->matrix[x][y]);
                temp_det *= A->matrix[x][y];
                x++;
                if (y == A->rows - 1)
                    y = 0;
                else
                    y++;
                step--;
            }
            step = A->columns;
            part_det_1 += temp_det;
            temp_det = 1.0;
            // printf("part 1: %lf\n", part_det_1);
            // int a;
            // scanf("%d", &a);
        }
        step = A->columns;
        x = 0;
        y = A->columns - 1;
        temp_det = 1.0;
        for (int j = A->columns - 1; j >= 0; j--)
        {
            x = 0;
            y = j;
            while (step > 0)
            {
                // printf("STEP: %d %lf\n", step, A->matrix[x][y]);
                temp_det *= A->matrix[x][y];
                x++;
                if (y == 0)
                    y = A->columns - 1;
                else
                    y--;
                step--;
            }
            step = A->columns;
            part_det_2 += temp_det;
            temp_det = 1.0;
            // printf("part 2: %lf\n", part_det_2);
            // int a;
            // scanf("%d", &a);
        }
        *result = part_det_1 - part_det_2;
    }
}