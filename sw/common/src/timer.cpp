#include "timer.hpp"

timer::timer(int device_id)
{
	_device_id = device_id;
	ttc_init();
}

void timer::ttc_init()
{
	XTtcPs_Config* cfg = XTtcPs_LookupConfig(_device_id);
	if (cfg == NULL)
	{
		cerr << "Failed to look up ttc device" << endl;
		return;
	}

	int status = XTtcPs_CfgInitialize(&_ttc, cfg, cfg->BaseAddress);
	if (status != XST_SUCCESS)
	{
		cerr << "Failed to initialize ttc" << endl;
	}

	/*XTtcPs_SetOptions(&_ttc, (XTTCPS_OPTION_INTERVAL_MODE | XTTCPS_OPTION_MATCH_MODE));

	XInterval ttc_interval = 0;
	unsigned char ttc_prescaler = 0;
	XTtcPs_CalcIntervalFromFreq(&_ttc, TTC_FREQ_HZ, &ttc_interval, &ttc_prescaler);
	XTtcPs_SetInterval(&_ttc, ttc_interval);
	XTtcPs_SetPrescaler(&_ttc, ttc_prescaler);*/
}

void timer::start()
{
	XTtcPs_ResetCounterValue(&_ttc);
	XTtcPs_Start(&_ttc);
}

float timer::stop()
{
	XTtcPs_Stop(&_ttc);
	int cnt = XTtcPs_GetCounterValue(&_ttc);

	return ((float)cnt) / ((float)XPAR_CPU_CORTEXR5_0_CPU_CLK_FREQ_HZ);
}

timer::~timer()
{

}
