#pragma once

#include <iostream>
#include "xparameters.h"
#include "xstatus.h"
#include "xttcps.h"
#include "debug.hpp"

using namespace std;

class timer
{
  private:
	int _device_id;
    XTtcPs _ttc;
    
    void ttc_init();

  public:
    timer(int device_id);
    void start();
    float stop();
    ~timer();
};


