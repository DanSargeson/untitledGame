#include "TileMap.h"
#include <memory>

int TileMap::MAP_IDENTIFIER = 0;

void TileMap::clear(){


	if (!this->map.empty()) {

		for (unsigned int x = 0; x < this->map.size(); x++) {

			for (unsigned int y = 0; y < this->map[x].size(); y++) {

				for (unsigned int z = 0; z < this->map[x][y].size(); z++) {

					for (size_t k = 0;  k < this->map[x][y][z].size();  k++){

						//delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;
					}

					this->map[x][y][z].clear();
				}

				this->map[x][y].clear();
			}

			this->map[x].clear();
		}

		this->map.clear();
	}

	/*for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {


		for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {


			for (int z = 0; z < this->layers; z++) {

				for (int k = 0; k < this->map[x][y][z].size(); k++){

					delete this->map[x][y][z][k];

					this->map[x][y][z][k] = NULL;
				}

				this->map[x][y][z].clear();
			}

			this->map[x][y].clear();
		}

		this->map[x].clear();
	}

	this->map.clear();*/

	///this->tileSheet->free();
	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(SDL_Renderer* rend, float gridSize, int width, int height, std::string textureFile/*, GUI::InfoText* box*/){

	//this->infoBox = box;

	this->mapID = -1;
	this->showHitbox = false;
	this->gridSizeF = gridSize; //Sets scale of the map grid size.
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;

	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;

	this->layers = 1;
	this->textureFile = textureFile;
	tileSheet = std::make_unique<Texture>();
	tileSheet->loadFromFile(textureFile, rend);

	//this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<std::make_shared<Tile>()>>>());

	map.resize(maxSizeWorldGrid.x, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>());

	for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

		for (int y = 0; y < this->maxSizeWorldGrid.y; y++){

			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<std::shared_ptr<Tile>>>());

			for (int z = 0; z < this->layers; z++){

				this->map[x][y].resize(this->layers, std::vector<std::shared_ptr<Tile>>());
			}
		}
	}


	//Tile Cullingdet
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
}

TileMap::TileMap(const std::string fileName/*, GUI::InfoText* box*/){


	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	if (fileName == "test.txt") {

		this->mapID = MAP_ID::WORLD_0;
	}
	if (fileName == "test2.txt") {

		this->mapID = MAP_ID::WORLD_1;
	}

	maxSizeWorldGrid.x = 0;
	maxSizeWorldGrid.y = 0;
	maxSizeWorldGrid.w = 64;
	maxSizeWorldGrid.h = 64;
	this->LoadFromFile(fileName);

	/*this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color::Transparent);
	this->collisionBox.setOutlineThickness(-1.f);
	this->nextCollisionBox.setOutlineColor(sf::Color::Cyan);*/
}

TileMap::TileMap(int ID, int charID /*,GUI::InfoText* box*/){

	//TileMap::MAP_IDENTIFIER++;

	this->spawnsEnemies = false;

	this->mapID = ID;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	/*if (ID == -1) {

		this->LoadFromFile("Maps/first");
	}
	else {
*/
	this->loadFromID(ID, charID);
	//}
}


std::shared_ptr<Texture> TileMap::getTileSheet() {

	return this->tileSheet;
}



const int TileMap::getTileLayers(const unsigned int x, const unsigned int y, const unsigned int layer) const{


    int s = this->map.size();

	if (x >= 0 && x < this->map.size()) {

		if (y >= 0 && y < this->map[x].size()) {

			if (layer >= 0 && layer < this->map[x][y].size()) {

				return this->map[x][y][layer].size();
			}

		}
	}

	return -1;
}

const std::string TileMap::getDestinationString(unsigned int x, unsigned int y, unsigned int layer){

	if (x >= 0 && x < this->map.size()) {

		if (y >= 0 && y < this->map[x].size()) {

			if (layer >= 0 && layer < this->map[x][y].size()) {

				for (unsigned int k = 0; k < this->map[x][y][layer].size(); k++) {
					if (!this->map[x][y][layer][k]) {

						return " ";

					}
					else {

						return this->map[x][y][layer][k]->getDestination();
					}
				}
			}
		}
	}
	return std::string();
}

const std::string TileMap::getTileTypeStr(int type){

	switch (type) {

	case TILE::DEFAULT_TILE:

		return "Water";
		break;

	case TILE::INN_TILE:
		return "The Golden Duck Inn";
		break;

	case TILE::CHURCH_TILE:
		return "Church of Baphomet";
		break;

    case TILE::SHEOL_TILE:
        return "Sheol Beach";
        break;

	case TILE::UNK_TILE:
		return "Unk Cekula";
		break;

    case TILE::EMESH_TILE:
		return "Emesh Forest";
		break;

    case TILE::INDIGO_TILE:
        return "INDIGO faction";
        break;

    case TILE::VIOLET_TILE:
        return "VIOLET faction";
        break;

    case 9:
        return "Suspicious Cave";
        break;

    case 12:
        return "Grassland";
        break;

	default:
		return "Unknown tile string";
		break;
	}

	//switch (type) {

	//case TILE_TYPES::DEFAULT:
	//	return "Default";

	//	break;

	//case TILE_TYPES::ENEMY_SPAWNER:
	//	return "Enemy Spawner";
	//	break;

	//case TILE_TYPES::HEALING:
	//	return "Bed";
	//	break;

	//case TILE_TYPES::ITEM_BOX:
	//	return "Chest";
	//	break;

	//case TILE_TYPES::OVERHEAD:
	//	return "Overhead";
	//	break;

	//case TILE_TYPES::TELEPORT:
	//	return "Teleport - Blank";
	//	break;

	//case TILE_TYPES::TELEPORT_HOME:
	//	return "Teleport - Home";
	//	break;

	//case TILE_TYPES::TELEPORT_WORLD0:
	//	return "Teleport - World 2";
	//	break;

	//case TILE_TYPES::TELEPORT_WORLD1:
	//	return "Teleport - Third";
	//	break;

	//case TILE_TYPES::CAVE:

	//	return "Cave";
	//	break;

	//case TILE_TYPES::BREAKABLE:
	//
	//	return "Breakable";
	//	break;
	//}

	return "Unown";
}

const SDL_Rect& TileMap::getMaxSizeGrid() const{

	return this->maxSizeWorldGrid;
}

const SDL_FRect& TileMap::getMaxSizeF() const{

	return this->maxSizeWorldF;
}

//Functions

const bool TileMap::isTileEmpty(int x, int y, int z) const{

	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)

	{
		return this->map[x][y][z].empty();
	}

	return false;
}



/*

		RANDOM TILE MAP GENERATORS - three different tilemap generating functions, two create mazes and one creates cave-like structures...

*/

/*

	MAZE TYPE "PUT IT IN H"

*/

void TileMap::initRandomMaze(Cell Level[][SIZE]) {

	for (int i = 0; i < SIZE; i++) {

		for (size_t j = 0; j < SIZE; j++){

			Level[i][j].display = false;
			Level[i][j].visited = false;
			Level[i][j].bottom_wall = true;
			Level[i][j].top_wall = true;
			Level[i][j].left_wall = true;
			Level[i][j].right_wall = true;
			Level[i][j].exit = false;
		}
	}

	for (size_t i = 1; i < SIZE-1; i++){

		for (size_t j = 1; j < SIZE-1; j++){


			Level[1][j].top_wall = false;
			Level[SIZE - 2][j].bottom_wall = false;
			Level[i][1].left_wall = false;
			Level[i][SIZE - 2].right_wall = false;
		}
	}
}

