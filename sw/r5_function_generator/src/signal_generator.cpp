#include "signal_generator.hpp"

signal_generator::signal_generator(command* cmd, int channel_idx)
{
  _cmd = cmd;
  _channel_idx = channel_idx;
}

float signal_generator::t(int n)
{
	return (float)(2.0 * M_PI * n / (float)_cmd->get_sample_rate(_channel_idx));
}

float signal_generator::f()
{
	return (float)_cmd->get_frequency(_channel_idx);
}

int signal_generator::calculate_sample(int n)
{
	cerr << "Non-implemented base class." << endl;
	return -1;
}

signal_generator::~signal_generator()
{
  
}
