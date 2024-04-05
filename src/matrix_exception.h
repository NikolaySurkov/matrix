#ifndef SRC_MATRIX_EXCEPTION_H_
#define SRC_MATRIX_EXCEPTION_H_
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

class ExceptHandling : public std::exception {
 public:
  explicit ExceptHandling(const std::string& message) : msg_(message) {}
  explicit ExceptHandling(int type_error) : type_error_(type_error) {
    WriteError();
  }
  ExceptHandling(int const type_error, int const rows, int const cols)
      : type_error_(type_error), count_rows_(rows), count_cols_(cols) {
    WriteError();
    msg_ += ", size matrix(rows = ";
    msg_ += std::to_string(count_rows_);
    msg_ += ", cols = ";
    msg_ += std::to_string(count_cols_) + ");";
  }
  const char* what() const noexcept override { return msg_.c_str(); }
  std::string get_msg() const noexcept { return this->msg_; }

 private:
  void WriteError();
  int type_error_;
  std::string msg_;
  int count_rows_;
  int count_cols_;
};

#endif  // SRC_MATRIX_EXCEPTION_H_
