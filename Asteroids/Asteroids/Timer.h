#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

//The application time based timer
class Timer
{
public:
	//Initializes variables
	Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 _StartTicks;

	//The ticks stored when the timer was paused
	Uint32 _PausedTicks;

	//The timer status
	bool _Paused;
	bool _Started;
};
#endif

