#include "../matrix_exception.h"
#include "../matrix_oop.h"
#include <gtest/gtest.h>
using namespace matrix;

/*CONSTRUCTORS*/
TEST(createMatrix, test_1) {
  Matrix a(10, 10);
  EXPECT_EQ(0.0, a(0, 0));
}

TEST(createMatrix, test_3) {
  Matrix a(10, 10);
  Matrix b = std::move(a);
  EXPECT_EQ(0, a.GetCols());
}

TEST(CreateMatrix, EXCEPTION_1) {
  try {
    Matrix A(-1, 4);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Constructor Matrix(...) -> Eroor: "
                 "MemoryAllocationForMatrix(...) -> The size of the "
                 "\"matrix(this)\" is zero, size matrix(rows = -1, cols = 4);",
                 e.what());
  }
}

TEST(copyConstructor, test_1) {
  Matrix a(3, 6);
  a(0, 0) = 77;
  a(1, 1) = 78;
  a(2, 2) = 79.1;
  a(2, 3) = 80;
  Matrix b(a);

  EXPECT_EQ(77.00, b(0, 0));
  EXPECT_EQ(78.0, b(1, 1));
  EXPECT_EQ(79.1, b(2, 2));
  EXPECT_EQ(80.0, b(2, 3));
}

/*ACCESSORS*/
TEST(getMatrix, test_1) {
  Matrix a(10, 10);
  EXPECT_EQ(0.0, a(0, 0));
}

/*OPERATORS*/
TEST(OperatorRoundBrackets, test_1) {
  Matrix a(10, 10);
  a(1, 1) = 78;
  EXPECT_EQ(78.0, a(1, 1));
}

TEST(OperatorRoundBrackets, TestException_0) {
  Matrix const A(4, 4);
  try {
    A(-1, 3);
    FAIL();
  } catch (ExceptHandling &e) {
    ASSERT_STREQ("operator()(...) const -> Invalid index value(index < 0), "
                 "size matrix(rows = 4, cols = 4);",
                 e.what());
  }
}

TEST(OperatorRoundBrackets, TestException_1) {
  Matrix A(4, 4);
  try {
    A(-1, 3);
    FAIL();
  } catch (ExceptHandling &e) {
    ASSERT_STREQ("& operator()(...) -> Invalid index value(index < 0), size "
                 "matrix(rows = 4, cols = 4);",
                 e.what());
  }
}

TEST(OperatorRoundBrackets, TestException_2) {
  Matrix A(4, 4);
  Matrix const B(4, 4);
  Matrix R(4, 4);
  try {
    R(1, 2) += A(2, 4) * B(3, 4);
    FAIL();
  } catch (ExceptHandling &e) {
    ASSERT_STREQ("& operator()(...) -> Index exceeds matrix dimensions, size "
                 "matrix(rows = 4, cols = 4);",
                 e.what());
  }
}

TEST(TestOperatorBrackets, TestOperatorBracketsException1) {
  Matrix matrix_check(99, 99);
  EXPECT_ANY_THROW(matrix_check(100, 99));
}

TEST(OperatorRoundBrackets, TestException_3) {
  Matrix A(4, 4);
  try {
    A(4, 4) = 15;
    FAIL();
  } catch (ExceptHandling &e) {
    ASSERT_STREQ("& operator()(...) -> Index exceeds matrix dimensions, size "
                 "matrix(rows = 4, cols = 4);",
                 e.what());
  }
}

TEST(OperatorRoundBrackets, TestException_4) {
  Matrix A(4, 4);
  try {
    A(-1, 3) = 27;
    FAIL();
  } catch (ExceptHandling &e) {
    ASSERT_STREQ("& operator()(...) -> Invalid index value(index < 0), size "
                 "matrix(rows = 4, cols = 4);",
                 e.what());
  }
}

