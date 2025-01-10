#include "Abilities.h"
#include "AbilitiesManager.h"
#include "Exceptions.h"
#include "Ship.h"
#include "ShipManager.h"
#include "Cell.h"
#include "Field.h"
#include "Play.h"
#include "Commander.h"
#include "Displayer.h"
#include "GameController.h"
#include <iostream>
using namespace std;
int main() 
{
	ShipManager ships({ 2,1,3,1,3 });
	Field a(ships, 10, 10);
	a.PlaceShip(0, 1, 2, ShipOrientation::horizontal);
	a.attack(1, 2);
	a.PrintField();

	Game gm;
	Commander cmd;
	Display dsp;
	GameController<Commander, Display> gc(gm, cmd, dsp);
	gc.RunGame();
    return 0;
}
