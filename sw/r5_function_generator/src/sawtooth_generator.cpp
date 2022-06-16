#include "sawtooth_generator.hpp"

int sawtooth_generator::calculate_sample(int n)
{
  float result = 2.0*(t(n)*f() - floor(1/2 + t(n)*f()));

  return (int)(result*(1<<16));
}
