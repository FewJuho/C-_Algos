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

class Vector {
  friend class Point;
  friend class Line;
  friend class Ray;
  friend class Segment;
  friend class Polygon;

  friend Vector operator+(const Vector&, const Vector&);
  friend Vector operator-(const Vector&, const Vector&);
  friend Vector operator-(const Point&, const Point&);
  friend Vector operator*(const Vector&, const int64_t&);
  friend Vector operator/(const Vector&, const int64_t&);
  friend bool operator==(const Vector&, const Vector&);

  friend double Length(const Vector&);
  friend int64_t Cos(const Vector&, const Vector&);
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
  static int64_t x_start;
  static int64_t y_start;
  bool HullContains = false;

  Point() = default;
  Point(const int64_t&, const int64_t&);

  Point& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Point* Clone() const override;
  std::string ToString() const override;
};

int64_t Point::x_start = 0;
int64_t Point::y_start = 0;

class Segment : public IShape {
  friend class Point;
  friend class Line;
  friend class Ray;
  friend class Polygon;

 public:
  Point begin_ = {0, 0};
  Point end_ = {0, 0};

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

 private:
  Point start_ = {0, 0};
  Vector vector_ = {0, 0};

 public:
  Ray() = default;
  Ray(const Point&, const Point&);
  Ray(const Vector&, const Point&);

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

 public:
  Point point_ = {0, 0};
  Vector vector_ = {0, 0};

  Line() = default;
  Line(const Point&, const Point&);
  Line(const Vector&, Point);
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

 public:
  std::vector<Point> n_points_;
  int64_t size_ = 0;
  Polygon() = default;
  explicit Polygon(std::vector<Point>);

