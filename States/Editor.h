#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.h"
#include "GUI.h"
#include "TileMap.h"
#include <filesystem>
#include <map>
#include <vector>
///#include "SaveData.h"
//#include "Menu.h"

enum CAMERA_MOVE{

    STILL = 0,
    HORIZONTAL = 1,
    VERTICAL = 2
};

class State;
//class GUI;
class PauseMenu;
class TileMap;

class Editor : public State{

private:

	//variables

	float zoomFactor;

	//sf::RectangleShape textBox;
	//sf::Text sfName;

///	SaveData saveData;

	bool hidden;
	//GUI::Button* newSave;

	//sf::View mainView;
	float cameraSpeed;

	bool firstRun; //Checks this is the first time the editor has run in tis state
	bool lockTiles; // Controls if mpore than one tile can be placed on a spot

	int width;
	int height;
	int layer;
	std::shared_ptr<TileMap> tileMap;
    int camDirection;


	SDL_Rect selectorRect;
	SDL_Rect selectorRectBig;
	//sf::RectangleShape selectorRect;
	//sf::RectangleShape collisionBox;
	//sf::IntRect textureRect;
	SDL_Rect textureRect;

	std::shared_ptr<GUI::TextureSelector> textureSelector;

	SDL_Rect sidebar;

	//PauseMenu* pMenu;
	//PauseMenu* fileMenu; //Choose which file to load in editor
	std::string fileName;
	bool fileOpen;
	bool save;
	bool load;
	bool mPaused;

	std::shared_ptr<GUI::Menu> loadFiles;

	bool bigMap;

	std::string mapTextureStr;

	TTF_Font* font;
	//Texture* cursorText;
	std::shared_ptr<Texture> cursorText;
	SDL_Rect background;
	std::unique_ptr<Texture> bgTexture;

	bool collision;
	short type;
	bool teleport;
	std::string destination;

	bool camMovement;


	int maxTileTypes;

	std::map<std::string, GUI::Button*> buttons;
	std::vector<std::string> fileNames;

	std::shared_ptr<GUI::textBox> pauseMenu;

	//functions
	void InitVariables();
	void InitView();
	void InitBackground();
	void InitFonts();
	void InitText();
	void InitKeyBinds();
	void InitButtons();
	void InitTileMap();
	void InitGUI();
	void InitPauseMenu();
	void InitFileMenu();

public:

	Editor();
	virtual ~Editor();

	//functions
	void toggleTileLock();

	//void EndState();
	void UpdateInput(const float& dt);

	void UpdateEditorInput(const float& dt); //TODO might want moving to Input.

	void setStateData();

	void update(const float &dt);
	void updateInput(const float &dt);
	void updateEvents(SDL_Event &e);
	void updateMouseEvents(SDL_MouseButtonEvent& e);
	void updateGUI();
	void UpdatePauseMenuButtons();
	//void ReadDirectory(const std::string name, std::vector<std::string>& v);
	void UpdateFileMenuButtons();
	void render();
	void RenderButtons();
	void RenderGUI();




};

#endif

