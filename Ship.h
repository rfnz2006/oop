#pragma once

#include <vector>

enum ShipState {
	intact, 
	damaged, 
	destroyed 
};
enum ShipOrientation { 
	horizontal, 
	vertical
};


class Ship
{
private:
	std::vector<ShipState> body;
	ShipOrientation orient;
	
public:
	Ship(unsigned int ship_length);
	bool hit(int ship_segment);
	ShipState state() const;
	int get_length(); 
	ShipOrientation get_orientation() const;
	void set_orientation(ShipOrientation) const;
	void show() const;
};



