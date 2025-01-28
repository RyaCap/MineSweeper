#include <iostream>
#include <string>
#include <vector>

//Custom Include Files
#include "Menu.h"
#include "UserInput.h"
#include "SaveAndLoad.h"
#include "GameBoard.h"
//"BorderLogic.h" is included within the GameBoard.h

//Symbolic Constant
const int MIN_MENU_OPTION = 1;
const int START_MENU_OPTIONS = 5;

int main()
{
    bool isLoaded = false, isSaved = false, checkIfWon = false;
    int boardSize = 1, minesExploded = 0, loseCondition = 0;
    std::vector<std::vector<std::string>> PlayerGameBoard; //This board is what the user sees
    std::vector<std::vector<std::string>> AnswerGameBoard;

LoadFailed:
    std::cout << "********************MineSweeper********************\n";
    int menuInput = UserInput(StartMenu, MIN_MENU_OPTION, START_MENU_OPTIONS);

    switch (menuInput) {
    case 1:
        boardSize = BASIC_DIFFICULTY;
        break;
    case 2:
        boardSize = INTERMEDIATE_DIFFICULTY;
        break;
    case 3:
        boardSize = ADVANCED_DIFFICULTY;
        break;
    case 4:
        isLoaded = LoadGame(boardSize, PlayerGameBoard, AnswerGameBoard, loseCondition, minesExploded);
        if (isLoaded == false) {
            system("cls");
            std::cout << "Unable to load saved game properly. Redirecting you back to the main menu.\n\n";
            goto LoadFailed;
        }
        goto LoadSuccessful;
        break;
    case 5: //QUIT
        system("cls");
        std::cout << "Thank you for playing. Have a great day!!\n";
        std::cout << "MineSweeper Terminated.\n";
        return 0;
    default:
        std::cout << "Could not recognize the selection. Basic level will be used instead.\n";
        boardSize = BASIC_DIFFICULTY;
    }

    //Establish Lose Condition
    loseCondition = UserInput(LoseConditionMenu, 0, MAX_FAILURES);

    PlayerGameBoard.resize(boardSize, std::vector<std::string>(boardSize, NOT_MINED));
    AnswerGameBoard.resize(boardSize, std::vector<std::string>(boardSize, NOT_MINED));
    AnswerGameBoard = InsertMines(AnswerGameBoard);

LoadSuccessful:
    system("cls");
    int menuSelection = 0, coordinateX = 0, coordinateY = 0;
    while (minesExploded <= loseCondition) {
        std::cout << "Player GameBoard:\n";
        DisplayGameBoard(PlayerGameBoard);
        std::cout<<"\n";

        menuSelection = UserInput(ActionMenu, MIN_MENU_OPTION, MENU_ACTION_COUNT);
        system("cls");
        switch (menuSelection) {
        case 1: //Clear a square
            PlayerGameBoard = ClearSquare(PlayerGameBoard, AnswerGameBoard, coordinateX, coordinateY, minesExploded);
            break;
        case 2: //Flag a square
            PlayerGameBoard = FlagSquare(PlayerGameBoard, coordinateX, coordinateY);
            break;
        case 3: //Unflag a square
            PlayerGameBoard = UnFlagSquare(PlayerGameBoard, coordinateX, coordinateY);
            break;
        case 4: //Check if won
            system("cls");
            std::cout << "Checking if won...\n";
            checkIfWon = CheckIfWon(PlayerGameBoard, AnswerGameBoard);
            if (checkIfWon == true) {
                system("cls");
                std::cout << "Congratulations!! You won MineSweeper!!\n";
                goto EndSequence;
            }
            else {
                system("cls");
                std::cout << "Sorry. You have not won yet. There are still places to mine.\n";
            }
            break;
        case 5: //Quit without saving
            std::cout << "You selected to quit without saving.\n";
            goto EndSequence;
            break;
        case MENU_ACTION_COUNT: //Save and Quit
            isSaved = SaveGame(boardSize, PlayerGameBoard, AnswerGameBoard, loseCondition, minesExploded);
            if (isSaved == false) {
                system("cls");
                std::cout << "Your current game was not saved properly. Redirecting you back to the main menu.\n";
            }
            else {
                goto SaveAndQuit;
            }
            break;
        default:
            system("cls");
            std::cout << "Error, should not happen. Please try again.\n";
        }
        std::cout << "-------------------------------------------------------------------------\n";
    }

    //ENDING SCRIPT
    if (minesExploded > loseCondition) {
        std::cout << "-------------------------------------------------------------------------\n";
        if (minesExploded == 1) { std::cout<<"You lost! You blew up " << minesExploded << " bomb.\n"; }
        else { std::cout<<"You lost! You blew up " << minesExploded << " bombs\n"; }
    }

    SaveAndQuit:
    if (isSaved) {
        std::cout << "--------------------------------------------------\n";
        std::cout << "Game Successfully Saved.\n";
    }

    EndSequence:
    std::cout << "--------------------------------------------------\n";
    std::cout << "Thank you for playing!! Have a great day!!\n";
    std::cout << "\n\n";
}