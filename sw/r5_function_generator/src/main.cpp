#include <iostream>
#include <queue>
#include "xparameters.h"
#include "sleep.h"
#include "debug.hpp"
#include "message_queue.hpp"
#include "tasks.hpp"

using namespace std;


int main(int argc, char* argv[])
{
  cout << "Starting r5_function_generator" << endl;
  device_ids_t device_ids_inst =
  {
		  XPAR_AXI_GPIO_0_DEVICE_ID,
		  XPAR_AXI_GPIO_2_DEVICE_ID,
		  XPAR_AXI_GPIO_1_DEVICE_ID,
		  XPAR_AXI_FIFO_MM_S_0_DEVICE_ID,
		  XPAR_AXI_FIFO_MM_S_1_DEVICE_ID,
		  XPAR_AXI_FIFO_MM_S_2_DEVICE_ID,
		  XPAR_AXI_FIFO_MM_S_3_DEVICE_ID,
  };
  tasks tasks_inst(&device_ids_inst);
  tasks_inst.run();


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
