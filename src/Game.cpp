/**
 @file Game.cpp
 @author Gregório da Luz
 @date February 2021
 @brief Game class for Othello game
 **/
#include "Game.h"

constexpr uint8_t COLUMNS = 8;
constexpr uint8_t ROWS = COLUMNS;

uint8_t convertToReal(int x, int y)
{
	return x * ROWS + y;	
}

Game::Game() : m_disk_counter{}, m_board{}, m_whose_turn{}, m_end{false}, m_playAgain{},
			   m_opponent{}, m_machine_check{}, m_move_available{}, m_if_two_end{0}, m_x_path{},
			   m_y_path{}, m_if_flip_equals_10{0}, m_temp{0}
{
	InitGame();
}

void Game::InitGame()
{
	// all the necessary setting up/cleaning up of variables for a new game
	m_disk_counter = 4;
	m_whose_turn = 'B';
	m_opponent = 'W';

	for (int i = 0; i < (ROWS * COLUMNS); i++)
	{
		auto row = i / COLUMNS;
		auto column = i % COLUMNS;

		if ((row == 3 && column == 3) || (row == 4 && column == 4))
		{
			m_board[i] = m_whose_turn;
		}
		else if ((row == 3 && column == 4) || (row == 4 && column == 3))
		{
			m_board[i] = m_opponent;
		}
		else
		{
			m_board[i] = '-';

			if ((row >= 2 && row <= 5) && (column >= 2 && column <= 5))
			{
				m_AllowedSpots[i] = true;
			}
			else
			{
				m_AllowedSpots[i] = false;
			}
		}
	}
}

void Game::Info() const
{
	std::cout << "Player ";
	if (m_whose_turn == 'B')
	{
		std::cout << "Black, it's your turn!\n";
	}
	else
	{
		std::cout << "White, it's your turn!\n";
	}
}

void Game::printBoard() const
{
	for (uint8_t i = 0; i < (ROWS * COLUMNS); i++)
	{
		auto row = i / COLUMNS;
		auto column = i % 8;

		if (row == 0 && column == 0)
		{
			std::cout << "    0 1 2 3 4 5 6 7 \n";
		}
		if (column == 0)
		{
			std::cout << row << " | " << m_board.at(i);
		}
		else if (column == 7)
		{
			std::cout << ' ' << m_board.at(i) << " |" << '\n';
		}
		else
		{
			std::cout << ' ' << m_board.at(i);
		}
	}
}

bool Game::validInput(std::string &move) const
{
	if (move[1] == ',' && move.length() == 3)
	{
		return true;
	}
	return false;
}

bool Game::goodSpotForCurrentPlayer(const int &x, const int &y)
{
	// TODO: need to be update
	return true;
}

bool Game::allowedInput(const std::string &move, int &x, int &y)
{
	x = move[0] - '0';
	y = move[2] - '0';

	if ((x < 0 || x >= 8) || (y < 0 || y >= 8))
	{
		std::cout << "Only coordinates in the range [0,7] are allowed!\n";
		return false;
	}

	if (m_AllowedSpots.at(convertToReal(x,y)))
	{
		return goodSpotForCurrentPlayer(x, y);
	}

	return false;
}

bool Game::allowedTurn()
{
	m_machine_check = true; // this will control the flipAllDirections() so that it won't actually flip the disks
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{ // it checks just until it finds one move that is available
			m_move_available = allowedSlot(x, y);
			if (m_move_available)
			{
				m_machine_check = false;
				return true;
			}
		}
	}
	m_machine_check = false;
	return false;
}

void Game::flipWhoseTurnAndOpponent()
{
	if (m_whose_turn == 'B')
	{
		m_whose_turn = 'W';
		m_opponent = 'B';
	}
	else
	{
		m_whose_turn = 'B';
		m_opponent = 'W';
	}
}

