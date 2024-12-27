#pragma once

#include <exception>

#include <exception> // Подключаем библиотеку для работы с исключениями

// Базовый класс для пользовательских исключений
class MyException : public std::exception 
{ 
public: 
    // Чисто виртуальная функция для получения текста ошибки
    virtual const char* GetErrorText() = 0; 

    // Деструктор по умолчанию
    ~MyException() {} 
}; 

// Исключение для случая отсутствия способностей
class AbilityAbsence : public MyException 
{ 
public: 
    virtual const char* GetErrorText() override { return "No abilities!"; } 
}; 

// Исключение для случая неправильного размещения корабля
class IllegalShipPlacement : public MyException 
{ 
public: 
    virtual const char* GetErrorText() override { return "Cannot place a ship close to or at an intersection with another ship!"; } 
}; 

// Исключение для случая атаки за пределами игрового поля
class OutOfBoundaries : public MyException 
{ 
public: 
    virtual const char* GetErrorText() override { return "An attack beyond the boundaries of the field!"; } 
};
class ScannerIsAppliedOutside : public MyException 
{ 
public: 
    virtual const char* GetErrorText() override { return "The scanner is applied outside the playing field!"; } 
};
class AllTheShipsAreSunk : public MyException 
{ 
public: 
    virtual const char* GetErrorText() override { return "All the ships are sunk!"; } 
};