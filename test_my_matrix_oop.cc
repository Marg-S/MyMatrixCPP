#include <exception>

#include "gtest/gtest.h"
#include "my_matrix_oop.h"

TEST(TestCreateMatrix, Test1) {
  int rows = 1, cols = 1;
  const MyMatrix m1(rows, cols);
  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  EXPECT_EQ(m1(0, 0), 0);
}

TEST(TestCreateMatrix, Test2) {
  int rows = 1, cols = 2;
  MyMatrix m1(rows, cols);
  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  EXPECT_EQ(m1(0, 0), 0);
  EXPECT_EQ(m1(0, 1), 0);
}

TEST(TestCreateMatrix, Test3) {
  int rows = 2, cols = 1;
  MyMatrix m1(rows, cols);
  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  EXPECT_EQ(m1(0, 0), 0);
  EXPECT_EQ(m1(1, 0), 0);
}

TEST(TestCreateMatrix, Test4) {
  int rows = 100, cols = 100;
  MyMatrix m1(rows, cols);
  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), 0);
}

TEST(TestCreateMatrix, Test5) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), 0);
}

TEST(TestCreateMatrix, Test6) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  MyMatrix m2(m1);

  EXPECT_EQ(m2.GetRows(), rows);
  EXPECT_EQ(m2.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m2(i, j), 0);

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), 0);
}

TEST(TestCreateMatrix, Test7) {
  int rows = 4, cols = 5;
  MyMatrix m1(4, 5);
  MyMatrix m2(std::move(m1));

  EXPECT_EQ(m2.GetRows(), rows);
  EXPECT_EQ(m2.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m2(i, j), 0);

  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(TestCreateMatrix, Test8) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;
  MyMatrix m2(m1);

  EXPECT_EQ(m2.GetRows(), rows);
  EXPECT_EQ(m2.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m2(i, j), i * cols + j + 1);

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), i * cols + j + 1);
}

TEST(TestCreateMatrix, Test9) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;
  MyMatrix m2(std::move(m1));

  EXPECT_EQ(m2.GetRows(), rows);
  EXPECT_EQ(m2.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m2(i, j), i * cols + j + 1);

  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(TestCreateMatrix, Test10) {
  try {
    MyMatrix m1(0, 1);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestCreateMatrix, Test11) {
  try {
    MyMatrix m1(2, 0);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestCreateMatrix, Test12) {
  try {
    MyMatrix m1(-1, 1);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestCreateMatrix, Test13) {
  try {
    MyMatrix m1(1, -21);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestCreateMatrix, Test14) {
  MyMatrix m1(5, 6);
  MyMatrix m2 = m1;

  EXPECT_EQ(m2.GetRows(), 5);
  EXPECT_EQ(m2.GetCols(), 6);

  EXPECT_EQ(m1.GetRows(), 5);
  EXPECT_EQ(m1.GetCols(), 6);
}

TEST(TestCreateMatrix, Test15) {
  MyMatrix m1(5, 6);
  MyMatrix m2 = std::move(m1);

  EXPECT_EQ(m2.GetRows(), 5);
  EXPECT_EQ(m2.GetCols(), 6);

  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(TestCreateMatrix, Test16) {
  MyMatrix m1(5, 6);
  MyMatrix m2;
  m2 = m1;

  EXPECT_EQ(m2.GetRows(), 5);
  EXPECT_EQ(m2.GetCols(), 6);

  EXPECT_EQ(m1.GetRows(), 5);
  EXPECT_EQ(m1.GetCols(), 6);
}

TEST(TestCreateMatrix, Test17) {
  MyMatrix m1(5, 6);
  MyMatrix m2;
  m2 = std::move(m1);

  EXPECT_EQ(m2.GetRows(), 5);
  EXPECT_EQ(m2.GetCols(), 6);

  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(TestChangeMatrix, Test1) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);

  m1.SetRows(3);

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), i * cols + j + 1);
}

TEST(TestChangeMatrix, Test2) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);

  int new_rows = 10;
  m1.SetRows(new_rows);

  EXPECT_EQ(m1.GetRows(), new_rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), i * cols + j + 1);
  for (int i = rows; i < new_rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), 0);
}

