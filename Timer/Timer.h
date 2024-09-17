#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include <string>
#include <chrono>

const int TARGET_FPS = 120;
const float TARGET_DELTATIME = 1.0f;

class Timer
{
    public:
        Timer();
        void Tick();
        inline float GetDeltaTime() { return m_DeltaTime; }
        inline void Restart() { m_DeltaTime = 0; m_LastTime = 0; }
        //inline static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

    private:
        //static Timer* s_Instance;
        float m_DeltaTime;
        float m_LastTime;
};

class GameTimer{

public:
    GameTimer();
    void start();
	void stop();
	void restart();
	void pause();
	void unpause();

	uint32_t getTicks();

	bool isStarted();
	bool isPaused();

	std::string saveTimer();
	void loadTimer(uint32_t start, uint32_t pause, bool started, bool paused);
	void loadTimerFromStr(std::string start_ticks, std::string pause_ticks, std::string started, std::string paused, std::string savedTimeSec);

private:

	uint32_t mStartTicks;
	uint32_t mPausedTicks;

	bool mPaused;
	bool mStarted;

	 std::chrono::system_clock::time_point mSavedTime; //Stores real world time

};




class WorldTimer {
public:
    float currentTime; // Current time in the game world, in seconds
    bool mStarted; // To track if the timer is running
    bool mPaused; // To track if the timer is paused
    float pausedTime; // Track how long the game has been paused
    float startTime; // The time when the timer was last started
    float deltaTime; // Time elapsed between updates
    float timeScale;

    WorldTimer() : currentTime(0.0f), mStarted(false), mPaused(false), pausedTime(0.0f), startTime(0.0f), deltaTime(0.0f), timeScale(0.005) {}

    // Start the timer
    void start() {
        mStarted = true;
        mPaused = false;
        startTime = currentTime; // Record the start time based on current in-game time
    }

    // Pause the timer
    void pause() {
        if (mStarted && !mPaused) {
            mPaused = true;
            pausedTime = currentTime; // Store the time when it was paused
        }
    }

    // Resume the timer
    void resume() {
        if (mPaused) {
            mPaused = false;
            startTime += (currentTime - pausedTime); // Adjust the start time when resuming
        }
    }

    // Stop the timer
    void stop() {
        mStarted = false;
        mPaused = false;
    }

    // Update the timer with delta time (time passed since last frame)
    void update(float deltaTime) {
        if (mStarted && !mPaused) {
            currentTime += deltaTime * timeScale; // Increment game time by the time passed in the game world
        }
    }

    // Get current in-game time in seconds
    float getTime() const {
        return currentTime;
    }

    // Save the current time to a file or string
    std::string saveTimer() {
        return std::to_string(currentTime); // Only save the game world time
    }

    // Load the saved time
    void loadTimerFromStr(const std::string& savedTime) {
        currentTime = std::stof(savedTime); // Restore saved game world time
    }

    bool isStarted(){ return mStarted; }
};




#endif // TIMER_H
