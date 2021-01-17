#pragma once

#include <vector>
#include <iostream>

class Matrix {
public:
    Matrix(int n, int m);
    Matrix(int n, int m, std::vector<double> values);
    int rows() const { return n; }
    int cols() const { return m; }
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;
    Matrix operator+() const;
    Matrix operator+(Matrix mx) const;
    Matrix operator-() const;
    Matrix operator-(Matrix mx) const;
    Matrix operator*(double s) const;
    Matrix operator*(Matrix mx) const;
    Matrix operator/(double s) const;
    Matrix transpose() const;
    static Matrix identity(int n, int m);
    static Matrix zeros(int n, int m);
    static Matrix ones(int n, int m);
    Matrix column(int j) const;
    Matrix row(int i) const;
    Matrix subMatrix(int i, int j, int subN, int subM) const;
    void setSubMatrix(int i, int j, Matrix mx);
    double maxNorm() const;
    double normL21() const;
private:
    Matrix(int n, int m, double value);
    template <typename T>
    static Matrix unaryOp(Matrix a, T op);
    template <typename T>
    static Matrix binaryOp(Matrix a, Matrix b, T op);
    int n, m;
    std::vector<double> values;
};

Matrix operator*(double s, Matrix mx);

template <typename T>
Matrix Matrix::unaryOp(Matrix mx, T op)
{
    for (auto& x : mx.values) {
        x = op(x);
    }
    return mx;
}

template <typename T>
Matrix Matrix::binaryOp(Matrix mx1, Matrix mx2, T op)
{
    assert(mx1.values.size() == mx2.values.size());
    for (int i = 0; i < mx1.values.size(); ++i) {
        mx1.values[i] = op(mx1.values[i], mx2.values[i]);
    }
    return mx1;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);