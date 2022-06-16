#include "wdt.hpp"

wdt::wdt(int device_id) : _gpio_inst(device_id)
{

}

void wdt::pet()
{
	DEBUG_MSG("Petting wdt");
	_gpio_inst.write(0x00000000);
	_gpio_inst.write(0x00000001);
	_gpio_inst.write(0x00000000);
	DEBUG_MSG("Done petting wdt");
}

wdt::~wdt()
{

}
