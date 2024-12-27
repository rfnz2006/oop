#pragma once

#include "Ship.h"
#include <vector>


class ShipManager
{
private:
	std::vector<Ship> ships;
public:
	ShipManager(){}
	ShipManager(const std::vector<unsigned int>& sizes);
	Ship& operator[](unsigned int index);
	int number_of_ships();
	int number_of_ships_state(ShipState state);
	void show();
};