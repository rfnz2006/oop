#include "Cell.h"

int Cell::get_value() const{
    return value;
}
void Cell::set_value(int new_value){
    value = new_value;
}
void Cell::set_state(CellState new_state){
    state = new_state;
}

CellState Cell::get_state() const{
    return state;
}
