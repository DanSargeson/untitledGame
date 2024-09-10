#pragma once
#include "Engine.h"
#include "json.hpp"

using json = nlohmann::json;


struct Response{

    double id;
    std::string text;
    int nextDialogue;
};

struct Dialogue{

    ///NEW SHIZZ
        int id;
         std::string faction;
         int dialogueId;
         std::string text;
         std::vector<Response> responses;
};

class LoadFiles{

    public:

        LoadFiles(std::string filename, int type = -1);
        ~LoadFiles();

        int loadFaction();
        std::string loadDialogue();
        std::string loadRandomDialogue();
        bool startsWith(const std::string& line, int number);
        std::string loadFactionDialogue(int id1, int id2 = 1, int id3 = 1);
        std::string loadQuestDialogue(int id);
        std::vector<std::string> loadPlayerOptions();
        std::string loadName();

        void readJsonFile(const std::string& filename);



        ///HERE BE NEWEST
        void readJsonFile2(const std::string& filename);
        std::string getDialogue(std::string faction, int id);
        std::pair<std::string, std::vector<Response>> getDialogueAndResponses(const std::string& faction, int dialogueId, double selectedResponseId);
        std::vector<std::string> getFirstResponses(const std::string& faction, int dialogueId);

        std::vector<std::string> getResponses(int id);

        void selectResponse(std::string faction, int id, int respID);

        int getNextDiagID() { return nextDiagID; };
        std::vector<std::string> getPlayerOps() { return playerOps; };
        inline int getCurrDiagID() { return currDiagID; }

        inline void setFaction(int i) { m_faction = i; }
        inline int getFaction() { return m_faction; }

    private:

        std::string m_filename;
        int m_faction;
        std::string m_name;
        std::string m_dialogue;
        std::vector<std::string> m_dialogueArray;
        int nextDiagID;
        int currDiagID;


        ///NEW SHIZZ
        std::string questDialogue;
        std::vector<std::string> playerOps;
        Dialogue dia;
        std::map<std::string, std::map<int, Dialogue>> dialogueMap;
};
