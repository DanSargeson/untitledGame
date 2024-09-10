#include "Engine.h"
#include "Input.h"
#include "MainMenu.h"
#include <iostream>

//#include <SDL2/SDL.h>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init(){

    currentState = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0){

        SDL_Log("Failed to initialise SDL: %s", SDL_GetError());

        return false;
    }

    if(!TTF_Init() == 0){

        std::cout << "Error loading TTF_Font" << std::endl;
    }

    if(SDL_Init(SDL_INIT_AUDIO) != 0){

        std:: cout << "Failed to initialise audio!" << std::endl;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0){

///        std::cout << "Mixer works!" << std::endl;
    }
    else{

        std::cerr << "Mix open audio failed: " << Mix_GetError() << std::endl;
    }

    m_Window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if(m_Window == nullptr){

        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

///TESTING

    return m_IsRunning = true;
}

bool Engine::Clean(){

//    TextureManager::GetInstance()->Clean();
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
   // Mix_Quit();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    return true;
}

void Engine::Quit(){

    m_IsRunning = false;
}

void Engine::Update(float dt){


    if(!mStates.empty()){

        if(currentState > 0){

            mStates[currentState]->update(dt);
        }
    }
    else{

        mStates.push_back(std::make_shared<MainMenu>());
        //currentState++;
    }
}

void Engine::UpdateEvents(SDL_Event &event){

    if(!mStates.empty()){

        mStates[currentState]->updateEvents(event);

    }

    if(event.window.event == SDL_WINDOWEVENT_RESIZED){

        if(!mStates.empty()){

            for(unsigned i = 0; i < mStates.size(); i++){

                mStates[i]->refreshGUI();
            }
        }
    }
}

void Engine::Render(){

    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
    SDL_RenderClear(m_Renderer);
    if(!mStates.empty()){

        mStates[currentState]->render();
    }
    else{

        SDL_SetRenderDrawColor(m_Renderer, 200, 127, 0, 25);
        SDL_RenderClear(m_Renderer);
    }

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events(){

    Input::GetInstance()->Listen();
}


