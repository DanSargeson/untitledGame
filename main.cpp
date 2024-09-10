#include "Engine.h"
#include "Timer.h"

int main(int argc, char** argv){

    auto gameTimer = std::make_unique<Timer>();

    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning()){

            Engine::GetInstance()->Events();
            Engine::GetInstance()->Update(gameTimer->GetDeltaTime());
            Engine::GetInstance()->Render();
            gameTimer->Tick();
    }

    Engine::GetInstance()->Clean();

    return 0;
}


