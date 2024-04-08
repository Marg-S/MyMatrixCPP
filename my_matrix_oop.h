#ifndef CPP1_MY_MATRIXPLUS_SRC_MyMATRIX_OOP_H_
#define CPP1_MY_MATRIXPLUS_SRC_MyMATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <stdexcept>

class MyMatrix {
 public:
  MyMatrix();
  MyMatrix(int rows, int cols);
  MyMatrix(const MyMatrix& other);
  MyMatrix(MyMatrix&& other) noexcept;
  ~MyMatrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  MyMatrix operator+(const MyMatrix& other);
  MyMatrix operator-(const MyMatrix& other);
  MyMatrix operator*(const MyMatrix& other);
  MyMatrix operator*(const double number);
  bool operator==(const MyMatrix& other);
  MyMatrix& operator=(const MyMatrix& other);
  MyMatrix& operator=(MyMatrix&& other) noexcept;
  MyMatrix& operator+=(const MyMatrix& other);
  MyMatrix& operator-=(const MyMatrix& other);
  MyMatrix& operator*=(const MyMatrix& other);
  MyMatrix& operator*=(const double number);
  double& operator()(int i, int j) const;

  bool EqMatrix(const MyMatrix& other);
  void SumMatrix(const MyMatrix& other);
  void SubMatrix(const MyMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const MyMatrix& other);
  MyMatrix Transpose();
  MyMatrix CalcComplements();
  double Determinant();
  MyMatrix InverseMatrix();

 private:
  int rows_, cols_;
  double* matrix_;

  void GetZero(int i, int j);
  double MinorItem(int row, int col);
};

#endif  // CPP1_MY_MATRIXPLUS_SRC_MyMATRIX_OOP_H_
