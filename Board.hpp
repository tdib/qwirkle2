#ifndef BOARD_H
#define BOARD_H

#include "Tile.hpp"
#include "TileCodes.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Board
{
public:
   Board();
   Board(int dimX, int dimY, std::string boardState);
   ~Board();
   void printBoard();
   Tile* getTile(std::string tile);
   int calculateScoreHorizontal(int coordX, int coordY);
   int calculateScoreVertical(int coordX, int coordY);
   bool placeTile(Tile* tileToPlace, int x, int y);
   bool isEmptySpot(int x, int y);
   std::string saveBoard();
   int getDimCols();
   int getDimRows();
   bool isFirstTile();

private:
   std::vector<std::vector<Tile*>> tilesOnBoard;
   int dimCols;
   int dimRows;
   bool canPlaceHorizontal(Tile* tileToPlace, int x, int y);
   bool canPlaceVertical(Tile* tileToPlace, int x, int y);
   bool hasAdjacent(int x, int y);
   bool loadingFromSave;
};

#endif // BOARD_H