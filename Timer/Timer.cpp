#include "Timer.h"

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif // _WIN32

//Timer* Timer::s_Instance = nullptr;

Timer::Timer(){

}

void Timer::Tick(){

    m_DeltaTime = (SDL_GetTicks() - m_LastTime) * (TARGET_FPS/1000.0f);

    if(m_DeltaTime > TARGET_DELTATIME){

        m_DeltaTime = TARGET_DELTATIME;
    }

    m_LastTime = SDL_GetTicks();
}



/*

        OLD GHAME TIMER CLASS....

*/


GameTimer::GameTimer() : mStartTicks(0), mPausedTicks(0), mStarted(false), mPaused(false){
}


void GameTimer::start(){

	mStarted = true;
	mPaused = false;

	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void GameTimer::stop(){

	mStarted = false;
	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void GameTimer::restart(){

    stop();
    start();
}

void GameTimer::pause(){

	if (mStarted && !mPaused) {

		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;

		mStartTicks = 0;
	}
}

void GameTimer::unpause(){

	if (mStarted && mPaused) {

		mPaused = false;

		mStartTicks = SDL_GetTicks() - mPausedTicks;

		mPausedTicks = 0;
	}
}

uint32_t GameTimer::getTicks(){

	uint32_t time = 0;

	//Check timer is running
	if (mStarted) {

		if (mPaused) {

			time = mPausedTicks;
		}
		else {

			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool GameTimer::isStarted(){

	return mStarted;
}

bool GameTimer::isPaused(){

	return mPaused && mStarted;
}

std::string GameTimer::saveTimer(){

     std::string msg = "";

        // Get current time in seconds since epoch
        auto currentTime = std::chrono::system_clock::now();
        auto currentTimeSec = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();

        msg += std::to_string(mStartTicks) + " " + std::to_string(mPausedTicks) + " " +
               std::to_string(mStarted) + " " + std::to_string(mPaused) + " " +
               std::to_string(currentTimeSec);

        return msg;
}

void GameTimer::loadTimer(uint32_t start_ticks, uint32_t pause_ticks, bool started, bool paused){

    mStartTicks = start_ticks;
    mPausedTicks = pause_ticks;
    mStarted = started;
    mPaused = paused;
}

void GameTimer::loadTimerFromStr(std::string start_ticks, std::string pause_ticks, std::string started, std::string paused, std::string savedTimeSec){

     mStartTicks = static_cast<uint32_t>(std::stoul(start_ticks));
    mPausedTicks = static_cast<uint32_t>(std::stoul(pause_ticks));
    mStarted = std::stoi(started);
    mPaused = std::stoi(paused);

    // Convert saved time (in seconds) back to a time_point
    auto savedTime = std::chrono::system_clock::time_point(std::chrono::seconds(std::stoul(savedTimeSec)));

    // Get the current real-world time
    auto currentTime = std::chrono::system_clock::now();

    // Calculate the difference between the saved time and the current time
    auto timePassed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - savedTime).count();

    // Apply the difference to the ticks if the game was running
    if (mStarted && !mPaused) {
        mStartTicks += static_cast<uint32_t>(timePassed * 1000); // Convert seconds to milliseconds and adjust ticks
    }
}






