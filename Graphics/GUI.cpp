#include "GUI.h"
#include "Texture.h"
#include "State.h"
#include "Engine.h"


const float GUI::p2pX(const float percent){


	int w;
	SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, NULL);

	float result = std::floor(static_cast<float>(w) * (percent / 100.f));

	return result;
}

const float GUI::p2pY(const float percent){

	int h;
	SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), NULL, &h);

	return std::floor(static_cast<float>(h) * (percent / 100.f));
}

const int GUI::p2pXi(const int percent){

	int w;
	SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, NULL);


	float result = std::floor(static_cast<float>(w) * (percent / 100.f));

	int r = static_cast<int>(result);

	return r;
}

const int GUI::p2pYi(const int percent){

	int h;
	SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), NULL, &h);

	float result = std::floor(static_cast<float>(h) * (percent / 100.f));

	int r = static_cast<int>(result);

	return r;
}

const unsigned int GUI::calcCharSize(int size){

	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	return static_cast<unsigned int>(dm.w + dm.h) / size;
}

GUI::Button::Button(){

	this->font = nullptr;
    stateChange = true;
	mSelected = false;
	//Button text colour
	colour = { 0, 77, 0, 255 };

	mTextureText = std::make_unique<Texture>();

	backgroundTexture = std::make_unique<Texture>();
	setBackgroundTexture("Assets/Background/button2.png");


	///TODO: - Has no effect...
	const char* fontFile = "Assets/Fonts/Roboto.ttf";
	this->font = TTF_OpenFont(fontFile , 30);

	if (!font) {

		printf("Failed to load font! File: %s\n", fontFile);

		return;
	}
}

GUI::Button::~Button(){
}

GUI::Button::Button(float x, float y, float w, float h, unsigned int charSize){

	//Button text colour
	colour = { 0, 117, 117, 255 };
    stateChange = true;
	backgroundTexture = std::make_unique<Texture>();
	setBackgroundTexture("Assets/Background/button2.png");

    mSelected = false;
	active = true;
	this->buttonShape.x = static_cast<int>(GUI::p2pX(x));
	this->buttonShape.y = static_cast<int>(GUI::p2pY(y));
	this->buttonShape.w = static_cast<int>(GUI::p2pX(w));
	this->buttonShape.h = static_cast<int>(GUI::p2pY(h));

	mTextureText = std::make_unique<Texture>();

    /** FONT FILE WHICH CHANGES BUTTONS....*/
	const char* fontFile = "Assets/Fonts/Roboto.ttf";
	this->font = TTF_OpenFont(fontFile, charSize);

	if (!font) {

		printf("Failed to load font! File: %s\n", fontFile);

		return;
	}

	mClicked = false;
	mInside = false;
}

void GUI::Button::setBackgroundTexture(std::string filename){

    backgroundTexture->loadFromFile(filename, Engine::GetInstance()->GetRenderer());
}

//void GUI::Button::setPosition(int x, int y){
//
//    buttonShape.x = x;
//    buttonShape.y = y;
//}

void GUI::Button::renderButtons(){

	this->mTextureText->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), mRenderText, colour, *this->font);

	if(backgroundTexture != nullptr && active){

        SDL_Rect gold = { buttonShape.x, buttonShape.y, buttonShape.w, buttonShape.h };
        const SDL_Rect g = backgroundTexture->getTextureRect();
        ///backgroundTexture->render(Engine::GetInstance()->GetRenderer(), buttonShape.x, buttonShape.y);
        SDL_Rect clip = {0, 0, 555, 520};
        if(!stateChange){

            clip.x = 557;
            clip.w = 560;
        }

        if(!SDL_ShowCursor(SDL_QUERY)){

            clip = {0, 0, 555, 520};
        }
        backgroundTexture->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &clip, &buttonShape);
       //SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), backgroundTexture->getTexture(), &clip, &buttonShape);
//        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 215, 0, 255);
//        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &gold);

	}
	else{


	if (!this->active) {

        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 164, 251, 251, 0);
	}
	else if (mInside && mClicked) {

		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 10);
		mClicked = false;
		mInside = false;
	}
	else if(mSelected){

        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 164, 164, 164, 100);
	}
	else {

		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 164, 251, 251, 255);
	}

	SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &buttonShape);
	}
	if (active) {

        int w = mTextureText->getWidth() / 2;
        int h = mTextureText->getHeight() / 2;
        mTextureText->setColour(0, 0, 0);
		this->mTextureText->render(Engine::GetInstance()->GetRenderer(), buttonShape.x + ((buttonShape.w / 2) - w), buttonShape.y + (buttonShape.h / 2) - h);
	}
}

void GUI::Button::isSelected(){

    int x,y;
    SDL_GetMouseState(&x, &y);

    if(backgroundTexture != nullptr && active && SDL_ShowCursor(SDL_QUERY)){

        if(x > buttonShape.x && x < buttonShape.x + buttonShape.w && y > buttonShape.y && y < buttonShape.y + buttonShape.h){

            stateChange = false;
            //setBackgroundTexture("Assets/Background/buttonSelected.png");
        }
        else{

            stateChange = true;
            //setBackgroundTexture("Assets/Background/button.png");
        }
    }
}

void GUI::Button::update(){

    isSelected();
}


void GUI::Button::setRenderText(std::string t){

    //TODO: Comment this out and see if it's ever used
	mRenderText = t;
}

bool GUI::Button::isPressed(SDL_MouseButtonEvent &e) {

	if (!active || !SDL_ShowCursor(SDL_QUERY)) {

		return false;
	}

	mClicked = false;
	mInside = true;

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x < buttonShape.x) {

		mInside = false;
	}
	else if (x > buttonShape.x + buttonShape.w) {

		mInside = false;
	}
	else if (y < buttonShape.y) {

		mInside = false;
	}
	else if (y > buttonShape.y + buttonShape.h) {

		mInside = false;
	}

	mClicked = false;


		if (e.type == SDL_MOUSEBUTTONDOWN && e.button == SDL_BUTTON_LEFT && mInside == true) {

			mClicked = true;
		}

	return mInside && mClicked;
}