TEST(OperatorMinusEq, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix C(2, 2);
  Matrix result(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  result = (A -= B);
  EXPECT_TRUE(result == C);
  EXPECT_TRUE(result == A);
  EXPECT_FALSE(result == B);
}

TEST(OperatorMOWE, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix C;
  Matrix result;
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  C = B = A;
  B = std::move(A);
  EXPECT_TRUE(A == result);
  EXPECT_FALSE(result == B);
}

TEST(OperatorMinus, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix C(2, 2);
  Matrix result(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;
  result = (A - B);
  EXPECT_TRUE(result == C);
  EXPECT_FALSE(result == A);
  EXPECT_FALSE(result == B);
}

TEST(OperatorPlusEq, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix C(2, 2);
  Matrix result(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  C(0, 0) = 2;
  C(0, 1) = 4;
  C(1, 0) = 6;
  C(1, 1) = 8;

  result = (A += B);
  EXPECT_TRUE(result == C);
}

TEST(OperatorMultEq, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix C(2, 2);
  Matrix result(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  C(0, 0) = 7;
  C(0, 1) = 10;
  C(1, 0) = 15;
  C(1, 1) = 22;

  result = (A *= B);
  EXPECT_TRUE(result == C);
  EXPECT_TRUE(result == A);
  EXPECT_FALSE(result == B);
}

TEST(OperatorMult, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix C(2, 2);
  Matrix result(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  C(0, 0) = 7;
  C(0, 1) = 10;
  C(1, 0) = 15;
  C(1, 1) = 22;

  result = (A * B);
  EXPECT_TRUE(result == C);
  EXPECT_FALSE(result == A);
  EXPECT_FALSE(result == B);
}

TEST(OperatorMultEqNum, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  double number = 2.0;
  Matrix result(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 2;
  B(0, 1) = 4;
  B(1, 0) = 6;
  B(1, 1) = 8;
  result = (number * A);
  EXPECT_TRUE(result == B);
  result = A *= number;
  EXPECT_TRUE(result == A);
  EXPECT_TRUE(result == B);
}

TEST(OperatorPlus, test_1) {
  Matrix A(2, 2);
  Matrix B(2, 2);
  Matrix C(2, 2);
  Matrix result(2, 2);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 3;
  B(1, 1) = 4;

  C(0, 0) = 2;
  C(0, 1) = 4;
  C(1, 0) = 6;
  C(1, 1) = 8;

  result = (A + B);
  EXPECT_TRUE(result == C);
  EXPECT_FALSE(result == A);
  EXPECT_FALSE(result == B);
}

TEST(OperatorRoundBrackets, test_2) {
  Matrix A(9, 20);
  A(8, 19) = 819.819;
  A(0, 0) = -819.819;
  double number_check1 = A(8, 19);
  double number_check2 = A(0, 0);
  EXPECT_NEAR(819.819, number_check1, EPSILON);
  EXPECT_NEAR(-819.819, number_check2, EPSILON);
}

TEST(OperatorEQ, test_1) {
  Matrix A(9, 20);
  A(8, 19) = 819.81922;
  A(0, 0) = -819.81923;
  Matrix B = A;
  EXPECT_NEAR(819.81922, B(8, 19), EPSILON);
  EXPECT_NEAR(-819.81923, B(0, 0), EPSILON);
}

TEST(OperatorEQ, test_1_true) {
  Matrix A(9, 20);
  A(8, 19) = 819.81922;
  A(0, 0) = -819.81923;
  Matrix B = A;
  ASSERT_TRUE(A == B);
  EXPECT_NEAR(-819.81923, B(0, 0), EPSILON);
}

TEST(OperatorEQ, test_2_false) {
  Matrix A(9, 20);
  A(8, 19) = 819.81922;
  A(0, 0) = -819.81923;
  Matrix C;
  C = std::move(A);
  Matrix B;
  ASSERT_TRUE(A == B);
  ASSERT_FALSE(B == C);
}

/* ******************FUNCTION ******************* */
// SUM

TEST(SumMatrix, test_1) {
  Matrix A(4, 4);
  A(0, 0) = 23.33;
  A(0, 1) = 12.55;
  A(0, 2) = 5.989;
  A(0, 3) = 45;
  A(1, 0) = 123.0;
  A(1, 1) = 234;
  A(1, 2) = 342;
  A(1, 3) = 343;
  A(2, 0) = 454;
  A(2, 1) = 432;
  A(2, 2) = 123;
  A(2, 3) = 77;
  A(3, 0) = -98;
  A(3, 1) = -6;
  A(3, 2) = -34;
  A(3, 3) = 341;
  Matrix B(4, 4);
  B(0, 0) = 76.670;
  B(0, 1) = 87.45;
  B(0, 2) = 94.011;
  B(0, 3) = 55;
  B(1, 0) = -23;
  B(1, 1) = -134;
  B(1, 2) = -242;
  B(1, 3) = -243;
  B(2, 0) = 46;
  B(2, 1) = 68;
  B(2, 2) = 377;
  B(2, 3) = 423;
  B(3, 0) = 598;
  B(3, 1) = 506;
  B(3, 2) = 534.000000001;
  B(3, 3) = 159;
  int rows = A.GetRows();
  int cols = A.GetCols();
  A.SumMatrix(B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i < 2) {
        EXPECT_NEAR(100, A(i, j), EPSILON);
      } else {
        EXPECT_NEAR(500, A(i, j), EPSILON);
      }
    }
  }
}

TEST(SumMatrix, TestException_1) {
  Matrix A(4, 4);
  Matrix B;
  try {
    A.SumMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    ASSERT_STREQ(
        "Eroor: SumMatrix(...) -> The size of the \"matrix(other)\" is zero",
        e.what());
  }
}

TEST(SumMatrix, TestException_2) {
  Matrix A;
  Matrix B(4, 4);
  try {
    A.SumMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    EXPECT_STREQ(
        "Eroor: SumMatrix(...) -> The size of the \"matrix(this)\" is zero",
        e.what());
  }
}

TEST(SumMatrix, TestException_3) {
  Matrix A;
  Matrix B;
  try {
    A.SumMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SumMatrix(...) -> The size of the matrices is zero",
                 e.what());
  }
}

TEST(SumMatrix, TestException_4) {
  Matrix A(1, 1);
  Matrix B(2, 2);
  try {
    A.SumMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SumMatrix(...) -> Different number of rows and "
                 "columns in \"this->matix_\" and \"other.matrix\"",
                 e.what());
  }
}

TEST(SumMatrix, TestException_5) {
  Matrix A(1, 1);
  Matrix B(2, 1);
  try {
    A.SumMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SumMatrix(...) -> Different number of rows in "
                 "'this->matix_' and \"other.matrix\"",
                 e.what());
  }
}

TEST(SumMatrix, TestException_6) {
  Matrix A(1, 1);
  Matrix B(2, 1);
  try {
    A.SumMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SumMatrix(...) -> Different number of rows in "
                 "'this->matix_' and \"other.matrix\"",
                 e.what());
  }
}
// SUB

