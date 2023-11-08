#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
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
  friend int64_t VectorProduct(const Vector&, const Vector&);
  friend int64_t ScalarProduct(const Vector&, const Vector&);

 public:
  int64_t x_ = 0;
  int64_t y_ = 0;
  Vector() = default;
  Vector(const Point&, const Point&);
  Vector(const int64_t&, const int64_t&);
  Vector(const int64_t&, const int64_t&, const int64_t&, const int64_t&);

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
  int64_t x_ = 0;
  int64_t y_ = 0;

  Point() = default;
  Point(const int64_t&, const int64_t&);

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

 private:
  Point begin_ = {0, 0};
  Point end_ = {0, 0};

 public:
  Segment() = default;
  Segment(const Point&, const Point&);
  Segment(const int64_t&, const int64_t&, const int64_t&, const int64_t&);

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

 private:
  Point point_ = {0, 0};
  Vector vector_ = {0, 0};

 public:
  Line() = default;
  Line(const Point&, const Point&);
  Line(const Vector&, const Point&);
  Line(const int64_t&, const int64_t&, const int64_t&);
  Line(const int64_t&, const int64_t&, const int64_t&, const int64_t&);

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
  int size_ = n_points_.size();

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

int64_t ScalarProduct(const Vector& first, const Vector& second) {
  return first.x_ * second.x_ + first.y_ * second.y_;
}

int64_t VectorProduct(const Vector& first, const Vector& second) {
  return first.x_ * second.y_ - first.y_ * second.x_;
}

// vector (class) methods and operators
Vector::Vector(const Point& begin, const Point& end) : x_(end.x_ - begin.x_), y_(end.y_ - begin.y_) {
}

Vector::Vector(const int64_t& x, const int64_t& y) : x_(x), y_(y) {
}