bool Game::noPossibleMove()
{
	while (!allowedTurn())
	{
		m_if_two_end++;
		// a player loses his turn because he had no possible move, but the other player has, so we keep playing.
		if (m_if_two_end == 1)
		{
			flipWhoseTurnAndOpponent();
		}
		// end of the game, no player can set a disk.
		if (m_if_two_end == 2)
		{
			m_if_two_end = 0;
			return true;
		}
	}
	m_if_two_end = 0;
	return false;
}

// I can simply keep an array of allowed positions from the beginning and block a move that is not part of that allowed
// x,y postion. Then once a piece is place make the adjustment in the colors in the board and update the allowed positions
// for each player

bool Game::allowedSlot(int x, int y)
{
	// variable that will control if some flipping on the disks occur
	m_temp = 0;
	m_if_flip_equals_10 = 0;
	// the ifs serves to separate parts of the board that have an equal type of surroundings check
	if (y > 1 && y < 6)
	{
		// The coulors refer to regions of the board, a schematics is present on the gitHub repository
		if (x < 2)
		{
			// allowedSlotLoop(x, y, 0, -1, 2, 2);
		} // red and blue upper check
		else if (x > 5)
		{
			// allowedSlotLoop(x, y, -1, -1, 1, 2);
		} // red and blue down check
		else
		{
			// allowedSlotLoop(x, y, -1, -1, 2, 2);
		} // yellow total check
	}
	else if (x > 1 && x < 6)
	{
		if (y < 2)
		{
			// allowedSlotLoop(x, y, -1, 0, 2, 2);
		} // check violet and rainbow(most left)
		else if (y > 5)
		{
			// allowedSlotLoop(x, y, -1, -1, 2, 1);
		} // check verde and moon(most right)
	}
	else if (x == 0 || x == 1)
	{
		if (y == 0 || y == 1)
		{
			// allowedSlotLoop(x, y, 0, 0, 2, 2);
		} // check upper left square
		else
		{
			// allowedSlotLoop(x, y, 0, -1, 2, 1);
		} // check upper right square
	}
	else if (x == 6 || x == 7)
	{
		if (y == 0 || y == 1)
		{
			// allowedSlotLoop(x, y, -1, 0, 1, 2);
		} // check lower left square
		else
		{
			// allowedSlotLoop(x, y, -1, -1, 1, 1);
		} // check lower right square
	}
	// end of possible checks
	if (m_if_flip_equals_10 == 10)
	{
		return true;
	}
	if (!m_machine_check)
	{
		std::cout << "This slot is not allowed, pick another one\n\n";
	}
	return false;
}

void Game::settingNewDisk(int x, int y)
{
	// here we must also update the allowed spots for both players
	m_board[convertToReal(x,y)] = m_whose_turn;
	m_disk_counter++;
}

bool Game::playAgain()
{
	while (1)
	{ // infinite loop until we get the right input from the player
		std::cout << "Would you like to play it again? (type y - yes or n - no)\n";
		std::cin >> m_playAgain;
		if (m_playAgain == 'y' || m_playAgain == 'Y')
		{
			std::cout << "Nice! Let's play again!\n";
			m_end = false;
			InitGame();
			return true;
		}
		else if (m_playAgain == 'n' || m_playAgain == 'N')
		{
			std::cout << "Thank you for playing my game! See you next time!\n";
			return false;
		}
		else
		{
			std::cout << "Wrong! You must type either 'Y'/'y' for yes or 'N'/'n' for now.\n";
		}
	}
}

void Game::theWinnerIs()
{
	printBoard();
	int black_disks = 0;
	int white_disks = 0;
	for (int i = 0; i < (ROWS * COLUMNS); i++)
	{
		if (m_board.at(i) == 'B')
		{
			black_disks++;
		}
		else if (m_board.at(i) == 'W')
		{
			white_disks++;
		}
	}
	std::cout << "Black had " << black_disks << "disks\n\n"
			  << "White had " << white_disks << "disks\n\n\n";
	if (black_disks > white_disks)
	{
		std::cout << "Congratulations player with black disks!\n\n";
	}
	else if (white_disks > black_disks)
	{
		std::cout << "Congratulations player with white disks!\n\n";
	}
	else
	{
		std::cout << "It looks like we have a draw\n\n";
	}
}
