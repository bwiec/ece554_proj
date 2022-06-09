#include "sine_generator.hpp"

int sine_generator::calculate_sample(int n)
{
  float t = 2.0 * M_PI * n / (float)_cmd->get_sample_rate(_channel_idx);

  float result = sin(t);

  return (int)result;
}
