#pragma once
#include "Field.h"
#include "ShipManager.h"
#include "Ship.h"
#include "AbilitiesManager.h"

struct GameState {
    int UserScore;
    int EnemyScore;
    int RoundNumber;
    bool EnemyTurn;
};


class Game {
private:
    size_t BoardWidth = 10;
    size_t BoardHeight = 10;
    Field   PlayerBoard;
    Field   EnemyBoard;
    GameState State;
    AbilitiesManager Abilities;
    bool isGameOver;

private:
    Field GenerateRandomBoard(ShipManager ship_man);
    void InitializePlayerBoard();
    void InitializeEnemyBoard();
    void InitializeAbilities(Field a_enemy, ShipManager b_enemy, size_t x, size_t y);
    bool UserTurn(size_t x, size_t y, bool use_ability);
    bool EnemyTurn();
    
    
public:
    Game();
    ~Game();
    void InitializeGame();
    bool Round();
    void SaveGame();
    void LoadGame();

public:  
    const Field& GetEnemyBoard()const { return EnemyBoard; }

};