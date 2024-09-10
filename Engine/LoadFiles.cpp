#include "LoadFiles.h"

#include <unordered_set>

LoadFiles::LoadFiles(std::string filename, int type) : m_filename(filename){

    //Open a file from


    ///FUNCTION 1
    if(type == -1){

        ifstream inFile(m_filename);

        int fact = -1;
        std::string dialogue;

        std::string line = "";
        stringstream strs;

        if(inFile.is_open()){

            while(getline(inFile, line)){

                strs.str(line);
                strs >> m_faction;
                strs.clear();
                line.clear();

                getline(inFile, line);
                strs.str(line);
                strs >> m_name;
                strs.clear();
                line.clear();

                getline(inFile, line);
                strs.str(line);
                // Replace "\n" with actual newline characters
                size_t found = line.find("\\n");
                while (found != std::string::npos) {
                    line.replace(found, 2, "\n");
                    found = line.find("\\n", found + 1);
                }
                m_dialogue = line;
                strs.clear();
                line.clear();
            }

            inFile.close();
        }
    }
    else if(type == 0){
            ///FUNCTION 2
             ifstream inFile(m_filename);

            int fact = -1;
            std::string dialogue;

            std::string line = "";
            stringstream strs;

            if(inFile.is_open()){

                while(getline(inFile, line)){

//                    strs.str(line);
//                    strs >> m_faction;
//                    strs.clear();
//                    line.clear();
//
//                    getline(inFile, line);
//                    strs.str(line);
//                    strs >> m_name;
//                    strs.clear();
//                    line.clear();
//
//                    getline(inFile, line);
                    strs.str(line);
                    // Replace "\n" with actual newline characters
                    size_t found = line.find("\\n");
                    while (found != std::string::npos) {
                        line.replace(found, 2, "\n");
                        found = line.find("\\n", found + 1);
                    }
                    m_dialogue = line;
                    strs.clear();
                    line.clear();

                    m_dialogueArray.push_back(m_dialogue);
                }

                inFile.close();
            }
    }
    else{

        loadFactionDialogue(type);
    }
}

LoadFiles::~LoadFiles(){

    this->currDiagID = 0;
    this->dialogueMap.clear();
    this->playerOps.clear();

}

int LoadFiles::loadFaction(){

    return m_faction;
}

std::string LoadFiles::loadDialogue(){


    return questDialogue;
}

bool LoadFiles::startsWith(const std::string& line, int number) {
    std::string searchString = std::to_string(number) + ".";
    return line.find(searchString) == 0;
}

string LoadFiles::loadFactionDialogue(int id1, int id2, int id3)
{

    std::unordered_set<int> searchNumbers;

    searchNumbers.insert(id1);
    searchNumbers.insert(id2);
    searchNumbers.insert(id3);
    if(m_filename == "Assets/factionQuests.txt"){

        m_dialogueArray.clear();

        std::ifstream file(m_filename);
        std::vector<std::string> matchingLines;

    std::string line;

     if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return "ERROR";
    }





    ///#############################################
    while (std::getline(file, line)) {
        // Use a string stream to parse the line
        //std::istringstream iss(line);

        if(startsWith(line, id1)){

            // Check if the line contains the second number
            std::string searchString = std::to_string(id2) + ".";
            size_t pos = line.find(searchString);
            if (pos != std::string::npos) {
                // Extract the last number from the line
                std::string lastNumberStr = line.substr(pos + searchString.length());

                // Try to convert the last number to an integer
                int lastNumber;
                if (std::istringstream(lastNumberStr) >> lastNumber) {
                    // Increase the last number by 1
                    lastNumber += 1;

                    // Create the new line with the updated last number
                    std::string updatedLine = line.substr(0, pos + searchString.length()) + std::to_string(lastNumber);

                    // Store the updated line in the vector
                    m_dialogueArray.push_back(updatedLine);



//            //yes OLD
//            // Check if the line contains the second and third numbers in order
//            std::string searchString = std::to_string(id2) + "." + std::to_string(id3);
//            if (line.find(searchString) != std::string::npos) {
//                // Store the line in the vector
//                m_dialogueArray.push_back(line);
//            }

        }
    }
    }
    ///###########################################

    // Close the file
    }
    file.close();

    return m_dialogueArray[0];
    }
    else{

        return "This is wrong";
    }
}


