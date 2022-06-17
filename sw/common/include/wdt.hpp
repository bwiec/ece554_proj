#pragma once

#include <iostream>
#include "debug.hpp"
#include "gpio.hpp"

using namespace std;

class wdt
{
  private:
    gpio _gpio;

  public:
    wdt(int device_id);
    void pet();
    ~wdt();
};


