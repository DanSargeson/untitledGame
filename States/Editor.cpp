#include "Editor.h"
#include "Input.h"
///#include "PauseMenuState.h"

Editor::Editor() : State(){


	this->InitVariables();
	this->InitBackground();
	InitFonts();
	this->InitText();
	this->InitKeyBinds();
	this->InitPauseMenu();
	this->InitTileMap();
	this->InitFileMenu();
	this->InitButtons();
	this->InitView();
	this->InitGUI();

	camMovement = false;
	mPaused = false;

	firstRun = true;
}

Editor::~Editor(){

	firstRun = true;
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {

		delete it->second;
	}

//	delete cursorText;

	//delete this->pMenu;
	//delete this->fileMenu;
//	delete this->tileMap;
//	delete this->textureSelector;
}

void Editor::toggleTileLock(){

	if (lockTiles) {

		lockTiles = false;
	}
	else
		lockTiles = true;
}


//INITIALISERS

void Editor::InitVariables() {

	//this->width = static_cast<int>(this->stateData->gridSize);
	//this->height = static_cast<int>(this->stateData->gridSize);
	this->layer = 0;

	hidden = true;

	this->bigMap = true;		//SECOND PLACE THAT GRIDSIZE IS SET OTHER IS STATE.H ./OVERRIDEN BY RANDOMGRAPHIC ENCOUNTER...
	if (bigMap) {

		StateData::GetInstance()->gridSize = 64;
		StateData::GetInstance()->gridSizeF = 64.f;
	}
	else {

		//StateData::GetInstance()->gridSize = 32;
		//StateData::GetInstance()->gridSizeF = 32.f;
	}

	this->mapTextureStr = " ";

	this->firstRun = true;
	this->lockTiles = true;

	this->cameraSpeed = 64.f;

	this->collision = false;
	this->type = TILE_TYPES::DEFAULT;
	this->teleport = false;
	this->destination = " ";

	this->maxTileTypes = TILE_TYPES::TOTAL_TILES;		//TODO - THIS NEEDS TO BE CHANGED SO TILE TYPES CAN BE CHANGED DYNAMICALLY

	textureRect.x = 0;
	textureRect.y = 0;
	textureRect.w = 64;
	textureRect.h = 64;

//	textureSelector->setActive(false);

	//this->fileMenu = false;
	this->save = false;
	this->load = false;
}

void Editor::InitView(){

    ///TODO sort this
    int maxSize = 2000;
  ///  int maxSize = (this->tileMap->getMaxSizeGrid().x); //TODO MAGIC NUMBERS NEED TO GET TILEMAP MAX SIZE...
    StateData::GetInstance()->createCamera(maxSize);
	/*this->zoomFactor = 0.3f;

	this->mainView.zoom(zoomFactor);*/

	//this->mainView.setSize(
	//	sf::Vector2f(static_cast<float>(this->stateData->gfxSettings->resolution.width),
	//		static_cast<float>(this->stateData->gfxSettings->resolution.height)));


	//this->mainView.setCenter(
	//	static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
	//	static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f);

	//this->mainView.move(-500.f, -250.f);
	//this->mainView.zoom(0.3f);
}

void Editor::InitBackground() {


}

void Editor::InitFonts() {

	//if (!this->font.loadFromFile("Fonts/SF Atarian System.ttf")) {

	//	throw("ERROR: EDITOR FAILED TO LOAD FONT\n");
	//}
	const char* fontFile = "Assets/Fonts/SF Atarian System.ttf";
	this->font = TTF_OpenFont(fontFile, 16);
}

void Editor::InitText(){


	//cursorText = new Texture();
	cursorText = std::make_shared<Texture>();
	cursorText->setBlendMode(SDL_BLENDMODE_BLEND);
	//mouseText.setColor(sf::Color::Yellow);
}

