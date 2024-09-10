#ifndef GUI_H
#define GUI_H

#ifdef _WIN32
#include <SDL.h>
#include <SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif // WIN32


#include "Timer.h"

#include <string>
#include <memory>
#include <vector>


class Texture;
class StateData;

namespace GUI{


	//Translates pixel points to grid position, used for when resolution changes
	const float p2pX(const float percent);
	const float p2pY(const float percent);

	const int p2pXi(const int percent);
	const int p2pYi(const int percent);

	//Calculates Character size based on screen resolution
	const unsigned int calcCharSize(int size = 50);

	class Button {

	public:

		Button();
		virtual ~Button();
		Button(float x, float y, float w, float h, unsigned int charSize);
		void renderButtons();
        void setAlpha(int a){ alpha = a; }
		void update();

		void setRenderText(std::string t);

		bool isPressed(SDL_MouseButtonEvent &e);

		SDL_Rect getRect();

		void setActive(bool val) { this->active = val; }
		bool isActive() { return this->active; }

		void setPosition(int x, int y) { buttonShape.x = x; buttonShape.y = y; }

		void setSelected(bool s) { mSelected = s; }
		bool getSelected() { return mSelected; }
        void isSelected();
		void setBackgroundTexture(std::string filename);
///		void setPosition(int x, int y);

	private:
		unsigned short buttonState;
		unsigned short id;
        int alpha;
		SDL_Rect buttonShape;
		TTF_Font* font;
		SDL_Colour colour;

		bool mSelected;

		bool mClicked;
		bool mInside;	//Checks mouse is inside this button

		bool active;
		bool stateChange;


		std::unique_ptr<class Texture> backgroundTexture;
		std::unique_ptr<class Texture> mTextureText;    //TODO: Check this is right.
		std::string mRenderText;
	};

	class Text {

	public:

		Text(bool border = false);
		Text(int x, int y, int w, int h, bool border = true);
		Text(std::string);
		virtual ~Text();

		void update();

		int getTextWidth();

		void setBgColour(int r, int g, int b, int a);

		int getTextHeight();

		void render();

		void setPosition(int x, int y);
		void setPositionF(int x, int y, int w = 0, int h = 0);

        bool isEmpty();
        void clearText();
        bool intersects(int x, int y);

		void setString(std::string text, bool wrapped = false, int width = 0);

		SDL_Texture* getTexture();

		std::string getString();

		SDL_Rect getGlobalBounds() { return mOutline; }

		SDL_Rect getPositionRect();

		void setColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		void setAlpha(Uint8 a);
		void setFontSize(int size);
		void updateWindow();
		void refreshGUI();
		void setTextParameters(std::string txt, SDL_Color colour, TTF_Font* font, int size);
		void setBorder(int x, int y, int w, int h);
		void setFontfile(std::string fontfile);

	private:

		void initFont();
		void initTextures();
		void initGUI();

		int offsetX, offsetY;
		std::string mFontFile;
		bool mBorder;

		SDL_Rect mOutline;
		SDL_Rect mFiller;
		SDL_Rect mFactionBg;
		SDL_Color mTextColour;
		SDL_Color mBackgroundColour;
		TTF_Font* mFont;

		int mFontSize;

		std::shared_ptr<Texture> mTextTexture;

		//SDL_Renderer* mRend;
		//SDL_Window* mWind;

		int percentX, percentY, percentW, percentH;
		std::string mMainText;
	};


	class TextureSelector {

	public:

		TextureSelector(float x, float y, float width, float height, float gridSize, std::shared_ptr<Texture> textureSheet, TTF_Font* font, std::string text, float scale = 1);
		~TextureSelector();

		//Accessors
		bool getActive();
		bool isHidden();
		const bool getKeyTime();
		const SDL_Rect& getTextureRect() const;

		void updateKeyTime(const float& dt);
		void update(SDL_MouseButtonEvent &e);
		void render();

	private:

		SDL_Rect bounds;
		std::shared_ptr<Texture> sheet;
		SDL_Rect selector;
		SDL_Rect textureRect;

		float keyTime;
		float keyTimeMax;
		float scale;
		float gridSize;
		bool active;
		bool hidden;
		GUI::Button* hideButton;
	};

	class Tooltip {

	public:

		Tooltip();
		~Tooltip();

		void setDisplayText(std::string txt);
        bool checkBounds(std::shared_ptr<GUI::Text> text);
		void setHidden(bool hidden);

