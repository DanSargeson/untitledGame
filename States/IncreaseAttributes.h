#ifndef CHARACTER_CREATOR
#define CHARACTER_CREATOR

#include "State.h"
#include "Texture.h"
#include "Player.h"


enum MENU_POS{

    NAME = -1,
    ATTRIBUTES = 0,
    SKILLS,
    DONE
};


class IncreaseAttributes : public State{


public:

    //void initFonts();
    void initKeyBinds();
    void initGUI();
    void initText();

    IncreaseAttributes();

    virtual ~IncreaseAttributes();

    //void setStateData();
    void updateButtons(const float& dt);
    void updateInput(const float& dt);
    void updateText(const float& dt);
    void update(const float& dt);

    std::shared_ptr<GUI::Text> strengthText;
    std::shared_ptr<GUI::Text> dexText;
    std::shared_ptr<GUI::Text> agiText;
    std::shared_ptr<GUI::Text> intText;
    std::shared_ptr<GUI::Text> charText;
    std::shared_ptr<GUI::Text> luckText;
    std::shared_ptr<GUI::Text> vitText;

    void updateEvents(SDL_Event& e);
    void updateMouseEvents(SDL_MouseButtonEvent& e);
    void updateTextInput(SDL_Event& e);

    void updateGUI();
    void render();

private:

//    char[] nameChar;

    std::shared_ptr<Texture> mTexture;
    int pointsToSpend;
    int maxPoints;

    std::unique_ptr<GUI::Text> pointsMessage;
    //std::unique_ptr<GUI::Text> nameMessage;

    int menuPos;
    int lastMenuPos;

    std::string agi;
    std::string cha;
    std::string dex;
    std::string intel;
    std::string luck;
    std::string strength;
    std::string vit;

    bool agiIncreased;
    bool chaIncreased;
    bool dexIncreased;
    bool intelIncreased;
    bool luckIncreased;
    bool strengthIncreased;
    bool vitIncreased;

    int agiCounter;
    int chaCounter;
    int dexCounter;
    int intelCounter;
    int luckCounter;
    int strengthCounter;
    int vitCounter;


    //std::shared_ptr<Player> temp;

   TTF_Font* font;
//    std::map<std::string, GUI::Button*> mButtons;   //TODO: Use smrt pointers

    std::unordered_map<std::string, std::unique_ptr<GUI::Button>> buttons;
    std::unordered_map<std::string, std::shared_ptr<Texture>> mSpritesPlus;
    std::unordered_map<std::string, std::shared_ptr<Texture>> mSpritesMinus;

    std::shared_ptr<Texture> spriteAddTexture;
    std::shared_ptr<Texture> spriteMinusTexture;

    std::shared_ptr<Texture> spriteAddAgility;
    std::shared_ptr<Texture> spriteMinusAgility;
    std::shared_ptr<Texture> spriteAddCha;
    std::shared_ptr<Texture> spriteMinusCha;
    std::shared_ptr<Texture> spriteAddDex;
    std::shared_ptr<Texture> spriteMinusDex;
    std::shared_ptr<Texture> spriteAddInt;
    std::shared_ptr<Texture> spriteMinusInt;
    std::shared_ptr<Texture> spriteAddLuck;
    std::shared_ptr<Texture> spriteMinusLuck;
    std::shared_ptr<Texture> spriteAddStrength;
    std::shared_ptr<Texture> spriteMinusStrength;
    std::shared_ptr<Texture> spriteAddVit;
    std::shared_ptr<Texture> spriteMinusVit;
    std::shared_ptr<GUI::Tooltip> attributeInfo;

    //TODO: Possibly need more textures for each stat..

    std::unique_ptr<GUI::Text> charCreatorText;
};

#endif // CHARACTER_CREATOR
