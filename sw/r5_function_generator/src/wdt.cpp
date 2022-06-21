#include "wdt.hpp"

#define WDT_IRQ_ID 125U // First four are FIFO irqs, last one is wdt IRQ

static void wdt_isr(void* data)
{
	cout << "WDT expired... resetting" << endl;
	while(1);
}

int wdt::gic_init()
{
	XScuGic_Config* _cfg;
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

wdt::wdt(int device_id) : _gpio(device_id)
{
	gic_init();
}

void wdt::pet()
{
	DEBUG_MSG("Petting wdt");
	_gpio.write(0x00000000);
	_gpio.write(0x00000001);
	_gpio.write(0x00000000);
	DEBUG_MSG("Done petting wdt");
}

wdt::~wdt()
{

}
