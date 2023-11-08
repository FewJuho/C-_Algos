#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
namespace geometry {
class IShape;
class Point;
class Line;
class Ray;
class Segment;
class Polygon;
class Circle;

class Vector {
  friend class Point;
  friend class Line;
  friend class Ray;
  friend class Segment;
  friend class Polygon;
  friend class Circle;

  friend Vector operator+(const Vector&, const Vector&);
  friend Vector operator-(const Vector&, const Vector&);
  friend Vector operator-(const Point&, const Point&);
  friend Vector operator*(const Vector&, const int64_t&);
  friend Vector operator/(const Vector&, const int64_t&);
  friend bool operator==(const Vector&, const Vector&);

  friend double Length(const Vector&);
  friend double Sin(const Vector&, const Vector&);
  friend double Cos(const Vector&, const Vector&);
  friend double VectorProduct(const Vector&, const Vector&);
  friend double ScalarProduct(const Vector&, const Vector&);

 public:
  double x_ = 0;
  double y_ = 0;
  Vector() = default;
  Vector(const Point&, const Point&);
  Vector(const double&, const double&);
  Vector(const double&, const double_t&, const double_t&, const double_t&);

  Vector operator+() const;
  Vector operator-() const;
  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(const int64_t&);
  Vector& operator/=(const int64_t&);

  ~Vector() = default;
};

class IShape {
 public:
  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;

  virtual ~IShape() = default;
};

class Point : public IShape {
  friend class Vector;
  friend class Segment;
  friend Vector operator-(const Point&, const Point&);

 public:
  double x_ = 0;
  double y_ = 0;

  Point() = default;
  Point(const double&, const double&);

  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Point* Clone() const override;
  std::string ToString() const override;
};

class Segment : public IShape {
  friend class Point;
  friend class Line;
  friend class Ray;
  friend class Polygon;
  friend class Circle;

 public:
  Point begin_ = {0, 0};
  Point end_ = {0, 0};

  Segment() = default;
  Segment(const Point&, const Point&);
  Segment(const double&, const double&, const double&, const double&);

  Segment& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Segment* Clone() const override;
  std::string ToString() const override;

  double LengthSegment() const;
  bool IntersectSegment(const Point& begin_first, const Point& end_first, const Point& begin_second,
                        const Point& end_second) const;
  double Distance(const Point& point) const;
};

class Ray : public IShape {
  friend class Point;
  friend class Line;
  friend class Segment;
  friend class Polygon;
  friend class Circle;

 private:
  Point start_ = {0, 0};
  Vector vector_ = {0, 0};

 public:
  Ray() = default;
  Ray(const Point&, const Point&);
  Ray(const Vector&, const Point&);
  Ray(const int64_t&, const int64_t&, const int64_t&, const int64_t&);

  double Distance(const Point& point);
  Ray& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Ray* Clone() const override;
  std::string ToString() const override;
};

class Line : public IShape {

  friend class Point;
  friend class Ray;
  friend class Segment;
  friend class Polygon;
  friend class Circle;

 public:
  Point point_ = {0, 0};
  Vector vector_ = {0, 0};

  Line() = default;
  Line(const Point&, const Point&);
  Line(const Vector&, const Point&);
  Line(const double&, const double&, const double&);
  Line(const double&, const double&, const double&, const double&);

  double DistToPoint(const Point&) const;

  Line& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Line* Clone() const override;
  std::string ToString() const override;
};

class Polygon : public IShape {
  friend class Point;
  friend class Line;
  friend class Ray;
  friend class Segment;
  friend class Circle;

 private:
  std::vector<Point> n_points_;
  double size_ = n_points_.size();

 public:
  Polygon() = default;
  explicit Polygon(const std::vector<Point>&);

  Polygon& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Polygon* Clone() const override;
  std::string ToString() const override;
};

class Circle : public IShape {
  friend class Point;
  friend class Line;
  friend class Ray;
  friend class Segment;
  friend class Polygon;

 private:
  Point point_;
  double radius_ = 0;

 public:
  Circle() = default;
  Circle(const int64_t&, const int64_t&, const int64_t&);
  Circle(const Point&, const int64_t&);

