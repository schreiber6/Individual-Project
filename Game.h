#pragma once

/*

Class definitions to be used by the game world class. This file contains
data structure definitions for:
- Victory
- Game
- Player

*/

#include <vector>
#include <iostream>

using namespace std;

struct Victory
{
	int gameID;
	int victoryID;
	string name;
	int value;

	Victory(int gid, int vid, string n, int val)
	{
		gameID = gid;
		victoryID = vid;
		name = n;
		value = val;
	}
};

struct Game
{
	string name;
	int gameID;
	
	Game()
	{
		name = "";
		gameID = 0;
	}
	
	Game(string n, int gid)
	{
		name = n;
		gameID = gid;
	}
	
};

struct Player
{
	// Internal structure to organize the game and player settings together
	struct GamePlayed
	{
		Game* game = NULL;
		string gamertag = "";
		
		GamePlayed() {}
		GamePlayed(Game* gamePointer, string gametag)
		{
			game = gamePointer;
			gamertag = gametag;
		}
	};

	int playerID;
	vector<Player*> friends;
	vector<Victory*> achievementsWon;
	vector<GamePlayed*> gamesPlayed;
	string playerName;
	
	Player()
	{
		playerID = -1;
		playerName = "";
	}
	
	Player(string n, int pid)
	{
		playerName = n;
		playerID = pid;
	}
	
	void addGamePlayed(Game* g, string n)
	{
		gamesPlayed.push_back(new GamePlayed(g,n));
	}
};