SDL_Rect GUI::Button::getRect() {

    //TODO: Comment this out and see if it's ever used
	return buttonShape;
}

GUI::Text::Text(bool border){

	mBorder = border;
//	mRend = rend;
//	mWind = wind;
///	mMainText = "Debug text 1";

    ///TODO: - Does nothing again....
	mFontFile = "Assets/Fonts/Roboto.ttf";
	mFontSize = 20;

	percentW = 0;
	percentH = 0;
	percentX = 0;
	percentY = 0;


	mOutline.x = GUI::p2pXi(5);
	mOutline.y = GUI::p2pYi(5);
	//mOutline.x = 0;
	//mOutline.y = 0;
	mOutline.w = 0;
	mOutline.h = 0;

	mFiller.x = 0;
	mFiller.y = 0;
	mFiller.w = 0;
	mFiller.h = 0;

	offsetX = 0;
	offsetY = 0;


	initFont();
	initTextures();
	initGUI();

	mTextColour = { 0, 255, 0, 255 };
	//mTextColour = { 0, 255, 0, 255 };
}

GUI::Text::Text(std::string n){

    setString(n);
}

GUI::Text::Text(int x, int y, int w, int h, bool border){

//	mRend = rend;
//	mWind = wind;

	mFontSize = 20;
	/** Main, Dynamic and Enemy Text font file....*/
	mFontFile = "Assets/Fonts/Roboto.ttf";
	mBorder = border;

	percentW = w;
	percentH = h;
	percentX = x;
	percentY = y;


    //FULL SCREEN FOR BACKGROUND COLOUR.
	SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w;
    auto Height = DM.h;
    mFactionBg = {0, 0, Width, Height};

	if (mBorder) {

		mOutline.x = GUI::p2pXi(x);
		mOutline.y = GUI::p2pYi(y);
		mOutline.w = GUI::p2pXi(w);
		mOutline.h = GUI::p2pYi(h);


		mFiller.x = mOutline.x - 2;
		mFiller.y = mOutline.y - 2;
		mFiller.w = mOutline.w + 4;
		mFiller.h = mOutline.h + 4;

		offsetX = 30;
		offsetY = 20;

		mBackgroundColour = { 0, 0, 0, 255 };
	}
	else {

		mOutline.x = GUI::p2pXi(x);
		mOutline.y = GUI::p2pYi(y);
		mOutline.w = 0;
		mOutline.h = 0;

		mFiller.x = 0;
		mFiller.y = 0;
		mFiller.w = 0;
		mFiller.h = 0;

		offsetX = 0;
		offsetY = 0;
	}

///	mMainText = "Debug text 2";

	initFont();
	initTextures();
	mTextColour = { 0, 255, 0, 255 };
}

void GUI::Text::setPositionF(int x, int y, int w, int h){

        /*TODO:  Width and Height are used for border of text */
        mOutline.x = GUI::p2pXi(x);
		mOutline.y = GUI::p2pYi(y);
		mOutline.w = GUI::p2pXi(w);
		mOutline.h = GUI::p2pYi(h);

		mFiller.x = GUI::p2pXi(x);
		mFiller.y = GUI::p2pYi(y);
		mFiller.w = GUI::p2pXi(w);
		mFiller.h = GUI::p2pYi(h);
}

GUI::Text::~Text(){

	mTextTexture->free();

//	delete mTextTexture;
}

void GUI::Text::update()
{

}


void GUI::Text::setBgColour(int r, int g, int b, int a){

    mBackgroundColour.r = r;
    mBackgroundColour.g = g;
    mBackgroundColour.b = b;
    mBackgroundColour.a = a;
}

int GUI::Text::getTextWidth() {

	return mTextTexture->getWidth();
}

int GUI::Text::getTextHeight() {

	return mTextTexture->getHeight();
}


void GUI::Text::render(){


    SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);

	if (mBorder) {

        SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), mBackgroundColour.r, mBackgroundColour.g, mBackgroundColour.b, mBackgroundColour.a);
        SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &mFactionBg);
		SDL_Rect bg = mOutline;
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &bg);

		if (mFiller.w != 0 && mFiller.h != 0) {

			SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), mTextColour.r, mTextColour.g, mTextColour.b, mTextColour.a);
			SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &mFiller);
		}

		if (mOutline.w != 0 && mOutline.h != 0) {

			SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), mTextColour.r, mTextColour.g, mTextColour.b, mTextColour.a);
			SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &mOutline);
		}
	}

	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), mTextColour.r, mTextColour.g, mTextColour.b, mTextColour.a);
	mTextTexture->render(Engine::GetInstance()->GetRenderer(), mOutline.x + offsetX, mOutline.y + offsetY);
	SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);
}

SDL_Rect GUI::Text::getPositionRect(){

    return mTextTexture->getTextureRect();
}

void GUI::Text::setPosition(int x, int y) {

	this->mOutline.x = x;
	mOutline.y = y;
}

void GUI::Text::setString(std::string text, bool wrapped, int width){

	mMainText = text;
	mTextTexture->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), mMainText, mTextColour, *mFont, wrapped, width);
}

SDL_Texture* GUI::Text::getTexture() {

	return mTextTexture->getTexture();
}

bool GUI::Text::isEmpty(){

    bool test = false;
    if(this->getString() == ""){
        test = true;
    }

    return test;
}

void GUI::Text::clearText(){

    this->setString("");
    //mBorder = false;
}