TEST(TestChangeMatrix, Test3) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);

  int new_rows = 2;
  m1.SetRows(new_rows);

  EXPECT_EQ(m1.GetRows(), new_rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < new_rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), i * cols + j + 1);
}

TEST(TestChangeMatrix, Test4) {
  try {
    MyMatrix m1;
    m1.SetRows(0);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows value must be > 0", ex.what());
  }
}

TEST(TestChangeMatrix, Test5) {
  try {
    MyMatrix m1;
    m1.SetRows(-2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows value must be > 0", ex.what());
  }
}

TEST(TestChangeMatrix, Test6) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);

  m1.SetCols(3);

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), i * cols + j + 1);
}

TEST(TestChangeMatrix, Test7) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);

  int new_cols = 10;
  m1.SetCols(new_cols);

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), new_cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(m1(i, j), i * cols + j + 1);
  for (int i = 0; i < rows; i++)
    for (int j = cols; j < new_cols; j++) EXPECT_EQ(m1(i, j), 0);
}

TEST(TestChangeMatrix, Test8) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);

  int new_cols = 2;
  m1.SetCols(new_cols);

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), new_cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < new_cols; j++) EXPECT_EQ(m1(i, j), i * cols + j + 1);
}

TEST(TestChangeMatrix, Test9) {
  try {
    MyMatrix m1;
    m1.SetCols(0);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, cols value must be > 0", ex.what());
  }
}

