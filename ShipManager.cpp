#include "ShipManager.h"
#include <exception>
#include <iostream>

ShipManager::ShipManager(const std::vector<unsigned int>& sizes){
    for (const auto& size : sizes) {
        Ship s(size);
        ships.emplace_back(s);
    }
}

Ship& ShipManager::operator[](unsigned int index) {
    if (index >= ships.size()) {
        throw std::exception();
    }
    return ships[index];
}

int ShipManager::number_of_ships() {
    return ships.size();
}
int ShipManager::number_of_ships_state(ShipState state){
    int count = 0;
    for (Ship& s: ships) {
        if (s.state() == state){
            count++;
        }
    }
    return count;
}
bool ShipManager::AllDestroyed() const
{
	for (const Ship& sh : ships) {
		if (sh.state() != ShipState::destroyed)
			return false;
	}
	return true;
}
void ShipManager::show(){
    std::cout<<"ShipList"<<std::endl;
    for(const Ship& s: ships){
        s.show();
        std::cout<<std::endl;
    }
}
void ShipManager::Save(std::ostream& str)
{
	str << ships.size()<<std::endl;
	for (auto& shp : ships)
		shp.Save(str);
}

void ShipManager::Load(std::istream& str)
{
	size_t sz;
	str >> sz;
	ships.resize(sz,{1});
	for (auto& shp : ships)
		shp.Load(str);
}