bool GUI::Text::intersects(int x, int y){

    if(mTextTexture->intersects(x, y)){

        return true;
    }
    else{

        return false;
    }
}

std::string GUI::Text::getString() {

	return mMainText;

}

void GUI::Text::setAlpha(Uint8 a){

    mTextColour.a = a;
}

void GUI::Text::setColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a){

	mTextColour = { r, g, b, a };
}

void GUI::Text::setFontSize(int s) {

	mFontSize = s;
	initFont();
}

void GUI::Text::updateWindow() {

    //TODO: OBSOLETE - REMOVE
//	mWind = wind;
}

void GUI::Text::refreshGUI(){

	initFont();
	initGUI();
	//mTextTexture->loadFromRenderedText(mRend, mMainText, mTextColour, *mFont);
}

void GUI::Text::initFont(){

	//this->font = TTF_OpenFont(fontFile, charSize);

	mFont = TTF_OpenFont(mFontFile.c_str(), mFontSize);

	if (!mFont) {

		//printf("Failed to load font! File: %s\n", mFontFile);
		std::cout << "Failed to load font! File: " + mFontFile << endl;

		return;
	}
}


void GUI::Text::setFontfile(std::string fontFile) {

	mFontFile = fontFile;
}

void GUI::Text::setBorder(int x, int y, int w, int h){

    mOutline.x = GUI::p2pXi(x);
    mOutline.y = GUI::p2pYi(y);
    mOutline.w = GUI::p2pXi(w);
    mOutline.h = GUI::p2pYi(h);


    mFiller.x = mOutline.x - 2;
    mFiller.y = mOutline.y - 2;
    mFiller.w = mOutline.w + 4;
    mFiller.h = mOutline.h + 4;

    offsetX = 10;
    offsetY = 10;
}

void GUI::Text::setTextParameters(std::string txt, SDL_Color colour, TTF_Font * font, int size){

	mFont = font;
	//mFontSize = size;
	mTextColour = colour;
	mTextTexture->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), mMainText, colour, *font);
}


void GUI::Text::initTextures(){

	mTextTexture = std::make_unique<Texture>();

	mTextColour = { 0, 255, 0, 255 };
	mTextTexture->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), mMainText, mTextColour, *mFont);
}

void GUI::Text::initGUI(){


	if (!mBorder) {

		int l_w, l_h;
		SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &l_w, &l_h);
		mOutline.x = GUI::p2pXi(percentX) - (mTextTexture->getWidth() / 2);
		mOutline.y = GUI::p2pYi(percentY);
		mOutline.w = 0;
		mOutline.h = 0;
	}
	else {

		mOutline.x = GUI::p2pXi(percentX);
		mOutline.y = GUI::p2pYi(percentY);
		mOutline.w = GUI::p2pXi(percentW);
		mOutline.h = GUI::p2pYi(percentH);
	}

	mFiller.x = mOutline.x - 2;
	mFiller.y = mOutline.y - 2;
	mFiller.w = mOutline.w + 4;
	mFiller.h = mOutline.h + 4;
}

GUI::TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, std::shared_ptr<Texture> textureSheet, TTF_Font * font, std::string text, float scale){

	keyTime = 0.f;
	keyTimeMax = 1.f;

	bounds.w = static_cast<int>(width);
	bounds.h = static_cast<int>(height);
	bounds.x = static_cast<int>(x);
	bounds.y = static_cast<int>(y);

	this->gridSize = gridSize;
	this->scale = scale;
	this->hidden = true;
	textureSheet->setPosition(static_cast<int>(x), static_cast<int>(y));

	if (textureSheet->getTextureRect().w > bounds.w || textureSheet->getTextureRect().h > bounds.h) {

		textureSheet->setTextureRect(0, 0, bounds.w, bounds.h);
	}

	selector.x = static_cast<int>(x);
	selector.y = static_cast<int>(y);
	selector.h = static_cast<int>(gridSize);
	selector.w = static_cast<int>(gridSize);

	textureRect.h = static_cast<int>(gridSize);
	textureRect.w = static_cast<int>(gridSize);

	this->active = false;

	int charSize = 30;
	this->hideButton = new GUI::Button(0, 0, 30, 30, charSize);

	this->sheet = textureSheet;
}

GUI::TextureSelector::~TextureSelector(){

	//hideButton->~Button();
	//delete this->hideButton;
}

bool GUI::TextureSelector::getActive(){

	return this->active;
}

bool GUI::TextureSelector::isHidden(){

	return this->hidden;
}

const bool GUI::TextureSelector::getKeyTime(){

	if (keyTime >= keyTimeMax) {

		keyTime = 0.f;
		return true;
	}
	return false;
}

const SDL_Rect & GUI::TextureSelector::getTextureRect() const{

	return this->textureRect;
}

void GUI::TextureSelector::updateKeyTime(const float & dt){

	if (keyTime < keyTimeMax) {

		keyTime += 0.3f * dt;
	}
}

void GUI::TextureSelector::update(SDL_MouseButtonEvent &e){

	hideButton->update();

	if (hideButton->isPressed(e)) {

		hidden = !hidden;
	}

	bool mInside = true;
	int x, y;
	SDL_GetMouseState(&x, &y);

	if (x < bounds.x) {

		mInside = false;
	}
	else if (x > bounds.x + bounds.w) {

		mInside = false;
	}
	else if (y < bounds.y) {

		mInside = false;
	}
	else if (y > bounds.y + bounds.h) {

		mInside = false;
	}

	if (mInside) {

		this->active = true;
	int mousePosGridX = (x - bounds.x) / (static_cast<int>(gridSize) * static_cast<int>(scale));
	int mousePosGridY = (y - bounds.y) / (static_cast<int>(gridSize) * static_cast<int>(scale));

	selector.x = bounds.x + mousePosGridX * (static_cast<int>(gridSize) * static_cast<int>(scale));
	selector.y = bounds.y + mousePosGridY * (static_cast<int>(gridSize) * static_cast<int>(scale));

	if (e.type == SDL_MOUSEBUTTONDOWN) {

		textureRect.x = (selector.x - bounds.x) / static_cast<int>(scale);
		textureRect.y = (selector.y - bounds.y) / static_cast<int>(scale);

	}
	}
	else {

		active = false;
	}
}

