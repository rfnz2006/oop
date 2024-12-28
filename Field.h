#pragma once

#include "Ship.h"
#include "ShipManager.h"
#include "Cell.h"
#include <vector>
#include "Abilities.h"

class Field
{
	
private: 
	ShipManager ship_man;	
	bool can_place_ship(int x0, int y0, int x1, int y1);
	void mark(int value,int x0, int y0, int x1_or_y1, ShipOrientation ori);
	 

public: 
	std::vector< std::vector< Cell > > cells_grid;
	Field();
	Field(ShipManager ship_man, size_t width, size_t height);
	Field(const Field&);
	Field(Field&&);
	Field& operator=(const Field&);
	Field& operator=(Field&&);
	~Field();
	bool place_ship(ShipManager& ship_man, size_t ship_index, size_t x, size_t y, ShipOrientation ori);
	CellState attack(size_t x, size_t y);
	size_t get_width();
	size_t get_height();
	void PrintField();
	void set_ship_manager(ShipManager ship_man);
	ShipManager get_ship_manager();
	void SetEnemyState(size_t x, size_t y, CellState cell_state, ShipState ship_state);
	void Display(std::ostream& os);
	void saveToStream(std::ostream& os) const {
        // Сохраняем размеры поля
        os << cells_grid.size() << " " << cells_grid[0].size() << std::endl;

        // Сохраняем состояние каждой ячейки
        for (const auto& row : cells_grid) {
            for (const auto& cell : row) {
                os << static_cast<int>(cell.get_state()) << " "; 
            }
            os << std::endl;
        }

    }

    // Метод для загрузки состояния поля из потока
    void loadFromStream(std::istream& is) {
        // Загружаем размеры поля
        size_t width, height;
        if (!(is >> height >> width)) {
            throw std::runtime_error("Failed to read field dimensions.");
        }
        cells_grid.resize(height, std::vector<Cell>(width));

        // Загружаем состояние каждой ячейки
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                int state;
                cells_grid[i][j].set_state(static_cast<CellState>(state)); 
            }
        }

        ship_man.load(is);
    }
};
std::ostream& operator <<(std::ostream&, const Field&);