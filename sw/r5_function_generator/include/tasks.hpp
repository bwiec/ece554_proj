#pragma once

#include <iostream>
#include "debug.hpp"
#include "gpio.hpp"
#include "reset.hpp"
#include "wdt.hpp"
#include "signal_generator.hpp"
#include "sine_generator.hpp"
#include "square_generator.hpp"
#include "triangle_generator.hpp"
#include "sawtooth_generator.hpp"
#include "hw_fifo.hpp"
#include "mailbox.hpp"

using namespace std;

typedef struct device_ids
{
	int wdt_gpio = 0;
	int reset_gpio = 0;
	int sample_rate_gpio = 0;
	int hw_fifo0 = 0;
	int hw_fifo1 = 0;
	int hw_fifo2 = 0;
	int hw_fifo3 = 0;
} device_ids_t;

typedef enum states
{
  RELEASE_RESET = 0,
  PET_WDT,
  RECV_CMD,
  SEND_SAMPLES,
} states_t;

class tasks
{
  private:
	int _n;
	command _cmd;
	wdt _wdt;
	reset _reset;
	gpio _sample_rate_gpio; // Single sample period controls all channels for now
	hw_fifo _hw_fifo0;
	hw_fifo _hw_fifo1;
	hw_fifo _hw_fifo2;
	hw_fifo _hw_fifo3;
	hw_fifo* _hw_fifos[NUM_CHANNELS];
	signal_generator* _waveform_generators[NUM_CHANNELS];
	mailbox _cmd_mailbox;
	
	void release_reset();
	void pet_wdt();
	void recv_cmd();
	void update_patterns();
	void send_samples();

  public:
	tasks(device_ids_t* device_ids);
    void run();
    ~tasks();
};


