#include <iostream>
#include <queue>
#include "debug.hpp"
#include "message_queue.hpp"

using namespace std;

#define DEBUG

typedef enum tasks
{
  RECV_CMD = 0,
  SEND_RESP = 1,
  SEND_SAMPLES = 2
} tasks_t;

int main(int argc, char* argv[])
{
  cout << "Starting r5_function_generator" << endl;

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
  }

  return 0;
}