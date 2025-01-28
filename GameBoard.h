#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "UserInput.h"
#include "BorderLogic.h"

//Difficulty Levels
const int BASIC_DIFFICULTY = 6;
const int INTERMEDIATE_DIFFICULTY = 8;
const int ADVANCED_DIFFICULTY = 10;
const int MIN_COORDINATE = 1;

//ANSI CODE for Color
const std::string ANSI_RED = "\033[31m";
const std::string ANSI_ORANGE = "\033[33m";
const std::string ANSI_GREEN = "\x1B[32m";
const std::string ANSI_BLUE = "\x1B[94m";
const std::string ANSI_WHITE = "\033[0m"; //White

//GameBoard Pieces
const std::string NOT_MINED = "n";
const std::string FLAG = ANSI_BLUE + "F" + ANSI_WHITE;
const std::string MINED_SQUARE = "m";
const std::string EMPTY_SQUARE = "e";

void DisplayGameBoard(std::vector<std::vector<std::string>> GameBoard);
std::vector<std::vector<std::string>> InsertMines(std::vector<std::vector<std::string>> GameBoard);
int CountMines(std::vector<std::vector<std::string>> GameBoard);
void GetCoordinates(std::vector<std::vector<std::string>> GameBoard, int& coordinateX, int& coordinateY);

std::vector<std::vector<std::string>> ClearSquare(std::vector<std::vector<std::string>> GameBoard, std::vector<std::vector<std::string>> AnswerGameBoard, int& coordinateX, int& coordinateY, int& minesExploded);
    int FindSurroundingMines(std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY);
std::vector<std::vector<std::string>> FlagSquare(std::vector<std::vector<std::string>> GameBoard, int& coordinateX, int& coordinateY);
std::vector<std::vector<std::string>> UnFlagSquare(std::vector<std::vector<std::string>> GameBoard, int& coordinateX, int& coordinateY);

bool CheckIfWon(std::vector<std::vector<std::string>> GameBoard, std::vector<std::vector<std::string>> AnswerBoard);