void Editor::InitKeyBinds() {

	std::ifstream ifs("Config/editorKeyBinds.ini");

	if (ifs.is_open()) {

		std::string key = " ";
		std::string key2 = " ";

		while (ifs >> key >> key2) {

//			this->keyBinds[key] = this->supportedKeys->at(key2);
			//sf::Keyboard::Key
		}
	}

	ifs.close();
}

void Editor::InitButtons() {

	//unsigned charSize = 30;
	//const sf::VideoMode vm = this->stateData->gfxSettings->resolution;

	/*this->buttons["EXIT_STATE"] = new GUI::Button(550, 525, 150, 50, &this->font, "Quit", charSize,
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50)
	);*/

	/*this->buttons["BACK"] = new GUI::Button(400, 525, 150, 50, &this->font, "Back", charSize,
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50)
	);*/
	//SDL_Window* vm = Engine::GetInstance()->GetWindow();

	this->buttons["HIDE"] = new GUI::Button(0, 0, 5, 5, 18);
	this->buttons["HIDE"]->setRenderText("Hide");

}

void Editor::InitTileMap(){


	try {

		if (bigMap) {

            StateData::GetInstance()->gridSize = 64;
            StateData::GetInstance()->gridSizeF = 64.f;
			//StateData::GetInstance()->gridSize = 64;
			//StateData::GetInstance()->gridSizeF = 64.f;
			this->mapTextureStr = "Assets/TilesBIG3.png";
		}
		else {

            StateData::GetInstance()->gridSize = 32;
            StateData::GetInstance()->gridSizeF = 32.f;
			this->mapTextureStr = "Assets/tilesBIG.png";
		}
	}
	catch(std::exception &e) {

		std::ofstream outFile;

		outFile.open("errorLog.txt");

		if (outFile.is_open()) {

			outFile << e.what() << std::endl;
		}

		outFile.close();
	}
	int tileMapMaxSizeX = 27; ///Was 15...
	int tileMapMaxSizeY = 15;
	this->tileMap = std::make_shared<TileMap>(Engine::GetInstance()->GetRenderer(), 64.f, tileMapMaxSizeX, tileMapMaxSizeY, this->mapTextureStr);
}

void Editor::InitGUI(){


	//unsigned int charSize = GUI::calcCharSize();

	int w, h;
	sidebar.w = 40;
	SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);
	sidebar.w = w;
	sidebar.h = h;

	selectorRect.x = 0;
	selectorRect.y = 0;
	selectorRect.w = 64;//StateData::GetInstance()->gridSize;
	selectorRect.h = 64;//StateData::GetInstance()->gridSize;

	selectorRectBig.x = 0;
	selectorRectBig.y = 0;
	selectorRectBig.w = 64;//StateData::GetInstance()->gridSize;
	selectorRectBig.h = 64;//StateData::GetInstance()->gridSize;

	std::string text = "Hide";
	textureSelector = std::make_unique<GUI::TextureSelector>(40.f, 0.f, 258.f, 480.f, 64.f, this->tileMap->getTileSheet(), font, text);

	SDL_Delay(200);
}

void Editor::InitPauseMenu() {

    pauseMenu = std::make_shared<GUI::textBox>();
    pauseMenu->setConfirm(true);
    pauseMenu->setSize(40, 40);
    pauseMenu->centreTextBox();
    pauseMenu->setHeader("PAUSED");
    pauseMenu->setText("Save Map?");
}

