#include <iostream>

int somefunc(int i){
  std::cout << "file2.cxx::somefunc: i = " << i << std::endl;
  int r = 2 * i;
  std::cout << "file2.cxx::somefunc: r = " << r << std::endl;
  return(r);
}