/*

Individual Project - Victory/Game/Player Tracker
CSCE 315 - Section 501

Author :	Christopher Ryan Schreiber
Date :		7 September 2016

Brief Description:
This program reads and interprets commands from the standard input, then
keeps track of what happens to the games, players, and victories in this
game world, and can report the state of the game world. More info on the
acceptable commands can be found in the report or documentation.

*/

#include <iostream>
#include <fstream>
#include "InputHandler.h"

using namespace std;

int main(int argc, char** argv)
{
	// There should not be any command line inputs
	if (argc > 1)
	{
		cout << "Too many command line input arguments.\n";
		cout << "Expecting 0, but received " << argc-1 << ".\n";
		return 1;
	}
	
	cout << endl;
	
	// The interpreter reads from the standard input
	InputHandler interpreter = InputHandler();
	interpreter.readAll();

}

