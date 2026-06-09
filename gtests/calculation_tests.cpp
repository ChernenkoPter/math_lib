#include "gtest/gtest.h"
#include <math_lib/math_functions.hpp>

using namespace ml;

struct BinarySuccessParam { Calculation::OperationType op; int64_t left, right, expected; };

class BinarySuccessTest : public ::testing::TestWithParam<BinarySuccessParam> {};
TEST_P(BinarySuccessTest, CalculateReturnsCorrectResult) {
    auto [op, left, right, expected] = GetParam();
    Calculation calc(left, op, right);
    ASSERT_EQ(calc.calculate(), expected);
}

INSTANTIATE_TEST_SUITE_P(BinaryOps, BinarySuccessTest, ::testing::Values(
    // Add
    BinarySuccessParam{Calculation::OperationType::Add, 2, 3, 5},
    BinarySuccessParam{Calculation::OperationType::Add, 0, 0, 0},
    BinarySuccessParam{Calculation::OperationType::Add, -1, 1, 0},
    BinarySuccessParam{Calculation::OperationType::Add, INT64_MAX, 0, INT64_MAX},
    // Sub
    BinarySuccessParam{Calculation::OperationType::Sub, 5, 3, 2},
    BinarySuccessParam{Calculation::OperationType::Sub, 0, 0, 0},
    BinarySuccessParam{Calculation::OperationType::Sub, -1, -1, 0},
    BinarySuccessParam{Calculation::OperationType::Sub, INT64_MIN, 0, INT64_MIN},
    // Mul
    BinarySuccessParam{Calculation::OperationType::Mul, 3, 4, 12},
    BinarySuccessParam{Calculation::OperationType::Mul, 0, 5, 0},
    BinarySuccessParam{Calculation::OperationType::Mul, -3, -4, 12},
    BinarySuccessParam{Calculation::OperationType::Mul, 7, -1, -7},
    // Div
    BinarySuccessParam{Calculation::OperationType::Div, 10, 2, 5},
    BinarySuccessParam{Calculation::OperationType::Div, 0, 5, 0},
    BinarySuccessParam{Calculation::OperationType::Div, -9, -3, 3},
    BinarySuccessParam{Calculation::OperationType::Div, 7, -1, -7},
    // Exp
    BinarySuccessParam{Calculation::OperationType::Exp, 2, 10, 1024},
    BinarySuccessParam{Calculation::OperationType::Exp, 5, 0, 1},
    BinarySuccessParam{Calculation::OperationType::Exp, -2, 3, -8},
    BinarySuccessParam{Calculation::OperationType::Exp, 10, 2, 100}
));

struct UnarySuccessParam {
    Calculation::OperationType op;
    int64_t left;
    int64_t expected;
};

class UnarySuccessTest : public ::testing::TestWithParam<UnarySuccessParam> {};
TEST_P(UnarySuccessTest, CalculateReturnsCorrectResult) {
    auto [op, left, expected] = GetParam();
    Calculation calc(left, op, 0);
    ASSERT_EQ(calc.calculate(), expected);
}

INSTANTIATE_TEST_SUITE_P(UnaryOps, UnarySuccessTest, ::testing::Values(
    // Fac
    UnarySuccessParam{Calculation::OperationType::Fac, 0, 1},
    UnarySuccessParam{Calculation::OperationType::Fac, 1, 1},
    UnarySuccessParam{Calculation::OperationType::Fac, 2, 2},
    UnarySuccessParam{Calculation::OperationType::Fac, 5, 120},
    UnarySuccessParam{Calculation::OperationType::Fac, 10, 3628800}
));
