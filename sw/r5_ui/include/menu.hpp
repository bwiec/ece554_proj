#pragma once

#include <iostream>
#include "command.hpp"

using namespace std;

class menu
{
  private:
    command cmd;

    void print_header();
    void prompt();
  
  public:
    menu();
    void print();
    command* get_user_input();
    ~menu();
};