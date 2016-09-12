#pragma once

// parser class that can read simple input types

#include <iostream>
#include <sstream>

using namespace std;

class ArgumentParser
{

	private:
	
	string rawLine;

	public:
	
	ArgumentParser(string input)
	{
		rawLine = input + ' ';
	}
	
	ArgumentParser(vector<string> line)
	{
		rawLine = "";
		for (string s : line)
		{
			rawLine += s + " ";
		}
	}

	string parseCommand()
	{
		string out = rawLine.substr(0,rawLine.find(' '));
		if (out.size() == 0)
			throw 20;
		rawLine = rawLine.substr(rawLine.find(' ')+1);
		return out;
	}
	
	int parseInt()
	{
		string input = parseCommand();
		int out;
		stringstream ss;
		
		ss << input;
		ss >> out;
		
		return out;
	}
	
	string parseString()
	{
		if (rawLine.at(0) != '"')
			throw 20;
		rawLine = rawLine.substr(1);
		
		string out = rawLine.substr(0,rawLine.find('"'));
		if (out.size() == 0)
			throw 20;
		rawLine = rawLine.substr(rawLine.find('"')+2);
		return out;
	}
	
	string getRawLine()
	{
		return rawLine;
	}
	
};
