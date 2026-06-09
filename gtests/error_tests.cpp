#include "gtest/gtest.h"
#include <math_lib/math_functions.hpp>

using namespace ml;

// --- DivisionByZero ---
class DivByZeroTest : public ::testing::TestWithParam<int64_t> {};
TEST_P(DivByZeroTest, ThrowsDivisionByZero) {
    Calculation calc(GetParam(), Calculation::OperationType::Div, 0);
    ASSERT_THROW(calc.calculate(), DivisionByZero);
}
INSTANTIATE_TEST_SUITE_P(Errors, DivByZeroTest, ::testing::Values( 0, 3, -4 ));


// --- Overflow ---
struct OverflowParam {
    int64_t left;
    Calculation::OperationType op;
    int64_t right;
};

class OverflowTest : public ::testing::TestWithParam<OverflowParam> {};
TEST_P(OverflowTest, ThrowsOverflow) {
    auto [l, op, r] = GetParam();
    Calculation calc(l, op, r);
    ASSERT_THROW(calc.calculate(), Overflow);
}
INSTANTIATE_TEST_SUITE_P(Errors, OverflowTest, ::testing::Values(
    OverflowParam{INT64_MAX, Calculation::OperationType::Add, 1},
    OverflowParam{INT64_MAX, Calculation::OperationType::Sub, -1},
    OverflowParam{INT64_MAX, Calculation::OperationType::Mul, 2},
    OverflowParam{INT64_MIN, Calculation::OperationType::Mul, -2},
    OverflowParam{2, Calculation::OperationType::Exp, 63},
    OverflowParam{21, Calculation::OperationType::Fac}
));


// --- Underflow ---
struct UnderflowParam {
    int64_t left;
    Calculation::OperationType op;
    int64_t right;
};

class UnderflowTest : public ::testing::TestWithParam<UnderflowParam> {};
TEST_P(UnderflowTest, ThrowsUnderflow) {
    auto [l, op, r] = GetParam();
    Calculation calc(l, op, r);
    ASSERT_THROW(calc.calculate(), Underflow);
}
INSTANTIATE_TEST_SUITE_P(Errors, UnderflowTest, ::testing::Values(
    UnderflowParam{INT64_MIN, Calculation::OperationType::Sub, 1},
    UnderflowParam{INT64_MIN, Calculation::OperationType::Add, -1},
    UnderflowParam{INT64_MIN, Calculation::OperationType::Mul, 2},
    UnderflowParam{INT64_MAX, Calculation::OperationType::Mul, -2},
    UnderflowParam{INT32_MIN, Calculation::OperationType::Exp, 3}
));


// --- NegativePower ---
class NegativePowerTest : public ::testing::TestWithParam<int64_t> {};
TEST_P(NegativePowerTest, ThrowsNegativePower) {
    Calculation calc(2, Calculation::OperationType::Exp, GetParam());
    ASSERT_THROW(calc.calculate(), NegativePower);
}
INSTANTIATE_TEST_SUITE_P(Errors, NegativePowerTest, ::testing::Values(-1, -2, -100));


// --- NegativeFactorial ---
class NegativeFactorialTest : public ::testing::TestWithParam<int64_t> {};
TEST_P(NegativeFactorialTest, ThrowsNegativeFactorial) {
    Calculation calc(GetParam(), Calculation::OperationType::Fac, 0);
    ASSERT_THROW(calc.calculate(), NegativeFactorial);
}
INSTANTIATE_TEST_SUITE_P(Errors, NegativeFactorialTest, ::testing::Values(-1, -2, -10));
