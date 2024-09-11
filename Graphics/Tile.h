#ifndef TILE_H
#define TILE_H

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Texture.h"



///TODO: TILE is the sprite that is being used.
enum TILE {

	DEFAULT_TILE = 0,
	VILLAGE_TILE,
	INN_TILE,
	CHURCH_TILE,
	SHEOL_TILE,
	UNK_TILE,
	BLUE_TILE,
	INDIGO_TILE,
	VIOLET_TILE
};

enum TILE_TYPES {

	DEFAULT = 0,
	OVERHEAD,
	DAMAGING,
	TELEPORT,
	TELEPORT_HOME,
	TELEPORT_WORLD0,
	HEALING,
	ITEM_BOX,
	ITEM_BOX_OPEN,
	ENEMY_SPAWNER,
	TELEPORT_WORLD1,
	CAVE,
	BREAKABLE,
	BROKEN,
	TOTAL_TILES
};

class Tile{

private:

protected:
	SDL_Rect shape;
	SDL_Rect textureRect;
	Texture* texture;
	short tileType;
	bool collision; //Is collision enabled?
	bool teleport; //Determines if the tile is a teleport tile.
	bool breakable;
	std::string destination; //Determines which map to load for teleportation tiles.
	float opacity;

	bool active;

public:

	Tile();
	Tile(int x, int y, int gridSizeF, Texture& tileTextureSheet, const SDL_Rect& textureRect, bool collision = false, short type = DEFAULT, bool teleport = false, std::string dest = " ");
	Tile(int x, int y, int gridSizeF, Texture& textureSheet, const SDL_Rect& textureRect, short type, std::vector<int> flags);
	virtual ~Tile() {};


	//Accessors
	const short& getType() const;
	const std::string getAsString() const;
	const SDL_Rect& getPosition() const;
	const bool& getCollision() const;
	const bool & getTeleport() const;
//	const std::string & getTypeStr(int type) const;
	const std::string& getDestination() const;
	const SDL_Rect getGlobalBounds() const;

	//Modifiers
	void setDestination(std::string dest);
	void setOpacity(uint8_t value);
	void openBox(int type = 0);

	void breakRock();

	void setActive(bool active);

	bool isActive();

	void disableEnemySpawn();

	//functions
	const bool intersects(SDL_Rect bounds) const;

	void Update();
	void Render(SDL_Renderer* target, SDL_Rect cam/*,sf::Shader* shader = NULL, const sf::Vector2f playerPosition = sf::Vector2f()*/);
};

#endif