TEST(SubMatrix, test_1) {
  Matrix A(4, 4);
  Matrix B(4, 4);
  A(0, 0) = 769.2342;
  A(0, 1) = 123444.120;
  A(0, 2) = 9893.07;
  A(0, 3) = 1.0;
  A(1, 0) = 14654.9999;
  A(1, 1) = 47.765432;
  A(1, 2) = 122395.89;
  A(1, 3) = -56.65;
  A(2, 0) = 345.54;
  A(2, 1) = 234.767;
  A(2, 2) = 123.674;
  A(2, 3) = 56743.56965430;
  A(3, 0) = -98.23452323;
  A(3, 1) = -5343.55;
  A(3, 2) = -0.342342;
  A(3, 3) = -0.9412345;

  B(0, 0) = -231.76580000;
  B(0, 1) = 122443.12000000;
  B(0, 2) = 8892.07000000;
  B(0, 3) = -1000.000000009;
  B(1, 0) = 13653.99990000;
  B(1, 1) = -953.23456800;
  B(1, 2) = 121394.89000000;
  B(1, 3) = -1057.65000000;
  B(2, 0) = 348.54000000;
  B(2, 1) = 237.76700000;
  B(2, 2) = 126.67400000;
  B(2, 3) = 56746.56965430;
  B(3, 0) = -95.23452323;
  B(3, 1) = -5340.55000000;
  B(3, 2) = 2.65765800;
  B(3, 3) = 2.05876550;
  Matrix result = A - B;
  for (int i = 0; i < A.GetRows(); i++) {
    for (int j = 0; j < A.GetCols(); j++) {
      if (i < 2) {
        EXPECT_NEAR(1001.0, result(i, j), EPSILON);
      } else {
        EXPECT_NEAR(-3, result(i, j), EPSILON);
      }
    }
  }
}

TEST(SubMatrix, TestException_1) {
  Matrix A(1, 1);
  Matrix B(2, 2);
  try {
    A.SubMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SubMatrix(...) -> Different number of rows and "
                 "columns in \"this->matix_\" and \"other.matrix\"",
                 e.what());
  }
}

TEST(SubMatrix, TestException_2) {
  Matrix A(1, 1);
  Matrix B(2, 1);
  try {
    A.SubMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SubMatrix(...) -> Different number of rows in "
                 "'this->matix_' and \"other.matrix\"",
                 e.what());
  }
}

TEST(SubMatrix, TestException_3) {
  Matrix A(1, 1);
  Matrix B(2, 1);
  try {
    A.SubMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SubMatrix(...) -> Different number of rows in "
                 "'this->matix_' and \"other.matrix\"",
                 e.what());
  }
}

TEST(SubMatrix, TestException_4) {
  Matrix A(1, 1);
  Matrix B(1, 2);
  try {
    A.SubMatrix(B);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: SubMatrix(...) -> Different number of  columns in "
                 "'this->matix_' and \"other.matrix\"",
                 e.what());
  }
}

// INVERSE
TEST(InverceMatrix, test_1) {
  Matrix A(3, 3);
  Matrix B(3, 3);
  Matrix result(3, 3);

  A(0, 0) = 2.00000000;
  A(0, 1) = 5.00000000;
  A(0, 2) = 7.00000000;
  A(1, 0) = 6.00000000;
  A(1, 1) = 3.00000000;
  A(1, 2) = 4.00000000;
  A(2, 0) = 5.00000000;
  A(2, 1) = -2.00000000;
  A(2, 2) = -3.00000000;

  B(0, 0) = 1.000000000;
  B(0, 1) = -1.000000000;
  B(0, 2) = 1.000000000;
  B(1, 0) = -38.000000000;
  B(1, 1) = 41.000000000;
  B(1, 2) = -34.000000000;
  B(2, 0) = 27.000000000;
  B(2, 1) = -29.000000000;
  B(2, 2) = 24.000000000;

  result = A.InverseMatrix();
  ASSERT_TRUE(result == B);
}

