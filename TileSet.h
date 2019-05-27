#ifndef TILESET_H
#define TILESET_H

#include <string>
#include "Rect.h"
#include "Sprite.h"
using namespace std;

class TileSet{
public:
    TileSet(GameObject& associated, float tileWidth, float tileHeight, string file);
    void RenderTile(int index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
	int GetRows();
	int GetColumns();
private:
    Sprite* tileSet;
    int rows, columns, tileWidth, tileHeight;
};

#endif