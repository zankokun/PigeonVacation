#ifndef TILEMAP_H_INCLUDED
#define TILEMAP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "MapManager.h"

class TileMap: public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    std::string m_pathToTexture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, int* tiles, unsigned int width, unsigned int height);
    void updateTileMap(MapManager mapMgr);
};

#endif // TILEMAP_H_INCLUDED