TEST(InverceMatrix, test_2) {
  Matrix A(3, 3);
  Matrix B(3, 3);
  Matrix result(3, 3);
  A(0, 0) = 2.00000000;
  A(0, 1) = 5.00000000;
  A(0, 2) = 7.00000000;
  A(1, 0) = 6.00000000;
  A(1, 1) = 3.00000000;
  A(1, 2) = 4.00000000;
  A(2, 0) = 5.00000000;
  A(2, 1) = -2.00000000;
  A(2, 2) = -3.00000000;
  B(0, 0) = 1.000000000;
  B(0, 1) = -1.000000000;
  B(0, 2) = 1.000000000;
  B(1, 0) = -38.000000000;
  B(1, 1) = 41.000000000;
  B(1, 2) = -34.000000000;
  B(2, 0) = 27.000000000;
  B(2, 1) = -29.000000000;
  B(2, 2) = 24.000000000;
  result = A.InverseMatrix();
  ASSERT_TRUE(result == B);
}

TEST(InverceMatrix, test_3) {
  Matrix A(1, 1);
  Matrix B(1, 1);
  Matrix result(1, 1);
  A(0, 0) = 2.00000000;

  B(0, 0) = 0.500000000;

  result = A.InverseMatrix();
  ASSERT_TRUE(result == B);
}

TEST(InverceMatrix, EXCEPTION_1) {
  Matrix A(100, 100);
  Matrix B(100, 100);
  try {
    B = A.InverseMatrix();
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Error: InverseMatrix() -> Determine the matrix is zero",
                 e.what());
  }
}

TEST(InverceMatrix, EXCEPTION_2) {
  Matrix A;
  Matrix B(100, 100);
  try {
    B = A.InverseMatrix();
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ(
        "Error: InverseMatrix() -> The size of the \"matrix(this)\" is zero",
        e.what());
  }
}

TEST(InverceMatrix, EXCEPTION_3) {
  Matrix A(100, 99);
  Matrix B(100, 100);
  try {
    B = A.InverseMatrix();
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ(
        "Error: InverseMatrix() -> The matrix is not square (rows != cols)",
        e.what());
  }
}

TEST(Determimant, EXCEPTION_1) {
  double res = 0;
  Matrix A(10, 100);
  try {
    res = A.Determinant();
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ(
        "Error: Determinant() -> The matrix is not square (rows != cols)",
        e.what());
    ASSERT_EQ(res, 0);
  }
}

TEST(CalcComp, EXCEPTION_1) {
  Matrix A(10, 100);
  try {
    A.CalcComplements();
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ(
        "Error: CalcComplements() -> The matrix is not square (rows != cols)",
        e.what());
  }
}

TEST(Transpose, test_1) {
  Matrix A(3, 3);
  Matrix B(3, 3);
  A(0, 0) = 2.00;
  A(0, 1) = 5.00;
  A(0, 2) = 7.00;
  A(1, 0) = 6.00;
  A(1, 1) = 3.00;
  A(1, 2) = 4.00;
  A(2, 0) = 5.00;
  A(2, 1) = -2.00;
  A(2, 2) = -3.00;
  B(0, 0) = 2.0000;
  B(0, 1) = 6.0000;
  B(0, 2) = 5.0000;
  B(1, 0) = 5.0000;
  B(1, 1) = 3.0000;
  B(1, 2) = -2.0000;
  B(2, 0) = 7.0000;
  B(2, 1) = 4.0000;
  B(2, 2) = -3.0000;
  Matrix result;
  result = A.Transpose();
  ASSERT_TRUE(result == B);
}

TEST(MultNumber, test_1) {
  Matrix A(4, 4);
  Matrix B(4, 4);
  double number = 3.89879383;
  A(0, 0) = 23.33000000;
  A(0, 1) = 12.57885000;
  A(0, 2) = 5.98900000;
  A(0, 3) = 45.00012000;
  A(1, 0) = 123.00000000;
  A(1, 1) = 234.78000000;
  A(1, 2) = 342.67000000;
  A(1, 3) = 343.65000000;
  A(2, 0) = 454.56700000;
  A(2, 1) = 432.97800000;
  A(2, 2) = 123.76900000;
  A(2, 3) = 77.87600000;
  A(3, 0) = -98.12300000;
  A(3, 1) = -6.09800000;
  A(3, 2) = -34.78900000;
  A(3, 3) = 341.02700000;
  B(0, 0) = 90.958860054;
  B(0, 1) = 49.042342768;
  B(0, 2) = 23.349876248;
  B(0, 3) = 175.446190205;
  B(1, 0) = 479.551641090;
  B(1, 1) = 915.358815407;
  B(1, 2) = 1335.999681726;
  B(1, 3) = 1339.820499679;
  B(2, 0) = 1772.263014922;
  B(2, 1) = 1688.091954926;
  B(2, 2) = 482.549813545;
  B(2, 3) = 303.622468305;
  B(3, 0) = -382.561346981;
  B(3, 1) = -23.774844775;
  B(3, 2) = -135.635138552;
  B(3, 3) = 1329.593963463;
  Matrix result = A * number;
  ASSERT_TRUE(result == B);
}

