#include "mailbox.hpp"

using namespace std;

volatile static int* new_msg = (int*)(XPAR_PSU_OCM_RAM_0_S_AXI_BASEADDR);
volatile static int* buf = (int*)(XPAR_PSU_OCM_RAM_0_S_AXI_BASEADDR+4);

mailbox::mailbox()
{
	*new_msg = 0;
	Xil_DCacheFlushRange((INTPTR)new_msg, 4);
}

bool mailbox::push(int msg[MAILBOX_MAX_LENGTH_WORDS], int len)
{
	Xil_DCacheInvalidateRange((INTPTR)new_msg, 4);
	if (*new_msg)
	{
		return false;
	}

	for (int ii = 0; ii < len; ii++)
	{
		buf[ii] = msg[ii];
	}
	*new_msg = 1;
	Xil_DCacheFlushRange((INTPTR)new_msg, (MAILBOX_MAX_LENGTH_WORDS+1)*4);

	return true;
}

bool mailbox::pop(int* msg, int len)
{
	Xil_DCacheInvalidateRange((INTPTR)new_msg, (MAILBOX_MAX_LENGTH_WORDS+1)*4);
	if(!(*new_msg))
	{
		return false;
	}

	for (int ii = 0; ii < len; ii++)
	{
		msg[ii] = buf[ii];
	}
	*new_msg = 0;
	Xil_DCacheFlushRange((INTPTR)new_msg, 4);

	return true;
}

mailbox::~mailbox()
{

}
