#pragma once

#include <iostream>
#include "debug.hpp"
#include "xgpio.h"
#include "xstatus.h"

using namespace std;

class gpio
{
  private:
    int _device_id;
    XGpio _xgpio;
    
    void xgpio_init();

  public:
    gpio(int device_id);
    void write(int val);
    int read();
    ~gpio();
};
