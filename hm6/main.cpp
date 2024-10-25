#include <iostream>

#include "src/Matrix.hpp"
#include <cassert>

using namespace std;


int main()
{
  /*Matrix<int, -1> myMatrix;
  auto n = myMatrix.size();
  auto a = myMatrix[0][1];
  auto n1 = myMatrix.size();
  myMatrix[1][0] = 5;
  myMatrix[1][1] = 15;
  auto n2 = myMatrix.size();
  auto n4 = myMatrix.begin();
  for (auto n : myMatrix)
  {
    int x,y,z;
    std::tie(x,y,z) = n;
    std::cout<<x << y << z <<std::endl;
    std::cout<<n.m_key.m_x << n.m_key.m_y << n.m_value <<std::endl;
  }*/
  
  Matrix<int, 0> resMatrix;
  int size = 9;
  for (int i = 0; i <= size; i++)
  {
    resMatrix[i][i] = i;
    resMatrix[i][size - i] = i;
  }
  resMatrix.printMatrix(Point(1,1), Point(8,8));
  std::cout<<"Size " << resMatrix.size() << std::endl;
  assert((resMatrix.size() == 18));
  resMatrix.printOnlyUsed();
  return 0;
}
