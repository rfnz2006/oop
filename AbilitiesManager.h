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
    void saveToStream(std::ostream& os) const {
        // Сохраняем количество способностей в очереди
        size_t size = queue_abilities.size();
        os << size << std::endl;

        // Сохраняем каждую способность
        auto temp_queue = queue_abilities; // Создаем временную очередь для обхода
        while (!temp_queue.empty()) {
            // Предполагается, что у класса Abilities есть метод для сохранения
            temp_queue.front()->saveToStream(os); // Сохраняем способность
            temp_queue.pop();
        }
    }

    // Загрузка состояния из потока
    void loadFromStream(std::istream& is) {
        // Очищаем текущую очередь
        while (!queue_abilities.empty()) {
            queue_abilities.pop();
        }

        // Загружаем количество способностей
        size_t size;
        if (!(is >> size)) {
            throw std::runtime_error("Failed to read number of abilities.");
        }
        is.ignore(); // Игнорируем символ новой строки после числа

        // Загружаем каждую способность
        for (size_t i = 0; i < size; ++i) {
            auto ability = std::make_unique<Abilities>(); // Создаем новую способность
            ability->loadFromStream(is); // Предполагается, что у класса Abilities есть метод для загрузки
            queue_abilities.push(std::move(ability)); // Добавляем в очередь
        }
    }
}; 

#endif // ABILITIESMANAGER_H
