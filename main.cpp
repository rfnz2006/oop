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

int main() 
{
	Game gm;
	Commander cmd;
	Display dsp;
	GameController<Commander, Display> gc(gm, cmd,dsp);
	gc.RunGame();
    return 0;
}
