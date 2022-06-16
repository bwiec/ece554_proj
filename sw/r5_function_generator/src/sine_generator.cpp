#include "sine_generator.hpp"

int sine_generator::calculate_sample(int n)
{
  float result = sin(f()*t(n));

  return (int)(result*(1<<16));
}
