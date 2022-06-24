#include "reset.hpp"

reset::reset(int device_id) : _gpio(device_id)
{

}

void reset::assert()
{
	DEBUG_MSG("Asserting reset");
	_gpio.write(0x00000000);
	DEBUG_MSG("Done asserting reset");
}

void reset::deassert()
{
	DEBUG_MSG("Deasserting reset");
	_gpio.write(0x00000001);
	DEBUG_MSG("Done deasserting reset");
}

reset::~reset()
{

}
