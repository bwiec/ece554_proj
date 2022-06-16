#include "gpio.hpp"

gpio::gpio(int device_id)
{
  _device_id = device_id;
  xgpio_init();
}

void gpio::xgpio_init()
{
	DEBUG_MSG("Starting xgpio_init() for " << _device_id);

	int status = XGpio_Initialize(&_xgpio_inst, _device_id);
	if (status != XST_SUCCESS)
	{
		cerr << "Initialization of xgpio failed for " << _device_id;
	}
	
	XGpio_SetDataDirection(&_xgpio_inst, 1, 0x00000000); // All outputs
	
	DEBUG_MSG("xgpio_init() complete for " << _device_id);
}

void gpio::write(int val)
{
	DEBUG_MSG("writing " << val << " to xgpio " << _device_id);
	XGpio_DiscreteWrite(&_xgpio_inst, 1, val);
	DEBUG_MSG("Done writing to xgpio " << _device_id);
}

int gpio::read()
{
	DEBUG_MSG("reading from xgpio " << _device_id);
	int val = XGpio_DiscreteRead(&_xgpio_inst, 1);
	DEBUG_MSG("Done reading " << val << " from xgpio " << _device_id);
	
	return val;
}

gpio::~gpio()
{
  
}
