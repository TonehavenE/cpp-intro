#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <array>

int add(const int x, const int y);
int subtract(const int x, const int y);
int multiply(const int x, const int y);
int divide(const int x, const int y);

class Line;
class Point;
class Triangle;
class Polygon;

class Circle {
  public:
    int radius;
    double area() {
      return M_PI * std::pow(radius, 2);
    }
};

class Point {
  public:
    double x;
    double y;
    Point() {}
    Point(double x, double y) {
      this->x = x;
      this->y = y;
    }
    double distance_to_origin() {
      return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }
    double distance_to_point(Point p) {
      return std::abs(std::sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2)));
    }
};

class Line {
  public:
    Point p1;
    Point p2;
    Line(Point p1, Point p2) {
      this->p1 = p1;
      this->p2 = p2;
    }
    double length() {
      return p1.distance_to_point(p2);
    }
    double distance_to_point(Point &p) {
      double numerator = std::abs((p2.x - p1.x) * (p1.y - p.y) - (p1.x - p.x) * (p2.y - p1.y));
      return (numerator / this->length());    
    }
 };

class Triangle {
  public:
    Point p1;
    Point p2;
    Point p3;
    Triangle(Point p1, Point p2, Point p3) {
      this->p1 = p1;
      this->p2 = p2;
      this->p3 = p3;
    }
    double area() {
      // Switch to Heron's Formula!
      return 0.5 * std::abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)));;
    }
};

class Polygon {
  /*
  Polygon must be convex. 
  */
  public:
    std::vector<Point> points;
    Polygon(std::vector<Point> points) {
      this->points = points;
    }
    double area() {
      double area = 0.0;
      for (int i = 1; i < points.size() - 1; i++) {
        Triangle t = Triangle(points[0], points[i], points[i + 1]);
        area += t.area();
      }
      return area;
    }
    double perimeter() {
      int n = points.size();
      double perimeter = 0.0;
      for (int i = 0; i < n - 1; i++) {
        perimeter += points[i].distance_to_point(points[i + 1]);
      }
      perimeter += points[0].distance_to_point(points[n - 1]);
      return perimeter;
    }
};

class AUV {
  public:
    std::string name;
    Point position;
    double depth;
    double heading;
    std::array<double, 3> speed;
    double angular_speed;
    AUV(std::string name, Point position, double depth, double heading, std::array<double, 3> speed, double angular_speed) {
      this->name = name;
      this->position = position;
      this->depth = depth;
      this->heading = heading;
      this->speed = speed;
      this->angular_speed = angular_speed;
    }
    void step(const double time_step) {
      heading += angular_speed * time_step;
      position.x += speed[0] * time_step;
      position.y += speed[1] * time_step;
      depth += speed[2] * time_step; 
    }

    void apply_acceleration(std::array<double, 3> accel_array, const double time_step) {
      speed[0] += accel_array[0] * time_step;
      speed[1] += accel_array[1] * time_step;
      speed[2] += accel_array[2] * time_step;
    }

    void apply_angular_acceleration(const double angular_acceleration, const double time_step) {
      angular_speed += angular_acceleration * time_step;
    }
};
int main()
{
  // Adding, subtracting, multiplying, dividing
  std::cout << "Eben Quenneville" << std::endl;
  std::cout << "Classroom 24-115" << std::endl;

  int x = 5;
  int y = 7;

  int z = add(x, y);
  std::cout << "The sum of " << x << " and " << y << " is " << z << std::endl;

  int w = multiply(multiply(x, y), z);
  std::cout << "The product of " << x << " and " << y << " and " << z << " is " << w << std::endl;

  int v = divide(x, y);
  std::cout << "The division of " << x << " and " << y << " is " << v << std::endl;

  int u = subtract(w, z);
  std::cout << "The difference between " << w << " and " << z << " is " << u << std::endl;

  // Circle Class Testing
  Circle c;
  c.radius = 10.0;
  std::cout << "The radius of a circle with radius 10.0 is " << c.area() << std::endl;

  // Point Class Testing
  Point o = Point(0, 0); // o = origin
  Point p1 = Point(1, 1);
  Point p2 = Point(2, 2);
  Point p3 = Point(0, 3);
  Point p4 = Point(0, 1);
  std::cout << "The distance to the origin from point (1, 1) is " << p1.distance_to_origin() << std::endl;
  std::cout << "The distance between (1, 1) and (2, 2) is " << p1.distance_to_point(p2) << std::endl;
  std::cout << "The distance between (2, 2) and (1, 1) is " << p2.distance_to_point(p1) << std::endl;

  // Line Class Testing
  Line l1 = Line(p1, p2);
  std::cout << "The distance between the line defined by (1, 1) and (2, 2) and the point (0, 3) is " << l1.distance_to_point(p3) << std::endl;

  // Triangle Class Testing
  Triangle t1 = Triangle(o, p4, p1);
  std::cout << "The area of the triangle defined by (0, 0), (1, 1), and (0, 1) is " << t1.area() << std::endl;


  return 0;
}

int add(const int x, const int y) {
  return x + y;
}

int subtract(const int x, const int y) {
  return x - y;
}

int multiply(const int x, const int y) {
  return x * y;
}

int divide(const int x, const int y) {
  return x / y;
}
