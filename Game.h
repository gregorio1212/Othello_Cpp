/**
 @file Game.h
 @author Gregório da Luz
 @date February 2021
 @brief Game header for Game.cpp for Othello game
 **/
#include <iostream>
#include "Player.h"

using namespace std;

class Game
{
private:
	char m_board[8][8];
	int m_disk_counter;			//limit up to 60
	char m_whose_turn;			//B -> Black, W -> White
	bool m_correctInput;		// check input when asking to play again
	bool m_end;	
	char m_playAgain;
	char m_opponent;			
	bool m_machine_check;
	bool m_move_available;
	int m_if_two_end;
	int m_x_path;
	int m_y_path;
	int m_temp;
	int m_if_flip_equals_10;
public:
	Game();
	void InitGame();
	void Info() const;
	bool goodInput(int x_value, int y_value)const;
	bool freeSlot(int x, int y)const;
	char getWhoseTurn() const { return m_whose_turn; }
	int getDiskCounter() const { return m_disk_counter; }
	void allowedSlotLoop(int x_, int y_, int i_c, int j_c, int lim_i, int lim_j);
	bool allowedSlot(int x, int y);
	bool allowedTurn();
	int flipAllDirections(int x, int y, int i_c, int j_c);
	void flipWhoseTurnAndOpponent();
	void settingNewDisk(int x, int y);
	void printBoard()const;
	bool noPossibleMove();
	bool getEnd() const { return m_end; }
	void setEnd(bool end) { m_end = end;}
	void theWinnerIs();
	void playAgain();
};



