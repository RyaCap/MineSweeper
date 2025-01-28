#include "SaveAndLoad.h"

/*.CSV SAVE FILE GOES LIKE THIS :
EXAMPLE:
    size,flattenedplayergameboard,flattenedAnswerGameBoard,errorsallowed,minesExploded
    6,nnnFnn2n,eeememmee,0,0
*/

bool SaveGame(int boardSize, std::vector<std::vector<std::string>> PlayerGameBoard, std::vector<std::vector<std::string>> AnswerGameBoard, int loseCondition, int minesExploded) {
    std::ofstream MyFile;
    MyFile.open(SAVE_FILE_NAME);
    if (!MyFile.is_open()) {
        std::cout << "Error opening output file to save!\n";
        return false;
    }

    MyFile << boardSize << ",";
    std::string PlayerGameBoardString = "", AnswerGameBoardString = "";
    for (int i = 0; i < PlayerGameBoard.size(); i++) {
        for (int j = 0; j < PlayerGameBoard[0].size(); j++) {
            if (PlayerGameBoard[i][j] == "n") {
                PlayerGameBoardString.append(PlayerGameBoard[i][j]);
            }
            else {
                PlayerGameBoardString.append(PlayerGameBoard[i][j] + "_");
            }
        }
        MyFile << PlayerGameBoardString << ",";
        PlayerGameBoardString = "";
    }
    for (int i = 0; i < AnswerGameBoard.size(); i++) {
        for (int j = 0; j < AnswerGameBoard[0].size(); j++) {
            AnswerGameBoardString.append(AnswerGameBoard[i][j]);
        }
        MyFile << AnswerGameBoardString << ",";
        AnswerGameBoardString = "";
    }
    MyFile << loseCondition << "," << minesExploded;
    MyFile.close();
    return true;
}

bool LoadGame(int& boardSize, std::vector<std::vector<std::string>>& PlayerGameBoard, std::vector<std::vector<std::string>>& AnswerGameBoard, int& loseCondition, int& minesExploded) {
    std::cout << "Checking for a saved game to load...\n";
    std::string data = "";
    std::ifstream MyFile;
    MyFile.open(SAVE_FILE_NAME);
    if (!MyFile.is_open()) {
        std::cout << "Error opening input file to save!\n";
        return false;
    }

    std::getline(MyFile, data);
    if (data.size() == 0) {
        return false;
    }

    int commaPlace = 0, mLoc = 0;
    std::string dataSegment = "", tempString = "";
    dataSegment = findWord(data); //size
    boardSize = std::stoi(dataSegment);
    
    PlayerGameBoard.resize(boardSize, std::vector<std::string>(boardSize));
    AnswerGameBoard.resize(boardSize, std::vector<std::string>(boardSize));

    for (int i = 0; i < boardSize; i++) {
        dataSegment = findWord(data); //PlayerGameBoard
        for (int j = 0; j < boardSize; j++) {
            if (dataSegment[0] == '\033' || dataSegment[0] == '\1B') {
                mLoc = dataSegment.find_first_of('_');
                PlayerGameBoard[i][j] = dataSegment.substr(0, mLoc);
                dataSegment.erase(0, mLoc + 1);
            }
            else {
                PlayerGameBoard[i][j] = dataSegment[0];
                dataSegment.erase(0, 1);
            }

            if ((j == (boardSize - 1)) && (dataSegment.size() != 0)) {
                PlayerGameBoard.clear();
                return false;
            }
        }
    }

    for (int i = 0; i < boardSize; i++) {
        dataSegment = findWord(data); //PlayerGameBoard
        for (int j = 0; j < boardSize; j++) {
            AnswerGameBoard[i][j] = dataSegment[0];
            dataSegment.erase(0, 1);

            if ((j == (boardSize - 1)) && (dataSegment.size() != 0)) {
                PlayerGameBoard.clear();
                return false;
            }
        }
    }

    dataSegment = findWord(data); //errorsAllowed
    loseCondition = std::stoi(dataSegment);
    dataSegment = findWord(data); //minesExploded
    minesExploded = std::stoi(dataSegment);

    // Close the file
    MyFile.close();
    return true;
}

std::string findWord(std::string& data) {
    int commaPlace = (int)data.find_first_of(",");
    std::string word;
    word = data.substr(0, commaPlace);
    data.erase(0, commaPlace + 1);

    return word;
}