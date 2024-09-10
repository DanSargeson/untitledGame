#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include <string>

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

private:

	uint32_t mStartTicks;
	uint32_t mPausedTicks;

	bool mPaused;
	bool mStarted;

};

#endif // TIMER_H
