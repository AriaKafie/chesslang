
#include "interpreter.h"
#include "types.h"

#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 2)
    return std::cerr << "please provide one file path\n", 1;

  Interpreter::parse(argv[1]);
}