void Editor::InitFileMenu(){

	/*
		TODO:

		Create an array of filenames with all saves in, add new ones etc.

		Create a vector of strings to go in stateData which will hold all fileNames for the maps
		Load it in mainMenu along with the player data
		Have each map generate a unique save id based on the vector size + 1 (same as characters)
	*/

	//this->fileMenu = new PauseMenu(Engine::GetInstance()->GetRenderer(), *this->font);

	///loadFiles = std::make_unique<GUI::Menu>(*StateData::GetInstance());

//	this->saveData.readDirectory("Data", this->fileNames);

	//loadFiles->setDynamicMenu(fileNames, 0);
///	loadFiles->setMenuOptions(fileNames, true);
	//this->ReadDirectory("maps", this->fileNames);

	 if(std::filesystem::exists("MAP1")){
             tileMap->LoadFromFile("MAP1");

        return;
     }


		//this->fileMenu->ad

		float yPos = 45.f;
		float yOffset = 12.f;

//		SDL_Window* vm = Engine::GetInstance()->GetWindow();

		for (unsigned int i = 0; i < fileNames.size(); i++) {

			yPos += yOffset;

			std::string  strBuild = this->fileNames[i].c_str();

	//		this->fileMenu->addButton(strBuild, GUI::p2pX(62.5f, vm), GUI::p2pY(yPos, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::calcCharSize(), strBuild);
		}

//	this->fileMenu->addButton("TEST", GUI::p2pX(62.f, vm), GUI::p2pY(33.3f, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::CalcCharSize(vm), "Test.txt");
//	this->fileMenu->addButton("TEST2", GUI::p2pX(62.5f, vm), GUI::p2pY(45.8f, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::CalcCharSize(vm), "Test2.txt");
//	this->fileMenu->addButton("TEST3", GUI::p2pX(62.5f, vm), GUI::p2pY(56.8f, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::CalcCharSize(vm), "Test3.txt");
	//this->fileMenu->addButton("NEW", GUI::p2pX(62.5f, vm), GUI::p2pY(58.3f, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::CalcCharSize(vm), "New");

	//this->fileMenu->addButton("NEWSAVE", GUI::p2pX(62.5f, vm), GUI::p2pY(33.3f, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::calcCharSize(), "New Save");
	//this->fileMenu->addButton("BACK", GUI::p2pX(62.5f, vm), GUI::p2pY(45.f, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::calcCharSize(), "Back");
}


//UPDATES

void Editor::UpdateInput(const float & dt) {

	//EXIT GAME
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeyTime()) {

	//	if (!this->paused) {
	//		this->PauseState();
	//	}
	//	else {
	//		this->UnpauseState();
	//	}
	//}
}

