#include <iostream>
#include <cstdlib>
#include "rational.h"

Rational operator+(const Rational &first_rational, const Rational &second_rational) {
  Rational temp(first_rational.numerator_ * second_rational.denominator_ +
                    first_rational.denominator_ * second_rational.numerator_,
                first_rational.denominator_ * second_rational.denominator_);
  return temp;
}

Rational operator-(const Rational &first_rational, const Rational &second_rational) {
  return first_rational + (-second_rational);
}

Rational operator*(const Rational &first_rational, const Rational &second_rational) {
  Rational tmp(first_rational.numerator_ * second_rational.numerator_,
               first_rational.denominator_ * second_rational.denominator_);
  return tmp;
}

Rational operator/(const Rational &first_rational, const Rational &second_rational) {
  Rational tmp(first_rational.numerator_ * second_rational.denominator_,
               first_rational.denominator_ * second_rational.numerator_);
  return tmp;
}

std::ostream &operator<<(std::ostream &out, const Rational &rational_number) {
  if (rational_number.denominator_ != 1) {
    out << rational_number.numerator_ << "/" << rational_number.denominator_;
  } else {
    out << rational_number.numerator_;
  }
  return out;
}

std::istream &operator>>(std::istream &in, Rational &rational_number) {
  char arr[100]{};
  char *slash;
  bool check = false;
  int64_t numerator = 0;
  int64_t denominator = 0;
  in >> arr;
  for (char i : arr) {
    if (i == '/') {
      check = true;
    }
  }
  numerator = std::strtoll(arr, &slash, 10);
  if (check) {
    denominator = std::strtoll(slash + 1, &slash, 10);
    rational_number = {numerator, denominator};
  } else {
    rational_number = numerator;
  }
  return in;
}

bool operator==(const Rational &first, const Rational &second) {
  return (first.numerator_ == second.numerator_ && first.denominator_ == second.denominator_);
}

bool operator!=(const Rational &first, const Rational &second) {
  return !(first == second);
}

bool operator<=(const Rational &first, const Rational &second) {
  int64_t left_number = first.numerator_ * second.denominator_;
  int64_t right_number = first.denominator_ * second.numerator_;
  return left_number <= right_number;
}

bool operator<(const Rational &first, const Rational &second) {
  return first <= second && first != second;
}

bool operator>=(const Rational &first, const Rational &second) {
  return !(first < second);
}

bool operator>(const Rational &first, const Rational &second) {
  return !(first <= second);
}
