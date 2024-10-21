#ifndef ENGINE_H
#define ENGINE_H

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif // _WIN32


#include <vector>
#include <memory>

#include "State.h"
#include "json.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960

class Engine{

public:

    static Engine* GetInstance(){       //Checks if object is created, if true returns object if false create object

            return s_Instance = (s_Instance != nullptr) ?  s_Instance : new Engine();
        }

        bool Init();
        bool Clean();
        void Quit();

        void Update(float dt);
        void UpdateEvents(SDL_Event &event);
        void Render();
        void Events();

        inline bool IsRunning() { return m_IsRunning; }
        inline SDL_Renderer* GetRenderer() { return m_Renderer; }
        inline SDL_Window* GetWindow() { return m_Window; }
        inline void AddState(std::shared_ptr<State> s) { mStates.push_back(s); currentState++; }
        inline void PopState(){ if(!mStates.empty()){ mStates.pop_back(); currentState--; }}

        inline const int getCurrentState(){ return currentState; }

private:

        Engine(){}
        bool m_IsRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance; //static object ptr singleton



        ///TEST
        ///Probably need an InitStateData function...
        std::vector<std::shared_ptr<class State>> mStates;
        int currentState;
//        GameMap* m_LevelMap;
};

#endif // ENGINE_H

