#include "UserInput.h"

int UserInput(void (*Menu)(), int minOption, int optionCount) {
    std::string userInput;
    int verifiedInput = 0;
    while (true) {
        Menu();
        std::cout << "Please type here: ";
        std::getline(std::cin >> std::ws, userInput);
        bool isNumericInput = true;
        for (char ch : userInput) {
            if (!std::isdigit(ch)) {
                isNumericInput = false;
                std::cout << "Invalid Input. You must input a valid input number value.\n\n";
                break;
            }
        }
        if (isNumericInput == true) {
            verifiedInput = std::stoi(userInput);
            if (!(verifiedInput >= minOption && verifiedInput <= optionCount)) {
                std::cout << "Invalid Input. You must input a valid input number value.\n\n";
                continue;
            }
            std::cout << '\n';
            return verifiedInput;
        }
    }
    std::cout << '\n';
    return -1;
}

void CoordinateXPrompt() {
    std::cout << "Please input a valid coordinate for X:\n";
}
void CoordinateYPrompt() {
    std::cout << "Please input a valid coordinate for Y:\n";
}