void Editor::UpdateEditorInput(const float & dt){

	////HORIZONTAL CAMERA MOVEMENT
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {

	//	this->mainView.move(this->cameraSpeed * dt, 0.f);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {

	//	this->mainView.move(-this->cameraSpeed * dt, 0.f);
	//}

	////VERTICAL CAMERA MOVEMENT
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {

	//	this->mainView.move(0.f, -this->cameraSpeed * dt);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {

	//	this->mainView.move(0.f, this->cameraSpeed * dt);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TOGGLE_LOCK"))) && this->getKeyTime()) {

	//	this->toggleTileLock();
	//}


	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->getKeyTime()) {


		this->zoomFactor += 1.0f;
		this->mainView.zoom(zoomFactor);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->getKeyTime()) {


		this->mainView.setSize(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);

		this->zoomFactor -= 0.1f;
		this->mainView.zoom(zoomFactor);
	}*/

		//Adds a tile to the tileMap

	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


	//	if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {

	//		if (!this->textureSelector->getActive() && !this->firstRun) {

	//			if (lockTiles) {

	//				if (this->tileMap->isTileEmpty(this->mousePosGrid.x, this->mousePosGrid.y, 0)) {

	//					this->tileMap->AddTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type); //Magic number is Z layer coordinate, TODO Refactor
	//				}
	//			}
	//			else {

	//				if (this->getKeyTime())
	//					this->tileMap->AddTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect, this->collision, this->type); //Magic number is Z layer coordinate, TODO Refactor
	//			}
	//		}
	//		else {

	//			this->textureRect = this->textureSelector->getTextureRect();
	//		}
	//	}
	//}

	//	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime()) {

	//		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow))) {

	//			if (!this->textureSelector->getActive())
	//				this->tileMap->RemoveTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	//		}

	//	}

	/*

		TODO - this goes in updateEvents..

	*/

	///updateKeyTime(dt, 0.1f);

		//TOGGLE TILE TYPE AND COLLISION
	//const Uint8* keyState = SDL_GetKeyboardState(NULL);
	//if (keyState[\fCODE_C] && getKeyTime()) {

	//	if (this->collision)
	//		this->collision = false;
	//	else
	//		this->collision = true;
	//}
	//else if (keyState[SDL_SCANCODE_RIGHT] && this->getKeyTime()) {

	//		//ADD NUMBER OF DIFFERENT TILE TYPES TO CHECK
	//		if(this->type < this->maxTileTypes)
	//			this->type++;
	//	}

	//	else if (keyState[SDL_SCANCODE_LEFT] && this->getKeyTime()) {

	//		if(this->type > 0)
	//			this->type--;
	//	}


	//	if (keyState[SDL_SCANCODE_G]) {

	//		//this->tileMap->runMazeGenerator();
	//		this->tileMap->runPerfectMazeGenerator();
	//		this->lockTiles = false;
	//		this->tileMap->placeTreasure(5, 5);
	//		this->lockTiles = true;
	//	}

	//	if (keyState[SDL_SCANCODE_H]) {

	//		int posX = 0;
	//		int posY = 0;
	//		int goalX = 0;
	//		int goalY = 0;

	//		TileMap::Cell level[SIZE][SIZE];
	//		this->tileMap->initRandomMaze(level);
	//		this->tileMap->generateMaze2(level, posX, posY, goalX, goalY);
	//		this->tileMap->autoAddCells(level);
	//	}

	/*if (keyState[SDL_SCANCODE_H]) {

			this->tileMap->runMazeGenerator();
			this->lockTiles = false;
			this->tileMap->placeTreasure(4, 1);
			this->lockTiles = true;
	}*/

//	if (this->firstRun) {
//
//		this->firstRun = false;
//		return;
//	}
}

void Editor::setStateData()
{

}

void Editor::updateEvents(SDL_Event &e) {

	/*

	Updates all buttons in the state and handles their functionality

	*/


	if(pauseMenu->getActive() && mPaused){

        if(pauseMenu->noPressed(e.button)){

            pauseMenu->setActive(false);
            mPaused = false;
            //Engine::GetInstance()->PopState();
        }

        else if(pauseMenu->yesPressed(e.button)){

            tileMap->SaveToFile("MAP1");
            pauseMenu->setActive(false);
            mPaused = false;
        }

        else if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

            pauseMenu->setActive(false);
            mPaused = false;
            Engine::GetInstance()->PopState();
        }

        return;
	}




	//} //End mouse click check

	//if (this->buttons["NEW_SAVE"]->isPressed(e) && this->getKeyTime() && !this->stateData->nameSet) {

	//	this->fileName = this->stateData->name;
	//	//this->stateData->nameSet = true;
	//}

	////Quit game
	//if (this->buttons["BACK"]->isPressed() && this->getKeyTime()) {


	//	this->EndState();
	//}

		//CHHJSHDKJSHDKJAHSJDHSJDHASKJHDKJAHSDKJAHSKJDHASD

        const Uint8* state = SDL_GetKeyboardState(NULL);


        if(this->firstRun && e.type == SDL_MOUSEBUTTONDOWN){

            SDL_PumpEvents();
                SDL_Delay(50);

            SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);

            firstRun = false;

            //return;
        }



		if (e.type == SDL_KEYDOWN) {

			const Uint8* keyState = SDL_GetKeyboardState(NULL);
			if (keyState[SDL_SCANCODE_C]) {

				if (this->collision)
					this->collision = false;
				else
					this->collision = true;
			}
			else if (keyState[SDL_SCANCODE_RIGHT]) {

				//ADD NUMBER OF DIFFERENT TILE TYPES TO CHECK
				if (this->type < this->maxTileTypes)
					this->type++;
			}

			else if (keyState[SDL_SCANCODE_LEFT]) {

				if (this->type > 0)
					this->type--;
			}

			if (keyState[SDL_SCANCODE_L]) {

				lockTiles = !lockTiles;
			}

			if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){

                if(pauseMenu->getActive()){

                    Engine::GetInstance()->PopState();

                }
                else{

                    pauseMenu->setActive(true);
                    mPaused = true;
                }


                return;
			}

			if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_U)){

               this->tileMap->LoadFromFile("Assets/Maps/Map1.txt");
            }

			if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {

                StateData::GetInstance()->moveCam2(LEFT, .25f);
                camMovement = true;
            }

            if(keyState[SDL_SCANCODE_D]){

                StateData::GetInstance()->moveCam2(RIGHT, .25f);
                camMovement = true;
            }


			if(keyState[SDL_SCANCODE_S]){

                StateData::GetInstance()->moveCam2(DOWN, .25f);
                camMovement = true;
			}

			if(keyState[SDL_SCANCODE_W]){

                StateData::GetInstance()->moveCam2(UP, .25f);
                camMovement = true;
			}




			if (keyState[SDL_SCANCODE_G]) {

				//this->tileMap->runMazeGenerator();
				this->tileMap->runPerfectMazeGenerator();
				this->lockTiles = false;
				this->tileMap->placeTreasure(5, 5);
				this->lockTiles = true;
			}

			if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_B)){

                ///TODO Clear the tilemap and create an empty one...
                tileMap->clear();
                InitTileMap();
                InitGUI();
			}

			if (keyState[SDL_SCANCODE_H]) {

				int posX = 0;
				int posY = 0;
				int goalX = 0;
				int goalY = 0;

				TileMap::Cell level[SIZE][SIZE];
				this->tileMap->initRandomMaze(level);
				tileMap->generateMaze2(level, posX, posY, goalX, goalY);
				this->tileMap->autoAddCells(level);
			}

			if (keyState[SDL_SCANCODE_ESCAPE]) {

///				StateData::GetInstance()->push_state(std::make_shared<PauseMenuState>(*StateData::GetInstance(), this->tileMap));
				SDL_Delay(100);
				//StateData::GetInstance()->states->push_back(new PauseMenuState(*StateData::GetInstance(), *tileMap));
				//StateData::GetInstance()->currentState++;
			}

			if (keyState[SDL_SCANCODE_F]) {

				this->tileMap->runMazeGenerator();
				this->lockTiles = false;
				this->tileMap->placeTreasure(2, 5); ///First parameter is number of alive neighbours, second is chance to spawn treasure.
				this->lockTiles = true;
			}
		}

		if(e.type == SDL_KEYUP && e.key.repeat == 0){

            switch(e.key.keysym.sym){

                case SDLK_a: StateData::GetInstance()->moveCamera(FREEZE, X_AXIS);
                break;

                case SDLK_d: StateData::GetInstance()->moveCamera(FREEZE, X_AXIS);
                break;

                case SDLK_w: StateData::GetInstance()->moveCamera(FREEZE, Y_AXIS);
                break;

                case SDLK_s: StateData::GetInstance()->moveCamera(FREEZE, Y_AXIS);
                break;
            }
		}



		///BELOW HERE IS EXACTLY THE SAME AS UpdateMouseEvents
        if(textureSelector->getActive()){

			textureSelector->update(e.button);
        }

	for (auto &it : this->buttons) {

		it.second->update();
	}


	if (buttons["HIDE"]->isPressed(e.button)) {

		hidden = !hidden;

		return;
	}
	//if (e.type == SDL_MOUSEBUTTONDOWN) {



