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

class AbilityAbsence : public MyException
{
public:
	virtual const char* GetErrorText() override { return "No abilities!"; }
};

class IllegalShipPlacement : public MyException
{
public:
	virtual const char* GetErrorText() override { return "Cannot place a ship close to or at an intersection with another ship!"; }
};

class OutOfBoundaries : public MyException
{
public:
	virtual const char* GetErrorText() override { return "An attack beyond the boundaries of the field!"; }
};

class EmptyBoard : public MyException
{
public:
	virtual const char* GetErrorText() override { return "Null board height or width!"; }
};

class InvalidBombing : public MyException
{
public:
	virtual const char* GetErrorText() override { return "Cannot make bombing!"; }
};

class OutOfShipSize : public MyException
{
public:
	virtual const char* GetErrorText() override { return "Index out of ship size!"; }
};

class InternalError : public MyException
{
public:
	virtual const char* GetErrorText() override { return "Something went wrong!"; }
};