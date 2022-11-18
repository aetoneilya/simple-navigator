#include <stdexcept>
#include <cmath>

#include "s21_matrix_oop.h"

bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool result = _rows == other._rows && _cols == other._cols;
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in EQ_MATRIX: matrix is invalid");

    for (int i = 0; i < _rows && result; i++) {
        for (int j = 0; j < _cols && result; j++) {
            if (fabs(_matrix[i][j] - other._matrix[i][j]) >= EPS)
                result = false;
        }
    }
    return result;
}
void S21Matrix::sum_matrix(const S21Matrix& other) {
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in SUM_MATRIX: matrix is invalid");
    if (_rows != other._rows || _cols != other._cols)
        throw std::logic_error("in SUM_MATRIX: matrices should have equal dimensions");

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
}
void S21Matrix::sub_matrix(const S21Matrix& other) {
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in SUB_MATRIX: matrix is invalid");
    if (_rows != other._rows || _cols != other._cols)
        throw std::logic_error("in SUB_MATRIX: matrices should have equal dimensions");

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] -= other._matrix[i][j];
        }
    }
}
void S21Matrix::mul_number(const double num) {
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in MUL_MATRIX(double): matrix is invalid");

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] *= num;
        }
    }
}
void S21Matrix::mul_matrix(const S21Matrix& other) {
    if (_rows == 0 || _cols == 0 || other._rows == 0 || other._cols == 0)
        throw std::logic_error("in MUL_MATRIX(S21Matrix): matrix is invalid");
    if (_cols != other._rows)
        throw std::logic_error("in MUL_MATRIX(S21Matrix): this->_cols should be equal to other._rows");

    S21Matrix tmp(_rows, other._cols);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < other._cols; j++) {
            for (int k = 0; k < _cols; k++)
                tmp._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
        }
    }
    (*this) = tmp;
}
S21Matrix S21Matrix::transpose() {
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in TRANSPOSE: matrix is invalid");
    
    S21Matrix result(_cols, _rows);

    for (int i = 0; i < _cols; i++) {
        for (int j = 0; j < _rows; j++) {
            result._matrix[i][j] = _matrix[j][i];
        }
    }
    return result;
}
S21Matrix S21Matrix::calc_complements() {
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in CALC_COMPLEMENTS: matrix is invalid");
    if (_rows != _cols)
        throw std::logic_error("in CALC_COMPLEMENTS: matrix must be square");

    S21Matrix result(*this);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result._matrix[i][j] = pow(-1, i + j) * minor(i, j);
        }
    }
    return result;
}
double S21Matrix::determinant() {
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in DETERMINANT: matrix is invalid");
    if (_rows != _cols)
        throw std::logic_error("in DETERMINANT: matrix must be square");

    double result = 0;
    if (_rows == 1) {
        result = _matrix[0][0];
    } else {
        for (int i = 0; i < _cols; i++)
            result += pow(-1, i) * _matrix[0][i] * minor(0, i);
    }
    return result;
}
double S21Matrix::minor(int row, int col) {
    if (_rows == 0 || _cols == 0)
        throw std::logic_error("in MINOR: matrix is invalid");
    if (_rows != _cols)
        throw std::logic_error("in MINOR: matrix must be square");
    
    S21Matrix submatr(_rows - 1, _cols - 1);
    int skipped_row = 0;
    for (int i = 0; i < _rows; i++) {
        if (i == row) {
            skipped_row = 1;
            continue;
        }
        int skipped_col = 0;
        for (int j = 0; j < _cols; j++) {
            if (j == col) {
                skipped_col = 1;
                continue;
            }
            submatr._matrix[i - skipped_row][j - skipped_col] = _matrix[i][j];
        }
    }
    return submatr.determinant();
}
S21Matrix S21Matrix::inverse_matrix() {
    double det = determinant();
    if (fabs(det) < EPS)
        throw std::runtime_error("in INVERSE_MATRIX: matrix determinant is 0");
    
    S21Matrix result = calc_complements();
    result = result.transpose();
    result.mul_number(1.0 / det);
    return result;
}