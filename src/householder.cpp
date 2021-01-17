#include "householder.h"

#include <cmath>

namespace {
    Matrix householderOneStep(Matrix A)
    {
        Matrix u(A.rows(), 1);
        double b = 0.0;
        for (int i = 1; i < A.rows(); ++i) {
            b += A(i, 0) * A(i, 0);
        }
        b = std::sqrt(b);

        u(0, 0) = 0.0;
        u(1, 0) = A(1, 0) + b;
        for (int i = 2; i < A.rows(); ++i) {
            u(i, 0) = A(i, 0);
        }

        Matrix H = buildReflectionTransformation(u / u.normL21());
        return H;
    }
}

Matrix buildReflectionTransformation(Matrix u)
{
    // u norm must be 1
    assert(u.cols() == 1);
    return Matrix::identity(u.rows(), u.rows()) - 2 * u * u.transpose();
}

Matrix buildHouseholderTransformation(Matrix A)
{
    // Matrix A must be symmetric
    assert(A.rows() == A.cols());

    const int n = A.rows();
    Matrix H = Matrix::identity(n, n);
    Matrix A_k = A;

    for (int k = 0; k < n - 2; ++k) {
        Matrix H_k = householderOneStep(A_k);
        
        Matrix H_aug = Matrix::identity(n, n);
        H_aug.setSubMatrix(k, k, H_k);
        H = H_aug * H;

        Matrix T_k = H_k * A_k * H_k;
        A_k = T_k.subMatrix(1, 1, T_k.rows() - 1, T_k.rows() - 1);
    }

    return H;
}