string LoadFiles::loadQuestDialogue(int id = 1){

    return "NOTHING";
}

std::vector<std::string> LoadFiles::loadPlayerOptions(){

    playerOps.clear();
//    playerOps.push_back(dia.responses[1]);
   return playerOps;
}




std::string LoadFiles::loadRandomDialogue(){

    //m_dialogueArray[];
    return m_dialogueArray[rand() % m_dialogueArray.size()];
}

string LoadFiles::loadName(){

    return m_name;
}

void LoadFiles::readJsonFile(const std::string& filename){

    m_filename = filename;

    std::ifstream file(m_filename);

        if(!file.is_open()){

            std::cerr << "Error opening file: " << m_filename << std::endl;

            return;
        }

        json jsonData;
        file >> jsonData;

        //extract variables
        for(const auto& dialogue : jsonData["dialogues"]){

            int id = dialogue["id"];
            std::string faction = dialogue["faction"];
            int dialogueID = dialogue["dialogueId"];
            std::string text = dialogue["text"];

            dia.dialogueId = dialogueID;
            dia.faction = faction;
            dia.text = text;

            questDialogue = dia.text;
//            dia.diagMap[dialogueID] = text;

            //process responses
            for(const auto& response : dialogue["responses"]){

                int responseID = response["id"];
                std::string responseText = response["text"];
                int nextDialogue = response["nextDialogue"];

                playerOps.push_back("responseText");
                //DO SOMETHING WITH EXTRACTED VARIABLES....
//                dia.responses[responseID] = responseText;
            }
        }
}

void LoadFiles::readJsonFile2(const std::string& filename)
{

    // Read the JSON file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    json jsonData;
    file >> jsonData;

    // Extract relevant variables and populate the map
    for (const auto& dialogue : jsonData["dialogues"]) {
        Dialogue dialog;
        dialog.id = dialogue["id"];
        dialog.faction = dialogue["faction"];
        dialog.dialogueId = dialogue["dialogueId"];
        dialog.text = dialogue["text"];

        // Process responses
        for (const auto& response : dialogue["responses"]) {
            Response resp;
            resp.id = response["id"];
            resp.text = response["text"];
            resp.nextDialogue = response["nextDialogue"];
            dialog.responses.push_back(resp);
        }

        // Store the dialogue in the map based on faction and ID
        dialogueMap[dialog.faction][dialog.dialogueId] = dialog;
}
}

std::string LoadFiles::getDialogue(std::string faction, int id){

    std::string msg = "";
    //msg = dialogueMap.at(faction).at(id);

    ///TODO Hacky as fuck, fix this
    if(id == 0){

        faction = "Red";
    }
    auto factionIter = dialogueMap.find(faction);
    if (factionIter != dialogueMap.end()) {
        auto dialogueIter = factionIter->second.find(id);
        msg = dialogueIter->second.text;

        currDiagID = id;
    }

    return msg;
}

std::vector<std::string> LoadFiles::getResponses(int id){

//    std::string faction = "red";
//    auto factionIter = dialogueMap.find(faction);
//    if (factionIter != dialogueMap.end()) {
//        auto dialogueIter = factionIter->second.find(id);
//        if (dialogueIter != factionIter->second.end()) {
//            const Dialogue& dialog = dialogueIter->second;
//
//            // Find the selected response
//            auto responseIter = std::find_if(dialog.responses.begin(), dialog.responses.end(), [selectedResponseId](const Response& resp) {
//      //          nextDiagID = resp.nextDiaglogue;
//                return resp.id == selectedResponseId;
//            });
//
//            if (responseIter != dialog.responses.end()) {
//                // Return the text of the selected response and the next dialogue with its responses
// ///               questDialogue = responseIter->text;
//                nextDiagID = responseIter->nextDialogue;
//                playerOps = getFirstResponses(faction, responseIter->nextDialogue);
//                return std::make_pair(responseIter->text, dialogueMap.at(faction).at(responseIter->nextDialogue).responses);
//            } else {
//                std::cerr << "Selected response not found." << std::endl;
//            }

std::vector<std::string> ops;

return ops;
}