///ADD/REMOVE TILE FUNCTION
/*
    This needs to move to it's own function....
*/
///
int x, y;
SDL_GetMouseState(&x, &y);
	SDL_Rect temp = { x, y, 32, 32 };
	SDL_Rect result = { 0, 0, 32, 32 };

	if (e.button.button == SDL_BUTTON_LEFT && !firstRun){


	x /= StateData::GetInstance()->gridSize;
	y /= StateData::GetInstance()->gridSize;

	int newX = (StateData::GetInstance()->getCamera().x / StateData::GetInstance()->gridSize);
	int newY = (StateData::GetInstance()->getCamera().y / StateData::GetInstance()->gridSize);

//int newX = (0 / 64);
//int newY = (0 / 64);
    newX += x;
	newY += y;


		if (SDL_HasIntersection(&this->textureSelector->getTextureRect(), &temp) || !SDL_IntersectRect(&this->textureSelector->getTextureRect(), &temp, &result)) {

			//}
			//if (!SDL_IntersectRect(&this->textureSelector->getTextureRect(), &temp, &result)) {

			if (hidden) {

                    //newX > tilemap->getMaxSizeGrid().x || newY > tilemap->getMaxSizeGrid().y

				if (newX >= 0 || newY >= 0) {

                    ///TODO: The layer is set to 0 for both but should allow layers...

					if (lockTiles) {

						if (this->tileMap->isTileEmpty(newX, newY, 0)) {

							this->tileMap->AddTile(newX, newY, 0, this->textureRect, this->collision, this->type); //Magic number is Z layer coordinate, TODO Refactor
						}
						else{

                            std::cout << "TILE IS NOT EMPTY!!!" << std::endl;
						}
					}
					else {


                        this->tileMap->AddTile(newX, newY, 0, this->textureRect, this->collision, this->type); //Magic number is Z layer coordinate, TODO Refactor
					}
				}
			}
			else {

                    if(!lockTiles && !buttons["HIDE"]->getSelected()){
                        this->tileMap->AddTile(newX, newY, 0, this->textureRect, this->collision, this->type);
                    }
                    else{

                        textureSelector->update(e.button);
                        this->textureRect = this->textureSelector->getTextureRect();
                    }
                //hidden = true;
			}

		}
	}
	if (e.button.button == SDL_BUTTON_RIGHT) {


        x /= (64);
        y /= 64;

	int newX = (StateData::GetInstance()->getCamera().x / StateData::GetInstance()->gridSize);
	int newY = (StateData::GetInstance()->getCamera().y / StateData::GetInstance()->gridSize);
//int newX = (0 / 64);
//int newY = (0 / 64);
	x += newX;
	y += newY;

		//if (!textureSelector->getActive()) {

		if(!tileMap->isTileEmpty(x, y, 0)){

			this->tileMap->RemoveTile(x, y, 0);
		}
		//}
	}


	///END ADD/REMOVE TILE FUNCTION
    /*
        This needs to move to it's own function....
    */
    ///

}   ///End updateEvents


