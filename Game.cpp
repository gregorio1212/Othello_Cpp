#include "Game.h"

Game::Game() : m_disk_counter{}, m_board{}, m_whose_turn{}, m_end{ false }, m_correctInput{ false },
m_playAgain{}, m_opponent{}, m_machine_check{}, m_move_available{}, m_if_two_end{0},
m_x_path{}, m_y_path{}, m_if_flip_equals_10{ 0 }, m_temp{0}{
	InitGame();
}

void Game::InitGame() {
	//all the necessary setting up/cleaning up of variables for a new game
	m_disk_counter = 4;
	m_whose_turn = 'B';
	m_opponent = 'W';
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i == 3 && j == 3) || (i == 4 && j == 4)) { m_board[i][j] = 'B'; }
			else if ((i == 3 && j == 4) || (i == 4 && j == 3)) { m_board[i][j] = 'W'; }
			else { m_board[i][j] = '-'; }
		}
	}
}

void Game::Info() const{
	cout << "Player ";
	if (m_whose_turn == 'B') { cout << "Black, it's your turn!\n"; }
	else { cout << "White, it's your turn!\n"; }
}

void Game::printBoard() const{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 0) { cout << "    0 1 2 3 4 5 6 7 \n"; }
			if (j == 0) { cout << i <<" | " << m_board[i][j]; }
			else if (j == 7) { cout << ' ' << m_board[i][j] << " |" << '\n'; }
			else { cout << ' ' << m_board[i][j]; }
		}
	}
}

bool Game::freeSlot(int x, int y)const{		//WHITE == 1 BLACK == 2
	if (m_board[x][y] == '-') { return true; }
	else {
		cout << "Pick a slot\n";
		return false;
	}
}

bool Game::goodInput(int x_value, int y_value) const{
	if (x_value <= 7 && x_value >= 0 && y_value <= 7 && y_value >= 0) { return true; }
	return false;
}

bool Game::allowedTurn() {
	m_machine_check = true; // this will control the flipAllDirections() so that it won't actually flip the disks
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {//it checks just until it finds one move that is available
			m_move_available = allowedSlot(x, y);
			if (m_move_available) {
				m_machine_check = false;
				return true;
			}
		}
	}
	m_machine_check = false;
	return false;
}

void Game::flipWhoseTurnAndOpponent() {
	if (m_whose_turn == 'B') {
		m_whose_turn = 'W';
		m_opponent = 'B';
	}
	else {
		m_whose_turn = 'B';
		m_opponent = 'W';
	}
}

bool Game::noPossibleMove() {
	while (!allowedTurn()) {
		m_if_two_end++;
		//a player loses his turn because he had no possible move, but the other player has, so we keep playing
		if (m_if_two_end == 1) { flipWhoseTurnAndOpponent(); }
		//end of game, no player can set a disk
		if (m_if_two_end == 2) {
			m_if_two_end = 0;
			return true;
		}
	}
	m_if_two_end = 0;
	return false;
}

void Game::allowedSlotLoop(int x_, int y_, int i_c, int j_c, int lim_i, int lim_j) {
	for (int i = i_c; i < lim_i; i++) {
		for (int j = j_c; j < lim_j; j++) {
			if (m_board[x_ + i][y_ + j] == m_opponent) {
				// once an opponent's disk is found in the surroundings, we check if it is "flippable"
				m_temp = flipAllDirections(x_, y_, i, j);
				//once one flip has occurred, other slots that have no flip won't change this variable
				if (m_temp == 10 && m_if_flip_equals_10 == 0) { m_if_flip_equals_10 = m_temp; }
			}
		}
	}
}

bool Game::allowedSlot(int x, int y) {
	// variable that will control if some flipping on the disks occur	
	m_temp = 0;
	m_if_flip_equals_10 = 0; 
	// the ifs serves to separate parts of the board that have an equal type of surroundings check
	if (y > 1 && y < 6) {
		//The coulors refer to regions of the board, a schematics is present on the gitHub repository
		if (x < 2) { allowedSlotLoop(x, y, 0, -1, 2, 2); }					//red and blue upper check 
		else if (x > 5) { allowedSlotLoop(x, y, -1, -1, 1, 2); }			//red and blue down check
		else { allowedSlotLoop(x, y, -1, -1, 2, 2); }						// yellow total check
	}
	else if (x > 1 && x < 6) {
		if (y < 2) { allowedSlotLoop(x, y, -1, 0, 2, 2); }					//check violet and rainbow(most left)
		else if (y > 5) { allowedSlotLoop(x, y, -1, -1, 2, 1); }			//check verde and moon(most right)
	}
	else if (x == 0 || x == 1) {
		if (y == 0 || y == 1) { allowedSlotLoop(x, y, 0, 0, 2, 2); }		//check upper left square
		else { allowedSlotLoop(x, y, 0, -1, 2, 1); }						//check upper right square
	}
	else if (x == 6 || x == 7) {
		if (y == 0 || y == 1) { allowedSlotLoop(x, y, -1, 0, 1, 2); }		//check lower left square
		else { allowedSlotLoop(x, y, -1, -1, 1, 1); }						//check lower right square
	}
	//end of possible checks
	if (m_if_flip_equals_10 == 10) {
		return true;
	}
	if (!m_machine_check) {
		cout << "This slot is not allowed, pick another one\n\n";
	}
	return false;
}