TEST(TestChangeMatrix, Test10) {
  try {
    MyMatrix m1;
    m1.SetCols(-2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, cols value must be > 0", ex.what());
  }
}

TEST(TestChangeMatrix, Test11) {
  int rows = 3, cols = 3;
  MyMatrix m1;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m1(i, j) = i * cols + j + 1;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);

  m1(1, 2) = 100;

  EXPECT_EQ(m1.GetRows(), rows);
  EXPECT_EQ(m1.GetCols(), cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (i == 1 && j == 2)
        EXPECT_EQ(m1(i, j), 100);
      else
        EXPECT_EQ(m1(i, j), i * cols + j + 1);
}

TEST(TestChangeMatrix, Test12) {
  try {
    MyMatrix m1;
    m1(0, -1) = 100;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, index is out of range", ex.what());
  }
}

TEST(TestChangeMatrix, Test13) {
  try {
    MyMatrix m1;
    m1(-2, 1) = 100;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, index is out of range", ex.what());
  }
}

TEST(TestEqMatrix, Test1) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 12345.678;
  m2(0, 0) = 12345.678;

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test2) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 12345.678;
  m2(0, 0) = 123.45678;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test3) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 123.45678;
  m2(0, 0) = 12345.678;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test4) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 12345.;
  m2(0, 0) = 123.45678;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test5) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 12345.678;
  m2(0, 0) = 12345.;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test6) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 12344.;
  m2(0, 0) = 12345.;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test7) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 12345.67891;
  m2(0, 0) = 12345.6789;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test8) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 123.456788;
  m2(0, 0) = 123.456789;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test9) {
  MyMatrix m1(1, 1), m2(1, 1);
  m1(0, 0) = 12.3456788;
  m2(0, 0) = 12.3456789;

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test10) {
  MyMatrix m1(1, 1), m2(1, 2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test11) {
  MyMatrix m1(1, 1), m2(2, 1);
  EXPECT_FALSE(m1 == m2);
}

TEST(TestEqMatrix, Test12) {
  MyMatrix m1(100, 100), m2(10, 10);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test13) {
  MyMatrix m1(100, 100), m2(100, 100);
  for (int i = 0, k = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) {
      m1(i, j) = ++k;
      m2(i, j) = k;
    }

  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(TestEqMatrix, Test14) {
  MyMatrix m1(100, 100), m2(100, 100);
  for (int i = 0, k = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) {
      m1(i, j) = ++k;
      m2(i, j) = k;
    }
  m1(50, 50) = DBL_MAX;

  EXPECT_FALSE(m1 == m2);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(TestSumMatrix, Test1) {
  MyMatrix m1(4, 40), m2(4, 40), goal(4, 40);
  for (int i = 0, k = 1; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) {
      m1(i, j) = k;
      m2(i, j) = k++;
    }

  for (int i = 0, k = 2; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++, k += 2) goal(i, j) = k;

  EXPECT_TRUE((m1 + m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy += m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.SumMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestSumMatrix, Test2) {
  MyMatrix m1(1, 1), m2(1, 1), goal(1, 1);
  m1(0, 0) = 5.55;
  m2(0, 0) = 4.44;
  goal(0, 0) = 9.99;

  EXPECT_TRUE((m1 + m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy += m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.SumMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestSumMatrix, Test3) {
  try {
    MyMatrix m1(10, 10), m2(10, 11);
    m1.SumMatrix(m2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }
}

TEST(TestSumMatrix, Test4) {
  try {
    MyMatrix m1(10, 10), m2(11, 10);
    m1 + m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }
}

TEST(TestSumMatrix, Test5) {
  try {
    MyMatrix m1(10, 10), m2(11, 10);
    m1 += m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }
}

TEST(TestSubMatrix, Test1) {
  MyMatrix m1(4, 40), m2(4, 40), goal(4, 40);
  for (int i = 0, k = 1; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) {
      m1(i, j) = k;
      m2(i, j) = k++;
    }

  EXPECT_TRUE((m1 - m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy -= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.SubMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestSubMatrix, Test2) {
  MyMatrix m1(1, 1), m2(1, 1), goal(1, 1);
  m1(0, 0) = 5.55;
  m2(0, 0) = 4.44;
  goal(0, 0) = 1.11;

  EXPECT_TRUE((m1 - m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy -= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.SubMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestSubMatrix, Test3) {
  try {
    MyMatrix m1(10, 10), m2(10, 11);
    m1.SubMatrix(m2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    char str_err[] = "Incorrect input, matrices should have the same size";
    EXPECT_STREQ(str_err, ex.what());
  }
}

TEST(TestSubMatrix, Test4) {
  try {
    MyMatrix m1(10, 10), m2(9, 10);
    m1 - m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }
}

TEST(TestSubMatrix, Test5) {
  try {
    MyMatrix m1(10, 10), m2(9, 10);
    m1 -= m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }
}

TEST(TestMulMatrix, Test1) {
  MyMatrix m1(1, 1), m2(1, 1), goal(1, 1);

  m1(0, 0) = 1.25;
  m2(0, 0) = 4;
  goal(0, 0) = 5;

  EXPECT_TRUE((m1 * m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulMatrix, Test2) {
  MyMatrix m1(1, 1), m2(1, 1), goal(1, 1);

  m1(0, 0) = -10.3;
  m2(0, 0) = 30.11111;
  goal(0, 0) = -310.144433;

  EXPECT_TRUE((m1 * m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulMatrix, Test3) {
  MyMatrix m1(4, 5), m2(5, 6), goal(4, 6);

  for (int i = 0, k = 1; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = k++;

  for (int i = 0, k = 1; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) m2(i, j) = k++;

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++)
      for (int k = 0; k < m1.GetCols(); k++) goal(i, j) += m1(i, k) * m2(k, j);

  EXPECT_TRUE((m1 * m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));
  m1.MulMatrix(m2);

  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulMatrix, Test4) {
  MyMatrix m1(4, 5), m2(5, 3), goal(4, 3);

  for (int i = 0, k = 1; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = k++;

  for (int i = 0, k = 1; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) m2(i, j) = k++;

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++)
      for (int k = 0; k < m1.GetCols(); k++) goal(i, j) += m1(i, k) * m2(k, j);

  EXPECT_TRUE((m1 * m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulMatrix, Test5) {
  MyMatrix m1(4, 5), m2(5, 4), goal(4, 4);

  for (int i = 0, k = 1; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = k++;

  for (int i = 0, k = 1; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) m2(i, j) = k++;

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++)
      for (int k = 0; k < m1.GetCols(); k++) goal(i, j) += m1(i, k) * m2(k, j);

  EXPECT_TRUE((m1 * m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulMatrix, Test6) {
  MyMatrix m1(3, 2), m2(2, 4), goal(3, 4);

  double values1[3][2] = {{0, 1}, {3, 4}, {6, 7}};
  double values2[2][4] = {{9, 8, 7, 7}, {6, 5, 4, 7}};
  double goal_values[3][4] = {{6, 5, 4, 7}, {51, 44, 37, 49}, {96, 83, 70, 91}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values1[i][j];

  for (int i = 0; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) m2(i, j) = values2[i][j];

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++) goal(i, j) = goal_values[i][j];

  EXPECT_TRUE((m1 * m2).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= m2;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulMatrix(m2);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulMatrix, Test7) {
  try {
    MyMatrix m1(5, 5), m2(6, 6);
    m1.MulMatrix(m2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and number of "
        "rows of the second matrix should have the same size",
        ex.what());
  }
}

TEST(TestMulMatrix, Test8) {
  try {
    MyMatrix m1(5, 6), m2(5, 6);
    m1* m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and number of "
        "rows of the second matrix should have the same size",
        ex.what());
  }
}

TEST(TestMulMatrix, Test9) {
  try {
    MyMatrix m1(5, 6), m2(5, 6);
    m1 *= m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and number of "
        "rows of the second matrix should have the same size",
        ex.what());
  }
}

TEST(TestMulNumber, Test1) {
  MyMatrix m1(4, 40), goal(4, 40);

  for (int i = 0, k = 1; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = k++;

  int mulNumber = 3;
  for (int i = 0, k = mulNumber; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++, k += mulNumber) goal(i, j) = k;

  EXPECT_TRUE((m1 * mulNumber).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= mulNumber;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulNumber(mulNumber);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulNumber, Test2) {
  MyMatrix m1(1, 1), goal(1, 1);

  int mulNumber = -4;
  m1(0, 0) = 1.25;
  goal(0, 0) = -5;

  EXPECT_TRUE((m1 * mulNumber).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= mulNumber;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulNumber(mulNumber);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestMulNumber, Test3) {
  MyMatrix m1(3, 3), goal(3, 3);

  double k = 0.25;
  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++, k += 1) m1(i, j) = k;

  int mulNumber = 4;
  for (int i = 0, k = 1; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++, k += mulNumber) goal(i, j) = k;

  EXPECT_TRUE((m1 * mulNumber).EqMatrix(goal));

  MyMatrix m1_copy(m1);
  m1_copy *= mulNumber;
  EXPECT_TRUE(m1_copy.EqMatrix(goal));

  m1.MulNumber(mulNumber);
  EXPECT_TRUE(m1.EqMatrix(goal));
}

TEST(TestTranspose, Test1) {
  MyMatrix m1(2, 3), goal(3, 2);

  for (int i = 0, k = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) {
      m1(i, j) = ++k;
      goal(j, i) = k;
    }

  EXPECT_TRUE(goal.EqMatrix(m1.Transpose()));
}

TEST(TestTranspose, Test2) {
  MyMatrix m1(3, 3), goal(3, 3);

  double values[3][3] = {{-1, 38, -27}, {1, -41, 29}, {-1, 34, -24}};
  double goal_values[3][3] = {{-1, 1, -1}, {38, -41, 34}, {-27, 29, -24}};
  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) {
      m1(i, j) = values[i][j];
      goal(i, j) = goal_values[i][j];
    }

  EXPECT_TRUE(goal.EqMatrix(m1.Transpose()));
}

TEST(TestTranspose, Test3) {
  MyMatrix m1(1, 1), goal(1, 1);

  m1(0, 0) = 1.25;
  goal(0, 0) = 1.25;

  EXPECT_TRUE(goal.EqMatrix(m1.Transpose()));
}

TEST(TestTranspose, Test4) {
  MyMatrix m1(3, 3), goal(3, 3);

  double values[3][3] = {
      {0.25, 1.25, 2.25}, {3.25, 4.25, 5.25}, {6.25, 7.25, 8.25}};

  double goal_values[3][3] = {
      {0.25, 3.25, 6.25}, {1.25, 4.25, 7.25}, {2.25, 5.25, 8.25}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++) goal(i, j) = goal_values[i][j];

  EXPECT_TRUE(goal.EqMatrix(m1.Transpose()));
}

TEST(TestDeterminant, Test1) {
  MyMatrix m1(5, 5);

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = j;

  EXPECT_NEAR(m1.Determinant(), 0, 9e-7);
}

TEST(TestDeterminant, Test2) {
  MyMatrix m1(4, 4);

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = i + j;

  EXPECT_NEAR(m1.Determinant(), 0, 9e-7);
}

TEST(TestDeterminant, Test3) {
  MyMatrix m1(5, 5);

  double values[5][5] = {{0, 6, -2, -1, 5},
                         {0, 0, 0, -9, -7},
                         {0, 15, 35, 0, 0},
                         {0, -1, -11, -2, 1},
                         {-2, -2, 3, 0, -2}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), 2480, 9e-7);
}

TEST(TestDeterminant, Test4) {
  MyMatrix m1(3, 3);

  double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), -1., 9e-7);
}

TEST(TestDeterminant, Test5) {
  MyMatrix m1(1, 1);
  m1(0, 0) = 1.25;

  EXPECT_NEAR(m1.Determinant(), 1.25, 9e-7);
}

TEST(TestDeterminant, Test6) {
  MyMatrix m1(3, 3);

  double values[3][3] = {
      {0.25, 1.25, 2.25}, {3.25, 10, 5.25}, {6.25, 7.25, 8.25}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), -69, 9e-7);
}

TEST(TestDeterminant, Test7) {
  MyMatrix m1(3, 3);

  double values[3][3] = {{2, 4, -6}, {-5, -7, 5}, {3, 5, -6}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), -2, 9e-7);
}

TEST(TestDeterminant, Test8) {
  MyMatrix m1(3, 3);

  double values[3][3] = {{-3, 4, -6}, {2, -7, 5}, {-4, 5, -6}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), 25, 9e-7);
}

TEST(TestDeterminant, Test9) {
  MyMatrix m1(3, 3);

  double values[3][3] = {{-3, 2, -6}, {2, -5, 5}, {-4, 3, -6}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), 23, 9e-7);
}

TEST(TestDeterminant, Test10) {
  MyMatrix m1(3, 3);

  double values[3][3] = {{-3, 2, 4}, {2, -5, -7}, {-4, 3, 5}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), -8, 9e-7);
}

TEST(TestDeterminant, Test11) {
  MyMatrix m1(5, 5);

  double values[5][5] = {{0.25, 1.25, 2.25, 3.25, 2.25},
                         {3.25, 10, 5.25, 5.25, 5.25},
                         {6.25, 7.25, 8.25, 6.25, 6.25},
                         {6.25, 7.25, 8.25, 6.25, 7.25},
                         {6.25, 7.25, 8.25, 6, 8.25}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), -69.0 / 4.0, 9e-7);
}

TEST(TestDeterminant, Test12) {
  MyMatrix m1(4, 4);

  double values[4][4] = {
      {1, 2, 3, 13}, {4, 5, 6, 16}, {7, 8, 90, 19}, {1, 7, 7, 17}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  EXPECT_NEAR(m1.Determinant(), 13608, 9e-7);
}

TEST(TestDeterminant, Test13) {
  try {
    MyMatrix m1(4, 5);
    m1.Determinant();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrix is not square", ex.what());
  }
}

TEST(TestDeterminant, Test14) {
  try {
    MyMatrix m1(5, 4);
    m1.Determinant();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrix is not square", ex.what());
  }
}

TEST(TestCalcComplements, Test1) {
  MyMatrix m1(3, 3), goal(3, 3);

  double values[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double goal_values[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++) goal(i, j) = goal_values[i][j];

  EXPECT_TRUE(goal.EqMatrix(m1.CalcComplements()));
}

TEST(TestCalcComplements, Test2) {
  MyMatrix m1(3, 3), goal(3, 3);

  double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double goal_values[3][3] = {{-1, 38, -27}, {1, -41, 29}, {-1, 34, -24}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++) goal(i, j) = goal_values[i][j];

  EXPECT_TRUE(goal.EqMatrix(m1.CalcComplements()));
}

TEST(TestCalcComplements, Test3) {
  MyMatrix m1(3, 3), goal(3, 3);

  double values[3][3] = {{5, -1, 1}, {2, 3, 4}, {1, 0, 3}};
  double goal_values[3][3] = {{9, -2, -3}, {3, 14, -1}, {-7, -18, 17}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++) goal(i, j) = goal_values[i][j];

  EXPECT_TRUE(goal.EqMatrix(m1.CalcComplements()));
}

TEST(TestCalcComplements, Test4) {
  MyMatrix m1(1, 1), goal(1, 1);

  m1(0, 0) = 5;
  goal(0, 0) = 1;

  EXPECT_TRUE(goal.EqMatrix(m1.CalcComplements()));
}

TEST(TestCalcComplements, Test5) {
  try {
    MyMatrix m1(2, 3);
    m1.CalcComplements();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrix is not square", ex.what());
  }
}

TEST(TestCalcComplements, Test6) {
  try {
    MyMatrix m1(2, 1);
    m1.CalcComplements();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrix is not square", ex.what());
  }
}

TEST(TestInverseMatrix, Test1) {
  MyMatrix m1(1, 1), goal(1, 1);

  m1(0, 0) = 5;
  goal(0, 0) = 1. / 5;

  EXPECT_TRUE(goal.EqMatrix(m1.InverseMatrix()));
}

TEST(TestInverseMatrix, Test2) {
  MyMatrix m1(3, 3), goal(3, 3);

  double values[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double goal_values[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++) goal(i, j) = goal_values[i][j];

  EXPECT_TRUE(goal.EqMatrix(m1.InverseMatrix()));
}

TEST(TestInverseMatrix, Test3) {
  MyMatrix m1(3, 3), goal(3, 3);

  double values[3][3] = {{2.8, 1.3, 7.01}, {-1.03, -2.3, 3.01}, {0, -3, 2}};
  double goal_values[3][3] = {
      {44300.0 / 367429.0, -236300.0 / 367429.0, 200360.0 / 367429.0},
      {20600.0 / 367429.0, 56000.0 / 367429.0, -156483.0 / 367429.0},
      {30900.0 / 367429.0, 84000.0 / 367429.0, -51010.0 / 367429.0}};

  for (int i = 0; i < m1.GetRows(); i++)
    for (int j = 0; j < m1.GetCols(); j++) m1(i, j) = values[i][j];

  for (int i = 0; i < goal.GetRows(); i++)
    for (int j = 0; j < goal.GetCols(); j++) goal(i, j) = goal_values[i][j];

  EXPECT_TRUE(goal.EqMatrix(m1.InverseMatrix()));
}

TEST(TestInverseMatrix, Test4) {
  MyMatrix m1(1, 1), goal(1, 1);

  m1(0, 0) = 1431.12312331;
  goal(0, 0) = 1. / 1431.12312331;

  EXPECT_TRUE(goal.EqMatrix(m1.InverseMatrix()));
}

TEST(TestInverseMatrix, Test5) {
  try {
    MyMatrix m1(1, 1);
    m1.InverseMatrix();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, determinant = 0", ex.what());
  }
}

TEST(TestInverseMatrix, Test6) {
  try {
    MyMatrix m1(1, 4);
    m1.InverseMatrix();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrix is not square", ex.what());
  }
}

TEST(TestEmptyMatrix, Test1) {
  try {
    MyMatrix m1;
    MyMatrix m2(std::move(m1));
    MyMatrix m3(m1);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestEmptyMatrix, Test2) {
  MyMatrix m1(5, 6);
  MyMatrix m2 = std::move(m1);
  EXPECT_EQ(m2.GetRows(), 5);
  EXPECT_EQ(m2.GetCols(), 6);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);

  MyMatrix m3 = std::move(m1);
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m3.GetCols(), 0);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(TestEmptyMatrix, Test3) {
  int rows = 5, cols = 6, new_rows = 2, new_cols = 3;
  MyMatrix m1(rows, cols);
  MyMatrix m2 = std::move(m1);

  m1.SetRows(new_rows);
  EXPECT_EQ(m1.GetRows(), new_rows);
  EXPECT_EQ(m1.GetCols(), 0);

  m1.SetCols(new_cols);
  EXPECT_EQ(m1.GetRows(), new_rows);
  EXPECT_EQ(m1.GetCols(), new_cols);

  for (int i = 0; i < new_rows; i++)
    for (int j = 0; j < new_cols; j++) EXPECT_EQ(m1(i, j), 0);
}

TEST(TestEmptyMatrix, Test4) {
  MyMatrix m1(5, 6);
  MyMatrix m2 = std::move(m1);
  MyMatrix m3 = std::move(m1);

  EXPECT_TRUE(m3.EqMatrix(m1));  // two empty matrices
  EXPECT_FALSE(m3.EqMatrix(m2));

  EXPECT_TRUE(m1.EqMatrix(m3));
  EXPECT_FALSE(m2.EqMatrix(m3));

  EXPECT_TRUE(m3 == m1);
  EXPECT_FALSE(m3 == m2);

  EXPECT_TRUE(m1 == m3);
  EXPECT_FALSE(m2 == m3);
}

TEST(TestEmptyMatrix, Test5) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);
  MyMatrix m3 = std::move(m1);

  m3.SumMatrix(m1);  // two empty matrices
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m3.GetCols(), 0);

  try {
    m2.SumMatrix(m1);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m1.SumMatrix(m2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m3 + m1;  // two empty matrices
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }

  try {
    m2 + m1;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m1 + m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }

  m3 += m1;  // two empty matrices
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m3.GetCols(), 0);

  try {
    m2 += m1;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m1 += m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }
}

TEST(TestEmptyMatrix, Test6) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);
  MyMatrix m3 = std::move(m1);

  m3.SubMatrix(m1);  // two empty matrices
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m3.GetCols(), 0);

  try {
    m2.SubMatrix(m1);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m1.SubMatrix(m2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m3 - m1;  // two empty matrices
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }

  try {
    m2 - m1;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m1 - m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }

  m3 -= m1;  // two empty matrices
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m3.GetCols(), 0);

  try {
    m2 -= m1;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }

  try {
    m1 -= m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, matrices should have the same size",
                 ex.what());
  }
}

TEST(TestEmptyMatrix, Test7) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);
  MyMatrix m3 = std::move(m1);

  m3.MulMatrix(m1);  // two empty matrices
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m3.GetCols(), 0);

  try {
    m2.MulMatrix(m1);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and "
        "number of rows of the second matrix should have the same size",
        ex.what());
  }

  try {
    m1.MulMatrix(m2);
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and "
        "number of rows of the second matrix should have the same size",
        ex.what());
  }

  try {
    m3* m1;  // two empty matrices
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }

  try {
    m2* m1;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and "
        "number of rows of the second matrix should have the same size",
        ex.what());
  }

  try {
    m1* m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }

  m3 *= m1;  // two empty matrices
  EXPECT_EQ(m3.GetRows(), 0);
  EXPECT_EQ(m3.GetCols(), 0);

  try {
    m2 *= m1;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and "
        "number of rows of the second matrix should have the same size",
        ex.what());
  }

  try {
    m1 *= m2;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ(
        "Incorrect input, number of columns of the first matrix and "
        "number of rows of the second matrix should have the same size",
        ex.what());
  }
}

TEST(TestEmptyMatrix, Test8) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);

  double mulNumber = 2.55;
  m1.MulNumber(mulNumber);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);

  try {
    m1* mulNumber;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }

  m1 *= mulNumber;
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(TestEmptyMatrix, Test9) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);

  try {
    m1.Transpose();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestEmptyMatrix, Test10) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);

  try {
    m1.Determinant();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestEmptyMatrix, Test11) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);

  try {
    m1.CalcComplements();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestEmptyMatrix, Test12) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);

  try {
    m1.InverseMatrix();
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, rows and cols values must be > 0",
                 ex.what());
  }
}

TEST(TestEmptyMatrix, Test13) {
  MyMatrix m1;
  MyMatrix m2 = std::move(m1);

  try {
    m1(0, 0) = 1.55;
    EXPECT_EQ(0, 1);
  } catch (std::exception& ex) {
    EXPECT_STREQ("Incorrect input, index is out of range", ex.what());
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}