  Circle& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Circle* Clone() const override;
  std::string ToString() const override;
};

Vector operator+(const Vector& first, const Vector& second) {
  return Vector{first.x_ + second.x_, first.y_ + second.y_};
}

Vector operator-(const Point& first, const Point& second) {
  return Vector{first.x_ - second.x_, first.y_ - second.y_};
}

Vector operator-(const Vector& frst, const Vector& scnd) {
  return Vector{frst.x_ - scnd.x_, frst.y_ - scnd.y_};
}

Vector operator*(const Vector& first, const int64_t& a) {
  return Vector{first.x_ * a, first.y_ * a};
}

Vector operator/(const Vector& first, const int64_t& a) {
  return Vector{first.x_ / a, first.y_ / a};
}

bool operator==(const Vector& first, const Vector& second) {
  return first.x_ == second.x_ && first.y_ == second.y_;
}

double Length(const Vector& vector) {
  return static_cast<double>(sqrt(pow(vector.x_, 2) + pow(vector.y_, 2)));
}

double Cos(const Vector& first, const Vector& second) {
  return ((ScalarProduct(first, second)) / (Length(first) * Length(second))) / 1.0;
}

double ScalarProduct(const Vector& first, const Vector& second) {
  return first.x_ * second.x_ + first.y_ * second.y_;
}

double VectorProduct(const Vector& first, const Vector& second) {
  return first.x_ * second.y_ - first.y_ * second.x_;
}

// vector (class) methods and operators
Vector::Vector(const Point& begin, const Point& end) : x_(end.x_ - begin.x_), y_(end.y_ - begin.y_) {
}

Vector::Vector(const double& x, const double& y) : x_(x), y_(y) {
}

Vector::Vector(const double& start_x, const double& start_y, const double& end_x, const double& end_y)
    : x_(end_x - start_x), y_(end_y - start_y) {
}

Vector Vector::operator+() const {
  return *this;
}

Vector Vector::operator-() const {
  return Vector(-x_, -y_);
}

Vector& Vector::operator+=(const Vector& inc_vector) {
  *this = *this + inc_vector;
  return *this;
}

Vector& Vector::operator-=(const Vector& dec_vector) {
  *this = *this - dec_vector;
  return *this;
}

Vector& Vector::operator*=(const int64_t& multiply) {
  *this = *this * multiply;
  return *this;
}

Vector& Vector::operator/=(const int64_t& multiply) {
  *this = *this / multiply;
  return *this;
}

// Point (class) methods
Point::Point(const double& x, const double& y) : x_(x), y_(y) {
}

Point& Point::Move(const Vector& vector) {
  this->x_ += vector.x_;
  this->y_ += vector.y_;
  return *this;
}

bool Point::ContainsPoint(const Point& point) const {
  return (x_ == point.x_) and (y_ == point.y_);
}

bool Point::CrossesSegment(const Segment& segment) const {
  return segment.begin_.x_ == 0;
}

Point* Point::Clone() const {
  return new Point(x_, y_);
}

std::string Point::ToString() const {
  std::string x_string = std::to_string(x_);
  std::string y_string = std::to_string(y_);
  return "Point(" + x_string + ", " + y_string + ")";
}

// Segment (class) methods
Segment::Segment(const Point& x, const Point& y) : begin_(x), end_(y) {
}

bool Segment::CrossesSegment(const Segment& segment) const {
  return segment.begin_.x_ == 0;
}

Segment& Segment::Move(const Vector& vect) {
  begin_.Move(vect);
  end_.Move(vect);
  return *this;
}

Segment* Segment::Clone() const {
  return new Segment(begin_, end_);
}

bool Segment::ContainsPoint(const Point& point) const {
  if (LengthSegment() == 0) {
    return point.ContainsPoint(end_);
  }
  Vector first{begin_, end_};
  Vector second{begin_, point};
  Vector third{end_, point};
  return Line{first, begin_}.ContainsPoint(point) && ScalarProduct(first, second) >= 0 &&
         ScalarProduct(-first, third) >= 0;
}

std::string Segment::ToString() const {
  auto str_begin_x = std::to_string(begin_.x_);
  auto str_begin_y = std::to_string(begin_.y_);
  auto str_end_x = std::to_string(end_.x_);
  auto str_end_y = std::to_string(end_.y_);
  return "Segment(Point(" + str_begin_x + ", " + str_begin_y + "), Point(" + str_end_x + ", " + str_end_y + "))";
}

double Segment::LengthSegment() const {
  return static_cast<double>(Length(Vector{begin_, end_}));
}

double Segment::Distance(const Point& point) const {
  Vector first_vector{begin_, end_};
  Vector second_vector{begin_, point};
  Vector third_vector{end_, point};
  if (ScalarProduct(first_vector, second_vector) >= 0 && ScalarProduct(-first_vector, third_vector) >= 0) {
    return Line{begin_, end_}.DistToPoint(point);
  }
  return std::min(Length(second_vector), Length(third_vector));
}

bool Segment::IntersectSegment(const Point& begin_first, const Point& end_first, const Point& begin_second,
                               const Point& end_second) const {
  Vector vector_first{begin_first, end_first};
  Vector vector_second{begin_second, end_second};

  Segment segment_first{begin_first, end_first};
  Segment segment_second{begin_second, end_second};

  auto scalar1 = VectorProduct(vector_first, Vector{begin_first, begin_second});
  auto scalar2 = VectorProduct(vector_first, Vector{begin_first, end_second});
  auto scalar3 = VectorProduct(vector_second, Vector{begin_second, begin_first});
  auto scalar4 = VectorProduct(vector_second, Vector{begin_second, end_first});

  bool check = segment_first.ContainsPoint(begin_second) || segment_first.ContainsPoint(end_second) ||
               segment_second.ContainsPoint(begin_first) || segment_second.ContainsPoint(end_first);

  return ((scalar1 * scalar2) < 0 && (scalar3 * scalar4) < 0) || check;
}

// Ray (class) methods
Ray::Ray(const Point& first, const Point& second) : start_(first), vector_({first.x_, first.y_, second.x_, second.y_}) {
}

Ray::Ray(const Vector& vector, const Point& start) : start_(start), vector_(vector) {
}

Ray& Ray::Move(const Vector& vect) {
  start_.Move(vect);
  return *this;
}

bool Ray::ContainsPoint(const Point& point) const {
  if (vector_.x_ == 0 && vector_.y_ == 0) {
    return point.ContainsPoint(start_);
  }
  return ScalarProduct(Vector{start_, point}, vector_) >= 0 && Line{vector_, start_}.ContainsPoint(point);
}
bool Ray::CrossesSegment(const Segment& segment) const {
  geometry::Line check_segment(vector_, start_);
  if (segment.LengthSegment() != 0) {
    if (start_.ContainsPoint(segment.begin_) or start_.ContainsPoint(segment.end_)) {
      return true;
    }
    if (!check_segment.CrossesSegment(segment)) {
      return false;
    }
    Vector first(start_, segment.begin_);
    Vector second(start_, segment.end_);
    auto diff_cos = Cos(first, vector_) - Cos(-second, vector_);
    return diff_cos >= 0;
  }
  return ContainsPoint(segment.begin_);
}

Ray* Ray::Clone() const {
  return new Ray(vector_, start_);
}

std::string Ray::ToString() const {
  auto str_point_x = std::to_string(start_.x_);
  auto str_point_y = std::to_string(start_.y_);
  auto str_vector_x = std::to_string(vector_.x_);
  auto str_vector_y = std::to_string(vector_.y_);

  return "Ray(Point(" + str_point_x + ", " + str_point_y + "), Vector(" + str_vector_x + ", " + str_vector_y + "))";
}

double Ray::Distance(const Point& point) {
  Vector tmp{start_, point};
  if (ScalarProduct(vector_, tmp) >= 0) {
    Line line(vector_, start_);
    return line.DistToPoint(point);
  }
  int64_t sqr1 = std::pow(point.x_ - start_.x_, 2);
  int64_t sqr2 = std::pow(point.y_ - start_.y_, 2);
  return std::sqrt(sqr1 + sqr2);
}

// Line (class) methods
Line::Line(const Point& first, const Point& second)
    : point_(first), vector_({first.x_, first.y_, second.x_, second.y_}) {
}

Line::Line(const Vector& vector, const Point& point) : point_(point), vector_(vector) {
}

Line::Line(const double& x_begin, const double& y_begin, const double& x_end, const double& y_end)
    : point_({x_begin, y_begin}), vector_({x_begin, y_begin, x_end, y_end}) {
}

double ExtGCD(int64_t a, int64_t b, double& x, double& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  double x1, y1;
  double d = ExtGCD(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

Line::Line(const double& a, const double& b, const double& c) {
  double x, y;
  auto d = geometry::ExtGCD(a, b, x, y);
  point_ = {x * -c / d, y * -c / d};
  vector_ = {b, -a};
}

double Line::DistToPoint(const Point& point) const {
  Vector vector{point_, point};
  return std::abs(VectorProduct(vector, vector_)) / Length(vector_);
}

Line& Line::Move(const Vector& vector) {
  this->point_.Move(vector);
  return *this;
}

bool Line::ContainsPoint(const Point& point) const {
  return VectorProduct(Vector{point, point_}, vector_) == 0;
}

bool Line::CrossesSegment(const Segment& segment) const {
  if (segment.LengthSegment() == 0) {
    return false;
  }
  Vector tmp1 = {point_, segment.begin_};
  Vector tmp2 = {point_, segment.end_};
  bool check1 = VectorProduct(tmp1, vector_) >= 0 && VectorProduct(tmp2, vector_) <= 0;
  bool check2 = VectorProduct(tmp2, vector_) >= 0 && VectorProduct(tmp1, vector_) <= 0;
  return (check1 or check2);
}

Line* Line::Clone() const {
  return new Line(vector_, point_);
}

std::string Line::ToString() const {
  auto a = std::to_string(vector_.y_);
  auto b = std::to_string(-vector_.x_);
  auto c = std::to_string((vector_.x_) * point_.y_ - (vector_.y_) * point_.x_);
  return "Line(" + a + ", " + b + ", " + c + ")";
}

Polygon::Polygon(const std::vector<Point>& nums) : n_points_(nums) {
}

Polygon& Polygon::Move(const Vector& vect) {
  for (auto i = 0; i < size_; i++) {
    n_points_[i].Move(vect);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
  return point.x_ == 0;
}

bool Polygon::CrossesSegment(const Segment& segment) const {
  for (auto i = 0; i < size_ - 1; i++) {
    Segment sgmnt{n_points_[i], n_points_[i + 1]};
  }
  Segment sgmnt{n_points_[size_ - 1], n_points_[0]};
  return segment.begin_.x_ == 0;
}

Polygon* Polygon::Clone() const {
  return new Polygon(n_points_);
}

std::string Polygon::ToString() const {
  std::string str_result = "Polygon(";
  for (auto i = 0; i < size_; i++) {
    str_result += ("Point(" + std::to_string(n_points_[i].x_) + ", " + std::to_string(n_points_[i].y_) + ")");
    if (i == size_ - 1) {
      str_result += ")";
    } else {
      str_result += ", ";
    }
  }
  return str_result;
}

Point CramerRule(double a1, double b1, double c1, double a2, double b2, double c2) {
  Point answer;
  answer.x_ = -(c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
  answer.y_ = -(a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
  return answer;
}
}  // namespace geometry

int main() {
  double x1, y1, x2, y2, x3, y3, x4, y4, result = 0;
  std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
  geometry::Point a = {x1, y1};
  geometry::Point b = {x2, y2};
  geometry::Point c = {x3, y3};
  geometry::Point d = {x4, y4};
  geometry::Segment segment1 = {a, b};
  geometry::Segment segment2 = {c, d};

  if (!segment1.IntersectSegment(a, b, c, d)) {
    auto dist1 = std::min(segment1.Distance(c), segment1.Distance(d));
    auto dist2 = std::min(segment2.Distance(a), segment2.Distance(b));
    result = std::min(dist1, dist2);
  }

  std::cout << std::fixed << std::setprecision(10) << result;
}