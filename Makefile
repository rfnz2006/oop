# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall

# Цель по умолчанию
all: test_class

# Сборка программы py из объектных файлов
test_class: Ship.o main.o ShipManager.o Cell.o Field.o Abilities.o AbilitiesManager.o Exceptions.o Play.o Commander.o Displayer.o GameController.o
	$(CXX) $(CXXFLAGS) Ship.o main.o ShipManager.o Cell.o Field.o Abilities.o AbilitiesManager.o Exceptions.o Play.o Commander.o Displayer.o GameController.o -o test_class


# Компиляция Ship.cpp в Ship.o
Ship.o: Ship.cpp Ship.h
	$(CXX) $(CXXFLAGS) -c Ship.cpp -o Ship.o

main.o: main.cpp ShipManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Компиляция ShipManager.cpp в ShipManager.o
ShipManager.o: ShipManager.cpp ShipManager.h
	$(CXX) $(CXXFLAGS) -c ShipManager.cpp -o ShipManager.o

Cell.o: Cell.cpp Cell.h
	$(CXX) $(CXXFLAGS) -c Cell.cpp -o Cell.o

# Компиляция Field.cpp в Field.o
Field.o: Field.cpp Field.h
	$(CXX) $(CXXFLAGS) -c Field.cpp -o Field.o

Abilities.o: Abilities.cpp Abilities.h
	$(CXX) $(CXXFLAGS) -c Abilities.cpp -o Abilities.o

AbilitiesManager.o: AbilitiesManager.cpp AbilitiesManager.h
	$(CXX) $(CXXFLAGS) -c AbilitiesManager.cpp -o AbilitiesManager.o

# Компиляция Exceptions.cpp в Exceptions.o
Exceptions.o: Exceptions.cpp Exceptions.h
	$(CXX) $(CXXFLAGS) -c Exceptions.cpp -o Exceptions.o

# Компиляция Exceptions.cpp в Exceptions.o
Play.o: Play.cpp Play.h
	$(CXX) $(CXXFLAGS) -c Play.cpp -o Play.o

Commander.o: Commander.cpp Commander.h
	$(CXX) $(CXXFLAGS) -c Commander.cpp -o Commander.o

Displayer.o: Displayer.cpp Displayer.h
	$(CXX) $(CXXFLAGS) -c Displayer.cpp -o Displayer.o

GameController.o: GameController.cpp GameController.h
	$(CXX) $(CXXFLAGS) -c GameController.cpp -o GameController.o

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f *.o test_class.exe

# Указание, что цели 'all' и 'clean' являются псевдоцелями
.PHONY: all clean