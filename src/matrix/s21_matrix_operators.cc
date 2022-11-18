#include <stdexcept>

#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    if (_rows != other._rows || _cols != other._cols)
        throw std::logic_error("in OPERATOR+: matrices should have same number of rows and cols");
    S21Matrix res(*this);
    res.sum_matrix(other);
    return res;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    if (_rows != other._rows || _cols != other._cols)
        throw std::logic_error("in OPERATOR-: matrices should have same number of rows and cols");
    S21Matrix res(*this);
    res.sub_matrix(other);
    return res;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
    if (_cols != other._rows)
        throw std::logic_error("in OPERATOR*(S21Matrix): this->_cols should be equal to other._rows");
    S21Matrix res(*this);
    res.mul_matrix(other);
    return res;
}
S21Matrix operator*(S21Matrix const& self, double number) {
    S21Matrix result(self);
    result.mul_number(number);
    return result;
}
S21Matrix operator*(double number, S21Matrix const& self) {
    return self * number;
}

bool S21Matrix::operator==(const S21Matrix& other) {
    return this->eq_matrix(other);
}
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        this->resize(other._rows, other._cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _matrix[i][j] = other._matrix[i][j];
            }
        }
    }
    return *this;
}
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    sum_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    sub_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
    mul_matrix(other);
    return *this;
}
S21Matrix& S21Matrix::operator*=(const double num) {
    mul_number(num);
    return *this;
}
double & S21Matrix::operator()(int i, int j) const{
    if (i >= _rows || j >= _cols || i < 0 || j < 0) {
        throw std::out_of_range("in OPERATOR(): i or j is out of range");
    }
    return _matrix[i][j];
}