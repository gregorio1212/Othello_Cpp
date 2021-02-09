#include "Game.h"

Game::Game() : m_disk_counter{}, m_board{}, m_whose_turn{}, m_end{}, m_correctInput{ false }, 
m_playAgain{}, m_opponent{}, m_machine_check{}, m_moves_available{}, m_if_two_end{0},
i_c_{}, j_c_{}, if_flip_equals_10{0}{
	InitGame();
}

void Game::InitGame() {
	//all the necessary setting up/ cleaning up of variables for a new game from zero
	m_disk_counter = 4;
	m_whose_turn = 'B';
	m_opponent = 'W';
	m_end = false;
	m_if_two_end = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i == 3 && j == 3) || (i == 4 && j == 4)) {
				m_board[i][j] = 'B';
			}
			else if ((i == 3 && j == 4) || (i == 4 && j == 3)) {
				m_board[i][j] = 'W';
			}
			else {
				m_board[i][j] = '0';
			}
		}
	}
}

void Game::Info() const{
	cout << "Player ";
	if (m_whose_turn == 'B') {
		cout << "Black, it's your turn!\n";
	}
	else {
		cout << "White, it's your turn!\n";
	}
}

void Game::printBoard() const{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 && j == 0) {
				cout << "    0 1 2 3 4 5 6 7 \n";
			}
			if (j == 0) {
				cout << i <<" | " << m_board[i][j];
			}
			else if (j == 7) {
				cout << ' ' << m_board[i][j] << " |" << '\n';
			}
			else {
				cout << ' ' << m_board[i][j];
			}
		}
	}
}

bool Game::freeSlot(int x, int y)const{		//WHITE == 1 BLACK == 2
	if (m_board[x][y] == '0') {
		return true;
	}
	else {
		cout << "Pick a slot\n";
		return false;
	}
}

bool Game::goodInput(int x_value, int y_value) const{
	if (x_value < 8 && x_value > -1 && y_value < 8 && y_value > -1) {
		return true;
	}
	return false;
}

