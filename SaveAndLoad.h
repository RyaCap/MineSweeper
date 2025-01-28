#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::string SAVE_FILE_NAME = "SavedGame1.csv";

bool SaveGame(int boardSize, std::vector<std::vector<std::string>> PlayerGameBoard, std::vector<std::vector<std::string>> AnswerGameBoard, int loseCondition, int minesExploded);
bool LoadGame(int& boardSize, std::vector<std::vector<std::string>>& PlayerGameBoard, std::vector<std::vector<std::string>>& AnswerGameBoard, int& loseCondition, int& minesExploded);
std::string findWord(std::string& data);