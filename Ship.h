#pragma once

#include <vector>
#include <ostream>
#include <istream>

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
	ShipState state_seg(int index);
	ShipState state() const;
	int get_length(); 
	ShipOrientation get_orientation() const;
	void set_orientation(ShipOrientation) const;
	void show() const;
	void Save(std::ostream& str);
	void Load(std::istream& str);
};