void TileMap::generateMaze2(Cell level[][SIZE], int &posX, int &posY, int &goalX, int &goalY) {

	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> diceDistribution(1, SIZE);
	std::uniform_int_distribution<int> randDist(1, 4);

	int randomX = diceDistribution(generator);
	int randomY = diceDistribution(generator);

	if (randomX % 2 == 0) {

		if (randomX + 1 >= SIZE) {
			randomX -= 1;
		}
		else
			randomX += 1;
	}

	if (randomY % 2 == 0) {

		if (randomY + 1 >= SIZE) {
			randomY -= 1;
		}
		else
			randomY += 1;
	}

	posX = randomX;
	posY = randomY;
	int visitedCells = 1;
	int totalCells = ((SIZE - 1) / 2)*((SIZE - 1) / 2);
	int percent = 0;
	std::stack<int> back_trackX, back_trackY;

	level[randomY][randomX].display = true;
	level[randomY][randomX].visited = true;


	while (visitedCells < totalCells) {

		if (((level[randomY - 2][randomX].visited == false) && (level[randomY][randomX].top_wall == true && level[randomY - 2][randomX].bottom_wall == true)) ||
			((level[randomY + 2][randomX].visited == false) && (level[randomY][randomX].bottom_wall == true && level[randomY + 2][randomX].top_wall == true)) ||
			((level[randomY][randomX - 2].visited == false) && (level[randomY][randomX].left_wall == true && level[randomY][randomX - 2].right_wall == true)) ||
			((level[randomY][randomX + 2].visited == false) && (level[randomY][randomX].right_wall == true && level[randomY][randomX + 2].left_wall == true))) {

			int random = randDist(generator);


			//GO UP
			if ((random) == 1 && (randomY > 1)) {

				if (level[randomY - 2][randomX].visited == false) {

					level[randomY - 1][randomX].display = true;
					level[randomY - 1][randomX].visited = true;
					level[randomY][randomX].top_wall = false;

					back_trackX.push(randomX);
					back_trackY.push(randomY);

					randomY -= 2;

					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = true;
					level[randomY][randomX].bottom_wall = false;

					visitedCells++;
				}
				else {

					continue;
				}
			}

			//GO DOWN
			else if ((random == 2) && (randomY < SIZE - 2)) {

				if (level[randomY + 2][randomX].visited == false) {

					level[randomY + 1][randomX].display = true;
					level[randomY + 1][randomX].visited = true;
					level[randomY][randomX].bottom_wall = false;


					back_trackX.push(randomX);
					back_trackY.push(randomY);


					randomY += 2;
					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = true;
					level[randomY][randomX].top_wall = false;

					visitedCells++;

				}
				else {

					continue;
				}
			}

			//GO LEFT
			else if ((random == 3) && (randomX > 1)) {

				if (level[randomY][randomX - 2].visited == false) {

					level[randomY][randomX - 1].display = true;
					level[randomY][randomX - 1].visited = true;
					level[randomY][randomX].left_wall = false;


					back_trackX.push(randomX);
					back_trackY.push(randomY);

					randomX -= 2;
					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = true;
					level[randomY][randomX].right_wall = false;

					visitedCells++;
				}
				else {

					continue;
				}
			}

			//GO RIGHT
			else if ((random == 4) && (randomX < SIZE - 2)) {


				if (level[randomY][randomX + 2].visited == false) {

					level[randomY][randomX + 1].visited = true;
					level[randomY][randomX + 1].display = true;
					level[randomY][randomX].right_wall = false;

					back_trackX.push(randomX);
					back_trackY.push(randomY);

					randomX += 2;

					level[randomY][randomX].visited = true;
					level[randomY][randomX].display = true;
					level[randomY][randomX].left_wall = false;

					visitedCells++;
				}
				else {

					continue;
				}
			}

			percent = (visitedCells * 100 / totalCells * 100) / 100; //Gives progress as a percentage for loading screen
			std::cout << std::endl << "Generating random maze...." << percent << "%" << std::endl;
		}
		else {
			randomX = back_trackX.top();
			back_trackX.pop();

			randomY = back_trackY.top();
			back_trackY.pop();
		}
	}

	goalX = 0;
	goalY = randomY;

	level[goalY][goalX].display = true;
	level[goalY][goalX].exit = true;
	//sf::IntRect rect = { 112, 0, 16, 16 };
	//this->AddTile(goalX, goalY, 0, rect, true, 10);
}

void TileMap::autoAddCells(Cell level[][SIZE]) {

	for (size_t i = 0; i < SIZE; i++){

		for (int j = 0; j < SIZE; j++) {

			if (level[i][j].display) {

				SDL_Rect textureRect;

				if (level[i][j].exit) {

					textureRect = { 192, 0, 64, 64 };
					this->AddTile(i, j, 0, textureRect, true, 10);
				}
				else {

					textureRect = { 128, 0, 64, 64 };
					this->AddTile(i, j, 0, textureRect, false, 0);
				}
			}
			else {

				SDL_Rect textureRect = { 64, 0, 64, 64 };
				this->AddTile(i, j, 0, textureRect, true, 0);
			}
		}
	}
}

///void TileMap::findPlayerStartingTile(Entity* entity) {
////
////	//int x = entity->getGridPosition(16).x;
////	//int y = entity->getGridPosition(16).y;
////
////
////	for (size_t x = 0; x < this->map.size(); x++){
////
////		for (size_t y = 0; y < this->map[x].size(); y++){
////
////			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++){
////
////				if (this->map[x][y][this->layer][k]->getCollision() == false) {
////
////					int setX = this->map[x][y][this->layer][k]->getPosition().x;
////					int setY = this->map[x][y][this->layer][k]->getPosition().y;
////
////					entity->setPosition(static_cast<float>(setX), static_cast<float>(setY));
////
////					return;
////				}
////			}
////		}
////	}
////
////	//if (maze[x][y] == false) {
////
////	//	//Do nothing player is on an open tile already
////	//	std::cout << "CAN ADD!";
////	//}
////	//else {
////
////
////	//	int aliveNeighbours = this->countAliveNeighbours(this->maze, x, y);
////
////	//	if (aliveNeighbours > 0 && aliveNeighbours < 8) {
////
////	//		for (size_t i = x - (aliveNeighbours / 2); i <= x + (aliveNeighbours / 2); i++){
////
////	//			if (maze[i][y] == false) {
////
////	//				entity->setPosition(i, y);
////
////	//				return;
////	//			}
////
////	//			else {
////
////	//				for (size_t i = 0; i < this->maxSizeWorldGrid.x; i++){
////
////	//					if (maze[i][y] == false) {
////
////	//						entity->setPosition(i, y);
////	//					}
////	//				}
////	//			}
////	//		}
////	//	}
////	//	else {
////
////	//		for (size_t y = 0; y < this->maxSizeWorldGrid.x; y++) {
////
////	//			if (maze[x][y] == false) {
////
////	//				entity->setPosition(x, y);
////	//			}
////	//		}
////	//	}
////	//}
///}

void TileMap::autoAddTiles() {

	/*


			CREATING THE MAZE

	*/

	for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

			if (maze[x][y] == false) {

				//Add floor tile
				SDL_Rect textureRect = { 192, 0, 64, 64 };
				this->AddTile(x, y, 0, textureRect, false, 0);
			}
			else {

				//Add wall tile

				SDL_Rect textureRect = { 64, 0, 64, 64 };
				std::vector<int> flags;
				flags.push_back(BREAKABLE);
				//this->AddTile2(x, y, 0, textureRect, BREAKABLE, flags);
				this->AddTile(x, y, 0, textureRect, true, BREAKABLE);
				//this->AddTile(x,  y, 0.f, )
			}
		}
	}
}


/*

	MAZE TYPE "G"

*/


void TileMap::runPerfectMazeGenerator() {

	float chanceToStayAlive = 40.f;

	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> diceDistribution(0, 100);


	int numberOfSteps = 2;

	//this->runMazeGenerator();

	this->maze.resize(this->maxSizeWorldGrid.y);

	for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {

		this->maze[y].resize(this->maxSizeWorldGrid.x);
	}

	for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

		for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {


			int dice = diceDistribution(generator);
			if (dice < chanceToStayAlive) {

				this->maze[x][y] = true;
			}
			else {

				this->maze[x][y] = false;
			}
		}
	}

	for (int i = 0; i < numberOfSteps; i++) {

		this->doSimulationStep(this->maze);
	}

	this->autoAddTiles();

}

int TileMap::countAliveNeighbours(std::vector<std::vector<bool>> l_maze, int x, int y) {

	int count = 0;

	for (int i = -1; i < 2; i++) {

		for (int j = -1; j < 2; j++){

			int neigbour_x = x + i;
			int neighbour_y = y + j;

			//If middle point
			if (i == 0 && j == 0) {

				//Do nothing
			}

			//Check index is off the edge of the map
			else if (neigbour_x < 0 || neighbour_y < 0 || neigbour_x >= this->maxSizeWorldGrid.x || neighbour_y >= this->maxSizeWorldGrid.y) {

				count = count + 1;
			}

			//Otherwise a normal check
			else if (l_maze[neigbour_x][neighbour_y]) {

				count = count + 1;
			}
		}
	}

	return count;
}


