#pragma once

#include <iostream>
#include <vector>

using namespace std;

#ifndef NUM_CHANNELS
#define NUM_CHANNELS 4
#endif

class command
{
  private:
    unsigned char channel_is_enabled;

    bool channel_index_out_of_bounds(unsigned int idx);

  public:
    command();
    void set_channel_is_enabled(unsigned int idx);
    void clr_channel_is_enabled(unsigned int idx);
    bool get_channel_is_enabled(unsigned int idx);
    ~command();
};