bool Game::allowedTurn() {
	m_machine_check = true; // this will control the flipAllDirections() so that it won't actually flip the disks
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {//it checks just until it finds one move that is available
			m_moves_available = allowedSlot(x, y);
			if (m_moves_available) {
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
		if (m_if_two_end == 1) {//a player lost its turn because he had no possible move, but the other player has, so we keep playing
			flipWhoseTurnAndOpponent();
		}
		if (m_if_two_end == 2) {//end of game, no player can set a disk
			return true;
		}
	}
	m_if_two_end = 0;
	return false;
}

bool Game::allowedSlot(int x, int y) {
	// variable that will control if some flipping on the disks occur	
	int temp = 0;
	int if_flip_equals_10 = 0; 
	//checking surroundings
	if (y > 1 && y < 6) {
		if (x < 2) {//red and blue upper check
			for (int i_c = 0; i_c < 2; i_c++) {
				for (int j_c = -1; j_c < 2; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						// flip disks if disk from the player is found;
						// the temp works as a protection, once one flip occured, if_flip_equals_10 
						// should remain unchanged no matter what happens after the first flip
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
		else if (x > 5) {//red and blue down check
			for (int i_c = -1; i_c < 1; i_c++) {
				for (int j_c = -1; j_c < 2; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
		else {// yellow total check
			for (int i_c = -1; i_c < 2; i_c++) {
				for (int j_c = -1; j_c < 2; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
	}
	else if (x > 1 && x < 6) {
		if (y < 2) {//check violet and rainbow
			for (int i_c = -1; i_c < 2; i_c++) {
				for (int j_c = 0; j_c < 2; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
		else if (y > 5) {//check verde and moon
			for (int i_c = -1; i_c < 2; i_c++) {
				for (int j_c = -1; j_c < 1; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
	}
	else if (x == 0 || x == 1) {
		if (y == 0 || y == 1) {//check upper left square
			for (int i_c = 0; i_c < 2; i_c++) {
				for (int j_c = 0; j_c < 2; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
		else {//j=6 or j=7 perhaps not necessary //check upper right square
			for (int i_c = 0; i_c < 2; i_c++) {
				for (int j_c = -1; j_c < 1; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
	}
	else if (x == 6 || x == 7) {
		if (y == 0 || y == 1) {//check lower left square
			for (int i_c = -1; i_c < 1; i_c++) {
				for (int j_c = 0; j_c < 2; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
		else {//j==6 or j==7 perhaps not necessary //check lower right square
			for (int i_c = -1; i_c < 1; i_c++) {
				for (int j_c = -1; j_c < 1; j_c++) {
					if (m_board[x + i_c][y + j_c] == m_opponent) {
						//flip disks if disk from the player is found
						temp = flipAllDirections(x, y, i_c, j_c);
						if (temp == 10) {
							if_flip_equals_10 = temp;
						}
					}
				}
			}
		}
	}
	
	if (if_flip_equals_10 == 10) {
		return true;
	}

	cout << "This slot is not allowed, pick another one\n\n";
	return false;
}
// if an opponent's disk was found, this function checks and flips the disks between the placed disk and the one already on the board 
// if and only if there's a disk of the player that is playing in the specific diretion already placed on the board, of course.
int Game::flipAllDirections(int x, int y, int i_c, int j_c) {
	i_c_ = i_c;
	j_c_ = j_c;
	//HORIZONTAL AND VERTICAL
	if (i_c_ == 0) {//horizontal flip
		if (j_c_ == -1) {//left flip
			//this while is present in all checks, it keeps increasing values to check if there are still opponents' disks
			while (m_board[x + i_c_][y + j_c_] == m_opponent && (y + j_c_) != 0) {
				j_c_--;
			}
			if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				j_c_++;
				while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
					if (!m_machine_check) {
						m_board[x + i_c_][y + j_c_] = m_whose_turn;
					}
					j_c_++;
					if_flip_equals_10 = 10;
				}
			}
		}
		else if (j_c_ == 1) {//right flip
			while (m_board[x + i_c_][y + j_c_] == m_opponent && (y + j_c_) != 7) {
				j_c_++;
			}
			if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				j_c_--;
				while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
					if (!m_machine_check) {
						m_board[x + i_c_][y + j_c_] = m_whose_turn;
					}
					j_c_--;
					if_flip_equals_10 = 10;
				}
			}
		}
	}
	else if (j_c_ == 0) {//vertical flip
		if (i_c_ == -1) {//upper
			while (m_board[x + i_c_][y + j_c_] == m_opponent && (x + i_c_) != 0) {
				i_c_--;
			}
			if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				i_c_++;
				while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
					if (!m_machine_check) {
						m_board[x + i_c_][y + j_c_] = m_whose_turn;
					}
					i_c_++;
					if_flip_equals_10 = 10;
				}
			}
		}
		else if (i_c_ == 1) {//down
			while (m_board[x + i_c_][y + j_c_] == m_opponent && (x + i_c_) != 7) {
				i_c_++;
			}
			if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
				i_c_--;
				while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
					if (!m_machine_check) {
						m_board[x + i_c_][y + j_c_] = m_whose_turn;
					}
					i_c_--;
					if_flip_equals_10 = 10;
				}
			}
		}
	}
	//DIAGONALS
	else if (i_c_ != 0 && j_c_ != 0) {
		if (i_c_ == -1) {//upper diagonals
			if (j_c_ == -1) {//left
				while (m_board[x + i_c_][y + j_c_] == m_opponent && (x + i_c_) != 0 && (y + j_c_)!=0) {
					i_c_--;
					j_c_--;
				}
				if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks 
					i_c_++;
					j_c_++;
					while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
						if (!m_machine_check) {
							m_board[x + i_c_][y + j_c_] = m_whose_turn;
						}
						j_c_++;
						i_c_++;
						if_flip_equals_10 = 10;
					}
				}		
			}
			else {//right
				while (m_board[x + i_c_][y + j_c_] == m_opponent && (x + i_c_) != 0 && (y + j_c_) != 7) {
					i_c_--;
					j_c_++;
				}
				if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
					i_c_++;
					j_c_--;
					while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
						if (!m_machine_check) {
							m_board[x + i_c_][y + j_c_] = m_whose_turn;
						}
						j_c_--;
						i_c_++;
						if_flip_equals_10 = 10;
					}
				}
			}
		}
		else {//lower diagonals
			if (j_c_ == -1) {//left
				while (m_board[x + i_c_][y + j_c_] == m_opponent && (x + i_c_) != 7 && (y + j_c_) != 0) {
					i_c_++;
					j_c_--;
				}
				if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
					i_c_--;
					j_c_++;
					while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
						if (!m_machine_check) {
							m_board[x + i_c_][y + j_c_] = m_whose_turn;
						}
						j_c_++;
						i_c_--;
						if_flip_equals_10 = 10;
					}
				}
			}
			else {//right
				while (m_board[x + i_c_][y + j_c_] == m_opponent && (x + i_c_) != 7 && (y + j_c_) != 0) {
					i_c_++;
					j_c_++;
				}
				if (m_board[x + i_c_][y + j_c_] == m_whose_turn) {//if we found a disk from the player playing, flip the disks
					i_c_--;
					j_c_--;
					while (m_board[x + i_c_][y + j_c_] != '0' && m_board[x + i_c_][y + j_c_] != m_whose_turn) {
						if (!m_machine_check) {
							m_board[x + i_c_][y + j_c_] = m_whose_turn;
						}
						j_c_--;
						i_c_--;
						if_flip_equals_10 = 10;
					}
				}
			}
		}
	}
	return if_flip_equals_10;
}

void Game::theWinnerIs() {
	int black_disks = 0;
	int white_disks = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (m_board[x][y] == 'B') {
				black_disks++;
			}
			else if(m_board[x][y] == 'W') {
				white_disks++;
			}
		}
	}
	cout << "Black had " << black_disks << "disks\n\n"
		<< "White had " << white_disks << "\n\n\n";
	if (black_disks > white_disks) {
		cout << "Congratulations player with black disks!";
	}
	else if (white_disks > black_disks){
		cout << "Congratulations player with white disks!";
	}
	else {
		cout << "It looks like we have a draw";
	}
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
		else {
			cout << "Wrong! You must type either 'Y'/'y' for yes or 'N'/'n' for now.\n";
		}
	}
	if (!m_end) {
		InitGame();
	}
}