void TileMap::doSimulationStep(std::vector<std::vector<bool>> l_maze) {

	std::vector<std::vector<bool>> newMap;

	newMap.resize(this->maxSizeWorldGrid.y);

	for (int y = 0; y < this->maxSizeWorldGrid.y; y++){

		newMap[y].resize(this->maxSizeWorldGrid.x);
	}

	int birthLimit = 4;
	int deathLimit = 3;

	for (size_t x = 0; x < l_maze.size(); x++) {

		for (size_t y = 0; y < l_maze[x].size(); y++) {

			int nbs = countAliveNeighbours(l_maze, x, y);

			if (l_maze[x][y]) {

				if (nbs < deathLimit) {

					newMap[x][y] = false;
				}
				else {

					newMap[x][y] = true;
				}
			}
			else {

				if (nbs > birthLimit) {

					newMap[x][y] = true;
				}
				else {

					newMap[x][y] = false;
				}
			}
		}
	}

	this->maze = newMap;
}


/*

	MAZE TYPE "F"

*/
void TileMap::runMazeGenerator(){

	float chanceToStayAlive = 55.f;

	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> diceDistribution(0, 100);


	maze.resize(this->maxSizeWorldGrid.y);

	for (int y = 0; y < this->maxSizeWorldGrid.y; y++){

		maze[y].resize(this->maxSizeWorldGrid.x);
	}

	for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

		for (int y = 0; y < this->maxSizeWorldGrid.y; y++){

			int dice = diceDistribution(generator);
			if (dice < chanceToStayAlive) {

				maze[x][y] = true;
			}
			else {

				maze[x][y] = false;
			}
		}
	}

	this->drillers.push_back(std::make_pair(this->maxSizeWorldGrid.x / 2, this->maxSizeWorldGrid.y / 2));

	while (drillers.size() > 0) {

		std::list<std::pair<int, int>>::iterator m, _m, temp;

		m = drillers.begin();
		_m = drillers.end();

		while (m != _m) {

			bool remove_driller = false;

			unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
			std::default_random_engine generator(seed);
			std::uniform_int_distribution<int> diceDistribution(0, 3);
			int dice = diceDistribution(generator);

			switch (dice) {

			case 0:

				(*m).second -= 2;
				if ((*m).second < 0 || maze[(*m).second][(*m).first]) {

					remove_driller = true;
					break;
				}

				maze[(*m).second + 1][(*m).first] = true;
				break;

			case 1:

				(*m).second += 2;

				if ((*m).second >= this->maxSizeWorldGrid.x || maze[(*m).second][(*m).first]) {

					remove_driller = true;
					break;
				}

				maze[(*m).second - 1][(*m).first] = true;
				break;

			case 2:

				(*m).first -= 2;
				if ((*m).first < 0 || maze[(*m).second][(*m).first]) {

					remove_driller = true;
					break;
				}

				maze[(*m).second][(*m).first + 1] = true;
				break;

			case 3:

				(*m).first += 2;
				if ((*m).first >= this->maxSizeWorldGrid.y || maze[(*m).second][(*m).first]) {

					remove_driller = true;
					break;
				}

				maze[(*m).second][(*m).first - 1] = true;
				break;
			}

			if (remove_driller) {

				m = drillers.erase(m);
			}
			else {

				drillers.push_back(std::make_pair((*m).first, (*m).second));


				if (dice % 2) {


					drillers.push_back(std::make_pair((*m).first, (*m).second));
				}

				maze[(*m).second][(*m).first] = true;
				++m;
			}
		}
	}

	this->autoAddTiles();
}

void TileMap::placeTreasure(int limit, int treasureChance) {

	int chanceOfTreasure = treasureChance;

	limit = limit;

	unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> diceDistribution(1, 100);

    ///TODO: Engine needs the get random faction function, call it here and assign to tileType.

	for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {

		for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {

			if (!this->maze[x][y]) {

				int nbs = this->countAliveNeighbours(this->maze, x, y);
				if (nbs >= limit) {


					int roll = diceDistribution(generator);

					if (roll <= chanceOfTreasure) {

                            int second = diceDistribution(generator);

						SDL_Rect rect = {0, 0, 0, 0};
						std::vector<int> numbers;

						if(second <= 50){
                            rect = { 128, 0, 64, 64 };
                            numbers = {2, 3, 4, 5, 6, 7, 8};
						}
						else{

                            rect = { 0, 0, 64, 64 };
                            numbers.push_back(9);
						}
                            RemoveTile(x, y, layer);
                            std::random_device rd;
                            std::mt19937 gen(rd());
                            std::uniform_int_distribution<> dis(numbers[0], numbers.back());
                            int randomIndex = dis(gen);
                            this->AddTile(x, y, 0, rect, true, randomIndex);
					}
				}
			}
		}
	}
}

void TileMap::Update() {


}

int TileMap::getNumOfEnemies() {

	int numEnemies = 0;

	//for (int x = 0; x < this->map.size(); x++) {

	//	for (int y = 0; y < this->map[x].size(); y++) {

	//		for (unsigned int k = 0; k < this->map[x][y].size(); k++) {

	//
	//		}
	//	}
	//}


	if (!this->map.empty()) {

		for (unsigned int x = 0; x < this->map.size(); x++) {

			for (size_t y = 0; y < this->map[x].size(); y++){

				for (unsigned int z = 0; z < this->map[x][y].size(); z++) {

					for (size_t k = 0; k < this->map[x][y][z].size(); k++) {


						if (this->map[x][y][z][k]->getType() == TILE_TYPES::ENEMY_SPAWNER) {

							std::cout << "HERE!";
							numEnemies++;
						}
					}
				}
			}
		}
	}

	return numEnemies;
}

void TileMap::disableEnemy(const unsigned int x, const unsigned int y) {

	int z = this->layer;

	if (!this->map.empty()) {

//		if (this->map[x][y][this->layer][0]->getType() == TILE_TYPES::ENEMY_SPAWNER) {

		if ((int)x < this->maxSizeWorldGrid.x && x >= 0 &&
			(int)y < this->maxSizeWorldGrid.y && y >= 0 &&
			z <= this->layers && z >= 0) {

			for (unsigned int i = 0; i < this->map[x][y][this->layer].size(); i++) {


				if(this->map[x][y][this->layer][i]->getType() == TILE_TYPES::ENEMY_SPAWNER){

					this->map[x][y][this->layer][i]->disableEnemySpawn();
				}
			}


		//	this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, textureRect, collision, type, teleport, dest));
		}
	//	}
	}
}

//std::vector<sf::Vector2f> TileMap::AddEnemies(std::vector<Enemy>& enemies) {
//
//	//If the current tile is an enemy spawner tile return true.
//
//	std::vector<sf::Vector2f> positions;
//
//	if (!this->map.empty()) {
//
//		for (unsigned int x = 0; x < this->map.size(); x++) {
//
//			for (unsigned int y = 0; y < this->map[x].size(); y++) {
//
//				for (unsigned int z = 0; z < this->map[x][y].size(); z++) {
//
//					for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
//
//
//						if (this->map[x][y][this->layer][k]->getType() == TILE_TYPES::ENEMY_SPAWNER) {
//
//							positions.push_back(this->map[x][y][this->layer][k]->getPosition());
//							//enemies.push_back()
//						}
//						//delete this->map[x][y][z][k];
//					//	this->map[x][y][z][k] = NULL;
//					}
//
//				//	this->map[x][y][z].clear();
//				}
//
//			//	this->map[x][y].clear();
//			}
//
//		//	this->map[x].clear();
//		}
//
//	//	this->map.clear();
//	}
//
//	for (int i = 0; i < positions.size(); i++) {
//
//		enemies.push_back(Enemy());
//
//		enemies[i].setPosition(positions[i].x, positions[i].y);
//	}
//
//	return positions;
//}

std::string TileMap::getTilePositionStr() {

	std::string posStr;
	int x, y;

	SDL_GetMouseState(&x, &y); //TODO - DOuble check`

	posStr =  "TILE X: " + std::to_string(this->map[x][y][this->layer][0]->getPosition().x);
	posStr += "  TILE Y: " + std::to_string(this->map[x][y][this->layer][0]->getPosition().y);

	return posStr;
}

void TileMap::setMapID(int id){

	do {
		MAP_IDENTIFIER++;
	} while (id != MAP_IDENTIFIER);

	if (id == MAP_IDENTIFIER) {

		this->mapID = MAP_IDENTIFIER;
	}
}

