#include <iostream>
#include "xparameters.h"
#include "sleep.h"
#include "tasks.hpp"
#include "xscugic.h"

using namespace std;

//#define WDT_IRQ_ID XPAR_FABRIC_AXI_FIFO_MM_S_3_INTERRUPT_INTR+1 // First four are FIFO irqs, last one is wdt IRQ
#define WDT_IRQ_ID 125U // First four are FIFO irqs, last one is wdt IRQ

XScuGic _gic;
static XScuGic_Config* _cfg;

void wdt_isr(void* data)
{
	cout << "WDT expired... resetting" << endl;
	while(1);
}

int gic_init()
{
	_cfg = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
	if (_cfg == NULL)
	{
		cerr << "Failed to look up SCU GIC" << endl;
		return -1;
	}

	int status = XScuGic_CfgInitialize(&_gic, _cfg, _cfg->CpuBaseAddress);
	if (status != XST_SUCCESS)
	{
		cerr << "Failed to initialize SCU GIC" << endl;
		return -1;
	}

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &_gic);
	Xil_ExceptionEnable();

	XScuGic_Connect(&_gic, WDT_IRQ_ID, (Xil_ExceptionHandler)wdt_isr, &_gic);
	XScuGic_Enable(&_gic, WDT_IRQ_ID);

	return 0;
}

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

	gic_init();
	tasks tasks_inst(&_device_ids);
	tasks_inst.run();

	return 0;
}