void GUI::TextureSelector::render(){


	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &this->bounds);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &this->selector);

	this->sheet->render(Engine::GetInstance()->GetRenderer(), this->bounds.x, bounds.y);
	//TODO
}

GUI::Tooltip::Tooltip(){

	displayText = std::make_unique<Text>(false);
	displayText->setColour(0, 0, 0, 255);

	outline.x = 0;
	outline.y = 0;
	outline.w = 0;
	outline.h = 50;//displayText->getString();

	hidden = true;
}

GUI::Tooltip::~Tooltip(){

//	displayText.release();
}

void GUI::Tooltip::setDisplayText(std::string txt) {

	displayText->setString(txt, true, 150);
	outline.w = displayText->getTextWidth() + 10;
	outline.h = displayText->getTextHeight() + 10;

	displayText->setPosition(outline.x + 5, outline.y + 5);
}

bool GUI::Tooltip::checkBounds(std::shared_ptr<GUI::Text> text){

    SDL_Rect r = text->getPositionRect();
    bool success = false;

    int x, y;
    SDL_GetMouseState(&x, &y);

    if(x > r.x && x < r.x + r.w && y > r.y && y < r.y + r.h){

        success = true;
    }

    return success;
}

void GUI::Tooltip::setHidden(bool h) {

	hidden = h;
}

bool GUI::Tooltip::getHidden() {

	return hidden;
}


void GUI::Tooltip::update(){

    int x, y;
    SDL_GetMouseState(&x, &y);

	outline.x = x;
	outline.y = y;

	int w, h;
	SDL_GetWindowSize(Engine::GetInstance()->GetWindow(), &w, &h);

	if(outline.x + outline.w > w){

        outline.x -= outline.w;
	}
	if(outline.y + outline.h > h){

        outline.y -= outline.h;
	}

	if(outline.x <= 0){

        outline.x = 1;
	}
	if(outline.y <= 0){

        outline.y = 1;
	}
}

void GUI::Tooltip::render(){

	if (!hidden) {

		fillRect = outline;
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 170, 255, 0, 255);
		SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &fillRect);
		SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 225, 254, 167, 255);
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &outline);

		displayText->render();
	}
}

GUI::Menu::Menu(){

//	this->hiddenCount = 0;
	this->selection = -1;
	this->exit = false;
	this->charSize = GUI::calcCharSize(100);

	menuTimer = std::make_shared<GameTimer>();
    menuTimer->start();
    options.clear();
	///TODO:- SEEMS TO DO NOTHING...
	this->font = TTF_OpenFont("Fonts/Roboto.ttf", charSize);
	this->active = true;
	this->scrollable = false;

	scrollArrowDown = std::make_unique<Texture>();
	scrollArrowDown->loadFromFile("Assets/GUI/arrowDown.png", Engine::GetInstance()->GetRenderer());

	scrollArrowUp = std::make_unique<Texture>();
	scrollArrowUp->loadFromFile("Assets/GUI/arrowUp.png", Engine::GetInstance()->GetRenderer());

//	this->mStateData = &stateData;

	//TODO:: Add sprite for scrolling up/down when more than four options.

	activeOption = 0;

    textSelectorActive = false;
	detachCursor = true;
}


//OBSOLETE -  REMOVE
GUI::Menu::Menu(int type, bool test){

    options.clear();
}

GUI::Menu::~Menu(){

	if(this->options.size() > 0){

		for(unsigned int i = 0; i < options.size(); i++){

			options[i]->free();
		}
	}
}

int GUI::Menu::getChoice(){

	return this->selection;
}


//MAY BE OBSOLETE..
int GUI::Menu::getType(){

	return this->type;
}

//SAme again, obsolete....
int GUI::Menu::getDynamicType(){

	return this->dynamicType;
}

bool GUI::Menu::cursorDetached(){

    if(SDL_ShowCursor(SDL_QUERY)){

    int x, y;
    SDL_GetMouseState(&x, &y);


    if(x > outline.x && x < (outline.x + outline.w) && y > outline.y && y < (outline.y + outline.h)){

            detachCursor = false;
    }
    else{

        detachCursor = true;
    }
    }
    else{

        detachCursor = true;
    }

    return detachCursor;
}


void GUI::Menu::setBattleMenu(){

    options.clear();
    ops.clear();

    ops.push_back("Back");
    ops.push_back("Attack");
    ops.push_back("Defend");
    ops.push_back("Use Item");

    setMenuOptions(ops, false);

    this->setPosition();
}

void GUI::Menu::setPosition(){

	float offsetY = GUI::p2pY(7.f);

	float diff = GUI::p2pY(2.f);

	for(size_t i = 0; i < options.size(); i++){

		float y = (offsetY * i) + this->outline.y;
		options[i]->setPosition(outline.x + static_cast<int>(diff), static_cast<int>(y) + static_cast<int>(diff));
	}

    textSelector.x = outline.x + 1;
    textSelector.y = outline.y;
	textSelector.w =  GUI::p2pX(89.7f);
	textSelector.h = GUI::p2pYi(7);
}

