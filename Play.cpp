#include "Play.h"
#include "Field.h"
#include "ShipManager.h"
#include "Ship.h"
#include "AbilitiesManager.h"
#include "Exceptions.h"
#include <random>
#include <fstream>
#include <sstream>
#include <ctime>


void GameState::Init()
{
    UserScore = EnemyScore = RoundNumber = 0;
    EnemyTurn = false;
}

void GameState::Save(std::ostream& str)
{
    str << UserScore << " " << EnemyScore << " " << RoundNumber << std::endl;
}

void GameState::Load(std::istream& str)
{
    str >> UserScore >> EnemyScore >> RoundNumber;
    EnemyTurn = false;
}

Game::Game()
{
   
}

Game::~Game()
{
}

void Game::InitializeGame(bool gen)
{
   std::cout << "initi...." << std::endl;
    InitializeEnemyBoard();
    InitializePlayerBoard(gen);
    //Abilities.InitForNewGame(BoardWidth,BoardHeight);
    State.Init();
}

Field& Game::GetPlayerBoard()
{
    return PlayerBoard;
}

size_t Game::GetAbilitiesSize() const
{
    return Abilities.Size();
}

const GameState& Game::GetGameState()
{
    return State;
}

std::string Game::GetAbilityMessage()
{
    return std::move(AbilityMessage);
}

bool Game::PlacePlayerShip(int indx, size_t x, size_t y, ShipOrientation ori)
{
    bool newship = false;
    try {
        newship = PlayerBoard.PlaceShip(indx, x, y, ori);
    }
    catch (...) {
    }

    return newship;
}

void Game::InitializeRound()
{
    InitializeEnemyBoard();
}
Field Game::GenerateRandomBoard()
{
    std::cout << "Generating RandomBoard" << std::endl;
    
    ShipManager ship_man({4,3,3,2,2,2,1,1,1,1});
    Field b(ship_man, 10, 10);
    
    srand(time(0)); // Seed the random number generator
    
    for (int i = 0; i < 10; i++) {
        std::cout << i << ": ";
        
        unsigned x, y;
        bool newship;
        int attempts = 0;
        const int maxAttempts = 100; // Limit number of attempts
        
        do {
            auto ori = (std::rand() % 2) ? ShipOrientation::horizontal : ShipOrientation::vertical;
            auto s = ship_man[i].get_length();
            
            if (ori == ShipOrientation::horizontal) {
                x = std::rand() % (BoardWidth - s);
                y = std::rand() % BoardHeight;
            } else {
                x = std::rand() % BoardWidth;
                y = std::rand() % (BoardHeight - s);
            }
            
            newship = false;
            
            try {
                newship = b.PlaceShip(i, x, y, ori);
                
                if (!newship && attempts < maxAttempts) {
                    throw std::runtime_error("Failed to place ship after multiple attempts");
                }
            } catch (const std::exception& e) {
                std::cerr << "Error placing ship " << i << ": " << e.what() << std::flush;
                
                // Log the position that caused the error
                std::cout << "Failed at (" << x << ", " << y << ") orientation: " 
                          << (ori == ShipOrientation::horizontal ? "H" : "V") << std::endl;
                
                attempts++;
            }
            
            if (!newship && attempts >= maxAttempts) {
                throw std::runtime_error("Max attempts reached while placing ship");
            }
            
            std::cout << "Random position: (" << x << ", " << y << ")" << std::endl;
        } while (!newship && attempts < maxAttempts);
        
        std::cout << "field generated" << std::endl;
        b.PrintField();
        return b;
    }
}
/*
    std::cout << "Generating RandomBoard" << std::endl;
    ShipManager ship_man({4,3,3,2,2,2,1,1,1,1});
    Field b(ship_man, 10, 10);
    for (int i = 0; i < 10; i++) {
        std::cout << i << std::endl;
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
                newship = b.PlaceShip(i, x, y, ori);
            }
            catch (...) {
            }
        } while (!newship);
    }
          std::cout << "field generated" << std::endl;
    b.PrintField();
    return b;*/




void Game::InitializePlayerBoard(bool gen)
{
    if (gen) {
        PlayerBoard = GenerateRandomBoard();
        return;
    }
    ShipManager sm({ 4,3,3,2,2,2,1,1,1,1 });
    PlayerBoard = Field(sm, BoardWidth, BoardHeight);
    //PlayerBoard.PrintField();
}

void Game::InitializeEnemyBoard()
{  std::cout << "initializing enemy" << std::endl;
    EnemyBoard = GenerateRandomBoard();
}


RoundResult Game::Turn(size_t x, size_t y, bool ab)
{

    std::cout << "turning" << std::endl;
    State.RoundNumber += 1;
    UserTurn(x, y, ab); 
    if (EnemyBoard.get_ship_manager().AllDestroyed()) {
        return RoundResult::RoundOver;
    }
    EnemyTurn();
    if (PlayerBoard.get_ship_manager().AllDestroyed()) {
        return RoundResult::GameOver;
    }
    return RoundResult::Continue;
}


bool Game::UserTurn(size_t x, size_t y, bool use_ability)
{
    // check state
    if (State.EnemyTurn)
        throw InternalError();
    State.EnemyTurn = true;
    // use ability
    if (use_ability) {
        Abilities.ApplicationOfAbilities(EnemyBoard, x, y);
            AbilityMessage+=": scanner found ship";
    }

    //perform attack
        std::cout << "attacking??" << std::endl;
        std::cout << x << std::endl;
        std::cout << y << std::endl;
    auto cs = EnemyBoard.attack(x, y);
    int index =  EnemyBoard.get_cell_value(x, y);
    ShipState ss =  EnemyBoard.get_ship_manager()[index].state();
    PlayerBoard.SetEnemyState(x, y, cs, ss);
    //return result
    if (cs != CellState::occupied)
        return false;
    State.UserScore += 1;
    if (ss == ShipState::destroyed) {
        //auto w = PlayerBoard.get_width();
        //auto h = PlayerBoard.get_height();
        Abilities.AddRandomAbility();
    }
    return true;
}

void Game::SetNextAttackDouble()
{
}

bool Game::Scan2x2(size_t x, size_t y)
{
    return true;
}

void Game::MakeBombing()
{
}

bool Game::EnemyTurn()
{
    // check state
    if (!State.EnemyTurn)
        throw InternalError();
    State.EnemyTurn = false;
    auto w = PlayerBoard.get_width();
    auto h = PlayerBoard.get_height();
    //generate random x and y for attack
    unsigned x = std::rand() % (w - 1);
    unsigned y = std::rand() % (h - 1);
    //perform attack
    auto cs = PlayerBoard.attack(x, y);
    int index = PlayerBoard.get_cell_value(x,y);
    ShipState ss = PlayerBoard.get_ship_manager()[index].state();
    EnemyBoard.SetEnemyState(x, y, cs, ss);
    //return result
    if (cs != CellState::occupied)
        return false;
    State.EnemyScore += 1;
    return true;
}

void Game::SaveGame()
{
    std::ofstream of("saved_game", std::ios_base::trunc);
    of << BoardWidth << " " << BoardHeight<<std::endl;
    PlayerBoard.Save(of);
    EnemyBoard.Save(of);
    State.Save(of);
}

void Game::LoadGame()
{
    std::ifstream f("saved_game");
    f>> BoardWidth>>BoardHeight;
    PlayerBoard.Load(f);
    EnemyBoard.Load(f);
    State.Load(f);
}
