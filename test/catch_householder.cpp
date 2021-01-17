#include <catch2/catch.hpp>

#include <iostream>
#include <random>

#include "householder.h"

using namespace std;

TEST_CASE("reflection")
{    
    const Matrix u(3, 1, {std::sqrt(0.5), std::sqrt(0.5), 0});
    const Matrix H = buildReflectionTransformation(u);
    
    const Matrix u_refl = H * u;
    REQUIRE((u_refl + u).maxNorm() < 1e-6);
    
    const Matrix v(3, 1, {-1, 2, 3});
    const Matrix v_refl = H * v;
    REQUIRE(v_refl(0, 0) == Approx(-2));
    REQUIRE(v_refl(0, 1) == Approx(1));
    REQUIRE(v_refl(0, 2) == Approx(3));
}

TEST_CASE("householder")
{
    const int n = 6;
    vector<double> values(n * n);
    
    std::mt19937 gen(42);
    std::uniform_real_distribution<> dis(-1, 1);

    for_each(begin(values), end(values), [&gen, &dis](double& x) { x = dis(gen); });
    const Matrix B(n, n, values);

    // symmetric A
    const Matrix A = B * B.transpose();
    
    const Matrix H = buildHouseholderTransformation(A);
    const Matrix T = H * A * H.transpose();
    const Matrix A_prime = H.transpose() * T * H;

    REQUIRE((A - A_prime).maxNorm() < 1e-6);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (i == j || i == j - 1 || i == j + 1) {
                continue;
            }
            CAPTURE(i, j, T(i, j));
            REQUIRE(T(i, j) > -1e-6);
            REQUIRE(T(i, j) < 1e-6);
        }
    }
}
