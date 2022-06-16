#include "signal_generator.hpp"

signal_generator::signal_generator(command* cmd, int channel_idx)
{
  _cmd = cmd;
  _channel_idx = channel_idx;
}

int signal_generator::calculate_sample(int n)
{
	cerr << "Non-implemented base class." << endl;
	return -1;
}

signal_generator::~signal_generator()
{
  
}
