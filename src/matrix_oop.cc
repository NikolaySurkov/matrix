#include "matrix_oop.h"

#include "matrix_exception.h"

namespace matrix {

Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  try {
    this->MemoryAllocationForMatrix(rows, cols);
  } catch (ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Constructor Matrix(...) -> " + e.get_msg()));
  } catch (std::bad_alloc& e) {
    std::cout << " Constructor Matrix(...) -> " << e.what();
    this->FreeMatrix();
    std::throw_with_nested(std::bad_alloc());
  }
}

Matrix::Matrix(const Matrix& other)
    : Matrix(other.rows_, other.cols_) {
  if (this->rows_ > 0 && this->cols_ > 0) {
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

Matrix::~Matrix() noexcept {
  if (matrix_) {
    this->FreeMatrix();
    this->rows_ = 0;
    this->cols_ = 0;
  }
}

void Matrix::SetRows(int const rows) {
  bool status = false;
  if (matrix_ && rows_ > 0 && cols_ > 0 && rows != rows_) {
    status = true;
  }
  if (status) {
    Matrix A(rows, cols_);
    int min_rows = rows < rows_ ? rows : rows_;
    for (int i = 0; i != min_rows; ++i) {
      for (int j = 0; j != cols_; ++j) {
        A(i, j) = matrix_[i][j];
      }
    }
    *this = std::move(A);
  }
}

void Matrix::SetCols(int const cols) {
  bool status = false;
  if (matrix_ && cols > 0 && rows_ > 0 && cols != cols_) {
    status = true;
  }
  if (status) {
    Matrix A(rows_, cols);
    int min_cols = cols < cols_ ? cols : cols_;
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != min_cols; ++j) {
        A(i, j) = matrix_[i][j];
      }
    }
    *this = std::move(A);
  }
}

bool Matrix::EqMatrix(const Matrix& other) const noexcept {
  bool status = false;
  status = rows_ == other.rows_ && cols_ == other.cols_ ? true : false;
  if (status && rows_ > 0 && cols_ > 0) {
    for (int i = 0; i != rows_ && status; ++i) {
      for (int j = 0; j != cols_ && status; ++j) {
        status = abs(matrix_[i][j] - other(i, j)) < EPSILON ? true : false;
      }
    }
  }
  return status;
}

void Matrix::SumMatrix(const Matrix& other) {
  try {
    this->CheckExistenceMatrices(other);
    this->CheckDimensionMatrices(other);
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] += other(i, j);
      }
    }
  } catch (ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Eroor: SumMatrix(...) -> " + e.get_msg()));
  }
}

void Matrix::SubMatrix(const Matrix& other) {
  try {
    this->CheckExistenceMatrices(other);
    this->CheckDimensionMatrices(other);
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] -= other(i, j);
      }
    }
  } catch (ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Eroor: SubMatrix(...) -> " + e.get_msg()));
  }
}

void Matrix::MulNumber(const double num) {
  try {
    this->CheckDimensionMatrices();
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  } catch (ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Eroor: MulNumber(...) -> " + e.get_msg()));
  }
}

void Matrix::MulMatrix(const Matrix& other) {
  try {
    this->CheckExistenceMatrices(other);
    this->CheckDimensionMatricesMult(other);
    Matrix m_result(rows_, other.GetCols());
    for (int i = 0; i != m_result.GetRows(); ++i) {
      for (int j = 0; j != m_result.GetCols(); ++j) {
        for (int k = 0; k != cols_; k++) {
          m_result(i, j) += matrix_[i][k] * other(k, j);
        }
      }
    }
    *this = std::move(m_result);
  } catch (const ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Error: MulMatrix(...) -> " + e.get_msg()));
  }
}

Matrix Matrix::Transpose() {
  this->CheckExistenceMatrix();  //?
  Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result(i, j) = matrix_[j][i];
    }
  }
  return result;
}