void Editor::updateGUI(){



	std::string test = this->tileMap->getTileTypeStr(this->type);

	int x = 0;
	int y = 0;
	int xOff = 0;
	int yOff = 0;

	int newX, newY;


    SDL_GetMouseState(&x, &y);


    x /= 64;
    y /= 64;

    newX = StateData::GetInstance()->getCamera().x / StateData::GetInstance()->gridSize;
    newY = StateData::GetInstance()->getCamera().y / StateData::GetInstance()->gridSize;



        newX += x;
        newY += y;

        selectorRectBig.x = x * 64;
        selectorRectBig.y = y * 64;


        /////////////////////////////////////

	//}



	selectorRectBig.h = 64;
	selectorRectBig.w = 64;
	//selectorRectBig.x += StateData::GetInstance()->getCamera().x;


	std::stringstream ss;
	ss  << "Xoff: " << xOff << "  Yoff: " << yOff << "\n"
        << "X: " << newX << "   Y: " << newY << "\n"
		//<< this->textureRect.left << "  " << this->textureRect.top << "\n"
		<< "Collision: " << this->collision << "\n"
		<< "Tile Type: " << this->type << "  -  " << test <<  "\n"
		<< "Tile Layers: " << this->tileMap->getTileLayers(newX, newY, this->layer) << "\n"
		<< "Lock Tiles:  " << this->lockTiles << "\n";
	SDL_Color col = { 255, 0, 127 };
	cursorText->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), ss.str(), col, *font, true, 190);
}