TEST(MulNumber, EXCEPTION_1) {
  Matrix A;
  try {
    A.MulNumber(1.2);
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("Eroor: MulNumber(...) -> The size of the \"matrix(this)\" is "
                 "zero, size matrix(rows = 0, cols = 0);",
                 e.what());
  }
}

TEST(MulMatrix, EXCEPTION_1) {
  Matrix A(3, 4);
  Matrix B(3, 4);
  Matrix result(3, 4);
  try {
    result = A * B;
    FAIL();
  } catch (ExceptHandling &e) {
    // check exception
    ASSERT_STREQ(
        "Error: MulMatrix(...) -> The number of columns of the first matrix is "
        "not equal to the number of rows of the second matrix",
        e.what());
  }
}
TEST(Transpose, test_2) {
  Matrix A(3, 2);
  Matrix B(2, 3);
  A(0, 0) = 1.00;
  A(0, 1) = 2.00;
  A(1, 0) = 0.00;
  A(1, 1) = 4.00;
  A(2, 0) = 5.00;
  A(2, 1) = 2.00;

  B(0, 0) = 1.0000;
  B(0, 1) = 0.0000;
  B(0, 2) = 5.0000;
  B(1, 0) = 2.0000;
  B(1, 1) = 4.0000;
  B(1, 2) = 2.0000;
  Matrix result;
  result = A.Transpose();
  ASSERT_TRUE(result == B);
}

TEST(Transpose, test_3) {
  Matrix A(2, 3);
  Matrix B(3, 2);
  A(0, 0) = 1.00;
  A(0, 1) = 2.00;
  A(0, 2) = 3.00;
  A(1, 0) = 4.00;
  A(1, 1) = 5.00;
  A(1, 2) = 6.00;
  B(0, 0) = 1.0000;
  B(0, 1) = 4.0000;
  B(1, 0) = 2.0000;
  B(1, 1) = 5.0000;
  B(2, 0) = 3.0000;
  B(2, 1) = 6.0000;
  Matrix result;
  result = A.Transpose();
  ASSERT_TRUE(result == B);
}

TEST(Transpose, test_4) {
  Matrix A(3, 3);
  Matrix B(3, 3);
  A(0, 0) = 1.00;
  A(0, 1) = 2.00;
  A(0, 2) = 3.00;
  A(1, 0) = 4.00;
  A(1, 1) = 5.00;
  A(1, 2) = 6.00;
  A(2, 0) = 7.00;
  A(2, 1) = 8.00;
  A(2, 2) = 9.00;

  B(0, 0) = 1.0000;
  B(0, 1) = 4.0000;
  B(0, 2) = 7.0000;
  B(1, 0) = 2.0000;
  B(1, 1) = 5.0000;
  B(1, 2) = 8.0000;
  B(2, 0) = 3.0000;
  B(2, 1) = 6.0000;
  B(2, 2) = 9.0000;
  Matrix result;
  result = A.Transpose();
  ASSERT_TRUE(result == B);
}

TEST(Transpose, test_5) {
  Matrix A(4, 4);
  Matrix B(4, 4);
  A(0, 0) = 1.00;
  A(0, 1) = 2.00;
  A(0, 2) = 3.00;
  A(0, 3) = 4.00;
  A(1, 0) = 0.00;
  A(1, 1) = 4.00;
  A(1, 2) = 2.00;
  A(1, 3) = 1.00;
  A(2, 0) = 5.00;
  A(2, 1) = 2.00;
  A(2, 2) = 1.00;
  A(2, 3) = 3.00;
  A(3, 0) = 3.00;
  A(3, 1) = 7.00;
  A(3, 2) = 2.00;
  A(3, 3) = 4.00;

  B(0, 0) = 1.0000;
  B(0, 1) = 0.0000;
  B(0, 2) = 5.0000;
  B(0, 3) = 3.0000;
  B(1, 0) = 2.0000;
  B(1, 1) = 4.0000;
  B(1, 2) = 2.0000;
  B(1, 3) = 7.0000;
  B(2, 0) = 3.0000;
  B(2, 1) = 2.0000;
  B(2, 2) = 1.0000;
  B(2, 3) = 2.0000;
  B(3, 0) = 4.0000;
  B(3, 1) = 1.0000;
  B(3, 2) = 3.0000;
  B(3, 3) = 4.0000;
  Matrix result;
  result = A.Transpose();
  ASSERT_TRUE(result == B);
}

