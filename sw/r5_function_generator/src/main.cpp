#include <iostream>
#include <queue>
#include "xparameters.h"
#include "sleep.h"
#include "debug.hpp"
#include "message_queue.hpp"
#include "reset.hpp"
#include "wdt.hpp"
#include "signal_generator.hpp"
#include "sine_generator.hpp"
#include "hw_fifo.hpp"

using namespace std;

typedef enum tasks
{
  RELEASE_RESET = 0,
  PET_WDT,
  RECV_CMD,
  SEND_RESP,
  SEND_SAMPLES,
} tasks_t;

int main(int argc, char* argv[])
{
  cout << "Starting r5_function_generator" << endl;

  // Initialize peripherals and local objects
  wdt wdt_inst(XPAR_AXI_GPIO_0_DEVICE_ID);
  reset reset_inst(XPAR_AXI_GPIO_2_DEVICE_ID);
  gpio sample_rate_gpio_inst(XPAR_AXI_GPIO_1_DEVICE_ID); // Single sample period controls all channels for now
  sample_rate_gpio_inst.write(2*1000*1000);

  hw_fifo hw_fifo0_inst(XPAR_AXI_FIFO_MM_S_0_DEVICE_ID);
  hw_fifo hw_fifo1_inst(XPAR_AXI_FIFO_MM_S_1_DEVICE_ID);
  hw_fifo hw_fifo2_inst(XPAR_AXI_FIFO_MM_S_2_DEVICE_ID);
  hw_fifo hw_fifo3_inst(XPAR_AXI_FIFO_MM_S_3_DEVICE_ID);
  hw_fifo* hw_fifos[NUM_CHANNELS] = {&hw_fifo0_inst, &hw_fifo1_inst, &hw_fifo2_inst, &hw_fifo3_inst};

  // Dummy command for now
  command cmd;
  for (int ii = 0; ii < NUM_CHANNELS; ii++)
  {
	  cmd.set_sample_rate(ii, 200);
	  cmd.set_frequency(ii, 10);
	  cmd.set_channel_is_enabled(ii);
	  cmd.set_pattern(ii, PATTERN_SINE);
	  cmd.set_pattern_specific(ii, 0);
  }
  signal_generator* waveform_generators[NUM_CHANNELS];


  int n;
  tasks_t cur_task = RELEASE_RESET;
  while (1)
  {
	int sample = 0;
    switch(cur_task)
    {
      case RELEASE_RESET:
    	DEBUG_MSG("RELEASE_RESET state");
    	reset_inst.deassert();
    	cur_task = PET_WDT;
    	break;
      case PET_WDT:
    	DEBUG_MSG("PET_WDT state");
    	wdt_inst.pet();
    	cur_task = RECV_CMD;
    	break;
      case RECV_CMD:
        DEBUG_MSG("RECV_CMD state");
        for (int ii = 0; ii < NUM_CHANNELS; ii++)
        {
        	waveform_generators[ii] = new sine_generator(&cmd, ii);
        	cur_task = SEND_RESP;
        }
        break;
      case SEND_RESP:
    	DEBUG_MSG("SEND_RESP state");
        cur_task = SEND_SAMPLES;
        break;
      case SEND_SAMPLES:
        DEBUG_MSG("SEND_SAMPLES state");
        for (int ii = 0; ii < NUM_CHANNELS; ii++)
        {
        	sample = waveform_generators[ii]->calculate_sample(n);
        	hw_fifos[ii]->push(sample);
        }
        n++;
        cur_task = PET_WDT;
        break;
      default:
        cerr << "Unknown task" << endl;
        return -1;
    }
	#ifdef MYDEBUG
    usleep(100*1000);
	#endif
  }


  /*
  queue<int> cmd_queue;
  tasks_t cur_task = RECV_CMD;
  int cmd_from_ui = 0;
  while (1)
  {
    switch(cur_task)
    {
      case RECV_CMD:
        cmd_from_ui = cmd_queue.back();
        cmd_queue.pop();
        DEBUG_MSG("Received : " << cmd_from_ui);
        cur_task = SEND_RESP;
        break;
      case SEND_RESP:
        DEBUG_MSG("Placeholder in case need to send response to user");
        cur_task = SEND_SAMPLES;
        break;
      case SEND_SAMPLES:
        DEBUG_MSG("Sending samples");
        cur_task = RECV_CMD;
        break;
      default:
        cerr << "Unknown task" << endl;
        return -1;
    }
  }*/

  return 0;
}
