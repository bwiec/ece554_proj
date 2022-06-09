#include "triangle_generator.hpp"

int triangle_generator::calculate_sample(int n)
{
  float t = 2.0 * M_PI * n / (float)_cmd->get_sample_rate(_channel_idx);
  float f = (float)_cmd->get_frequency(_channel_idx);

  float result = 2.0*abs(t*f - floor(t*f + 1.0/2.0));

  return (int)result;
}
