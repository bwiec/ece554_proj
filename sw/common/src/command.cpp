#include "command.hpp"

command::command()
{
  _channel_is_enabled = 0;
  for (int ii = 0; ii < NUM_CHANNELS; ii++)
  {
    _sample_rate[ii] = 0;
    _frequency[ii] = 0;
    _pattern[ii] = (unsigned char)PATTERN_SINE;
    _pattern_specific[ii] = 0;
  }
}


bool command::channel_index_out_of_bounds(unsigned char idx)
{
  if (idx < 0 || idx > NUM_CHANNELS)
  {
    cerr << "ERROR! Illegal channel index " << idx << endl;
    return true;
  }
  return false;
}

bool command::sample_rate_out_of_bounds(unsigned char sample_rate)
{
  if (sample_rate > 100000)
  {
    cerr << "ERROR! Illegal sample rate " << sample_rate << endl;
    return true;
  }
  return false;
}

bool command::frequency_out_of_bounds(unsigned char frequency)
{
  if (frequency > frequency / 2)
  {
    cerr << "ERROR! Illegal frequency " << frequency << endl;
    return true;
  }
  return false;
}

bool command::pattern_illegal(unsigned char pattern)
{
  if (pattern > NUM_PATTERNS-1)
  {
    cerr << "ERROR! Illegal pattern " << pattern << endl;
    return true;
  }
  return false;
}

bool command::pattern_specific_out_of_bounds(pattern_t pattern, int pattern_specific)
{
  if (
    (pattern == PATTERN_SINE     && (pattern_specific < -3 || pattern_specific > 3))   ||
    (pattern == PATTERN_SQUARE   && (pattern_specific <  0 || pattern_specific > 100)) ||
    (pattern == PATTERN_TRIANGLE && (pattern_specific <  0 || pattern_specific > 100)) ||
    (pattern == PATTERN_SAWTOOTH && (pattern_specific <  0 || pattern_specific > 100))
  )
  {
    cerr << "ERROR! Illegal pattern specific (" << pattern << ") " << pattern_specific << endl;
    return true;
  }
  return false;
}

void command::set_channel_is_enabled(unsigned char idx)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  _channel_is_enabled |= (1 << idx);
}

void command::clr_channel_is_enabled(unsigned char idx)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  _channel_is_enabled &= ~(1 << idx);
}

bool command::get_channel_is_enabled(unsigned char idx)
{
  if (channel_index_out_of_bounds(idx)) { return false; }
  return (_channel_is_enabled & (1 << idx));
}

void command::set_sample_rate(unsigned char idx, unsigned char sample_rate)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  if (sample_rate_out_of_bounds(sample_rate)) { return; }
  _sample_rate[idx] = sample_rate;
}

unsigned char command::get_sample_rate(unsigned char idx)
{
  if (channel_index_out_of_bounds(idx)) { return (unsigned char)(-1); }
  return _sample_rate[idx];
}

void command::set_frequency(unsigned char idx, unsigned char frequency)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  if (frequency_out_of_bounds(frequency)) { return; }
  _frequency[idx] = frequency;
}

unsigned char command::get_frequency(unsigned char idx)
{
  if (channel_index_out_of_bounds(idx)) { return (unsigned char)(-1); }
  return _frequency[idx];
}

void command::set_pattern(unsigned char idx, pattern_t pattern)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  if (pattern_illegal(pattern)) { return; }
  _pattern[idx] = pattern;
}

pattern_t command::get_pattern(unsigned char idx)
{
  if (channel_index_out_of_bounds(idx)) { return (pattern_t)(NUM_PATTERNS); }
  return (pattern_t)_pattern[idx];
}

void command::set_pattern_specific(unsigned char idx, int pattern_specific)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  if (pattern_specific_out_of_bounds((pattern_t)_pattern[idx], pattern_specific)) { return; }
  _pattern_specific[idx] = pattern_specific;
}

int command::get_pattern_specific(unsigned char idx)
{
  if (channel_index_out_of_bounds(idx)) { return -1; }
  return _pattern_specific[idx];
}

command::~command()
{

}