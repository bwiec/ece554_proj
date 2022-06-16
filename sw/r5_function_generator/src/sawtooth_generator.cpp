#include "sawtooth_generator.hpp"

int sawtooth_generator::calculate_sample(int n)
{
  float t = 2.0 * M_PI * n / (float)_cmd->get_sample_rate(_channel_idx);
  float f = (float)_cmd->get_frequency(_channel_idx);

  float result = 2.0*(t*f - floor(1/2 + t*f));

  return (int)(result*(1<<16));
}
