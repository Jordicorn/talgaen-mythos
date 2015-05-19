#include "editormap.h"
#include "Rect.h"
#include "Math/Operations.h"
#include "Texture.h"

namespace talga
{
  namespace editor
  {

    EditorMap::EditorMap()
      : Map()
    {

    }

    EditorMap::~EditorMap()
    {

    }

    EditorMap::EditorMap(const EditorMap &cpy)
      : Map (cpy)
    {

    }

    const EditorMap &EditorMap::operator=(const EditorMap &cpy)
    {
      Map::operator =(cpy);
      return *this;
    }

    const EditorMap &EditorMap::operator=(const Map &cpy)
    {
      Map::operator =(cpy);
      return *this;
    }

    I32 EditorMap::getOffset(cpTex tex)
    {
      for (I32 i = 0; i < mTileSet.size(); ++i)
      {
        if (tex == mTileSet[i].first)
        {
          return i;
        }
      }

      TALGA_WARN(0, std::string("attempted to find the offest of non exsistent texture in map ") + mName );
      return -1;
    }

    void EditorMap::insertSheet(cpTex tex)
    {
      bool found = false;
      for (auto iter = mTileSet.begin(); iter != mTileSet.end(); ++iter)
      {
        if (iter->first == tex) return;
      }

      for (I32 y = 0; y < tex->h(); y += mTileHeight)
      {
        for (I32 x = 0; x < tex->w(); x += mTileWidth)
        {
          vec2 uvBL = GET_UV( x, tex->w(), y, tex->h());
          vec2 uvBR = GET_UV( x + mTileWidth, tex->w(), y, tex->h());
          vec2 uvTR = GET_UV( x + mTileWidth, tex->w(),y + mTileHeight, tex->h());
          vec2 uvTL = GET_UV( x, tex->w(), y + mTileHeight, tex->h());

          mTileSet.push_back( Tile{tex, UVFrame{{uvTL, uvTR, uvBR, uvBL}}} );
        }
      }

      TALGA_MSG(tex->getName() + std::string(" was sucessfully added to the map ") + mName);

      return;
    }

    void EditorMap::insertIndices(IndicesList tiles, Rect drop)
    {
      I32 y = drop.y;
      for (auto& row : tiles)
      {
        I32 x = drop.x;
        for (auto& index : row)
        {
          mMap[y * mWidth + x] = index;

          ++x;
        }

        ++y;
      }
    }

    IndicesList EditorMap::insertTile(Rect selection, Rect dropPos, cpTex tex)
    {
      insertSheet(tex);

      I32 offset = getOffset(tex);
      IndicesList previousIndices;

      for (I32 y = selection.y, countY = 0; y < selection.y + selection.h; ++y, ++countY)
      {
        previousIndices.push_back(std::vector<I32>{});
        for (I32 x = selection.x, countX = 0; x < selection.x + selection.w; ++x, ++countX)
        {
          if (!Exists((I32)dropPos.x + countX, (I32)dropPos.y + countY)) continue;
          I32 index = offset + (y * (tex->w() / mTileWidth) + x) + 1;

          previousIndices.back().push_back(mMap[ ((I32)dropPos.y + countY)* mWidth + ((I32)dropPos.x + countX)]);
          mMap[ ((I32)dropPos.y + countY)* mWidth + ((I32)dropPos.x + countX)] = index;
        }
      }

      return previousIndices;
    }

    Tile EditorMap::getTile(I32 x, I32 y, cpTex tex)
    {
      I32 offset = getOffset(tex);
      TALGA_ASSERT(offset != -1, "attempted to get offset of nonexistent texture");

      I32 tileWidth = tex->w() / mTileWidth;
      I32 tileHeight = tex->h() / mTileHeight;

      TALGA_ASSERT( (x >= 0 && x < tileWidth) && (y >= 0 && y < tileHeight), "");

      return mTileSet[offset + (y * tileWidth + x)];
    }



    std::vector<Tile> EditorMap::getTiles(Rect tiles, cpTex tex)
    {
      std::vector<Tile> set;

      for (I32 y = tiles.y; y < tiles.y + tiles.h; ++y)
      {
        for (I32 x = tiles.x; x < tiles.x + tiles.w; ++x)
        {
          set.push_back(getTile(x, y, tex));
        }
      }

      return set;
    }

  }
}
