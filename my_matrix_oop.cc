#include "my_matrix_oop.h"

MyMatrix::MyMatrix() : MyMatrix(3, 3) {}

MyMatrix::MyMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::out_of_range(
        "Incorrect input, rows and cols values must be > 0");
  matrix_ = new double[rows_ * cols_]();
}

MyMatrix::MyMatrix(const MyMatrix& other) : MyMatrix(other.rows_, other.cols_) {
  memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
}

MyMatrix::MyMatrix(MyMatrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

MyMatrix::~MyMatrix() {
  if (matrix_) delete[] matrix_;
}

int MyMatrix::GetRows() const { return rows_; }

int MyMatrix::GetCols() const { return cols_; }

void MyMatrix::SetRows(int rows) {
  if (rows <= 0)
    throw std::out_of_range("Incorrect input, rows value must be > 0");
  if (rows == rows_) return;

  double* matrix_old = matrix_;
  int min_rows = rows < rows_ ? rows : rows_;

  matrix_ = new double[rows * cols_]();
  memcpy(matrix_, matrix_old, min_rows * cols_ * sizeof(double));
  rows_ = rows;
  delete[] matrix_old;
}

void MyMatrix::SetCols(int cols) {
  if (cols == cols_) return;
  if (cols <= 0)
    throw std::out_of_range("Incorrect input, cols value must be > 0");

  double* matrix_old = matrix_;
  int min_cols = cols < cols_ ? cols : cols_;
  matrix_ = new double[rows_ * cols]();
  for (int i = 0; i < rows_; i++) {
    double* dest = matrix_ + i * cols;
    double* src = matrix_old + i * cols_;
    memcpy(dest, src, min_cols * sizeof(double));
  }
  cols_ = cols;
  delete[] matrix_old;
}

bool MyMatrix::EqMatrix(const MyMatrix& other) {
  if (this == &other) return true;
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (int i = 0; i < other.rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      if (fabs((*this)(i, j) - other(i, j)) > 9e-7) return false;

  return true;
}

void MyMatrix::SumMatrix(const MyMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) += other(i, j);
}

void MyMatrix::SubMatrix(const MyMatrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) -= other(i, j);
}

void MyMatrix::MulMatrix(const MyMatrix& other) {
  if (cols_ != other.rows_)
    throw std::out_of_range(
        "Incorrect input, number of columns of the first matrix and "
        "number of rows of the second matrix should have the same size");

  double* matrix_new = new double[rows_ * other.cols_]();

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < cols_; k++)
        matrix_new[i * other.cols_ + j] += (*this)(i, k) * other(k, j);

  delete[] matrix_;
  matrix_ = matrix_new;
  cols_ = other.cols_;
}

void MyMatrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) (*this)(i, j) *= num;
}

MyMatrix MyMatrix::Transpose() {
  MyMatrix result(cols_, rows_);

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result(j, i) = (*this)(i, j);

  return result;
}

void MyMatrix::GetZero(int i, int j) {
  if ((*this)(j, j) == 0) {
    for (int k = 0; k < cols_; k++) {
      double buf = (*this)(j, k);
      (*this)(j, k) = (*this)(i, k);
      (*this)(i, k) = -buf;
    }
  } else {
    double mult = (*this)(i, j) / (*this)(j, j);
    for (int k = 0; k < cols_; k++) (*this)(i, k) -= mult * (*this)(j, k);
  }
}

double MyMatrix::Determinant() {
  if (rows_ != cols_)
    throw std::out_of_range("Incorrect input, matrix is not square");

  MyMatrix temp(*this);
  for (int j = 0; j < temp.cols_ - 1; j++)
    for (int i = j + 1; i < temp.rows_; i++)
      if (temp(i, j) != 0) temp.GetZero(i, j);

  double det = 1;
  for (int i = 0; i < temp.rows_; i++) det *= temp(i, i);

  return det;
}

double MyMatrix::MinorItem(int row, int col) {
  double result;

  MyMatrix temp(*this);
  temp.SetRows(temp.GetRows() - 1);
  temp.SetCols(temp.GetCols() - 1);

  for (int i = 0, x = 0; i < rows_; i++)
    if (i != row) {
      for (int j = 0, y = 0; j < cols_; j++)
        if (j != col) temp(x, y++) = (*this)(i, j);
      x++;
    }

  result = temp.Determinant();

  return result;
}

MyMatrix MyMatrix::CalcComplements() {
  if (rows_ != cols_)
    throw std::out_of_range("Incorrect input, matrix is not square");

  MyMatrix result(rows_, cols_);

  if (rows_ == 1)
    result(0, 0) = 1;
  else
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        result(i, j) = MinorItem(i, j) * pow(-1, i + j);

  return result;
}

MyMatrix MyMatrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) throw std::out_of_range("Incorrect input, determinant = 0");

  return CalcComplements().Transpose() * (1. / det);
}

MyMatrix MyMatrix::operator+(const MyMatrix& other) {
  MyMatrix result(*this);
  result.SumMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator-(const MyMatrix& other) {
  MyMatrix result(*this);
  result.SubMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator*(const MyMatrix& other) {
  MyMatrix result(*this);
  result.MulMatrix(other);
  return result;
}

MyMatrix MyMatrix::operator*(const double number) {
  MyMatrix result(*this);
  result.MulNumber(number);
  return result;
}

bool MyMatrix::operator==(const MyMatrix& other) { return EqMatrix(other); }

MyMatrix& MyMatrix::operator=(const MyMatrix& other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;

    delete[] matrix_;
    matrix_ = new double[rows_ * cols_]();
    memcpy(matrix_, other.matrix_, rows_ * cols_ * sizeof(double));
  }

  return *this;
}

MyMatrix& MyMatrix::operator=(MyMatrix&& other) noexcept {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;

    delete[] matrix_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

  return *this;
}

MyMatrix& MyMatrix::operator+=(const MyMatrix& other) {
  SumMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator-=(const MyMatrix& other) {
  SubMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const MyMatrix& other) {
  MulMatrix(other);
  return *this;
}

MyMatrix& MyMatrix::operator*=(const double number) {
  MulNumber(number);
  return *this;
}

double& MyMatrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[i * cols_ + j];
}