  Polygon& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  Polygon* Clone() const override;
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

int64_t Cos(const Vector& first, const Vector& second) {
  return ((ScalarProduct(first, second)) / (Length(first) * Length(second)));
}

int64_t ScalarProduct(const Vector& first, const Vector& second) {
  return first.x_ * second.x_ + first.y_ * second.y_;
}

int64_t VectorProduct(const Vector& first, const Vector& second) {
  return first.x_ * second.y_ - first.y_ * second.x_;
}

bool operator<(const Point& a, const Point& b) {
  return (a.x_ < b.x_) or (a.x_ == b.x_ && a.y_ < b.y_);
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

Line::Line(const Vector& vector, Point point) : point_(std::move(point)), vector_(vector) {
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

Polygon::Polygon(std::vector<Point> nums) : n_points_(std::move(nums)) {
}

Polygon& Polygon::Move(const Vector& vect) {
  for (auto i = 0; i < size_; ++i) {
    n_points_[i].Move(vect);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& point) const {
  auto x_max = n_points_[0].x_;
  auto count = 0;
  int64_t size = n_points_.size();

  for (int i = 0; i < size; ++i) {
    if (x_max <= n_points_[i].x_) {
      x_max = n_points_[i].x_;
    }
  }
  Segment segment_for_check{point.x_, point.y_, x_max + 1, point.y_ + 1};
  for (int i = 0; i < size - 1; ++i) {
    Segment segment{n_points_[i], n_points_[i + 1]};
    if (segment.CrossesSegment(segment_for_check)) {
      count++;
    }
    if (segment.ContainsPoint(point)) {
      return true;
    }
  }
  Segment segment{n_points_[size - 1], n_points_[0]};
  if (segment.CrossesSegment(segment_for_check)) {
    count++;
  }
  if (segment.ContainsPoint(point)) {
    return true;
  }
  return (count % 2 != 0);
}

bool Polygon::CrossesSegment(const Segment& segment) const {
  for (auto i = 0; i < size_ - 1; ++i) {
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
  for (auto i = 0; i < size_; ++i) {
    str_result += ("Point(" + std::to_string(n_points_[i].x_) + ", " + std::to_string(n_points_[i].y_) + ")");
    if (i == size_ - 1) {
      str_result += ")";
    } else {
      str_result += ", ";
    }
  }
  return str_result;
}

Segment::Segment(const int64_t& begin_x, const int64_t& begin_y, const int64_t& end_x, const int64_t& end_y)
    : begin_({begin_x, begin_y}), end_({end_x, end_y}) {
}

int64_t S(std::vector<Point> shape) {
  int64_t result = 0;
  for (size_t i = 0; i < shape.size(); ++i) {
    if (i == shape.size() - 1) {
      result += (shape[i].y_ + shape[0].y_) * (shape[0].x_ - shape[i].x_);
    } else {
      result += (shape[i].y_ + shape[i + 1].y_) * (shape[i + 1].x_ - shape[i].x_);
    }
  }
  return result;
}

bool operator==(const Point& a, const Point& b) {
  return (a.x_ == b.x_) && (a.y_ == b.y_);
}

bool operator!=(const Point& a, const Point& b) {
  return !(a == b);
}

double ValueAngle(const Point a, const Point b, const Point c) {
  double first = std::sqrt((a.x_ - b.x_) * (a.x_ - b.x_) + (a.y_ - b.y_) * (a.y_ - b.y_));
  double second = std::sqrt((b.x_ - c.x_) * (b.x_ - c.x_) + (b.y_ - c.y_) * (b.y_ - c.y_));
  double length = first * second;
  return ((b.x_ - a.x_) * (c.x_ - b.x_) + (b.y_ - a.y_) * (c.y_ - b.y_)) / length;
}

bool Cmp(const Point& a, const Point& b);

auto VectorProduct(const Point& a, const Point& b, const Point& c) {
  return (b.x_ - a.x_) * (c.y_ - b.y_) - (c.x_ - b.x_) * (b.y_ - a.y_);
}

void ConvexHull(std::vector<Point> polygon) {
  size_t size = polygon.size();
  Point start_point = polygon[0];
  double max_angle = 10e10;
  int position = 0;
  for (auto i = 0ull; i < polygon.size(); ++i) {
    if (polygon[i].x_ < start_point.x_ || (polygon[i].x_ == start_point.x_ && polygon[i].y_ < start_point.y_)) {
      start_point = polygon[i];
    }
  }

  std::vector<Point> hull = {start_point};
  Point min_point = start_point;

  for (size_t i = 0; i < size; ++i) {
    if (polygon[i] != start_point &&
        atan2(polygon[i].y_ - start_point.y_, polygon[i].x_ - start_point.x_) < max_angle) {
      min_point = polygon[i];
      max_angle = atan2(min_point.y_ - start_point.y_, min_point.x_ - start_point.x_);
      position = i;
    }
  }

  polygon[position].HullContains = true;
  hull.push_back(min_point);

  for (auto i = 1;; ++i) {
    double value = -1000;
    for (size_t j = 0; j < size; ++j) {
      if (!polygon[j].HullContains && ValueAngle(hull[i - 1], hull[i], polygon[j]) > value) {
        min_point = polygon[j];
        value = ValueAngle(hull[i - 1], hull[i], polygon[j]);
        position = j;
      }
    }
    if (min_point == start_point) {
      break;
    }
    polygon[position].HullContains = true;
    hull.push_back(min_point);
  }

  std::vector<Point> new_hull;
  new_hull.resize(hull.size());
  new_hull[0] = hull[0];
  for (size_t i = 1; i < new_hull.size(); ++i) {
    new_hull[i] = hull[hull.size() - i];
  }

  geometry::Vector first;
  geometry::Vector second;

  for (size_t i = 0; i < new_hull.size() - 2; ++i) {
    first = {new_hull[i], new_hull[i + 1]};
    second = {new_hull[i + 1], new_hull[i + 2]};
    if (VectorProduct(first, second) == 0) {
      for (size_t j = i + 1; j < new_hull.size() - 1; j++) {
        std::swap(new_hull[j], new_hull[j + 1]);
      }
      new_hull.pop_back();
      i -= 1;
    }
  }
  first = {new_hull[new_hull.size() - 2], new_hull[new_hull.size() - 1]};
  second = {new_hull[new_hull.size() - 1], new_hull[0]};
  while (VectorProduct(first, second) == 0) {
    new_hull.pop_back();
    first = {new_hull[new_hull.size() - 2], new_hull[new_hull.size() - 1]};
    second = {new_hull[new_hull.size() - 1], new_hull[0]};
  }
  std::cout << new_hull.size() << "\n";
  for (auto& i : new_hull) {
    std::cout << i.x_ << ' ' << i.y_ << "\n";
  }

  int64_t s = std::abs(S(new_hull));
  if (s % 2 == 0) {
    std::cout << s / 2 << ".0";
  } else {
    std::cout << s / 2 << ".5";
  }
}

bool Cmp(const Point& a, const Point& b) {
  bool result = false;
  Point start{geometry::Point::x_start, geometry::Point::y_start};
  Vector first{start, a};
  Vector second{start, b};
  if (VectorProduct(first, second) < 0) {
    result = true;
  } else if (VectorProduct(first, second) == 0) {
    result = Length(first) < Length(second);
  }
  return result;
}

}  // namespace geometry

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int64_t n;
  int64_t a, b;

  std::cin >> n;
  geometry::Point point{a, b};
  std::vector<geometry::Point> polygon;
  std::vector<geometry::Vector> vector;
  polygon.reserve(n);

  for (int i = 0; i < n; ++i) {
    int64_t x, y;
    std::cin >> x >> y;
    polygon.emplace_back(geometry::Point(x, y));
  }
  geometry::Polygon shape{polygon};
  shape.size_ = n;
  geometry::ConvexHull(polygon);
}
