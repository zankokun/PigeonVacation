#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "MapManager.h"

class Player: public sf::Drawable, public sf::Transformable
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f speed;
    int lookAt; /// -1 == Left, 1 == Right

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateSprite(sf::Time &time, MapManager& mapMgr);

public:
    Player(const std::string & filePath, const MapManager& mapMgr);
    void handleEvent(sf::Event &event);

    void update(sf::Time &time, MapManager& mapMgr);

};

#endif // PLAYER_H_INCLUDED
