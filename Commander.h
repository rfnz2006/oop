#pragma once

class Commander 
{
public:
	struct ShipPlacement {unsigned x, y; bool Vert; };
	enum class Cmd { Quit, Load, Save, Move, Error };
	struct NextAction { Cmd cmd; unsigned x, y; bool ab;};
public:
	Commander();
	~Commander();
	bool AskPlayerboardType();
	ShipPlacement AskShipPlacement(unsigned s);
	NextAction AskNextAction(bool ab);
};