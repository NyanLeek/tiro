#include "data.h"

void
data::print (void)
{
  std::cout << "X:\t" << x << std::endl;
  std::cout << "Y:\t" << y << std::endl;
  std::cout << "SP:\t" << speed << std::endl;
  std::cout << "X_D:\t" << x_dest << std::endl;
  std::cout << "Y_D:\t" << y_dest << std::endl;
  std::cout << "V:\t" << valid << std::endl;
}
