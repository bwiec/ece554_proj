#include "tasks.hpp"

tasks::tasks(device_ids_t* device_ids) :
	_menu(&_cmd)
{
	// Dummy command for now
	for (int ii = 0; ii < NUM_CHANNELS; ii++)
	{
		_cmd.set_channel_is_enabled(ii);
		_cmd.set_sample_rate(ii, (unsigned char)200);
		_cmd.set_frequency(ii, (unsigned char)10);
		_cmd.set_pattern(ii, (pattern_t)ii);
		_cmd.set_pattern_specific(ii, 0);
	}
	_cmd.set_frequency(1, (unsigned char)2);
	_cmd.set_frequency(2, (unsigned char)2);
	_cmd.set_frequency(3, (unsigned char)2);
}

void tasks::run()
{
	states_t cur_state = PET_WDT;
	int buf[MAILBOX_MAX_LENGTH_WORDS];
	while (1)
	{
		switch(cur_state)
		{
			case PET_WDT:
				DEBUG_MSG("PET_WDT state");
				cur_state = GET_CMD;
				break;
			case GET_CMD:
				DEBUG_MSG("GET_CMD state");
				_menu.print();
				_menu.get_user_input();
				_cmd.dump();
				cur_state = SEND_CMD;
				break;
			case SEND_CMD:
				DEBUG_MSG("SEND_CMD state");
				for (int ii = 0; ii < NUM_CHANNELS; ii++)
				{
					buf[ii*5+0] = (int)_cmd.get_channel_is_enabled(ii);
					buf[ii*5+1] = (int)_cmd.get_sample_rate(ii);
					buf[ii*5+2] = (int)_cmd.get_frequency(ii);
					buf[ii*5+3] = (int)_cmd.get_pattern(ii);
					buf[ii*5+4] = (int)_cmd.get_pattern_specific(ii);
				}
				_cmd_mailbox.push(buf, NUM_CHANNELS*5);
				cur_state = PET_WDT;
				break;
			default:
				cerr << "Unknown task" << endl;
				return;
		}
	}
}


tasks::~tasks()
{

}
