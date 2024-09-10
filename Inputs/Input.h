#ifndef INPUT_H
#define INPUT_H

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif // WIN32

class Input{

    public:

        static Input* GetInstance(){       //Checks if object is created, if true returns object if false create object

            return s_Instance = (s_Instance != nullptr) ?  s_Instance : new Input();
        }

        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        bool GetKeyUp(SDL_Scancode key);

    private:
        Input();
        void KeyUp();
        void KeyDown();

        const Uint8* m_KeyState;

        static Input* s_Instance;
};

#endif // INPUT_H
