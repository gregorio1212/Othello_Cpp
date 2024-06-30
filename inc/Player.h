#pragma once
/**
 @file Player.h
 @author Gregório da Luz
 @date February 2021
 @brief header for Player class for Othello game
 **/
#include <iostream>
#include <assert.h> 

class Player
{
private:
	int m_n_disks_available;
	int m_color;				//WHITE == 1 BLACK == 2
public:
	Player(int color) : m_color{color}, m_n_disks_available { 28 } {}
	int getDisksAvailable() const { return m_n_disks_available; }
	void oneLessDisk();
	void giveMeOneDisk(Player& giving);
	void resetDisks() { m_n_disks_available = 28; }
	int getColor() const { return m_color; }
};

// I could set X in the places the player can set their next move