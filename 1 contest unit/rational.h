#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>

#ifndef RATIONAL_H
#define RATIONAL_H
class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational;

std::ostream &operator<<(std::ostream &out, const Rational &rational_number);
std::istream &operator>>(std::istream &in, Rational &rational_number);

Rational operator+(const Rational &first_rational, const Rational &second_rational);
Rational operator-(const Rational &first_rational, const Rational &second_rational);
Rational operator*(const Rational &first_rational, const Rational &second_rational);
Rational operator/(const Rational &first_rational, const Rational &second_rational);

bool operator==(const Rational &first, const Rational &second);
bool operator!=(const Rational &first, const Rational &second);
bool operator<(const Rational &first, const Rational &second);
bool operator>(const Rational &first, const Rational &second);
bool operator<=(const Rational &first, const Rational &second);
bool operator>=(const Rational &first, const Rational &second);

class Rational {
  friend Rational operator+(const Rational &first_rational, const Rational &second_rational);
  friend Rational operator-(const Rational &first_rational, const Rational &second_rational);
  friend Rational operator*(const Rational &first_rational, const Rational &second_rational);
  friend Rational operator/(const Rational &first_rational, const Rational &second_rational);
  friend bool operator==(const Rational &first, const Rational &second);
  friend bool operator!=(const Rational &first, const Rational &second);
  friend bool operator<=(const Rational &first, const Rational &second);
  friend bool operator<(const Rational &first, const Rational &second);
  friend bool operator>(const Rational &first, const Rational &second);
  friend bool operator>=(const Rational &first, const Rational &second);
  friend std::ostream &operator<<(std::ostream &out, const Rational &rational_number);
  friend std::istream &operator>>(std::istream &in, Rational &rational_number);

 private:
  int64_t numerator_;
  size_t denominator_;

 public:
  Rational() {
    numerator_ = 0;
    denominator_ = 1;
  }

  Rational(const int64_t &x) {  // NOLINT
    numerator_ = x;
    denominator_ = 1;
  }

  Rational(const int64_t &x, const int64_t &y) {
    SetRational(x, y);
  }

  void SetRational(const int64_t &numerator, const int64_t &denominator) {
    if (denominator != 0) {
      int64_t tmp_numerator = std::abs(numerator);
      int64_t tmp_denominator = std::abs(denominator);
      int64_t gcd = std::__gcd(tmp_numerator, tmp_denominator);
      tmp_numerator /= gcd;
      tmp_denominator /= gcd;
      if (numerator * denominator == 0) {
        numerator_ = 0;
        denominator_ = 1;
      }
      if (numerator * denominator > 0) {
        numerator_ = tmp_numerator;
        denominator_ = tmp_denominator;
      }
      if (numerator * denominator < 0) {
        numerator_ = -tmp_numerator;
        denominator_ = tmp_denominator;
      }
    } else {
      throw RationalDivisionByZero{};
    }
  }

  int64_t GetNumerator() const {
    return numerator_;
  }

  size_t GetDenominator() const {
    return denominator_;
  }

  void SetNumerator(const int &x) {
    SetRational(x, denominator_);
  }

  void SetDenominator(const int &x) {
    int tmp = abs(x);
    if (x >= 0) {
      SetRational(numerator_, tmp);
    } else {
      SetRational(-numerator_, tmp);
    }
  }

  Rational operator+() const {
    Rational tmp(numerator_, denominator_);
    return tmp;
  }

  Rational operator-() const {
    Rational tmp(-numerator_, denominator_);
    return tmp;
  }

  Rational &operator=(const Rational &rational) {
    SetRational(rational.numerator_, rational.denominator_);
    return *this;
  }

  Rational &operator+=(const Rational &second_rational) {
    SetRational(numerator_ * second_rational.denominator_ + denominator_ * second_rational.numerator_,
                denominator_ * second_rational.denominator_);
    return *this;
  }

  Rational &operator-=(const Rational &second_rational) {
    SetRational(numerator_ * second_rational.denominator_ - denominator_ * second_rational.numerator_,
                denominator_ * second_rational.denominator_);
    return *this;
  }

  Rational &operator*=(const Rational &second_rational) {
    SetRational(numerator_ * second_rational.numerator_, denominator_ * second_rational.denominator_);
    return *this;
  }

  Rational &operator/=(const Rational &second_rational) {
    SetRational(numerator_ * second_rational.denominator_, denominator_ * second_rational.numerator_);
    return *this;
  }

  Rational &operator++() {
    SetRational(numerator_ + denominator_, denominator_);
    return *this;
  }

  Rational &operator--() {
    SetRational(numerator_ - denominator_, denominator_);
    return *this;
  }

  Rational operator++(int) {
    Rational tmp(numerator_, denominator_);
    SetRational(numerator_ + denominator_, denominator_);
    return tmp;
  }

  Rational operator--(int) {
    Rational tmp(numerator_, denominator_);
    SetRational(numerator_ - denominator_, denominator_);
    return tmp;
  }
};
#endif