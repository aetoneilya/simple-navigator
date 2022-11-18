#pragma once

#define DEFAULT_MATR_SIZE 3

#define EPS 1e-7

class S21Matrix {
 private:
    int _rows, _cols;
    double **_matrix;

 public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    bool eq_matrix(const S21Matrix& other);
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose();
    S21Matrix calc_complements();
    double determinant();
    double minor(int row, int col);
    S21Matrix inverse_matrix();

    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    friend S21Matrix operator*(S21Matrix const& self, double number);
    friend S21Matrix operator*(double number, S21Matrix const& self);
    bool operator==(const S21Matrix& other);
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(const double num);
    double & operator()(int i, int j) const;

    int get_rows();
    int get_cols();

    void set_rows(int rows);
    void set_cols(int cols);
    void resize(int rows, int cols);
};
