#include <iostream>

int main()
{
  std::cout << "Eben Quenneville" << std::endl;
  std::cout << "Classroom 24-115" << std::endl;

  int x = 5;
  int y = 7;

  int z = x + y;
  std::cout << "The sum of " << x << " and " << y << " is " << z << std::endl;

  int w = x * y * z;
  std::cout << "The product of " << x << " and " << y << " and " << z << " is " << w << std::endl;

  int v = x / y;
  std::cout << "The division of " << x << " and " << y << " is " << v << std::endl;

  return 0;
}