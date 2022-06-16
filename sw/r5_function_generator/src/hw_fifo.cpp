#include "hw_fifo.hpp"

hw_fifo::hw_fifo(int device_id)
{
  _device_id = device_id;
  xllfifo_init();
}

void hw_fifo::xllfifo_init()
{
	DEBUG_MSG("Starting llfifo_init() for " << _device_id);

	XLlFifo_Config *cfg;	
	cfg = XLlFfio_LookupConfig(_device_id);
	if (!cfg)
	{
		cerr << "No llfifo configuration found for " << _device_id;
	}
	
	int status = XLlFifo_CfgInitialize(&_xllfifo_inst, cfg, cfg->BaseAddress);
	if (status != XST_SUCCESS)
	{
		cerr << "Initialization of llfifo failed for " << _device_id;
	}
	
	status = XLlFifo_Status(&_xllfifo_inst);
	XLlFifo_IntClear(&_xllfifo_inst, 0xFFFFFFFF);
	status = XLlFifo_Status(&_xllfifo_inst);
	if (status != 0x0)
	{
		cerr << "For " << _device_id << ", reset value of ISR0: " << XLlFifo_Status(&_xllfifo_inst) << ", expected: 0x0" << endl;
	}
	
	DEBUG_MSG("llfifo_init() complete for " << _device_id);
}

void hw_fifo::push(int val)
{
	DEBUG_MSG("writing " << val << " to llfifo " << _device_id);
	if (XLlFifo_iTxVacancy(&_xllfifo_inst))
	{
		XLlFifo_TxPutWord(&_xllfifo_inst, val);
		XLlFifo_iTxSetLen(&_xllfifo_inst, 4);
		while (!(XLlFifo_IsTxDone(&_xllfifo_inst)));
	}
	else
	{
		cerr << "llfifo " << _device_id << " full" << endl;
	}
	
	DEBUG_MSG("Done writing to llfifo " << _device_id);
}

hw_fifo::~hw_fifo()
{
  
}
