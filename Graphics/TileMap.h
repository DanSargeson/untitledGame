#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
//#include "Entity.h"
//#include "Player.h"
//#include "Enemy.h"
#include "GUI.h"
#include <list>
#include <stack>
#include <time.h>
#include <chrono>
#include <random>
#include <filesystem>
//#include "item.h"
//#include "weapon.h"

#define SIZE 49

enum MAP_ID {

	WORLD_0,
	WORLD_1,
	WORLD_2
};

class TileMap{


private:

	static int MAP_IDENTIFIER;
	bool showHitbox;

	bool spawnsEnemies;

	float gridSizeF;


	//GUI::InfoText* infoBox;

	int mapID;
	int gridSizeI;
	int layers;
	//sf::Vector2i maxSizeWorldGrid;
	//sf::Vector2f maxSizeWorldF;
	SDL_Rect maxSizeWorldGrid;
	SDL_FRect maxSizeWorldF;

	/*

		Procedural maze generation

	*/
	std::vector<std::vector<bool>> maze;
	std::list<std::pair<int, int>> drillers;

	std::vector<std::vector<std::vector<std::vector<std::shared_ptr<Tile>> > > >map;
	std::stack<Tile*> deferredRenderStack;

	std::shared_ptr<Texture> tileSheet;
	std::string textureFile;
	SDL_Rect collisionBox;

	SDL_Rect nextCollisionBox;


	//Tile Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;


public:

	void clear();
	struct Cell {

		bool display;
		bool visited;
		bool top_wall;
		bool bottom_wall;
		bool left_wall;
		bool right_wall;
		bool exit;
	};

	TileMap(SDL_Renderer* rend, float gridSize, int width, int height, std::string textureFile/*, GUI::InfoText* box = NULL*/);
	TileMap(const std::string fileName/*, GUI::InfoText* box*/);
	TileMap(int ID, int charID/*, GUI::InfoText* box*/);
	~TileMap();

	//Accessors

	std::shared_ptr<Texture> getTileSheet();
	const int getTileLayers(const unsigned int x, const unsigned int y, const unsigned int layer) const;
	const std::string getDestinationString(unsigned int x, unsigned int y, unsigned int layer = 0);
	const std::string getTileTypeStr(int type);
	const SDL_Rect& getMaxSizeGrid() const;
	const SDL_FRect& getMaxSizeF() const;
	const bool isTileEmpty(int x, int y, int z) const;

	//void initRandomMaze(Cell Level[][]);

	void initRandomMaze(Cell Level[][SIZE]);

	void generateMaze2(Cell level[][SIZE], int & posX, int & posY, int & goalX, int & goalY);

	void autoAddCells(Cell level[][SIZE]);

//	void findPlayerStartingTile(Entity* entity);

	void autoAddTiles();

	//functions

	void runPerfectMazeGenerator();

	int countAliveNeighbours(std::vector<std::vector<bool>> l_maze, int x, int y);

	void doSimulationStep(std::vector<std::vector<bool>> l_maze);

	void runMazeGenerator();

	void placeTreasure(int limit = 5, int treasureChance = 10);

	void Update();

	int getNumOfEnemies();

	void disableEnemy(const unsigned int x, const unsigned int y);

	//std::vector<sf::Vector2f> AddEnemies(std::vector<Enemy>& enemies);

	std::string getTilePositionStr();

	//void AddEnemy(std::vector<Entity*> enemies);

	void setMapID(int id);
	void setSpawnsEnemies(int x, int y, bool choice);
	bool getSpawnsEnemies();
	int getMapID();

	void AddTile2(int x, int y, const int z, const SDL_Rect& textureRect, short type, std::vector<int> flags);

	void AddTile(const int x, const int y, const int z, const SDL_Rect& textureRect, const bool& collision, const short& type);
	void RemoveTile(const int x, const int y, const int z);

	void saveWithID(int id, int charID);

	//void SaveToFileNEW(const std::string fileName);

	void SaveToFile(const std::string fileName, bool generateID = false, int ID = -1);
	void resizeMap(int x, int y);
	void createFromSave(int l_x, int l_y, int l_z, int tr_x, int tr_y, bool l_collision, short l_type);
	//void LoadFromFileNEW(const std::string fileName, const int lineOffset = 7);
	void LoadFromFile(const std::string fileName);

	void loadFromID(int ID, int charID);

	int getID();
	int getTileType(unsigned x, unsigned y, unsigned z = 0);

///	void updateCollision(Entity* entity, const float& dt);

///	void UpdateTileCollision(Entity * entity, const float & dt);

	//void UpdateSurroundingTiles(Entity * entity, const float & dt, std::vector<string>& ops, bool& choice);

	//void Teleport(int dest, Entity& entity);

	//void Render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());
	//void renderDeferredStack(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f());

	void updateGUI();

	void render(SDL_Renderer* target, SDL_Rect cam);
};

#endif

