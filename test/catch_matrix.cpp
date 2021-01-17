#include <catch2/catch.hpp>

#include "matrix.h"

TEST_CASE("matrix addition")
{
    const Matrix m1(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix m2(2, 3, {5, 6, 7, 8, 9, 10});
    const Matrix r = m1 + m2;
    REQUIRE(r(0, 0) == 6);
    REQUIRE(r(0, 1) == 8);
    REQUIRE(r(0, 2) == 10);
    REQUIRE(r(1, 0) == 12);
    REQUIRE(r(1, 1) == 14);
    REQUIRE(r(1, 2) == 16);
}

TEST_CASE("matrix subtraction")
{
    const Matrix m1(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix m2(2, 3, {5, 6, 7, 8, 9, 10});
    const Matrix r = m1 - m2;
    REQUIRE(r(0, 0) == -4);
    REQUIRE(r(0, 1) == -4);
    REQUIRE(r(0, 2) == -4);
    REQUIRE(r(1, 0) == -4);
    REQUIRE(r(1, 1) == -4);
    REQUIRE(r(1, 2) == -4);
}

TEST_CASE("matrix unary minus")
{
    const Matrix m1(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix r = -m1;
    REQUIRE(r(0, 0) == -1);
    REQUIRE(r(0, 1) == -2);
    REQUIRE(r(0, 2) == -3);
    REQUIRE(r(1, 0) == -4);
    REQUIRE(r(1, 1) == -5);
    REQUIRE(r(1, 2) == -6);
}

TEST_CASE("matrix unary plus")
{
    const Matrix m1(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix r = +m1;
    REQUIRE(r(0, 0) == 1);
    REQUIRE(r(0, 1) == 2);
    REQUIRE(r(0, 2) == 3);
    REQUIRE(r(1, 0) == 4);
    REQUIRE(r(1, 1) == 5);
    REQUIRE(r(1, 2) == 6);
}

TEST_CASE("matrix transpose")
{
    const Matrix m1(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix r = m1.transpose();
    REQUIRE(r.rows() == m1.cols());
    REQUIRE(r.cols() == m1.rows());
    REQUIRE(r(0, 0) == 1);
    REQUIRE(r(0, 1) == 4);
    REQUIRE(r(1, 0) == 2);
    REQUIRE(r(1, 1) == 5);
    REQUIRE(r(2, 0) == 3);
    REQUIRE(r(2, 1) == 6);
}

TEST_CASE("matrix multiply by a scalar")
{
    const Matrix m1(2, 2, {1, 2, 3, 4});
    const Matrix r1 = m1 * 2;
    REQUIRE(r1(0, 0) == 2);
    REQUIRE(r1(0, 1) == 4);
    REQUIRE(r1(1, 0) == 6);
    REQUIRE(r1(1, 1) == 8);

    const Matrix r2 = 3 * m1;
    REQUIRE(r2(0, 0) == 3);
    REQUIRE(r2(0, 1) == 6);
    REQUIRE(r2(1, 0) == 9);
    REQUIRE(r2(1, 1) == 12);
}

TEST_CASE("matrix divide by a scalar")
{
    const Matrix m1(2, 2, {1, 2, 3, 4});
    const Matrix r1 = m1 / 2;
    REQUIRE(r1(0, 0) == 0.5);
    REQUIRE(r1(0, 1) == 1);
    REQUIRE(r1(1, 0) == 1.5);
    REQUIRE(r1(1, 1) == 2);
}

TEST_CASE("sq matrix multiply by a sq matrix")
{
    const Matrix m1(2, 2, {1, 2, 3, 4});
    const Matrix m2(2, 2, {5, 6, 7, 8});
    const Matrix r = m1 * m2;
    REQUIRE(r(0, 0) == 1*5+2*7);
    REQUIRE(r(0, 1) == 1*6+2*8);
    REQUIRE(r(1, 0) == 3*5+4*7);
    REQUIRE(r(1, 1) == 3*6+4*8);
}

TEST_CASE("vector multiply by a vector")
{
    const Matrix m1(2, 1, {1, 2});
    const Matrix m2(1, 2, {5, 6});
    const Matrix r1 = m1 * m2;
    REQUIRE(r1.rows() == 2);
    REQUIRE(r1.cols() == 2);
    REQUIRE(r1(0, 0) == 5);
    REQUIRE(r1(0, 1) == 6);
    REQUIRE(r1(1, 0) == 10);
    REQUIRE(r1(1, 1) == 12);

    const Matrix r2 = m2 * m1;
    REQUIRE(r2.rows() == 1);
    REQUIRE(r2.cols() == 1);
    REQUIRE(r2(0, 0) == 1*5+2*6);
}

TEST_CASE("identity matrix")
{
    const Matrix mx = Matrix::identity(2, 3);
    REQUIRE(mx(0, 0) == 1);
    REQUIRE(mx(0, 1) == 0);
    REQUIRE(mx(0, 2) == 0);
    REQUIRE(mx(1, 0) == 0);
    REQUIRE(mx(1, 1) == 1);
    REQUIRE(mx(1, 2) == 0);
}

TEST_CASE("zeros matrix")
{
    const Matrix mx = Matrix::zeros(2, 3);
    REQUIRE(mx(0, 0) == 0);
    REQUIRE(mx(0, 1) == 0);
    REQUIRE(mx(0, 2) == 0);
    REQUIRE(mx(1, 0) == 0);
    REQUIRE(mx(1, 1) == 0);
    REQUIRE(mx(1, 2) == 0);
}

TEST_CASE("ones matrix")
{
    const Matrix mx = Matrix::ones(2, 3);
    REQUIRE(mx(0, 0) == 1);
    REQUIRE(mx(0, 1) == 1);
    REQUIRE(mx(0, 2) == 1);
    REQUIRE(mx(1, 0) == 1);
    REQUIRE(mx(1, 1) == 1);
    REQUIRE(mx(1, 2) == 1);
}

TEST_CASE("matrix column")
{
    const Matrix mx = Matrix(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix col = mx.column(1);
    REQUIRE(col.rows() == 2);
    REQUIRE(col.cols() == 1);
    REQUIRE(col(0, 0) == 2);
    REQUIRE(col(1, 0) == 5);
}

TEST_CASE("matrix row")
{
    const Matrix mx = Matrix(2, 3, {1, 2, 3, 4, 5, 6});
    const Matrix row = mx.row(1);
    REQUIRE(row.rows() == 1);
    REQUIRE(row.cols() == 3);
    REQUIRE(row(0, 0) == 4);
    REQUIRE(row(0, 1) == 5);
    REQUIRE(row(0, 2) == 6);
}

TEST_CASE("get sub-matrix 1")
{
    const Matrix mx = Matrix(3, 4, {1, 2, 3, 4,
                                    5, 6, 7, 8,
                                    9, 10, 11, 12});
    const Matrix sub = mx.subMatrix(1, 1, 2, 3);
    REQUIRE(sub.rows() == 2);
    REQUIRE(sub.cols() == 3);
    REQUIRE(sub(0, 0) == 6);
    REQUIRE(sub(0, 1) == 7);
    REQUIRE(sub(0, 2) == 8);
    REQUIRE(sub(1, 0) == 10);
    REQUIRE(sub(1, 1) == 11);
    REQUIRE(sub(1, 2) == 12);
}

TEST_CASE("get sub-matrix 2")
{
    const Matrix mx = Matrix(3, 4, {1, 2, 3, 4,
                                    5, 6, 7, 8,
                                    9, 10, 11, 12});
    const Matrix sub = mx.subMatrix(0, 0, 2, 2);
    REQUIRE(sub.rows() == 2);
    REQUIRE(sub.cols() == 2);
    REQUIRE(sub(0, 0) == 1);
    REQUIRE(sub(0, 1) == 2);
    REQUIRE(sub(1, 0) == 5);
    REQUIRE(sub(1, 1) == 6);
}

TEST_CASE("set sub-matrix 1")
{
    Matrix mx = Matrix(3, 4, {1, 2, 3, 4,
                              5, 0, 0, 0,
                              9, 0, 0, 0});
    const Matrix sub = Matrix(2, 3, {6, 7, 8, 10, 11, 12});
    mx.setSubMatrix(1, 1, sub);
    REQUIRE(mx.rows() == 3);
    REQUIRE(mx.cols() == 4);
    REQUIRE(mx(0, 1) == 2);
    REQUIRE(mx(0, 2) == 3);
    REQUIRE(mx(0, 3) == 4);
    REQUIRE(mx(1, 0) == 5);
    REQUIRE(mx(0, 0) == 1);
    REQUIRE(mx(1, 1) == 6);
    REQUIRE(mx(1, 2) == 7);
    REQUIRE(mx(1, 3) == 8);
    REQUIRE(mx(2, 0) == 9);
    REQUIRE(mx(2, 1) == 10);
    REQUIRE(mx(2, 2) == 11);
    REQUIRE(mx(2, 3) == 12);
}

TEST_CASE("set sub-matrix 2")
{
    Matrix mx = Matrix(3, 4, {0, 0, 3, 4,
                              0, 0, 7, 8,
                              9, 10, 11, 12});
    const Matrix sub = Matrix(2, 2, {1, 2, 5, 6});
    mx.setSubMatrix(0, 0, sub);
    REQUIRE(mx.rows() == 3);
    REQUIRE(mx.cols() == 4);
    REQUIRE(mx(0, 0) == 1);
    REQUIRE(mx(0, 1) == 2);
    REQUIRE(mx(1, 0) == 5);
    REQUIRE(mx(1, 1) == 6);
}

TEST_CASE("matrix maxNorm")
{
    const Matrix m1(2, 2, {1, 2, 3, -4});
    REQUIRE(m1.maxNorm() == 4);
}

TEST_CASE("matrix normL21")
{
    const Matrix m1(2, 2, {1, 2, 3, -4});
    REQUIRE(m1.normL21() == Approx(std::sqrt(1*1 + 3*3) + std::sqrt(2*2 + -4*-4)));
}
