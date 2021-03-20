#include "Player.h"

Player::Player(const std::string &filePath, const MapManager& mapMgr)
{
    if(!texture.loadFromFile(filePath)){
        throw; /// std::logic_error("wrong file for ping"); ///
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,mapMgr.getBlockSize().x,mapMgr.getBlockSize().y));

    int x = (mapMgr.getWidth()/2 ) * mapMgr.getBlockSize().x;
    int y = (mapMgr.getHeight()/2 ) * mapMgr.getBlockSize().y;

    sprite.setPosition(x, y);
    sprite.setOrigin(mapMgr.getBlockSize().x/2,mapMgr.getBlockSize().y/2);
    speed = sf::Vector2f(mapMgr.getBlockSize());
    lookAt = -1;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &texture;

    // draw the vertex array
    target.draw(sprite, states);
}

void Player::handleEvent(sf::Event &event)
{

}

void Player::updateSprite(sf::Time &time, MapManager& mapMgr)
{
    static float texturePosition = 1.f;
    static float s=5;
    texturePosition += s * time.asSeconds();
    if(lookAt == -1)
    {
        sprite.setTextureRect(sf::IntRect(int(texturePosition) * mapMgr.getBlockSize().x,
                                          0,
                                          mapMgr.getBlockSize().x,
                                          mapMgr.getBlockSize().y)
                              );
    }
    else
    {
        sprite.setTextureRect(sf::IntRect(int(texturePosition + 1 ) * mapMgr.getBlockSize().x,
                                          0,
                                          -1 * mapMgr.getBlockSize().x,
                                          mapMgr.getBlockSize().y)
                              );
    }
    if(texturePosition>=2.5f || texturePosition<=0.5f) s *= -1;
    texturePosition = std::min(2.5f, std::max(texturePosition,0.5f));
}

void Player::update(sf::Time &time, MapManager& mapMgr)
{
    updateSprite(time, mapMgr);

    sf::Vector2f move_vec(0.f,0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // left key is pressed: move our character
        move_vec.y = -speed.y;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        // left key is pressed: move our character
        move_vec.x=speed.x;
        lookAt = 1; /// Right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        // left key is pressed: move our character
        move_vec.x = -speed.x;
        lookAt = -1; /// Left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // left key is pressed: move our character
        move_vec.y=speed.y;
    }
    sprite.move(time.asSeconds() * move_vec);

    int x = sprite.getPosition().x / mapMgr.getBlockSize().x;
    int y = sprite.getPosition().y / mapMgr.getBlockSize().y;
    auto blockType = mapMgr.getBlockType(y, x);

    if(blockType==MapManager::BlockType::Tree ||
       blockType==MapManager::BlockType::Stone)
       {
           sprite.move(time.asSeconds() * move_vec * -1.f);
       }
}
