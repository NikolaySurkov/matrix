#include "matrix_exception.h"

void ExceptHandling::WriteError() {
  if (type_error_ == 1) {
    this->msg_ += "The size of the matrices is zero";
  } else if (type_error_ == 2) {
    this->msg_ += "The size of the \"matrix(this)\" is zero";
  } else if (type_error_ == 3) {
    this->msg_ += "The size of the \"matrix(other)\" is zero";
  } else if (type_error_ == 4) {
    this->msg_ +=
        "Different number of rows and columns in \"this->matix_\" and "
        "\"other.matrix\"";
  } else if (type_error_ == 5) {
    this->msg_ +=
        "Different number of  columns in \'this->matix_\' and \"other.matrix\"";
  } else if (type_error_ == 6) {
    this->msg_ +=
        "Different number of rows in \'this->matix_\' and \"other.matrix\"";
  } else if (type_error_ == 7) {
    this->msg_ +=
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix";
  } else if (type_error_ == 8) {
    this->msg_ += "Index exceeds matrix dimensions";
  } else if (type_error_ == 9) {
    this->msg_ += "Invalid index value(index < 0)";
  } else if (type_error_ == 10) {
    this->msg_ += "The matrix is not square (rows != cols)";
  } else if (type_error_ == 11) {
    this->msg_ += "Determine the matrix is zero";
  }
}
