#pragma once

/// Game World

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "Game.h"
#include "Parser.h"

using namespace std;

class GameWorld
{	
	private:
	vector<string> commandNames;
	
	vector<Game*> games;
	vector<Player*> players;
	vector<Victory*> victories;
	
	int findIndexOfElement(vector<string> vec, string arg)
	{
		for (int i = 0; i<vec.size(); ++i)
		{
			if (vec[i] == arg)
				return i;
		}
		return -1;
	}
	
	// I wanted to generalize this method using template, but I got lots of
	// strange errors when I tried to. Fortunately, the only data type I needed
	// to use this on was pointers to victory objects.
	bool elementInList(Victory* elem, vector<Victory*> list)
	{
		for (auto e : list)
		{
			if (e == elem)
				return true;
		}
		return false;
	}
	
	
	public:
	
	GameWorld()
	{
		commandNames.push_back("AddGame");
		commandNames.push_back("AddVictory");
		commandNames.push_back("AddPlayer");
		commandNames.push_back("AddFriends");
		commandNames.push_back("Plays");
		commandNames.push_back("WinVictory");
		commandNames.push_back("FriendsWhoPlay");
		commandNames.push_back("ComparePlayers");
		commandNames.push_back("SummarizePlayer");
		commandNames.push_back("SummarizeGame");
		commandNames.push_back("SummarizeVictory");
		commandNames.push_back("VictoryRanking");
	}
	
	// Returns true if the execution of the command succeeds
	bool processCommand(vector<string> line)
	{
		if (line.size() == 0)
			return true;
		
		switch (findIndexOfElement(commandNames,line[0]))
		{
			case 0: return comAddGame(line);
			case 1: return comAddVictory(line);
			case 2: return comAddPlayer(line);
			case 3: return comAddFriends(line);
			case 4: return comPlays(line);
			case 5: return comWinVictory(line);
			case 6: return comFriendsWhoPlay(line);
			case 7: return comComparePlayers(line);
			case 8: return comSummarizePlayer(line);
			case 9: return comSummarizeGame(line);
			case 10: return comSummarizeVictory(line);
			case 11: return comVictoryRanking(line);
			default: return false;
		}
	}
	
	// ---- ------------------ - - - -- ----------------------- //
	
	Player* findPlayerWithID(int id)
	{
		Player* out = NULL;
		for (Player* p : players)
		{
			if (p->playerID == id)
				out = p;
		}
		if (out == NULL)
			throw (20);
		return out;
	}

	Game* findGameWithID(int id)
	{
		Game* out = NULL;
		for (Game* g : games)
		{
			if (g->gameID == id)
				out = g;
		}
		if (out == NULL)
			throw (20);
		return out;
	}

	Victory* findVictoryWithID(int gid, int vid)
	{
		Victory* out = NULL;
		for (Victory* v : victories)
		{
			if (v->victoryID == vid && v->gameID == gid)
				out = v;
		}
		if (out == NULL)
			throw (20);
		return out;
	}
	
	// Output in the form: [victories won, total possible, gamerscore]
	vector<int> victoryDataForPlayerForGame(Player* player, Game* game)
	{
		int totalVictories = 0;
		int victoriesWon = 0;
		int gamerscore = 0;
		for (Victory* v : player->achievementsWon)
		{
			if (v->gameID == game->gameID)
			{
				victoriesWon++;
				gamerscore += v->value;
			}
		}
		for (Victory* v : victories)
		{
			if (v->gameID == game->gameID)
				totalVictories++;
		}
		vector<int> out;
		out.push_back(victoriesWon);
		out.push_back(totalVictories);
		out.push_back(gamerscore);
		return out;
	}
	
	// this is the total
	int gamerscoreForPlayer(Player* player)
	{
		int total = 0;
		for (auto g : player->gamesPlayed)
		{
			total += victoryDataForPlayerForGame(player,g->game)[2];
		}
		return total;
	}
	
	vector<Player*> playersWhoWonVictory(int id)
	{
		vector<Player*> out;
		for (Player* p : players)
		{
			for (Victory* v : p->achievementsWon)
			{
				if (v->victoryID == id)
					out.push_back(p);
			}
		}
		return out;
	}
	
	vector<Player*> playersWhoPlayGame(int id)
	{
		vector<Player*> out;
		for (Player* p : players)
		{
			for (auto g : p->gamesPlayed)
			{
				if (g->game->gameID == id)
					out.push_back(p);
			}
		}
		return out;
	}
	
