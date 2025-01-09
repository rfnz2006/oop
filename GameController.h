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
        dsplr.ShowMessage("Initialize GAME");
        bool gen = cmder.AskPlayerboardType();
        game.InitializeGame(gen);
        if (!gen)       
            PreparePlayerBoard();
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
    for (;;) {
        dsplr.ShowBoard(game.GetPlayerBoard());
        dsplr.ShowGameState(game.GetGameState(), game.GetAbilitiesSize());
        auto next_action = cmder.AskNextAction(game.GetAbilitiesSize() > 0);
        switch (next_action.cmd) {
        case Commander::Cmd::Error:
            continue;
        case Commander::Cmd::Move:{
            auto turn_result = game.Turn(next_action.x, next_action.y, next_action.ab);
            auto abmsg = game.GetAbilityMessage();
            if (!abmsg.empty())
                dsplr.ShowMessage(abmsg);
            if (turn_result == RoundResult::Continue)
                continue;
            return turn_result;
        }
        case Commander::Cmd::Quit:
            return RoundResult::Quit;
        case Commander::Cmd::Load:
            game.LoadGame();
            continue;
        case Commander::Cmd::Save:
            game.SaveGame();
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
