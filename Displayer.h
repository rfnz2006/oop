#pragma once

#include <string>
#include "Field.h"
#include "Play.h"



class Display 
{
public:
	Display();
	~Display();
	void ShowBoard(const Field& gb );
	void ShowMessage(const std::string&);
	void ShowGameState( const GameState&, size_t num_abilities);
};