Matrix Matrix::CalcComplements() {
  Matrix m_result(rows_, cols_);
  try {
    this->CheckExistenceMatrix();
    this->CheckingThatMatrixSquare();
    int sign = 1;
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != cols_; ++j) {
        sign = ((i + 1 + j + 1) % 2) ? -1 : 1;
        Matrix MinorMatrix;
        MinorMatrix = MatrixMinor(i, j);
        m_result(i, j) = (MinorMatrix.Determinant() * sign);
      }
    }
  } catch (const ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Error: CalcComplements() -> " + e.get_msg()));
  }
  return m_result;
}

double Matrix::Determinant() {
  double result = 1.0;
  try {
    this->CheckExistenceMatrix();
    this->CheckingThatMatrixSquare();
    if (rows_ == 1) {
      result = matrix_[0][0];
    } else {
      result = CalculateByGaussMethod();
    }
  } catch (const ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Error: Determinant() -> " + e.get_msg()));
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  Matrix m_result;
  double determinant = 0.0;
  try {
    this->CheckExistenceMatrix();
    this->CheckingThatMatrixSquare();
    determinant = this->Determinant();
    if (std::abs(determinant) <= EPSILON) {
      throw ExceptHandling(11);
    }
    if (rows_ == 1) {
      m_result = *this;
      m_result(0, 0) = (1 / determinant);
    } else {
      m_result = Transpose().CalcComplements() * (1.0 / determinant);
    }
  } catch (const ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("Error: InverseMatrix() -> " + e.get_msg()));
  }
  return m_result;
}

bool Matrix::operator==(const Matrix& other) const {
  return this->EqMatrix(other);
}

// не забыть переписать это и конструктор копирования (общая функция)
Matrix& Matrix::operator=(const Matrix& other) {
  Matrix Dublicate(other);
  *this = std::move(Dublicate);
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
  if (this != &other) {
    this->FreeMatrix();
    std::swap(matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
  }
  return *this;
}

double Matrix::operator()(int i, int j) const {
  try {
    this->CheckMatrixIndexBoundaries(i, j);
  } catch (const ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("operator()(...) const -> " + e.get_msg()));
  }
  return this->matrix_[i][j];
}

