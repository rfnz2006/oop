#include "Ship.h"
#include <iostream>

Ship::Ship(unsigned int ship_length)
:orient{horizontal} 
{
    if (ship_length > 4 || ship_length < 1) {
        throw std::exception();
    }

    body.resize(ship_length, ShipState::intact);
}

bool Ship::hit(int ship_segment)  
{
    if (ship_segment >= body.size()) 
        return false; // Проверка на допустимый индекс

    // Обработка состояния корабля при атаке
    if (body[ship_segment] == ShipState::intact) 
    {
        body[ship_segment] = ShipState::damaged; // Изменение состояния на Damaged
    } 
    else if (body[ship_segment] == ShipState::damaged) 
    {
        body[ship_segment] = ShipState::destroyed; // Изменение состояния на Destroyed
    }

    return true; // Атака выполнена успешно
}

ShipState Ship::state() const  
{
    int destr_segment = 0;

    for (const auto& state : body) 
    {
        if (state == ShipState::destroyed) 
            destr_segment++;
    }

    // Определение общего состояния корабля
    if (destr_segment == body.size()) 
        return ShipState::destroyed; 
	
	else if (destr_segment != 0)
		return ShipState::damaged;
	
	else
		return ShipState::intact;
	 
}

int Ship::get_length() 
{ 
    return body.size(); 
}

ShipOrientation Ship::get_orientation() const 
{ 
    return orient; // Возвращаем ориентацию корабля
}

void Ship::set_orientation(ShipOrientation orient) const 
{ 
    orient = orient; 
}

void Ship::show() const{
    const char* name[] = {"horisontal", "vertical"};
    std::cout<<"orient="<<name[orient]<<std::endl;
    std::cout<<"Ship_size="<<body.size()<<std::endl;
}

void Ship::save(std::ostream& str){
    str<<body.size()<<std::endl;
    for(const auto& seg : body)
        str<<int(seg)<<" ";
    str<<int (orient)<<std::endl;
}

void Ship::load(std::istream& str){
    size_t size;
    str>>size;
    body.resize(size);
    int tmp;
    for(auto& seg : body){
        str >> tmp;
        seg=ShipState(tmp);
        }
    str>> tmp;
    auto orient = ShipOrientation(tmp);
}
