#pragma once

#include "Ship.h"
#include "ShipManager.h"
#include "Cell.h"
#include <vector>

class Field
{
	
private: 
	ShipManager ship_man;	
	bool can_place_ship(int x0, int y0, int x1, int y1);
	void mark(int value, int x0, int y0, int x1_or_y1, ShipOrientation orientation);
    std::vector< std::vector< Cell > > cells_grid;
	 

public: 
	Field();
	Field(ShipManager ship_man, size_t width, size_t height);
	Field(const Field&);
	Field(Field&&);
	Field& operator=(const Field&);
	Field& operator=(Field&&);
	~Field();
    bool PlaceShip(size_t ship_index, size_t x, size_t y, ShipOrientation ori);
	CellState attack(size_t x, size_t y);
	size_t get_width();
	size_t get_height();
	void set_field_size(int width, int height) {
        width = width;
        height = height;
    }
	void PrintField() const;
	void set_ship_manager(ShipManager ship_man);
	ShipManager get_ship_manager();
    size_t get_cell_value(size_t x, size_t y);
    void SetEnemyState(size_t x, size_t y, CellState cell_state, ShipState ship_state);
	void Save(std::ostream& str);
	void Load(std::istream& str);
}; 