// this function checks and, if allowed, flips disks 
int Game::flipAllDirections(int x, int y, int i_c, int j_c) {
	m_x_path = i_c;
	m_y_path = j_c;
	//HORIZONTAL AND VERTICAL
	if (m_x_path == 0) {//horizontal flip
		if (m_y_path == -1) {//left flip
			//this while is present in all checks, it keeps increasing values to check if there are still opponents' disks
			while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (y + m_y_path) > 0) { m_y_path--; }
			if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				m_y_path++;
				while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
					if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
					m_y_path++;
					m_if_flip_equals_10 = 10;
				}
			}
		}
		else if (m_y_path == 1) {//right flip
			while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (y + m_y_path) < 7) { m_y_path++; }
			if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				m_y_path--;
				while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
					if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
					m_y_path--;
					m_if_flip_equals_10 = 10;
				}
			}
		}
	}
	else if (m_y_path == 0) {//vertical flip
		if (m_x_path == -1) {//upper
			while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (x + m_x_path) > 0) { m_x_path--; }
			if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				m_x_path++;
				while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
					if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
					m_x_path++;
					m_if_flip_equals_10 = 10;
				}
			}
		}
		else if (m_x_path == 1) {//down
			while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (x + m_x_path) < 7) { m_x_path++; }
			if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				m_x_path--;
				while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
					if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
					m_x_path--;
					m_if_flip_equals_10 = 10;
				}
			}
		}
	}
	//DIAGONALS
	else if (m_x_path != 0 && m_y_path != 0) {
		if (m_x_path == -1) {//upper diagonals
			if (m_y_path == -1) {//left
				while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (x + m_x_path) > 0 && (y + m_y_path) > 0) {
					m_x_path--;
					m_y_path--;
				}
				if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks 
					m_x_path++;
					m_y_path++;
					while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
						if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
						m_y_path++;
						m_x_path++;
						m_if_flip_equals_10 = 10;
					}
				}		
			}
			else {//right
				while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (x + m_x_path) > 0 && (y + m_y_path) < 7) {
					m_x_path--;
					m_y_path++;
				}
				if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
					m_x_path++;
					m_y_path--;
					while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
						if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
						m_y_path--;
						m_x_path++;
						m_if_flip_equals_10 = 10;
					}
				}
			}
		}
		else {//lower diagonals
			if (m_y_path == -1) {//left
				while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (x + m_x_path) < 7 && (y + m_y_path) > 0) {
					m_x_path++;
					m_y_path--;
				}
				if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
					m_x_path--;
					m_y_path++;
					while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
						if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
						m_y_path++;
						m_x_path--;
						m_if_flip_equals_10 = 10;
					}
				}
			}
			else {//right
				while (m_board[x + m_x_path][y + m_y_path] == m_opponent && (x + m_x_path) < 7 && (y + m_y_path) > 0) {
					m_x_path++;
					m_y_path++;
				}
				if (m_board[x + m_x_path][y + m_y_path] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
					m_x_path--;
					m_y_path--;
					while (m_board[x + m_x_path][y + m_y_path] != '-' && m_board[x + m_x_path][y + m_y_path] != m_whose_turn) {
						if (!m_machine_check) { m_board[x + m_x_path][y + m_y_path] = m_whose_turn; }
						m_y_path--;
						m_x_path--;
						m_if_flip_equals_10 = 10;
					}
				}
			}
		}
	}
	return m_if_flip_equals_10;
}

void Game::settingNewDisk(int x, int y) {
	m_board[x][y] = m_whose_turn;
	m_disk_counter++;
}

void Game::playAgain() {
	while (!m_correctInput) {
		cout << "Would you like to play it again? (type y - yes or n - no)\n";
		cin >> m_playAgain;
		if (m_playAgain == 'y' || m_playAgain == 'Y') {
			cout << "Nice! Let's play again!\n";
			m_end = false;
			m_correctInput = true;
		}
		else if (m_playAgain == 'n' || m_playAgain == 'N') {
			cout << "Thank you for playing my game! See you next time!\n";
			m_correctInput = true;
		}
		else { cout << "Wrong! You must type either 'Y'/'y' for yes or 'N'/'n' for now.\n"; }
	}
	if (!m_end) { InitGame(); }
}

void Game::theWinnerIs() {
	printBoard();
	int black_disks = 0;
	int white_disks = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (m_board[x][y] == 'B') { black_disks++; }
			else if (m_board[x][y] == 'W') { white_disks++; }
		}
	}
	cout << "Black had " << black_disks << "disks\n\n"
		 << "White had " << white_disks << "disks\n\n\n";
	if (black_disks > white_disks) { cout << "Congratulations player with black disks!\n\n"; }
	else if (white_disks > black_disks) { cout << "Congratulations player with white disks!\n\n"; }
	else { cout << "It looks like we have a draw\n\n"; }
	playAgain();
}