		void setBounds(SDL_Rect outline){ this->outline = outline; }

		bool getHidden();

		void update();
		void render();

	private:

		std::unique_ptr<GUI::Text> displayText; //TODO: Check this is right...
		SDL_Rect outline;
		SDL_Rect fillRect;
		bool hidden;

	};

	class Menu{

		public:

			Menu();
			Menu(int type, bool test = false);

			virtual ~Menu();

			int getChoice();
			int getType();
			int getDynamicType();

			bool isSelected();
			void setActive(bool active);
			void toggleActive();
			bool getActive();

			void updateTextSelector();
			void updateInput();

            void update();
			void updateEvents(SDL_Event& e);

			void scrollText(int direction = 0);

			void render();
			void setClicked(); //WTF??
			void refreshGUI();

			/* Here be demons */
			void setBattleMenu();
			void setStandardMenu();
			void clearOptions();
			void setDialogueMenu(std::string percent = " ");
			void setDynamicMenu(std::vector<std::string> ops, int type);
            int getActiveOption() { return activeOption; }
			void setMenuOptions(std::vector<std::string> options, bool dynamic = false, bool item = false, bool wep = false, bool arm = false); //ONLY ONE YOU NEED I BELIEVE!!!!
			void setPosition();

			bool cursorDetached();
			void setCursorDetached(bool d) { detachCursor = d; }

		private:

			TTF_Font* font;
			SDL_Rect outline;
			SDL_Rect textSelector;

			bool detachCursor;

			std::unique_ptr<Texture> scrollArrowDown;
			std::unique_ptr<Texture> scrollArrowUp;

			std::shared_ptr<GameTimer> menuTimer;

			unsigned charSize;
            int activeOption;
			unsigned hiddenCount;
			int selection;
			bool clicked;
			bool active;

			class StateData* mStateData;

			bool exit;

			/*Think this is not used too mmuch??*/
			int type;
			int dynamicType;

			bool textSelectorActive;
			bool scrollable;

			std::vector<std::string> ops; //Duplicate, why have this??
			std::vector<Texture*> options;
	};


	class textBox{

        public:

            textBox();
            ~textBox();

            void setHeader(std::string txt);
            void setText(std::string txt);
            void setSize(int h, int w);
            void setAlpha(int alpha);
            void update();
            void setPosition(int x, int y);
            void centreTextBox();
            void refreshGUI();
            void render();
            void updateEvents(SDL_MouseButtonEvent &e);

            void setConfirm(bool c) { confirm = c;}
            bool getConfirm(){ return confirm; }
            bool getChoice() { return choice; }
            void setChoice(bool c) { choice = c; }

            inline void setActive(bool a) { active = a; }
            inline bool getActive() { return active; }
            inline GUI::Text getText() { return text; }
            inline SDL_Texture* getTexture() { return text.getTexture(); }
            inline SDL_Texture* getHeaderTexture() { return header.getTexture(); }

            bool yesPressed(SDL_MouseButtonEvent &e){ return yesButton->isPressed(e); }
            bool noPressed(SDL_MouseButtonEvent &e){ return noButton->isPressed(e); }

        private:

            GUI::Text header;
            GUI::Text text;

            int alpha;
            int width;
            int height;

            std::shared_ptr<GUI::Button> yesButton;
            std::shared_ptr<GUI::Button> noButton;

            bool confirm;
            bool choice;

            bool active;

            SDL_Rect outline;
            SDL_Rect filler;
            SDL_Rect bg;
	};


	class InvSlot{

    public:
        InvSlot();
        ~InvSlot();

        void update();
        void render();

        void setPosition(int x, int y);
        void setDimensions(int w, int h);
        void setTileSheet(std::string filename, SDL_Rect* clip = NULL);
        std::shared_ptr<Texture> getTexture() { return iconTexture; }
//        void setClips(std::vector<SDL_Rect> c){ clips = c; }
        void setText(std::string t){ itemText->setString(t, true); }
        int getWidth() {return w;}
        int getHeight(){ return h; }

        bool isSelected(){ return selectorActive; }

    private:
        std::shared_ptr<Texture> iconTexture;
        std::shared_ptr<Texture> tileSheet;
        std::shared_ptr<Text> itemText;

        SDL_Rect bgRect;
        SDL_Rect bgSelectedRect;
        SDL_Rect clip;
        SDL_Rect iconRect;
        SDL_Rect outline;
      //  SDL_Rect selector;
        bool selectorActive;
        int w;
        int h;
	};
};

#endif

