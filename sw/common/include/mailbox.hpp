#pragma once

#include <iostream>
#include "xparameters.h"
#include "xil_cache.h"
#include "debug.hpp"

#define MAILBOX_MAX_LENGTH_WORDS 5*4+2

class mailbox
{
	public:
		mailbox();
		bool push(int msg[MAILBOX_MAX_LENGTH_WORDS], int len);
		bool pop(int* msg, int len);
		~mailbox();
};