void TileMap::setSpawnsEnemies(int x, int y, bool choice) {


	if (this->map[x][y][this->layer][0]->getType() == ENEMY_SPAWNER) {

		this->spawnsEnemies = choice;

		if (choice == false && this->map[x][y][this->layer][0]->isActive()) {

			this->map[x][y][this->layer][0]->setActive(choice);
		}
	}

	/*for (unsigned int i = 0; i < this->map[x][y][this->layer].size(); i++) {

		if (this->map[x][y][this->layer][i]->getType() == ENEMY_SPAWNER) {

			this->spawnsEnemies = choice;
		}
	}*/
}

bool TileMap::getSpawnsEnemies() {

	return this->spawnsEnemies;
}

int TileMap::getMapID(){


	return this->mapID;
}

TileMap::~TileMap(){

    clear();
    this->tileSheet->free();
}

void TileMap::AddTile2(int x, int y, const int z, const SDL_Rect& textureRect, short type, std::vector<int> flags) {


//	std::vector<int> flags;
	std::string dest = " ";
	bool teleport = false;
	/* Takes three indices from the mouse Position, snaps to grid and adds a new tile. */
	if (type == TELEPORT_HOME) {

		dest = "Maps/first";
		teleport = true;
	}
	else if (type == TELEPORT_WORLD0) {

		dest = "Maps/second";
		teleport = true;
	}
	else if (type == TELEPORT_WORLD1) {

		dest = "Maps/third";
		teleport = true;
	}
	else {

		dest = " ";
		teleport = false;
	}


	//DEBUG - PLEASE REMOVE
	if (type == TILE_TYPES::ENEMY_SPAWNER) {


		std::cout << "here";
	}

	/*if (type == TILE_TYPES::BREAKABLE) {

		flags.push_back(BREAKABLE);
	}

	if (type == TILE_TYPES::BROKEN) {

		flags.push_back(BROKEN);
	}*/

	if (this->map.empty()) {

		this->resizeMap(this->maxSizeWorldGrid.x, this->maxSizeWorldGrid.y);
	}

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z <= this->layers && z >= 0) {

		//this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, textureRect, collision, type, teleport, dest));
		this->map[x][y][z].push_back(std::make_shared<Tile>(x, y, static_cast<int>(this->gridSizeF), *this->tileSheet, textureRect, type, flags));
	}
}

void TileMap::AddTile(const int x, const int y, const int z, const SDL_Rect& textureRect, const bool& collision, const short& type){


	std::string dest = " ";
	bool teleport = false;
	/* Takes three indices from the mouse Position, snaps to grid and adds a new tile. */
	if (type == TELEPORT_HOME) {

		dest = "Maps/first";
		teleport = true;
	}
	else if(type == TELEPORT_WORLD0) {

		dest = "Maps/second";
		teleport = true;
	}
	else if (type == TELEPORT_WORLD1) {

		dest = "Maps/third";
		teleport = true;
	}
	else {

		dest = " ";
		teleport = false;
	}


	//DEBUG - PLEASE REMOVE
	if (type == TILE_TYPES::ENEMY_SPAWNER) {


		std::cout << "here";
	}

	if (this->map.empty()) {

		this->resizeMap(this->maxSizeWorldGrid.x, this->maxSizeWorldGrid.y);
	}

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z <= this->layers && z >= 0) {

		    ///TODO: SMART POINTERS PLEASE!!!

			this->map[x][y][z].push_back(std::make_shared<Tile>(x, y, static_cast<int>(this->gridSizeF), *this->tileSheet, textureRect, collision, type, teleport, dest));
	}
}

void TileMap::RemoveTile(const int x, const int y, const int z){

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z <= this->layers && z >= 0
		) {

		if (!this->map[x][y][z].empty()) { //Checks can add tile

			//delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
		}
	}
}


void TileMap::saveWithID(int id, int charID) {

	//THIS MIGHT WORK

	std::string dirName = "Data\\Auto_" + std::to_string(charID);

	if (id == -1) {

		this->SaveToFile("Maps/test.map");
	}
	else {

		this->SaveToFile(dirName + "\\auto_" + std::to_string(charID) + std::to_string(id) + ".map");

	}

	if (id == MAP_ID::WORLD_0) {

//		this->SaveToFile("Data/auto_" + std::to_string(charID) + std::to_string(id) + ".map");
		//this->SaveToFile("Data/playTest" + std::to_string(charID) + ".txt");
//		this->mapID = MAP_ID::WORLD_0;
	}
	if (id == MAP_ID::WORLD_1) {

	//	this->SaveToFile("Data/auto_" + std::to_string(charID) + std::to_string(id) + ".map");
		//this->SaveToFile("Data/playTest2" + std::to_string(charID) + ".txt");
	//	this->mapID = MAP_ID::WORLD_1;
	}
}

//void TileMap::SaveToFileNEW(const std::string fileName) {
//
//	/*
//		Saves current tileMap to a text file
//
//	float gridSizeF;
//	unsigned gridSizeU;
//	unsigned layers;
//	sf::Vector2u maxSize;
//	std::vector<std::vector<std::vector<Tile *> > > map;
//	sf::Texture tileSheet;
//	*/
//
//	//std::ofstream binOut;
//
//	//binOut.open("data.bin", ios::out | ios::binary);
//	//char buffer[200];
//	//if (binOut.is_open()) {
//
//
//	//	binOut.seekp(0);
//	//	binOut.write(buffer, 200);
//
//
//
//	//	binOut.write(buffer, 200);
//	//}
//
//	std::ofstream outFile;
//
//	outFile.open(fileName, ios::app);
//
//	if (outFile.is_open()) {
//
//	//	outFile << "THIS HELLO NJKDHFKJSDGFHDSG\n";
//
//		outFile << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n" <<
//			this->gridSizeI << "\n" <<
//			this->layers << "\n" <<
//			this->textureFile << "\n";
//
//
//		for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {
//
//
//			for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {
//
//
//				for (int z = 0; z < this->layers; z++) {
//
//					if (!this->map[x][y][z].empty())
//
//						for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
//
//							outFile << x << " " << " " << y << " " << z << " " <<
//								this->map[x][y][z][k]->getAsString() << " ";
//
//						}
//				}
//			}
//		}
//
//		std::cout << "Saved Game\n";
//
//	}
//	else {
//
//		std::cout << "Error saving tilemap, SaveToFile() in TileMap.cpp: " << fileName << "\n";
//	}
//
//	outFile.close();
//}

void TileMap::SaveToFile(const std::string fileName, bool generateID, int ID){

	/*
		Saves current tileMap to a text file

	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile *> > > map;
	sf::Texture tileSheet;
	*/
	if (generateID) {

		this->mapID = ID;
	}

	std::ofstream outFile;

	outFile.open(fileName);

	if (outFile.is_open()) {

		outFile << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n" <<
			this->gridSizeI << "\n" <<
			this->layers << "\n" <<
			this->textureFile << "\n" <<
			this->mapID << "\n";


		for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {


			for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {


				for (int z = 0; z < this->layers; z++) {

					if(!this->map[x][y][z].empty())

						for (size_t k = 0; k < this->map[x][y][z].size(); k++){

							outFile << x << " " << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString() << " ";

						}
				}
			}
		}

		std::cout << "Saved Game\n";

	}
	else {

		std::cout << "Error saving tilemap, SaveToFile() in TileMap.cpp: " << fileName << "\n";
	}

	outFile.close();
}

void TileMap::resizeMap(int x, int y) {

	this->maxSizeWorldGrid.x = x;
	this->maxSizeWorldGrid.y = y;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {


		for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {

			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<std::shared_ptr<Tile>>>());

			for (int z = 0; z < this->layers; z++) {

				this->map[x][y].resize(this->layers, std::vector<std::shared_ptr<Tile>>());
			}
		}
	}
}

void TileMap::createFromSave(int l_x, int l_y, int l_z, int tr_x, int tr_y, bool l_collision, short l_type) {


}

