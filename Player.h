#include <iostream>
#include <assert.h> 

using namespace std;

class Player
{
private:
	int m_n_disks_available;
	int m_color;				//WHITE == 1 BLACK == 2
public:
	Player(int color) : m_color{color}, m_n_disks_available { 29 } {}
	int getDisksAvailable() const { return m_n_disks_available; }
	void oneLessDisk();
	void giveMeOneDisk(Player& giving);
	int getColor() const { return m_color; }
};
