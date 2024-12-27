#include "Field.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>

Field::Field()
{
}

Field::Field(size_t width, size_t height)
{	
	cells_grid.resize(height);
	for (std::vector< Cell >& row : cells_grid){
		row.resize(width);
		}
}
Field::Field(const Field& other)
{
	cells_grid = other.cells_grid;
}
Field::Field(Field&& other)
{
	cells_grid = std::move(other.cells_grid);
}
Field& Field::operator=(const Field& other)
{
	cells_grid = other.cells_grid;
	return 	*this;
}
Field& Field::operator=(Field&& other)
{
	cells_grid = std::move(other.cells_grid);
	return 	*this;
}
Field::~Field()
{
}

bool Field::place_ship(ShipManager& ship_man, size_t ship_index, size_t x0, size_t y0, ShipOrientation ori) 
{ 
	Ship& ship = ship_man[ship_index]; 
	size_t len = ship.get_length(); 
	size_t h = cells_grid.size(); 
	if (h == 0) 
		throw OutOfBoundaries();
	size_t w = cells_grid[0].size(); 
	if (w == 0) 
		throw OutOfBoundaries();
	if (y0 >= h || x0 >= w) 
		throw OutOfBoundaries();

	if (ori == ShipOrientation::horizontal) { 
		if (x0 + len - 1 >= w) 
			return false; 		
		if (!can_place_ship(static_cast<int>(x0) - 1, static_cast<int>(y0) - 1, static_cast<int>(x0 + len), static_cast<int>(y0) + 1)) 
			return false; 		
		mark(static_cast<int>(ship_index), static_cast<int>(x0), static_cast<int>(y0), static_cast<int>(x0 + len - 1), ShipOrientation::horizontal); 
		mark(-2, static_cast<int>(x0), static_cast<int>(y0) - 1, static_cast<int>(x0 + len - 1), ShipOrientation::horizontal); 
		mark(-2, static_cast<int>(x0), static_cast<int>(y0) + 1, static_cast<int>(x0 + len - 1), ShipOrientation::horizontal); 
		mark(-2, static_cast<int>(x0) - 1, static_cast<int>(y0) - 1, static_cast<int>(y0) + 1, ShipOrientation::vertical); 
		mark(-2, static_cast<int>(x0) + len, static_cast<int>(y0) - 1, static_cast<int>(y0) + 1, ShipOrientation::vertical); 
	} 
	else { 
		if (y0 + len - 1 >= h) 
			return false; 
		if (!can_place_ship(static_cast<int>(x0) - 1, static_cast<int>(y0) - 1, static_cast<int>(x0) + 1, static_cast<int>(y0 + len))) 
			return false; 
		mark(static_cast<int>(ship_index), static_cast<int>(x0), static_cast<int>(y0), static_cast<int>(y0 + len - 1), ShipOrientation::vertical); 
		mark(-2, static_cast<int>(x0) - 1, static_cast<int>(y0), static_cast<int>(y0 + len - 1), ShipOrientation::vertical); 
		mark(-2, static_cast<int>(x0) + 1, static_cast<int>(y0), static_cast<int>(y0 + len - 1), ShipOrientation::vertical); 
		mark(-2, static_cast<int>(x0) - 1, static_cast<int>(y0) - 1, static_cast<int>(x0) + 1, ShipOrientation::horizontal);
		mark(-2, static_cast<int>(x0) - 1, static_cast<int>(y0 + len), static_cast<int>(x0) + 1, ShipOrientation::horizontal); 
	} 

	ship.set_orientation(ori); 
	return true; 
}

bool Field::can_place_ship(int x0, int y0, int x1, int y1) 
{ 
    size_t h = cells_grid.size(); 
    if (h == 0) 
        throw IllegalShipPlacement(); 

    size_t w = cells_grid[0].size(); 
    if (w == 0) 
        throw IllegalShipPlacement(); 

    if (y1 >= (int)h || x1 >= (int)w || y0 < 0 || x0 < 0)  
        throw IllegalShipPlacement();  

    for (int x = x0; x <= x1; ++x) { 
        for (int y = y0; y <= y1; ++y) { 
            if (cells_grid[y][x].get_value() != -1) 
                throw IllegalShipPlacement(); 
        } 
    } 

    return true; 
}


void Field::mark(int value, int x0, int y0, int x1_or_y1, ShipOrientation orientation) 
{ 
	size_t h = cells_grid.size(); 
	if (h == 0) 
		return; 
	size_t w = cells_grid[0].size(); 
	if (x0 >= (int)w || x0 < 0 || y0 < 0 || y0 >= (int)h ) 
		return;
	if (orientation == ShipOrientation::horizontal) { 
		if (x1_or_y1 >= (int)w) 
			return; 
	for (int x = x0; x <= x1_or_y1; ++x) 
		cells_grid[y0][x].set_value(value); 
	} else if (orientation == ShipOrientation::vertical) {
		if (x1_or_y1 >= (int)h) 
			return; 
		for (int y = y0; y <= x1_or_y1; ++y) 
			cells_grid[y][x0].set_value(value); 
	}
}

