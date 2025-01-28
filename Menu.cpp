#include "Menu.h"

void BoardSelectionMenu() {
    std::cout << "Please select one of the following:\n";
    std::cout << "1. Basic Level\n";
    std::cout << "2. Intermediate Level\n";
    std::cout << "3. Advanced Level\n";
    std::cout << "4. Load a Previously Saved Game\n";
    std::cout << "5. Quit\n";
}

void LoseConditionMenu() {
    std::cout << "Please select the maximum number of mines m that can be selected without losing.\n";
    std::cout << "Please input a number between 0-3: ";
}

void ActionMenu() {
    std::cout << "Please select your next action.\n";
    std::cout << "1. Clear a square.\n";
    std::cout << "2. Flag a square.\n";
    std::cout << "3. Unflag a square.\n";
    std::cout << "4. Check if won.\n";
    std::cout << "5. Quit without saving.\n"; //MAYBE PUT A HELP SUGGESTION
    std::cout << "6. Save and Quit.\n";
}