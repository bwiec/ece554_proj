#include "tasks.hpp"

tasks::tasks(device_ids_t* device_ids) :
	_menu(&_cmd)
{
	// Dummy command for now
	for (int ii = 0; ii < NUM_CHANNELS; ii++)
	{
		_cmd.set_sample_rate(ii, 200);
		_cmd.set_frequency(ii, 10);
		_cmd.set_channel_is_enabled(ii);
		_cmd.set_pattern(ii, (pattern_t)ii);
		_cmd.set_pattern_specific(ii, 0);
	}
	_cmd.set_frequency(1, 2);
	_cmd.set_frequency(2, 2);
	_cmd.set_frequency(3, 2);
}

void tasks::run()
{
	states_t cur_state = PET_WDT;
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
					_cmd_queue.push((int)_cmd.get_channel_is_enabled(ii));
					_cmd_queue.push((int)_cmd.get_sample_rate(ii));
					_cmd_queue.push((int)_cmd.get_frequency(ii));
					_cmd_queue.push((int)_cmd.get_pattern(ii));
					_cmd_queue.push((int)_cmd.get_pattern_specific(ii));
				}
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
