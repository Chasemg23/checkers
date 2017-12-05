///@file main.cc
///@brief Main function
///@details Creates a game object pointer, makes the pointer point to a new checkers object, and then calls the game::play() function to start the game
///@author Chase Gindlesperger

/**
	* Chase Gindlesperger
	* main.cc
	*
	* CS3560 Term Project
*/

#include <iostream>
#include "colors.h"
#include "checkers.h"

using namespace main_savitch_14;

int main () {
	game * c;			///< game object pointer
	c = new checkers;		///< set the pointer to point to a new checkers object
	c->play();			///< call the game::play() function to start the game
	return 0;
}