void GUI::Menu::setMenuOptions(std::vector<std::string> strings, bool dynamic, bool item, bool wep, bool arm){


    hiddenCount = 0;
	this->options.clear();

	//options = strings;

	unsigned charSize = GUI::calcCharSize(80);
	SDL_Color colour = { 0, 255, 0 };

    /*** HANDLES MENU FONT, this needs looking at as it currently breaks...  */
	font = TTF_OpenFont("Assets/Fonts/Roboto.ttf", 18);
	if(dynamic){

///		this->options.push_back(new Texture());
///		this->options[0]->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), "Back", colour, *font);

		for(size_t i = 0; i < strings.size(); i++){

			options.push_back(new Texture());
			if(item){
                if(wep){

                    colour = StateData::GetInstance()->getActiveCharacter()->getWepItemColour(i);
                }
                else if(arm){

                    colour = StateData::GetInstance()->getActiveCharacter()->getArmItemColour(i);
                }
                else{
                    if(strings[0] != "You have no items"){

                        colour = StateData::GetInstance()->getActiveCharacter()->getItemColour(i);
                    }
                }
                ///std::cout << "\nR:" + std::to_string(colour.r) + " G:" + std::to_string(colour.g) + " B:" + std::to_string(colour.b);
			}
			this->options[i]->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), strings[i], colour, *font);
		}
	}
	else{

		for(size_t i = 0; i < strings.size(); i++){

            std::cout << strings[i];
			this->options.push_back(new Texture());
			if(item){
                colour = StateData::GetInstance()->getActiveCharacter()->getItemColour(i);
			}
			this->options[i]->loadFromRenderedText(Engine::GetInstance()->GetRenderer(), strings[i], colour, *font);

			if(i > 3){

                hiddenCount++;
			}
		}
	}

	this->setPosition();
	this->refreshGUI();
}

bool GUI::Menu::isSelected(){

	SDL_Rect result;

	/* TODO check myGame menu.cpp, skipped some code that may be obsolete, but maybe not?? */

	if(this->active){

	if(!this->options.empty()){

		for(size_t i = 0; i < options.size(); i++){

			SDL_Rect textRect;
			SDL_Rect r = options[i]->getTextureRect();

			if(SDL_IntersectRect(std::move(&textSelector), std::move(&r), std::move(&textRect)) && textSelectorActive){

				this->selection = i;
				SDL_Color colour = { 255, 255, 255, 150 };
				//SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &textSelector);

				return true;
			}
		}
	}
	}
	return false;
}

void GUI::Menu::setActive(bool active){

	this->active = active;
	this->textSelectorActive = active;
}

void GUI::Menu::toggleActive(){

	this->active = !this->active;
	this->textSelectorActive = !this->textSelectorActive;
}

bool GUI::Menu::getActive(){

	return this->active;
}

void GUI::Menu::updateTextSelector(){

	float x = GUI::p2pX(89.7f);
	float newY = GUI::p2pY(8.f);

	float y = 0;
	y = this->options.size() * newY;

	if(y >= (4 * newY)){

		y = 4 * newY;
	}

	textSelector.w = static_cast<int>(x);

	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 255, 255, 255);

	int mouseX, mouseY;


    SDL_GetMouseState(&mouseX, &mouseY);


	SDL_Rect result;
	bool inside = true;

	for(unsigned int i = 0; i < options.size(); i++){

		SDL_Rect temp = options[i]->getTextureRect();
		if(SDL_IntersectRect(&textSelector, &temp, &result)){

			inside = true;
			activeOption = i;
		}
	}

	if(mouseX < outline.x){

		inside = false;
	}
	if(mouseX > outline.x + outline.w){

		inside = false;
	}
	if(mouseY < outline.y){

		inside = false;
	}
	if(mouseY > outline.y + outline.h){

		inside = false;
	}

	if(inside && this->active && !detachCursor){

		int gridPosX, gridPosY;

		gridPosX = mouseX - outline.x;
		gridPosY = (mouseY - outline.y) / static_cast<int>(newY);

		textSelector.x = outline.x + 1;
		textSelector.y = outline.y + gridPosY * (textSelector.h);

        ///SDL_ShowCursor(SDL_DISABLE); ///THIS IS WHERE YOU LOSE CURSOR
		textSelectorActive = true;
	}
	else{

        ///textSelector.x = outline.x + 1;
        ///textSelector.y = outline.y;
	}
}

void GUI::Menu::updateInput(){

	//DEFINITELY OBSOLETE
}

void GUI::Menu::update(){

    if(cursorDetached()){

        if(SDL_ShowCursor(SDL_QUERY)){

            textSelectorActive = false;

            return;
        }
        else{

            textSelectorActive = true;
        }
    }


    if(active){

    int x, y;
	SDL_GetMouseState(&x, &y);
	bool inside = false;

        ///TODO ADD TIMER TO THIS SO IT DOESN'T GO TOO FAST...
        SDL_Rect t = scrollArrowDown->getTextureRect();
        SDL_Rect d = scrollArrowUp->getTextureRect();
        if(scrollArrowDown->intersects(x, y)){

            //INSIDE
            inside = true;
            if(menuTimer->getTicks() > 450){

                scrollText(0);
                menuTimer->restart();
            }
        }

        if(x > d.x && x < d.x + d.w && y > d.y && y < d.y + d.h){

            //INSIDE
            inside = true;
            if(menuTimer->getTicks() > 450){

                scrollText(1);
                menuTimer->restart();
            }
        }
    }
}

