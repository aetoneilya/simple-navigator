#include <stdexcept>

#include "s21_matrix_oop.h"

int S21Matrix::get_rows() {
    return _rows;
}

int S21Matrix::get_cols() {
    return _cols;
}

void S21Matrix::set_rows(int rows) {
    if (rows < 1) 
        throw std::invalid_argument("in SET_ROWS: number of rows must be > 0");
    if (rows  != _rows) {
        double ** new_matrix = new double *[rows];
        for (int i = 0; i < rows; i++) {
            new_matrix[i] = new double[_cols];
            for (int j = 0; j < _cols; j++) {
                new_matrix[i][j] = i < _rows ? _matrix[i][j] : 0;
            }
        }
        for (int i = 0; i < _rows; i++) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
        _matrix = new_matrix;
        _rows = rows;
    }
}

void S21Matrix::set_cols(int cols) {
    if (cols < 1)
        throw std::invalid_argument("in SET_COLS: number of cols must be > 0");
    if (cols  != _cols) {
        for (int i = 0; i < _rows; i++) {
            double *tmp_row = new double[cols];
            for (int j = 0; j < cols; j++) {
                tmp_row[j] = j< _cols ? _matrix[i][j] : 0;
            }
            delete[] _matrix[i];
            _matrix[i] = tmp_row;
        }
        _cols = cols;
    }
}

void S21Matrix::resize(int rows, int cols) {
    if (rows < 1 || cols < 1)
        throw std::invalid_argument("in RESIZE: number of rows and cols must be > 0");
    if (rows != _rows || cols != _cols) {
        double ** new_matrix = new double *[rows];
        for (int i = 0; i < rows; i++) {
            new_matrix[i] = new double[cols];
            for (int j = 0; j < cols; j++) {
                new_matrix[i][j] = (i < _rows && j < _cols) ? _matrix[i][j] : 0;
            }
        }
        this->~S21Matrix();
        _matrix = new_matrix;
        _rows = rows;
        _cols = cols;
    }
}