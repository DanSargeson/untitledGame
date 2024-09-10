#include "Tile.h"

Tile::Tile(){

	this->collision = false;
	this->teleport = false;
	this->tileType = DEFAULT;
	this->destination = " ";
	this->texture = NULL;
	this->active = true;
}

Tile::Tile(int x, int y, int gridSizeF, Texture& tileTextureSheet, const SDL_Rect& textureRect, bool collision, short type, bool teleport, std::string dest){


	this->shape.x = x * static_cast<int>(gridSizeF);
	shape.y =  y * gridSizeF;
	//shape.x = x;
	//shape.y = y;
	this->texture = &tileTextureSheet;

	this->active = true;

	this->collision = collision;
	this->tileType = type;

	if (this->tileType == TILE_TYPES::ITEM_BOX_OPEN) {

		this->openBox();
	}
	this->destination = dest;
	this->teleport = teleport;
//	texture = new Texture();
	this->textureRect = textureRect;
	//texture->setTextureRect(textureRect.x, textureRect.y, 32, 32);
}

Tile::Tile(int x, int y, int gridSizeF, Texture & textureSheet, const SDL_Rect& textureRect, short type, std::vector<int> flags){


	this->shape.x = x * gridSizeF;
	shape.y  = y * gridSizeF;
	this->texture = &textureSheet;

	this->active = true;

	this->collision = false;
	this->tileType = type;


	for (size_t i = 0; i < flags.size(); i++){

		if (flags[i] < TOTAL_TILES && flags.size() > 0) {

			switch (flags[i]) {

			case TILE_TYPES::BROKEN:

				this->textureRect.x = 80;
				this->textureRect.y = 16;
				this->textureRect.w = 16;
				this->textureRect.h = 16;

				break;

			case TILE_TYPES::BREAKABLE:

				this->collision = true;
				break;
			}
		}
	}

	//this->shape.setTexture(textureSheet);
	//this->shape.setTextureRect(textureRect);
}


const short& Tile::getType() const{


	return this->tileType;
}

const std::string Tile::getAsString() const{

	std::stringstream ss;
	int x = textureRect.x;
	int y = textureRect.y;

	ss << x << " " << y << " " <<
		this->collision << " " << this->tileType;

	return ss.str();
}

const SDL_Rect& Tile::getPosition() const{

	return this->shape;
}

const bool & Tile::getCollision() const{

	return this->collision;
}

const bool & Tile::getTeleport() const {

	return this->teleport;
}

//const std::string& Tile::getTypeStr(int type) const{
//
//	switch (type) {
//
//	case TILE_TYPES::DEFAULT:
//		return "Default";
//
//		break;
//
//	case TILE_TYPES::ENEMY_SPAWNER:
//		return "Enemy Spawner";
//		break;
//
//	case TILE_TYPES::HEALING:
//		return "Bed";
//		break;
//
//	case TILE_TYPES::ITEM_BOX:
//		return "Chest";
//		break;
//
//	case TILE_TYPES::OVERHEAD:
//		return "Overhead";
//		break;
//
//	case TILE_TYPES::TELEPORT:
//		return "Teleport - Blank";
//		break;
//	}
//
//	return "Unown";
//}

const std::string & Tile::getDestination() const
{

	return this->destination;
}

const SDL_Rect Tile::getGlobalBounds() const{

	return this->shape;
}

void Tile::setDestination(std::string dest){

	this->destination = dest;
}

void Tile::setOpacity(uint8_t value){

	//this->shape.setColor(sf::Color(255, 255, 255, value));
}

void Tile::openBox(int type){

	this->tileType = ITEM_BOX_OPEN;


	if (type == 0) {

		this->textureRect.x = 48;
		this->textureRect.y = 64;
		this->textureRect.h = 16;
		this->textureRect.w = 16;
	}
	else {

		this->textureRect.x = 80;
		this->textureRect.y = 0;
		this->textureRect.h = 16;
		this->textureRect.w = 16;
	}

	//sf::Texture texture;

	//texture.loadFromFile("Resources/Images/Tiles/basicTiles2.png");

	//	this->shape.setTexture(*texture);
	//	this->shape.setTextureRect(this->textureRect);

//	this->active = true;
	this->collision = false;
}

void Tile::breakRock() {

	this->tileType = BROKEN;

	this->textureRect.x = 16;
	this->textureRect.y = 80;
	this->textureRect.w = 16;
	this->textureRect.h = 16;

		//this->shape.setTexture(*texture);
		//this->shape.setTextureRect(this->textureRect);

	this->collision = false;
}

void Tile::setActive(bool active){

	this->active = active;
}

bool Tile::isActive(){


	return this->active;
}

void Tile::disableEnemySpawn(){

	this->tileType = TILE_TYPES::DEFAULT;
}

const bool Tile::intersects(SDL_Rect bounds) const{

	SDL_Rect result;
	return SDL_IntersectRect(&shape, &bounds, &result);
	//return this->shape.getGlobalBounds().intersects(bounds);
}

void Tile::Update(){


}

void Tile::Render(SDL_Renderer* target, SDL_Rect cam/*, sf::Shader* shader, const sf::Vector2f playerPosition*/){


	//SDL_RenderFillRect(target, &shape);
	shape.w = 64;
	shape.h = 64;

	int offX = 0;
	int offY = 0;


    texture->render(target, shape.x, shape.y, &this->textureRect, cam);

	//if (shader) {

	//	shader->setUniform("hasTexture", true);
	//	shader->setUniform("light", playerPosition);
	//
	//	target.draw(this->shape, shader);
	//}
	//else {

	//	target.draw(this->shape);
	//}
}
