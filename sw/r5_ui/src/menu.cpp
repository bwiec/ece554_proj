#include "menu.hpp"

menu::menu(command* cmd)
{
	_cmd = cmd;
	_new_input_available = false;
}

void menu::print()
{
	print_header();
	cout << " --- Main Menu (type a letter followed by enter):" << endl;
	cout << "c: Channel enable" << endl;
	cout << "s: Sample Rate" << endl;
	cout << "f: Frequency" << endl;
	cout << "p: Pattern" << endl;
	cout << "m: Misc (pattern-specific)" << endl;
	cout << "q: Quit" << endl;
}

void menu::print_header()
{
	cout << "***********************" << endl;
	cout << "* ece554_proj - bwiec *" << endl;
	cout << "***********************" << endl;
	cout << endl;
}

void menu::get_user_input() // This should be a non-blocking function to allow switching of tasks
{
	DEBUG_MSG("Getting user input");
	prompt();
	char c = get_character();
	DEBUG_MSG("c: " << c);
	if (c == 'c')
	{
		submenu_channel_enable();
	}
	else if (c == 's')
	{
		submenu_sample_rate();
	}
	else if (c == 'f')
	{
		submenu_frequency();
	}
	else if (c == 'p')
	{
		submenu_pattern();
	}
	else if (c == 'm')
	{
		submenu_misc();
	}
	else
	{
		return;
	}
	DEBUG_MSG("Done getting user input");
}

char menu::get_character()
{
	//return getchar();
	char c;
	cin >> c;
	return c;
}

unsigned int menu::get_number(int max_digits)
{
	DEBUG_MSG("Getting number");
	char digits[32];
	int digit_idx = 0;
	char c = get_character();
	while (c != '\n')
	{
		if (digit_idx > max_digits)
		{
			break;
		}
		digits[digit_idx] = c - '0';
		c = get_character();
	}
	unsigned char val = 0;
	sprintf(digits, "%d", (int)val);

	DEBUG_MSG("val: " << val);
	DEBUG_MSG("Done getting number");

	return val;
}

unsigned char menu::submenu_channel_select()
{
	cout << "which channel do you want to modify (type a number from 0 to " << NUM_CHANNELS-1 << "): " << endl;
	char c = get_character();
	return (c - '0');
}

void menu::submenu_channel_enable()
{
	cout << "--- Channel Enable Menu (type a number from 0 to 4 to toggle channel enable): " << endl;
	char c = get_character();
	unsigned char idx = c - '0';
	if (_cmd->get_channel_is_enabled(idx))
	{
		_cmd->clr_channel_is_enabled(idx);
	}
	else
	{
		_cmd->set_channel_is_enabled(idx);
	}
	_new_input_available = true;
}

void menu::submenu_sample_rate()
{
	unsigned char idx = submenu_channel_select();
	cout << "--- Sample Rate Menu (type a number from 0 to 100000 to set the sample rate): " << endl;
	_cmd->set_sample_rate(idx, get_number(5));
	_new_input_available = true;
}

void menu::submenu_frequency()
{
	unsigned char idx = submenu_channel_select();
	cout << "--- Frequency Menu (type a number from 0 to " << (int)(_cmd->get_sample_rate((int)idx))/2 << " to set the frequency): " << endl;
	_cmd->set_frequency(idx, get_number(4));
	_new_input_available = true;
}

void menu::submenu_pattern()
{
	unsigned char idx = submenu_channel_select();
	cout << "--- Pattern Menu (type a number from 0 to " << NUM_PATTERNS-1 << " to set the pattern): " << endl;
	_cmd->set_pattern(idx, (pattern_t)get_number(1));
	_new_input_available = true;
}

void menu::submenu_misc()
{
	unsigned char idx = submenu_channel_select();
	cout << "--- Pattern-specific Menu (type a number from 0 to 2^32 to set the pattern-specific value): " << endl;
	_cmd->set_pattern_specific(idx, get_number(32));
	_new_input_available = true;
}

void menu::prompt()
{
	cout << ">> ";
}

void menu::consumed()
{
	_new_input_available = false;
}

menu::~menu()
{

}
