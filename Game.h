#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

class Game
{
private:
	char m_board[8][8];
	int m_disk_counter;			//limit up to 62
	char m_whose_turn;			//B -> Black, W -> White
	bool m_correctInput;		// check input when asking to play again
	bool m_end;	
	char m_playAgain;
	char m_opponent;			//used when checking surroundings of free slots
	bool m_machine_check;
	bool m_moves_available;
	int m_if_two_end;
	//flipAllDirections variables, i_c_ represent x changes and j_c_ represents y changes
	int i_c_;
	int j_c_;
	int if_flip_equals_10;
public:
	Game();
	void InitGame();
	void Info() const;
	bool goodInput(int x_value, int y_value)const;
	bool freeSlot(int x, int y)const;
	char getWhoseTurn() const { return m_whose_turn; }
	int getDiskCounter() const { return m_disk_counter; }
	bool allowedSlot(int x, int y);
	bool allowedTurn();
	int flipAllDirections(int x, int y, int i_c, int j_c);
	void flipWhoseTurnAndOpponent();
	void oneLessDiskGame() { m_disk_counter++; }
	void settingNewDisk(int x, int y) { m_board[x][y] = m_whose_turn; }
	void printBoard()const;
	bool noPossibleMove();
	bool getEnd() const { return m_end; }
	void setEnd(bool end) { m_end = end;}
	void theWinnerIs();
	void playAgain();
};