//void TileMap::LoadFromFileNEW(const std::string fileName, const int lineOffset) {
//
//	this->clear();
//
//	std::ifstream inFile;
//
//	std::string line = " ";
//	std::stringstream ss;
//	int count = 0;
//
//	inFile.open(fileName);
//
//	if (inFile.is_open()) {
//
//		/*while (count < lineOffset) {
//
//			getline(inFile, line);
//
//			count++;
//		}*/
//
//		sf::Vector2i l_size;
//		int l_gridSize = 0;
//		int l_layers = 0;
//		std::string l_textureFile = " ";
//		int l_x = 0;
//		int l_y = 0;
//		int l_z = 0;
//		int tr_x = 0;
//		int tr_y = 0;
//		bool l_collision = false;
//		short l_type = 0;
//		//int l_mapID = -1;
//
//		//Basics
//
//		inFile >> l_size.x >> l_size.y >> l_gridSize >> l_layers >> l_textureFile;
//
//
//		this->gridSizeI = l_gridSize;
//		this->gridSizeF = static_cast<float>(l_gridSize);
//		this->maxSizeWorldGrid.x = l_size.x;
//		this->maxSizeWorldGrid.y = l_size.y;
//		this->maxSizeWorldF.x = static_cast<float>(l_size.x * l_gridSize);
//		this->maxSizeWorldF.y = static_cast<float>(l_size.y * l_gridSize);
//		this->layers = l_layers;
//		this->textureFile = l_textureFile;
//	//	this->mapID = l_mapID;
//		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
//		for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {
//
//
//			for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {
//
//				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());
//
//				for (int z = 0; z < this->layers; z++) {
//
//					this->map[x][y].resize(this->layers, std::vector<Tile*>());
//				}
//			}
//		}
//		// "Resources/Images/Tiles/basicTiles.png"
//		if (!this->tileSheet.loadFromFile(this->textureFile))
//			std::cout << "Error loading tileTextureSheet : TileMap.cpp. File Name: " << this->textureFile << "\n";
//
//		//LOAD ALL TILES
//
//		while (inFile >> l_x >> l_y >> l_z >> tr_x >> tr_y >> l_collision >> l_type) {
//
//			if (l_type == 8) {
//
//				std::cout << "Pause";
//			}
//
//			this->map[l_x][l_y][l_z].push_back(new Tile(l_x, l_y, this->gridSizeF, this->tileSheet,
//				sf::IntRect(tr_x, tr_y, this->gridSizeI, this->gridSizeI), l_collision, l_type));
//		}
//	}
//	else {
//
//		std::cout << "Error loading tilemap, LoadFromFile() in TileMap.cpp: " << fileName << "\n";
//	}
//
//	inFile.close();
//}

void TileMap::LoadFromFile(const std::string fileName){

	this->clear();

	std::ifstream inFile;

	inFile.open(fileName);

	if (inFile.is_open()) {

		SDL_Rect l_size;
		int l_gridSize = 0;
		int l_layers = 0;
		std::string l_textureFile = " ";
		int l_x = 0;
		int l_y = 0;
		int l_z = 0;
		int tr_x = 0;
		int tr_y = 0;
		bool l_collision = false;
		short l_type = 0;
		int l_mapID = -1;

		//Basics
		inFile >> l_size.x >> l_size.y >> l_gridSize >> l_layers >> l_textureFile >> l_mapID;


		this->gridSizeI = l_gridSize;
		this->gridSizeF = static_cast<float>(l_gridSize);
		this->maxSizeWorldGrid.x = l_size.x;
		this->maxSizeWorldGrid.y = l_size.y;
		this->maxSizeWorldF.x = static_cast<float>(l_size.x * l_gridSize);
		this->maxSizeWorldF.y = static_cast<float>(l_size.y * l_gridSize);
		this->layers = l_layers;
		this->textureFile = l_textureFile;
		this->mapID = l_mapID;
		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++) {


			for (int y = 0; y < this->maxSizeWorldGrid.y; y++) {

				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<std::shared_ptr<Tile>>>());

				for (int z = 0; z < this->layers; z++) {

					this->map[x][y].resize(this->layers, std::vector<std::shared_ptr<Tile>>());
				}
			}
		}
		// "Resources/Images/Tiles/basicTiles.png"
			//if (!this->tileSheet.loadFromFile(this->textureFile))
			//	std::cout << "Error loading tileTextureSheet : TileMap.cpp. File Name: " << this->textureFile << "\n";

		//LOAD ALL TILES

		while (inFile >> l_x >> l_y >> l_z >> tr_x >> tr_y >> l_collision >> l_type ) {

			SDL_Rect temp = { tr_x, tr_y, gridSizeI, gridSizeI };

			//CHANGE l_x && l_y to tr_x & tr_y
			this->map[l_x][l_y][l_z].push_back(std::make_shared<Tile>(l_x, l_y, static_cast<int>(this->gridSizeF), *this->tileSheet,
				temp, l_collision, l_type));
		}
	}
	else {

		std::cout << "Error loading tilemap, LoadFromFile() in TileMap.cpp: " << fileName << "\n";
	}

	inFile.close();
}

void TileMap::loadFromID(int ID, int charID) {

	if (ID == -1) {

		//TODO - (if bigTiles == true) this VVVV. Else load Maps/first
		this->LoadFromFile("Maps/first");

		this->mapID = MAP_ID::WORLD_0;
	}
	else {

		std::string dirName = "Data\\Auto_" + std::to_string(charID);

		if (!std::filesystem::is_directory(dirName) || !std::filesystem::exists(dirName)) {

			std::filesystem::create_directory(dirName);
		}

		if (std::filesystem::exists(dirName + "\\auto_" + std::to_string(charID) + std::to_string(ID) + ".map")) {



			this->LoadFromFile(dirName + "\\auto_" + std::to_string(charID) + std::to_string(ID) + ".map");
		}

		else{

				//Character has data but nothing saved on this map

				if (ID == MAP_ID::WORLD_0) {

					this->LoadFromFile("Maps/First");
				}

				else if (ID == MAP_ID::WORLD_1) {

					this->LoadFromFile("Maps/Second");
				}
				else if (ID == MAP_ID::WORLD_2) {

					this->LoadFromFile("Maps/Third");
				}
				else {

					this->LoadFromFile("Maps/third");
				}
		}
			//Open file. Ignore first 11 lines as this is player DATA.

			//this->LoadFromFileNEW("Data/auto_" + std::to_string(charID) + ".DATA")
	}

	/*if (ID == 1) {

		this->LoadFromFile("Maps/first");

		this->mapID = MAP_ID::WORLD_0;
	}
	else if(ID == 2){

		this->LoadFromFile("Maps/second");

		this->mapID = MAP_ID::WORLD_1;
	}*/
}

int TileMap::getID() {

	return this->mapID;
}

int TileMap::getTileType(unsigned x, unsigned y, unsigned z){

    int s = this->map.size();

	if (x >= 0 && x < this->map.size()){

        if(y >= 0 && y < map.size()){

            if (!map[x][y][z].empty()) {

                return map[x][y][0][z]->getType();
            }
        }
	}

	return -1;
}

///void TileMap::updateCollision(Entity * entity, const float& dt){
//
//	/************** WORLD BOUNDS *****************/
//
//	//CHECK COLLISION ON X AXIS
//	//if (entity->getPosition().x < 0.f) {
//	//	entity->stopVelocityX();
//	//	entity->setPosition(0.f, entity->getPosition().y);
//	//}
//
//	//else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x) {
//
//	//	entity->stopVelocityX();
//	//	entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
//	//}
//
//	////CHECK COLLISION ON Y AXIS
//	//if (entity->getPosition().y < 0.f) {
//
//	//	entity->stopVelocityY();
//	//	entity->setPosition(entity->getPosition().x, 0.f);
//	//}
//	//else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y) {
//
//	//	entity->stopVelocityY();
//	//	entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
//	//}
//
//
//
//	///************** TILE BOUNDS *****************/
//	////TODO REFACTOR TO USE ITERATORS
//
//	//this->layer = 0;
//	//this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
//	//if (this->fromX < 0) {
//
//	//	this->fromX = 0;
//	//}
//	//else if (this->fromX > this->maxSizeWorldGrid.x) {
//
//	//	this->fromX = this->maxSizeWorldGrid.x;
//	//}
//
//	//this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
//	//if (this->toX < 0) {
//
//	//	this->toX = 0;
//	//}
//	//else if (this->toX > this->maxSizeWorldGrid.x) {
//
//	//	this->toX = this->maxSizeWorldGrid.x;
//	//}
//
//
//	//this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
//	//if (this->fromY < 0) {
//
//	//	this->fromY = 0;
//	//}
//	//else if (this->fromY > this->maxSizeWorldGrid.y) {
//
//	//	this->fromY = this->maxSizeWorldGrid.y;
//	//}
//
//	//this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
//	//if (this->toY < 0) {
//
//	//	this->toY = 0;
//	//}
//	//else if (this->toY > this->maxSizeWorldGrid.y) {
//
//	//	this->toY = this->maxSizeWorldGrid.y;
//	//}
//}

