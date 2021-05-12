#include "Board.hpp"

Board::Board()
{
   this->loadingFromSave = false;
   this->dimCols         = 26; // X
   this->dimRows         = 26; // Y
   this->tilesOnBoard.resize(dimRows, std::vector<Tile*>(dimCols, 0));

   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         tilesOnBoard[row][col] = nullptr;
      }
   }
}

Board::Board(int dimCols, int dimRows, std::string boardState)
{
   this->loadingFromSave = true;
   this->dimCols         = dimCols; // Cols
   this->dimRows         = dimRows; // Rows
   this->tilesOnBoard.resize(dimRows, std::vector<Tile*>(dimCols, 0));
   std::stringstream boardTiles(boardState);

   // iterate through boardstate
   while (boardTiles.good())
   {
      Tile* tileToPlace          = nullptr;
      std::string tileToPlaceStr = "";
      std::getline(boardTiles, tileToPlaceStr, '@');
      // DUPLICATED CODE - MAKE METHOD FOR THIS?
      Colour tileColour     = tileToPlaceStr[0];
      std::string toConvert = "";
      toConvert.push_back(tileToPlaceStr[1]);
      Shape tileShape = atoi(toConvert.c_str());

      Colour colours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
      Shape shapes[]   = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
      // check if tile is valid
      for (Colour colour : colours)
      {
         for (Shape shape : shapes)
         {
            if (tileShape == shape && tileColour == colour)
            {
               tileToPlace = new Tile(tileShape, tileColour);
            }
         }
      }

      std::string coordToPlace = "";
      // currently delimiting with a single comma, should be ", " (with a space)
      std::getline(boardTiles, coordToPlace, ',');
      // find the tile on board
      // CODE YOINKED FROM GAME.CPP
      // bool isValid = false;

      if (coordToPlace.size() == 2)
      {
         std::string str = "";
         for (char A = 'A'; A <= 'Z'; A++)
         {
            if (coordToPlace[0] == A)
            {
               str.push_back(coordToPlace[1]);
               int col = atoi(str.c_str());
               if (col >= 0 && col <= 9) // for A0 - A9
               {
                  // isValid = true;
               }
            }
         }
      }
      else if (coordToPlace.size() == 3)
      {
         std::string str = "";
         for (char A = 'A'; A <= 'Z'; A++)
         {
            if (coordToPlace[0] == A)
            {
               str.push_back(coordToPlace[1]);
               str.push_back(coordToPlace[2]);
               int col = atoi(str.c_str());
               if (col >= 10 && col <= 25) // for A10 - A25
               {
                  // isValid = true;
               }
            }
         }
      }

      // place tileToPlace there
      int x = 0;
      if (coordToPlace.size() == 2)
      {
         std::string str = "";
         str.push_back(coordToPlace[1]);
         x = atoi(str.c_str());
      }
      else if (coordToPlace.size() == 3)
      {
         std::string str = "";
         str.push_back(coordToPlace[1]);
         str.push_back(coordToPlace[2]);
         x = atoi(str.c_str());
      }

      int y   = 0;
      int row = 0;
      for (char A = 'A'; A <= 'Z'; A++)
      {
         if (coordToPlace[0] == A)
         {
            y = row;
         }
         row++;
      }

      // END YOINK
      placeTile(tileToPlace, x, y);
   }
   // place each tile at its given location

   loadingFromSave = false;
}

Board::~Board()
{
   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] != nullptr)
         {
            delete tilesOnBoard[row][col];
         }
      }
   }
}

void Board::printBoard()
{
   std::cout << "   ";

   for (int i = 0; i < dimCols; i++)
   {
      if (i >= 10)
      {
         std::cout << i << " ";
      }
      else
      {
         std::cout << i << "  ";
      }
   }

   std::cout << std::endl;
   std::cout << "  ";

   // Static 79 for the 26x26 board
   for (int i = 0; i < 79; i++)
   {
      std::cout << "-";
   }

   std::cout << std::endl;

   char c      = 'A';
   int rowSize = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      std::cout << c << " |";
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] == nullptr)
         {
            std::cout << "  ";
         }
         else
         {
            tilesOnBoard[row][col]->printTile();
         }
         std::cout << "|";
      }

      std::cout << std::endl;
      c++;
   }

   std::cout << "  ";

   for (int i = 0; i < 79; i++)
   {
      std::cout << "-";
   }

   std::cout << std::endl;
}

Tile* Board::getTile(std::string tile)
{
   return nullptr;
}

int Board::calculateScoreHorizontal(int coordX, int coordY)
{
   int score = 0;

   // check left
   int leftX = coordX - 1;
   while (leftX >= 0 && tilesOnBoard[coordY][leftX] != nullptr)
   {
      leftX--;
   }
   leftX++;

   // check right
   int rightX = coordX + 1;
   while (rightX < dimCols && tilesOnBoard[coordY][rightX] != nullptr)
   {
      rightX++;
   }
   rightX--;

   score = (rightX - leftX) + 1;

   if (score == 6)
   {
      score += 6;
   }

   if (score == 1)
   {
      score = 0;
   }

   return score;
}

int Board::calculateScoreVertical(int coordX, int coordY)
{
   int score = 0;

   // check up
   int upY = coordY - 1;
   while (upY >= 0 && tilesOnBoard[upY][coordX] != nullptr)
   {
      upY--;
   }
   upY++;

   // check down
   int downY = coordY + 1;
   while (downY < dimRows && tilesOnBoard[downY][coordX] != nullptr)
   {
      downY++;
   }
   downY--;

   score = (downY - upY) + 1;

   if (score == 6)
   {
      score += 6;
   }

   if (score == 1)
   {
      score = 0;
   }

   return score;
}

