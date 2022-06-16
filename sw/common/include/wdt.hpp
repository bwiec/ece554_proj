#pragma once

#include <iostream>
#include "debug.hpp"
#include "gpio.hpp"

using namespace std;

class wdt
{
  private:
    gpio _gpio_inst;

  public:
    wdt(int device_id);
    void pet();
    ~wdt();
};