void Editor::UpdatePauseMenuButtons(){

//	//if (this->pMenu->isButtonPressed("EXIT_STATE") && this->getKeyTime()) {
//	//	this->EndState();
//	//}
//	//if (this->pMenu->isButtonPressed("BACK") && this->getKeyTime()) {
//	//
//	//	this->UnpauseState();
//	//}
//	//if (this->pMenu->isButtonPressed("SAVE") && this->getKeyTime()) {
//	//	this->stateData->name = " ";
//	//	this->fileOpen = true;
//	//	this->save = true;
//	//	this->getKeyTime();
//	//	//this->tileMap->SaveToFile("test.txt");
//	//}
//	//if (this->pMenu->isButtonPressed("LOAD") && this->getKeyTime()) {
//
//	//	//this->ReadDirectory("Maps", this->fileNames);
//	//	this->fileOpen = true;
//	//	this->load = true;
//	//	this->getKeyTime();
//	//	//this->tileMap->LoadFromFile("test.txt");
//	//}
}

void Editor::UpdateFileMenuButtons(){

	this->fileName = " ";

	if (load) {

		//this->fileMenu->

		for (unsigned int i = 0; i < this->fileNames.size(); ++i) {

			std::string name = this->fileNames[i].c_str();

			//if (this->fileMenu->isButtonPressed(name)) {

			//	this->fileName = name;
			//}
		}

		/*float yPos = 33.3f;
		float yOffset = 12.f;
		sf::VideoMode vm = this->stateData->gfxSettings->resolution;

		for (int i = 0; i < fileNames.size(); i++) {

			yPos += yOffset;

			std::string  strBuild = this->fileNames[i].c_str();

			this->fileMenu->addButton(strBuild, GUI::p2pX(62.5f, vm), GUI::p2pY(yPos, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::CalcCharSize(vm), strBuild);
		}*/

		//this->fileMenu->addButton(, GUI::p2pX(62.5f, vm), GUI::p2pY(33.3f, vm), GUI::p2pX(31.3f, vm), GUI::p2pY(8.3f, vm), GUI::CalcCharSize(vm), "New Save");

	}


		/*if (this->fileMenu->isButtonPressed("TEST") && this->getKeyTime()) {

			this->fileName = "test.txt";
		}

		if (this->fileMenu->isButtonPressed("TEST2") && this->getKeyTime()) {

			this->fileName = "test2.txt";
		}*/


		/*std::experimental::filesystem::directory_iterator*/
		//std::filesystem::
		/*if (this->fileMenu->isButtonPressed("TEST3") && this->getKeyTime()) {

			this->fileName = "test3.txt";
		}*/
			//if (this->fileMenu->isButtonPressed("NEWSAVE") && this->getKeyTime()) {

			//	this->fileName = "maps/" + this->stateData->name;
			//}

			//if (this->fileMenu->isButtonPressed("BACK") && this->getKeyTime()) {

			//	this->fileOpen = false;
			//}


		if (save) {

			//if (!this->stateData->nameSet) {

			//	sfName.setString(this->stateData->name);
			//}

			for (unsigned int i = 0; i < this->fileNames.size(); ++i) {

				std::string name = this->fileNames[i].c_str();

				//if (this->fileMenu->isButtonPressed(name)) {

				//	this->fileName = name;
				//}
			}
		}

		if (save && fileName != " ") {

			std::vector<std::string> files;
///			this->saveData.readDirectory("Maps", files);

			int ID = files.size();
			if (std::filesystem::exists(fileName)) {

				std::ifstream inFile;

			std::string line;

				try {

					inFile.open(fileName);

					if (inFile.is_open()) {

						for (int i = 0; i < 4; i++) {

							getline(inFile, line);
						}

						inFile >> ID;
					}

					inFile.close();
				}
				catch (std::exception &e) {

					std::cout << e.what() << std::endl;
				}
			}


			this->tileMap->SaveToFile(fileName, true, ID);
			std::cout << "New Save function!\n";
			save = false;
			fileOpen = false;
			unpauseState();
		}

		if (load && fileName != " ") {

			//this->tileMap->LoadFromFile(fileName);
			//this->tileMap = this->tileMap;
			std::cout << "New Load function!\n";
			load = false;
			fileOpen = false;
			unpauseState();
		}

}

