#ifndef STONE_H_INCLUDED
#define STONE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "MapManager.h"

class Stone: public sf::Drawable, public sf::Transformable
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f speed;
    sf::Vector2f dir;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateSprite(sf::Time &time, MapManager& mapMgr);

public:
    Stone(const std::string & filePath, const MapManager& mapMgr);

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    void update(sf::Time &time, MapManager& mapMgr);

};


#endif // STONE_H_INCLUDED
