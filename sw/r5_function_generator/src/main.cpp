#include <iostream>
#include "xparameters.h"
#include "tasks.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	device_ids_t _device_ids =
	{
		XPAR_AXI_GPIO_0_DEVICE_ID,
		XPAR_AXI_GPIO_2_DEVICE_ID,
		XPAR_AXI_GPIO_1_DEVICE_ID,
		XPAR_AXI_FIFO_MM_S_0_DEVICE_ID,
		XPAR_AXI_FIFO_MM_S_1_DEVICE_ID,
		XPAR_AXI_FIFO_MM_S_2_DEVICE_ID,
		XPAR_AXI_FIFO_MM_S_3_DEVICE_ID,
	};

	tasks tasks_inst(&_device_ids);
	tasks_inst.run();

	return 0;
}
