#pragma once
/**
 @file Game.h
 @author Gregório da Luz
 @date February 2021
 @brief Game header for Game.cpp for Othello game
 **/
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>

class Game
{
private:
	std::unordered_map<int, char> m_board; // use % 8 to find the row
	std::unordered_map<int, bool> m_AllowedSpots;
	int m_disk_counter; // limit up to 60
	char m_whose_turn;	// B -> Black, W -> White
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
	void allowedSlotLoop(int x_, int y_, int i_c, int j_c, int lim_i, int lim_j);
	int flipAllDirections(int x, int y, int i_c, int j_c);
	bool allowedTurn();

public:
	Game();
	void InitGame();
	void Info() const;
	void printBoard() const;

	bool validInput(std::string &move) const;
	bool allowedInput(const std::string &move, int &x, int &y);
	bool goodSpotForCurrentPlayer(const int& x, const int& y);
	void updateTableAndAllowedSpots(const int& x, const int y);

	bool allowedSlot(int x, int y);

	void flipWhoseTurnAndOpponent();
	void settingNewDisk(int x, int y);

	bool noPossibleMove();
	void setEnd(bool end) { m_end = end; }
	void theWinnerIs();
	bool playAgain();

	char getWhoseTurn() const { return m_whose_turn; }
	int getDiskCounter() const { return m_disk_counter; }
	bool getEnd() const { return m_end; }
};
