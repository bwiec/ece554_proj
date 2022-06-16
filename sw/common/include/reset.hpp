#pragma once

#include <iostream>
#include "debug.hpp"
#include "gpio.hpp"

using namespace std;

class reset
{
  private:
    gpio _gpio_inst;

  public:
    reset(int device_id);
    void assert();
    void deassert();
    ~reset();
};


