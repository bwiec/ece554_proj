#pragma once

#include <iostream>
#include "debug.hpp"
#include "xllfifo.h"
#include "xstatus.h"

using namespace std;

class hw_fifo
{
  private:
    int _device_id;
    XLlFifo _xllfifo_inst;
    
    void xllfifo_init();

  public:
    hw_fifo(int device_id);
    void push(int val);
    ~hw_fifo();
};
