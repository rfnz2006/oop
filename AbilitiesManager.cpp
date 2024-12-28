#include "AbilitiesManager.h"
#include "Exceptions.h"
#include <random> // Необходим для random_device и default_random_engine
#include <vector> // Необходим для vector
#include <algorithm> // Необходим для shuffle

AbilitiesManager::AbilitiesManager() {
    // Инициализируем генератор
    std::random_device rd; // Создаем random_device
    generator = std::default_random_engine(rd()); // Инициализируем generator

    std::vector<std::unique_ptr<Abilities>> AbbilityList; 
    AbbilityList.push_back(std::make_unique<DoubleDamage>()); // добавляем способности в вектор
    AbbilityList.push_back(std::make_unique<Scanner>()); 
    AbbilityList.push_back(std::make_unique<Bombing>()); 

    // Перемещаем способности 
    std::shuffle(AbbilityList.begin(), AbbilityList.end(), generator); // перемешиваем способности, результат обределяется генератором
    // Добавляем способности в очередь 
    for (auto& ability : AbbilityList) { 
        queue_abilities.push(std::move(ability)); // перемещаем указатели способностей в очередь
    } 
}

// Использование способности 
void AbilitiesManager::ApplicationOfAbilities(Field& field, ShipManager& manager, size_t x, size_t y) { 
    if (queue_abilities.empty()) { 
        throw AbilityAbsence(); 
    } 

    std::unique_ptr<Abilities> temp_abil = std::move(queue_abilities.front()); // берем способность с края
    queue_abilities.pop(); // удаляем указатель на класс способности, которую закинули в temp_abil
    temp_abil->use_abilities(field, manager, x, y);// вызывается use_abilities для соответствующего класса
    
}  

// Добавление случайной способности при уничтожении вражеского корабля 
void AbilitiesManager::AddRandomAbility() { 
    std::vector<std::unique_ptr<Abilities>> new_ability; 
    new_ability.push_back(std::make_unique<DoubleDamage>()); 
    new_ability.push_back(std::make_unique<Scanner>()); 
    new_ability.push_back(std::make_unique<Bombing>()); 

    // Перемещаем способности 
    std::shuffle(new_ability.begin(), new_ability.end(), generator); 

    queue_abilities.push(std::move(new_ability.front())); 
}
