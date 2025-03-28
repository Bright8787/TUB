#include "../lib/RR.h"

static queue_object *RR_queue;
// You can add more global variables
int quantum_global;
static int quantum_counter = 0;

process *RR_tick(process *running_process)
{
	// TODO
	if (running_process == NULL || running_process->time_left == 0 || quantum_counter == quantum_global)
	{
		if (running_process != NULL && running_process->time_left > 0)
		{
			queue_add(running_process, RR_queue);
		}
		running_process = queue_poll(RR_queue);
		// reset quantum counter
		quantum_counter = 0;
	}

	if (running_process != NULL)
	{
		running_process->time_left--;
		// add Quantum number
		quantum_counter++;
	}

	return running_process;
}

int RR_startup(int quantum)
{
	// TODO
	quantum_global = quantum;
	RR_queue = new_queue();
	if (RR_queue == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

process *RR_new_arrival(process *arriving_process, process *running_process)
{
	// TODO
	if (arriving_process != NULL)
	{
		queue_add(arriving_process, RR_queue);
	}
	return running_process;
}

void RR_finish()
{
	// TODO
	free_queue(RR_queue);
}
