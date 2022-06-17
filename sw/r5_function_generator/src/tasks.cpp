#include "tasks.hpp"

tasks::tasks(device_ids_t* device_ids) :
	_wdt_inst(device_ids->wdt_gpio),
	_reset_inst(device_ids->reset_gpio),
	_sample_rate_gpio_inst(device_ids->sample_rate_gpio), // Single sample period controls all channels for now
	_hw_fifo0_inst(device_ids->hw_fifo0),
	_hw_fifo1_inst(device_ids->hw_fifo1),
	_hw_fifo2_inst(device_ids->hw_fifo2),
	_hw_fifo3_inst(device_ids->hw_fifo3)
{
	_n = 0;
	_hw_fifos[0] = &_hw_fifo0_inst;
	_hw_fifos[1] = &_hw_fifo1_inst;
	_hw_fifos[2] = &_hw_fifo2_inst;
	_hw_fifos[3] = &_hw_fifo3_inst;
	_sample_rate_gpio_inst.write(2*1000*1000);

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

	for (int ii = 0; ii < NUM_CHANNELS; ii++)
	{
		_waveform_generators[ii] = new sine_generator(&_cmd, ii); // Set them all to sine to begin with
	}
}

void tasks::run()
{
	states_t cur_state = RELEASE_RESET;
	  while (1)
	  {
		switch(cur_state)
		{
		  case RELEASE_RESET:
			DEBUG_MSG("RELEASE_RESET state");
			_reset_inst.deassert();
			cur_state = PET_WDT;
			break;
		  case PET_WDT:
			DEBUG_MSG("PET_WDT state");
			_wdt_inst.pet();
			cur_state = RECV_CMD;
			break;
		  case RECV_CMD:
			DEBUG_MSG("RECV_CMD state");
			update_patterns();
			cur_state = SEND_RESP;
			break;
		  case SEND_RESP:
			DEBUG_MSG("SEND_RESP state");
			cur_state = SEND_SAMPLES;
			break;
		  case SEND_SAMPLES:
			DEBUG_MSG("SEND_SAMPLES state");
			send_samples();
			cur_state = PET_WDT;
			break;
		  default:
			cerr << "Unknown task" << endl;
			return;
		}
	  }
}

void tasks::update_patterns()
{
	static pattern_t last_pattern[NUM_CHANNELS];
	for (int ii = 0; ii < NUM_CHANNELS; ii++)
	{
		if (_cmd.get_pattern(ii) != last_pattern[ii]) // Only re-allocate pattern if it changed from last time
		{
			delete _waveform_generators[ii]; // De-allocate the old one
			switch (_cmd.get_pattern(ii))
			{
				case PATTERN_SINE:
					_waveform_generators[ii] = new sine_generator(&_cmd, ii);
					break;
				case PATTERN_SQUARE:
					_waveform_generators[ii] = new square_generator(&_cmd, ii);
					break;
				case PATTERN_TRIANGLE:
					_waveform_generators[ii] = new triangle_generator(&_cmd, ii);
					break;
				case PATTERN_SAWTOOTH:
					_waveform_generators[ii] = new sawtooth_generator(&_cmd, ii);
					break;
				default:
					cerr << "Unsupported pattern" << endl;
					break;
			}
			last_pattern[ii] = _cmd.get_pattern(ii);
		}
	}
}

void tasks::send_samples()
{
	for (int ii = 0; ii < NUM_CHANNELS; ii++)
	{
		int sample = _waveform_generators[ii]->calculate_sample(_n);
		_hw_fifos[ii]->push(sample);
	}
	_n++;
}

tasks::~tasks()
{

}