// isEmptySpot and placeTile both use the crappy coordinate.size beacuse i need
// to convert the coordinate information each time i need to read it >:(
// maybe we need a convert coordinate thing in game.cpp?
bool Board::isEmptySpot(int x, int y)
{
   bool isEmpty = false;
   int rowSize  = tilesOnBoard.size();
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (x == col && y == row)
         {
            if (tilesOnBoard[row][col] == nullptr)
            {
               isEmpty = true;
            }
         }
      }
   }

   return isEmpty;
}

bool Board::canPlaceHorizontal(Tile* tileToPlace, int x, int y)
{
   bool valid          = true;
   Colour targetColour = tileToPlace->toString().at(0);
   char targetShape    = tileToPlace->toString().at(1);

   // check left
   int leftX = x - 1;
   while (leftX >= 0 && tilesOnBoard[y][leftX] != nullptr)
   {
      leftX--;
   }
   leftX++;
   // check right
   int rightX = x + 1;
   while (rightX < dimCols && tilesOnBoard[y][rightX] != nullptr)
   {
      rightX++;
   }
   rightX--;

   // check tiles in range
   for (int currX = leftX; currX <= rightX; currX++)
   {
      // don't check target coordinate
      if (currX != x)
      {
         Tile* currentTile      = tilesOnBoard[y][currX];
         Colour currentColour   = currentTile->toString().at(0);
         char currentShape      = currentTile->toString().at(1);
         bool isMatchingColours = currentColour == targetColour;
         bool isMatchingShapes  = currentShape == targetShape;
         if (isMatchingColours && isMatchingShapes)
         {
            // can't repeat the same tile
            valid = false;
         }
         else if (!isMatchingColours && !isMatchingShapes)
         {
            // can't place the tile next to a tile with no matches
            valid = false;
         }
      }
   }

   return valid;
}

bool Board::canPlaceVertical(Tile* tileToPlace, int x, int y)
{
   bool valid          = true;
   Colour targetColour = tileToPlace->toString().at(0);
   char targetShape    = tileToPlace->toString().at(1);

   // check up
   int upY = y - 1;
   while (upY >= 0 && tilesOnBoard[upY][x] != nullptr)
   {
      upY--;
   }
   upY++;
   // check down
   int downY = y + 1;
   while (downY < dimRows && tilesOnBoard[downY][x] != nullptr)
   {
      downY++;
   }
   downY--;

   // check tiles in range
   for (int currY = upY; currY <= downY; currY++)
   {
      // don't check target coordinate
      if (currY != y)
      {
         Tile* currentTile      = tilesOnBoard[currY][x];
         Colour currentColour   = currentTile->toString().at(0);
         char currentShape      = currentTile->toString().at(1);
         bool isMatchingColours = currentColour == targetColour;
         bool isMatchingShapes  = currentShape == targetShape;
         if (isMatchingColours && isMatchingShapes)
         {
            // can't repeat the same tile
            valid = false;
         }
         else if (!isMatchingColours && !isMatchingShapes)
         {
            // can't place the tile next to a tile with no matches
            valid = false;
         }
      }
   }

   return valid;
}

bool Board::hasAdjacent(int x, int y)
{
   bool success = false;

   // left
   if (x > 0 && tilesOnBoard[y][x - 1] != nullptr)
   {
      success = true;
   }
   // right
   if (x < dimCols - 1 && tilesOnBoard[y][x + 1] != nullptr)
   {
      success = true;
   }
   // up
   if (y > 0 && tilesOnBoard[y - 1][x] != nullptr)
   {
      success = true;
   }
   // down
   if (y < dimRows - 1 && tilesOnBoard[y + 1][x] != nullptr)
   {
      success = true;
   }

   return success;
}

bool Board::isFirstTile()
{
   bool firstTile = true;
   for (int y = 0; y < dimRows; y++)
   {
      for (int x = 0; x < dimCols; x++)
      {
         if (tilesOnBoard[y][x] != nullptr)
         {
            firstTile = false;
         }
      }
   }
   return firstTile;
}

bool Board::placeTile(Tile* tileToPlace, int x, int y)
{
   bool success = false;
   if (y >= 0 && y < dimRows && x >= 0 && x < dimCols)
   {
      // empty check
      if (tilesOnBoard[y][x] == nullptr)
      {
         if (!loadingFromSave)
         {
            if ((hasAdjacent(x, y) && canPlaceHorizontal(tileToPlace, x, y) &&
                   canPlaceVertical(tileToPlace, x, y)) ||
                isFirstTile())
            {
               tilesOnBoard[y][x] = tileToPlace;
               success            = true;
            }
         }
         else
         {
            tilesOnBoard[y][x] = tileToPlace;
            success            = true;
         }
      }
   }

   return success;
}

std::string Board::saveBoard()
{
   std::string boardState = "";
   int rowSize            = tilesOnBoard.size();
   bool matchingTile      = false;
   for (int row = 0; row < rowSize; row++)
   {
      int colSize = tilesOnBoard[row].size();
      for (int col = 0; col < colSize; col++)
      {
         if (tilesOnBoard[row][col] != nullptr)
         {
            // Converting row into alphbetical
            char c = 'A';
            for (int i = 0; i < rowSize; i++)
            {
               if (i == row)
               {
                  matchingTile = true;
                  boardState.append(tilesOnBoard[row][col]->toString() + "@" +
                                    c + std::to_string(col) + ", ");
               }
               c++;
            }
         }
      }
   }

   // Sorry guys :C
   if (matchingTile)
   {
      int size = boardState.size();
      boardState.erase(size - 1);
      boardState.erase(size - 2);
   }
   return boardState;
}

int Board::getDimCols()
{
   return dimCols;
}

int Board::getDimRows()
{
   return dimRows;
}