CellState Field::attack(size_t x, size_t y) { 
	
	size_t h = cells_grid.size(); 
	if (h == 0 || cells_grid[0].size() == 0) 
		throw std::exception(); 

	size_t w = cells_grid[0].size(); 
	if (x >= w || y >= h) 
		throw std::exception();

	int ship_index = cells_grid[y][x].get_value(); 
	if (ship_index < 0) 
		return CellState::empty; 
	ShipManager manager = get_ship_manager();
	Ship& ship = manager[ship_index]; 
	size_t n = 0; 

	if (ship.get_orientation() == ShipOrientation::horizontal) { 
		while (n + x < w && cells_grid[y][x + n].get_value() == ship_index) 
			n++; 
	} else { 
	while (n + y < h && cells_grid[y + n][x].get_value() == ship_index) 
	n++; 
	} 

	ship.hit(ship.get_length() - 1 - n);
	ship.state();
	return CellState::occupied;
}

size_t Field::get_width(){
	return cells_grid[0].size();
}

size_t Field::get_height(){
	return cells_grid.size();
}
 
void Field::PrintField() { 
    std::cout << "\n- The playing field -" << std::endl; 
    for (int y = 0; y < cells_grid.size(); y++) { 
        for (int x = 0; x < cells_grid[0].size(); x++) { 
              
            // Проверка статуса клетки на Unknown 
            if (cells_grid[y][x].get_value() <= -1) { 
                std::cout << "~  "; 
            } 
            else if (cells_grid[y][x].get_state() == CellState::occupied) { // Проверка состояния на occupied
                std::cout << "X  "; // Выводим 'X' для занятых клеток
            } 
            else if (cells_grid[y][x].get_value() >= 0) { 
                std::cout << cells_grid[y][x].get_value() << "  "; 
            } 
        } 
        std::cout << std::endl; 
    } 
}

void Field::set_ship_manager(ShipManager new_ship_man){
	ship_man = ship_man;
}

ShipManager Field::get_ship_manager(){
	return ship_man;
}

void Field::SetEnemyState(size_t x, size_t y, CellState cell_state, ShipState ship_state)
{
	auto w = get_width();
	auto h = get_height();
	if (x >= w || y >= h)
		throw std::exception();
	cells_grid[y][x].set_state(cell_state);
	cells_grid[y][x].EnemyShip = ship_state;
}

static const char ship_names[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void Field::Display(std::ostream& os)
{
	auto w = get_width();
	auto h = get_height();
	for (size_t y = 0; y < h; y++) {
		os <<std::setw(3)<< y<<":  ";
		for (size_t x = 0; x < w; x++) {
			int j = cells_grid[y][x].get_value();
			if (j < 0) {
				os << ". ";
				continue;
			}
			const Ship& ship = get_ship_manager()[j];
			char c = (unsigned) j >= sizeof(ship_names) ? '%' : j >= 0 ? ship_names[j] : '*';
			os << c;
			unsigned count = 0;
			if (ship.get_orientation() == ShipOrientation::horizontal) {
				while (count+1 <= x && cells_grid[y][x - count-1].get_value() == j) {
					count++;
				}
			}
			else {
				while (count + 1 <= y && cells_grid[y - count - 1][x].get_value() == j) {
					count++;
				}
			}
			ShipState state = ship.state();
			if (state==ShipState::intact)
				os << '+';
			else if (state == ShipState::damaged)
				os << '-';
			else 
				os << 'X';
		}

		os << "   ";
		os << std::setw(3) << y << ":  ";
		for (size_t x = 0; x < w; x++) {
			os << ' ';
			auto cs= cells_grid[y][x].get_state();
			int index = cells_grid[x][y].get_value();
    		ShipState ss = get_ship_manager()[index].state();
			if(cs==CellState::occupied){
				 if (ss == ShipState::intact)
					 os << '+';
				 else if (ss == ShipState::damaged)
					 os << '-';
				 else
					 os << 'X';
			 }
			 else if (cs == CellState::unknown) 
					 os << '?';
			 else
				 os << '.';
		}

		os << std::endl;
	}
	os << std::setw(5) << " ";
	for (int i = 0; i <w; i++)
		os << std::setw(2) << i % 10;
	os << std::setw(10) << " ";
	for (int i = 0; i < w; i++)
		os << std::setw(2) << i % 10;
	os << std::endl;
}

std::ostream& operator<<(std::ostream& os, Field& field)
{
	field.Display(os);
	return os;
}