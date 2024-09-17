#include "GraphicRandomEncounter.h"
#include "RandomEncounter.h"
#include "Battle.h"
#include "Church.h"
#include "Sheol.h"
#include "Emesh.h"

GraphicRandomEncounter::GraphicRandomEncounter() : State(){
    //ctor

    unsigned int charSize = GUI::calcCharSize(125);
    mButtons["BACK"] = std::make_shared<GUI::Button>(5.f, 93.f, 11.8f, 6.1f, charSize);
    mButtons["BACK"]->setRenderText("Back");

    for (auto button : mButtons) {

		button.second->setBackgroundTexture("Assets/Background/button2.png");
	}

    SDL_ShowCursor(SDL_ENABLE);
    backButton->setActive(false);

    ///CHANGE HERE FOR TILES ///GRIDSIZE - THIS IS THE ONE
    StateData::GetInstance()->gridSize = 64;
    StateData::GetInstance()->gridSizeF = 64.f;
    this->mapTextureStr = "Assets/tilesBIG3.png";
	int maxSizeX = 27;   //15
	int maxSizeY = 15;
	StateData::GetInstance()->createCamera(2000); ///TODO: MAGIC NUMBER

	tileInfo = std::make_shared<GUI::Tooltip>();
	tileInfo->setHidden(false);

			this->tilemap = std::make_shared<TileMap>(Engine::GetInstance()->GetRenderer(), StateData::GetInstance()->gridSizeF, maxSizeX, maxSizeY, this->mapTextureStr);

//            int rando = getRandomValue(1, 100);
//            if(rando <= 60){
//
//                int roll = getRandomValue(1, 5);
//                tilemap->runMazeGenerator();
//                tilemap->placeTreasure(4, roll);
//            }
//            else{
//
//                int roll = getRandomValue(40, 70);
//                this->tilemap->runPerfectMazeGenerator();
//                this->tilemap->placeTreasure(6, roll);
//            }

            tilemap->LoadFromFile("MAP1");
}

GraphicRandomEncounter::~GraphicRandomEncounter(){
    //dtor
    backButton->setActive(true);
    worldTimerText->setPosition(GUI::p2pX(55), GUI::p2pY(20));
    //tilemap->clear();
    //tilemap.reset();
}

void GraphicRandomEncounter::updateEvents(SDL_Event& e){

    float time = .25f;

//    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
//
//                StateData::GetInstance()->moveCam2(1, time);
//                //StateData::GetInstance()->updateCamera();
//            }
//
//            if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
//
//                    StateData::GetInstance()->moveCam2(2, time);
//            }
//
//
//			if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
//
//                StateData::GetInstance()->moveCam2(4, time);
//			}
//
//			if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)){
//
//                StateData::GetInstance()->moveCam2(3, time);
//			}
//
//
//    if(e.type == SDL_KEYUP && e.key.repeat == 0){
//
//            switch(e.key.keysym.sym){
//
//                case SDLK_a: StateData::GetInstance()->moveCam2(FREEZE, 0);
//                break;
//
//                case SDLK_d: StateData::GetInstance()->moveCam2(FREEZE, 0);
//                break;
//
//                case SDLK_w: StateData::GetInstance()->moveCam2(FREEZE, 0);
//                break;
//
//                case SDLK_s: StateData::GetInstance()->moveCam2(FREEZE, 0);
//                break;
//            }
//    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E) && e.key.repeat == 0){

        tileInfo->setHidden(!tileInfo->getHidden());

        return;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN){


        if(mButtons["BACK"]->isPressed(e.button)){

            Engine::GetInstance()->PopState();

            return;
        }

        int x, y = 0;
    SDL_GetMouseState(&x, &y);

            x /= StateData::GetInstance()->gridSize;
            y /= StateData::GetInstance()->gridSize;

        int newX = StateData::GetInstance()->getCamera().x / StateData::GetInstance()->gridSize;
        int newY = StateData::GetInstance()->getCamera().y / StateData::GetInstance()->gridSize;
        newX += x;

        newY += y;
        int type = tilemap->getTileType(newX, newY, 0);


        ///TODO: HERE IS WHERE YOU HAVE THE NUMBERS LOCKED (SO SHOULD BE SIMILAR FOR THE START OF THE GAME (NEED TO CHANGE IT IN TILEMAP AS WELL))
        ///TODO:: Bring the bellow back
        //if(type == 2 || type == 3 || type == 4){
            if(type == 2){ ///PUB
                int r = getRandomValue(2, 8);       ///TODO make a "getRandomFaction" function which checks for faction unlocks...
            Engine::GetInstance()->AddState(std::make_shared<RandomEncounter>(r));
        }
        else if(type == TILE::CHURCH_TILE){

            Engine::GetInstance()->AddState(std::make_shared<Church>());
        }
        else if(type == TILE::SHEOL_TILE){

            Engine::GetInstance()->AddState(std::make_shared<Sheol>());
        }
        else if(type == TILE::EMESH_TILE){

            Engine::GetInstance()->AddState(std::make_shared<Emesh>());
        }

        else if(type == 9){

            //Engine::GetInstance()->PopState();
//            if(getData()->isDay){
//
//                getMainText()->setString("A mysterious looking rock blocks the path..");
//
//            }
            //else{

                Engine::GetInstance()->AddState(std::make_shared<Battle>());
            //}
        }
    }

