#include "../server/exe_headers.h"
#include "Timer.h"


int last_timestamp = 0;
int stored_total_time = 0;
int stored_level_time = 0;
volatile int current_total_time = 0;
volatile int current_level_time = 0;
bool paused = true;

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
	if (paused)
	{
		paused = false;
		last_timestamp = Sys_Milliseconds();
	}
}

void SpeedrunStoreCurrentTime()
{
	int const current_timestamp = Sys_Milliseconds();
	stored_total_time += (current_timestamp - last_timestamp);
	stored_level_time += (current_timestamp - last_timestamp);
	current_total_time = stored_total_time;
	current_level_time = stored_level_time;
	last_timestamp = current_timestamp;
}

bool SpeedrunPauseTimer()
{
	if (paused)
	{
		return true;
	}

	SpeedrunStoreCurrentTime();
	paused = true;
	return false;
}

void SpeedrunLevelFinished()
{
	if (!paused)
	{
		SpeedrunStoreCurrentTime();
	}

	constexpr int PRINT_ACCURACY = 3;
	std::string time_string = GetTimeStringFromMilliseconds(current_level_time,
	                                                        PRINT_ACCURACY);
	Com_Printf(S_COLOR_RED "=========================\n"
	           S_COLOR_GREEN "Level time: " S_COLOR_WHITE "%s\n",
			   time_string.c_str());
	if (current_level_time != current_total_time)
	{
		time_string = GetTimeStringFromMilliseconds(current_total_time,
		                                            PRINT_ACCURACY);
		Com_Printf(S_COLOR_GREEN "Total time: " S_COLOR_WHITE "%s\n",
		           time_string.c_str());
	}
	Com_Printf(S_COLOR_RED "=========================\n");

	stored_level_time = 0;
}

int SpeedrunGetTotalTimeMilliseconds()
{
	return current_total_time;
}

int SpeedrunGetLevelTimeMilliseconds()
{
	return current_level_time;
}
