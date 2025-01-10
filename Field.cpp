#include "Field.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>

Field::Field()
{
}

Field::Field(ShipManager ship_man, size_t width, size_t height)
: ship_man(ship_man)
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

bool Field::PlaceShip(size_t ship_index, size_t x0, size_t y0, ShipOrientation ori) 
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
	size_t w = cells_grid[0].size(); 

	int ship_index = cells_grid[y][x].get_value(); 
	 std::cout << "attacking??" << std::endl;
	  std::cout << ship_index << std::endl;
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
	cells_grid[y][x].set_state(occupied);
	ship.state();
	return CellState::occupied;
}

size_t Field::get_width(){
	return cells_grid[0].size();
}

size_t Field::get_height(){
	return cells_grid.size();
}
 
void Field::PrintField() const{ 
    std::cout << "\n- The playing field --" << std::endl; 
    for (size_t y = 0; y < size_t(cells_grid.size()); y++) { 
        for (size_t x = 0; x < size_t(cells_grid[0].size()); x++) { 
              
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
	ship_man = new_ship_man;
}

ShipManager Field::get_ship_manager(){
	return ship_man;
}

size_t Field::get_cell_value(size_t x, size_t y){
	return cells_grid[x][y].get_value();
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

void Field::Save(std::ostream& str)
{
	auto w = get_width();
	auto h = get_height();
	str << w <<" "<< h<<std::endl;
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			str << cells_grid[y][x].get_value()<< " " << cells_grid[y][x].get_state() << " " << int(cells_grid[y][x].EnemyShip) << std::endl;
		}
	}
	ship_man.Save(str);
}

void Field::Load(std::istream& str)
{
	size_t w, h;
	str >> w >> h;
	set_field_size(w, h);
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			int value, state, enemishp;
			str >> value >> state >> enemishp;
			cells_grid[y][x].set_value(value);
			cells_grid[y][x].set_state(CellState(state));
			cells_grid[y][x].EnemyShip = ShipState(enemishp);
		}
	}
	ship_man.Load(str);
}

