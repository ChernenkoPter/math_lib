#include <cstdint>
#include "errors.hpp"

namespace ml {
    class Calculation {
    public:
        enum class OperationType { Add, Sub, Mul, Div, Exp, Fac };

        Calculation(int64_t left, OperationType op, int64_t right = 0)
         : left_(left), op_(op), right_(right) { }

        int64_t calculate() const;

    private:
        int64_t left_, right_;
        OperationType op_;
    };

    inline int64_t Calculation::calculate() const {
        int64_t result = 0;
        switch (op_) {
            case Calculation::OperationType::Add:
                if (right_ < 0) {
                    Calculation sub = { left_, OperationType::Sub, -right_ };
                    result = sub.calculate();
                } else if (INT64_MAX - right_ < left_) {
                    throw Overflow();
                } else {
                    result = left_ + right_;
                }
                break;

            case Calculation::OperationType::Sub:
                if (right_ < 0) {
                    Calculation add = { left_, OperationType::Add, -right_ };
                    result = add.calculate();
                } else if (INT64_MIN + right_ > left_) {
                    throw Underflow();
                } else {
                    result = left_ - right_;
                }
                break;

            case Calculation::OperationType::Mul:
                if (right_ == 0 || left_ == 0)
                    result = 0;
                else if (((right_ > 0) == (left_ > 0)) && (INT64_MAX / right_) / left_ == 0)
                    throw Overflow();
                else if (((right_ > 0) ^ (left_ > 0)) && (INT64_MIN / right_) / left_ == 0)
                    throw Underflow();
                else
                    result = left_ * right_;
                break;

            case Calculation::OperationType::Div:
                if (right_ == 0)
                    throw DivisionByZero();
                else
                    result = left_ / right_;
                break;

            case Calculation::OperationType::Exp:
                if (right_ < 0)
                    throw NegativePower();
                else {
                    result = 1;
                    for (int64_t i = 0; i < right_; ++i) {
                        Calculation mult = { left_, OperationType::Mul, result };
                        result = mult.calculate();
                    }
                }
                break;

            case Calculation::OperationType::Fac:
                if (left_ < 0) {
                    throw NegativeFactorial();
                }
                if (left_ < 2) {
                    result = 1;
                    break;
                }
                Calculation fac = { left_ - 1, OperationType::Fac };
                int64_t fac_res = fac.calculate();
                Calculation mult = { left_, OperationType::Mul, fac_res };
                result = mult.calculate();
                break;
        }
        return result;
    }
}
