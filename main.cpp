#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <array>
#include <map>

int add(const int x, const int y);
int subtract(const int x, const int y);
int multiply(const int x, const int y);
int divide(const int x, const int y);

class Line;
class Point;
class Triangle;
class Polygon;

/**
 * A representation of a circle. Only includes radius.
 */
class Circle
{
public:
  int radius;
  /**
   * @param none
   * @returns the area of the circle with `this->radius`
   */
  double area()
  {
    return M_PI * std::pow(radius, 2);
  }
  void print()
  {
    std::cout << "The area of the circle with radius " << radius << " is: " << this->area() << std::endl;
  }
};

/**
 * Describes a point in the 2D plane.
 */
class Point
{
public:
  double x;
  double y;
  /**
   * Default constructor for a point is (0, 0).
   * @param none
   * @returns none
   */
  Point()
  {
    this->x = 0;
    this->y = 0;
  }
  /**
   * Constructor for a point with (x, y) coordinates.
   * @param x, y: the coordinates of the point
   * @returns none
   */
  Point(const double x, const double y)
  {
    this->x = x;
    this->y = y;
  }
  /**
   * @param none
   * @returns the distance from the point to the origin, using Pythagorean theorem
   */
  double distance_to_origin()
  {
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
  }
  /**
   * @param p: the point to calculate the distance to
   * @returns the distance from this to the given point
   */
  double distance_to_point(const Point &p)
  {
    return std::abs(std::sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2)));
  }

  /**
   * @param none
   * @returns A formatted String representation of the point, like "(x, y)"
   */
  std::string to_str()
  {
    return ("(" + std::to_string(x) + ", " + std::to_string(y) + ")");
  }
};

/**
 * Representation of a line given 2 Points on the line
 */
class Line
{
public:
  Point p1;
  Point p2;
  /**
   * Default constructor sets both points to (0, 0).
   * @param none
   * @returns none
   */
  Line()
  {
    this->p1 = Point(0, 0);
    this->p2 = Point(0, 0);
  }
  /**
   * Constructs a line segment between p1 and p2.
   * @param p1,p2: the points on the line
   * @returns none
   */
  Line(const Point &p1, const Point &p2)
  {
    this->p1 = p1;
    this->p2 = p2;
  }
  /**
   * @param none
   * @returns the length of the line segment between p1 and p2.
   */
  double length()
  {
    return p1.distance_to_point(p2);
  }
  /**
   * @param p: another point to find the distance between
   * @returns the shortest distance from the point to the line
   */
  double distance_to_point(const Point &p)
  {
    double numerator = std::abs((p2.x - p1.x) * (p1.y - p.y) - (p1.x - p.x) * (p2.y - p1.y));
    return (numerator / this->length());
  }
};

/**
 * A representation of a triangle as 3 Points
 */
class Triangle
{
public:
  Point p1;
  Point p2;
  Point p3;
  /**
   * Default constructor sets all points to (0, 0).
   * @param none
   * @returns none
   */
  Triangle()
  {
    this->p1 = Point(0, 0);
    this->p1 = Point(0, 0);
    this->p1 = Point(0, 0);
  }
  /**
   * Constructs a triangle with vertices at p1, p2, and p3.
   * @param none
   * @returns none
   */
  Triangle(const Point &p1, const Point &p2, const Point &p3)
  {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
  }
  /**
   * Calculates the area of the triangle, using Heron's Formula.
   * @param none
   * @returns the area of the triangle
   */
  double area()
  {
    // Heron's Formula!
    double a = Line(p1, p2).length();
    double b = Line(p1, p3).length();
    double c = Line(p2, p3).length();
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
  }
  /**
   * Prints a string representing the triangle, e.g:
   * The area of the triangle defined by (0, 0), (0, 1), and (1, 1) is 0.5.
   * @param none
   * @returns none
   */
  void print()
  {
    std::cout << "The area of the triangle defined by " << p1.to_str() << ", " << p2.to_str() << " and " << p3.to_str() << " is: " << this->area() << std::endl;
  }
};