///void TileMap::UpdateTileCollision(Entity * entity, const float& dt) {
//
//	// *****************************************
//
//	//for (int x = this->fromX; x < this->toX; x++) {
//
//
//	//	for (int y = this->fromY; y < this->toY; y++) {
//
//	//		//if (this->map[x][y][this->layer] != NULL) {
//
//	//		for (unsigned int k = 0; k < this->map[x][y][this->layer].size(); k++) {
//
//
//	//			sf::FloatRect playerBounds = entity->getGlobalBounds();
//	//			sf::Vector2f playerPos = entity->getPosition();
//	//			sf::Vector2i playerPosI = entity->getGridPosition(16);
//	//			sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
//	//			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);
//	//			sf::FloatRect itemBoxBounds;
//
//	//			if (this->map[x][y][this->layer][k]->getType() == ITEM_BOX) {
//
//	//				itemBoxBounds.height = this->map[x][y][this->layer][k]->getGlobalBounds().height / 2;
//	//				itemBoxBounds.width = this->map[x][y][this->layer][k]->getGlobalBounds().width;
//	//			}
//
//	//			if (this->map[x][y][this->layer][k]->getType() == OVERHEAD) {
//
//
//	//				if (this->map[x][y][this->layer][k]->intersects(playerBounds)) {
//
//	//					this->map[x][y][this->layer][k]->setOpacity(150);
//	//				}
//	//				else {
//
//	//					this->map[x][y][this->layer][k]->setOpacity(255);
//	//				}
//	//			}
//
//	//			if (this->map[x][y][this->layer][k]->getType() == DAMAGING && this->map[x][y][this->layer][k]->intersects(playerBounds)) {
//
//	//				entity->loseHP(1);
//	//			}
//
//	//			/*if (this->map[x][y][this->layer][k]->getType() == HEALING && this->map[x][y][this->layer][k]->intersects(nextPositionBounds)) {
//
//	//				entity->stopVelocity();
//	//				entity->gainHP(100000);
//	//				this->infoBox->setVisible(true);
//	//				this->infoBox->setText("You awake feeling well rested!");
//	//			}*/
//
//
////TI//LE COLLISION CHECK
//	//			if (this->map[x][y][this->layer][k]->getCollision() && this->map[x][y][this->layer][k]->intersects(nextPositionBounds)) {
//
//	//				//lastPositionBounds = nextPositionBounds;
//
//
//
//	//				//if(nextPositionBounds.top == )
//	//				if (this->map[x][y][this->layer][k]->getType() == CAVE) {
//
//	//					int id = dynamic_cast<Player*>(entity)->getID();
//	//					//Save this map, teleport to a new map which is made with the random generator
//	//					this->saveWithID(this->mapID, id);
//
//	//					unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
//	//					std::default_random_engine generator(seed);
//	//					std::uniform_int_distribution<int> diceDistribution(0, 1);
//
//	//					int diceRoll = diceDistribution(generator);
//
//	//					if (diceRoll == 0) {
//
//	//						//F Gen
//	//						this->map.clear();
//	//						this->runMazeGenerator();
//	//						this->findPlayerStartingTile(entity);
//	//						this->placeTreasure();
//	//						this->mapID = 99998;
//
//	//					}
//	//					else if (diceRoll == 1) {
//
//	//						//G gen
//	//						this->map.clear();
//	//						this->runPerfectMazeGenerator();
//	//						this->findPlayerStartingTile(entity);
//	//						this->placeTreasure();
//	//						this->mapID = 99999;
//	//					}
//	//					else {
//
//	//						this->map.clear();
//	//						Cell level[SIZE][SIZE];
//	//						this->initRandomMaze(level);
//	//						int goalX, goalY = 0;
//	//						int x = entity->getGridPosition(16).x;
//	//						int y = entity->getGridPosition(16).y;
//	//						this->generateMaze2(level, x, y, goalX, goalY);
//	//						this->autoAddCells(level);
//	//						float xF = entity->getPosition().x;
//	//						float yF = entity->getPosition().y;
//	//						entity->setPosition(xF, yF);
//	//						this->findPlayerStartingTile(entity);
//
//	//						this->mapID = 99997;
//	//					}
//
//
//	//					//this->runPerfectMazeGenerator();
//	//					//new TileMap();
//	//
//	//					this->setMapID(mapID);
//	//					entity->setMapID(mapID);
//	//					//sf::IntRect rect = { 112, 0, 16, 16 };
//	//					//this->AddTile(goalX, goalY, 0, rect, true, 10);
//	//				}	//END CAVE`
//
//	//				if (this->map[x][y][this->layer][k]->getType() == TELEPORT) {
//
//	//
//	//					this->LoadFromFile(this->map[x][y][this->layer][k]->getDestination());
//	//				}
//
//	//				if (this->map[x][y][this->layer][k]->getType() == TELEPORT_HOME) {
//
//
//	//					this->Teleport(this->map[x][y][this->layer][k]->getType(), *entity);
//
//	//					return;
//	//				}
//
//	//				/*
//	//
//	//					TODO - SPLIT THESE INTO A TELEPORT FUNCTION
//	//
//	//				*/
//
//	//				if (this->map[x][y][this->layer][k]->getType() == TELEPORT_WORLD1) {
//
//
//	//					this->Teleport(this->map[x][y][this->layer][k]->getType(), *entity);
//	//					return;
//	//				}
//
//	//				if (this->map[x][y][this->layer][k]->getType() == TELEPORT_WORLD0) {
//
//
//	//					this->Teleport(this->map[x][y][this->layer][k]->getType(), *entity);
//
//	//					return;
//	//				}
//
//
//	//				//ENEMY_SPAWNER
//	//				if (this->map[x][y][this->layer][k]->getType() == ENEMY_SPAWNER) {
//
//	//					//Have an isActive function for tiles which can be used to control their state.. e.g open box, open door, enemys alive/defeated etc..
//
//	//					if (this->map[x][y][this->layer][k]->isActive()) {
//
//	//						this->spawnsEnemies = true;
//	//					}
//	//					else {
//
//	//						this->spawnsEnemies = false;
//	//					}
//
//	//				}
//
//
//	//					//Bottom Collision
//	//				else if (playerBounds.top < wallBounds.top &&
//	//					playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
//	//					playerBounds.left < wallBounds.left + wallBounds.width &&
//	//					playerBounds.left + playerBounds.width > wallBounds.left) {
//
//	//
//	//					//entity->setPosition(playerPos.x, playerPos.y);
//	//					entity->stopVelocityY();
//	//					//entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
//	//					//entity->setPosition(playerPos.x, wallBounds.top - playerBounds.height);
//	//
//	//				}
//
//
//	//				//Top collision
//	//				else if (playerBounds.top > wallBounds.top &&
//	//					playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
//	//					playerBounds.left < wallBounds.left + wallBounds.width &&
//	//					playerBounds.left + playerBounds.width > wallBounds.left) {
//
//	//			//		else {
//
//	//						//entity->setPosition(playerPos.x, playerPos.y);
//	//						entity->stopVelocityY();
//	//						//entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
//	//						//entity->setPosition(playerPos.x, wallBounds.top + wallBounds.height);
//	//			//		}
//	//				}
//
//	//
//
//
//
//
//	//				//RIGHT TESTING
//	//				else if (playerBounds.left < wallBounds.left &&
//	//					playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
//	//					playerBounds.top < wallBounds.top + wallBounds.height &&
//	//					playerBounds.top + playerBounds.height > wallBounds.top) {
//
//
//	//					//entity->setPosition(playerPos.x, playerPos.y);
//	//					entity->stopVelocityX();
//	//					//entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
//	//					//entity->setPosition(wallBounds.left - playerBounds.width, playerPos.y);
//
//	//				}
//
//
//	//				//Left Collision
//	//				else if (playerBounds.left > wallBounds.left &&
//	//					playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
//
//	//					playerBounds.top < wallBounds.top + wallBounds.height &&
//	//					playerBounds.top + playerBounds.height > wallBounds.top) {
//
//
//	//					//entity->setPosition(wallBounds.left + wallBounds.width + 2.f, playerBounds.top);
//	//					//entity->setPosition(playerPos.x, playerPos.y);
//	//					entity->stopVelocityX();
//	//					//entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
//	//					//entity->setPosition(wallBounds.left + wallBounds.width, playerPos.y);
//
//	//				}
//	//			}
//	//			//End tile Check
//
//	//		}
//	//		//} //END NULL CHECK
//	//	}	//END TILE CHECK
//	//}
//}

