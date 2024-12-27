#ifndef ABILITIESMANAGER_H 
#define ABILITIESMANAGER_H 

#include <memory> 
#include <queue> 
#include <random> 
#include <algorithm> 
#include "Abilities.h" 
#include "Field.h" 

class AbilitiesManager { 
private: 
    std::queue<std::unique_ptr<Abilities>> queue_abilities; // Очередь указателей на класс 
    std::default_random_engine generator; // Генератор случайных чисел 

public: 
    AbilitiesManager(); 

    // Использование способности 
    void ApplicationOfAbilities(Field& field, ShipManager& manager, size_t x, size_t y); 

    // Добавление случайной способности при уничтожении вражеского корабля 
    void AddRandomAbility();
 
}; 

#endif // ABILITIESMANAGER_H