void GUI::Menu::updateEvents(SDL_Event& e){

	///updateTextSelector();
	if(this->options.empty()){

		this->active = false;
	}

	if(this->active /*&& !detachCursor*/){

		this->updateTextSelector();
		this->updateInput(); //CAN BE REMOVED..
	}

	///TODO: - Fix and bring back
	if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP)){

        SDL_ShowCursor(SDL_DISABLE);
        detachCursor = true;
        SDL_Delay(50);
        if(active){

            if(textSelectorActive){

                if(!isSelected()){

                    if(options.size() > 4){

                        detachCursor = true;
                        textSelector.x = outline.x + 1;
                        textSelector.y = outline.y;
                    }
                }

                detachCursor = true;
                textSelector.y -= textSelector.h;
                if(textSelector.y < outline.y){

                    textSelector.y = outline.y;
                    if(options.size() > 0){

                        scrollText(1);
                    }
                }
            }
            else{

                textSelectorActive = true;

                return;
            }
        }
	}

	if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_DOWN)){

        SDL_Delay(50);
        SDL_ShowCursor(SDL_DISABLE);
        detachCursor = true;
        if(active){

            if(textSelectorActive){


                if(!isSelected()){

                    if(options.size() > 4){

                        detachCursor = true;
                        textSelector.x = outline.x + 1;
                        textSelector.y = outline.y;
                    }
                }

                detachCursor = true;
                textSelector.y += textSelector.h;
                if((textSelector.y + textSelector.h) > (outline.y + outline.h)){

                    textSelector.y = (outline.y + outline.h) - textSelector.h;

                    //if(hiddenCount > 0){
                    if(options.size() > 0){

                        scrollText(0);
                    }
                    //}
                }
            }
            else{

                textSelectorActive = true;
            }
        }
	}

	if(e.type == SDL_MOUSEWHEEL){
        //detachCursor = true;
        if(SDL_ShowCursor(SDL_QUERY)){

            SDL_ShowCursor(SDL_DISABLE);
            if(!textSelectorActive){
                textSelectorActive = true;
                textSelector.y = outline.y;
                return;
            }
        }
        if(e.wheel.y > 0){
           //detachCursor = true;
            SDL_Delay(100);
            if(active){

            if(!isSelected()){

                if(options.size() > 4){

                    //detachCursor = true;
                    textSelector.x = outline.x + 1;
                    textSelector.y = outline.y;
                }
            }
            textSelector.y -= textSelector.h;
            if(textSelector.y < outline.y){

                textSelector.y = outline.y;
                if(options.size() > 0){

                    scrollText(1);
                }
            }

            SDL_ShowCursor(SDL_DISABLE);
            if(!cursorDetached()){
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            SDL_WarpMouseInWindow(Engine::GetInstance()->GetWindow(), x, (y-textSelector.h));
            }
        }
        }

        if(e.wheel.y < 0){

           /// scrollText(0);
           // detachCursor = true;
           SDL_Delay(50);
            if(active){

            if(!isSelected()){

                if(options.size() > 4){

                    //detachCursor = true;
                    textSelector.x = outline.x + 1;
                    textSelector.y = outline.y;
                }
            }

           // detachCursor = true;
            textSelector.y += textSelector.h;
            if((textSelector.y + textSelector.h) > (outline.y + outline.h)){

                textSelector.y = (outline.y + outline.h) - textSelector.h;

                //if(hiddenCount > 0){
                if(options.size() > 0){

                    scrollText(0);
                }
                //}
                SDL_ShowCursor(SDL_DISABLE);
            if(!cursorDetached()){
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            SDL_WarpMouseInWindow(Engine::GetInstance()->GetWindow(), x, (y+textSelector.h));
            }
            }
        }
        }

        e.wheel.y = 0;

        return;
	}

//	if(e.type == SDL_MOUSEBUTTONDOWN && cursorDetached()){
//
//        this->clicked = true;
//        //this->activeOption =
//	}

    if(!SDL_ShowCursor(SDL_QUERY)){

            static int lastX = -1, lastY = -1;
            int currentX, currentY;

        if(e.type == SDL_MOUSEMOTION){

                /*CHATGPT GOES HERE*/


                currentX = e.motion.x;
        currentY = e.motion.y;

        if (lastX == -1 && lastY == -1) {
            lastX = currentX;
            lastY = currentY;
            return;
        }

        int dx = currentX - lastX;
        int dy = currentY - lastY;
        double distance = sqrt(dx * dx + dy * dy);

        lastX = currentX;
        lastY = currentY;

        if (distance > 50) {
            SDL_ShowCursor(SDL_ENABLE);
        }





                /* ENDS HERE */

//                if(cursorDetached()){
//
//                    textSelectorActive = false;
//                }
//                SDL_ShowCursor(SDL_ENABLE);
        }
    }

}

/* TODO SCROLL TEXT FUNCTION!!! */


void GUI::Menu::render(){


	SDL_Rect fill = outline;

	SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 0, 0, 255);

	SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &fill);

	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, 255);
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &outline);
	SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);

	if(this->textSelectorActive && this->getActive()){

		SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
		if(clicked){

            SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 255);
			clicked = false;
		}
		else{

		       	SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 255, 0, 0, 100);
		}

		SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &textSelector);
		SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);
	}

	float posY = GUI::p2pY(70.f);
	float maxY = GUI::p2pY(95.f);


	for(size_t i = 0; i < this->options.size(); i++){

            int yy = options[i]->getTextureRect().y;

		if(this->options[i]->getTextureRect().y < posY){

			//break
			//return;
		}
		else if(this->options[i]->getTextureRect().y > maxY){

			//break
			//return;
		}
		else{


            options[i]->render(Engine::GetInstance()->GetRenderer(), options[i]->getTextureRect().x, options[i]->getTextureRect().y);
		}
	}

	if(options.size() >= 4){

        if(hiddenCount < (options.size() - 4)){

        scrollArrowDown->setPosition(GUI::p2pXi(46), GUI::p2pYi(94));
        scrollArrowDown->render(Engine::GetInstance()->GetRenderer(), scrollArrowDown->getTextureRect().x, scrollArrowDown->getTextureRect().y);
        }

        if(hiddenCount > 0){

            scrollArrowUp->setPosition(GUI::p2pXi(46),  GUI::p2pY(70));
            scrollArrowUp->render(Engine::GetInstance()->GetRenderer(), scrollArrowUp->getTextureRect().x, scrollArrowUp->getTextureRect().y);
        }
	}
	/*TODO Fix this.... see menu.cpp from myGAme for cheatz..
	 *
	 * if(hiddenCount > 0){
	 *
	 * int w = (this->outline.x + outline.w) / 2 + 20;
	 *
	 * spriteUp->render(Engine::GetInstance()->GetRenderer(), w, this->outline.y + 10;
	 * }
	 */
}

