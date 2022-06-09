#include "signal_generator.hpp"

signal_generator::signal_generator(command* cmd, int channel_idx)
{
  _cmd = cmd;
  _channel_idx = channel_idx;
}

signal_generator::~signal_generator()
{
  
}