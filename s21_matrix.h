#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct
{
    double **matrix;
    int rows;
    int columns;
} matrix_t;

typedef enum s21_result
{
    S21_MATRIX_OK = 0,
    S21_MATRIX_WRONG = 1,
    S21_MATRIX_ERROR = 2,
} result;

typedef enum s21_row_or_col
{
    S21_ROW = 0,
    S21_COL = 1,
} row_or_col;

// Создание матриц (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result);
// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A);
// Сравнение матриц (eq_matrix)
// #define SUCCESS 1
// #define FAILURE 0
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// Сложение (sum_matrix) и вычитание матриц (sub_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Умножение матрицы на число (mult_number). Умножение двух матриц (mult_matrix)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result);
// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);
// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result);
// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
// Доп
void s21_zero_matrix(int rows, int columns, matrix_t *A);
void s21_matrix_for_det(int not_use_i, int not_use_j, matrix_t *A, matrix_t *A_det);
void s21_free_mem_matrix(matrix_t *matrix);
void s21_minor(matrix_t *A, double *result);
void s21_del_row(matrix_t *A, matrix_t *RESULT, int x);
void s21_del_col(matrix_t *A, matrix_t *RESULT, int x);
double s21_determ_rec(matrix_t *A);
void s21_copy_matrix(matrix_t *A, matrix_t *B);

#endif // S21_MATRIX_H