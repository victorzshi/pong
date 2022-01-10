#pragma once

class Timer
{
public:
	Timer();

	void start();

	Uint32 get_elapsed_time();

private:
	Uint32 start_time;
};
