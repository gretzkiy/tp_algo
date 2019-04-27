#include <iostream>

int main(int argc, char const *argv[])
{
  int r = 10;
  for( auto i : r ) {
    std::cout << i << std::endl;    
  } 
  return 0;
}