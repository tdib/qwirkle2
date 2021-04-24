#ifndef ASSIGN2_GAME_H
#define ASSIGN2_GAME_H

#include "Bag.h"
#include "InputCodes.h"
#include "Player.h"
#include "Tile.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Game
{
public:
   Game();
   Game(std::string* fileName);
   ~Game();

   // Public or else qwirkle.cpp can't use them
   void playGame();
   void initalisePlayers();
   void loadTiles(std::string* tilesInfo);
   void printState();
   bool saveGame();
   void quit();
   std::vector<std::string> splitString(
      std::string rawUserInput, char delimiter);

private:
   // player as a vector

   Board* board;
   Bag* bag;
   std::vector<Player*> players;
};

#endif // ASSIGN2_GAME_H
