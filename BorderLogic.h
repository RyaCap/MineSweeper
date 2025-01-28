#pragma once
#include <iostream>
#include <vector>

int NonBorderSpots(const std::string MINED_SQUARE, std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY, int mineCount);
int SingleBorderSpots(const std::string MINED_SQUARE, std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY, int mineCount, char border);
int DoubleBorderSpots(const std::string MINED_SQUARE, std::vector<std::vector<std::string>> GameBoard, int coordinateX, int coordinateY, int mineCount, char xBorder, char yBorder);