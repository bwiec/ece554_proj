#include "message_queue.hpp"

using namespace std;

#define MAX_QUEUE_LENGTH 10

volatile static int* wr_ptr = (int*)XPAR_PSU_OCM_RAM_0_S_AXI_BASEADDR;
volatile static int* rd_ptr = (int*)(XPAR_PSU_OCM_RAM_0_S_AXI_BASEADDR+4);
volatile static int* buf = (int*)(XPAR_PSU_OCM_RAM_0_S_AXI_BASEADDR+8);

message_queue::message_queue()
{

}

void message_queue::push(int val)
{
  while (is_full())
  {
    // Wait for free space
  }
  buf[*wr_ptr] = val;
  incr_ptr((int*)wr_ptr);
}

bool message_queue::is_full()
{
  return ((*wr_ptr == (*rd_ptr)-1) ||
          (*wr_ptr == MAX_QUEUE_LENGTH-1 && (*rd_ptr) == 0));
}

void message_queue::incr_ptr(int* ptr)
{
  if (*ptr == MAX_QUEUE_LENGTH-1)
  {
    *ptr = 0;
  }
  else
  {
    (*ptr)++;
  }
}

int message_queue::pop()
{
  while(is_empty())
  {
    // Wait for a new value
  }
  int val = buf[*rd_ptr];
  incr_ptr((int*)rd_ptr);
  return val;
}

bool message_queue::is_empty()
{
  return (*rd_ptr == *wr_ptr);
}

message_queue::~message_queue()
{

}