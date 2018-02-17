#include "../server/exe_headers.h"
#include "Timer.h"


int last_timestamp = 0;
int stored_total_time = 0;
int stored_level_time = 0;
volatile int current_total_time = 0;
volatile int current_level_time = 0;
bool paused = true;


void SpeedrunPrintTime(char const *description, int milliseconds)
{
	constexpr int HOUR_IN_MILLISECONDS = 1000 * 60 * 60;
	constexpr int MINUTE_IN_MILLISECONDS = 1000 * 60;
	constexpr int SECOND_IN_MILLISECONDS = 1000;

	int const hours = milliseconds / HOUR_IN_MILLISECONDS;
	milliseconds %= HOUR_IN_MILLISECONDS;
	int const minutes = milliseconds / MINUTE_IN_MILLISECONDS;
	milliseconds %= MINUTE_IN_MILLISECONDS;
	int const seconds = milliseconds / SECOND_IN_MILLISECONDS;
	milliseconds %= SECOND_IN_MILLISECONDS;

	if (hours > 0)
	{
		Com_Printf("%s%i:%02i:%02i.%03i\n",
		           description, hours, minutes, seconds, milliseconds);
	}
	else
	{
		Com_Printf("%s%02i:%02i.%03i\n",
		           description, minutes, seconds, milliseconds);
	}
}

void SpeedrunResetTimer()
{
	last_timestamp = 0;
	stored_total_time = 0;
	stored_level_time = 0;
	current_total_time = 0;
	current_level_time = 0;
	paused = true;
}

void SpeedrunUpdateTimer()
{
	if (paused)
	{
		return;
	}
	
	int const current_timestamp = Sys_Milliseconds();
	current_total_time = stored_total_time + (current_timestamp - last_timestamp);
	current_level_time = stored_level_time + (current_timestamp - last_timestamp);
}

void SpeedrunUnpauseTimer()
{
	paused = false;
	last_timestamp = Sys_Milliseconds();
}

bool SpeedrunPauseTimer()
{
	if (paused)
	{
		return true;
	}

	int const current_timestamp = Sys_Milliseconds();
	stored_total_time += (current_timestamp - last_timestamp);
	stored_level_time += (current_timestamp - last_timestamp);
	current_total_time = stored_total_time;
	current_level_time = stored_level_time;
	last_timestamp = current_timestamp;
	paused = true;
	return false;
}

void SpeedrunLevelFinished()
{
	if (!paused)
	{
		int const current_timestamp = Sys_Milliseconds();
		stored_total_time += (current_timestamp - last_timestamp);
		stored_level_time += (current_timestamp - last_timestamp);
		current_total_time = stored_total_time;
		current_level_time = stored_level_time;
		last_timestamp = current_timestamp;
	}

	SpeedrunPrintTime(S_COLOR_RED "=========================\n"
	                  S_COLOR_GREEN "Level time: " S_COLOR_WHITE, current_level_time);
	if (current_level_time != current_total_time)
	{
		SpeedrunPrintTime(S_COLOR_GREEN "Total time: " S_COLOR_WHITE, current_total_time);
	}
	Com_Printf(S_COLOR_RED "=========================\n");

	stored_level_time = 0;
}
