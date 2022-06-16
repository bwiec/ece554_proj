#include <iostream>
#include <queue>
#include "xparameters.h"
#include "sleep.h"
#include "debug.hpp"
#include "message_queue.hpp"
#include "reset.hpp"
#include "wdt.hpp"
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

  wdt wdt_inst(XPAR_AXI_GPIO_0_DEVICE_ID);
  reset reset_inst(XPAR_AXI_GPIO_2_DEVICE_ID);
  gpio sample_rate_gpio_inst(XPAR_AXI_GPIO_1_DEVICE_ID);
  sample_rate_gpio_inst.write(2*1000*1000);

  command cmd;
  cmd.set_sample_rate(0, 200);
  cmd.set_frequency(0, 10);
  cmd.set_channel_is_enabled(0);
  cmd.set_pattern(0, PATTERN_SINE);
  cmd.set_pattern_specific(0, 0);
  sine_generator ch0_waveform_generator(&cmd, 0);
  hw_fifo hw_fifo_inst(XPAR_AXI_FIFO_MM_S_0_DEVICE_ID);

  int n;
  tasks_t cur_task = RELEASE_RESET;
  while (1)
  {
	int sample;
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
        cur_task = SEND_RESP;
        break;
      case SEND_RESP:
    	DEBUG_MSG("SEND_RESP state");
        cur_task = SEND_SAMPLES;
        break;
      case SEND_SAMPLES:
        DEBUG_MSG("SEND_SAMPLES state");
        sample = ch0_waveform_generator.calculate_sample(n);
        hw_fifo_inst.push(sample);
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
