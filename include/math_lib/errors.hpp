#pragma once
#include <exception>

class CalculationError : std::exception {
    const char *what() const noexcept override {
        return "Unknown error";
    }
};

class DivisionByZero : CalculationError {
    const char *what() const noexcept override {
        return "Cannot divide bu zero";
    }
};

class Overflow : CalculationError {
    const char *what() const noexcept override {
        return "Integer overflow";
    }
};

class Underflow : CalculationError {
    const char *what() const noexcept override {
        return "Integer underflow";
    }
};

class NegativePower : CalculationError {
    const char *what() const noexcept override {
        return "Didn't implement taking roots";
    }
};

class NegativeFactorial : CalculationError {
    const char *what() const noexcept override {
        return "Cannot calculate faclotial of negative number";
    }
};