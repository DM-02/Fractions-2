//
//  main.cpp
//  Fractions№2
//
//  Created by Дмитрий Сергеевич on 15.02.2024.
//

#include <iostream>
#include <cmath>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    Fraction() : numerator(0), denominator(1) {}

    explicit Fraction(int num) : numerator(num), denominator(1) {}

    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        simplify();
    }

    Fraction(double value) {
        double integralPart;
        denominator = 1000000;
        numerator = static_cast<int>(value * denominator);
        simplify();
    }

    Fraction operator+(const Fraction& other) const {
        int num = (numerator * other.denominator) + (other.numerator * denominator);
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(const Fraction& other) const {
        int num = (numerator * other.denominator) - (other.numerator * denominator);
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Нельзя делить на ноль");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Fraction(num, denom);
    }

    bool operator==(const Fraction& other) const {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

    bool operator!=(const Fraction& other) const {
        return !(*this == other);
    }

    Fraction operator-() const {
        return Fraction(-numerator, denominator);
    }

    Fraction& operator++() {
        numerator += denominator;
        simplify();
        return *this;
    }

    Fraction operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }

    Fraction& operator--() {
        numerator -= denominator;
        simplify();
        return *this;
    }

    Fraction operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& frac);
    friend std::istream& operator>>(std::istream& in, Fraction& frac);

    void simplify() {
        int common = gcd(std::abs(numerator), denominator);
        numerator /= common;
        denominator /= common;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    int getIntegralPart() const {
        return numerator / denominator;
    }

    Fraction getFractionalPart() const {
        return Fraction(numerator % denominator, denominator);
    }

    Fraction getReciprocal() const {
        if (numerator == 0) {
            throw std::invalid_argument("Дробь не имеет обратной");
        }
        return Fraction(denominator, numerator);
    }

    bool isProper() const {
        return std::abs(numerator) < denominator;
    }

    bool isImproper() const {
        return std::abs(numerator) >= denominator;
    }

    bool isWhole() const {
        return std::abs(numerator) % denominator == 0;
    }

    int gcd(int a, int b) const {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }
};

std::ostream& operator<<(std::ostream& out, const Fraction& frac) {
    out << frac.numerator << "/" << frac.denominator;
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& frac) {
    char delim;
    in >> frac.numerator >> delim >> frac.denominator;
    frac.simplify();
    return in;
}

int main() {
    Fraction f1(3, 4);
    Fraction f2(5, 7);
    Fraction result = f1 + f2;
    std::cout << "Сумма: " << result << std::endl;

Fraction f3 = -f1;
    std::cout << "Отрицательное значение f1: " << f3 << std::endl;

    Fraction f4(9, 2);
    Fraction f5 = f4.getFractionalPart();
    std::cout << "Дробная часть от 9/2: " << f5 << std::endl;

    Fraction f6(5, 2);
    Fraction f7 = f6.getReciprocal();
    std::cout << "Обратная дробь к 5/2: " << f7 << std::endl;

    Fraction f8(7);
    std::cout << "Дробь из целого числа 7: " << f8 << std::endl;

    Fraction f9(0.75);
    std::cout << "Дробь из числа с плавающей точкой 0.75: " << f9 << std::endl;

    Fraction f10(4, 3);
    std::cout << "Является ли 4/3 правильной дробью? " << std::boolalpha << f10.isProper() << std::endl;

    Fraction f11(15, 4);
    std::cout << "Является ли 15/4 неправильной дробью? " << std::boolalpha << f11.isImproper() << std::endl;

    Fraction f12(9, 3);
    std::cout << "Является ли 9/3 целым числом? " << std::boolalpha << f12.isWhole() << std::endl;

    Fraction f13;
    std::cin >> f13;
    std::cout << "Введенная дробь: " << f13 << std::endl;

    return 0;
}

