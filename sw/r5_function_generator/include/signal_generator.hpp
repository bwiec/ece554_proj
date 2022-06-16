#pragma once

#include <iostream>
#include "command.hpp"

using namespace std;

class signal_generator
{
  protected:
    int _channel_idx;
    command* _cmd;

  public:
    signal_generator(command* cmd, int channel_idx);
    virtual int calculate_sample(int n);
    virtual ~signal_generator();
};
