#include <iostream>
#include <queue>
#include "debug.hpp"
#include "message_queue.hpp"
#include "tasks.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Starting r5_ui" << endl;
	device_ids_t device_ids_inst =
	{
		XPAR_AXI_GPIO_0_DEVICE_ID,
	};
	tasks tasks_inst(&device_ids_inst);
	tasks_inst.run();

	return 0;
}