void GUI::Menu::setClicked(){

	clicked = true;
}

void GUI::Menu::scrollText(int direction){

   if(active == false){

        return;
    }

	float offsetY = GUI::p2pY(7.f);

	if(direction == 0){

		if(options.size() > 4){

			if((size_t)hiddenCount < this->options.size() - 4){

				for(size_t i = 0; i < this->options.size(); i++){

					int x = options[i]->getTextureRect().x;
					int y = options[i]->getTextureRect().y;

					y -= static_cast<int>(offsetY);

					//options.insert(options.begin() + 3, t);
					options[i]->setPosition(options[i]->getTextureRect().x, options[i]->getTextureRect().y - static_cast<int>(offsetY));
				}

				hiddenCount++;
			}
		}
	}
	else{

		int w = this->options.size() - 4;

		if(hiddenCount > 0){

			for(size_t i = 0; i < this->options.size(); i++){

				options[i]->setPosition(options[i]->getTextureRect().x, options[i]->getTextureRect().y + static_cast<int>(offsetY));
			}

			hiddenCount--;
		}
	}
}

void GUI::Menu::refreshGUI(){

	float x, y = 0;

	float outlineY;

	y = GUI::p2pY(7.f);
	outlineY = 4 * y;

	x = GUI::p2pX(89.9f);

	outline.w = static_cast<int>(x);
	outline.h = static_cast<int>(outlineY);

	float posX, posY = 0;

	posX = GUI::p2pX(5.f);
	posY = GUI::p2pY(70.f);

	outline.x = static_cast<int>(posX + 1);
	outline.y = static_cast<int>(posY);

	/*TODO Use the newly created p2pYi and p2pXi instead of static casting all the time....*/

	float xOffset = GUI::p2pX(20.f);
	float yOffset = GUI::p2pY(12.f);

    textSelector.x = outline.x + 1;
    textSelector.y = outline.y;
	textSelector.w =  GUI::p2pX(89.7f);
	textSelector.h = GUI::p2pYi(7);

	if(hiddenCount > 0){

		//scrollText(1); //TODO create this
	}

	setPosition();
}

GUI::textBox::textBox(){

    outline = { GUI::p2pXi(20), GUI::p2pYi(20), 50, 50 };
    header = GUI::Text();
    text = GUI::Text();

    alpha = 255;

    confirm = false;
    choice = false;

    filler.x = outline.x - 2;
    filler.y = outline.y - 2;
    filler.w = outline.w + 4;
    filler.h = outline.h + 4;

    bg.x = outline.x + 1;
    bg.y = outline.y + 1;
    bg.w = outline.w - 2;
    bg.h = outline.h - 2;

    yesButton = std::make_shared<GUI::Button>(outline.x + 5, outline.h, 5, 5, 10);
    yesButton->setRenderText("YES");
    yesButton->setBackgroundTexture("Assets/Background/button2.png");
    noButton = std::make_shared<GUI::Button>(outline.x + 205, outline.h, 5, 5, 10);
    noButton->setRenderText("NO");
    noButton->setBackgroundTexture("Assets/Background/button2.png");

    active = false;
}

GUI::textBox::~textBox(){

    outline = { 0, 0, 0, 0};
}

void GUI::textBox::setAlpha(int al){

    if(al >=0 && al <= 255){

        alpha = al;
    }
    else{

        alpha = 255;
    }
}

void GUI::textBox::setHeader(std::string txt){

    header.setString(txt);
    header.setPosition(bg.x + ((bg.w / 2) - header.getTextWidth() / 2), bg.y + 10);
}

void GUI::textBox::setText(std::string txt){

    text.setString(txt, true, outline.w - GUI::p2pXi(1));
    text.setPosition(bg.x + GUI::p2pXi(5), header.getGlobalBounds().y + GUI::p2pYi(10));
}

void GUI::textBox::setSize(int w, int h){

    outline.h = GUI::p2pXi(h);
    outline.w = GUI::p2pYi(w);

    filler.x = outline.x - 5;
    filler.y = outline.y - 5;
    filler.w = outline.w + 10;
    filler.h = outline.h + 10;

    bg.x = outline.x + 1;
    bg.y = outline.y + 1;
    bg.w = outline.w - 1;
    bg.h = outline.h - 1;

    header.setPosition(bg.x + ((bg.w / 2) - header.getTextWidth() / 2), bg.y + 5);
    text.setPosition(bg.x + GUI::p2pXi(1), header.getGlobalBounds().y + GUI::p2pYi(5));

//    yesButton->setPosition(outline.x + GUI::p2pX(5), GUI::p2pY(outline.h - 2));
//    noButton->setPosition((outline.x + outline.w) - GUI::p2pX(10), outline.h - 2);
}

