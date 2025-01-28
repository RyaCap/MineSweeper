#include "BorderLogic.h"

int NonBorderSpots(const std::string MINED_SQUARE, std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY, int mineCount) {
    for (int i = coordinateX - 1; i <= coordinateX + 1; i++) {
        for (int j = coordinateY - 1; j <= coordinateY + 1; j++) {
            if (GameBoard[j][i] == MINED_SQUARE) {
                mineCount++;
            }
        }
    }
    return mineCount;
}

int SingleBorderSpots(const std::string MINED_SQUARE, std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY, int mineCount, char border) {
    if ((border != 'l' && border != 'r') && (border != 't' && border != 'b')) {
        system("cls");
        std::cerr << "There was an error. XBorder or YBorder found as something else in GameBoard.cpp. AKA NOT VALID. Function is SingleBorderingSpots.\n";
        exit(-1);
    }

    if (border == 'l') { //X is 0
        for (int i = coordinateX; i <= coordinateX + 1; i++) {
            for (int j = coordinateY - 1; j <= coordinateY + 1; j++) {
                if (GameBoard[j][i] == MINED_SQUARE) {
                    mineCount++;
                }
            }
        }
    }
    else if (border == 'r') { //X is MaxRightSide of GameBoard
        for (int i = coordinateX - 1; i <= coordinateX; i++) {
            for (int j = coordinateY - 1; j <= coordinateY + 1; j++) {
                if (GameBoard[j][i] == MINED_SQUARE) {
                    mineCount++;
                }
            }
        }
    } //Y is 0
    else if (border == 't') {
        for (int i = coordinateX - 1; i <= coordinateX + 1; i++) {
            for (int j = coordinateY; j <= coordinateY + 1; j++) {
                if (GameBoard[j][i] == MINED_SQUARE) {
                    mineCount++;
                }
            }
        }
    } //Y is at the bottom of GameBoard
    else if (border == 'b') {
        for (int i = coordinateX - 1; i <= coordinateX + 1; i++) {
            for (int j = coordinateY - 1; j <= coordinateY; j++) {
                if (GameBoard[j][i] == MINED_SQUARE) {
                    mineCount++;
                }
            }
        }
    }

    return mineCount;
}

int DoubleBorderSpots(const std::string MINED_SQUARE, std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY, int mineCount, char xBorder, char yBorder) {
    if ((xBorder != 'l' && xBorder != 'r') || (yBorder != 'b' && yBorder != 't')) {
        system("cls");
        std::cerr << "There was an error. YBorder found as something else in GameBoard.cpp. AKA NOT VALID. Function is DoubleBorderSpots.\n";
        exit(-1);
    }

    if (xBorder == 'l') {
        if (yBorder == 't') {
            for (int i = coordinateX; i <= coordinateX + 1; i++) {
                for (int j = coordinateY; j <= coordinateY + 1; j++) {
                    if (GameBoard[j][i] == MINED_SQUARE) {
                        mineCount++;
                    }
                }
            }
        }
        else if (yBorder == 'b') {
            for (int i = coordinateX; i <= coordinateX + 1; i++) {
                for (int j = coordinateY - 1; j <= coordinateY; j++) {
                    if (GameBoard[j][i] == MINED_SQUARE) {
                        mineCount++;
                    }
                }
            }
        }
    }
    else if (xBorder == 'r') {
        if (yBorder == 't') {
            for (int i = coordinateX - 1; i <= coordinateX; i++) {
                for (int j = coordinateY; j <= coordinateY + 1; j++) {
                    if (GameBoard[j][i] == MINED_SQUARE) {
                        mineCount++;
                    }
                }
            }
        }
        else if (yBorder == 'b') {
            for (int i = coordinateX - 1; i <= coordinateX; i++) {
                for (int j = coordinateY - 1; j <= coordinateY; j++) {
                    if (GameBoard[j][i] == MINED_SQUARE) {
                        mineCount++;
                    }
                }
            }
        }
    }

    return mineCount;
}