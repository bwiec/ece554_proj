#include <iostream>
#include <queue>
#include "debug.hpp"
#include "message_queue.hpp"

using namespace std;

#define DEBUG

typedef enum tasks
{
  GET_CMD = 0,
  SEND_CMD = 1,
  RECV_RESP = 2
} tasks_t;

int main(int argc, char* argv[])
{
  cout << "Starting r5_ui" << endl;

  queue<int> cmd_queue;
  tasks_t cur_task = GET_CMD;
  int cmd_from_user = 0;
  int cmd_from_function_generator = 0;
  while (1)
  {
    switch(cur_task)
    {
      case GET_CMD:
        DEBUG_MSG("Getting command");
        cmd_from_user++;
        cur_task = SEND_CMD;
        break;
      case SEND_CMD:
        cmd_queue.push(cmd_from_user);
        DEBUG_MSG("Sending command: " << cmd_from_user);
        cur_task = RECV_RESP;
        break;
      case RECV_RESP:
        cmd_from_function_generator = cmd_queue.back();
        cmd_queue.pop();
        DEBUG_MSG("Received : " << cmd_from_function_generator);
        cur_task = GET_CMD;
        break;
      default:
        cerr << "Unknown task" << endl;
        return -1;
    }
  }

  return 0;
}