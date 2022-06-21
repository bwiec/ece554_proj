#pragma once

#include <iostream>
#include "debug.hpp"
#include "gpio.hpp"
#include "xscugic.h"

using namespace std;

class wdt
{
  private:
    gpio _gpio;
    XScuGic _gic;
    int gic_init(void (*isr)(void* data));

  public:
    wdt(int device_id, void (*isr)(void* data));
    void pet();
    ~wdt();
};


