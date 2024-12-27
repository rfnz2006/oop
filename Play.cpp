#include "Play.h"
#include "Field.h"
#include "ShipManager.h"
#include "Ship.h"
#include "AbilitiesManager.h"
#include "Exceptions.h"
#include <iostream>
#include <random>

Game::Game()
{
   
}

Game::~Game()
{
}

void Game::InitializeGame()
{
    InitializeEnemyBoard();
    InitializePlayerBoard();
    //InitializeAbilities(Field a_enemy, ShipManager b_enemy, size_t x, size_t y);
}


Field Game::GenerateRandomBoard(ShipManager ship_man)
{
    Field b(10, 10);
    for (int i = 0; i < 10; i++) {
        bool newship;
        do {
            auto ori = std::rand() & 1 ? ShipOrientation::horizontal : ShipOrientation::vertical;
            auto s = ship_man[i].get_length();   //ship size
            unsigned x, y;
            if (ori == ShipOrientation::horizontal) {
                x = std::rand() % (BoardWidth - 1 - s);
                y = std::rand() % (BoardHeight - 1);
            }
            else {
                x = std::rand() % (BoardWidth - 1);
                y = std::rand() % (BoardHeight - 1 - s);
            }
            newship = false;
            try {
                newship = b.place_ship(ship_man, i, x, y, ori);
            }
            catch (...) {
            }
        } while (!newship);
    }
    return b;
}

void Game::InitializePlayerBoard()
{
    ShipManager sm({4,3,3,2,2,2,1,1,1,1});
    Field b(BoardWidth, BoardHeight);
    for (int i = 0; i < 10; i++) {
        bool newship;
        do {
         //   
            auto s = sm[i].get_length();   //ship size
            unsigned x, y;
            char o;
            std::cout << b<<std::endl<<s<<"-segment ship; enter X Y O(h or v): ";
            std::cin >> x >> y >> o;
            auto ori = o=='h' ? ShipOrientation::horizontal : ShipOrientation::vertical;
            newship = false;
            try {
                newship = b.place_ship(sm, i, x, y, ori);
            }
            catch (...) {
            }
        } while (!newship);
    }
    PlayerBoard = b;
}

void Game::InitializeEnemyBoard()
{
    ShipManager sm({4,3,3,2,2,2,1,1,1,1});
    EnemyBoard = GenerateRandomBoard(sm);
}

void Game::InitializeAbilities(Field a_enemy, ShipManager b_enemy, size_t x, size_t y)
{
    AbilitiesManager am;
	am.ApplicationOfAbilities(a_enemy, b_enemy, 2, 1);
	am.ApplicationOfAbilities(a_enemy, b_enemy, 2, 1);
	am.ApplicationOfAbilities(a_enemy, b_enemy, 2, 1);
}

bool Game::Round()
{
    for (;;) {
        std::cout << std::endl;
        std::cout << PlayerBoard;
        std::cin.clear();
        char cmd;
        std::cout << "Enter cmd (q,p,l,s): ";
        std::cin >> cmd;
        std::cout << std::endl;
        if (cmd == 'q')
            return false;
        if (cmd == 'l'){
            LoadGame();
            continue;
        }
        if (cmd == 's') {
            SaveGame();
            continue;
        }
        if (cmd != 'p') {
            continue;
        }
        std::cin.clear();
        int x = -1, y = -1;
        char ability='n';
        std::cout << "Enter x y ability(y or n): ";
        std::cin >> x >> y >> ability;
        std::cout << std::endl;
        if (x < 0 || y < 0)
            continue;
        UserTurn(x, y, ability == 'y'); 
        if (EnemyBoard.get_ship_manager().number_of_ships_state(destroyed) == EnemyBoard.get_ship_manager().number_of_ships()) {
            std::cout << EnemyBoard << std::endl;
            std::cout << "Round is over. You won!"<<std::endl;
            break;
        }
        EnemyTurn(); 
        if (PlayerBoard.get_ship_manager().number_of_ships_state(destroyed) == PlayerBoard.get_ship_manager().number_of_ships()) {
            std::cout << PlayerBoard << std::endl;
            std::cout << "Round is over. You were defeated!" << std::endl;
            break;
        }
    }

    return true;
}


bool Game::UserTurn(size_t x, size_t y, bool use_ability)
{
    if (State.EnemyTurn)
        throw std::exception();
    State.EnemyTurn = true;
    // сделать удар абилкой

    CellState cs = EnemyBoard.attack(x, y);
    int index =  EnemyBoard.cells_grid[x][y].get_value();
    ShipState ss =  EnemyBoard.get_ship_manager()[index].state();
    EnemyBoard.SetEnemyState(x, y, cs, ss);
    PlayerBoard.SetEnemyState(x, y, cs, ss);
    if (cs != CellState::occupied)
        return false;
    if (ss == ShipState::destroyed)
        Abilities.AddRandomAbility();
    return true;
}

bool Game::EnemyTurn()
{
    if (!State.EnemyTurn)
        throw std::exception();
    State.EnemyTurn = false;
    auto w = PlayerBoard.get_width();
    auto h = PlayerBoard.get_height();
    unsigned x = std::rand() % (w - 1);
    unsigned y = std::rand() % (h - 1);
    CellState cs = PlayerBoard.attack(x, y);
    int index = PlayerBoard.cells_grid[x][y].get_value();
    ShipState ss = PlayerBoard.get_ship_manager()[index].state();
    EnemyBoard.SetEnemyState(x, y, cs, ss);
    if (cs == CellState::occupied)
        return true;
    return false;
}

void Game::SaveGame()
{
}

void Game::LoadGame()
{
}