Vector::Vector(const int64_t& start_x, const int64_t& start_y, const int64_t& end_x, const int64_t& end_y)
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
Point::Point(const int64_t& x, const int64_t& y) : x_(x), y_(y) {
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
  return segment.ContainsPoint(*this);
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

Segment::Segment(const int64_t& start_x, const int64_t& start_y, const int64_t& end_x, const int64_t& end_y)
    : begin_({start_x, start_y}), end_({end_x, end_y}) {
}

Segment& Segment::Move(const Vector& vect) {
  begin_.Move(vect);
  end_.Move(vect);
  return *this;
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

bool Segment::CrossesSegment(const Segment& segment) const {
  if (LengthSegment() != 0 && segment.LengthSegment() == 0) {
    return ContainsPoint(segment.begin_);
  }
  if (LengthSegment() == 0 && segment.LengthSegment() == 0) {
    return segment.begin_.ContainsPoint(begin_);
  }
  if (LengthSegment() == 0 && segment.LengthSegment() != 0) {
    return segment.ContainsPoint(begin_);
  }
  return IntersectSegment(begin_, end_, segment.begin_, segment.end_);
}

Segment* Segment::Clone() const {
  return new Segment(begin_, end_);
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

bool Segment::IntersectSegment(const Point& begin_first, const Point& end_first, const Point& begin_second,
                               const Point& end_second) const {
  Vector vector_first{begin_first, end_first};
  Vector vector_second{begin_second, end_second};

  Segment segment_first{begin_first, end_first};
  Segment segment_second{begin_second, end_second};
  return false;
}

// Ray methods

Ray::Ray(const Point& first, const Point& second) : start_(first), vector_({first.x_, first.y_, second.x_, second.y_}) {
}

Ray::Ray(const Vector& vector, const Point& start) : start_(start), vector_(vector) {
}

Ray::Ray(const int64_t& start_x, const int64_t& start_y, const int64_t& end_x, const int64_t& end_y)
    : start_({start_x, start_y}), vector_({start_x, start_y, end_x, end_y}) {
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

// Line (class) methods
Line::Line(const Point& first, const Point& second)
    : point_(first), vector_({first.x_, first.y_, second.x_, second.y_}) {
}

Line::Line(const Vector& vector, const Point& point) : point_(point), vector_(vector) {
}

Line::Line(const int64_t& x_begin, const int64_t& y_begin, const int64_t& x_end, const int64_t& y_end)
    : point_({x_begin, y_begin}), vector_({x_begin, y_begin, x_end, y_end}) {
}

int64_t ExtGCD(int64_t a, int64_t b, int64_t& x, int64_t& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  int64_t x1, y1;
  int64_t d = ExtGCD(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

Line::Line(const int64_t& a, const int64_t& b, const int64_t& c) {
  int64_t x, y;
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
    return ContainsPoint(segment.begin_);
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
  auto x_max = n_points_[0].x_;
  auto count = 0;

  for (auto i = 0; i < size_; i++) {
    if (x_max <= n_points_[i].x_) {
      x_max = n_points_[i].x_;
    }
  }

  Segment segment_for_check{point.x_, point.y_, x_max + 1, point.y_ + 1};
  for (auto i = 0; i < size_ - 1; i++) {
    Segment segment{n_points_[i], n_points_[i + 1]};
    if (segment.CrossesSegment(segment_for_check)) {
      count++;
    }
    if (segment.ContainsPoint(point)) {
      return true;
    }
  }
  Segment segment{n_points_[size_ - 1], n_points_[0]};
  if (segment.CrossesSegment(segment_for_check)) {
    count++;
  }
  if (segment.ContainsPoint(point)) {
    return true;
  }
  return (count % 2 != 0);
}

bool Polygon::CrossesSegment(const Segment& segment) const {
  for (auto i = 0; i < size_ - 1; i++) {
    Segment sgmnt{n_points_[i], n_points_[i + 1]};
    if (segment.CrossesSegment(sgmnt)) {
      return true;
    }
  }
  Segment sgmnt{n_points_[size_ - 1], n_points_[0]};
  return false;
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

Circle::Circle(const int64_t& x, const int64_t& y, const int64_t& radius) : point_({x, y}), radius_(radius) {
}

Circle::Circle(const Point& point, const int64_t& radius) : point_(point), radius_(radius) {
}

Circle& Circle::Move(const Vector& vector) {
  point_.Move(vector);
  return *this;
}

bool Circle::ContainsPoint(const Point& point) const {
  auto distance = Length(Vector{point, point_});
  return distance <= radius_;
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

bool Circle::CrossesSegment(const Segment& segment) const {
  if (segment.LengthSegment() == 0) {
    return ContainsPoint(segment.begin_);
  }
  if (radius_ == 0) {
    return segment.ContainsPoint(point_);
  }
  Vector first{point_, segment.begin_};
  Vector second{point_, segment.end_};
  return segment.Distance(point_) <= radius_ && (Length(first) >= radius_ || Length(second) >= radius_);
}

Circle* Circle::Clone() const {
  return new Circle(point_, radius_);
}

std::string Circle::ToString() const {
  return "Circle(Point(" + std::to_string(point_.x_) + ", " + std::to_string(point_.y_) + "), " +
         std::to_string(static_cast<int>(radius_)) + ")";
}
}  // namespace geometry

int main() {
  int64_t a1, a2, a3, a4, b1, b2, b3, b4;
  std::cin >> a1 >> a2 >> a3 >> a4 >> b1 >> b2 >> b3 >> b4;
  geometry::Vector vector1(geometry::Point{a1, a2}, geometry::Point{a3, a4});
  geometry::Vector vector2(geometry::Point{b1, b2}, geometry::Point{b3, b4});

  std::cout << std::fixed << std::setprecision(6) << Length(vector1) << ' ' << Length(vector2) << std::endl;
  std::cout << std::fixed << std::setprecision(6) << static_cast<double>((vector1 + vector2).x_) << ' '
            << static_cast<double>((vector1 + vector2).y_) << std::endl;
  std::cout << std::fixed << std::setprecision(6) << static_cast<double>(geometry::ScalarProduct(vector1, vector2))
            << ' ' << static_cast<double>(geometry::VectorProduct(vector1, vector2)) << std::endl;
  std::cout << std::fixed << std::setprecision(6) << std::abs(geometry::VectorProduct(vector1, vector2)) / 2.0;
}