	vector<Victory*> victoriesInGame(int id)
	{
		vector<Victory*> out;
		for (Victory* v : victories)
		{
			if (v->gameID == id)
				out.push_back(v);
		}
		return out;
	}
	
	
	// For this next (and final) section, I added the prefix 'com' to all of
	// the methods to indicate that they execute a command that the user
	// specified. The methods will return true if they worked, and return
	// false if an exception occurred for any reason.
	
	
	bool comAddGame(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int gameID;
		string name;
		
		try
		{
			parser.parseCommand();
			gameID = parser.parseInt();
			name = parser.parseString();
		} 
		catch (...) { return false; }
		
		games.push_back(new Game(name,gameID));
		
		return true;
	}
	
	bool comAddPlayer(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int playerID;
		string name;
		
		try
		{
			parser.parseCommand();
			playerID = parser.parseInt();
			name = parser.parseString();
		} 
		catch (...) { return false; }
		
		players.push_back(new Player(name,playerID));
		
		return true;
	}
	
	bool comAddVictory(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int gameID, victoryID, value;
		string victoryName;
		
		try
		{
			parser.parseCommand();
			gameID = parser.parseInt();
			victoryID = parser.parseInt();
			victoryName = parser.parseString();
			value = parser.parseInt();
		} 
		catch (...) { return false; }
		
		victories.push_back(new Victory(gameID, victoryID, victoryName, value));
		
		return true;
	}
	
	bool comAddFriends(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int id1,id2;
		Player* player1;
		Player* player2;
		
		try
		{
			parser.parseCommand();
			id1 = parser.parseInt();
			id2 = parser.parseInt();
			player1 = findPlayerWithID(id1);
			player2 = findPlayerWithID(id2);
			player1->friends.push_back(player2);
			player2->friends.push_back(player1);
		} 
		catch (...) { return false; }
		
		return true;
	}
	
	bool comPlays(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int pid, gid;
		string gamertag;
		
		try
		{
			parser.parseCommand();
			pid = parser.parseInt();
			gid = parser.parseInt();
			gamertag = parser.parseString();
			Player* player = findPlayerWithID(pid);
			Game* game = findGameWithID(gid);
			player->addGamePlayed(game,gamertag);
		}
		catch (...) { return false; }
		
		return true;
	}
	
	bool comWinVictory(vector<string> line)
	{	
		ArgumentParser parser = ArgumentParser(line);
		int playerID, gameID, victoryID;
		
		try
		{
			parser.parseCommand();
			playerID = parser.parseInt();
			gameID = parser.parseInt();
			victoryID = parser.parseInt();
			Player* player = findPlayerWithID(playerID);
			Victory* victory = findVictoryWithID(gameID,victoryID);
			player->achievementsWon.push_back(victory);
		}
		catch (...) { return false; }
		
		return true;
	}
	
	bool comFriendsWhoPlay(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int playerID, gameID;
		Player* player;
		Game* game;
		
		try
		{
			parser.parseCommand();
			playerID = parser.parseInt();
			gameID = parser.parseInt();
			player = findPlayerWithID(playerID);
			game = findGameWithID(gameID);
			
			printf("Friends of '%s' who play '%s':\n\n",player->playerName.c_str(),game->name.c_str());
			printf("%5s | %s\n","ID","Name");
			printf("------+---------------------------------------\n");
			for (Player* f : player->friends)
			{
				printf("%5d | %s\n",f->playerID, f->playerName.c_str());
			}
		}
		catch (...) { return false; }
	
		return true;
	}
	
	bool comComparePlayers(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int id1,id2,gameID;
		Player* player1;
		Player* player2;
		Game* game;
		
		try
		{
			parser.parseCommand();
			id1 = parser.parseInt();
			id2 = parser.parseInt();
			gameID = parser.parseInt();
			player1 = findPlayerWithID(id1);
			player2 = findPlayerWithID(id2);
			game = findGameWithID(gameID);
		}
		catch (...) { return false; }
		
		printf("Comparing players playing game : '%s'\n\n",game->name.c_str());
		printf("%-25s | %-20s | %-20s\n","Achievement",
				player1->playerName.c_str(),
				player2->playerName.c_str());
		printf("-------------------------------------------------------------------\n");
		for (Victory* v : victoriesInGame(gameID))
		{
			int value;
			printf("%-25s | ",v->name.c_str());
			value = 0;
			if (elementInList(v,player1->achievementsWon))
				value = v->value;
			printf("%4d %-15s | ",value,"pts");
			value = 0;
			if (elementInList(v,player2->achievementsWon))
				value = v->value;
			printf("%4d %-15s \n",value,"pts");
		}
		printf("-------------------------------------------------------------------\n");
		int value;
		printf("%-25s | ","Total");
		printf("%4d %-15s | ",victoryDataForPlayerForGame(player1,game)[2],"pts");
		printf("%4d %-15s \n",victoryDataForPlayerForGame(player2,game)[2],"pts");
	
		return true;
	}
	