/**
 * Class to represent a Polygon as a vector of points. Must be convex.
 */
class Polygon
{
public:
  std::vector<Point> points;
  /**
   * Constructs a polygon from a vector of points. Automatically orders the points counterclockwi
   * @param points: a vector of points describing the convex polygon. Can be in any order.
   * @returns none
   */
  Polygon(const std::vector<Point> &points)
  {
    this->points = points;
    this->order_points();
  }
  /**
   * Calculates the area of the polygon, using the triangular method.
   * @param none
   * @returns the area of the polygon
   */
  double area()
  {
    double area = 0.0;
    for (int i = 1; i < points.size() - 1; i++)
    {
      Triangle t = Triangle(points[0], points[i], points[i + 1]);
      area += t.area();
    }
    return area;
  }
  /**
   * Calculates the perimeter of the polygon.
   * @param none
   * @returns the perimeter of the polygon
   */
  double perimeter()
  {
    int n = points.size();
    double perimeter = 0.0;
    for (int i = 0; i < n - 1; i++)
    {
      perimeter += points[i].distance_to_point(points[i + 1]);
    }
    perimeter += points[0].distance_to_point(points[n - 1]);
    return perimeter;
  }
  /**
   * Orders `this->points` counterclockwise.
   * @param none
   * @returns none
   */
  void order_points()
  {
    // Calculate centroid
    double c_x, c_y = 0.0;
    for (int i = 0; i < points.size(); i++)
    {
      c_x += points[i].x;
      c_y += points[i].y;
    }
    c_x /= points.size();
    c_y /= points.size();
    Point centroid = Point(c_x, c_y);

    // Calculate and store the angle from the vector between centroid and each point
    std::map<double, Point> angle_to_point;
    for (int i = 0; i < points.size(); i++)
    {
      double angle = std::atan2(points[i].x - centroid.x, points[i].y - centroid.y);
      angle_to_point.insert({angle, points[i]});
    }

    // the map will automatically be ordered from least to greatest angle, so we just need to change the
    // Polygon's points array to reflect that ordering
    int points_index = 0;
    std::map<double, Point>::iterator itr;
    for (itr = angle_to_point.begin(); itr != angle_to_point.end(); itr++)
    {
      points[points_index] = itr->second;
      points_index += 1;
    }
  }
  /**
   * Prints the list of points describing the polygon.
   * @param none
   * @returns none
   */
  void print_points()
  {
    std::cout << "The polygon consists of the following points:" << std::endl;
    for (auto i : points)
    {
      std::cout << i.to_str() << std::endl;
    }
  }
};

/**
 * Describes an autonomous underwater vehicle.
 */
class AUV
{
public:
  std::string name;
  Point position;
  double depth;
  double heading;
  std::array<double, 3> speed;
  double angular_speed;
  /**
   * Construct an AUV.
   * @param name: the name of the AUV, e.g. "Nautilus"
   * @param position: the current position of the AUV in global space
   * @param depth: the depth of the AUV beneath the surface
   * @param heading: the local heading of the AUV
   * @param speed: a 3-element array giving the speed in x, y, and z respectively
   * @param angular_speed: the angular velocity of the AUV. Positive is counterclockwise.
   * @returns none
   */
  AUV(std::string name, Point position, double depth, double heading, std::array<double, 3> speed, double angular_speed)
  {
    this->name = name;
    this->position = position;
    this->depth = depth;
    this->heading = heading;
    this->speed = speed;
    this->angular_speed = angular_speed;
  }
  /**
   * Simulates a single step forward in time for the AUV, using the velocities that already are set.
   * @param time_step: the duration of time to step forward. e.g. 0.1 seconds
   * @returns none, but modifies the state of the AUV
   */
  void step(const double time_step)
  {
    heading += angular_speed * time_step;
    position.x += speed[0] * time_step;
    position.y += speed[1] * time_step;
    depth += speed[2] * time_step;
  }

