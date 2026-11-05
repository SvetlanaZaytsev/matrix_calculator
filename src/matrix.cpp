#include "matrix.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace {
bool is_valid(Matrix m) {
    return m.data != nullptr && m.rows > 0 && m.cols > 0;
}
}  // namespace

Matrix create_matrix(int rows, int cols) {
    // 1. Проверка корректности размеров
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    // 2. Выделение памяти для массива указателей
    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }

    // 3. Выделение памяти для каждой строки
    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        if (mat.data[i] == nullptr) {
            // Освобождение уже выделенной памяти при ошибке
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }

        // 4. Инициализация нулями
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }

    // 5. Возврат созданной матрицы
    return mat;
}

void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }
    for (int i = 0; i < m.rows; ++i) {
        delete[] m.data[i];
    }
    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (!is_valid(a) || !is_valid(b)) {
        throw std::invalid_argument("Invalid matrix");
    }
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match");
    }

    Matrix result = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (!is_valid(a) || !is_valid(b)) {
        throw std::invalid_argument("Invalid matrix");
    }
    if (a.cols != b.rows) {
        throw std::invalid_argument("cols(a) must equal rows(b)");
    }

    Matrix result = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < a.cols; ++k) {
                sum += a.data[i][k] * b.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }
    return result;
}

void print_matrix(Matrix m) {
    if (!is_valid(m)) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    const int MAX_ROWS_TO_SHOW = 10;
    const int MAX_COLS_TO_SHOW = 8;
    bool show_summary = (m.rows > MAX_ROWS_TO_SHOW || m.cols > MAX_COLS_TO_SHOW);
    int rows_to_show = show_summary ? MAX_ROWS_TO_SHOW : m.rows;
    int cols_to_show = show_summary ? MAX_COLS_TO_SHOW : m.cols;

    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < rows_to_show; ++i) {
        std::cout << "[";
        for (int j = 0; j < cols_to_show; ++j) {
            std::cout << std::setw(6) << m.data[i][j];
            if (j < cols_to_show - 1) {
                std::cout << " ";
            }
        }
        std::cout << "]";
        if (show_summary && m.cols > MAX_COLS_TO_SHOW) {
            std::cout << " ...";
        }
        std::cout << std::endl;
    }
    if (show_summary) {
        std::cout << "Matrix " << m.rows << "x" << m.cols
                  << " (showing first " << rows_to_show << "x"
                  << cols_to_show << ")" << std::endl;
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    if (data == nullptr || rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Invalid input for matrix_from_array");
    }

    Matrix mat = create_matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat.data[i][j] = data[i * cols + j];
        }
    }
    return mat;
}
