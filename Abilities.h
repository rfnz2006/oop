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
     // Метод сохранения состояния
    virtual void saveToStream(std::ostream& os) const = 0;

    // Метод загрузки состояния
    virtual void loadFromStream(std::istream& is) = 0;
    
    // деструктор 
    virtual ~Abilities() = default; 
}; 

class DoubleDamage : public Abilities {
public:
    // Просто два раза бьем по клетке
    virtual void use_abilities(Field& field, ShipManager& ship_manager, int x, int y) override;

    // Реализация сохранения состояния
    virtual void saveToStream(std::ostream& os) const override {
        os << "DoubleDamage" << std::endl; // Сохраняем тип способности
        // Сохраняем другие параметры способности, если есть
    }

    // Реализация загрузки состояния
    virtual void loadFromStream(std::istream& is) override {
        // Загружаем параметры способности, если есть
        std::string type;
        is >> type;
        if (type != "DoubleDamage") {
            throw std::runtime_error("Invalid ability type for DoubleDamage.");
        }
    }
};

class Scanner : public Abilities {
public:
    // Подаются координаты правого нижнего угла и исследуем
    virtual void use_abilities(Field& field, ShipManager& ship_manager, int x, int y) override;

    // Реализация сохранения состояния
    virtual void saveToStream(std::ostream& os) const override {
        os << "Scanner" << std::endl; // Сохраняем тип способности
        // Сохраняем другие параметры способности, если есть
    }

    // Реализация загрузки состояния
    virtual void loadFromStream(std::istream& is) override {
        // Загружаем параметры способности, если есть
        std::string type;
        is >> type;
        if (type != "Scanner") {
            throw std::runtime_error("Invalid ability type for Scanner.");
        }
    }
};

class Bombing : public Abilities {
public:
    virtual void use_abilities(Field& field, ShipManager& ship_manager, int x = 0, int y = 0) override;

    // Реализация сохранения состояния
    virtual void saveToStream(std::ostream& os) const override {
        os << "Bombing" << std::endl; // Сохраняем тип способности
        // Сохраняем другие параметры способности, если есть
    }

    // Реализация загрузки состояния
    virtual void loadFromStream(std::istream& is) override {
        // Загружаем параметры способности, если есть
        std::string type;
        is >> type;
        if (type != "Bombing") {
            throw std::runtime_error("Invalid ability type for Bombing.");
        }
    }
};

#endif
