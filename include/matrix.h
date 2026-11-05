/**
 * @file matrix.h
 * @brief Библиотека "Калькулятор матриц".
 * @version 1.0
 */
#ifndef MATRIX_H
#define MATRIX_H

/**
 * @brief Структура матрицы.
 * @warning Память освобождается через free_matrix().
 */
typedef struct {
    double** data; /**< Указатель на массив указателей на строки. */
    int rows;      /**< Количество строк. */
    int cols;      /**< Количество столбцов. */
} Matrix;

/**
 * @brief Создание матрицы заданного размера, заполненной нулями.
 * @param rows Количество строк (> 0).
 * @param cols Количество столбцов (> 0).
 * @return Matrix Инициализированная нулями матрица.
 * @exception std::invalid_argument Если rows <= 0 или cols <= 0.
 * @exception std::bad_alloc Если не удалось выделить память.
 * @see free_matrix()
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождение памяти, занятой матрицей.
 * @param m Матрица для освобождения.
 * @note Безопасно вызывать для матрицы с data == nullptr.
 */
void free_matrix(Matrix m);

/**
 * @brief Сложение двух матриц: C = A + B, c_ij = a_ij + b_ij.
 * @param a Первая матрица.
 * @param b Вторая матрица.
 * @return Новая матрица — результат сложения.
 * @exception std::invalid_argument Если размеры не совпадают или матрицы невалидны.
 * @warning Результат нужно освободить через free_matrix().
 */
Matrix matrix_add(Matrix a, Matrix b);

/**
 * @brief Умножение матриц: C = A * B, c_ij = sum_k a_ik * b_kj.
 * @param a Матрица M×N.
 * @param b Матрица N×K.
 * @return Новая матрица M×K.
 * @exception std::invalid_argument Если cols(a) != rows(b) или матрицы невалидны.
 * @note Сложность: O(M * N * K).
 * @warning Результат нужно освободить через free_matrix().
 */
Matrix matrix_multiply(Matrix a, Matrix b);

/**
 * @brief Вывод матрицы в консоль с выравниванием и обрамлением.
 * @param m Матрица для вывода.
 * @note Матрицы крупнее 10×8 выводятся в сокращённом виде.
 */
void print_matrix(Matrix m);

/**
 * @brief Создание матрицы из одномерного массива (заполнение по строкам).
 * @param data Указатель на массив из rows*cols элементов.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Новая матрица с копией данных.
 * @exception std::invalid_argument Если data == nullptr или размеры некорректны.
 */
Matrix matrix_from_array(double* data, int rows, int cols);

#endif // MATRIX_H