void Editor::update(const float & dt) {

	//this->mainView.setSize(this->window->getSize().x, this->window->getSize().y);

	//this->updateMousePositions(&this->mainView);
///	updateKeyTime(dt, 0.5f);
	//this->UpdateInput(dt);

    if(pauseMenu->getActive() && mPaused){

        pauseMenu->update();

        return;
    }

	this->paused = false;

	if (!this->mPaused) {
		this->updateGUI();
		this->UpdateEditorInput(dt);
	//	this->updateMousePositions(&this->mainView);
	}
	else {

///		this->updateKeyTime(dt, 0.5f);
		if (this->fileOpen) {

			//this->fileMenu->Update(mousePosView);
			//this->fileMenu->UpdateWindow();
			this->UpdateFileMenuButtons();

			//this->updateButtons();
			//this->getKeyTime();

		}
		else {

			this->firstRun = true;
		//	this->pMenu->Update(this->mousePosView);
			//this->pMenu->UpdateWindow();
			this->UpdatePauseMenuButtons();
			//this->getKeyTime();
		}
	}
}

void Editor::updateInput(const float & dt)
{

}


//RENDER


void Editor::RenderButtons() {

	//this->testButton->Render(target);

	for (auto &it : this->buttons) {

		it.second->renderButtons();
	}
}

void Editor::RenderGUI(){

///H ??????
    //StateData::GetInstance()->updateCamera();
	bool check = false;
	if (!hidden) {

		check = textureSelector->getActive();
	}
	if (!check){

        int x, y;
        SDL_GetMouseState(&x, &y);
		SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &selectorRect);
		cursorText->render(Engine::GetInstance()->GetRenderer(), x + 5, y + 5);
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 255, 255, 255);
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &selectorRectBig);
	}
	if(!hidden){

		buttons["HIDE"]->setRenderText("Hide");
		RenderButtons();
	}
	else {

		buttons["HIDE"]->setRenderText("Show");
		RenderButtons();
	}
	if (!hidden) {

		this->textureSelector->render();
	}

	if(pauseMenu->getActive()){

        pauseMenu->render();
	}

	//SDL_RenderFillRect(rend, &sidebar);
}

void Editor::render() {

//	target->draw(this->background);


	//this->tileMap->renderDeferredStack(*target);



	if (this->mPaused) {

		if (this->fileOpen) {

			//target->setView(this->window->getDefaultView());

			if (save) {

				//target->draw(this->textBox);
				//target->draw(this->sfName);
			}
			//this->fileMenu->Render(Engine::GetInstance()->GetRenderer());
			//this->RenderButtons(*target);
		}
		else {


			//target->setView(this->window->getDefaultView());
			//this->pMenu->Render(Engine::GetInstance()->GetRenderer());
		}
	}
	//tileMap->render(Engine::GetInstance()->GetRenderer(), StateData::GetInstance()->getCamera());
	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
	this->tileMap->render(Engine::GetInstance()->GetRenderer(), StateData::GetInstance()->getCamera());

//	SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
    this->RenderButtons();
	this->RenderGUI();
}