void LoadFiles::selectResponse(std::string faction, int id, int respID){

///TODO more hacky stuff
if(id == 0){

    faction = "Red";
}

auto factionIter = dialogueMap.find(faction);
    if (factionIter != dialogueMap.end()) {
        auto dialogueIter = factionIter->second.find(currDiagID);
        if (dialogueIter != factionIter->second.end()) {
            const Dialogue& dialog = dialogueIter->second;

            // Find the selected response
            auto responseIter = std::find_if(dialog.responses.begin(), dialog.responses.end(), [respID](const Response& resp) {
                //nextDiagID = resp.nextDialogue;
                return resp.id == respID;
            });

            if (responseIter != dialog.responses.end()) {
                // Return the text of the selected response and the next dialogue with its responses
 ///               questDialogue = responseIter->text;
                playerOps = getFirstResponses(faction, responseIter->nextDialogue);
                currDiagID = responseIter->nextDialogue;
                //nextDiagID = responseIter->nextDialogue;
      //          return std::make_pair(responseIter->text, dialogueMap.at(faction).at(responseIter->nextDialogue).responses);
            } else {
                std::cerr << "Selected response not found." << std::endl;
            }
        } else {
            std::cerr << "Dialogue ID not found for faction: " << faction << std::endl;
        }
    } else {
        std::cerr << "Faction not found: " << faction << std::endl;
    }

    // Return an empty pair if something goes wrong
    //return std::make_pair("", std::vector<Response>());
}


std::pair<std::string, std::vector<Response>> LoadFiles::getDialogueAndResponses(const std::string& faction, int dialogueId, double selectedResponseId){

    auto factionIter = dialogueMap.find(faction);
    if (factionIter != dialogueMap.end()) {
        auto dialogueIter = factionIter->second.find(dialogueId);
        if (dialogueIter != factionIter->second.end()) {
            const Dialogue& dialog = dialogueIter->second;

            // Find the selected response
            auto responseIter = std::find_if(dialog.responses.begin(), dialog.responses.end(), [selectedResponseId](const Response& resp) {
      //          nextDiagID = resp.nextDiaglogue;
                return resp.id == selectedResponseId;
            });

            if (responseIter != dialog.responses.end()) {
                // Return the text of the selected response and the next dialogue with its responses
 ///               questDialogue = responseIter->text;
                nextDiagID = responseIter->nextDialogue;
                playerOps = getFirstResponses(faction, responseIter->nextDialogue);
                return std::make_pair(responseIter->text, dialogueMap.at(faction).at(responseIter->nextDialogue).responses);
            } else {
                std::cerr << "Selected response not found." << std::endl;
            }
        } else {
            std::cerr << "Dialogue ID not found for faction: " << faction << std::endl;
        }
    } else {
        std::cerr << "Faction not found: " << faction << std::endl;
    }

    // Return an empty pair if something goes wrong
    return std::make_pair("", std::vector<Response>());

}

std::vector<std::string> LoadFiles::getFirstResponses(const std::string& faction, int dialogueId) {
    std::vector<std::string> firstResponses;

    ///TODO HACKZ
    if(dialogueId == 0){

        return std::vector<std::string>();
    }

    auto factionIter = dialogueMap.find(faction);
    if (factionIter != dialogueMap.end()) {
        auto dialogueIter = factionIter->second.find(dialogueId);
        if (dialogueIter != factionIter->second.end()) {
            const Dialogue& dialog = dialogueIter->second;
            currDiagID = dialog.dialogueId;
            // Extract response texts
            for (const auto& response : dialog.responses) {
                firstResponses.push_back(response.text);
     ///           nextDiagID = response.nextDialogue;
            }
        } else {
            std::cerr << "Dialogue ID not found for faction: " << faction << std::endl;
        }
    } else {
        std::cerr << "Faction not found: " << faction << std::endl;
    }

    return firstResponses;
}