void GUI::textBox::refreshGUI(){

    outline.x = GUI::p2pXi(25);
    outline.y = GUI::p2pYi(25);
    outline.w = GUI::p2pX(50);
    outline.h = GUI::p2pY(50);

//    outline.x -= GUI::p2pX(50);
//    outline.y -= GUI::p2pY(outline.h / 2);

    filler.x = outline.x - 5;
    filler.y = outline.y - 5;
    filler.w = outline.w + 10;
    filler.h = outline.h + 10;

    bg.x = outline.x + 1;
    bg.y = outline.y + 1;
    bg.w = outline.w - 2;
    bg.h = outline.h - 2;

    header.setPosition(bg.x + ((bg.w / 2) - header.getTextWidth() / 2), bg.y + 25);
    text.setPosition(bg.x + GUI::p2pXi(2), header.getGlobalBounds().y + GUI::p2pYi(5));

    yesButton = std::make_shared<GUI::Button>(outline.x + 2, outline.h, 7.8f, 5, 10);
    yesButton->setRenderText("YES");
    noButton = std::make_shared<GUI::Button>(outline.x + 190, outline.h + 5, 7.8f, 5, 10);
    noButton->setRenderText("NO");

    yesButton->setBackgroundTexture("Assets/Background/button2.png");
    noButton->setBackgroundTexture("Assets/Background/button2.png");
//    yesButton->setPosition(outline.x + GUI::p2pX(2), outline.h - 5);
//    noButton->setPosition((outline.x + outline.w) - GUI::p2pX(10), outline.h - 5);
}

void GUI::textBox::centreTextBox(){

    outline.x = GUI::p2pXi(50);
    outline.y = GUI::p2pYi(50);

    outline.x -= outline.w / 2;
    outline.y -= outline.h / 2;

    filler.x = outline.x - 5;
    filler.y = outline.y - 5;
    filler.w = outline.w + 10;
    filler.h = outline.h + 10;

    bg.x = outline.x + 1;
    bg.y = outline.y + 1;
    bg.w = outline.w - 2;
    bg.h = outline.h - 2;

    header.setPosition(bg.x + ((bg.w / 2) - header.getTextWidth() / 2), bg.y + 25);
    text.setPosition(bg.x + GUI::p2pXi(2), header.getGlobalBounds().y + GUI::p2pYi(5));

    ///NEEDED
    yesButton->setPosition(outline.x + GUI::p2pX(2), outline.h + 180);
    noButton->setPosition((outline.x + outline.w) - GUI::p2pX(10), outline.h + 180);
}

void GUI::textBox::update(){

    yesButton->update();
    noButton->update();
}

void GUI::textBox::setPosition(int x, int y){

    outline.x = x;
    outline.y = y;

    filler.x = outline.x - 5;
    filler.y = outline.y - 5;
    filler.w = outline.w + 10;
    filler.h = outline.h + 10;

    bg.x = outline.x + 1;
    bg.y = outline.y + 1;
    bg.w = outline.w - 2;
    bg.h = outline.h - 2;

    header.setPosition(bg.x + ((bg.w / 2) - header.getTextWidth() / 2), bg.y + 25);
    text.setPosition(bg.x + GUI::p2pXi(2), header.getGlobalBounds().y + GUI::p2pYi(5));

    yesButton->setPosition(outline.x +5, outline.h - 5);
    noButton->setPosition(outline.x + 205, outline.h - 5);
}

void GUI::textBox::updateEvents(SDL_MouseButtonEvent &e){

    if(confirm){

    if(yesButton->isPressed(e)){

          choice = true;
    }

    if(noButton->isPressed(e)){

        choice = false;
        ///confirm = false;
        active = false;
    }
    }
}

void GUI::textBox::render(){


    if(alpha < 255){

        SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
    }
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 192, 192, 192, alpha);
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &filler);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 13, 19, 20, alpha);
    SDL_RenderFillRect(Engine::GetInstance()->GetRenderer(), &bg);
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(), 0, 255, 0, alpha);
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &outline);

    SDL_SetRenderDrawBlendMode(Engine::GetInstance()->GetRenderer(), SDL_BLENDMODE_NONE);
    header.render();
    text.render();

    if(confirm){

        yesButton->renderButtons();
        noButton->renderButtons();
    }
}

GUI::InvSlot::InvSlot(){

    w = 0;
    h = 0;
    outline.x = 100;
    outline.y = 100;

    bgRect = {0, 0, 300, 77};
    bgSelectedRect = { 300, 0, 300, 77 };

//    selector.w = 600;
//    selector.h = 70;
    selectorActive = false;

    iconTexture = std::make_shared<Texture>();
    tileSheet = std::make_shared<Texture>();
    iconTexture->loadFromFile("Assets/itembg.png", Engine::GetInstance()->GetRenderer());
    itemText = std::make_shared<GUI::Text>();
}

GUI::InvSlot::~InvSlot(){

}

void GUI::InvSlot::update(){

    int x, y = 0;
    SDL_GetMouseState(&x, &y);

    if(outline.x < x && outline.x + outline.w > x && outline.y < y && outline.y + outline.h > y){

        selectorActive = true;
    }
    else{

        selectorActive = false;
    }
}

void GUI::InvSlot::render(){


    if(selectorActive){
        iconTexture->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &bgSelectedRect, &outline);
    }else{
        iconTexture->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &bgRect, &outline);
    }
    itemText->render();
    tileSheet->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, &this->clip, &iconRect);
    //iconTexture->renderToViewPort(Engine::GetInstance()->GetRenderer(), 0, 0, NULL, &outline);
}

void GUI::InvSlot::setDimensions(int w, int h){

    outline.w = w;
    outline.h = h;
}

void GUI::InvSlot::setPosition(int x, int y){

    outline.x = x;
    outline.y = y;

    iconRect.x = outline.x + 10;
    iconRect.y = outline.y + 7;
    iconRect.w = GUI::p2pX(3);
    iconRect.h = GUI::p2pX(3);
    itemText->setPosition(outline.x + GUI::p2pX(5), outline.y + 5);
}

void GUI::InvSlot::setTileSheet(std::string filename, SDL_Rect* c){

    if(c){

        clip.x = c->x;
        clip.y = c->y;
        clip.h = c->h;
        clip.w = c->w;
    }
    tileSheet->loadFromFile(filename, Engine::GetInstance()->GetRenderer());

}