TEST(Transpose_EXCEPTION, test_6) {
  Matrix A;
  Matrix result;

  try {
    result = A.Transpose();
    FAIL();
  } catch (const ExceptHandling &e) {
    // check exception
    ASSERT_STREQ("The size of the \"matrix(this)\" is zero", e.what());
  }
}

TEST(SetRows, test_1_plus_rows) {
  Matrix A(3, 7);
  A(0, 6) = 777.777;
  A(2, 6) = 9.99;
  A.SetRows(7);
  EXPECT_EQ(7, A.GetRows());
  EXPECT_EQ(777.777, A(0, 6));
  EXPECT_EQ(9.99, A(2, 6));
}

TEST(SetRows, test_2_minus_rows) {
  Matrix A(3, 7);
  A(0, 6) = 777.777;
  A.SetRows(1);
  EXPECT_EQ(1, A.GetRows());
  EXPECT_EQ(777.777, A(0, 6));
}

TEST(SetRows, test_2_zero_rows) {
  Matrix A;
  A.SetRows(8);
  EXPECT_EQ(0, A.GetRows());
}

TEST(SetCols, test_1_plus_cols) {
  Matrix A(7, 3);
  A(6, 0) = 777.777;
  A(6, 2) = 9.99;
  A.SetCols(7);
  EXPECT_EQ(7, A.GetCols());
  EXPECT_EQ(777.777, A(6, 0));
  EXPECT_EQ(9.99, A(6, 2));
}

TEST(SetCols, test_2_minus_cols) {
  Matrix A(7, 3);
  A(6, 0) = 777.777;
  A.SetCols(1);
  EXPECT_EQ(1, A.GetCols());
  EXPECT_EQ(777.777, A(6, 0));
}

TEST(SetCols, test_2_zero_cols) {
  Matrix A;
  A.SetCols(8);
  EXPECT_EQ(0, A.GetCols());
}

TEST(MultMatrix, test_1_correct) {
  Matrix A(1, 4);
  Matrix B(4, 4);
  Matrix Result(1, 4);

  A(0, 0) = 23.33;
  A(0, 1) = 12.57885;
  A(0, 2) = 5.989;
  A(0, 3) = 45.00012;

  B(0, 0) = 90.958860054;
  B(0, 1) = 49.042342768;
  B(0, 2) = 23.349876248;
  B(0, 3) = 175.446190205;
  B(1, 0) = 479.551641090;
  B(1, 1) = 915.358815407;
  B(1, 2) = 1335.999681726;
  B(1, 3) = 1339.820499679;
  B(2, 0) = 1772.263014922;
  B(2, 1) = 1688.091954926;
  B(2, 2) = 482.549813545;
  B(2, 3) = 303.622468305;
  B(3, 0) = -382.561346981;
  B(3, 1) = -23.774844775;
  B(3, 2) = -135.635138552;
  B(3, 3) = 1329.593963463;

  Result(0, 0) = 1553.055040446;
  Result(0, 1) = 21698.430942155;
  Result(0, 2) = 14136.485531609;
  Result(0, 3) = 82596.843579659;

  A.MulMatrix(B);
  ASSERT_TRUE(A.EqMatrix(Result));
  ASSERT_NEAR(Result(0, 0), A(0, 0), EPSILON);
  ASSERT_NEAR(Result(0, 1), A(0, 1), EPSILON);
  ASSERT_NEAR(Result(0, 2), A(0, 2), EPSILON);
  ASSERT_NEAR(Result(0, 3), A(0, 3), EPSILON);
}

