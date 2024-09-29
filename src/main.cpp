/**
 @file main.cpp
 @author Gregório da Luz
 @date February 2021
 @brief main.cpp for Othello game
 **/
#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"

int main()
{
    Game othello;
    Player white(PlayerColor::WHITE);
    Player black(PlayerColor::BLACK);

    int user_input_x = -1;
    int user_input_y = -1;
    std::string input_move = "";

    while (!othello.getEnd())
    {
        othello.printBoard();
        othello.Info();

        // This is useless, we should simply get the input from the user such 4,3 for example
        do
        {
            do
            {
                std::cout << "Write the coordinate move (e.g. 3,4):\n";
                std::cin >> input_move;
            } while (!othello.validInput(input_move));
        } while (!othello.allowedInput(input_move, user_input_x, user_input_y)); // Check if its a good and allowed input

        // othello.updateTableAndAllowedSpots(user_input_x, user_input_y);

#if 0 // User does not need to see this stuff, move for an internal function
        // keeping record of how many disks each player still has
        if (othello.getWhoseTurn() == 'B')
        {
            black.oneLessDisk(); // integrate players with the game class
        }
        else
        {
            white.oneLessDisk();
        }

        // if we have reached 60 disks on the board we avoid the normal procedure and set the end
        if (othello.getDiskCounter() <= 60)
        {
            othello.flipWhoseTurnAndOpponent();
            if (othello.noPossibleMove())
            {
                othello.setEnd(true);
            }
        }
        else
        {
            othello.setEnd(true);
        }


        // showing results and asking if the player wants to play again
        if (othello.getEnd())
        {
            othello.theWinnerIs();
            if (othello.playAgain()) // This can be here
            {
                black.resetDisks(); //  integrate it with the Game class
                white.resetDisks(); // integrate it with the Game class
            }
        }
        // checking if the player needs disks from the opponent to play
        else
        {
            if (othello.getWhoseTurn() == 'B' && black.getDisksAvailable() == 0)
            {
                black.giveMeOneDisk(white);//  integrate it with the Game class
            }
            else if (othello.getWhoseTurn() == 'W' && white.getDisksAvailable() == 0)
            {
                white.giveMeOneDisk(black);//  integrate it with the Game class
            }
        }
#endif
    }
}
