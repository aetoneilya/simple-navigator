#include <stdexcept>
#include <iostream>

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : _rows(0), _cols(0), _matrix(nullptr) {
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
    if (_rows < 1 || _cols < 1) {
        throw std::invalid_argument("in S21MATRIX(rows, cols): rows and cols should be > 0");
    }
     _matrix = new double *[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new double[_cols]();
    }
}

S21Matrix::S21Matrix(const S21Matrix &other) : _rows(other._rows), _cols(other._cols) {
    _matrix = new double *[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new double[_cols];
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other(i, j);
        }
    }
}

S21Matrix::S21Matrix(S21Matrix &&other) : _rows(other._rows), _cols(other._cols), _matrix(other._matrix) {
    other._matrix = nullptr;
    other._rows = other._cols = 0;
}

S21Matrix::~S21Matrix() {
    if (_matrix != nullptr)
        for (int i = 0; i < _rows; i++) {
            delete[] _matrix[i];
        }
    delete[] _matrix;
    _matrix = nullptr;
    _rows = _cols = 0;
}
