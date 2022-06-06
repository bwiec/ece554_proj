#include "command.hpp"

command::command()
{
  channel_is_enabled = 0;
}

void command::set_channel_is_enabled(unsigned int idx)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  channel_is_enabled |= (unsigned char)(1 << idx);
}

bool command::channel_index_out_of_bounds(unsigned int idx)
{
  if (idx < 0 || idx > NUM_CHANNELS)
  {
    cerr << "ERROR! Illegal channel index " << idx << endl;
    return true;
  }
  return false;
}

void command::clr_channel_is_enabled(unsigned int idx)
{
  if (channel_index_out_of_bounds(idx)) { return; }
  channel_is_enabled &= (unsigned char)(~(1 << idx));
}

bool command::get_channel_is_enabled(unsigned int idx)
{
  if (channel_index_out_of_bounds(idx)) { return false; }
  return (channel_is_enabled & (unsigned char)(1 << idx));
}

command::~command()
{

}