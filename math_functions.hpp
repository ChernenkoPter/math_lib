#include <cstdint>

namespace ml {
    struct Calculation {
        int64_t left, right;
        int64_t result;
        enum class OperationType { Add, Sub, Mul, Div, Exp, Fac } operation_type;
        enum class ErrorCode { NoError, DivByZero, Overflow, Underflow, NegativePower, NegativeFactorial } error;
    };

    inline const char* to_str(Calculation::ErrorCode& ec) {
        switch (ec) {
        case Calculation::ErrorCode::NoError:
            return "No Error";
        case Calculation::ErrorCode::DivByZero:
            return "Cannot divide bu zero";
        case Calculation::ErrorCode::Overflow:
            return "Integer overflow";
        case Calculation::ErrorCode::Underflow:
            return "Integer underflow";
        case Calculation::ErrorCode::NegativePower:
            return "Didn't implement taking roots";
        case Calculation::ErrorCode::NegativeFactorial:
            return "Cannot calculate faclotial of negative number";
        default:
            return "Unknown error";
        }
    }

    inline void calculate(Calculation& calc) {
        calc.error = Calculation::ErrorCode::NoError;
        switch (calc.operation_type) {
            case Calculation::OperationType::Add:
                if (INT64_MAX - calc.right < calc.left)
                    calc.error = Calculation::ErrorCode::Overflow;
                else
                    calc.result = calc.left + calc.right;
                break;

            case Calculation::OperationType::Sub:
                if (INT64_MIN + calc.right > calc.left)
                    calc.error = Calculation::ErrorCode::Underflow;
                else
                    calc.result = calc.left - calc.right;
                break;

            case Calculation::OperationType::Mul:
                if (INT64_MAX / calc.right < calc.left)
                    calc.error = Calculation::ErrorCode::Overflow;
                else
                    calc.result = calc.left * calc.right;
                break;

            case Calculation::OperationType::Div:
                if (calc.right == 0)
                    calc.error = Calculation::ErrorCode::DivByZero;
                else
                    calc.result = calc.left / calc.right;
                break;

            case Calculation::OperationType::Exp:
                if (calc.right < 0)
                    calc.error = Calculation::ErrorCode::NegativePower;
                else {
                    calc.result = 1;
                    while (calc.error == Calculation::ErrorCode::NoError && calc.right--) {
                        Calculation mult_calc = { calc.left, calc.result, .operation_type = Calculation::OperationType::Mul };
                        calculate(mult_calc);
                        if (mult_calc.error != Calculation::ErrorCode::NoError)
                            calc.error = mult_calc.error;
                        else
                            calc.result = mult_calc.result;
                    }
                }
                break;

            case Calculation::OperationType::Fac:
                if (calc.left < 0) {
                    calc.error = Calculation::ErrorCode::NegativeFactorial;
                    break;
                }
                if (calc.left < 2) {
                    calc.result = 1;
                    break;
                }
                Calculation fac_calc;
                fac_calc.left = calc.left - 1;
                fac_calc.operation_type = calc.operation_type;
                calculate(fac_calc);
                if (fac_calc.error != Calculation::ErrorCode::NoError) {
                    calc.error = fac_calc.error;
                    break;
                }
                Calculation mult_calc = { calc.left, fac_calc.result, .operation_type = Calculation::OperationType::Mul };
                calculate(mult_calc);
                if (mult_calc.error != Calculation::ErrorCode::NoError)
                    calc.error = mult_calc.error;
                else
                    calc.result = mult_calc.result;
                break;
        }
    }
}