#pragma once

// Input Handler Class

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "GameWorld.h"

using namespace std;

class InputHandler
{
	private:

	bool exitCondition;
	int linesRead;				// <-- How many are lines are valid commands
	int linesProcessed;			// <-- How many lines actually worked: 
								//     proper syntax, valid arguments, etc.
	vector<string> line;
	GameWorld gw = GameWorld();
	
	public:
	
	InputHandler()
	{
		exitCondition = false;
		linesRead = 0;
		linesProcessed = 0;
	}
	
	// A continuous loop version of the readNextLine method
	void readAll()
	{
		int linesRead = 0;
		while (!cin.eof() && !exitCondition)
		{
			readNextLine();
			if (gw.processCommand(line))
				linesProcessed++;
			else
				cout << "Line number [" << linesRead+1 << "] failed." << endl;
			linesRead++;
		}
		cout << "\n\nSuccessfully read " << linesRead << " lines.\n";
		cout << "Successfully processed " << linesProcessed << " lines.\n";
	}
	
	// Special case consideration: the program is intended to have an input
	// file directed to the standard input, but if none is specified, the
	// commands can be typed line by line in the command line. In this case
	// the user can brake the infinite loop by typing the 'quit' command.
	void readNextLine()
	{
		line.clear();
		stringstream ss;
		char text[256];
		cin.getline(text,256);
		ss << text;
		string arg;
		while (ss>>arg)
			line.push_back(arg);
		exitCondition = (line.size() > 0 && line.at(0) == "quit");
	}
	
};
