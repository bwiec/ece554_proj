#pragma once

#include <iostream>
#include <vector>

using namespace std;

#ifndef NUM_CHANNELS
#define NUM_CHANNELS 4
#endif

typedef enum pattern
{
  PATTERN_SINE = 0,
  PATTERN_SQUARE = 1,
  PATTERN_TRIANGLE = 2,
  PATTERN_SAWTOOTH = 3,
  NUM_PATTERNS
} pattern_t;

class command
{
  private:
    unsigned char _channel_is_enabled;
    unsigned char _sample_rate[NUM_CHANNELS];
    unsigned char _frequency[NUM_CHANNELS];
    unsigned char _pattern[NUM_CHANNELS];
    unsigned char _pattern_specific[NUM_CHANNELS];
    unsigned int _test_wdt;

    bool channel_index_out_of_bounds(unsigned char idx);
    bool sample_rate_out_of_bounds(unsigned char sample_rate);
    bool frequency_out_of_bounds(unsigned char frequency, unsigned char sample_rate);
    bool pattern_illegal(unsigned char pattern);
    bool pattern_specific_out_of_bounds(pattern_t pattern, int pattern_specific);

  public:
    command();

    void set_channel_is_enabled(unsigned char idx);
    void clr_channel_is_enabled(unsigned char idx);
    bool get_channel_is_enabled(unsigned char idx);
    
    void set_sample_rate(unsigned char idx, unsigned char sample_rate);
    unsigned char get_sample_rate(unsigned char idx);

    void set_frequency(unsigned char idx, unsigned char frequency);
    unsigned char get_frequency(unsigned char idx);

    void set_pattern(unsigned char idx, pattern_t pattern);
    pattern_t get_pattern(unsigned char idx);

    void set_pattern_specific(unsigned char idx, int _pattern_specific);
    int get_pattern_specific(unsigned char idx);

    void set_test_wdt();
    void clr_test_wdt();
    int get_test_wdt();

    void dump();

    ~command();
};
