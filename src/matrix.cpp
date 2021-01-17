#include "matrix.h"
#include <cmath>

using namespace std;

Matrix::Matrix(int n, int m, double value) : n(n), m(m), values(n * m, value)
{}

Matrix::Matrix(int n, int m) : Matrix(n, m, 0.0)
{}

Matrix::Matrix(int n, int m, std::vector<double> values)
    : n(n), m(m), values(values)
{
    assert(n * m == values.size());
}

double& Matrix::operator()(int i, int j)
{
    return const_cast<double&>(const_cast<const Matrix*>(this)->operator()(i, j));
}

const double& Matrix::operator()(int i, int j) const
{
    return values[i * m + j];
}

Matrix Matrix::operator+() const
{
    return *this;
}

Matrix Matrix::operator+(Matrix mx) const
{
    return binaryOp(*this, mx, [](double a, double b) { return a + b; });
}

Matrix Matrix::operator-() const
{
    return unaryOp(*this, [](double x) { return -x; });
}

Matrix Matrix::operator-(Matrix mx) const
{
    return binaryOp(*this, mx, [](double a, double b) { return a - b; });
}

Matrix Matrix::operator*(double s) const
{
    return unaryOp(*this, [s](double x) { return s * x; });
}

Matrix operator*(double s, Matrix mx)
{
    return mx * s;
}

Matrix Matrix::operator*(Matrix mx) const
{
    assert(m == mx.n);

    Matrix result(n, mx.m);

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < mx.m; ++k) {
            result(i, k) = 0;
            double v = 0;
            for (int j = 0; j < m; ++j) {
                result(i, k) += (*this)(i, j) * mx(j, k);
            }
        }
    }

    return result;
}

Matrix Matrix::operator/(double s) const
{
    return unaryOp(*this, [s](double x) { return x / s; });
}

Matrix Matrix::transpose() const
{
    Matrix result(m, n);
    for (int i = 0; i < result.n; ++i) {
        for (int j = 0; j < result.m; ++j) {
            result(i, j) = this->operator()(j, i);
        }
    }
    return result;
}

Matrix Matrix::identity(int n, int m)
{
    Matrix result(n, m, 0);
    const int k = min(n, m);
    for (int i = 0; i < k; ++i) {
        result(i, i) = 1;
    }
    return result;
}

Matrix Matrix::zeros(int n, int m)
{
    return Matrix(n, m, 0);
}

Matrix Matrix::ones(int n, int m)
{
    return Matrix(n, m, 1);
}

Matrix Matrix::column(int j) const
{
    assert(0 <= j && j < m);

    Matrix result(n, 1);
    for (int i = 0; i < n; ++i) {
        result(i, 0) = this->operator()(i, j);
    }
    return result;
}

Matrix Matrix::row(int i) const
{
    assert(0 <= i && i < n);

    Matrix result(1, m);
    for (int j = 0; j < m; ++j) {
        result(0, j) = this->operator()(i, j);
    }
    return result;
}

Matrix Matrix::subMatrix(int i, int j, int subN, int subM) const
{
    assert(0 <= i && (i + subN <= n));
    assert(0 <= j && (j + subM <= m));
    Matrix result(subN, subM);
    for (int k = 0; k < subN; ++k) {
        for (int l = 0; l < subM; ++l) {
            result(k, l) = this->operator()(i + k, j + l);
        }
    }
    return result;
}

void Matrix::setSubMatrix(int i, int j, Matrix mx)
{
    assert(0 <= i && (i + mx.n <= n));
    assert(0 <= j && (j + mx.m <= m));
    for (int k = 0; k < mx.n; ++k) {
        for (int l = 0; l < mx.m; ++l) {
            this->operator()(i + k, j + l) = mx(k, l);
        }
    }
}

double Matrix::maxNorm() const
{
    double r = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            r = std::max(r, std::abs(this->operator()(i, j)));
        }
    }
    return r;
}

double Matrix::normL21() const
{
    Matrix s = Matrix::zeros(1, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double c = this->operator()(i, j);
            s(0, j) += c * c;
        }
    }
    double r = 0.0;
    for (int j = 0; j < m; ++j) {
        r += std::sqrt(s(0, j));
    }
    return r;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {

    for (int i = 0; i < matrix.rows(); ++i) {
        for (int j = 0; j < matrix.cols(); ++j) {
            double k = std::abs(matrix(i, j));
            if (k < 1e-6) {
                os << 0 << "\t";
            } else {
                os << matrix(i, j) << "\t";
            }
        }
        os << "\n";
    }
    return os;
}