double& Matrix::operator()(int i, int j) {
  try {
    this->CheckMatrixIndexBoundaries(i, j);
  } catch (const ExceptHandling& e) {
    std::throw_with_nested(
        ExceptHandling("& operator()(...) -> " + e.get_msg()));
  }
  return this->matrix_[i][j];
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

Matrix Matrix::operator*(double number) const noexcept {
  Matrix result = *this;
  result.MulNumber(number);
  return result;
}

Matrix operator*(double number, const Matrix& matrix_obj) noexcept {
  Matrix result = matrix_obj * number;
  return result;
}

Matrix& Matrix::operator*=(double number) {
  this->MulNumber(number);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

Matrix Matrix::operator-(const Matrix& other) const {
  Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
  Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

void Matrix::MemoryAllocationForMatrix(int rows, int cols) {
  try {
    CheckDimensionMatrices();
    this->matrix_ = new double*[rows]();
    this->matrix_[0] = new double[rows * cols]();
    for (int i = 1; i != rows; ++i) {
      this->matrix_[i] = this->matrix_[i - 1] + cols;
    }
  } catch (ExceptHandling& e) {
    std::throw_with_nested(ExceptHandling(
        "Eroor: MemoryAllocationForMatrix(...) -> " + e.get_msg()));
  } catch (std::bad_alloc& e) {
    std::cout << e.what();
    std::throw_with_nested(std::bad_alloc());
  }
}

void Matrix::FreeMatrix() noexcept {
  if (matrix_) {
    delete[] this->matrix_[0];
    matrix_[0] = nullptr;
    delete[] this->matrix_;
    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

void Matrix::CheckExistenceMatrices(const Matrix& other) const {
  if (!this->matrix_ && !other.matrix_) {
    throw ExceptHandling{1};
  } else if (!this->matrix_ && other.matrix_) {
    throw ExceptHandling{2};
  } else if (this->matrix_ && !other.matrix_) {
    throw ExceptHandling{3};
  }
}
void Matrix::CheckExistenceMatrix() const {
  if (!this->matrix_) {
    throw ExceptHandling(2);
  }
}
void Matrix::CheckDimensionMatricesMult(const Matrix& other) const {
  if (this->cols_ != other.rows_) {
    throw ExceptHandling(7);
  }
}
void Matrix::CheckingThatMatrixSquare() const {
  if (this->rows_ != this->cols_) {
    throw ExceptHandling(10);
  }
}
void Matrix::CheckDimensionMatrices(const Matrix& other) const {
  if (this->rows_ != other.rows_ && this->cols_ != other.cols_) {
    throw ExceptHandling(4);
  } else if (this->rows_ == other.rows_ && this->cols_ != other.cols_) {
    throw ExceptHandling(5);
  } else if (this->cols_ == other.cols_ && this->rows_ != other.rows_) {
    throw ExceptHandling(6);
  }
}

void Matrix::CheckDimensionMatrices() const {
  if (this->rows_ <= 0 || this->cols_ <= 0) {
    throw ExceptHandling(2, this->GetRows(), this->GetCols());
  }
}

void Matrix::CheckMatrixIndexBoundaries(const int i, const int j) const {
  if (i >= this->rows_ || j >= this->cols_) {
    throw ExceptHandling(8, this->GetRows(), this->GetCols());
  } else if (i < 0 || j < 0) {
    throw ExceptHandling(9, this->GetRows(), this->GetCols());
  }
}

double Matrix::FindMaximumNumberInColumn(int indx_rows, int const indx_cols,
                                            int& index_max_el) const {
  double maxValueElement = 0.0;
  for (int i = indx_rows; i != rows_; ++i) {
    if ((std::abs((*this)(i, indx_cols)) - maxValueElement) > EPSILON) {
      maxValueElement = std::abs((*this)(i, indx_cols));
      index_max_el = i;
    }
  }
  return maxValueElement;
}

double Matrix::SwapRowsMatrix(int indx_rows, int const indx_cols,
                                 int index_max_el) {
  double maxValueElement = 0.0;
  if (index_max_el != indx_rows) {
    for (int j = indx_cols; j != cols_; ++j) {
      maxValueElement = (*this)(indx_cols, j);
      (*this)(indx_rows, j) = (*this)(index_max_el, j);
      (*this)(index_max_el, j) = (-maxValueElement);
    }
  }
  maxValueElement = (*this)(indx_rows, indx_cols);
  return maxValueElement;
}

void Matrix::MultiplyRows(int indx_rows, int const indx_cols,
                             double maxValueElement) {
  double commonMult = 0.0;
  for (int i = indx_rows + 1; i != rows_; ++i) {
    commonMult = -((*this)(i, indx_cols)) / maxValueElement;
    matrix_[i][indx_cols] = 0.0;
    for (int j = indx_cols + 1; j != cols_; ++j) {
      matrix_[i][j] += commonMult * (*this)(indx_rows, j);
    }
  }
}

double Matrix::CalculateByGaussMethod() {
  bool status = true;
  double result = 1.0;
  double numberMax = 0.0;
  int importIndex = 0;
  Matrix B = *this;
  for (int i = 0, j = 0; status && i != rows_ && j != cols_; ++i, ++j) {
    numberMax = B.FindMaximumNumberInColumn(i, j, importIndex);
    if (numberMax > EPSILON) {
      numberMax = B.SwapRowsMatrix(i, j, importIndex);
      B.MultiplyRows(i, j, numberMax);
    } else {
      result = 0.0;
      status = false;
    }
  }
  for (int i = 0; status && i < B.rows_; i++) result *= B(i, i);
  return result;
}

Matrix Matrix::MatrixMinor(int index_closed_row,
                                 int index_closed_cols) const {
  Matrix minor(rows_ - 1, cols_ - 1);
  int count_rows = 0;
  int count_cols = 0;
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      if (i != index_closed_row && j != index_closed_cols) {
        minor(count_rows, count_cols) = matrix_[i][j];
        count_cols++;
      }
    }
    if (i != index_closed_row) {
      count_rows++;
      count_cols = 0;
    }
  }
  return minor;
}

}  // namespace matrix
