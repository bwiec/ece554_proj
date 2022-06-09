#pragma once

#include <iostream>
#include <cmath>
#include "signal_generator.hpp"

using namespace std;

class sine_generator : public signal_generator
{
  public:
    sine_generator(command* cmd, int channel_idx) : signal_generator(cmd, channel_idx) { };
    int calculate_sample(int n);
    ~sine_generator() { };
};