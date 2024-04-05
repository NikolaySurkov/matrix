/*
 @file matrix_oop.h
 @author ns
 @copyright ns
*/

#ifndef SRC_MATRIX_OOP_H_
#define SRC_MATRIX_OOP_H_

#include <iostream>
#include <utility>
#define EPSILON 1.0e-7
namespace matrix {
class Matrix {
 public:
  Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr){};

  explicit Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other) noexcept;
  ~Matrix() noexcept;

  int GetRows() const noexcept { return rows_; }
  int GetCols() const noexcept { return cols_; }
  void SetRows(int const rows);
  void SetCols(int const cols);

  bool EqMatrix(const Matrix& other) const noexcept;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();

  bool operator==(const Matrix& other) const;
  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other) noexcept;
  double operator()(int i, int j) const;
  double& operator()(int i, int j);
  Matrix operator*(const Matrix& other);
  Matrix operator*(double number) const noexcept;
  friend Matrix operator*(double number, const Matrix& matrix) noexcept;
  Matrix& operator*=(double number);
  Matrix& operator*=(const Matrix& other);
  Matrix operator-(const Matrix& other) const;
  Matrix& operator-=(const Matrix& other);
  Matrix operator+(const Matrix& other) const;
  Matrix& operator+=(const Matrix& other);

 private:
  void MemoryAllocationForMatrix(int rows, int cols);
  void FreeMatrix() noexcept;
  void CheckExistenceMatrices(const Matrix& other) const;
  void CheckExistenceMatrix() const;
  void CheckDimensionMatrices(const Matrix& other) const;
  void CheckDimensionMatrices() const;
  void CheckDimensionMatricesMult(const Matrix& other) const;
  void CheckingThatMatrixSquare() const;
  void CheckMatrixIndexBoundaries(const int i, const int j) const;
  Matrix MatrixMinor(int index_rows, int index_cols) const;
  double FindMaximumNumberInColumn(int indx_rows, int indx_cols,
                                   int& index_max_el) const;
  double SwapRowsMatrix(int indx_rows, int const indx_cols, int index_max_el);
  void MultiplyRows(int indx_rows, int const indx_cols, double maxValueElement);
  double CalculateByGaussMethod();
  int rows_;
  int cols_;
  double** matrix_;
};
}  // namespace 

#endif  // SRC_MATRIX_OOP_H_
