#include "Input.h"
#include "Engine.h"

#include <iostream>

Input* Input::s_Instance = nullptr;

Input::Input(){

    m_KeyState = SDL_GetKeyboardState(nullptr);
}

void Input::Listen(){

    SDL_Event event;

    while(SDL_PollEvent(&event)){

        switch(event.type){

            case SDL_QUIT:
                Engine::GetInstance()->Quit();
                break;

            case SDL_KEYDOWN:
                KeyDown();
                Engine::GetInstance()->UpdateEvents(event);
                break;

            case SDL_KEYUP:
                KeyUp();
                Engine::GetInstance()->UpdateEvents(event);
                break;

            case SDL_MOUSEBUTTONDOWN:
                 Engine::GetInstance()->UpdateEvents(event);
                //Engine::GetInstance()->m_LevelMap
                //get tile co-ords
                break;

            case SDL_MOUSEMOTION:
                 Engine::GetInstance()->UpdateEvents(event);
                break;

            default:
                Engine::GetInstance()->UpdateEvents(event);

        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key){


    return m_KeyState[key] == 1;
//    if(m_KeyStates[key] == 1){
//
//        return true;
//    }
//
//    return false;
}

bool Input::GetKeyUp(SDL_Scancode key){


    return m_KeyState[key] == 0;
//    if(m_KeyStates[key] == 1){
//
//        return true;
//    }
//
//    return false;
}

void Input::KeyUp(){

    m_KeyState = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(){

     m_KeyState = SDL_GetKeyboardState(nullptr);
}


