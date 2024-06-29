/**
 @file Player.cpp
 @author Gregório da Luz
 @date February 2021
 @brief Player class for Othello game
 **/
#include "Player.h"

void Player::oneLessDisk() {
	assert(m_n_disks_available>0);
	m_n_disks_available--;
	if (m_n_disks_available == 0) { cout << "You have no more disks" << endl; }
	else { cout << "You have still " << m_n_disks_available <<" disks available.\n" << endl; }
}

void Player::giveMeOneDisk(Player& player_giving) {
	m_n_disks_available++;
	player_giving.oneLessDisk();
}