//    mButtons["BACK"]->update();

    State::updateEvents(e);
}

void GraphicRandomEncounter::refreshGUI(){

   /// StateData::GetInstance()->createCamera(2000);
   StateData::GetInstance()->camera->setCameraDimensions(StateData::GetInstance()->getCamera().x, StateData::GetInstance()->getCamera().y,
                                                         SDL_GetWindowSurface(Engine::GetInstance()->GetWindow())->w, SDL_GetWindowSurface(Engine::GetInstance()->GetWindow())->h);


    //StateData::GetInstance()->updateCamera();
}

void GraphicRandomEncounter::update(const float& dt)
{

    mButtons["BACK"]->update();
    if(!SDL_ShowCursor(SDL_QUERY)){

        SDL_ShowCursor(SDL_ENABLE);
    }
    StateData::GetInstance()->updateCamera(dt);
    int x, y = 0;
    SDL_GetMouseState(&x, &y);

            ///CONTROLS THE MOUSE GRID THING???
            int gr = StateData::GetInstance()->gridSize;
            x /= StateData::GetInstance()->gridSize;
            y /= StateData::GetInstance()->gridSize;

       int newX = StateData::GetInstance()->getCamera().x / StateData::GetInstance()->gridSize;
       int newY = StateData::GetInstance()->getCamera().y / StateData::GetInstance()->gridSize;

       newX += x;
       newY += y;

       if(newX >= tilemap->getMaxSizeGrid().x || newY >= tilemap->getMaxSizeGrid().y){

        if(!tileInfo->getHidden()){
//                int type = tilemap->getTileType(tilemap->getMaxSizeGrid().x, tilemap->getMaxSizeGrid().y, 0);
//                std::string msg = tilemap->getTileTypeStr(type);
//                if(msg == "Unknown tile string"){
//
//                    return;
//                }
//                tileInfo->update();
//                tileInfo->setDisplayText(msg);

                tileInfo->setHidden(true);
                tileInfo->update();
            }
       }
       else{

            if(tileInfo->getHidden()){

                tileInfo->setHidden(false);
            }

            int type = tilemap->getTileType(newX, newY, 0);
            std::string msg = tilemap->getTileTypeStr(type);
            tileInfo->setDisplayText(msg);
            tileInfo->update();
       }

       getActiveCharacter()->getWorldTimer()->update(dt);
       calcWorldTime();
}

void GraphicRandomEncounter::render(){


    //TODO: Need to offset where tilemap renders to give a bit of room at the top of the screen...
    tilemap->render(Engine::GetInstance()->GetRenderer(), StateData::GetInstance()->getCamera());


    tileInfo->render();

    for(auto button : mButtons){

        button.second->renderButtons();
    }

    worldTimerText->setPosition(GUI::p2pX(55), GUI::p2pY(93));
    worldTimerText->render();
}

