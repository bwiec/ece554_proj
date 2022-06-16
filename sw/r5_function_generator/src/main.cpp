#include <iostream>
#include <queue>
#include "xparameters.h"
#include "sleep.h"
#include "debug.hpp"
#include "message_queue.hpp"
#include "reset.hpp"
#include "wdt.hpp"

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

  tasks_t cur_task = RELEASE_RESET;
  while (1)
  {
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
        cur_task = PET_WDT;
        break;
      default:
        cerr << "Unknown task" << endl;
        return -1;
    }
	#ifdef DEBUG
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
