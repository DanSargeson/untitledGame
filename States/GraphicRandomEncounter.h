#ifndef GRAPHICRANDOMENCOUNTER_H
#define GRAPHICRANDOMENCOUNTER_H

#include "State.h"
#include "TileMap.h"


class GraphicRandomEncounter : public State{


    public:
        GraphicRandomEncounter();
        virtual ~GraphicRandomEncounter();

        void update(const float &dt);
        void updateEvents(SDL_Event& e);
        void render();
        void refreshGUI();

    protected:

    private:
        std::shared_ptr<TileMap> tilemap;
        std::string mapTextureStr;
        std::shared_ptr<GUI::Tooltip> tileInfo;
};

#endif // GRAPHICRANDOMENCOUNTER_H