TEST(MultMatrix, test_2_correct) {
  Matrix A(2, 3);
  Matrix B(3, 2);
  Matrix Result(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 1.0;
  A(1, 2) = 1.0;

  B(0, 0) = 4.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 1.0;
  B(2, 0) = 1.0;
  B(2, 1) = 5.0;

  Result(0, 0) = 12.0;
  Result(0, 1) = 14.0;
  Result(1, 0) = 16.0;
  Result(1, 1) = 12.0;

  A.MulMatrix(B);
  ASSERT_TRUE(A.EqMatrix(Result));
  ASSERT_NEAR(Result(0, 0), A(0, 0), EPSILON);
  ASSERT_NEAR(Result(0, 1), A(0, 1), EPSILON);
  ASSERT_NEAR(Result(1, 0), A(1, 0), EPSILON);
  ASSERT_NEAR(Result(1, 1), A(1, 1), EPSILON);
}

TEST(MultMatrix, test_3_correct_Sqr) {
  Matrix A(4, 4);
  Matrix B(4, 4);
  Matrix Result(4, 4);

  A(0, 0) = 23.33;
  A(0, 1) = 12.57885;
  A(0, 2) = 5.989;
  A(0, 3) = 45.00012;
  A(1, 0) = 123.0;
  A(1, 1) = 234.78;
  A(1, 2) = 342.67;
  A(1, 3) = 343.65;
  A(2, 0) = 454.567;
  A(2, 1) = 432.978;
  A(2, 2) = 123.769;
  A(2, 3) = 77.876;
  A(3, 0) = -98.123;
  A(3, 1) = -6.098;
  A(3, 2) = -34.789;
  A(3, 3) = 341.027;

  B(0, 0) = 90.958860054;
  B(0, 1) = 49.042342768;
  B(0, 2) = 23.349876248;
  B(0, 3) = 175.446190205;
  B(1, 0) = 479.551641090;
  B(1, 1) = 915.358815407;
  B(1, 2) = 1335.999681726;
  B(1, 3) = 1339.820499679;
  B(2, 0) = 1772.263014922;
  B(2, 1) = 1688.091954926;
  B(2, 2) = 482.549813545;
  B(2, 3) = 303.622468305;
  B(3, 0) = -382.561346981;
  B(3, 1) = -23.774844775;
  B(3, 2) = -135.635138552;
  B(3, 3) = 1329.593963463;

  Result(0, 0) = 1553.055040446;
  Result(0, 1) = 21698.430942155;
  Result(0, 2) = 14136.485531609;
  Result(0, 3) = 82596.843579659;
  Result(1, 0) = 599611.234515053;
  Result(1, 1) = 791228.395629283;
  Result(1, 2) = 435282.369298205;
  Result(1, 3) = 897100.215067985;
  Result(2, 0) = 438541.080230421;
  Result(2, 1) = 625705.223159852;
  Result(2, 2) = 638234.539213560;
  Result(2, 3) = 800987.357431217;
  Result(3, 0) = -203968.468635456;
  Result(3, 1) = -77228.934864781;
  Result(3, 2) = -73480.755824638;
  Result(3, 3) = 417479.186599506;

  A.MulMatrix(B);
  ASSERT_TRUE(A.EqMatrix(Result));
  ASSERT_NEAR(Result(0, 0), A(0, 0), EPSILON);
  ASSERT_NEAR(Result(0, 1), A(0, 1), EPSILON);
  ASSERT_NEAR(Result(0, 2), A(0, 2), EPSILON);
  ASSERT_NEAR(Result(0, 3), A(0, 3), EPSILON);
}

TEST(Determinant, test_1) {
  Matrix A(4, 4);
  Matrix B(4, 4);

  A(0, 0) = 23.33;
  A(0, 1) = 12.57885;
  A(0, 2) = 5.989;
  A(0, 3) = 45.00012;
  A(1, 0) = 123.0;
  A(1, 1) = 234.78;
  A(1, 2) = 342.67;
  A(1, 3) = 343.65;
  A(2, 0) = 454.567;
  A(2, 1) = 432.978;
  A(2, 2) = 123.769;
  A(2, 3) = 77.876;
  A(3, 0) = -98.123;
  A(3, 1) = -6.098;
  A(3, 2) = -34.789;
  A(3, 3) = 341.027;

  B(0, 0) = 90.958860054;
  B(0, 1) = 49.042342768;
  B(0, 2) = 23.349876248;
  B(0, 3) = 175.446190205;
  B(1, 0) = 479.551641090;
  B(1, 1) = 915.358815407;
  B(1, 2) = 1335.999681726;
  B(1, 3) = 1339.820499679;
  B(2, 0) = 1772.263014922;
  B(2, 1) = 1688.091954926;
  B(2, 2) = 482.549813545;
  B(2, 3) = 303.622468305;
  B(3, 0) = -382.561346981;
  B(3, 1) = -23.774844775;
  B(3, 2) = -135.635138552;
  B(3, 3) = 1329.593963463;

  EXPECT_NEAR(A.Determinant(), -1015239860.10555, 1e-04);
  EXPECT_NEAR(B.Determinant(), -234579329719.24, 1e-03);
}

TEST(Determinant, test_2) {
  Matrix A(1, 1);

  A(0, 0) = -3;
  EXPECT_NEAR(A.Determinant(), -3, EPSILON);
}

TEST(Determinant, test_3) {
  Matrix A(2, 2);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  EXPECT_NEAR(A.Determinant(), -2, EPSILON);
}

TEST(Determinant, test_4) {
  Matrix A(5, 5);
  A(0, 0) = 5;
  A(0, 1) = -5;
  A(0, 2) = 0;
  A(0, 3) = -2;
  A(0, 4) = 13;
  A(1, 0) = 9;
  A(1, 1) = 10;
  A(1, 2) = 12;
  A(1, 3) = 0;
  A(1, 4) = 1;
  A(2, 0) = 13;
  A(2, 1) = 14;
  A(2, 2) = 160;
  A(2, 3) = 5;
  A(2, 4) = 1;
  A(3, 0) = 0;
  A(3, 1) = 2;
  A(3, 2) = 0;
  A(3, 3) = 0;
  A(3, 4) = 1;
  A(4, 0) = 0;
  A(4, 1) = 0;
  A(4, 2) = 51;
  A(4, 3) = 0;
  A(4, 4) = -6;
  EXPECT_NEAR(A.Determinant(), 108153, EPSILON);
}

TEST(CalcComplements, test_1) {
  Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;

  A(1, 0) = 0.0;
  A(1, 1) = 4.0;
  A(1, 2) = 2.0;

  A(2, 0) = 5.0;
  A(2, 1) = 2.0;
  A(2, 2) = 1.0;
  Matrix B;
  B = A.CalcComplements();
  EXPECT_NEAR(B(0, 0), 0.0, EPSILON);
  EXPECT_NEAR(B(0, 1), 10.0, EPSILON);
  EXPECT_NEAR(B(0, 2), -20.0, EPSILON);

  EXPECT_NEAR(B(1, 0), 4.0, EPSILON);
  EXPECT_NEAR(B(1, 1), -14.0, EPSILON);
  EXPECT_NEAR(B(1, 2), 8.0, EPSILON);

  EXPECT_NEAR(B(2, 0), -8.0, EPSILON);
  EXPECT_NEAR(B(2, 1), -2.0, EPSILON);
  EXPECT_NEAR(B(2, 2), 4.0, EPSILON);
}

TEST(CalcComplements, test_2) {
  Matrix A(5, 5);
  A(0, 0) = -255;
  A(0, 1) = -918;
  A(0, 2) = 1683;
  A(0, 3) = 408;
  A(0, 4) = -918;

  A(1, 0) = -1354.5;
  A(1, 1) = 2214;
  A(1, 2) = 31.5;
  A(1, 3) = -1287;
  A(1, 4) = 396;

  A(2, 0) = -333;
  A(2, 1) = 801;
  A(2, 2) = -711;
  A(2, 3) = 351;
  A(2, 4) = -108;

  A(3, 0) = 6712.5;
  A(3, 1) = 1743;
  A(3, 2) = -2791.5;
  A(3, 3) = -741;
  A(3, 4) = 228;

  A(4, 0) = -13851;
  A(4, 1) = -1626;
  A(4, 2) = 9546;
  A(4, 3) = -18;
  A(4, 4) = 798;
  Matrix B(5, 5);
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(0, 2) = 3.0;
  B(0, 3) = -2.0;
  B(0, 4) = -14.5;

  B(1, 0) = -2;
  B(1, 1) = 1;
  B(1, 2) = -2;
  B(1, 3) = -11;
  B(1, 4) = -9;

  B(2, 0) = 0;
  B(2, 1) = 12.0;
  B(2, 2) = 2.0;
  B(2, 3) = 21.0;
  B(2, 4) = 1.0;

  B(3, 0) = 4.0;
  B(3, 1) = 5.0;
  B(3, 2) = 6.0;
  B(3, 3) = 7.0;
  B(3, 4) = 8.0;

  B(4, 0) = 1.0;
  B(4, 1) = 2.0;
  B(4, 2) = 3.0;
  B(4, 3) = 4.0;
  B(4, 4) = 5.0;
  Matrix C;
  C = B.CalcComplements();
  ASSERT_TRUE(A.EqMatrix(C));
}

TEST(TestDeterminant, TestDeterminantZero2) {
  Matrix matrix1{3, 3};
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_EQ(matrix1.GetRows(), 3);

  matrix1(0, 0) = 1.1;
  matrix1(0, 1) = 1.2;
  matrix1(0, 2) = 1.3;
  matrix1(1, 0) = 1.4;
  matrix1(1, 1) = 1.5;
  matrix1(1, 2) = 1.6;
  matrix1(2, 0) = 1.7;
  matrix1(2, 1) = 1.8;
  matrix1(2, 2) = 1.9;

  double result_check = 0.0;
  Matrix matrix_before = matrix1;
  double result = matrix1.Determinant();

  EXPECT_NEAR(result_check, result, EPSILON);
  EXPECT_TRUE(matrix1.EqMatrix(matrix_before));
}

// TEST (ALLOC, EXCEPTION_1) {
//     try {
//     Matrix A(2000000000,20000000);
//     Matrix B(200000000,20000000);
//     Matrix result(2000000,20000000);
//     FAIL();
//   } catch (std::bad_alloc& e) {
//     // check exception
//     ASSERT_STREQ("std::bad_alloc", e.what());
//   }
// }

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