//void TileMap::UpdateSurroundingTiles(Entity* entity, const float& dt, std::vector<string>& ops, bool& choice) {
//
//	Player* player = dynamic_cast<Player*>(entity);
//
//	//if()
//
//
//
//	//********************************* X AXIS *****************************************************
//	if (player->getDirection() == LEFT) {
//
//		this->fromX = player->getGridPosition(16).x - 1;
//		this->toX = player->getGridPosition(16).x;
//
//
//		if (fromX < 0) {
//
//			fromX = 0;
//		}
//		if (fromX > this->maxSizeWorldGrid.x) {
//
//			this->fromX = this->maxSizeWorldGrid.x;
//		}
//
//		int y = player->getGridPosition(16).y;
//
//		for (int x = fromX; x < toX; x++) {
//			for (unsigned int k = 0; k < this->map[x][y][this->layer].size(); k++) {
//
////				if (player->getAttacking()) {
//
//					if (this->map[x][y][this->layer][k]->getType() == BREAKABLE) {
//
//						if (player->getEquippedToolType() == itemTypes::TOOL) {
//
//
//							if (player->checkDurability() > 0) {
//
//								this->map[x][y][this->layer][k]->breakRock();
//								player->loseDurability();
//
//
//								if (player->checkDurability() <= 0) {
//
//									this->infoBox->setText("ITEM BROKE!");
//									this->infoBox->setVisible(true);
//
//									//	player->removeItem(player->item)
//								}
//							}
//							else {
//
//								this->infoBox->setText("Cannot use broken item!");
//								this->infoBox->setVisible(true);
//							}
//						}
//					}
//					else if (this->map[x][y][this->layer][k]->getType() == ITEM_BOX) {
//
//						this->map[x][y][this->layer][k]->openBox();
//
//
//					unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
//					std::default_random_engine generator(seed);
//					std::uniform_int_distribution<int> diceDistribution(0, 2);
//
//
//					int roll = diceDistribution(generator);
//
//					if (roll < 1) {
//
//						Weapon w(dynamic_cast<Player*>(entity)->getLevel(), 0);
//						//std::make_shared<Item>(w);
//						auto av = make_shared<Weapon>(w);
//						dynamic_cast<Player*>(entity)->addItem(av);
//						infoBox->setText("ITEM AQUIRED! " + w.getTypeStr());
//						infoBox->setVisible(true);
//					}
//					else {
//
//						int lvl = dynamic_cast<Player*>(entity)->getLevel();
//						Tool t;
//
//						auto av = make_shared<Tool>(t);
//						dynamic_cast<Player*>(entity)->addItem(av);
//						infoBox->setText("ITEM AQUIRED! " + av->getToolName());
//						infoBox->setVisible(true);
//					}
//
//
//
//
//
//						this->saveWithID(this->mapID, dynamic_cast<Player*>(entity)->getID());
//					}
//
//					else if (this->map[x][y][this->layer][k]->getType() == HEALING) {
//
//						this->infoBox->setText("Rest? Restores health.");
//						this->infoBox->setVisible(true);
//						choice = true;
//						ops.push_back("Rest");
//						entity->stopVelocity();
//					}
//	//			}
//			}
//		}
//	}
//	if (player->getDirection() == RIGHT) {
//
//		this->fromX = player->getGridPosition(16).x;
//		this->toX = player->getGridPosition(16).x + 1;
//
//		int y = entity->getGridPosition(16).y;
//
//		if (toX < 0) {
//
//			toX = 0;
//		}
//		if (toX >= this->maxSizeWorldGrid.x) {
//
//			this->toX = this->maxSizeWorldGrid.x - 1;
//		}
//
//		for (int x = fromX; x <= toX; x++) {
//			for (unsigned int k = 0; k < this->map[x][y][this->layer].size(); k++) {
//
//				if (this->map[x][y][this->layer][k]->getType() == BREAKABLE) {
//
//		//			if (player->getAttacking()) {
//					if (player->getEquippedToolType() == itemTypes::TOOL) {
//
//						if (player->checkDurability() > 0) {
//
//							this->map[x][y][this->layer][k]->breakRock();
//							player->loseDurability();
//
//
//							if (player->checkDurability() <= 0) {
//
//								this->infoBox->setText("Item is BROKEN!");
//								this->infoBox->setVisible(true);
//								player->inv.addItemVectorSmart(player->getActiveTool());
//								player->removeActiveTool();
//							}
//						}
//						else {
//
//							this->infoBox->setText("Cannot use broken item!");
//							this->infoBox->setVisible(true);
//						}
//					}
//			//		}
//				}
//
//
//				else if (this->map[x][y][this->layer][k]->getType() == ITEM_BOX) {
//
//					//if (player->getAttacking()) {
//
//
//						this->map[x][y][this->layer][k]->openBox();
//
//						Weapon w(dynamic_cast<Player*>(entity)->getLevel(), 0);
//						//std::make_shared<Item>(w);
//						auto av = make_shared<Weapon>(w);
//
//						dynamic_cast<Player*>(entity)->addItem(av);
//
//
//						infoBox->setText("ITEM AQUIRED! " + w.getTypeStr());
//						infoBox->setVisible(true);
//
//
//						this->saveWithID(this->mapID, dynamic_cast<Player*>(entity)->getID());
//					//}
//				}
//
//			}
//		}
//	}
//
//
//
//	//********************************** Y AXIS **************************************************************
//
//	if (player->getDirection() == UP) {
//
//		this->fromY = player->getGridPosition(16).y - 1;
//		this->toY = player->getGridPosition(16).y;
//
//
//		if (fromY < 0) {
//
//			fromY = 0;
//		}
//		if (fromY > this->maxSizeWorldGrid.y) {
//
//			this->fromY = this->maxSizeWorldGrid.y;
//		}
//
//		int x = player->getGridPosition(16).x;
//
//		for (int y = fromY; y < toY; y++) {
//			for (unsigned int k = 0; k < this->map[x][y][this->layer].size(); k++) {
//
//				if (this->map[x][y][this->layer][k]->getType() == BREAKABLE) {
//
//					//if (player->getAttacking()) {
//					if (player->getEquippedToolType() == itemTypes::TOOL) {
//
//						if (player->checkDurability() > 0) {
//
//							this->map[x][y][this->layer][k]->breakRock();
//							player->loseDurability();
//
//
//							if (player->checkDurability() <= 0) {
//
//								this->infoBox->setText("ITEM BROKE!");
//								this->infoBox->setVisible(true);
//							}
//						}
//						else {
//
//							this->infoBox->setText("Cannot use broken item!");
//							this->infoBox->setVisible(true);
//						}
//					}
//					//}
//				}
//
//				else if (this->map[x][y][this->layer][k]->getType() == ITEM_BOX) {
//
//					//if (player->getAttacking()) {
//
//
//						this->map[x][y][this->layer][k]->openBox();
//
//						Weapon w(dynamic_cast<Player*>(entity)->getLevel(), 0);
//						//std::make_shared<Item>(w);
//						auto av = make_shared<Weapon>(w);
//
//						dynamic_cast<Player*>(entity)->addItem(av);
//
//
//						infoBox->setText("ITEM AQUIRED! " + w.getTypeStr());
//						infoBox->setVisible(true);
//
//
//						this->saveWithID(this->mapID, dynamic_cast<Player*>(entity)->getID());
//					//}
//				}
//			}
//
//		}
//	}
//	if (player->getDirection() == DOWN) {
//
//		this->fromY = player->getGridPosition(16).y;
//		this->toY = player->getGridPosition(16).y + 1;
//
//
//		if (toY < 0) {
//
//			toY = 0;
//		}
//		if (toY >= this->maxSizeWorldGrid.y) {
//
//			this->toY = this->maxSizeWorldGrid.y - 1;
//		}
//
//		int x = player->getGridPosition(16).x;
//
//		for (int y = fromY; y <= toY; y++) {
//			for (unsigned int k = 0; k < this->map[x][y][this->layer].size(); k++) {
//
//				if (this->map[x][y][this->layer][k]->getType() == BREAKABLE) {
//
//					//if (player->getAttacking()) {
//					if (player->getEquippedToolType() == itemTypes::TOOL) {
//
//						if (player->checkDurability() > 0) {
//
//							this->map[x][y][this->layer][k]->breakRock();
//							player->loseDurability();
//
//
//							if (player->checkDurability() <= 0) {
//
//								this->infoBox->setText("ITEM BROKE!");
//								this->infoBox->setVisible(true);
//								player->inv.addItemVectorSmart(player->getActiveTool());
//								player->removeActiveTool();
//							}
//						}
//						else {
//
//							this->infoBox->setText("Cannot use broken item!");
//							this->infoBox->setVisible(true);
//						}
//					}
//					//}
//				}
//
//				else if (this->map[x][y][this->layer][k]->getType() == ITEM_BOX) {
//
//					//if (player->getAttacking()) {
//
//
//						this->map[x][y][this->layer][k]->openBox();
//
//						Weapon w(dynamic_cast<Player*>(entity)->getLevel(), 0);
//						//std::make_shared<Item>(w);
//						auto av = make_shared<Weapon>(w);
//
//						dynamic_cast<Player*>(entity)->addItem(av);
//
//
//						infoBox->setText("ITEM AQUIRED! " + w.getTypeStr());
//						infoBox->setVisible(true);
//
//
//						this->saveWithID(this->mapID, dynamic_cast<Player*>(entity)->getID());
//					//}
//				}
//			}
//
//		}
//	}
//}

