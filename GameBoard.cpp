#include "GameBoard.h"

void DisplayGameBoard(std::vector<std::vector<std::string>> GameBoard) {
    for (int i = 0; i < GameBoard.size(); i++) {
        for (int j = 0; j < GameBoard[0].size(); j++) {
            std::cout << GameBoard[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

std::vector<std::vector<std::string>> InsertMines(std::vector<std::vector<std::string>> GameBoard) {
    int numberOfMines = 1, rateOfMines = 0;
    if ((GameBoard.size() != BASIC_DIFFICULTY) && (GameBoard.size() != INTERMEDIATE_DIFFICULTY) && (GameBoard.size() != ADVANCED_DIFFICULTY)) {
        system("cls");
        std::cerr << "Error insterting mines. Exiting the game.\n";
        exit(1);
    }

    if (GameBoard.size() == BASIC_DIFFICULTY) {
        numberOfMines = (BASIC_DIFFICULTY * BASIC_DIFFICULTY) / 3;
    }
    else if (GameBoard.size() == INTERMEDIATE_DIFFICULTY) {
        numberOfMines = (INTERMEDIATE_DIFFICULTY * INTERMEDIATE_DIFFICULTY) / 4;
    }
    else if (GameBoard.size() == ADVANCED_DIFFICULTY) {
        numberOfMines = (ADVANCED_DIFFICULTY * ADVANCED_DIFFICULTY) / 4;
    }

    //Places the correct number of mines within the vector. Will be shuffled later
    int rows = (int)GameBoard.size();
    int cols = (int)GameBoard[0].size();
    std::vector<std::string> flattenedBoard(rows * cols, EMPTY_SQUARE);
    if (!(numberOfMines <= rows * cols)) { exit(1); } //checks to prevent out of bounds. SHOULD NOT HAPPEN. Temporary solution

    //Places the proper number of mines into the temporary game board that will be transfered into the proper board after shuffling
    for (int i = 0; i < numberOfMines; i++) {
        flattenedBoard[i] = 'm';
    }
    
    //Randomly shuffles the flattened board
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(flattenedBoard.begin(), flattenedBoard.end(), rng);

    //Places the flattened board's new order and puts it into the GameBoard
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            GameBoard[i][j] = flattenedBoard[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(i) * cols + j];
        }
    }

    return GameBoard;
}

int CountMines(std::vector<std::vector<std::string>> GameBoard) {
    int count = 0;
    for (int i = 0; i < GameBoard.size(); i++) {
        for (int j = 0; j < GameBoard.size(); j++) {
            if (GameBoard[i][j] == MINED_SQUARE) {
                count++;
            }
        }
    }
    return count;
}

void GetCoordinates(std::vector<std::vector<std::string>> GameBoard, int& coordinateX, int& coordinateY) {
    DisplayGameBoard(GameBoard);
    std::cout << "Please follow the directions to ensure your input is properly read...\n";
    std::cout << "The top left begins at (1,1) with the (x,y) being the (column number, row number).\n\n";
    coordinateX = (UserInput(CoordinateXPrompt, MIN_COORDINATE, (int)GameBoard.size()) - 1);
    coordinateY = (UserInput(CoordinateYPrompt, MIN_COORDINATE, (int)GameBoard[0].size()) - 1);
    return;
}

std::vector<std::vector<std::string>> ClearSquare(std::vector<std::vector<std::string>> GameBoard, std::vector<std::vector<std::string>> AnswerGameBoard, int& coordinateX, int& coordinateY, int& minesExploded) {
    int mineCount = 0;
    bool spotWasMine = false;
    std::string numberOfMines;
    while (true) {
        system("cls");
        std::cout << "You selected to clear a square.\n";
        GetCoordinates(GameBoard, coordinateX, coordinateY);

        if (GameBoard[coordinateY][coordinateX] != NOT_MINED) {
            system("cls");
            std::cout << "The area has already been mined. You will be returned back to the Action Menu.\n";
            return GameBoard;
        }

        if (GameBoard[coordinateY][coordinateX] == FLAG) {
            system("cls");
            std::cout << "This spot is flagged, you cannot clear the square until the square is unflagged.\n";
            return GameBoard;
        }

        if (GameBoard[coordinateY][coordinateX] == NOT_MINED) {
            if (AnswerGameBoard[coordinateY][coordinateX] == MINED_SQUARE) {
                AnswerGameBoard[coordinateY][coordinateX] = EXPLODED_BOMB;
                system("cls");
                std::cout << "BOOM! You found a mine and it exploded.\n";
                spotWasMine = true;
                minesExploded++;
            }
            else {
                system("cls");
                std::cout << "The desired square has been mined. No bomb was found.\n";
            }
            //Find the surrounding mines
            mineCount = FindSurroundingMines(AnswerGameBoard, coordinateX, coordinateY);
            numberOfMines = std::to_string(mineCount);

            if (spotWasMine == true) {
                numberOfMines = ANSI_RED + numberOfMines + ANSI_WHITE;
            }
            else if (numberOfMines == "0") {
                numberOfMines = ANSI_GREEN + numberOfMines + ANSI_WHITE;
            }
            else {
                numberOfMines = ANSI_ORANGE + numberOfMines + ANSI_WHITE;
            }
            GameBoard[coordinateY][coordinateX] = numberOfMines;
            return GameBoard;
        }
    }
    return GameBoard;
}

int FindSurroundingMines(std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY) {
    int mineCount = 0;
    char xBorder = 'n';
    char yBorder = 'n';
    if (coordinateX == 0) {
        xBorder = 'l';
    }
    else if (coordinateX == GameBoard.size() - 1) {
        xBorder = 'r';
    }

    if (coordinateY == 0) {
        yBorder = 't';
    }
    else if (coordinateY == GameBoard[0].size() - 1) {
        yBorder = 'b';
    }


    if (xBorder == 'n' && yBorder == 'n') {
        mineCount = NonBorderSpots(MINED_SQUARE, GameBoard, coordinateX, coordinateY, mineCount);
    }
    else if (xBorder == 'n') {
        if (yBorder != 't' && yBorder != 'b') {
            system("cls");
            std::cerr << "There was an error. YBorder found as something else in GameBoard.cpp. Function is FindSurroundingMines.\n";
            exit(-1);
        }
        mineCount = SingleBorderSpots(MINED_SQUARE, GameBoard, coordinateX, coordinateY, mineCount, yBorder);
    }
    else if (yBorder ==  'n') {
        if (xBorder != 'l' && xBorder != 'r') {
            system("cls");
            std::cerr << "There was an error. XBorder found as something else in GameBoard.cpp. Function is FindSurroundingMines.\n";
            exit(-1);
        }
        mineCount = SingleBorderSpots(MINED_SQUARE, GameBoard, coordinateX, coordinateY, mineCount, xBorder);
    }
    else if (xBorder != 'n' && yBorder != 'n') {
        if ((xBorder != 'l' && xBorder != 'r') && (yBorder != 't' && yBorder != 'b')) {
            system("cls");
            std::cerr << "There was an error. XBorder and YBorder found as something else in GameBoard.cpp. AKA NOT VALID. Function is FindSurroundingMines.\n";
            exit(-1);
        }
        mineCount = DoubleBorderSpots(MINED_SQUARE, GameBoard, coordinateX, coordinateY, mineCount, xBorder, yBorder);
    }
    return mineCount;
}

std::vector<std::vector<std::string>> FlagSquare(std::vector<std::vector<std::string>> GameBoard, int& coordinateX, int& coordinateY) {
    system("cls");
    std::cout << "You selected to Flag a Square.\n";
    GetCoordinates(GameBoard, coordinateX, coordinateY);
    if ((GameBoard[coordinateY][coordinateX] != FLAG) && (GameBoard[coordinateY][coordinateX] != NOT_MINED)) {
        system("cls");
        std::cout << "A flag cannot be placed at this position.\n";
        return GameBoard;
    }

    if (GameBoard[coordinateY][coordinateX] == FLAG) {
        system("cls");
        std::cout << "A flag at that position already exists.\n";
        return GameBoard;
    }
    else {
        GameBoard[coordinateY][coordinateX] = FLAG;
        system("cls");
        std::cout << "A flag has been placed at that position.\n";
        return GameBoard;
    }

}

std::vector<std::vector<std::string>> UnFlagSquare(std::vector<std::vector<std::string>> GameBoard, int& coordinateX, int& coordinateY) {
    system("cls");
    std::cout << "You chose to Unflag a Square\n";
    GetCoordinates(GameBoard, coordinateX, coordinateY);

    if (GameBoard[coordinateY][coordinateX] != FLAG) {
        system("cls");
        std::cout << "There is no flag to be found at that position.\n";
        return GameBoard;
    }

    GameBoard[coordinateY][coordinateX] = NOT_MINED;
    system("cls");
    std::cout << "Flag Cleared at that position.\n";
    return GameBoard;
}

bool CheckIfWon(std::vector<std::vector<std::string>> GameBoard, std::vector<std::vector<std::string>> AnswerBoard) {
    for (int i = 0; i < GameBoard.size(); i++) {
        for (int j = 0; j < GameBoard[0].size(); j++) {
            if ((GameBoard[i][j] == NOT_MINED) || (GameBoard[i][j] == FLAG) && (AnswerBoard[i][j] == EMPTY_SQUARE)) {
                return false;
            }
        }
    }
    return true;
}