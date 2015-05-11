#include "Timer.h"


Timer::Timer()
{
	//Initialize the variables
	_StartTicks = 0;
	_PausedTicks = 0;

	_Paused = false;
	_Started = false;
}

void Timer::start()
{
	//Start the timer
	_Started = true;

	//Unpause the timer
	_Paused = false;

	//Get the current clock time
	_StartTicks = SDL_GetTicks();
	_PausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer
	_Started = false;

	//Unpause the timer
	_Paused = false;

	//Clear tick variables
	_StartTicks = 0;
	_PausedTicks = 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if (_Started && !_Paused)
	{
		//Pause the timer
		_Paused = true;

		//Calculate the paused ticks
		_PausedTicks = SDL_GetTicks() - _StartTicks;
		_StartTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused
	if (_Started && _Paused)
	{
		//Unpause the timer
		_Paused = false;

		//Reset the starting ticks
		_StartTicks = SDL_GetTicks() - _PausedTicks;

		//Reset the paused ticks
		_PausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (_Started)
	{
		//If the timer is paused
		if (_Paused)
		{
			//Return the number of ticks when the timer was paused
			time = _PausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - _StartTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return _Started;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return _Paused && _Started;
}
