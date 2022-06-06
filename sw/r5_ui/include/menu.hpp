#pragma once

#include <iostream>
#include "command.hpp"

using namespace std;

class menu
{
  private:
    bool _new_input_available;
    command _cmd;

    void print_header();
    char get_character();
    unsigned int get_number(int max_digits);
    unsigned char submenu_channel_select();
    void submenu_channel_enable();
    void submenu_sample_rate();
    void submenu_frequency();
    void submenu_pattern();
    void submenu_misc();
    void prompt();
  
  public:
    menu();
    void print();
    command* get_user_input();
    void consumed();
    ~menu();
};