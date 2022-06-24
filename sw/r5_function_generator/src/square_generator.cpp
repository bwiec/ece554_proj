#include "square_generator.hpp"

int square_generator::calculate_sample(int n)
{
  float result = pow(-1.0, floor(2*f()*t(n)));

  return (int)(result*(1<<16));
}
