#pragma once

#include <iostream>
#include <cmath>
#include "signal_generator.hpp"

using namespace std;

class sawtooth_generator : public signal_generator
{
  public:
    sawtooth_generator(command* cmd, int channel_idx) : signal_generator(cmd, channel_idx) { };
    int calculate_sample(int n);
    ~sawtooth_generator() { };
};