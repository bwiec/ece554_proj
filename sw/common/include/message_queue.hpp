#pragma once

#include <iostream>
#include "xparameters.h"

class message_queue
{
  private:
    bool overflow;
    bool underflow;

    bool is_full();
    void incr_ptr(int* ptr);
    bool is_empty();

  public:
    message_queue();
    void push(int val);
    int pop();
    ~message_queue();
};