//void TileMap::Teleport(int dest, Entity& entity) {
//
//		int id = dynamic_cast<Player&>(entity).getID();
//		std::string dirName = "Data\\Auto_" + std::to_string(id);
//
//
//		if (!experimental::filesystem::is_directory(dirName) || !experimental::filesystem::exists(dirName)) {
//
//			experimental::filesystem::create_directory(dirName);
//		}
//
//		saveWithID(this->mapID, id);
//		entity.stopVelocity();
//		int prevID = this->mapID;
//
//		if (dest == TELEPORT_WORLD0) {
//
//			this->mapID = MAP_ID::WORLD_1;
//			entity.setMapID(this->mapID);
//			if (prevID == 0) {
//
//				entity.setPosition(146.f, 50.f);
//			}
//			else if (prevID == 2) {
//
//				entity.setPosition(242.f, 82.f);
//			}
//		}
//
//		if (dest == TELEPORT_HOME) {
//
//
//			this->mapID = MAP_ID::WORLD_0;
//			entity.setMapID(this->mapID);
//			entity.setPosition(146.f, 150.f);
//		}
//
//		if (dest == TELEPORT_WORLD1) {
//
//			this->mapID = MAP_ID::WORLD_2;	//
//			entity.setMapID(this->mapID);
//			entity.setPosition(52.f, 190.f);
//		}
//
//		if (experimental::filesystem::exists(dirName + "\\auto_" + std::to_string(id) + std::to_string(this->mapID) + ".map")) {
//
//			//	this->LoadFromFile("playTest2" + std::to_string(dynamic_cast<Player*>(entity)->getID()) + ".txt");
//			//this->saveWithID(prevID, id);
//			//this->map.clear();
//			this->loadFromID(this->mapID, id);
//		}
//		else {
//
//			if (dest == TELEPORT_HOME) {
//
//				this->LoadFromFile("Maps/first");
//			}
//			else if (dest == TELEPORT_WORLD0) {
//
//				this->LoadFromFile("Maps/second");
//			}
//			else if (dest == TELEPORT_WORLD1) {
//
//				this->LoadFromFile("Maps/third");
//			}
//		}
//
//		this->saveWithID(this->mapID, id);
//		//this->SaveToFile("playTest" + std::to_string(dynamic_cast<Player*>(entity)->getID()) + ".txt")
//}

void TileMap::updateGUI(){

}

void TileMap::render(SDL_Renderer * target, SDL_Rect cam) {

	layer = 0;
	int x, y;
	SDL_GetMouseState(&x, &y);
	x /= gridSizeI;
	y /= gridSizeI;


	fromX = x - cam.w;
	if (fromX < 0) {

		fromX = 0;
	}
	else if (fromX > maxSizeWorldGrid.x) {

		fromX = maxSizeWorldGrid.x;
	}

	toX = x + cam.w;
	if (toX < 0) {

		toX = 0;
	}
	else if (toX > maxSizeWorldGrid.x) {

		toX = maxSizeWorldGrid.x;
	}

	//Y

	fromY = x - cam.h;
	if (fromY < 0) {

		fromY = 0;
	}
	else if (fromY > maxSizeWorldGrid.y) {

		fromY = maxSizeWorldGrid.y;
	}

	toY = y + cam.h;
	if (toY < 0) {

		toY = 0;
	}
	else if (toY > maxSizeWorldGrid.y) {

		toY = maxSizeWorldGrid.y;
	}

	for (int x = fromX; x < toX; x++) {

		for (int y = fromY; y < toY; y++) {

			for (unsigned int k = 0; k < map[x][y][layer].size(); k++) {

                map[x][y][layer][k]->Render(target, cam);
			}
		}
	}
}

//void TileMap::Render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, sf::Shader* shader, const sf::Vector2f playerPosition) {
//
//
//	//target.draw(this->nextCollisionBox);
//
//	//if (entity) {
//
//
//		this->layer = 0;
//
//		this->fromX = gridPosition.x - 14;
//		if (this->fromX < 0) {
//
//			this->fromX = 0;
//		}
//		else if (this->fromX > this->maxSizeWorldGrid.x) {
//
//			this->fromX = this->maxSizeWorldGrid.x;
//		}
//
//		this->toX = gridPosition.x + 15;
//		if (this->toX < 0) {
//
//			this->toX = 0;
//		}
//		else if (this->toX > this->maxSizeWorldGrid.x) {
//
//			this->toX = this->maxSizeWorldGrid.x;
//		}
//
//
//		this->fromY = gridPosition.y - 12;
//		if (this->fromY < 0) {
//
//			this->fromY = 0;
//		}
//		else if (this->fromY > this->maxSizeWorldGrid.y) {
//
//			this->fromY = this->maxSizeWorldGrid.y;
//		}
//
//		this->toY = gridPosition.y + 15;
//		if (this->toY < 0) {
//
//			this->toY = 0;
//		}
//		else if (this->toY >= this->maxSizeWorldGrid.y) {
//
//			this->toY = (this->maxSizeWorldGrid.y);
//		}
//
//		//********
//
//		for (int x = this->fromX; x < this->toX; x++) {
//
//
//			for (int y = this->fromY; y < this->toY; y++) {
//
//				//if (this->map[x][y][this->layer] != NULL) {
//
//				for (unsigned int k = 0; k < this->map[x][y][this->layer].size(); k++){
//
//					if (this->map[x][y][this->layer][k]->getType() == TILE_TYPES::OVERHEAD) {
//
//						this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
//					}
//					else {
//						if (shader) {
//
//							this->map[x][y][this->layer][k]->Render(target, shader, playerPosition);
//						}
//						else {
//
//							this->map[x][y][this->layer][k]->Render(target);
//						}
//					}
//
//
//
//					if (this->map[x][y][this->layer][k]->getCollision()) {
//
//						this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
//						if(this->showHitbox)
//							target.draw(this->collisionBox);
//					}
//
//
//				//} //END NULL CHECK
//				}
//
//			}
//		}
//
//	//} //END ENTITY CHECK
//
//	//********
//
//	//else {
//
//	//	//********************************************************
//	//	for (auto& x : this->map) {
//
//	//		for (auto& y : x) {
//
//	//			for (auto &z : y) {
//
//	//				for (auto &k : z) {
//
//	//					k->Render(target);
//	//					if (k->getCollision()) {
//
//	//						this->collisionBox.setPosition(k->getPosition());
//	//						target.draw(this->collisionBox);
//	//					}
//	//				}
//	//			}
//	//		}
//	//	}
//	//}
//}
//
//void TileMap::renderDeferredStack(sf::RenderTarget & target, sf::Shader* shader, const sf::Vector2f playerPosition){
//
//	while (!this->deferredRenderStack.empty()) {
//
//		if (shader) {
//
//			deferredRenderStack.top()->Render(target, shader, playerPosition);
//		}
//		else {
//
//			deferredRenderStack.top()->Render(target);
//		}
//		deferredRenderStack.pop();
//	}
//}