	bool comSummarizePlayer(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int id;
		Player* player;
		
		try
		{
			parser.parseCommand();
			id = parser.parseInt();
			player = findPlayerWithID(id);
		}
		catch (...) { return false; }
		
		printf("\n%s: %s\n%s: %d pts\n",
				"Player",player->playerName.c_str(),
				"Gamerscore",gamerscoreForPlayer(player));
		
		int index = 0;
		printf("\n    %-20s | Victories |  Score  | Gamertag\n","Game Name");
		printf("---------------------------------------------------------------------\n");
		for (auto g : player->gamesPlayed)
		{
			Game* game = g->game;
			vector<int> data = victoryDataForPlayerForGame(player,game);
			index++;
			printf("%2d. %-20s | %4d/%-4d | %3d pts | '%s'\n",
					index,g->game->name.c_str(),data[0],data[1],data[2],g->gamertag.c_str());
		}
		
		index = 0;
		printf("\n    %-20s | Score \n","Friend");
		printf("---------------------------------------------------------------------\n");
		for (Player* f : player->friends)
		{
			index++;
			printf("%2d. %-20s | %4d pts\n",index,f->playerName.c_str(),gamerscoreForPlayer(f));
		}
		
		return true;
	}
	
	bool comSummarizeGame(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int gameID;
		Game* game;
		vector<Player*> gamePlayers;
		vector<Victory*> gameVictories;
		
		try
		{
			parser.parseCommand();
			gameID = parser.parseInt();
			game = findGameWithID(gameID);
			gamePlayers = playersWhoPlayGame(gameID);
			gameVictories = victoriesInGame(gameID);
		}
		catch (...) { return false; }
		
		printf("Game : '%s'\nID : %d\n\n",game->name.c_str(),game->gameID);
		printf("%-20s | Score for Game\n","Player");
		printf("--------------------------------------\n");
		for (Player* p : gamePlayers)
		{
			printf("%-20s | %d pts \n",
					p->playerName.c_str(),
					victoryDataForPlayerForGame(p,game)[2]);
		}

		printf("\n%-25s |  Value  | Times Won \n","Victory");
		printf("------------------------------------------------\n");
		for (Victory* v : gameVictories)
		{
			printf("%-25s | %3d pts | %d/%d \n",
					v->name.c_str(),
					v->value,
					playersWhoWonVictory(v->victoryID).size(),
					gamePlayers.size());
		}
		
		
		return true;
	}
	
	bool comSummarizeVictory(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		int gameID, victoryID;
		vector<Player*> gamePlayers;
		vector<Victory*> gameVictories;
		vector<Player*> playersWhoWonTheVictory;
		
		try
		{
			parser.parseCommand();
			gameID = parser.parseInt();
			victoryID = parser.parseInt();
			gamePlayers = playersWhoPlayGame(gameID);
			gameVictories = victoriesInGame(gameID);
			playersWhoWonTheVictory = playersWhoWonVictory(victoryID);
		}
		catch (...) { return false; }
		
		printf("Victory : '%s'\n",findVictoryWithID(gameID,victoryID)->name.c_str());
		printf("Game : '%s'\n",findGameWithID(gameID)->name.c_str());
		float percentage = playersWhoWonTheVictory.size()*100.0;
		percentage /= gamePlayers.size();
		
		printf("\nPlayers who achieved victory [%5.2f %%]\n",percentage);
		printf("----------------------------------------\n");
		for (Player* p : playersWhoWonTheVictory)
		{
			printf("%s\n",p->playerName.c_str());
		}
		
		return true;
	}
	
	bool comVictoryRanking(vector<string> line)
	{
		ArgumentParser parser = ArgumentParser(line);
		try
		{
			parser.parseCommand();
		}
		catch (...) { return false; }
		
		printf("Victory Ranking\n");
		
		printf("\n%-20s | Gamerscore\n","Player");
		printf("-----------------------------------------------\n");
		for (Player* p : players)
		{
			printf("%-20s | %d pts\n",p->playerName.c_str(),gamerscoreForPlayer(p));
		}
		return true;
	}
};
