#pragma once

#include "Play.h"
#include "Commander.h"
#include "Displayer.h"


template< typename CMDER, typename DSPLR >
class GameController 
{
public:
	GameController(Game& g, CMDER& c, DSPLR& d) : game(g), cmder(c), dsplr(d){}
	~GameController() {}
	void  RunGame();
    void PreparePlayerBoard();
private:
    RoundResult Round();
private:
    Game& game;
	CMDER& cmder;
    DSPLR& dsplr;
};

template< typename CMD, typename DSPLR >
void  GameController<CMD, DSPLR>::RunGame()
{

    for (;;) {
         bool gen = cmder.AskPlayerboardType();
        dsplr.ShowMessage("Initialize GAME...");
         dsplr.ShowMessage("31");
       // dsplr.ShowMessage(gen);
          std::cout << gen << std::endl;
        game.InitializeGame(gen);
         std::cout << "game controller" << std::endl;
        if (!gen)       {
            PreparePlayerBoard();}
        for (;;) {
            
            auto res = Round();
            if (res == RoundResult::Quit) {
                dsplr.ShowMessage( "Quit");
                return;
            }
            if (res == RoundResult::GameOver) {
                dsplr.ShowBoard( game.GetPlayerBoard());
                dsplr.ShowMessage("Game is over. You were defeated!");
                break;
            }
            if (res == RoundResult::RoundOver) {
                dsplr.ShowBoard(game.GetEnemyBoard());
                dsplr.ShowMessage("Round is over. You won!");
                dsplr.ShowMessage("Initialize ROUND" );
                game.InitializeRound();
            }
        }
    }
}
template<typename CMDER, typename DSPLR>
RoundResult GameController<CMDER,DSPLR>::Round()
{ 
     std::cout << "Entering Round() function" << std::endl;
    std::cout << "Round..." << std::endl;
    for (;;) {
         std::cout << "looping...." << std::endl;
        dsplr.ShowBoard(game.GetPlayerBoard());
        dsplr.ShowGameState(game.GetGameState(), game.GetAbilitiesSize());
        
        auto next_action = cmder.AskNextAction(game.GetAbilitiesSize() > 0);
        auto abmsg=0;    
        auto turn_result=RoundResult::Continue;
        // Print out the values
        std::cout << "x: " << next_action.x << std::endl;
        std::cout << "y: " << next_action.y << std::endl;
        std::cout << "cmd: " << static_cast<int>(next_action.cmd) << std::endl;
        std::cout << "ab: " << next_action.ab << std::endl;
        
        std::cout << "Before switch, cmd value: " << static_cast<int>(next_action.cmd) << std::endl;
        
        switch (next_action.cmd) {
        case Commander::Cmd::Error:
            std::cout << "Error case executed" << std::endl;
            std::cout << "error:::: " << next_action.x << std::endl;
            turn_result = game.Turn(next_action.x, next_action.y, next_action.ab);
            if (turn_result == RoundResult::Continue)
                continue;
            
        case Commander::Cmd::Move:
            std::cout << "Move case executed" << std::endl;
            std::cout << "move: " << next_action.x << std::endl;
            
            continue;
            /*
            // Move these lines outside the switch statement
            turn_result = game.Turn(next_action.x, next_action.y, next_action.ab);
            abmsg = game.GetAbilityMessage();
            
            if (!abmsg.empty())
                dsplr.ShowMessage(abmsg);
            
            if (turn_result == RoundResult::Continue)
                continue;
            
            return turn_result;*/
        case Commander::Cmd::Quit:
            std::cout << "Quit case executed" << std::endl;
            return RoundResult::Quit;
        case Commander::Cmd::Load:
            std::cout << "Load case executed" << std::endl;
            game.LoadGame();
            continue;
        case Commander::Cmd::Save:
            std::cout << "Save case executed" << std::endl;
            game.SaveGame();
            continue;
        default:
            std::cout << "Default case executed" << std::endl;
            std::cout << "Unknown command: " << static_cast<int>(next_action.cmd) << std::endl;
            std::cout << "hz: " << next_action.x << std::endl;
            continue;
        }
    }
}




template<typename CMDER, typename DSPLR>
void GameController<CMDER,DSPLR>::PreparePlayerBoard()
{
    size_t  num_ships = game.GetPlayerBoard().get_ship_manager().number_of_ships();
    for (int i = 0; i < (int)num_ships; i++) {
        bool newship;
        do {
            dsplr.ShowBoard(game.GetPlayerBoard());
            auto ship_size = game.GetPlayerBoard().get_ship_manager()[i].get_length();   //ship size
            auto [x, y, o] = cmder.AskShipPlacement(ship_size);
            auto ori = !o ? ShipOrientation::horizontal : ShipOrientation::vertical;
            newship = game.PlacePlayerShip(i, x, y, ori);
        } while (!newship);
    }
}
