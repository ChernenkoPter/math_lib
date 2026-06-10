#pragma once
#include <exception>

class CalculationError : public std::exception {
public:
    const char *what() const noexcept override {
        return "Unknown error";
    }
};

class DivisionByZero : public CalculationError {
public:
    const char *what() const noexcept override {
        return "Cannot divide bu zero";
    }
};

class Overflow : public CalculationError {
public:
    const char *what() const noexcept override {
        return "Integer overflow";
    }
};

class Underflow : public CalculationError {
public:
    const char *what() const noexcept override {
        return "Integer underflow";
    }
};

class NegativePower : public CalculationError {
public:
    const char *what() const noexcept override {
        return "Didn't implement taking roots";
    }
};

class NegativeFactorial : public CalculationError {
public:
    const char *what() const noexcept override {
        return "Cannot calculate faclotial of negative number";
    }
};