#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef _WIN32
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#endif // _WIN32

#include "Engine.h"
#include <string>
#include <iostream>

class Texture{


    //TODO: Texture Manager class???

public:

	Texture();
	virtual ~Texture();

	bool loadFromFile(const std::string& fileName, SDL_Renderer* rend);

	bool loadFromRenderedText(SDL_Renderer* rend, const std::string& text, SDL_Color textColour, TTF_Font& font, bool wrapped = false, int width = 0);

	void free();

	void setColour(Uint8 r, Uint8 g, Uint8 b);

	void setBlendMode(SDL_BlendMode mode);

	void setAlpha(Uint8 alpha);

	void setPositionFloat(float x, float y);

	void setPosition(int x = 0, int y = 0);

	void setTextureRect(int x, int y, int w, int h);

	bool intersects(int &x, int &y);

	//Renders texture at given point
	void render(SDL_Renderer* rend, int x, int y, SDL_Rect* clip = NULL, SDL_Rect cam = {0, 0, 600, 400}, double angle = 0.0, SDL_Point* centre = NULL, SDL_RendererFlip = SDL_FLIP_NONE);

	void renderToViewPort(SDL_Renderer* rend, int x, int y, SDL_Rect* clip, SDL_Rect* viewport);
	//Getters for image dimensions
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }
	SDL_Rect getTextureRect();

	SDL_Texture* getTexture() { return mTexture; }

private:

	SDL_Texture* mTexture;

	std::string textFileName;

	int mWidth;
	int mHeight;
	int mX;
	int mY;

	std::string mRenderedText;

};

#endif

