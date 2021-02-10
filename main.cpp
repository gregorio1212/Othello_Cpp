/**
 @file main.cpp
 @author Gregório da Luz
 @date February 2021
 @brief main.cpp for Othello game
 **/
#include <iostream>
#include "Game.h"

using namespace std;
#define WHITE 1
#define BLACK 2

int main() {
    Game othello;
    Player white(WHITE);
    Player black(BLACK);
    int user_input_x = -1;
    int user_input_y = -1;
    bool allowed = false;

    while (!othello.getEnd()) {
        othello.printBoard();
        othello.Info();

        //while the slot is not allowed or not free, keep asking the user for input
        while (!allowed) {
            user_input_x = -1;
            user_input_y = -1;
            while (!othello.goodInput(user_input_x, user_input_y)) {//cheking if it is inside the range of 0 to 7 index 
                cout << "Write the x coord you want to place your disk:\n";
                cin >> user_input_x;
                cout << "Write the y coord you want to place your disk:\n";
                cin >> user_input_y;
            }
            if (othello.freeSlot(user_input_x, user_input_y)) { allowed = othello.allowedSlot(user_input_x, user_input_y); }
        }
        allowed = false;

        othello.settingNewDisk(user_input_x, user_input_y);
        //keeping record of how many disks each player still has
        if (othello.getWhoseTurn() == 'B') { black.oneLessDisk();}
        else { white.oneLessDisk();}

        // if we have reached 60 disks on the board we avoid the normal procedure and set the end
        if (othello.getDiskCounter() <= 60) {
            othello.flipWhoseTurnAndOpponent();
            if (othello.noPossibleMove()) { othello.setEnd(true); }
        }
        else { othello.setEnd(true); }

        //showing results and asking if the player wants to play again
        if (othello.getEnd()) {
            othello.theWinnerIs();
            black.resetDisks();
            white.resetDisks();
        }
        //checking if the player needs disks from the opponent to play
        else {
            if (othello.getWhoseTurn() == 'B' && black.getDisksAvailable() == 0) { black.giveMeOneDisk(white); }
            else if (othello.getWhoseTurn() == 'W' && white.getDisksAvailable() == 0) { white.giveMeOneDisk(black); }
        }  
    }
}
