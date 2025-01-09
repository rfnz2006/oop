#ifndef CELL_H
#define CELL_H

#include "Ship.h"

enum CellState {unknown, empty, occupied};

class Cell {
private:
	int value = -1;//-1 - пустая -2 - рядом с корблем
	CellState state = CellState::unknown;
public:
	int get_value() const;
    void set_value(int new_value);
    void set_state(CellState new_state);
	CellState get_state() const;
	ShipState EnemyShip;
};

#endif // CELL_H