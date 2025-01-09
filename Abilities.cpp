#include "Abilities.h"
#include <iostream>


void DoubleDamage::UseAbilities(Field& field, size_t x, size_t y) {
    field.attack(x, y);
    field.attack(x, y);
}
   

void Scanner::UseAbilities(Field& field, size_t x, size_t y) {
    while(true){
        try{
            
            if (x <= 0 || y <= 0 || x > size_t(field.get_width()) || y > size_t(field.get_height())) {
                throw ScannerIsAppliedOutside();
            }

            for (size_t i = y - 1; i <= y; i++) {
                for (size_t j = x - 1; j <= x; j++) {
                    if (field.get_cell_value(x, y) >= 0) {
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
void Bombing::UseAbilities(Field& field, size_t x, size_t y)
{
	size_t flag = 0;
	size_t w = field.get_width();
    size_t h = field.get_height();
    if (field.get_ship_manager().number_of_ships_state(destroyed) != field.get_ship_manager().number_of_ships()){
	    while (flag == 0){
		    unsigned x = std::rand() % w;
		    unsigned y = std::rand() % h;
		    size_t indx = field.get_cell_value(x, y);
		    if (indx >= 0) {
			    Ship& ship = field.get_ship_manager()[indx];
			    unsigned n = std::rand() % ship.get_length();
			    ship.hit(n);
			    flag = 1;
			    return;
		    } 

	    }
    }

    throw AllTheShipsAreSunk();
}