#ifndef BAG_H
#define BAG_H

#include "LinkedList.hpp"
#include "TileCodes.hpp"

#include <algorithm>
#include <random>
#include <string>
#include <vector>

class Bag
{
public:
   Bag();
   Bag(std::string bagInfo);
   ~Bag();
   Tile* popTile();
   void pushTile(Tile* tile);
   void scrambleTiles(std::vector<Tile*> tilesToScramble);
   void initialiseTiles();
   LinkedList* getTilesInBag();

private:
   LinkedList* tilesInBag;
   std::vector<int> ints;
};

#endif // BAG_H