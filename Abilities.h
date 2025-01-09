#ifndef ABILITIES_H
#define ABILITIES_H

#include "ShipManager.h"
#include "Exceptions.h"
#include "Field.h"
#include <random>

//класс-родитель
#include <iostream>

// Базовый класс
class Abilities {
public:
    // Метод применения способности
    virtual void UseAbilities(Field& field, size_t x, size_t y) = 0;
    // Деструктор
    virtual ~Abilities() = default;
};

// Класс-наследник DoubleDamage
class DoubleDamage : public Abilities {
public:
    // Просто два раза бьем по клетке
    void UseAbilities(Field& field, size_t x, size_t y) override;
};

// Класс-наследник Scanner
class Scanner : public Abilities {
public:
    // Подаются координаты правого нижнего угла и исследуем
    void UseAbilities(Field& field, size_t x, size_t y) override;
};
// Класс-наследник Bombing
class Bombing : public Abilities {
public:
    void UseAbilities(Field& field, size_t x, size_t y) override;
};

#endif
