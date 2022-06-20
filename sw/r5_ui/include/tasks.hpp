#pragma once

#include <iostream>
#include "debug.hpp"
#include "menu.hpp"
#include "mailbox.hpp"

using namespace std;

typedef struct device_ids
{
	int wdt_gpio = 0;
	
} device_ids_t;

typedef enum states
{
  PET_WDT = 0,
  GET_CMD,
  SEND_CMD
} states_t;

class tasks
{
	private:
		command _cmd;
		menu _menu;
		mailbox _cmd_mailbox;
	
	public:
		tasks(device_ids_t* device_ids);
		void run();
		~tasks();
};


