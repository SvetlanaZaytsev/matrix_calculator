#include "matrix.h"

#include <cstdio>
#include <stdexcept>

int main() {
    try {
        // 1. Демонстрация create_matrix / matrix_from_array
        double arr_a[] = {1, 2, 3, 4};
        double arr_b[] = {5, 6, 7, 8};

        Matrix A = matrix_from_array(arr_a, 2, 2);
        Matrix B = matrix_from_array(arr_b, 2, 2);

        // 2. Сложение и умножение
        Matrix sum = matrix_add(A, B);
        Matrix product = matrix_multiply(A, B);

        printf("Matrix A:\n");
        print_matrix(A);
        printf("Matrix B:\n");
        print_matrix(B);
        printf("Sum A+B:\n");
        print_matrix(sum);
        printf("Product A*B:\n");
        print_matrix(product);

        // 3. Демонстрация print_matrix на большой матрице 15x12
        // (сработает сокращённый вывод: first 10x8 + сводка)
        Matrix big = create_matrix(15, 12);
        for (int i = 0; i < big.rows; ++i) {
            for (int j = 0; j < big.cols; ++j) {
                big.data[i][j] = (i + 1) * 10 + (j + 1) + 0.5;
            }
        }
        printf("\nBig matrix 15x12:\n");
        print_matrix(big);
        free_matrix(big);

        // 4. Демонстрация защиты от некорректной матрицы
        Matrix empty;
        empty.data = nullptr;
        empty.rows = 0;
        empty.cols = 0;
        printf("\nEmpty matrix test:\n");
        print_matrix(empty);

        // 5. Освобождение памяти
        free_matrix(A);
        free_matrix(B);
        free_matrix(sum);
        free_matrix(product);
    } catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }
    return 0;
}