  /**
   * Applies the linear acceleration to the linear speed.
   * @param accel_array: a 3-element array where the first element is x-speed, second element is y-acceleration, and third element is z-acceleration
   * @param time_step: the amount of time we are accelerating for, e.g. 0.1 seconds
   * @returns none, but modifies the state of the AUV
   */
  void apply_acceleration(std::array<double, 3> accel_array, const double time_step)
  {
    speed[0] += accel_array[0] * time_step;
    speed[1] += accel_array[1] * time_step;
    speed[2] += accel_array[2] * time_step;
  }
  /**
   * Applies the angular acceleration to angular velocity.
   * @param angular_acceleration: the amount of angular acceleration
   * @param time_step: the amount of time we are accelerating for, e.g. 0.1 seconds
   * @returns none, but modifies the state of the AUV
   */
  void apply_angular_acceleration(const double angular_acceleration, const double time_step)
  {
    angular_speed += angular_acceleration * time_step;
  }

  /**
   * Prints a string representation of the AUV
   * @param none
   * @returns none
   */
  void print()
  {
    std::cout << name << std::endl;
    std::cout << "Position: " << position.x << ", " << position.y << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Heading: " << heading << std::endl;
    std::cout << "Speed: [" << speed[0] << ", " << speed[1] << ", " << speed[2] << "]" << std::endl;
    std::cout << "Angular Velocity: " << angular_speed << std::endl;
  }
};
int main()
{
  // Hello, world!
  /*
  std::cout << "Eben Quenneville" << std::endl;
  std::cout << "Classroom 24-115" << std::endl;
  */
  // Adding, subtracting, multiplying, dividing
  /*
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
  */

  // Circle Class Testing
  Circle c;
  c.radius = 10.0;
  c.print();

  // Point Class Testing
  std::cout << std::endl;

  std::cout << "The distance to the origin from point (1, 1) is " << Point(1, 1).distance_to_origin() << std::endl;
  std::cout << "The distance between (1, 1) and (2, 2) is " << Point(1, 1).distance_to_point(Point(2, 2)) << std::endl;
  std::cout << "The distance between (2, 2) and (1, 1) is " << Point(2, 2).distance_to_point(Point(1, 1)) << std::endl;

  // Line Class Testing
  std::cout << std::endl;

  Point p1 = Point(1, 1);
  Point p2 = Point(2, 2);
  Point p3 = Point(0, 3);
  Line l1 = Line(p1, p2);
  std::cout << "The distance between the line defined by (1, 1) and (2, 2) and the point (0, 3) is " << l1.distance_to_point(p3) << std::endl;

  // Triangle Class Testing
  std::cout << std::endl;

  Triangle t1 = Triangle(Point(0, 0), Point(1, 1), Point(0, 1));
  t1.print();

  // Polygon Class Testing
  std::cout << std::endl;

  std::vector<Point> points = {Point(0, 1), Point(0, 0), Point(1, 0), Point(1, 1)};
  Polygon poly1 = Polygon(points);
  poly1.order_points();
  poly1.print_points();
  std::cout << "The area of the polygon is: " << poly1.area() << std::endl;

  // AUV Testing
  std::cout << std::endl;

  std::array<double, 3> auv_1_speed = {0.0, 0.0, 10};
  AUV auv_1 = AUV("AUV 1", Point(0, 0), 0, 0, auv_1_speed, 0);

  auv_1.print();
  auv_1.step(1);
  std::cout << std::endl;
  auv_1.print();

  return 0;
}

int add(const int x, const int y)
{
  return x + y;
}

int subtract(const int x, const int y)
{
  return x - y;
}

int multiply(const int x, const int y)
{
  return x * y;
}

int divide(const int x, const int y)
{
  return x / y;
}
