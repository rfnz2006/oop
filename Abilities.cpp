#include "Abilities.h"
#include "Field.h"
#include "ShipManager.h"
#include "Exceptions.h"
#include <iostream>


void DoubleDamage::use_abilities(Field& field, ShipManager& ship_manager, int x, int y) {
    field.attack(x, y);
    field.attack(x, y);
}
   

void Scanner::use_abilities(Field& field, ShipManager& ship_manager, int x, int y) {
    while(true){
        try{
            
            if (x <= 0 || y <= 0 || x > field.get_width() || y > field.get_height()) {
                throw ScannerIsAppliedOutside();
            }

            for (int i = y - 1; i <= y; i++) {
                for (int j = x - 1; j <= x; j++) {
                    if (field.cells_grid[i][j].get_value() >= 0) {
                        std::cout << "Ship detected in area 2x2!" << std::endl;
                        return;
                    }
                }
            }
            std::cout << "No ship in area 2x2." << std::endl;
            break;
            }catch(const ScannerIsAppliedOutside& e){
                std::cout << e.what() << "Please enter the new correct x and y coordinates: ";
                std::cin >> x >> y;  
            }
        }
};
void Bombing::use_abilities(Field& field, ShipManager& ship_manager, int x, int y)
{
	int flag = 0;
	int w = field.get_width();
    int h = field.get_height();
    if (ship_manager.number_of_ships_state(destroyed) != ship_manager.number_of_ships()){
	    while (flag == 0){
		    unsigned x = std::rand() % w;
		    unsigned y = std::rand() % h;
		    int indx = field.cells_grid[y][x].get_value();
		    if (indx >= 0) {
			    Ship& ship = ship_manager[indx];
			    unsigned n = std::rand() % ship.get_length();
			    ship.hit(n);
			    flag = 1;
			    return;
		    }

	    }
    }

    throw AllTheShipsAreSunk();
}