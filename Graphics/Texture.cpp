#include "Texture.h"

Texture::Texture() : mTexture(nullptr), mWidth(0), mHeight(0){

    //std::cout << "New Texture created!" << std::endl;
}

Texture::~Texture(){

//	this->free();
}

bool Texture::loadFromFile(const std::string & fileName, SDL_Renderer* rend){

	this->free();

	SDL_Texture* tex = nullptr;

	SDL_Surface* surf = IMG_Load(fileName.c_str());

	textFileName = fileName;

	if (!surf) {

		printf("Unable to load image %s! SDL_Error: %s\n", fileName.c_str(), IMG_GetError());

		return false;
	}
	else {

		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0, 0xFF, 0xFF));

		tex = SDL_CreateTextureFromSurface(rend, surf);

		if (!tex) {

			printf("Unable to create texture from %s! SDL_Error: %s\n", fileName.c_str(), SDL_GetError());

			return false;
		}
		else {

			mWidth = surf->w;
			mHeight = surf->h;
		}

		SDL_FreeSurface(surf);
	}

	mTexture = tex;

	///std::cout << textFileName << std::endl;

	return mTexture != nullptr;
}

bool Texture::loadFromRenderedText(SDL_Renderer* rend, const std::string & text, SDL_Color textColour, TTF_Font& font, bool wrapped, int width){

	this->free();

	if(text.length() <= 0){

        return false;
	}

	SDL_Surface* surf;
	if (!wrapped) {

		surf = TTF_RenderText_Solid(&font, text.c_str(), textColour);
	}
	else {

        surf = TTF_RenderText_Blended_Wrapped(&font, text.c_str(), textColour, width);
	}
	mRenderedText = text;
	if (!surf) {

		printf("Unable to render text surface! SDL_TTF Error: %s\n", TTF_GetError());
	}
	else {

		mTexture = SDL_CreateTextureFromSurface(rend, surf);

		if (!mTexture) {

			printf("Failed to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
		}
		else {

			mWidth = surf->w;
			mHeight = surf->h;
		}

		SDL_FreeSurface(surf);
	}

	return mTexture != nullptr;
}

void Texture::free(){

	if (mTexture != nullptr) {

		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;

		mWidth = 0;
		mHeight = 0;
	}
	else{

        mTexture = nullptr;
	}
}

void Texture::setColour(Uint8 r, Uint8 g, Uint8 b){

	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void Texture::setBlendMode(SDL_BlendMode mode){

	SDL_SetTextureBlendMode(mTexture, mode);
}

void Texture::setAlpha(Uint8 alpha){

	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::setPositionFloat(float x, float y) {

	mX = static_cast<int>(x);
	mY = static_cast<int>(y);
}

void Texture::setPosition(int x, int y){

	mX = x;
	mY = y;
}

void Texture::setTextureRect(int x, int y, int w, int h){

	mX = x;
	mY = y;
	mWidth = w;
	mHeight = h;
}

bool Texture::intersects(int & x, int & y)
{
	bool inside = true;
	SDL_Rect temp = getTextureRect();

	if (x < temp.x) {

		inside = false;
	}
	if (x > temp.x + temp.w) {

		inside = false;
	}
	if (y < temp.y) {

		inside = false;
	}
	if (y > temp.y + temp.h) {

		inside = false;
	}

	return inside;
}

void Texture::renderToViewPort(SDL_Renderer* rend, int x, int y, SDL_Rect* clip, SDL_Rect* viewport){

    ///SDL_RenderSetViewport(rend, viewport);

    mX = x;
    mY = y;
    SDL_Rect renderQuad = { mX, mY, mWidth, mHeight };

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

	//SDL_Rect result = cam;

	//if(SDL_IntersectRect(&cam, &renderQuad, &result)){

      //  SDL_RenderCopy(rend, mTexture, clip, &renderQuad);
	//}

	SDL_RenderCopy(rend, mTexture, clip, viewport);
}

void Texture::render(SDL_Renderer* rend, int x, int y, SDL_Rect * clip, SDL_Rect cam, double angle, SDL_Point * centre, SDL_RendererFlip){


	mX = x - cam.x;
	mY = y - cam.y;
	SDL_Rect renderQuad = { mX,  mY, mWidth, mHeight };

	if (clip) {

		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

	//SDL_Rect result = cam;

	//if(SDL_IntersectRect(&cam, &renderQuad, &result)){

      //  SDL_RenderCopy(rend, mTexture, clip, &renderQuad);
	//}

	SDL_RenderCopy(rend, mTexture, clip, &renderQuad);
}

SDL_Rect Texture::getTextureRect(){

	SDL_Rect r;
	r.x = mX;
	r.y = mY;
	r.h = mHeight;
	r.w = mWidth;

	return r;
}
