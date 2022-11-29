#ifndef SRC_MATRIX_S21_MATRIX_OOP_H_
#define SRC_MATRIX_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace s21 {

class Matrix {
 public:
  Matrix() = default;
  Matrix(std::size_t rows, std::size_t cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  ~Matrix();

  void Swap(Matrix* other);

  std::size_t GetRows() const;
  void SetRows(std::size_t rows);
  std::size_t GetColumns() const;
  void SetColumns(std::size_t cols);

  bool EqMatrix(const Matrix& other) const;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(int number);
  void MulMatrix(const Matrix& other);
  Matrix Transpose() const;

  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  friend Matrix operator*(const Matrix& self, int number);
  friend Matrix operator*(int number, const Matrix& self);
  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(int number);
  int& operator()(std::size_t i, std::size_t j);
  const int& operator()(std::size_t i, std::size_t j) const;

 private:
  constexpr static const double kEps = 1e-7;

  std::size_t rows_ = 0, cols_ = 0;
  int** matrix_ = nullptr;
};

}  // namespace s21

#endif  // SRC_MATRIX_S21_MATRIX_OOP_H_
