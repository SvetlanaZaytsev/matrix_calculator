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

        // 5. Индивидуальное задание (вариант 8): matrix_fill
        matrix_fill(A, 7.25);
        printf("\nMatrix A after fill(7.25):\n");
        print_matrix(A);
        Matrix sum2 = matrix_add(A, B);
        printf("Sum A+B after fill:\n");
        print_matrix(sum2);
        free_matrix(sum2);

        // 7. Демонстрация create_matrix: нулевая матрица 3x3
        Matrix zeros = create_matrix(3, 3);
        printf("\nZero matrix 3x3 (create_matrix):\n");
        print_matrix(zeros);
        free_matrix(zeros);

        // 8. Демонстрация обработки ошибки в create_matrix
        try {
            Matrix bad = create_matrix(0, -5);
            free_matrix(bad);
        } catch (const std::exception& e) {
            printf("\nCaught expected error: %s\n", e.what());
        }

        // 8b. Ошибка matrix_add: матрица создаётся ДО try, освобождается ПОСЛЕ catch
        Matrix wrong = create_matrix(2, 3);
        try {
            Matrix result = matrix_add(A, wrong);  // 2x2 + 2x3 -> ошибка
            free_matrix(result);
        } catch (const std::exception& e) {
            printf("\nCaught dimension mismatch error in matrix_add: %s\n", e.what());
        }
        free_matrix(wrong);

        // 8c. Ошибка matrix_multiply: та же схема
        Matrix tall = create_matrix(3, 2);
        try {
            Matrix result = matrix_multiply(A, tall);  // 2x2 * 3x2 -> ошибка
            free_matrix(result);
        } catch (const std::exception& e) {
            printf("\nCaught dimension mismatch error in matrix_multiply: %s\n", e.what());
        }
        free_matrix(tall);

        // 9. Демонстрация free_matrix: освобождение и защита от double free
        Matrix temp = create_matrix(2, 3);
        printf("\nMatrix temp before free:\n");
        print_matrix(temp);
        free_matrix(temp);
        temp.data = nullptr;
        temp.rows = 0;
        temp.cols = 0;
        free_matrix(temp);
        printf("Matrix temp freed, double-free protection: OK\n");

        // Освобождение памяти
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
