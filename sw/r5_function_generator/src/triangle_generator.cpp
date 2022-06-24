#include "triangle_generator.hpp"

int triangle_generator::calculate_sample(int n)
{
  float result = 2.0*abs(t(n)*f() - floor(t(n)*f() + 1.0/2.0));

  return (int)(result*(1<<16));
}
