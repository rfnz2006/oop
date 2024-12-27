#ifndef ABILITIES_H 
#define ABILITIES_H 

#include "Field.h" 
#include "ShipManager.h" 
#include <random> 

// класс-родитель 
class Abilities { 
public: 
    // метод применения способности 
    virtual void use_abilities(Field& field, ShipManager& ship_manager, int x, int y) = 0; 
    // деструктор 
    virtual ~Abilities() = default; 
}; 

// классы-наследники 
class DoubleDamage: public Abilities { 
public: 
    // просто два раза бьем по клетке 
    virtual void use_abilities(Field& field, ShipManager& ship_manager, int x, int y) override; 
}; 

class Scanner: public Abilities { 
public: 
    // подаются координаты правого нижнего угла и исследуем  
    virtual void use_abilities(Field& field, ShipManager& ship_manager, int x, int y) override; 
}; 

class Bombing: public Abilities { 
public: 
    virtual void use_abilities(Field& field, ShipManager& ship_manager, int x = 0, int y = 0) override; 
}; 

#endif
