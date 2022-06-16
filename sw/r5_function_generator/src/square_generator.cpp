#include "square_generator.hpp"

int square_generator::calculate_sample(int n)
{
  float t = 2.0 * M_PI * n / (float)_cmd->get_sample_rate(_channel_idx);
  float f = (float)_cmd->get_frequency(_channel_idx);

  float result = pow(-1.0, floor(2*f*t));

  return (int)(result*(1<<16));
}
